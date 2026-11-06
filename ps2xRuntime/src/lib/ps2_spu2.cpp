#include "runtime/ps2_spu2.h"

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>

namespace
{
    using namespace ps2x::iop::sd;  

    constexpr uint32_t kMeminWords = 0x2000u;
    constexpr uint32_t kMeminFrames = 512u;

    constexpr uint32_t kMeminHalfFrames = 256u;
    constexpr int32_t kEnvMax = 0x7FFF;

    inline int16_t clamp16(int32_t v)
    {
        return static_cast<int16_t>(std::clamp(v, -32768, 32767)); 

    }

    inline uint32_t paramIndex(uint32_t entry)
    {   
        return (entry >> 8) & 0xFFu;
    }

    inline uint32_t entryCore(uint32_t entry)
    {
        return entry & 1u;
    }

    inline uint32_t entryVoice(uint32_t entry)
    {
         return (entry >> 1) & 0x1Fu;
    }

    inline uint32_t wrapRam(uint32_t addr)
    {

        return addr & (RAM_SIZE - 1u);
    }

    constexpr std::array<int32_t, 5> kFilterPos{0, 60, 115, 98, 122} ;
    constexpr std::array<int32_t, 5> kFilterNeg{0, 0, -52, -55, -60};

    constexpr std::array<uint16_t, 10> kEffectSizes{0x1, 0x26C, 0x1F4, 0x484, 0x6FE, 0xADE, 0xF6C, 0x1804, 0x1804, 0x3C0};
    constexpr uint32_t kEffectParams[160] = {
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00010001, 0x00000000, 0x00000000,
        0x00000000, 0x00010001, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x005B007D, 0x54B86D80, 0x0000BED0, 0xBA800000, 0x53005800, 0x033304D6, 0x022703F0, 0x01EF0374,
        0x01B70336, 0x01B60335, 0x01B50334, 0x01B50334, 0x01B50334, 0x013601B4, 0x005C00B8, 0x80008000,
        0x00250033, 0x4FA870F0, 0x4410BCE0, 0x9C00C0F0, 0x4EC05280, 0x031B03E4, 0x02AF03A4, 0x02660372,
        0x025D031C, 0x018E025C, 0x0135022F, 0x00B701D2, 0x00B5018F, 0x008000B4, 0x0026004C, 0x80008000,

        0x007F00B1, 0x4FA870F0, 0x4510BCE0, 0xB4C0BEF0, 0x4EC05280, 0x076B0904, 0x065F0824, 0x061607A2,
        0x05ED076C, 0x042E05EC, 0x0305050F, 0x02B70462, 0x0265042F, 0x01B20264, 0x00800100, 0x80008000,
        0x00A900E3, 0x4FA86F60, 0x4510BCE0, 0xA680BEF0, 0x52C05680, 0x0B580DFB, 0x0A3C0D09, 0x09730BD9,
        0x08DA0B59, 0x05E908D9, 0x04B007EC, 0x03D206EF, 0x031D05EA, 0x0238031C, 0x00AA0154, 0x80008000,
        0x013901A5, 0x50006000, 0xB8004C00, 0xC000BC00, 0x5C006000, 0x11BB15BA, 0x10BD14C2, 0x0DC111BC,
        0x0DC311C0, 0x09C10DC0, 0x07C10BC4, 0x06CD0A00, 0x05C109C2, 0x041A05C0, 0x013A0274, 0x80008000,
        0x0231033D, 0x50007E00, 0xB000B400, 0xB0004C00, 0x54006000, 0x1A311ED6, 0x183B1D14, 0x16B21BC2,
        0x15EF1A32, 0x105515EE, 0x0F2D1334, 0x0C5D11F6, 0x0AE11056, 0x07A20AE0, 0x02320464, 0x80008000,
         0x00030003, 0x7FFF7FFF, 0x00000000, 0x81000000, 0x00000000, 0x0FFD1FFD, 0x00091009, 0x00000000,
        0x00091009, 0x1FFF1FFF, 0x1FFE1FFE, 0x1FFE1FFE, 0x1FFE1FFE, 0x10041008, 0x00040008, 0x80008000,
        0x00030003, 0x7FFF7FFF, 0x00000000, 0x00000000, 0x00000000, 0x0FFD1FFD, 0x00091009, 0x00000000,
        0x00091009, 0x1FFF1FFF, 0x1FFE1FFE, 0x1FFE1FFE, 0x1FFE1FFE, 0x10041008, 0x00040008, 0x80008000,
        0x00130017, 0x4FA870F0, 0x4510BCE0, 0x8500BEF0, 0x54C05F80, 0x02AF0371, 0x01DF02E5, 0x01D702B0,
        0x026A0358, 0x011E01D6, 0x00B1012D, 0x0059011F, 0x00E301A0, 0x00400058, 0x00140028, 0x80008000,
    };

    constexpr uint32_t kReverbTaps = 39u;
    constexpr std::array<int32_t, kReverbTaps> kReverbFilter{
        -1, 0, 2, 0, -10, 0, 35, 0, -103, 0, 266, 0, -616, 0, 1332, 0, -2960, 0, 10246, 16384,
        10246, 0, -2960, 0, 1332, 0, -616, 0, 266, 0, -103, 0, 35, 0, -10, 0, 2, 0, -1};

    // Byte address of the end of a core's effect area, as libsd's GetEEA.
    inline uint32_t effectEndBytes(uint32_t eea)
    {
        return ((eea >> 17) << 17) | 0x1FFFFu;
    }
}

PS2Spu2::PS2Spu2()
     : m_ram(kRamSize, 0u)
{
    resetUnlocked();
}

PS2Spu2::~PS2Spu2() = default;

void PS2Spu2::attachGuestMemory(GuestResolver resolver)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    m_resolver = std::move(resolver);
}


void PS2Spu2::reset()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    resetUnlocked();
}

void PS2Spu2::resetUnlocked()
{

    std::fill(m_ram.begin(), m_ram.end(), 0u);
    m_ramWritten.assign((kRamSize / 16u + 63u) / 64u, 0u);
    for (Core &core : m_cores)
    {
        core = Core{};
        setSweep(core.mvolL, 0x3FFFu);
        setSweep(core.mvolR, 0x3FFFu);
        core.bvolL = 0x7FFFu;
        core.bvolR = 0x7FFFu;
        core.avolL = 0x7FFFu;
        core.avolR = 0x7FFFu;
    }
    m_hostStreams.clear();
    m_initialized = false;
    m_stats = Stats{};
}

PS2Spu2::Stats PS2Spu2::stats() const
 {
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_stats;
}


uint32_t PS2Spu2::meminBase(uint32_t coreIndex) const
{
    return (kMeminWords + coreIndex * 0x400u) * 2u;
}

uint8_t *PS2Spu2::guestRange(uint32_t iopAddr, uint32_t size) const
{
    if (!m_resolver || size == 0u)
        return nullptr;
    return m_resolver(iopAddr, size);
}

namespace
{
    bool openMixOnInit()
    {
        static const bool value = []
        {
            const char *env = std::getenv("PS2X_SPU2_INIT_OPEN_MIX");
            return env == nullptr || env[0] != '0';
        }();
        return value;
    }
}

