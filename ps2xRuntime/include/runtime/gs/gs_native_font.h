#pragma once
#include <cstdint>
#include <memory>
#include <mutex>
#include <vector>


struct GSNativeFontData
{  
    uint32_t cell = 0, cellBytes = 0, cells = 0;
    std::vector<uint8_t> bitmap;
    mutable std::shared_ptr<void> gpu;
}; 

#ifndef DK_RENDER_DLL
#include "runtime/gs/render_cmd.h"

// A glyph of a batch: the game's GS words of its sprite.
struct GSNativeFontGlyph
{
    uint64_t rgbaq = 0;          // RGBAQ register
    uint64_t xyz0 = 0, xyz1 = 0; // XYZF2 registers of the two vertices  
    uint32_t cell = 0;           // bitmap cell (glyph / 2)
    uint32_t odd = 0;            // TEX0 of odd glyphs (glyph & 1)
};

struct GSNativeFontBatch
{
    std::shared_ptr<const GSNativeFontData> font;
    uint64_t tex0[2]{};                       // TEX0_2 of even / odd glyphs
    uint64_t tex1 = 0, alpha = 0, prim = 0;   // TEX1_2, ALPHA_2, PRIM
    uint64_t uv0 = 0, uv1 = 0;                // UV of the two vertices
    uint64_t bitbltbuf = 0, trxpos = 0, trxreg = 0;

    uint32_t owner = 0; // the hooked draw function that wrote the text (widescreen anchor), 0: unknown
    mutable std::mutex mutex;
    std::vector<GSNativeFontGlyph> glyphs;
};

namespace NativeDraw
{

    std::unique_ptr<RenderCmd> makeFontDraw(std::shared_ptr<const GSNativeFontBatch> batch);
    void fontAddGlyph(RenderCmd &cmd, GSNativeFontBatch &batch, const GSNativeFontGlyph &glyph);
}
#endif
