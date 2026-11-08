#include "runtime/ps2_vdisc.h"
#include "ps2_vdisc_mods.h"
#include "dk_formats/dk_formats.h"

#if defined(PS2X_HOST_SDL3)
#include <SDL3/SDL.h> 
#else
#include "raylib.h"   
#endif

#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
#include <map>   
#include <sstream>
#include <unordered_map>

#if !defined(PS2X_HAS_FFMPEG)
#define PS2X_HAS_FFMPEG 1
#endif

#if PS2X_HAS_FFMPEG
extern "C"
{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/channel_layout.h>
#include <libswresample/swresample.h>
}
#endif


namespace
{
    namespace fs = std::filesystem;

    std::FILE *openFile(const fs::path &path, const char *mode)
    {
#if defined(_WIN32)
        const std::wstring wmode(mode, mode + std::strlen(mode));
        return ::_wfopen(path.c_str(), wmode.c_str()) ;
#else
        return std::fopen(path.c_str(), mode);
#endif
    }

    bool readBytes(const fs::path &path, std::vector<uint8_t> &out)
    {
        std::FILE *f = openFile(path, "rb");
        if (!f)
             return false;
        std::error_code ec;
        out.resize(static_cast<size_t>(fs::file_size(path, ec)));
        const bool ok = !ec && std::fread(out.data(), 1, out.size(), f) == out.size();
        std::fclose(f);
        return ok;

    }

    bool writeBytes(const fs::path &path, const void *data, size_t size)
     {
        std::error_code ec;
        fs::create_directories(path.parent_path(), ec);
        std::FILE *f = openFile(path, "wb");
        if (!f)
            return false;
        const bool ok =  std::fwrite(data, 1, size, f) == size;
        return std::fclose(f) == 0 && ok;
    }

    std::string utf8(const fs::path &path)
    {
        const std::u8string s = path.u8string();
        return std::string(s.begin(), s.end());  
    }

#if defined(PS2X_HOST_SDL3)
    // ---- PNG (SDL3, through memory: the files are opened as std::filesystem paths) ----

    bool writePng(const fs::path &path, const dk_formats::WzimImage &image)
    {
        SDL_Surface *surface = SDL_CreateSurfaceFrom(int(image.width), int(image.height), SDL_PIXELFORMAT_ABGR8888,
                                                     const_cast<uint8_t *>(image.rgba.data()), int(image.width) * 4);
        SDL_IOStream *io = SDL_IOFromDynamicMem();
        bool ok = surface && io && SDL_SavePNG_IO(surface, io, false);
        if (ok)
        {
            const auto *png = static_cast<const uint8_t *>(
                SDL_GetPointerProperty(SDL_GetIOProperties(io), SDL_PROP_IOSTREAM_DYNAMIC_MEMORY_POINTER, nullptr));
            const Sint64 size = SDL_GetIOSize(io);

            ok = png && size > 0 && writeBytes(path, png, static_cast<size_t>(size));

        }
        if (io)

            SDL_CloseIO(io);
        SDL_DestroySurface(surface);
        return ok;
    }

    bool readPng(const fs::path &path, dk_formats::WzimImage &image)
    {
        std::vector<uint8_t> bytes;
        if (!readBytes(path, bytes)) 
            return false;
        SDL_Surface *loaded = SDL_LoadPNG_IO(SDL_IOFromConstMem(bytes.data(), bytes.size()), true);
        if (!loaded)
            return false;
        // ABGR8888: bytes R, G, B, A in memory.

        SDL_Surface *rgba = SDL_ConvertSurface(loaded, SDL_PIXELFORMAT_ABGR8888);
        SDL_DestroySurface(loaded);
        if (!rgba)
             return false;
        image.width = static_cast<uint32_t>(rgba->w);
        image.height = static_cast<uint32_t>(rgba->h);
        image.rgba.resize(size_t(rgba->w) * size_t(rgba->h) * 4u);
         for (int y = 0; y < rgba->h; ++y)   
            std::memcpy(image.rgba.data() + size_t(y) * size_t(rgba->w) * 4u,
                        static_cast<const uint8_t *>(rgba->pixels) + size_t(y) * size_t(rgba->pitch), size_t(rgba->w) * 4u);
        SDL_DestroySurface(rgba);
        return true;
    }
#else
    // ---- PNG (raylib, through memory: its file functions take ANSI paths) ----