void PS2Spu2::init(uint32_t flags)
{
    const bool warm = (flags & 1u) != 0u;
    std::lock_guard<std::mutex> lock(m_mutex);   
     for (uint32_t c = 0; c < kCoreCount; ++c)
    {
        Core &core = m_cores[c];
        for (Voice &voice : core.voices)
        {

            voice = Voice{};
        }
        core.adma = Adma{};
        core.reverb = Reverb{};
        core.mmix = c == 0u ? 0xFF0u : 0xFFCu;
        core.vmixl = core.vmixr = core.vmixel = core.vmixer = openMixOnInit() ? 0xFFFFFFu : 0u;
        core.avolL = core.avolR = c == 0u ? 0u : 0x7FFFu ;  
        core.bvolL = core.bvolR = 0u;
        core.attrs[CORE_ATTR_EFFECT_ENABLE >> 1] =  warm ? 1u : 0u;
        if (!warm)
        {
            setSweep(core.mvolL, 0u);
            setSweep(core.mvolR, 0u);
            core.evolL = core.evolR = 0u;
            core.eea = c == 0u ? 0x1DFFFFu : 0x1FFFFFu;
        }
     }
    m_initialized = true;
}

int32_t PS2Spu2::plainVolume(uint16_t reg)
{
    return static_cast<int32_t>(static_cast<int16_t>(reg << 1));
}

void PS2Spu2::setSweep(Sweep &sweep, uint16_t reg)
{
    sweep.reg = reg;
    if ((reg & 0x8000u) == 0u)
    {
        sweep.level = plainVolume(reg);
        sweep.counter = 0u ;
    }
}

int32_t PS2Spu2::sweepValue(Sweep &sweep)
{
    if ((sweep.reg & 0x8000u) == 0u)
        return sweep.level;   

    const bool exponential = (sweep.reg & 0x4000u) != 0u;
    const bool decrease = (sweep.reg & 0x2000u) != 0u;
    const bool negative = (sweep.reg & 0x1000u) != 0u;
    int32_t magnitude =  std::abs(sweep.level);
    stepEnvelope(magnitude, sweep.counter, sweep.reg & 0x7Fu, exponential, decrease);
    sweep.level = negative ? -magnitude : magnitude;  
    return sweep.level;
}

void PS2Spu2::stepEnvelope(int32_t &level, uint32_t &counter, uint32_t rate, bool exponential, bool decrease)
{
    if (rate >= 0x7Fu)
        return; 
    uint32_t shift = rate >> 2;
    int32_t step = decrease ? static_cast<int32_t>(rate & 3u) - 8 : 7 - static_cast<int32_t>(rate & 3u);
    uint32_t cycles = 1u;

    if (shift > 11u)
        cycles = 1u << (shift - 11u);

    else
         step <<= (11u - shift);
    if (exponential && !decrease && level > 0x6000)
        cycles *= 4u;
    if (exponential && decrease)
        step = (step * level) >> 15;

    if(++counter < cycles)
        return;

    counter = 0u;

    level = std::clamp(level + step, 0, kEnvMax);
}

void PS2Spu2::advanceEnvelope(Voice &voice)
{   
    switch (voice.phase)

    {
    case EnvPhase::Attack:
    {
        const uint32_t rate = (voice.adsr1 >> 8) & 0x7Fu;
        const bool exponential = (voice.adsr1 & 0x8000u) != 0u;
        stepEnvelope(voice.envLevel, voice.envCounter, rate, exponential, false);
        if (voice.envLevel >= kEnvMax)
        {
            voice.envLevel = kEnvMax;   
            voice.phase = EnvPhase::Decay;
            voice.envCounter = 0u;
        }
        break;
    }
    case EnvPhase::Decay:
    {
        const uint32_t rate = ((voice.adsr1 >> 4) & 0xFu) << 2;
        const int32_t sustainLevel = std::min<int32_t>(kEnvMax, ((voice.adsr1 & 0xFu) + 1) << 11);
        if (voice.envLevel <= sustainLevel)
        {
            voice.phase = EnvPhase::Sustain;
            voice.envCounter = 0u;
            break;
        }
        stepEnvelope(voice.envLevel, voice.envCounter, rate, true, true);
        break;
    }
    case EnvPhase::Sustain:
    {
        const uint32_t rate = (voice.adsr2 >> 6) & 0x7Fu;
        const bool exponential = (voice.adsr2 & 0x8000u) != 0u;
        const bool decrease = (voice.adsr2 & 0x4000u) != 0u;
        stepEnvelope(voice.envLevel, voice.envCounter, rate, exponential, decrease);
        if (decrease && voice.envLevel <= 0)
        {
            voice.envLevel = 0;
            voice.phase = EnvPhase::Off;
        }
        break;
    }
    case EnvPhase::Release:
    {
        const uint32_t rate = (voice.adsr2 & 0x1Fu) << 2;
        const bool exponential = (voice.adsr2 & 0x0020u) != 0u;
        stepEnvelope(voice.envLevel, voice.envCounter, rate, exponential, true);
        if (voice.envLevel <= 0 || (exponential && voice.envLevel < 4))
        {   
            voice.envLevel = 0; 
            voice.phase = EnvPhase::Off;
        }
        break;
    }
    case EnvPhase::Off:
    default:
        break;
    }
}

bool PS2Spu2::decodeBlock(Voice &voice)
{
    const uint32_t addr = wrapRam(voice.nax & ~0xFu);
    const uint32_t written = addr / 16u;
    if ((m_ramWritten[written >> 6] & (1ull << (written & 63u))) == 0u)
        ++m_traceUnwrittenBlocks;
    const uint8_t *block = m_ram.data() + addr;

    const uint32_t shift = std::min<uint32_t>(block[0] & 0x0Fu, 12u);
    const uint32_t filter = std::min<uint32_t>((block[0] >> 4) & 0x07u, 4u);
    voice.blockFlags = block[1];
    if ((voice.blockFlags & 0x04u) != 0u)
        voice.lsax = addr;


    int32_t h1 = voice.history1 ;
    int32_t h2 = voice.history2;
    for (uint32_t i = 0; i < 28u; ++i)
    {

        const uint8_t byte = block[2u + (i >> 1)];
        const uint32_t nibble = (i & 1u) ? (byte >> 4) : (byte & 0x0Fu);
        int32_t sample = static_cast<int32_t>(static_cast<int16_t>(nibble << 12)) >> shift;
        sample += (h1 * kFilterPos[filter] + h2 * kFilterNeg[filter] + 32) >> 6;
        const int16_t out = clamp16(sample);
        h2 =  h1;
        h1 = out;
        voice.block[i] = out;
    }
    voice.history1 = static_cast<int16_t>(h1);
    voice.history2 = static_cast<int16_t>(h2);
    voice.sampleIndex = 0;
    return true;
}

