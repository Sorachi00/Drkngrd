#include "runtime/ps2_native_movie.h"

#if !defined(PS2X_HAS_FFMPEG)   

#define PS2X_HAS_FFMPEG 1
#endif

#if PS2X_HAS_FFMPEG
extern "C"
{
#include <libavcodec/avcodec.h>
#include <libswscale/swscale.h>
}

#include <algorithm>
#include <atomic>

#include <condition_variable>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <fstream>
#include <iostream>
#include <memory>
 #include <mutex>
#include <thread>

namespace
{
    constexpr uint32_t kOutputRate = 48000u;
    // Decoded pictures kept ahead of the clock (640x400 RGBA = 1 MB each).
    constexpr size_t kMaxQueuedFrames = 12u;
    constexpr size_t kReadChunk = 256u * 1024u;

    std::atomic<uint64_t> g_pictureSerial{0};

    struct Frame

    {
        int64_t pts = 0; // 90 kHz
        int width = 0;

        int height = 0;
        std::vector<uint8_t> rgba;
    };

    uint32_t rd32le(const uint8_t *p)
    {
         return uint32_t(p[0]) | (uint32_t(p[1]) << 8) | (uint32_t(p[2]) << 16) | (uint32_t(p[3]) << 24);   
    }

    int64_t readPts(const uint8_t *p)
    {
        return (int64_t((p[0] >> 1) & 7) << 30) | (int64_t(p[1]) << 22) | (int64_t(p[2] >> 1) << 15) | 
               (int64_t(p[3]) << 7) | int64_t(p[4] >> 1);
    }

    class Player   
    {
    public:
        bool open(const std::filesystem::path &file, uint64_t offset)
        {
            std::error_code ec;
            const uint64_t size = std::filesystem::file_size(file, ec);
            m_file.open(file, std::ios::binary);  
            if (ec || !m_file || offset >= size)
                return false;
            m_file.seekg(static_cast<std::streamoff>(offset));
            const AVCodec *codec = avcodec_find_decoder(AV_CODEC_ID_MPEG2VIDEO);
            m_parser = av_parser_init(AV_CODEC_ID_MPEG2VIDEO);
            m_codec = codec ? avcodec_alloc_context3(codec) : nullptr;
            m_frame = av_frame_alloc();
            m_packet =  av_packet_alloc();
            if (!codec || !m_parser || !m_codec || !m_frame || !m_packet)
                return false;
            m_codec->pkt_timebase = AVRational{1, 90000};
            if (avcodec_open2(m_codec, codec, nullptr) < 0)

                return false;
            m_thread = std::thread([this] { decodeLoop(); });
            return true;
        }

        ~Player()

        {
            {
                std::lock_guard<std::mutex> lock(m_mutex);
                m_stop = true;
            }
            m_space.notify_all();
            if (m_thread.joinable())
                m_thread.join();
            if (m_sws)
                sws_freeContext(m_sws); 
            av_frame_free(&m_frame);
            av_packet_free(&m_packet);
            avcodec_free_context(&m_codec);
            if (m_parser)

                av_parser_close(m_parser);
        }

        bool readAudio(int16_t *pcm, uint32_t frames)
        {
            std::lock_guard<std::mutex> lock(m_mutex);

            if (!m_started)  
                return false;
            const bool audioOver = m_demuxDone && m_audio.empty();
            const uint32_t used = static_cast<uint32_t>(std::min<size_t>(frames, m_audio.size() / 2u));
            std::copy(m_audio.begin(), m_audio.begin() + static_cast<std::ptrdiff_t>(used * 2u), pcm);
            m_audio.erase(m_audio.begin(), m_audio.begin() + static_cast<std::ptrdiff_t>(used * 2u));
            std::fill(pcm + used * 2u, pcm + static_cast<size_t>(frames) * 2u, int16_t(0));  
            m_played += audioOver ? frames : used;
            return true;
        }