    bool writePng(const fs::path &path, const dk_formats::WzimImage &image)
    {
        Image img{};

        img.data = const_cast<uint8_t *>(image.rgba.data());
        img.width = static_cast<int>(image.width);
        img.height = static_cast<int>(image.height);
        img.mipmaps = 1;

        img.format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8;

        int size = 0;
        unsigned char *png = ExportImageToMemory(img, ".png", &size);
        const bool ok = png && size > 0 && writeBytes(path, png, static_cast<size_t>(size));
        MemFree(png);
        return ok;
    }

    bool readPng(const fs::path &path, dk_formats::WzimImage &image)
    {
        std::vector<uint8_t> bytes;
        if (!readBytes(path, bytes)) 
            return false;
         Image img = LoadImageFromMemory(".png", bytes.data(), static_cast<int>(bytes.size()));
        if (!img.data)
            return false;

        ImageFormat(&img, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);

        image.width = static_cast<uint32_t>(img.width);
        image.height = static_cast<uint32_t>(img.height);
        const auto *p = static_cast<const uint8_t *>(img.data);

        image.rgba.assign(p, p + size_t(img.width) * size_t(img.height) * 4u);
        UnloadImage(img);
        return true;
    }
#endif

    // ---- audio (FFmpeg): FLAC out; any audio file in, converted to the game's rate ----

#if PS2X_HAS_FFMPEG
    bool writeFlac(const fs::path &path, const dk_formats::CadsAudio &audio, std::string &error)
    {

        const std::string file = utf8(path);
        std::error_code ec;
        fs::create_directories(path.parent_path(), ec);
        AVFormatContext *oc = nullptr;
        AVCodecContext *c = nullptr;
        AVFrame *frame = nullptr;
        AVPacket *pkt = nullptr;
        bool ok = false;
        const AVCodec *codec = avcodec_find_encoder(AV_CODEC_ID_FLAC);
        do
        {

            if (!codec || audio.channels == 0 || audio.sampleRate == 0 ||
                avformat_alloc_output_context2(&oc, nullptr, "flac", file.c_str()) < 0)
                break;
            AVStream *st = avformat_new_stream(oc, nullptr);
            c = avcodec_alloc_context3(codec);
            frame = av_frame_alloc();
            pkt = av_packet_alloc();
            if (!st || !c || !frame || !pkt)
                break;
            c->sample_fmt = AV_SAMPLE_FMT_S16;
            c->sample_rate =  static_cast<int>(audio.sampleRate);
            av_channel_layout_default(&c->ch_layout, static_cast<int>(audio.channels));
            c->time_base = AVRational{1, c->sample_rate};
            if (avcodec_open2(c, codec, nullptr) < 0 || avcodec_parameters_from_context(st->codecpar, c) < 0 ||
                avio_open(&oc->pb, file.c_str(), AVIO_FLAG_WRITE) < 0)
                break;
            st->time_base = c->time_base;
            if (avformat_write_header(oc, nullptr) < 0)
                break;
             const int frameSize = c->frame_size > 0 ? c->frame_size : 4608;

            frame->format = AV_SAMPLE_FMT_S16;
            frame->sample_rate = c->sample_rate;
            frame->nb_samples = frameSize;
            av_channel_layout_copy(&frame->ch_layout, &c->ch_layout);
            if (av_frame_get_buffer(frame, 0) < 0)
                break;
            auto drain = [&]()
            {
                while (avcodec_receive_packet(c, pkt) == 0)
                {
                    av_packet_rescale_ts(pkt, c->time_base, st->time_base);
                    pkt->stream_index = st->index;
                    if (av_interleaved_write_frame(oc, pkt) < 0)
                        return false;
                }
                return true;
            };
            const size_t total = audio.pcm.size() / audio.channels;
            ok = true;
            for (size_t pos = 0; ok && pos < total; pos += size_t(frameSize))
            {
                const size_t n = std::min<size_t>(size_t(frameSize), total - pos);
                ok = av_frame_make_writable(frame) >= 0;
                if (!ok)
                    break; 

                frame->nb_samples = static_cast<int>(n);
                std::memcpy(frame->data[0], audio.pcm.data() + pos * audio.channels, n * audio.channels * 2u);
                frame->pts = static_cast<int64_t>(pos);
                ok = avcodec_send_frame(c, frame) >= 0 && drain();
            }
            ok = ok && avcodec_send_frame(c, nullptr) >= 0 && drain() && av_write_trailer(oc) >= 0;
        } while (false);
        if (oc && oc->pb)
            avio_closep(&oc->pb);
        avformat_free_context(oc);
         avcodec_free_context(&c);
        av_frame_free(&frame);
        av_packet_free(&pkt);
        if (!ok)
            error = "cannot write " + file;
        return ok;
    }