void PS2Spu2::keyOn(Core &core, uint32_t voiceIndex)
{
    Voice &voice = core.voices[voiceIndex];
    voice.nax = voice.ssa & ~0xFu;

    voice.lsax = voice.nax;
    voice.phase = EnvPhase::Attack;
    voice.envLevel = 0;
    voice.envCounter = 0u;
    voice.phaseCounter = 0u;
    voice.sampleIndex = 28;
    voice.history1 = 0;
    voice.history2 = 0;
    voice.prevSample = 0;
    voice.curSample = 0;
    voice.endx = false;
    voice.blockLoaded = false;
    voice.blockFlags =  0u;
    voice.pendingKeyOn = false;
    ++m_stats.keyOns;
    ++m_traceKeyOns;
    static const bool trace = std::getenv("PS2X_TRACE_KEYON") != nullptr;
    if (trace)
        std::fprintf(stderr, "[spu2] kon t=%.2f v%02u ssa=%06x pitch=%04x adsr=%04x/%04x vol=%04x/%04x\n",
                     static_cast<double>(m_stats.framesMixed) / kSampleRate, voiceIndex,
                     voice.ssa, voice.pitch, voice.adsr1, voice.adsr2, voice.volL.reg, voice.volR.reg);
}

void PS2Spu2::keyOff(Voice &voice)  
{
    if (voice.phase != EnvPhase::Off)
    {
        voice.phase = EnvPhase::Release;
        voice.envCounter = 0u;
        ++m_traceKeyOffs;
    }  
}

int32_t PS2Spu2::voiceSample(Voice &voice)
{
    if (voice.phase == EnvPhase::Off)
        return 0;

    voice.phaseCounter += std::min<uint32_t>(voice.pitch, 0x3FFFu);
    while (voice.phaseCounter >= 0x1000u)
    {
        voice.phaseCounter -= 0x1000u;
        if (voice.sampleIndex >= 28)
         {
            if (voice.blockLoaded && (voice.blockFlags & 0x01u) != 0u)
            {
                voice.endx = true;
                voice.nax = voice.lsax & ~0xFu;
                if ((voice.blockFlags & 0x02u) == 0u)
                {
                    voice.phase = EnvPhase::Off;

                    voice.envLevel = 0;
                    return 0;
                }
            }

            decodeBlock(voice);
            voice.blockLoaded = true;
            voice.nax = wrapRam((voice.nax & ~0xFu) + 16u);
        }
        voice.prevSample = voice.curSample;
        voice.curSample = voice.block[voice.sampleIndex++];
    }

    advanceEnvelope(voice);
    const int32_t frac = static_cast<int32_t>(voice.phaseCounter & 0xFFFu);
    const int32_t interpolated = voice.prevSample + (((voice.curSample - voice.prevSample) * frac) >> 12);
    return (interpolated * voice.envLevel) >> 15;
}

 void PS2Spu2::admaStart(Core &core, uint32_t coreIndex, uint32_t mode, uint32_t iopAddr, uint32_t size, uint32_t startAddr)
{
    Adma &adma = core.adma;
    adma.active = true;
    adma.finished = false;
     adma.loop = (mode & TRANS_LOOP) != 0u;
    adma.mode = static_cast<uint16_t>(mode);
    adma.iopBase = iopAddr;   
    adma.size = size & ~(ADMA_BLOCK_BYTES - 1u);
    if (adma.size == 0u)
    {
        adma.active = false;
        return;
    }
    uint32_t startOffset = 0u;
    if ((mode & TRANS_DIRECTION_MASK) == TRANS_WRITE_FROM && startAddr >= iopAddr && startAddr < iopAddr + adma.size)
        startOffset = (startAddr - iopAddr) & ~(ADMA_BLOCK_BYTES - 1u);
    adma.consumed = startOffset;
    adma.chunksFilled = 0u;
    adma.lastRing.assign(adma.size, 0u);
    adma.staleFills = 0u;

    adma.freshFills = 0u;

    adma.playPos = 0u;
    admaFillHalf(core, coreIndex, 0u);
    admaFillHalf(core, coreIndex, 1u);
}

 void PS2Spu2::admaFillHalf(Core &core, uint32_t coreIndex, uint32_t half)
{
    Adma &adma = core.adma;
    const uint32_t base = meminBase(coreIndex);
    uint8_t *left = m_ram.data() + base + half * kMeminHalfFrames * 2u;
    uint8_t *right = left + kMeminFrames * 2u;

    if (!adma.active || adma.finished || adma.consumed >= adma.size)
    {
        if (adma.active && !adma.loop)
            adma.finished = true;  
        std::memset(left, 0, kMeminHalfFrames * 2u);
         std::memset(right, 0, kMeminHalfFrames * 2u);

        return ; 
     }

    const uint8_t *chunk = guestRange(adma.iopBase + adma.consumed, ADMA_BLOCK_BYTES);

    static const bool holdOnStale = []
    {
        const char *env = std::getenv("PS2X_SPU2_ADMA_HOLD");
         return env == nullptr || env[0] != '0';
    }();
    bool stale = false;  
    if (chunk && holdOnStale)
    {
        if (adma.lastRing.size() != adma.size)
            adma.lastRing.assign(adma.size, 0u);
        uint8_t *seen = adma.lastRing.data() + adma.consumed ;
        stale = std::memcmp(seen, chunk, ADMA_BLOCK_BYTES) == 0;
        if (stale)
        {
            ++adma.staleFills ;
        }
        else

        {
            std::memcpy(seen, chunk, ADMA_BLOCK_BYTES);
            ++adma.freshFills;
        }
    }
    if (stale)
    {
        std::memset(left, 0, kMeminHalfFrames * 2u);
        std::memset(right, 0, kMeminHalfFrames * 2u);
        chunk =  nullptr;   
     }
    if (chunk)
    {
        static std::FILE *admaDump =  []() -> std::FILE *
        {
             const char *path = std::getenv("PS2X_DUMP_ADMA");
            return (path && path[0] != '\0') ? std::fopen(path, "wb") : nullptr;
        }();
        if (admaDump)
        {
             std::fwrite(chunk, 1, ADMA_BLOCK_BYTES, admaDump);
            std::fflush(admaDump);
        }
        std::memcpy(left, chunk, kMeminHalfFrames * 2u);
         std::memcpy(right, chunk + kMeminHalfFrames * 2u, kMeminHalfFrames * 2u) ;
        m_stats.admaBytes += ADMA_BLOCK_BYTES;
        static const bool trace = std::getenv("PS2X_TRACE_SPU2") != nullptr;
        static uint32_t traced = 0u;
        if (trace && traced < 64u && (adma.chunksFilled % 64u) == 0u)  
        {
            ++traced;
            int64_t acc = 0;

            int32_t peak = 0;
            for (uint32_t i =  0; i < kMeminHalfFrames; ++i)
            {
                int16_t v = 0;
                 std::memcpy(&v, chunk + i * 2u, 2);
                acc += static_cast<int64_t>(v) * v ;
                peak = std::max<int32_t>(peak, std::abs(static_cast<int32_t>(v)));
            }
            std::fprintf(stderr, "[spu2] adma core%u chunk %u iop=0x%x rms=%.0f peak=%d head=%02x%02x%02x%02x%02x%02x%02x%02x\n",
                         coreIndex, adma.chunksFilled, adma.iopBase + adma.consumed,
                         std::sqrt(static_cast<double>(acc) / kMeminHalfFrames), peak,
                         chunk[0], chunk[1], chunk[2], chunk[3], chunk[4], chunk[5], chunk[6], chunk[7]);
        }
    }
    else 
    {
        std::memset(left, 0, kMeminHalfFrames * 2u);
        std::memset(right, 0, kMeminHalfFrames * 2u);
    }  

    adma.consumed += ADMA_BLOCK_BYTES;
    ++adma.chunksFilled;
    if (adma.consumed >= adma.size)
    {
        if (adma.loop)
            adma.consumed = 0u;
        else
            adma.finished = true;
    }
}

