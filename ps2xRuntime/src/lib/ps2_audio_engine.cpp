#include "runtime/ps2_audio_engine.h"

#include "runtime/ps2_native_movie.h"
#include "ps2_host_backend.h"

#include <algorithm>
#include <atomic>
#include <cmath>
#include <cstdio>
#include <cstdlib>
 #include <cstring> 
#include <iostream>
#include <mutex>
#include <vector>

// Ported from the earlier Drakengard port (SR Ps2: ps2xRuntime/src/lib/ps2_audio.cpp).

namespace
{
    using namespace ps2x::iop::sd;

    constexpr uint32_t kSdrInit = 0x8000u;
    constexpr uint32_t kSdrSetParam = 0x8010u;
    constexpr uint32_t kSdrGetParam = 0x8020u;
    constexpr uint32_t kSdrSetSwitch = 0x8030u;
    constexpr uint32_t kSdrGetSwitch = 0x8040u;
    constexpr uint32_t kSdrSetAddr = 0x8050u;
    constexpr uint32_t kSdrGetAddr = 0x8060u;
    constexpr uint32_t kSdrSetCoreAttr = 0x8070u;
    constexpr uint32_t kSdrGetCoreAttr = 0x8080u;
    constexpr uint32_t kSdrNote2Pitch = 0x8090u;
    constexpr uint32_t kSdrPitch2Note = 0x80A0u;
    constexpr uint32_t kSdrProcBatch = 0x80B0u;
    constexpr uint32_t kSdrProcBatchEx = 0x80C0u;
    constexpr uint32_t kSdrVoiceTrans = 0x80D0u;
    constexpr uint32_t kSdrBlockTrans = 0x80E0u;
    constexpr uint32_t kSdrVoiceTransStatus = 0x80F0u;
    constexpr uint32_t kSdrBlockTransStatus = 0x8100u;   
    constexpr uint32_t kSdrStopTrans = 0x81A0u;
    constexpr uint32_t kSdrdrvSid =  0x80000701u;
    constexpr uint32_t kVoiceSlots = 24u;

    // PS2_AUDIO_DUMP=<file.wav>: everything the engine outputs.
    struct WavDump
    {
        std::FILE *file = nullptr;
        uint64_t dataBytes = 0;
        uint32_t writes = 0;

        bool open(const char *path)
        {
            file = std::fopen(path, "wb");
            if (!file)
                return false;
            writeHeader(0u);
            return true;
         }

        void writeHeader(uint32_t dataSize)
        {

            const uint32_t sampleRate =  PS2Spu2::kSampleRate;

            const uint32_t byteRate = sampleRate * 4u;
            uint8_t h[44];
            std::memcpy(h, "RIFF", 4);
            const uint32_t riffSize = 36u + dataSize;
            std::memcpy(h + 4, &riffSize, 4);
            std::memcpy(h + 8, "WAVEfmt ", 8);
            const uint32_t fmtSize = 16u;
            std::memcpy(h + 16, &fmtSize, 4);
            const uint16_t pcmTag = 1u;
            const uint16_t channels = 2u;
             std::memcpy(h + 20, &pcmTag, 2);
            std::memcpy(h + 22, &channels, 2);
            std::memcpy(h + 24, &sampleRate, 4);
            std::memcpy(h + 28, &byteRate, 4);
            const uint16_t blockAlign = 4u;   
            const uint16_t bits = 16u;
            std::memcpy(h + 32, &blockAlign, 2);
             std::memcpy(h + 34, &bits, 2);
            std::memcpy(h + 36, "data", 4);  
            std::memcpy(h + 40, &dataSize, 4);
            std::fseek(file, 0, SEEK_SET);
            std::fwrite(h, 1, sizeof(h), file) ;
            std::fseek(file, 0, SEEK_END);
        }