    bool readAudio(const fs::path &path, uint32_t rate, uint32_t channels, dk_formats::CadsAudio &audio,
                   std::string &error)
    {
        const std::string file = utf8(path);
        AVFormatContext *ic =  nullptr;
        AVCodecContext *d = nullptr;
        SwrContext *swr = nullptr;

        AVFrame *frame = av_frame_alloc();
        AVPacket *pkt = av_packet_alloc();
        AVChannelLayout outLayout{};   
        av_channel_layout_default(&outLayout, static_cast<int>(channels));
        audio.sampleRate = rate;
        audio.channels = channels;
        audio.pcm.clear();
        bool ok = false;
        do
        {
            if (!frame || !pkt || avformat_open_input(&ic, file.c_str(), nullptr, nullptr) < 0 ||
                avformat_find_stream_info(ic, nullptr) < 0)
                break;
            const AVCodec *dec = nullptr ;
            const int index = av_find_best_stream(ic, AVMEDIA_TYPE_AUDIO, -1, -1, &dec, 0);
            if (index < 0 || !dec)
                break;   
            d = avcodec_alloc_context3(dec);
            if (!d || avcodec_parameters_to_context(d, ic->streams[index]->codecpar) < 0 ||
                avcodec_open2(d, dec, nullptr) < 0)
                break;
            if (swr_alloc_set_opts2(&swr, &outLayout, AV_SAMPLE_FMT_S16, static_cast<int>(rate), &d->ch_layout,
                                    d->sample_fmt, d->sample_rate, 0, nullptr) < 0 ||
                swr_init(swr) < 0)
                break;
            auto convert = [&](const AVFrame *in)
            {
                const int room = swr_get_out_samples(swr, in ? in->nb_samples : 0);
                if (room <= 0)
                    return true;  
                const size_t old = audio.pcm.size();
                audio.pcm.resize(old + size_t(room) * channels); 
                uint8_t *out = reinterpret_cast<uint8_t *>(audio.pcm.data() + old);
                const int got = swr_convert(swr, &out, room, in ? const_cast<const uint8_t **>(in->extended_data) : nullptr,
                                             in ? in->nb_samples : 0);
                if (got < 0)
                    return false;
                audio.pcm.resize(old + size_t(got) * channels);
                return true;
             };
            ok = true;
            while (ok && av_read_frame(ic, pkt) >= 0)
            {
                if (pkt->stream_index == index && avcodec_send_packet(d, pkt) >= 0)
                {
                    while (ok && avcodec_receive_frame(d, frame) == 0)
                        ok = convert(frame);
                }
                av_packet_unref(pkt);
            }
            if (ok && avcodec_send_packet(d, nullptr) >= 0)
            {
                while (ok && avcodec_receive_frame(d, frame) == 0)
                    ok = convert(frame);
            }
            ok = ok && convert(nullptr);
        } while (false);
        swr_free(&swr);
        avcodec_free_context(&d);
        avformat_close_input(&ic);
        av_frame_free(&frame);   
        av_packet_free(&pkt);
        av_channel_layout_uninit(&outLayout);
        if (!ok)
            error = "cannot read the sound file " + file;
        return ok;
    }
#endif