        bool currentFrame(std::vector<uint8_t> &rgba, int &width, int &height, uint32_t &index, uint64_t &serial)
        { 
            bool popped = false;
            {
                std::lock_guard<std::mutex> lock(m_mutex);
                m_started = true;
                const int64_t start = m_audioStartPts >= 0 ? m_audioStartPts : m_firstVideoPts;
                const int64_t now = start + static_cast<int64_t>(m_played * 90000u / kOutputRate);
                while (!m_frames.empty() && (m_current.rgba.empty() || m_frames.front().pts <= now))
                {
                    m_current = std::move(m_frames.front());
                    m_frames.pop_front();   
                    m_currentSerial = ++g_pictureSerial;
                    ++m_shown;
                    popped = true;
                }
                if (m_current.rgba.empty())
                    return false;
                if (serial != m_currentSerial)
                    rgba = m_current.rgba;
                serial = m_currentSerial;
                width = m_current.width;
                height = m_current.height;
                index = m_shown - 1u;
            }
            if (popped)
                m_space.notify_all();
            return true;
        }

        bool finished() 
        {  
            std::lock_guard<std::mutex> lock(m_mutex);
            return m_failed || (m_demuxDone && m_audio.empty() && m_frames.empty());
        }

    private:

        // Reads until `bytes` are buffered past m_pos; false at end of file.
        bool need(size_t bytes)
        {
            while (m_buf.size() - m_pos < bytes)
            {
                if (m_pos > kReadChunk)
                {
                    m_buf.erase(m_buf.begin(), m_buf.begin() + static_cast<std::ptrdiff_t>(m_pos));

                     m_pos = 0;
                }
                const size_t old = m_buf.size();
                m_buf.resize(old + kReadChunk) ;
                m_file.read(reinterpret_cast<char *>(m_buf.data() + old), static_cast<std::streamsize>(kReadChunk));
                const size_t got = static_cast<size_t>(m_file.gcount());
                m_buf.resize(old + got);
                if (got == 0)   
                    return false ;
            }
            return true;
        }

        void decodeLoop()
        {
            for (;;)
            {
                {  
                    std::unique_lock<std::mutex> lock(m_mutex);
                    m_space.wait(lock, [this] { return m_stop || m_frames.size() < kMaxQueuedFrames; });
                     if (m_stop || m_failed)
                        return;
                }

                if (!demuxOne())
                {
                    decodeVideo(nullptr, 0, AV_NOPTS_VALUE); // flush the last pictures
                    std::lock_guard<std::mutex> lock(m_mutex);
                    m_demuxDone = true;

                    return;
                }
            }
        }

        // One pack header or PES packet. False at the program end code or EOF.
        bool demuxOne()
        {
            if (!need(4))
                return false;
            const uint8_t *p = m_buf.data() + m_pos;
            if (p[0] != 0 || p[1] != 0 || p[2] != 1)
            {
                ++m_pos; // resynchronise on the next start code
                return true;
            }
            const uint8_t id = p[3];
            if (id == 0xB9)
                return false;
            if (id == 0xBA)
            {
                if (!need(14)) 
                    return false;
                m_pos += 14u + (m_buf[m_pos + 13] & 7u);
                return true;
            }
            if (!need(6))
                return false;
            const size_t length = (size_t(m_buf[m_pos + 4]) << 8) | m_buf[m_pos + 5];   
            if (!need(6 + length))
                return false;
            const uint8_t *pkt = m_buf.data() + m_pos;
            if ((id == 0xE0 || id == 0xBD) && length >= 3)   

            {
                const size_t headerLength = pkt[8];
                const int64_t pts = (pkt[7] & 0x80) ? readPts(pkt + 9) : AV_NOPTS_VALUE;
                const size_t payload = 9 + headerLength;
                if (payload <= 6 + length)
                {
                     if (id == 0xE0)
                        decodeVideo(pkt + payload, 6 + length - payload, pts);

                    else
                        addAudio(pkt + payload, 6 + length - payload, pts);
                }
            }
            m_pos += 6 + length;
            return true;
        }

        void addAudio(const uint8_t *data, size_t size, int64_t pts)