        void write(const int16_t *pcm, uint32_t frames)
         {
            if (!file)
                return;
            std::fwrite(pcm, sizeof(int16_t) * 2u, frames, file);
            dataBytes += static_cast<uint64_t>(frames) * 4u;

            if ((++writes & 0x3Fu) == 0u)
                std::fflush(file);
        }

        void close()
        {
            if (!file)
                return;
            writeHeader(static_cast<uint32_t>(std::min<uint64_t>(dataBytes, 0xFFFFFFFFu - 44u)));
            std::fclose(file);
            file = nullptr;
        }
    };

    void audioStreamCallback(void *bufferData, unsigned int frames)
    {

        if (bufferData && frames != 0u)
            PS2AudioEngine::instance().render(static_cast<int16_t *>(bufferData), frames);
    }

     uint32_t note2Pitch(uint32_t centerNote, uint32_t centerFine, uint32_t note, int32_t fine)
    {
        const double semitones = (static_cast<double>(note) - static_cast<double>(centerNote)) +
                                 (static_cast<double>(fine) - static_cast<double>(centerFine)) / 128.0;
        const double pitch = 4096.0 * std::pow(2.0, semitones / 12.0);
        return static_cast<uint32_t>(std::clamp(pitch, 0.0, 16383.0));
    }

    uint32_t pitch2Note(uint32_t centerNote, uint32_t centerFine, uint32_t pitch)
    {
        if (pitch == 0u)
            return 0u;
        const double semitones = 12.0 * std::log2(static_cast<double>(pitch) / 4096.0);
        const double total = static_cast<double>(centerNote) * 128.0 + static_cast<double>(centerFine) + semitones * 128.0;
        const int32_t clamped = static_cast<int32_t>(std::clamp(total, 0.0, 127.0 * 128.0 + 127.0));
        return (static_cast<uint32_t>(clamped / 128) << 8) | static_cast<uint32_t>(clamped % 128);
    }

}


struct PS2AudioEngine::Impl
{
#if !defined(PLATFORM_VITA) 
    AudioStream stream{};
#endif
    bool streaming = false;
    std::atomic<float> masterVolume{1.0f};
    std::atomic<bool> muted{false};
    bool volumeFromEnv = false;
    bool muteFromEnv = false;
    PS2Spu2::GuestResolver resolver;
    std::mutex outputMutex; // dump
    WavDump dump; 
    std::vector<int16_t> renderMovie; 
};

PS2AudioEngine &PS2AudioEngine::instance()
{
    static PS2AudioEngine engine;
    return engine;
}

PS2AudioEngine::PS2AudioEngine() : m_impl(std::make_unique<Impl>())
{
    if (const char *env = std::getenv("PS2_AUDIO_VOLUME"))
    {
        const float parsed = static_cast<float>(std::atof(env));   
        if (parsed >= 0.0f && parsed <= 4.0f)
        {
            m_impl->masterVolume = parsed;
            m_impl->volumeFromEnv = true;
        }
    }
    if (const char *env = std::getenv("PS2_AUDIO_MUTE"))
    {
        m_impl->muted = env[0] != '0';
        m_impl->muteFromEnv = true;
    }
}

PS2AudioEngine::~PS2AudioEngine()
 {
    stop();
}

void PS2AudioEngine::start(PS2Spu2::GuestResolver resolver, bool audioDeviceReady)
{
    m_impl->resolver = resolver;

    m_spu2.attachGuestMemory(std::move(resolver)) ;

    if (const char *path = std::getenv("PS2_AUDIO_DUMP"))
    {
        std::lock_guard<std::mutex> lock(m_impl->outputMutex);
        if (path[0] != '\0' && !m_impl->dump.file && m_impl->dump.open(path))  
             std::cerr << "[audio] dumping mixer output to " << path << std::endl;
    }

#if !defined(PLATFORM_VITA)
    if (!audioDeviceReady || m_impl->streaming)
        return;
    m_impl->stream = LoadAudioStream(PS2Spu2::kSampleRate, 16, 2);
    SetAudioStreamCallback(m_impl->stream, audioStreamCallback);
    PlayAudioStream(m_impl->stream);
    m_impl->streaming = true;
    std::cerr << "[audio] SPU2 mixer streaming at " << PS2Spu2::kSampleRate << " Hz" << std::endl;

#else
    (void)audioDeviceReady;
#endif
}   