    // ---- pc.manifest: pc <pc path> <game path> <image index> <size> <time> ----

    struct PcRecord
    {
        std::string pc;   // relative to the data folder, '/' separated
        std::string game; // relative to the data folder
        uint32_t image = 0 ;

        uint64_t size = 0;
        int64_t time = 0;
    };

    bool statFile(const fs::path &path, uint64_t &size, int64_t &time)
    {
        std::error_code ec ;
        size =  fs::file_size(path, ec);
        if (ec)
            return false;

        time = static_cast<int64_t>(fs::last_write_time(path, ec).time_since_epoch().count());
        return !ec;
    }

    bool readManifest(const fs::path &dataDir, std::vector<PcRecord> &records)
    {
        std::ifstream in(dataDir / "pc" / "pc.manifest", std::ios::binary);
        if (!in)
            return false;
        std::string line;
        while (std::getline(in, line))
        {
            if (!line.empty() && line.back() == '\r')
                line.pop_back();
            std::vector<std::string> f;

            std::stringstream ss(line);
            for (std::string part; std::getline(ss, part, '\t');)
                 f.push_back(part);
             if (f.size() != 6 || f[0] != "pc")
                continue;
            PcRecord r;
            r.pc = f[1];
            r.game = f[2];
            r.image = static_cast<uint32_t>(std::strtoul(f[3].c_str(), nullptr, 10));
            r.size = std::strtoull(f[4].c_str(), nullptr, 10);
            r.time = std::strtoll(f[5].c_str(), nullptr, 10);
            records.push_back(std::move(r));
        }
        return true;
    }


    bool writeManifest(const fs::path &dataDir, const std::vector<PcRecord> &records)
    {
        std::ostringstream out;
        for (const PcRecord &r : records)
            out << "pc\t" << r.pc << "\t" << r.game << "\t" << r.image << "\t" << r.size << "\t" << r.time << "\n";
        const std::string text = out.str();
         const fs::path tmp = dataDir / "pc" / "pc.manifest.tmp";
        std::error_code ec;
        if (!writeBytes(tmp, text.data(), text.size()))
            return false;
        fs::rename(tmp, dataDir / "pc" / "pc.manifest", ec);
        return !ec;
    }

    std::string lowerExt(const fs::path &path)
    {
        std::string ext = path.extension().string();
        std::transform(ext.begin(), ext.end(), ext.begin(), [](unsigned char c) { return char(std::tolower(c)); });
        return ext;
    }

    // Writes PC copies ({file, image index}) into the game file `bytes` (extension `ext`).
    bool applyPcCopies(const std::string &ext, std::vector<uint8_t> &bytes,
                       const std::vector<std::pair<fs::path, uint32_t>> &pcs, std::string &why)
    {
        if (ext == ".zim")
        {
            std::vector<dk_formats::WzimImage> images;
            if (!dk_formats::wzimDecode(bytes.data(), bytes.size(), images, why))
                return false;
            for (const auto &[file, k] : pcs)

            {
                dk_formats::WzimImage image;  
                if (k >= images.size() || !readPng(file, image) || image.width != images[k].width ||
                    image.height != images[k].height)
                {

                    why = "the PNG must keep its size (" + utf8(file) + ")";
                    return false;
                }
                images[k] = std::move(image);

            }

            return dk_formats::wzimEncode(bytes, images, why);
        } 
        if (ext == ".kps")
        {
            std::vector<uint8_t> text;
            return readBytes(pcs.front().first, text) &&
                   dk_formats::kpsEncode(std::string(text.begin(), text.end()), bytes, why);
        }
        if (ext == ".cads")
        {
#if PS2X_HAS_FFMPEG
            dk_formats::CadsAudio original;
            dk_formats::CadsAudio audio;
            return dk_formats::cadsDecode(bytes.data(), bytes.size(), original, why) &&
                   readAudio(pcs.front().first, original.sampleRate, original.channels, audio, why) &&
                   dk_formats::cadsEncode(bytes, audio, why);
#else
             why = "no FFmpeg in this build";
            return false;
#endif
        }
        why = "no PC format for " + ext;
        return false;

    }