void PS2Spu2::admaStep(Core &core, uint32_t coreIndex, int32_t &left, int32_t &right) 
{
    Adma &adma = core.adma;
    if (!adma.active)
        return;

    const uint32_t base = meminBase(coreIndex);
    const int16_t *leftRing = reinterpret_cast<const int16_t *>(m_ram.data() + base);
    const int16_t *rightRing = leftRing + kMeminFrames;
    left = leftRing[adma.playPos];
    right = rightRing[adma.playPos];

    adma.playPos = (adma.playPos + 1u) % kMeminFrames; 
    if (adma.playPos == 0u)
    {
        admaFillHalf(core, coreIndex, 1u);
    }

    else if (adma.playPos == kMeminHalfFrames)
    {
        admaFillHalf(core, coreIndex, 0u);
    }
    if (adma.finished && adma.chunksFilled == 0u)
        adma.active = false;  
}

bool PS2Spu2::hostStreamSample(HostStream &stream, int32_t &left, int32_t &right)
{
    if (stream.paused || !stream.source)
        return false;

    const uint32_t step = (stream.sampleRate << 12) / kSampleRate;
    auto fetch = [&](int16_t &l, int16_t &r) -> bool
    {
        if (stream.pendingPos + 2u > stream.pending.size())
        {
             if (stream.finished)
                return false;

            constexpr uint32_t kPullFrames = 2048u;
            stream.pending.resize(kPullFrames * 2u);
            const uint32_t got = stream.source->pull(stream.pending.data(), kPullFrames);

            stream.pending.resize(static_cast<size_t>(got) * 2u);
            stream.pendingPos = 0u;
            if (got == 0u)
            {
                if (stream.source->finished())
                    stream.finished = true;
                return false;
            }
        }
        l = stream.pending[stream.pendingPos];
        r = stream.pending[stream.pendingPos + 1u];  
        stream.pendingPos += 2u;
        return true;
    };

    if (!stream.primed)
    { 
        if(!fetch(stream.lastL, stream.lastR))
            return false;
        if (!fetch(stream.nextL, stream.nextR))
        {
            stream.nextL = stream.lastL;
            stream.nextR = stream.lastR;
        }
        stream.primed = true;
        stream.phase = 0u;
    }

    stream.phase += step;
     while (stream.phase >= 0x1000u)
    {
        stream.phase -= 0x1000u;
        stream.lastL = stream.nextL;
        stream.lastR = stream.nextR;
        if (!fetch(stream.nextL, stream.nextR))
        {
            stream.primed = false;
            return false;
        }
    }
    const int32_t frac = static_cast<int32_t>(stream.phase & 0xFFFu);
    const int32_t l = stream.lastL + (((stream.nextL - stream.lastL) * frac) >> 12);
    const int32_t r = stream.lastR + (((stream.nextR - stream.lastR) * frac) >> 12);
    left = static_cast<int32_t>(l * stream.volL) ; 
    right = static_cast<int32_t>(r * stream.volR) ;
    return true;
}

void PS2Spu2::doReverb(Core &core, int32_t inL, int32_t inR, int32_t &outL, int32_t &outR)   
{
    Reverb &rv = core.reverb;

    const bool right = (rv.cycles & 1u) != 0u ;
    const uint32_t cycles = rv.cycles++;
    outL = outR = 0;
    const uint32_t start = core.esa >> 1;
    const uint32_t end =  (effectEndBytes(core.eea) >> 1) | 0xFFFFu;
    if (start >= end)
        return;

    const uint32_t pos = rv.bufPos ;
     rv.down[0][pos] =  rv.down[0][pos | 64u] = clamp16(inL);
    rv.down[1][pos] = rv.down[1][pos | 64u] = clamp16(inR);

    const uint32_t length = end - start + 1u;
    auto at = [&](int32_t offset) -> int16_t &
    {
        const uint32_t word = ((((cycles >> 1) + static_cast<uint32_t>(offset)) % length) + start) & 0xFFFFFu;
        return *reinterpret_cast<int16_t *>(m_ram.data() + ((word * 2u) & (kRamSize - 1u)));
    };
    auto mul = [](int32_t a, int32_t b) { return (a * b) >> 15; };
    const auto &r = rv.reg;

    int32_t in = 0;
    {
        const std::array<int32_t, 128> &buf = rv.down[right ? 1 : 0];
        const uint32_t index = (pos - kReverbTaps) & 63u;
        for (uint32_t i = 0; i < kReverbTaps; ++i)
            in += buf[index + i] * kReverbFilter[i];
        in = clamp16(in >> 15);
    }
    in = mul(r[right ? IN_COEF_R : IN_COEF_L], in);

     int16_t &sameSrc = at(r[right ? SAME_R_SRC : SAME_L_SRC]);
    int16_t &sameDst = at(r[right ? SAME_R_DST : SAME_L_DST]);
    int16_t &samePrv = at(r[right ? SAME_R_DST : SAME_L_DST] - 1);
    int16_t &diffSrc =  at(r[right ? DIFF_L_SRC : DIFF_R_SRC]);
    int16_t &diffDst = at(r[right ? DIFF_R_DST : DIFF_L_DST]);

    int16_t &diffPrv = at(r[right ? DIFF_R_DST : DIFF_L_DST] - 1);
    const int32_t comb1 = at(r[right ? COMB1_R_SRC : COMB1_L_SRC]);
    const int32_t comb2 = at(r[right ? COMB2_R_SRC : COMB2_L_SRC]);
    const int32_t comb3 = at(r[right ? COMB3_R_SRC : COMB3_L_SRC]);
    const int32_t comb4 = at(r[right ? COMB4_R_SRC : COMB4_L_SRC]);
    int16_t &apf1Src = at(r[right ? APF1_R_DST : APF1_L_DST] - r[APF1_SIZE]);

    int16_t &apf1Dst = at(r[right ? APF1_R_DST : APF1_L_DST]); 
    int16_t &apf2Src = at(r[right ? APF2_R_DST : APF2_L_DST] - r[APF2_SIZE]);
    int16_t &apf2Dst = at(r[right ? APF2_R_DST : APF2_L_DST]);

     const int32_t same = mul(r[IIR_VOL], in + mul(r[WALL_VOL], sameSrc) - samePrv) + samePrv;
    const int32_t diff = mul(r[IIR_VOL], in + mul(r[WALL_VOL], diffSrc) - diffPrv) + diffPrv;
    int32_t out = mul(r[COMB1_VOL], comb1) + mul(r[COMB2_VOL], comb2) + mul(r[COMB3_VOL], comb3) +
                  mul(r[COMB4_VOL], comb4);
    const int32_t apf1 = out - mul(r[APF1_VOL], apf1Src);

    out = apf1Src + mul(r[APF1_VOL], apf1);
    const int32_t apf2 = out - mul(r[APF2_VOL], apf2Src);
    out = apf2Src + mul(r[APF2_VOL], apf2);

    if (core.attrs[CORE_ATTR_EFFECT_ENABLE >> 1] != 0u)
    {
        sameDst = clamp16(same);
        diffDst = clamp16(diff);
        apf1Dst = clamp16(apf1);
        apf2Dst = clamp16(apf2);
    }

    out = clamp16(out);
    rv.up[right ? 1 : 0][pos] = rv.up[right ? 1 : 0][pos | 64u] = out;
    rv.up[right ? 0 : 1][pos] =  rv.up[right ? 0 : 1][pos | 64u] = 0;
    rv.bufPos = (pos + 1u) & 63u;

    const uint32_t index = (rv.bufPos - kReverbTaps) & 63u;
    int32_t l = 0;
    int32_t rr = 0;
    for (uint32_t i = 0; i < kReverbTaps; ++i)
    {
        const int32_t coef = std::clamp(kReverbFilter[i] * 2, -32768, 32767);
        l += rv.up[0][index + i] * coef;  
        rr += rv.up[1][index + i] * coef;
    }
    outL = clamp16(l >> 15);
    outR = clamp16(rr >> 15);
}