void PS2AudioEngine::stop()
{
#if !defined(PLATFORM_VITA)
    if (m_impl->streaming)
    {
        StopAudioStream(m_impl->stream);
        UnloadAudioStream(m_impl->stream);
        m_impl->streaming = false;
    }
#endif
    std::lock_guard<std::mutex> lock(m_impl->outputMutex);   
    m_impl->dump.close();   
}

void PS2AudioEngine::reset()
{

    m_spu2.reset();
}

void PS2AudioEngine::render(int16_t *pcm, uint32_t frames)
{
    Impl *impl = m_impl.get();
    std::vector<int16_t> &movie = impl->renderMovie;
    movie.resize(static_cast<size_t>(frames) * 2u);
    const bool moviePlaying = PS2NativeMovie::readAudio(movie.data(), frames);
    m_spu2.mix(pcm, frames, moviePlaying ? movie.data() : nullptr);
    {
        std::lock_guard<std::mutex> lock(impl->outputMutex);
        impl->dump.write(pcm, frames);
    }
    const float masterVolume = impl->masterVolume.load(std::memory_order_relaxed);
     if (masterVolume != 1.0f)
    {
        for (uint32_t i = 0; i < frames * 2u; ++i)

        {
            const float v = static_cast<float>(pcm[i]) * masterVolume;
            pcm[i] = static_cast<int16_t>(std::clamp(v, -32768.0f, 32767.0f));
        }
    }
    if (impl->muted.load(std::memory_order_relaxed))
        std::memset(pcm, 0, static_cast<size_t>(frames) * 4u);
}

void PS2AudioEngine::setMasterVolume(float volume)
{
    if (!m_impl->volumeFromEnv)
        m_impl->masterVolume.store(std::clamp(volume, 0.0f, 4.0f), std::memory_order_relaxed);
}

float PS2AudioEngine::masterVolume() const
{
    return m_impl->masterVolume.load(std::memory_order_relaxed);
}

void PS2AudioEngine::setMuted(bool muted)
{
    if (!m_impl->muteFromEnv)
        m_impl->muted.store(muted, std::memory_order_relaxed);
}

bool PS2AudioEngine::muted() const
{
    return m_impl->muted.load(std::memory_order_relaxed);
}

uint32_t PS2AudioEngine::sdrCommand(uint32_t function, const uint32_t *args, uint32_t argCount)

