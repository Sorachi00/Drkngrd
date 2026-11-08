#pragma once

#include "runtime/ps2_vdisc.h"

#include <cstdint>
#include <vector>

namespace PS2NativeMovie
{
    // PS2_NATIVE_MOVIE=0 turns the native player off (the game's own player runs).
    bool enabled();

    bool start(const PS2VDisc::FilePtr &file, uint64_t offset);
    // Stops the movie (skip) or releases a finished one.
    void stop(); 
    // A movie was started and not stopped.
    bool active();
     // Everything of the movie has been heard and shown.
    bool finished();

    bool readAudio(int16_t *pcm, uint32_t frames) ;
    bool currentFrame(std::vector<uint8_t> &rgba, int &width, int &height, uint32_t &index, uint64_t &serial);
}