void PS2Spu2::clearEffectAreaUnlocked(const Core &core, uint32_t mode)
{
    if (mode == 0u || mode > 9u)
        return;
    const uint32_t size = static_cast<uint32_t>(kEffectSizes[mode]) << 4;
    const uint32_t start = effectEndBytes(core.eea) - (size - 2u);
     for (uint32_t i = 0; i < size; ++i)
        m_ram[(start + i) & (kRamSize - 1u)] = 0u;
}

void PS2Spu2::setEffectAttr(uint32_t coreIndex, uint32_t mode, uint32_t depthL, uint32_t depthR, uint32_t delay,
                            uint32_t feedback)
{

    std::lock_guard<std::mutex> lock(m_mutex);
    Core &core = m_cores[coreIndex & 1u];
    const bool clearRam = (mode & 0x100u) != 0u;
    mode &= ~0x100u;
    if (mode > 9u)
        return;
    const uint32_t lastMode = core.reverb.mode;

    std::array<uint16_t, REVERB_REG_COUNT> data{};
    std::memcpy(data.data(), &kEffectParams[mode * 16u], sizeof(uint16_t) * REVERB_REG_COUNT);
    if (mode == 7u || mode == 8u)
    {

        const uint16_t d = static_cast<uint16_t>((delay + 1u) << 5);
        data[WALL_VOL] = static_cast<uint16_t>(((feedback << 7) + feedback) << 1);
        data[SAME_L_DST] =  static_cast<uint16_t>((d << 1) - data[APF1_SIZE]);
        data[SAME_R_DST] = static_cast<uint16_t>(d - data[APF2_SIZE]);
        data[SAME_L_SRC] = static_cast<uint16_t>(data[SAME_R_SRC] + d);
        data[COMB1_L_SRC] = static_cast<uint16_t>(data[COMB1_R_SRC] + d);
        data[APF1_R_DST] = static_cast<uint16_t>(data[APF2_R_DST] + d);

        data[APF1_L_DST] = static_cast<uint16_t>(data[APF2_L_DST] + d);
     }


    if (clearRam && core.attrs[CORE_ATTR_EFFECT_ENABLE >> 1] != 0u)
        clearEffectAreaUnlocked(core, lastMode) ;
    core.evolL = static_cast<uint16_t>(depthL);
    core.evolR = static_cast<uint16_t>(depthR);
    for (uint32_t i = 0; i < REVERB_REG_COUNT; ++i)
    {
        const bool volume = (i >= IIR_VOL && i <= APF2_VOL) || i == IN_COEF_L || i == IN_COEF_R;
        core.reverb.reg[i] = volume ? static_cast<int16_t>(data[i]) : static_cast<int32_t>(data[i]) * 4;
    }
    core.esa = effectEndBytes(core.eea) - ((static_cast<uint32_t>(kEffectSizes[mode]) << 4) - 2u);
    core.reverb.mode = mode;
    if (clearRam)
        clearEffectAreaUnlocked(core, mode);
}

void PS2Spu2::clearEffectWorkArea(uint32_t coreIndex, uint32_t mode)
{
    std::lock_guard<std::mutex> lock(m_mutex);
     clearEffectAreaUnlocked(m_cores[coreIndex & 1u], mode);
}

void PS2Spu2::mix(int16_t *out, uint32_t frames, const int16_t *core0Input)
{
    {  
        std::lock_guard<std::mutex> tickLock(m_tickMutex);
        if (m_tick && m_tickInterval != 0u)
        {
            m_tickAccumulated += frames;
            uint32_t runs = m_tickAccumulated / m_tickInterval;
            m_tickAccumulated -= runs * m_tickInterval;
            runs = std::min(runs, 8u);
            for (uint32_t i = 0; i < runs; ++i)
                m_tick();   
        }

    }

    std::lock_guard<std::mutex> lock(m_mutex);

    for (Core &core : m_cores)  
    {
        for (uint32_t v = 0; v < kVoiceCount; ++v)

        {
            if (core.voices[v].pendingKeyOn)
                keyOn(core, v);
        }   
    }

     uint32_t activeVoices = 0u;
    int32_t peak = 0; 
    for (uint32_t f = 0; f < frames; ++f)
     {
        auto plain = [](int32_t x, uint16_t vol) { return (x * static_cast<int32_t>(static_cast<int16_t>(vol))) >> 15; };
        auto gate = [](int32_t x, uint32_t mmix, uint32_t bit) { return (mmix & bit) != 0u ? x : 0; };

        int32_t extL = 0; 
        int32_t extR = 0;
        int32_t outL =  0;
        int32_t outR = 0;
        for (uint32_t c = 0; c < kCoreCount; ++c)
        {

            Core &core = m_cores[c];
            int32_t dryL = 0;   
            int32_t dryR = 0;
            int32_t wetL = 0;

            int32_t wetR = 0;
            for (uint32_t v = 0; v < kVoiceCount; ++v)
            {
                Voice &voice = core.voices[v];
                if (voice.phase == EnvPhase::Off)
                    continue;
                if (f == 0u)
                    ++activeVoices;
                const int32_t sample = voiceSample(voice) ;
                const int32_t l = (sample * sweepValue(voice.volL)) >> 15;
                const int32_t r = (sample * sweepValue(voice.volR)) >> 15;

                const uint32_t bit = 1u << v;
                dryL += (core.vmixl & bit) ? l : 0;
                dryR += (core.vmixr & bit) ? r : 0;
                wetL += (core.vmixel & bit) ? l : 0 ;
                wetR += (core.vmixer & bit) ? r : 0;
            }
            dryL = clamp16(dryL);
            dryR = clamp16(dryR);

            wetL = clamp16(wetL);
            wetR = clamp16(wetR);

            int32_t inL = 0;
            int32_t inR = 0;
            admaStep(core, c, inL, inR);
            if (c == 0u && core0Input)
            {
                inL = core0Input[f * 2u];
                inR = core0Input[f * 2u + 1u];

            }
            inL = plain(inL, core.bvolL);
            inR = plain(inR, core.bvolR);

            const uint32_t m = core.mmix;
            const int32_t tdL = gate(inL, m, MMIX_MINL) + gate(dryL, m, MMIX_MSNDL) + gate(extL, m, MMIX_SINL);
            const int32_t tdR = gate(inR, m, MMIX_MINR) + gate(dryR, m, MMIX_MSNDR) + gate(extR, m, MMIX_SINR);
            const int32_t twL = gate(inL, m, MMIX_MINEL) + gate(wetL, m, MMIX_MSNDEL) + gate(extL, m, MMIX_SINEL);
            const int32_t twR = gate(inR, m, MMIX_MINER) + gate(wetR, m, MMIX_MSNDER) + gate(extR, m, MMIX_SINER);
            int32_t rvL = 0 ;
            int32_t rvR = 0 ;
            doReverb(core, twL, twR, rvL, rvR);
            const int32_t coreL = clamp16(tdL + plain(rvL, core.evolL));
            const int32_t coreR =  clamp16(tdR + plain(rvR, core.evolR));

            const int32_t mvolL = sweepValue(core.mvolL);
            const int32_t mvolR = sweepValue(core.mvolR);
            const int32_t voiceL = (dryL * mvolL) >> 15;
            const int32_t admaL = (inL * mvolL) >> 15;
            m_traceVoiceEnergy += static_cast<double>(voiceL) * voiceL;
            m_traceAdmaEnergy += static_cast<double>(admaL) * admaL;
            if (voiceL != 0)
                ++m_traceVoiceFrames;
            if (c == 0u)
            {
                extL = plain((coreL * mvolL) >> 15, m_cores[1].avolL);
                extR = plain((coreR * mvolR) >> 15, m_cores[1].avolR);
            }
            else
            {
                outL = (coreL * mvolL) >> 15;
                outR = (coreR * mvolR) >> 15;
            }
        }

        for (HostStream &stream : m_hostStreams)
        {
            int32_t l = 0;
            int32_t r = 0;

            if (hostStreamSample(stream, l, r))
            {
                 outL += l;  
                outR += r;
                m_traceHostEnergy += static_cast<double>(l) * l;
            }
        } 

        if (outL == 0)

            ++m_traceZeroFrames;
        peak = std::max({peak, std::abs(outL), std::abs(outR)});
        out[f * 2u] = clamp16(outL);
        out[f * 2u + 1u] = clamp16(outR);
    }

    m_hostStreams.erase(std::remove_if(m_hostStreams.begin(), m_hostStreams.end(),
                                       [](const HostStream &s)
                                       { return s.finished; }),

                        m_hostStreams.end());

    traceVoices(frames);
    m_stats.activeVoices = activeVoices;
    m_stats.activeAdma = 0u;
    for (const Core &core : m_cores)
        m_stats.activeAdma += core.adma.active ? 1u : 0u;
    m_stats.activeHostStreams = static_cast<uint32_t>(m_hostStreams.size());

    m_stats.framesMixed += frames;
    m_stats.peak = std::max(m_stats.peak, peak);
}

