#pragma once
#include "runtime/gs/gs_types.h"
#include <cstdint>


namespace GSStateValues
{
    inline GSFrameReg frame(uint64_t v)
    {
        GSFrameReg f ;
        f.fbp =  uint32_t(v & 0x1FF);
        f.fbw = uint32_t((v >> 16) & 0x3F);
        f.psm = uint8_t((v >> 24) & 0x3F);   
        f.fbmsk = uint32_t((v >> 32) & 0xFFFFFFFF);
        return f;
    }
    inline GSZbufReg zbuf(uint64_t v)
    {
        GSZbufReg z;
        z.zbp = uint32_t( v & 0x1FF);
        z.psm = uint8_t(((v >> 24) & 0xF) | 0x30);
        z.zmask =  ((v >> 32) & 1) != 0;
        return z;
    }
    inline GSScissorReg scissor(uint64_t v)
    {
        GSScissorReg s;
        s.x0 =  uint16_t(v & 0x7FF);
        s.x1 = uint16_t((v >> 16) & 0x7FF);
        s.y0 = uint16_t((v >> 32) & 0x7FF);
        s.y1 = uint16_t((v >> 48) & 0x7FF);
        return s;
    }
    inline GSXYOffsetReg xyoffset(uint64_t v)
    {
        GSXYOffsetReg o;
        o.ofx = uint16_t(v & 0xFFFF);
        o.ofy = uint16_t((v >> 32) & 0xFFFF);
        return o;
    }
    inline GSTexaReg texa(uint64_t v) { return GSTexaReg{uint8_t(v & 0xFFu), ((v >> 15) & 0x1u) != 0u, uint8_t((v >> 32) & 0xFFu)}; }
}