{
    auto arg = [&](uint32_t i) -> uint32_t
    { return (args && i < argCount) ? args[i] : 0u; } ;

    switch (function)
    {

    case kSdrInit:
        m_spu2.init(arg(0));
        return 0u;
    case kSdrSetParam:
        m_spu2.setParam(arg(0), arg(1));
        return 0u;
    case kSdrGetParam:
        return m_spu2.getParam(arg(0));
    case kSdrSetSwitch:
        m_spu2.setSwitch(arg(0), arg(1));
        return 0u;
    case kSdrGetSwitch:
        return m_spu2.getSwitch(arg(0));
     case kSdrSetAddr:
        m_spu2.setAddr(arg(0), arg(1));
        return 0u;
    case kSdrGetAddr:
        return m_spu2.getAddr(arg(0));
     case kSdrSetCoreAttr:

        m_spu2.setCoreAttr(arg(0), arg(1));
        return 0u;
    case kSdrGetCoreAttr:

        return m_spu2.getCoreAttr(arg(0));
    case kSdrNote2Pitch:
        return note2Pitch(arg(0) & 0xFFFFu, arg(1) & 0xFFFFu, arg(2) & 0xFFFFu, static_cast<int16_t>(arg(3) & 0xFFFFu));
    case kSdrPitch2Note:

        return pitch2Note(arg(0) & 0xFFFFu, arg(1) & 0xFFFFu, arg(2) & 0xFFFFu);
    case kSdrProcBatch:
    case kSdrProcBatchEx:
    {
        const uint32_t batchAddr = arg(0);
        const uint32_t returnsAddr = arg(1);  
        const uint32_t count = std::min<uint32_t>(arg(2), 512u);
        if (!m_impl->resolver || count == 0u)
            return 0u;
        const uint8_t *src = m_impl->resolver(batchAddr, count * sizeof(ps2x::iop::Spu2Batch));
        if (!src)
            return 0u;
        std::vector<ps2x::iop::Spu2Batch> entries(count);
        std::memcpy(entries.data(), src, count * sizeof(ps2x::iop::Spu2Batch));
        std::vector<uint32_t> returns(count * kVoiceSlots, 0u);
        const uint32_t mask = function == kSdrProcBatchEx ? arg(3) : 0xFFFFFFu;
        const int32_t slots = m_spu2.procBatch(entries.data(), count, returns.data(), mask);
        if (returnsAddr != 0u && slots > 0)
        {
            uint8_t *dst = m_impl->resolver(returnsAddr, static_cast<uint32_t>(slots) * 4u);
            if (dst)
                std::memcpy(dst, returns.data(), static_cast<uint32_t>(slots) * 4u);
        }
        return static_cast<uint32_t>(slots);
    }
    case kSdrVoiceTrans:
        return m_spu2.voiceTrans(arg(0), arg(1), arg(2), arg(3), arg(4));
    case kSdrBlockTrans:
         return m_spu2.blockTrans(arg(0), arg(1), arg(2), arg(3), arg(4));
    case kSdrVoiceTransStatus:

        return m_spu2.voiceTransStatus(arg(0), arg(1));

     case kSdrBlockTransStatus:
        return m_spu2.blockTransStatus(arg(0), arg(1));
    case kSdrStopTrans:
        return m_spu2.blockTrans(arg(0), TRANS_STOP, 0u, 0u, 0u);
     default:
        return 0u;
     }
}

void PS2AudioEngine::onSoundCommand(uint32_t sid, uint32_t function, const uint8_t *sendBuf, uint32_t sendSize,
                                    uint8_t *recvBuf, uint32_t recvSize)
{
    if (sid != kSdrdrvSid)   
        return;

    uint32_t args[16] = {};
    uint32_t argCount = 0u;
    if(sendBuf)

    {
        argCount = std::min<uint32_t>(sendSize / 4u, 16u);
        std::memcpy(args, sendBuf, argCount * 4u);
    }

    uint32_t result = 0u;
    if ((function == kSdrProcBatch || function == kSdrProcBatchEx) && sendBuf && sendSize >= 8u)
     {
        // Over RPC the batch travels inline: count first, entries after.
        const uint32_t count = std::min<uint32_t>(args[0], (sendSize - 4u) / sizeof(ps2x::iop::Spu2Batch));
        std::vector<ps2x::iop::Spu2Batch> entries(count) ;
         std::memcpy(entries.data(), sendBuf + 4u, count * sizeof(ps2x::iop::Spu2Batch));
        std::vector<uint32_t> returns(count * kVoiceSlots, 0u); 
        const int32_t slots = m_spu2.procBatch(entries.data(), count, returns.data(), 0xFFFFFFu);

        if (recvBuf && slots > 0 && recvSize >= 4u + static_cast<uint32_t>(slots) * 4u)
            std::memcpy(recvBuf + 4u, returns.data(), static_cast<uint32_t>(slots) * 4u);
        result = static_cast<uint32_t>(std::max(slots, 0));
    }   
    else
    {
         result = sdrCommand(function, args, argCount); 
    }

    if (recvBuf && recvSize >= 4u)
         std::memcpy(recvBuf, &result, sizeof(result));
}