void PS2Spu2::traceVoices(uint32_t frames)
{
    static const bool enabled = std::getenv("PS2X_TRACE_SPU2") != nullptr;
    if (!enabled)
        return;
    m_traceFrames += frames;
    if (m_traceFrames < kSampleRate * 2u)
        return;
    const double window = static_cast<double>(kSampleRate) * 2.0;
    std::fprintf(stderr, "[spu2] t=%.1fs peak=%d rms_voice=%.0f rms_adma=%.0f rms_host=%.0f voiced=%u zero=%u kon=%u koff=%u unwritten=%u",  
                 static_cast<double>(m_stats.framesMixed) / kSampleRate, m_stats.peak,
                 std::sqrt(m_traceVoiceEnergy / window), std::sqrt(m_traceAdmaEnergy / window),
                 std::sqrt(m_traceHostEnergy / window), m_traceVoiceFrames, m_traceZeroFrames,
                  m_traceKeyOns, m_traceKeyOffs, m_traceUnwrittenBlocks);
    m_traceFrames = 0u;
    m_traceVoiceEnergy = 0.0; 
    m_traceAdmaEnergy = 0.0;
    m_traceHostEnergy = 0.0;
    m_traceVoiceFrames = 0u;
    m_traceZeroFrames = 0u;
    m_traceKeyOns = 0u;
    m_traceKeyOffs = 0u;
    m_traceUnwrittenBlocks = 0u;
    for (uint32_t c = 0; c < kCoreCount; ++c)
    {
        const Core &core = m_cores[c];
        std::fprintf(stderr, " | core%u mvol=%04x/%04x mmix=%03x vmix=%06x/%06x wet=%06x/%06x fx=%u/%u evol=%04x/%04x adma=%d fresh=%u stale=%u",

                     c, core.mvolL.reg, core.mvolR.reg, core.mmix, core.vmixl, core.vmixr, core.vmixel, core.vmixer,
                     core.reverb.mode, core.attrs[CORE_ATTR_EFFECT_ENABLE >> 1], core.evolL, core.evolR,
                     core.adma.active ? 1 : 0, core.adma.freshFills, core.adma.staleFills); 
        for (uint32_t v = 0; v < kVoiceCount; ++v)
        {
            const Voice &voice = core.voices[v];
            if (voice.phase == EnvPhase::Off)
                continue;   
            std::fprintf(stderr, "\n[spu2]   c%u v%02u pitch=%04x vol=%04x/%04x adsr=%04x/%04x ssa=%06x lsax=%06x nax=%06x env=%04x flags=%02x phase=%d",
                         c, v, voice.pitch, voice.volL.reg, voice.volR.reg, voice.adsr1, voice.adsr2,
                         voice.ssa, voice.lsax, voice.nax, static_cast<unsigned>(voice.envLevel), voice.blockFlags,
                         static_cast<int>(voice.phase));
        }
    }
    std::fprintf(stderr, " | host streams=%zu\n", m_hostStreams.size());
}

 void PS2Spu2::setParam(uint32_t entry, uint32_t value)
{
    std::lock_guard<std::mutex> lock(m_mutex);   
    Core &core = m_cores[entryCore(entry)];
    const uint32_t index = paramIndex(entry);
    const uint16_t v = static_cast<uint16_t>(value);
    if (index <= 0x07u)
    {
         const uint32_t vi = entryVoice(entry);
        if (vi >= kVoiceCount)
            return ;
        Voice &voice = core.voices[vi];
        switch (index)
        {  
        case 0x00:
            setSweep(voice.volL, v);
            break;

        case 0x01:
            setSweep(voice.volR, v);
            break;
        case 0x02:
            voice.pitch = v;
            break ;
        case 0x03:
            voice.adsr1 = v;
            break;
        case 0x04:
            voice.adsr2 = v;
            break;
        case 0x05:
            voice.envLevel = std::clamp<int32_t>(static_cast<int16_t>(v), 0, kEnvMax);
            break;
        default:
            break;
        }
        return;

    }
     switch (index)
    {
    case 0x08:   
        core.mmix = value & 0xFFFu;
        break;

     case 0x09:
        setSweep(core.mvolL, v);
        break;
    case 0x0A:
        setSweep(core.mvolR, v);
        break;
    case 0x0B:
        core.evolL = v;
        break;
    case 0x0C:
        core.evolR = v;
        break;
    case 0x0D:
        core.avolL = v;
        break;
    case 0x0E:
        core.avolR = v;
        break;
    case 0x0F:
        core.bvolL = v;
        break;
    case 0x10:
        core.bvolR = v;
         break;
    default: 
        break;

    }
}

