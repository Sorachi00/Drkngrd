#pragma once
#include "runtime/gs/gs_native_types.h"
#include "runtime/gs/render_cmd.h"

#include <cstdint>
#include <memory>
#include <vector>

struct GSNativeBlobParams
{
    std::vector<GSNativeBlobQuad> quads;
#ifndef DK_RENDER_DLL
    uint64_t tex0 = 0; // TEX0_2 of the quads (the exe's: the renderer asks for texture slot 0)
#endif
};

namespace NativeDraw
{
    std::unique_ptr<RenderCmd> makeBlobDraw(GSNativeBlobParams params);

}