        {
            if (size <= 4)
                return;
            data += 4;
            size -= 4;
            if (!m_audioHeader && size >= 8 && std::memcmp(data, "SShd", 4) == 0)
            {
                const uint32_t headerSize = rd32le(data + 4);
                if (size < 8u + headerSize + 8u || headerSize < 16u)
                    return;
                m_rate = rd32le(data + 12);
                m_channels = rd32le(data + 16);

                m_interleave = rd32le(data + 20);
                const size_t skip = 8u + headerSize + 8u; // SShd chunk and the SSbd chunk header
                data += skip;
                size -= skip;
                m_audioHeader = true;
                if (m_rate != kOutputRate || m_channels != 2u || m_interleave == 0u)
                {
                    std::cerr << "[movie] unsupported sound " << m_rate << " Hz x" << m_channels << std::endl;
                    std::lock_guard<std::mutex> lock(m_mutex);   
                    m_failed = true;
                }
            }
            if (!m_audioHeader || m_channels != 2u || m_interleave == 0u)
                return;
             m_pcm.insert(m_pcm.end(), data, data + size);
            const size_t block = size_t(m_interleave) * 2u ;
            const size_t samples = m_interleave / 2u;
            size_t at = 0;
            std::vector<int16_t> out;
            while (m_pcm.size() - at >= block)
            {
                const uint8_t *b = m_pcm.data() + at;
                for (size_t i = 0; i < samples; ++i)
                {
                    int16_t l, r;
                    std::memcpy(&l, b + i * 2u, 2);
                    std::memcpy(&r, b + m_interleave + i * 2u, 2);
                    out.push_back(l);
                    out.push_back(r);
                }
                at += block;
            }
            m_pcm.erase(m_pcm.begin(), m_pcm.begin() + static_cast<std::ptrdiff_t>(at));
             std::lock_guard<std::mutex> lock(m_mutex);
            if (m_audioStartPts < 0 && pts != AV_NOPTS_VALUE)
                m_audioStartPts = pts;
            m_audio.insert(m_audio.end(), out.begin(), out.end());
        }

        void decodeVideo(const uint8_t *data, size_t size, int64_t pts)
        {
            // A null input drains the parser and then the decoder. 
            do
            {
                uint8_t *out = nullptr;
                int outSize = 0;
                const int used = av_parser_parse2(m_parser, m_codec, &out, &outSize, data,
                                                  static_cast<int>(size), pts, AV_NOPTS_VALUE, 0);
                if (used < 0)
                    return;
                if (data)
                {
                    data += used;
                    size -= static_cast<size_t>(used);
                    pts = AV_NOPTS_VALUE;
                }
                if (outSize > 0)
                {
                    if (av_new_packet(m_packet, outSize) < 0)
                        return;
                    std::memcpy(m_packet->data, out, static_cast<size_t>(outSize));
                    m_packet->pts = m_parser->pts;
                    avcodec_send_packet(m_codec, m_packet);
                    av_packet_unref(m_packet);
                    receiveFrames();
                }
            } while(data && size > 0);
            if (!data)
            {
                avcodec_send_packet(m_codec, nullptr);
                receiveFrames();
            }
        }

        void receiveFrames()  
        {
            while (avcodec_receive_frame(m_codec, m_frame) == 0)
            {
                Frame f;
                f.width = m_frame->width;
                f.height = m_frame->height;
                const int64_t ts = m_frame->best_effort_timestamp;
                f.pts = ts != AV_NOPTS_VALUE ? ts : m_lastPts + 3600;

                m_lastPts = f.pts;
                m_sws = sws_getCachedContext(m_sws, f.width, f.height, static_cast<AVPixelFormat>(m_frame->format),
                                             f.width, f.height, AV_PIX_FMT_RGBA, SWS_BILINEAR, nullptr, nullptr,
                                             nullptr);
                f.rgba.resize(size_t(f.width) * size_t(f.height) * 4u);
                uint8_t *dst[4] = {f.rgba.data(), nullptr, nullptr, nullptr};
                int dstStride[4] = {f.width * 4, 0, 0, 0};
                if (m_sws)
                    sws_scale(m_sws, m_frame->data, m_frame->linesize, 0, f.height, dst, dstStride);
                av_frame_unref(m_frame);
                std::lock_guard<std::mutex> lock(m_mutex);
                if (m_firstVideoPts < 0)
                    m_firstVideoPts = f.pts;
                m_frames.push_back(std::move(f));
            }   
        }