uint32_t PS2Spu2::getParam(uint32_t entry)
{

    std::lock_guard<std::mutex> lock(m_mutex);
    Core &core = m_cores[entryCore(entry)];
    const uint32_t index = paramIndex(entry);
    if (index <= 0x07u)
    {
        const uint32_t vi = entryVoice(entry);

        if (vi >= kVoiceCount)
            return 0u;
        Voice &voice = core.voices[vi];
        switch (index)
        {
        case 0x00:
            return voice.volL.reg;
        case 0x01:
            return voice.volR.reg;
        case 0x02:
            return voice.pitch;
        case 0x03:
            return voice.adsr1;
        case 0x04: 
            return voice.adsr2;
        case 0x05:
            return static_cast<uint32_t>(voice.envLevel) & 0xFFFFu;
        case 0x06:

            return static_cast<uint32_t>(voice.volL.level) & 0xFFFFu;
        case 0x07:
            return static_cast<uint32_t>(voice.volR.level) & 0xFFFFu;
         default:
            return 0u;
        }
    }
    switch (index)
    {
    case 0x08:
        return core.mmix;
    case 0x09:
        return core.mvolL.reg;
    case 0x0A:
        return core.mvolR.reg;
    case 0x0B:
        return core.evolL;
     case 0x0C:
        return core.evolR; 
    case 0x0D:
        return core.avolL;
    case 0x0E:
        return core.avolR;
    case 0x0F:

         return core.bvolL;
    case 0x10:
        return core.bvolR;
    case 0x11:
        return static_cast<uint32_t>(core.mvolL.level) & 0xFFFFu;
    case 0x12:
        return static_cast<uint32_t>(core.mvolR.level) & 0xFFFFu;
    default:
        return 0u;
    }
}

void PS2Spu2::setSwitch(uint32_t entry, uint32_t value)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    Core &core = m_cores[entryCore(entry)];
    const uint32_t mask = value & 0xFFFFFFu ;
    switch (paramIndex(entry))
    { 
    case 0x13:
        core.pmon = mask;
        break;
    case 0x14:
        core.non = mask;
        break ;
    case 0x15:
        for (uint32_t v = 0; v < kVoiceCount; ++v)
         {
            if (mask & (1u << v))
             {
                keyOn(core, v);
                advanceEnvelope(core.voices[v]);
            }
        }
        break;
    case 0x16:
        for (uint32_t v = 0; v < kVoiceCount; ++v)
        {
            if (mask & (1u << v))
                keyOff(core.voices[v]);
        }
        break;
    case 0x17:
        for (uint32_t v = 0; v < kVoiceCount; ++v)
        {
            if (mask & (1u << v))  

                core.voices[v].endx = false;
        }
        break;

    case 0x18:
        core.vmixl = mask;
        break;
    case 0x19:
        core.vmixel = mask;
        break;
    case 0x1A:
        core.vmixr = mask;
        break;
    case 0x1B:
        core.vmixer = mask;
        break;  
    default:
        break;
    }  
}

uint32_t PS2Spu2::getSwitch(uint32_t entry)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    Core &core = m_cores[entryCore(entry)];
    switch (paramIndex(entry))
     {
    case 0x13:
        return core.pmon;
    case 0x14:
        return core.non;
     case 0x15:
    {
        uint32_t mask = 0u;
        for (uint32_t v = 0; v < kVoiceCount; ++v)
        {
            if (core.voices[v].phase != EnvPhase::Off && core.voices[v].phase != EnvPhase::Release)
                mask |= 1u << v;
        }
         return mask;
    }
    case 0x16:
        return 0u;

    case 0x17:
     {
        uint32_t mask = 0u;
        for (uint32_t v = 0; v < kVoiceCount; ++v)

        {
            if(core.voices[v].endx)
                mask |= 1u << v;
        }
        return mask;
    } 
    case 0x18:
        return core.vmixl;
    case 0x19:
        return core.vmixel;
    case 0x1A:
        return core.vmixr;
    case 0x1B:
        return core.vmixer ;
    default:
        return 0u;
    }
}

void PS2Spu2::setAddr(uint32_t entry, uint32_t value) 
{
    std::lock_guard<std::mutex> lock(m_mutex);
    Core &core = m_cores[entryCore(entry)];
    const uint32_t index = paramIndex(entry);
    const uint32_t addr = wrapRam(value);
    if (index >= 0x20u)
    {
        const uint32_t vi = entryVoice(entry);
        if (vi >= kVoiceCount)
            return;
        Voice &voice = core.voices[vi];
        switch (index)
        {
        case 0x20:
            voice.ssa = addr;  
            break;
        case 0x21:
            voice.lsax = addr;

            break;
        case 0x22:
            voice.nax = addr;
            break;
        default:  
            break;
        }
        return;
    }
    switch (index)

    {
    case 0x1C:
        core.esa = addr;
        break;
    case 0x1D:
        core.eea = addr;
        break;
    case 0x1E:   
        core.tsa = addr;

        break;
    case 0x1F:
        core.irqa = addr;
        break;

    default:
        break;
    }
}

uint32_t PS2Spu2::getAddr(uint32_t entry)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    Core &core = m_cores[entryCore(entry)];
    const uint32_t index =  paramIndex(entry);
    if (index >= 0x20u)
    {
        const uint32_t vi = entryVoice(entry);
        if (vi >= kVoiceCount)   
            return 0u;

        const Voice &voice = core.voices[vi];
        switch (index)
        {
        case 0x20:
            return voice.ssa;
        case 0x21:
            return voice.lsax;
        case 0x22:
            return voice.nax;
        default:
            return 0u;
        }
    }
    switch (index)
    {
    case 0x1C:
        return core.esa;
    case 0x1D:
        return core.eea;
    case 0x1E:  
        return core.tsa;
    case 0x1F:
        return core.irqa;

    default:
        return 0u;
    }
}

void PS2Spu2::setCoreAttr(uint32_t entry, uint32_t value)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    Core &core = m_cores[entryCore(entry)];

    const uint32_t index =  (entry >> 1) & 0xFu;

    core.attrs[index] = value;
}

uint32_t PS2Spu2::getCoreAttr(uint32_t entry)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    Core &core = m_cores[entryCore(entry)];
    const uint32_t index = (entry >> 1) & 0xFu;
    return core.attrs[index];
}

uint32_t PS2Spu2::voiceTrans(uint32_t coreIndex, uint32_t mode, uint32_t iopAddr, uint32_t spuAddr, uint32_t size)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    (void)coreIndex;
    if (size == 0u)   

        return 0u ;
    const uint32_t direction = mode & TRANS_DIRECTION_MASK;

    const uint32_t dest = wrapRam(spuAddr);
    const uint32_t clamped = std::min(size, kRamSize - dest);
    if (direction == TRANS_READ)
    {
        uint8_t *dst = guestRange(iopAddr, clamped);
        if (!dst)

            return 0u;
        std::memcpy(dst, m_ram.data() + dest, clamped);
        return clamped;
    }
    const uint8_t *src = guestRange(iopAddr, clamped);
    if (!src)  
        return 0u;

    std::memcpy(m_ram.data() + dest, src, clamped);
    for (uint32_t block = dest / 16u; block <= (dest + clamped - 1u) / 16u; ++block)
        m_ramWritten[block >> 6] |= 1ull << (block & 63u);
    m_stats.voiceTransBytes += clamped;
    return (mode & TRANS_MODE_IO) != 0u ? 0u : clamped;

}

