#pragma once

#include <atomic>
#include <chrono>
#include <cstdint>

#include "runtime/ps2_perf.h"

namespace GSPerf
{
    using Clock = std::chrono::steady_clock;
    // Completed frame submissions from the game's frame routine, not GS
    // register writes, VBlanks, draw calls or changes in pixel contents.
    inline std::atomic<uint64_t> gameFrames{0};
    inline std::atomic<uint32_t> frameSubmitReturnPc{0};

    inline void recordFrameSubmission(uint32_t returnPc, int32_t result)
    {
        // Count only an accepted submission, once even if the EE yielded.
        if (returnPc != 0u && returnPc == frameSubmitReturnPc.load(std::memory_order_relaxed) && result == 0)
        {
            gameFrames.fetch_add(1, std::memory_order_relaxed);
            PS2Perf::onGameFrame();   

        }
    }

    inline double framesPerSecond(uint64_t frames, Clock::duration elapsed)
    {
        return frames / std::chrono::duration<double>(elapsed).count();
    }

}
