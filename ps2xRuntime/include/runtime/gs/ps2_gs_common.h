#ifndef PS2_GS_COMMON_H
#define PS2_GS_COMMON_H

#include "runtime/gs/gs_types.h"
#include <cstdint>

namespace GSInternal
{
static inline uint32_t bitsPerPixel(uint8_t psm)
{
    switch (psm)
    {
    case GS_PSM_CT32:
    case GS_PSM_Z32:
        return 32;
    case GS_PSM_CT24:
    case GS_PSM_Z24:
        return 32;
    case GS_PSM_CT16:
    case GS_PSM_CT16S:
    case GS_PSM_Z16:
    case GS_PSM_Z16S:
        return 16;
    case GS_PSM_T8:
    case GS_PSM_T8H:
        return 8;
    case GS_PSM_T4:
    case GS_PSM_T4HL:
    case GS_PSM_T4HH:
        return 4;
    default:
        return 32;
    }
}

static inline uint32_t fbStride(uint32_t fbw, uint8_t psm)
{
    uint32_t pixelsPerRow = fbw * 64u;
    return pixelsPerRow * (bitsPerPixel(psm) / 8u);
}

static inline uint32_t framePageBaseToBlock(uint32_t fbp)
{
    return fbp << 5u;
}

static inline int clampInt(int v, int lo, int hi)
{
    if (v < lo) return lo;
    if (v > hi) return hi;
    return v;
}

static inline uint8_t clampU8(int v)
{
    if (v < 0) return 0;
    if (v > 255) return 255;
    return static_cast<uint8_t>(v);
}
}

namespace GSGameHeuristics
{
constexpr int kDisplayCopyWidth = 640, kDisplayCopyHeight = 448;
inline bool isDisplayCopyBlend(uint64_t alpha)
{
    const uint32_t mode = static_cast<uint32_t>(alpha & 0xFFu), fix = static_cast<uint32_t>((alpha >> 32u) & 0xFFu);
    return mode == 0x64u && (fix == 0x60u || fix == 0x80u);   
}
inline bool isDeflickerBlend(uint64_t alpha)

{
    return (alpha & 0xFFu) == 0x64u && ((alpha >> 32u) & 0xFFu) == 0x40u;
}

inline bool tryContextFrames(bool preferredSource, uint32_t displayFbp)
{
    return !preferredSource && displayFbp == 0u;
}
inline bool sameFrame(const GSFrameReg &a, const GSFrameReg &b)
{   
    return a.fbp == b.fbp && a.fbw == b.fbw && a.psm == b.psm;
}
constexpr uint32_t kDisplayMinSize = 64, kDisplayDefaultWidth = 640, kDisplayDefaultHeight = 448,
                   kDisplayMaxWidth = 640, kDisplayMaxHeight = 512;
}

#endif