    // PC copy path of image `k` of a game file: "pc/<path without ext><_k>.<ext>".
     std::string pcPath(const std::string &game, const char *ext, uint32_t k)
    {
        const fs::path rel(game);
        std::string out = "pc/" + (rel.parent_path() / rel.stem()).generic_string(); 
        if (k != 0)
            out += "_" + std::to_string(k);
        return out + ext;
    }
}

namespace PS2VDisc
{
    bool exportPcFiles(const fs::path &dataDir, const Progress &progress, std::string &error)

    {
        std::vector<std::string> files;
        std::error_code ec;
        for (auto it = fs::recursive_directory_iterator(dataDir, ec); !ec && it != fs::recursive_directory_iterator();
             it.increment(ec))
        {
            const fs::path rel = fs::relative(it->path(), dataDir, ec);
            const std::string top = rel.begin() != rel.end() ? rel.begin()->string() : std::string();  
            if (it->is_directory() && (top == "pc" || rel.generic_string() == "image/compressed"))
            {
                it.disable_recursion_pending();
                 continue;
            } 
            const std::string ext = lowerExt(rel);
            if (it->is_regular_file() && (ext == ".zim" || ext == ".kps" || ext == ".cads"))
                files.push_back(rel.generic_string()) ;
        }
        std::sort(files.begin(), files.end());
        fs::remove_all(dataDir / "pc", ec);

        std::vector<PcRecord> records;
        uint32_t failed = 0, skipped = 0;
        std::vector<uint8_t> bytes;
        for (size_t i = 0; i < files.size(); ++i)
        {
            if (progress && (i % 64) == 0)
                progress("export PC files", i, files.size());
            const std::string &game = files[i];
            const std::string ext = lowerExt(game);
            std::string why;
            std::vector<std::string> written;
            bool ok = readBytes(dataDir / fs::path(game), bytes);

            if (ok && ext == ".zim")
            {
                std::vector<dk_formats::WzimImage> images;
                ok = dk_formats::wzimDecode(bytes.data(), bytes.size(), images, why);
                for (uint32_t k = 0; ok && k < images.size(); ++k)
                {
                    written.push_back(pcPath(game, ".png", k));
                     ok = writePng(dataDir / fs::path(written.back()), images[k]);
                }
            }
            else if (ok && ext == ".kps")
             {   
                // 20 ".kps" entries are not text packs (no "KPS_" magic): no PC copy.
                if (bytes.size() < 4 || std::memcmp(bytes.data(), "KPS_", 4) != 0)
                {
                    ++skipped ;
                    continue;
                }
                std::string text;
                ok = dk_formats::kpsDecode(bytes.data(), bytes.size(), text, why);
                written.push_back(pcPath(game, ".txt", 0));
                ok = ok && writeBytes(dataDir / fs::path(written.back()), text.data(), text.size());
             }
            else if (ok && ext == ".cads")
            {
#if PS2X_HAS_FFMPEG
                dk_formats::CadsAudio audio; 
                ok = dk_formats::cadsDecode(bytes.data(), bytes.size(), audio, why);
                written.push_back(pcPath(game, ".flac", 0));
                ok = ok && writeFlac(dataDir / fs::path(written.back()), audio, why);
#else
                continue;
#endif

            }
            if (!ok)
            {   
                ++failed;
                std::cerr << "[pc] cannot convert " << game << (why.empty() ? "" : ": " + why) << std::endl;
                continue;

            }
            for (uint32_t k = 0; k < written.size(); ++k)
            {
                PcRecord r;
                r.pc = written[k];
                r.game = game;
                r.image = k;
                statFile(dataDir / fs::path(r.pc), r.size, r.time);
                records.push_back(std::move(r));
            }
        }
        if (!writeManifest(dataDir, records))
        {
            error = "cannot write pc/pc.manifest";
            return false;
        }
        std::cout << "[pc] " << records.size() << " PC files from " << files.size() - failed - skipped
                  << " game files (" << failed << " not converted, " << skipped << " not text packs)" << std::endl;
        return true;
     }

