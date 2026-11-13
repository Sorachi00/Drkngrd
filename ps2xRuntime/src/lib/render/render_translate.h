#pragma once
#include "runtime/render/rdraw.h"
#include <cstdint>

namespace rtrans
{
    inline bool validPsm(uint32_t psm)
    {
        switch (psm)
        {
        case 0x00: case 0x01: case 0x02: case 0x0A: case 0x13: case 0x14: case 0x1B: case 0x24: case 0x2C:
        case 0x30: case 0x31: case 0x32: case 0x3A:
            return true;
        default:
            return false;
        }
    }
    inline bool paletted(uint32_t psm) { return psm == 0x13 || psm == 0x14 || psm == 0x1B || psm == 0x24 || psm == 0x2C; }

    // TEX0 TCC / TFX.
    inline rdraw::TexMode texMode(uint64_t tex0)
    {
        rdraw::TexMode m;
        m.function = rdraw::TexFunction((tex0 >> 35) & 3);
        m.textureAlpha = ((tex0 >> 34) & 1) != 0;
        return m;
    }
    // TEX1 MMAG. 
    inline bool bilinear(uint64_t tex1) { return ((tex1 >> 5) & 1) != 0; }
    // CLAMP WMS / WMT. 
    inline rdraw::Wrap wrapU(uint64_t clamp) { return rdraw::Wrap(clamp & 3); }
    inline rdraw::Wrap wrapV(uint64_t clamp) { return rdraw::Wrap((clamp >> 2) & 3); }
    // FRAME / ZBUF PSM.
    inline bool colorFormat(uint32_t psm, rdraw::Format &out)
    {
        switch (psm)
        {
        case 0x00: out = rdraw::Format::Color32; return true;
        case 0x01: out = rdraw::Format::Color24; return true;
        case 0x02:
        case 0x0A: out = rdraw::Format::Color16; return true;
        default: return false;
        }
    }
    inline rdraw::Format depthFormat(uint32_t psm)
    {
        return psm == 0x30 ? rdraw::Format::Depth32 : psm == 0x31 ? rdraw::Format::Depth24 : rdraw::Format::Depth16;  
    }
}
