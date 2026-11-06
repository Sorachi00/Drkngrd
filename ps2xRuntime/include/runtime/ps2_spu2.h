#ifndef PS2_SPU2_H
#define PS2_SPU2_H

#include "ps2x/iop/spu2_device.h"

#include <array>
#include <atomic>
#include <cstdint>
#include <memory>

#include <functional>
#include <mutex>
#include <vector>

class PS2Spu2 final : public ps2x::iop::Spu2Device
 {
public:
    static constexpr uint32_t kRamSize = ps2x::iop::sd::RAM_SIZE;
    static constexpr uint32_t kSampleRate =  ps2x::iop::sd::SAMPLE_RATE;
    static constexpr uint32_t kCoreCount = ps2x::iop::sd::CORE_COUNT;
    static constexpr uint32_t kVoiceCount = ps2x::iop::sd::VOICE_COUNT;

    struct Stats
    {
        uint32_t activeVoices = 0;
        uint32_t activeAdma = 0;
        uint32_t activeHostStreams = 0;
        uint64_t framesMixed = 0;
        uint64_t keyOns = 0;
        uint64_t voiceTransBytes = 0;
        uint64_t admaBytes = 0;
        int32_t peak = 0;
    };

    PS2Spu2();
    ~PS2Spu2() override;

    using GuestResolver = std::function<uint8_t *(uint32_t address, uint32_t size)>;
    void attachGuestMemory(GuestResolver resolver);
    void reset();
    void mix(int16_t *interleavedStereo, uint32_t frames, const int16_t *core0Input = nullptr);
    Stats stats() const;

    void init(uint32_t flags) override;
    void setParam(uint32_t entry, uint32_t value) override;
    uint32_t getParam(uint32_t entry) override;
    void setSwitch(uint32_t entry, uint32_t value) override;
    uint32_t getSwitch(uint32_t entry) override;
    void setAddr(uint32_t entry, uint32_t value) override;
    uint32_t getAddr(uint32_t entry) override;
    void setCoreAttr(uint32_t entry, uint32_t value) override;
    uint32_t getCoreAttr(uint32_t entry) override; 
     uint32_t voiceTrans(uint32_t core, uint32_t mode, uint32_t iopAddr, uint32_t spuAddr, uint32_t size) override;
    uint32_t blockTrans(uint32_t core, uint32_t mode, uint32_t iopAddr, uint32_t size, uint32_t startAddr) override;
    uint32_t voiceTransStatus(uint32_t core, uint32_t flag) override;
    uint32_t blockTransStatus(uint32_t core, uint32_t flag) override;
    int32_t procBatch(const ps2x::iop::Spu2Batch *batch, uint32_t count, uint32_t *returns, uint32_t voiceMask) override;
    void setEffectAttr(uint32_t core, uint32_t mode, uint32_t depthL, uint32_t depthR, uint32_t delay,

                       uint32_t feedback) override;
    void clearEffectWorkArea(uint32_t core, uint32_t mode) override;

    bool writeRam(uint32_t spuAddr, const void *data, uint32_t size) override;
    bool readRam(uint32_t spuAddr, void *out, uint32_t size) const override;

    void setPeriodicTick(std::function<void()> tick, uint32_t intervalFrames) override;
    uint32_t createHostStream(uint32_t sampleRate, std::shared_ptr<ps2x::iop::HostPcmSource> source) override;
    void destroyHostStream(uint32_t id) override;
    void setHostStreamVolume(uint32_t id, float left, float right) override;
    void setHostStreamPaused(uint32_t id, bool paused) override;   
    bool hostStreamActive(uint32_t id) const override;

private:
    enum class EnvPhase : uint8_t
    {
        Off,
        Attack,
        Decay,
        Sustain,
        Release
    };

    struct Sweep
    {
         uint16_t reg = 0;
        int32_t level = 0;
        uint32_t counter = 0;
    };

    struct Voice
    {  
        Sweep volL ;
        Sweep volR;
        uint16_t pitch = 0;
        uint16_t adsr1 = 0;
        uint16_t adsr2 = 0;
        uint32_t ssa = 0;
        uint32_t lsax = 0;
         uint32_t nax = 0;
        EnvPhase phase = EnvPhase::Off ;
        int32_t envLevel = 0;
        uint32_t envCounter = 0;
        uint32_t phaseCounter = 0;
        int32_t sampleIndex = 28;
        std::array<int16_t, 28> block{};
        int16_t history1 = 0;
        int16_t history2 = 0;
        int16_t prevSample = 0;
        int16_t curSample = 0;
        uint8_t blockFlags = 0;
        bool endx = false;
        bool blockLoaded = false;
        bool pendingKeyOn = false;
    };

    struct Adma
    {
        bool active = false;
        bool loop = false;
        bool finished = false;
        uint32_t iopBase = 0;
        uint32_t size = 0;
        uint32_t consumed = 0;
        uint32_t playPos = 0;
        uint32_t chunksFilled = 0 ;
        uint16_t mode = 0;
        std::vector<uint8_t> lastRing;
        uint32_t staleFills = 0;
        uint32_t freshFills = 0;  
    };

    enum ReverbReg : uint32_t
    {  
        APF1_SIZE, APF2_SIZE, IIR_VOL, COMB1_VOL, COMB2_VOL, COMB3_VOL, COMB4_VOL, WALL_VOL,
        APF1_VOL, APF2_VOL, SAME_L_DST, SAME_R_DST, COMB1_L_SRC, COMB1_R_SRC, COMB2_L_SRC, COMB2_R_SRC,
        SAME_L_SRC, SAME_R_SRC, DIFF_L_DST, DIFF_R_DST, COMB3_L_SRC, COMB3_R_SRC, COMB4_L_SRC, COMB4_R_SRC,
        DIFF_L_SRC, DIFF_R_SRC, APF1_L_DST, APF1_R_DST, APF2_L_DST, APF2_R_DST, IN_COEF_L, IN_COEF_R,
        REVERB_REG_COUNT
    };

    struct Reverb

    {
        std::array<int32_t, REVERB_REG_COUNT> reg{};
        uint32_t mode = 0;
        uint32_t cycles = 0;
        uint32_t bufPos = 0;
        std::array<std::array<int32_t, 128>, 2> down{};
        std::array<std::array<int32_t, 128>, 2> up{};
    };

    struct Core
    { 
        std::array<Voice, kVoiceCount> voices{};
        Reverb reverb ;
        uint32_t mmix = 0xFFFu;
        Sweep mvolL;
        Sweep mvolR ;
        uint16_t evolL = 0;
        uint16_t evolR = 0;
        uint16_t avolL = 0;
        uint16_t avolR = 0;
        uint16_t bvolL = 0;
        uint16_t bvolR = 0;
        uint32_t pmon = 0;
        uint32_t non = 0;
        uint32_t vmixl = 0xFFFFFFu;

        uint32_t vmixel = 0xFFFFFFu;
        uint32_t vmixr = 0xFFFFFFu;
        uint32_t vmixer = 0xFFFFFFu;
        uint32_t esa = 0;
        uint32_t eea = 0;
        uint32_t tsa = 0;
        uint32_t irqa = 0;
        std::array<uint32_t, 16> attrs{};
        Adma adma;
     };

    struct HostStream
    {
        uint32_t id = 0;
        uint32_t sampleRate = 48000;
        std::shared_ptr<ps2x::iop::HostPcmSource> source;
        float volL = 1.0f;  
         float volR = 1.0f;
        bool paused = false;
        bool finished = false;
        std::vector<int16_t> pending;   
        uint32_t pendingPos = 0;
        uint32_t phase = 0 ;

        int16_t lastL =  0;
        int16_t lastR = 0;
        int16_t nextL = 0;
        int16_t nextR = 0;
        bool primed = false;
    };

    void resetUnlocked();
     void traceVoices(uint32_t frames);
    void keyOn(Core &core, uint32_t voiceIndex);
    void keyOff(Voice &voice);
    bool decodeBlock(Voice &voice);
    void advanceEnvelope(Voice &voice);
    static void stepEnvelope(int32_t &level, uint32_t &counter, uint32_t rate, bool exponential, bool decrease);
    static int32_t sweepValue(Sweep &sweep);
    static void setSweep(Sweep &sweep, uint16_t reg);
     static int32_t plainVolume(uint16_t reg);
    int32_t voiceSample(Voice &voice);
    void admaStart(Core &core, uint32_t coreIndex, uint32_t mode, uint32_t iopAddr, uint32_t size, uint32_t startAddr);
    void admaFillHalf(Core &core, uint32_t coreIndex, uint32_t half);
    void admaStep(Core &core, uint32_t coreIndex, int32_t &left, int32_t &right);
    bool hostStreamSample(HostStream &stream, int32_t &left, int32_t &right);
    void doReverb(Core &core, int32_t inL, int32_t inR, int32_t &outL, int32_t &outR);
    void clearEffectAreaUnlocked(const Core &core, uint32_t mode);
    uint32_t meminBase(uint32_t coreIndex) const;
    uint8_t *guestRange(uint32_t iopAddr, uint32_t size) const;
    int32_t batchOne(const ps2x::iop::Spu2Batch &entry, uint32_t *ret);

     mutable std::mutex m_mutex;
    std::vector<uint8_t> m_ram;
    std::vector<uint64_t> m_ramWritten;
    std::array<Core, kCoreCount> m_cores{};
    std::vector<HostStream> m_hostStreams;
    uint32_t m_nextHostStreamId = 1;
    GuestResolver m_resolver;
    bool m_initialized = false;
    Stats m_stats;
    uint32_t m_noise = 1;
    uint32_t m_traceFrames = 0;
    double m_traceVoiceEnergy = 0.0;
    double m_traceAdmaEnergy = 0.0;

    double m_traceHostEnergy = 0.0;
    uint32_t m_traceVoiceFrames = 0;
    uint32_t m_traceZeroFrames = 0;
     uint32_t m_traceKeyOns = 0; 
    uint32_t m_traceKeyOffs = 0;

    uint32_t m_traceUnwrittenBlocks = 0;
    std::mutex m_tickMutex;
    std::function<void()> m_tick;
    uint32_t m_tickInterval = 0;
    uint32_t m_tickAccumulated = 0; 
};

#endif