    uint32_t importPcFiles(const fs::path &dataDir)

    {
        std::vector<PcRecord> records;
        if (!readManifest(dataDir, records))
            return 0;
        // Game files with an edited PC copy, in manifest order.
        std::map<std::string, std::vector<size_t>> edited;
        for (size_t i = 0; i < records.size(); ++i)
        {
            uint64_t size = 0;
            int64_t time = 0;
            if (statFile(dataDir / fs::path(records[i].pc), size, time) &&
                (size != records[i].size || time != records[i].time))
                edited[records[i].game].push_back(i);
        }
        uint32_t changed = 0;
        for (const auto &[game, list] : edited)
        {
            const fs::path gamePath = dataDir / fs::path(game);
            std::vector<uint8_t> bytes;
            std::string why;
            bool ok = readBytes(gamePath, bytes);
            const size_t oldSize = bytes.size();
            std::vector<std::pair<fs::path, uint32_t>> pcs;
            for(size_t i : list)
                pcs.emplace_back(dataDir / fs::path(records[i].pc), records[i].image);
            ok = ok && applyPcCopies(lowerExt(game), bytes, pcs, why);
            if (ok && bytes.size() != oldSize)
            {
                ok = false;
                why = "the game file would change size (" + std::to_string(oldSize) + " -> " +
                      std::to_string(bytes.size()) + " bytes); put the PC copy in a mod (mods/<name>/pc/...) for that";
            }
            if (ok)
            {
                // Keep the original once, then write the new game file.
                const fs::path original = dataDir / "pc" / "_original" / fs::path(game);
                std::error_code ec ;
                if (!fs::exists(original, ec))
                {
                    fs::create_directories(original.parent_path(), ec);
                    fs::copy_file(gamePath, original, ec);
                    ok = !ec;
                    why = ok ? why : "cannot keep the original of " + game;
                } 
                fs::path tmp = gamePath;
                tmp += ".tmp";
                ok = ok && writeBytes(tmp, bytes.data(), bytes.size());

                if (ok)
                {
                    fs::rename(tmp, gamePath, ec);

                    ok = !ec;
                }
                if (!ok)
                    fs::remove(tmp, ec);
                why = ok || !why.empty() ? why : "cannot write " + game;
            }
            if (!ok)
            {
                std::cerr << "[pc] edit of " << game << " not used: " << why << std::endl;
                continue;
            }
            ++changed;
            std::cerr << "[pc] edit used: " << game << std::endl;
            for (size_t i : list)
                statFile(dataDir / fs::path(records[i].pc), records[i].size, records[i].time);
        }
        if (changed != 0)
            writeManifest(dataDir, records);
        return changed;
    }

