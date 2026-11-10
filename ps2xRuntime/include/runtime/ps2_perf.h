#pragma once

#include <chrono>
#include <cstdint>

// Measuring is not part of this build: every call does nothing. 
namespace PS2Perf
{
    enum Zone : uint8_t

    {
        ZoneEe = 0,
        ZoneVu1,
        ZoneVu0,
        ZoneVif1,
        ZoneGif,
        ZoneGs,
        ZoneWait,
        ZoneSyscall,
        ZoneMpeg,
        ZonePresent,

        ZoneIo,
        ZoneCount
    };

    // Same order as the numbers dk_render.dll passes (dk_render_abi.h perfCount).
    enum Counter : uint8_t
    {
        CountGsPrim = 0,

        CountGsDispatch,
        CountGsBatch,
        CountGsBatchPrim,
        CountGsUpload,
        CountGsLine,
        CountGsSerial,
        CountGsOrdered,
        CountGsNoRov,
        CountGpuRovUs,
        CountGpuRasterUs,
        CountGpuTransferUs,
        CountGpuPresentUs,
        CountGsDrainUs,
        CountGsRingFullUs,  
        CountGsFlush,
        CountGsFlushUs,
        CountGsUploadPx,
        CountGsCopyPx,
        CountGsClearPx,
        CountGsRovSpritePx,
        CountGsRovTriBoxPx,
        CountGpuPsK,
        CountGpuCsK,
        CountCount
    };

    constexpr bool g_enabled = false;
    inline bool enabled() { return false; }

    inline uint64_t now()
    {
        return static_cast<uint64_t>(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now().time_since_epoch()) .count());
    }

    inline void count(Counter, uint32_t = 1) {}
    inline void enter(Zone) {}  
    inline void leave() {}
    inline void spinWait(bool) {}
    inline void onGameFrame() {}
    inline void markCinematic() {}
    inline void markIo() {}
    inline void countVuProgram(bool, bool) {}

    struct Scope
    {
        explicit Scope(Zone) {}

    };
}

#define PS2_PERF_ZONE(zone) ((void)0)