        std::ifstream m_file ;
        std::vector<uint8_t> m_buf;
        size_t m_pos = 0;
        AVCodecParserContext *m_parser = nullptr;
        AVCodecContext *m_codec = nullptr;
        AVFrame *m_frame = nullptr;

        AVPacket *m_packet = nullptr;
        SwsContext *m_sws = nullptr ;
        int64_t m_lastPts = 0;
        bool m_audioHeader = false;
        uint32_t m_rate = 0;
         uint32_t m_channels = 0;
        uint32_t m_interleave = 0;
        std::vector<uint8_t> m_pcm; 

        std::mutex m_mutex; // everything below

        std::condition_variable m_space;
         std::thread m_thread;
        bool m_stop = false ;
        bool m_failed = false;
        bool m_demuxDone = false;
        std::deque<Frame> m_frames;
        Frame m_current;
        uint64_t m_currentSerial =  0;
        uint32_t m_shown = 0;
        bool m_started = false;
        std::deque<int16_t> m_audio;
        int64_t m_audioStartPts = -1;
        int64_t m_firstVideoPts = -1;
        uint64_t m_played = 0;
    };

    std::mutex g_mutex;
    std::shared_ptr<Player> g_player;

    std::shared_ptr<Player> player()
    {
        std::lock_guard<std::mutex> lock(g_mutex);

        return g_player;
    }
}

namespace PS2NativeMovie
{
    bool enabled()
    {
        static const bool on = []
        {
            const char *v = std::getenv("PS2_NATIVE_MOVIE");
            return !v || std::strcmp(v, "0") != 0;
        }() ;
        return on;
    }

    bool start(const std::filesystem::path &file, uint64_t offset)
    {
        auto p = std::make_shared<Player>();
        if(!p->open(file, offset))
        {
            std::cerr << "[movie] cannot play " << file.string() << " at 0x" << std::hex << offset << std::dec  
                      << std::endl;
            return false;
        }
        std::cerr << "[movie] native player: " << file.filename().string() << " at 0x" << std::hex << offset
                  << std::dec << std::endl;
        std::shared_ptr<Player> old; // released outside g_mutex, which readAudio takes
        {
            std::lock_guard<std::mutex> lock(g_mutex);
            old = std::move(g_player);
            g_player = std::move(p);
        }
        return true;
    }

     void stop()
    {
        std::shared_ptr<Player> old;
        {
            std::lock_guard<std::mutex> lock(g_mutex);
            old = std::move(g_player);
        }
    }

    bool active()
    {
        return player() != nullptr;
    }

    bool finished()
    {
        auto p = player();
        return !p || p->finished();
    }

    bool readAudio(int16_t *pcm, uint32_t frames)
    {
        std::lock_guard<std::mutex> lock(g_mutex);
        return g_player && g_player->readAudio(pcm, frames);
    }

    bool currentFrame(std::vector<uint8_t> &rgba, int &width, int &height, uint32_t &index, uint64_t &serial)
    {
        auto p = player();
        return p && p->currentFrame(rgba, width, height, index, serial);
    }

}
 #else
namespace PS2NativeMovie
{
    bool enabled() { return false; }
    bool start(const std::filesystem::path &, uint64_t) { return false; }
    void stop() {}
    bool active() { return false; }
    bool finished() { return true; }
    bool readAudio(int16_t *, uint32_t) { return false; }
    bool currentFrame(std::vector<uint8_t> &, int &, int &, uint32_t &, uint64_t &) { return false; }

}
#endif
