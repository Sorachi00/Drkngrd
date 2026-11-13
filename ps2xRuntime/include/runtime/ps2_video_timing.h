#pragma once

#include <cstdint>

namespace PS2VideoTiming
{
    void setDisplayPal(bool pal);
    void setMovieActive(bool active);
    bool pal();
    // Vertical blanks per second.
    inline uint32_t fieldsPerSecond() { return pal() ? 50u : 60u; }
}
