#pragma once
#include "runtime/gs/gs_native_types.h"
#include "runtime/gs/render_cmd.h"
#include "runtime/gs/gs_native_model.h"
#include "runtime/render/rdraw.h"

#include <cstdint>
#include <memory>
#include <vector>

struct GSNativeMapMesh
{

    std::vector<GSNativeMapVertex> vertices ;
    std::vector<uint32_t> indices;
    std::vector<GSNativeMapGroup> groups;
    mutable std::shared_ptr<void> gpu;   
};

struct GSNativeMapParams
{
    std::shared_ptr<const GSNativeMapMesh> mesh;
#ifndef DK_RENDER_DLL
    std::vector<uint64_t> tex0;  // TEX0_1 list of the block (the exe's: it gives the renderer the slots)
#endif
    std::vector<rdraw::TexMode> slots;
    // The list's textures decoded from the map file (null: read GS memory).
    std::vector<std::shared_ptr<const GSNativeTexture>> textures;
    float matrix[4][4]{};        // columns c0..c3 (VU1 903-906)
    int32_t origin[3]{};         // block origin (VU1 917), block units * 16
    float camera[3]{};           // camera for the strip planes (VU1 907)
    float fog[2]{};              // fog = fog[0] + fog[1] * w, clamped to 0..255
    float ramp[3]{};             // big MAP alpha = clamp(ramp[0] + ramp[1] * w, 0, ramp[2])
    uint32_t aref = 0;           // TEST_1 AREF (alpha test GREATER, AFAIL FB_ONLY)
    bool colourOnly = false;     // layer 3 of a block: TEST NEVER + RGB_ONLY (no Z, no alpha write)

    bool worldMatrix = false;    // matrix = the camera's world -> window (not a prop's own matrix)
};


struct GSNativeSkyMesh
{
    std::vector<GSNativeSkyVertex> vertices;
    std::vector<uint32_t> indices;
    mutable std::shared_ptr<void> gpu;
};

struct GSNativeSkyCell
{
    std::shared_ptr<const GSNativeSkyMesh> mesh;
    std::shared_ptr<const GSNativeTexture> texture;
#ifndef DK_RENDER_DLL
    uint64_t tex0 = 0, tex1 = 0;                    // TCC / TFX, MMAG (the exe's: it gives the renderer mode, bilinear)  

#endif
    rdraw::TexMode mode;
    bool bilinear = false;
    int32_t row[2]{};                               // VIF ROW x, z

};

struct GSNativeSkyParams
{
    std::vector<GSNativeSkyCell> cells; // in the game's draw order

    float m1[4][4]{};                   // columns, VU1 0-3 (window coordinates)
    float m2[4][4]{};                   // columns, VU1 4-7 (clip test)
    float scale[4]{};                   // VU1 16
    float fog[4]{};                     // VU1 15
};

namespace NativeDraw
{
    std::unique_ptr<RenderCmd> makeMapDraw(GSNativeMapParams params);
    std::unique_ptr<RenderCmd> makeSkyDraw(GSNativeSkyParams params);
}