uint32_t PS2Spu2::blockTrans(uint32_t coreIndex, uint32_t mode, uint32_t iopAddr, uint32_t size, uint32_t startAddr)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    Core &core = m_cores[coreIndex & 1u];
    const uint32_t direction = mode & TRANS_DIRECTION_MASK;
    if (direction == TRANS_STOP)
    {

         Adma &adma = core.adma;
        const uint32_t status = adma.active
                                    ? (((adma.consumed >= adma.size / 2u) ? 1u : 0u) << 24) |
                                          ((adma.iopBase + adma.consumed) & 0x00FFFFFFu)
                                    : 0u ;  
        adma = Adma{};
        const uint32_t base = meminBase(coreIndex & 1u);   
        std::memset(m_ram.data() + base, 0, kMeminFrames * 4u);
        return status;
    }
    if (direction == TRANS_READ)
        return 0u;
    if (iopAddr == 0u || size < ADMA_BLOCK_BYTES)
        return 0xFFFFFFFFu;
    admaStart(core, coreIndex & 1u, mode, iopAddr, size, startAddr);
    return 0u;
}

uint32_t PS2Spu2::voiceTransStatus(uint32_t coreIndex, uint32_t flag)
{
    (void)coreIndex;
    (void)flag;
    return 1u;
}

uint32_t PS2Spu2::blockTransStatus(uint32_t coreIndex, uint32_t flag)
{
    (void)flag;
    std::lock_guard<std::mutex> lock(m_mutex) ;
    const Adma &adma = m_cores[coreIndex & 1u].adma;
    if (!adma.active)
        return 0u;
    const uint32_t bank = (adma.size != 0u && adma.consumed >= adma.size / 2u) ? 1u : 0u;

    return (bank << 24) | ((adma.iopBase + adma.consumed) & 0x00FFFFFFu);
}

int32_t PS2Spu2::batchOne(const ps2x::iop::Spu2Batch &b, uint32_t *ret) 
{
    uint32_t value = 0u;
     switch (b.func)
    {
    case BATCH_SETPARAM:
        setParam(b.entry, b.value & 0xFFFFu);
        break;
    case BATCH_SETSWITCH:
        setSwitch(b.entry, b.value);
        break;
    case BATCH_SETADDR:
        setAddr(b.entry, b.value);
         break;
    case BATCH_SETCOREATTR:
        setCoreAttr(b.entry, b.value & 0xFFFFu);
        break;
    case BATCH_WRITEIOP:
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        uint8_t *dst = guestRange(b.value, 4u);
        if (dst)   
        {
            const uint32_t word = b.entry;

            std::memcpy(dst, &word, sizeof(word));

        }
        break;

    }   
    case BATCH_WRITEEE:
    case BATCH_EERETURN:
         break;
     case BATCH_GETPARAM:
        value = getParam(b.entry);

        break;
    case BATCH_GETSWITCH:
        value = getSwitch(b.entry);
        break;
    case BATCH_GETADDR:
        value = getAddr(b.entry);
        break;
    case BATCH_GETCOREATTR:

        value = getCoreAttr(b.entry);
         break;
    default:
        return -1;
     }
    if (ret)
        *ret = value;
    return 0;
}

int32_t PS2Spu2::procBatch(const ps2x::iop::Spu2Batch *batch, uint32_t count, uint32_t *returns, uint32_t voiceMask)  
{
    if(!batch)
        return 0;
    uint32_t slot = 0u;
    for (uint32_t i = 0; i < count; ++i)
     {
        const ps2x::iop::Spu2Batch &b = batch[i];
        const bool paramLike = b.func == BATCH_SETPARAM || b.func == BATCH_GETPARAM;
        const bool addrLike = b.func == BATCH_SETADDR || b.func == BATCH_GETADDR;
        const bool wildcard =  (paramLike && (b.entry & 0x3Eu) == 0x3Eu) ||
                              (addrLike && (b.entry & 0x7Eu) == 0x7Eu);
        if (wildcard)
        {
            for (uint32_t v = 0; v < kVoiceCount; ++v)
            {
                if ((voiceMask & (1u << v)) == 0u)
                    continue;
                ps2x::iop::Spu2Batch expanded = b;

                expanded.entry = static_cast<uint16_t>((b.entry & ~0x3Eu) | (v << 1));
                if (batchOne(expanded, returns ? &returns[slot] : nullptr) < 0)
                    return -static_cast<int32_t>(i + 1u);
                ++slot;
            }
            continue;
        }
        if (batchOne(b, returns ? &returns[slot] : nullptr) < 0)
            return -static_cast<int32_t>(i + 1u);
        ++slot;
    }
    return static_cast<int32_t>(slot);
 }

bool PS2Spu2::writeRam(uint32_t spuAddr, const void *data, uint32_t size)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    const uint32_t dest = wrapRam(spuAddr);
     if (!data || dest + size > kRamSize)
        return false;
    std::memcpy(m_ram.data() + dest, data, size);
    if (size != 0u)
    {
        for (uint32_t block = dest / 16u; block <= (dest + size - 1u) / 16u; ++block)
            m_ramWritten[block >> 6] |= 1ull << (block & 63u);
    }
     return true;
}

bool PS2Spu2::readRam(uint32_t spuAddr, void *out, uint32_t size) const
{

    std::lock_guard<std::mutex> lock(m_mutex);
     const uint32_t src = wrapRam(spuAddr);
    if (!out || src + size > kRamSize)
        return false;
    std::memcpy(out, m_ram.data() + src, size);
    return true;
}

void PS2Spu2::setPeriodicTick(std::function<void()> tick, uint32_t intervalFrames)
{
    std::lock_guard<std::mutex> lock(m_tickMutex);
    m_tick = std::move(tick);
    m_tickInterval = intervalFrames;
    m_tickAccumulated = 0u;
}

uint32_t PS2Spu2::createHostStream(uint32_t sampleRate, std::shared_ptr<ps2x::iop::HostPcmSource> source)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    HostStream stream;
    stream.id = m_nextHostStreamId++;

    stream.sampleRate = sampleRate == 0u ? kSampleRate : sampleRate;
    stream.source = std::move(source);
     m_hostStreams.push_back(std::move(stream));
    return m_hostStreams.back().id;  

 }

void PS2Spu2::destroyHostStream(uint32_t id)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    m_hostStreams.erase(std::remove_if(m_hostStreams.begin(), m_hostStreams.end(),
                                       [id](const HostStream &s)
                                        { return s.id == id; }),
                        m_hostStreams.end());
}

void PS2Spu2::setHostStreamVolume(uint32_t id, float left, float right)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    for (HostStream &s : m_hostStreams)
    {
        if (s.id == id)
        {
            s.volL = std::clamp(left, 0.0f, 4.0f);
            s.volR = std::clamp(right, 0.0f, 4.0f);
        }
    }
}

void PS2Spu2::setHostStreamPaused(uint32_t id, bool paused)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    for (HostStream &s : m_hostStreams)

    {
        if (s.id == id)
            s.paused = paused;
    }
}

bool PS2Spu2::hostStreamActive(uint32_t id) const
{
     std::lock_guard<std::mutex> lock(m_mutex);
    for (const HostStream &s : m_hostStreams)
    {
        if (s.id == id)
             return !s.finished;
    }
    return false;
}
