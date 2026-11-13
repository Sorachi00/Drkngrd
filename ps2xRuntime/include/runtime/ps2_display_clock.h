#pragma once

#include <chrono>
#include <cstdint>

namespace PS2DisplayClock
{
    using Clock = std::chrono::steady_clock;

    struct Grid
    {
        Clock::time_point vblank; // a recent monitor vblank
        Clock::duration period;   // refresh period
        double hz = 0;
    };
    void setWindow(void *window);
    // False while no steady vblank comes from that monitor (or off Windows).
    bool grid(Grid &out);

    Clock::time_point lockVBlank(Clock::time_point target, uint32_t gameHz);

    void frameShown(Clock::time_point t, Clock::time_point published, uint64_t serial);
    // At exit: stops and joins the vblank thread.
    void shutdown();

}