    uint32_t buildModPcFiles(const fs::path &dataDir)
    {
        const std::vector<fs::path> mods = ps2_mods::modDirectories();
        std::vector<PcRecord> records;
        bool haveRecords = false;
        std::unordered_map<std::string, size_t> byPc; // lower-case PC path -> record
        auto lower = [](std::string s) 
        {
            std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c) { return char(std::tolower(c)); });
            return s;
        };
        auto stamp = [](const fs::path &path)
        {
            uint64_t size = 0;
            int64_t time = 0;
            statFile(path, size, time);
            return std::to_string(size) + ":" + std::to_string(time);
        };

        uint32_t built = 0;
        for (const fs::path &dir : mods)
        {
            std::error_code ec;
            if (!fs::is_directory(dir / "pc", ec))
                continue;
            if (!haveRecords)
            {
                haveRecords = true;
                if (!readManifest(dataDir, records))
                    ps2_mods::log("[mods] no " + utf8(dataDir / "pc" / "pc.manifest") +
                                  ": PC copies of mods cannot be used (start once with --export-pc)");
                for (size_t i = 0; i < records.size(); ++i)
                    byPc[lower(records[i].pc)] = i;
            }
            const std::string mod = dir.filename().string();
            // Game file -> its PC copies in this mod.
            std::map<std::string, std::vector<std::pair<fs::path, uint32_t>>> edits;
            for (auto it = fs::recursive_directory_iterator(dir / "pc", ec);
                 !ec && it != fs::recursive_directory_iterator(); it.increment(ec))
            {

                std::error_code fileEc;
                if (!it->is_regular_file(fileEc))
                    continue ;
                const std::u8string relU8 = fs::relative(it->path(), dir / "pc", fileEc).generic_u8string();
                const std::string rel = "pc/" + std::string(relU8.begin(), relU8.end());
                const auto record = byPc.find(lower(rel));
                if (record == byPc.end())
                { 
                    if (!records.empty())
                        ps2_mods::log("[mods] " + mod + ": " + rel + " is not a PC copy of a game file (not used)");
                    continue;
                }
                edits[records[record->second].game].emplace_back(it->path(), records[record->second].image);
            }

            const fs::path cache = dir / ".cache";
            std::map<std::string, std::string> oldStamps, newStamps;
            {
                std::ifstream in(dir / ".cache.manifest", std::ios::binary);
                for (std::string line; std::getline(in, line);)
                {
                    const size_t tab = line.find('\t');
                    if (tab != std::string::npos)
                        oldStamps[line.substr(0, tab)] = line.substr(tab + 1);
                }
            }
             uint32_t madeHere = 0;
            for (auto &[game, pcs] : edits)
            {
                fs::path base = dir / "data" / fs::path(game);
                if (!fs::exists(base, ec))
                    base = fs::exists(dataDir / "pc" / "_original" / fs::path(game), ec)
                               ? dataDir / "pc" / "_original" / fs::path(game)
                               : dataDir / fs::path(game);
                std::sort(pcs.begin(), pcs.end(), [](const auto &a, const auto &b) { return a.second < b.second; });
                std::string inputs = utf8(base) + "|" + stamp(base);
                for (const auto &[file, k] : pcs)
                    inputs += "|" + std::to_string(k) + "=" + stamp(file);
                const fs::path out = cache / fs::path(game) ;
                if (oldStamps[game] == inputs && fs::exists(out, ec))
                { 
                    newStamps[game] = inputs;
                    continue;
                }
                std::vector<uint8_t> bytes;

                std::string why;

                const size_t oldSize = fs::file_size(base, ec);
                if (!readBytes(base, bytes) || !applyPcCopies(lowerExt(game), bytes, pcs, why) ||
                    !writeBytes(out, bytes.data(), bytes.size()))
                {
                    fs::remove(out, ec);

                    ps2_mods::log("[mods] " + mod + ": PC copy of " + game + " not used: " +
                                  (why.empty() ? "cannot read or write the file" : why));  
                    continue;
                }
                newStamps[game] = inputs;
                ++built;

                ++madeHere;
                if (bytes.size() != oldSize)
                    ps2_mods::log("[mods] " + mod + ": " + game + " " + std::to_string(oldSize) + " -> " +
                                  std::to_string(bytes.size()) + " bytes");
            }
            if (madeHere != 0)
                ps2_mods::log("[mods] " + mod + ": " + std::to_string(madeHere) + " game file(s) made from PC copies");
            // Game files whose PC copies are gone.

            for (const auto &[game, inputs] : oldStamps) 
                if (!newStamps.count(game))
                    fs::remove(cache / fs::path(game), ec);
            std::ostringstream text;
            for (const auto &[game, inputs] : newStamps)   
                text << game << "\t" << inputs << "\n";
            const std::string s = text.str();
            if (newStamps.empty())
                fs::remove(dir / ".cache.manifest", ec);
            else
                writeBytes(dir / ".cache.manifest", s.data(), s.size());
        }
        return built;
    }
}
