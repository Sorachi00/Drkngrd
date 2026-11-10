#pragma once

#include <atomic>
#include <cstdint>

// The frame number of the renderer and the native ports.
namespace PS2Det
{
    inline std::atomic<uint64_t> g_vsyncTick{0};

    inline bool enabled() { return false; }
    inline uint64_t vsyncTick() { return g_vsyncTick.load(std::memory_order_acquire); }
    inline void onVBlank(uint64_t tick) { g_vsyncTick.store(tick, std::memory_order_release); }
    inline void hashGif(const uint8_t *, uint32_t) {} 
}
