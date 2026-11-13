#pragma once
#include "runtime/gs/gs_native_types.h"
#include "runtime/gs/render_cmd.h"

#include <array>
#include <cstdint>
#include <memory>
#include <vector>

// A decoded texture: RGBA8 GS byte values (alpha 0x80 = 1.0).
struct GSNativeTexture
{
    uint32_t width = 0, height = 0;
    std::vector<uint32_t> rgba; 
    mutable std::shared_ptr<void> gpu;
};

struct GSNativeMeshGroup
{
    uint32_t firstIndex = 0, indexCount = 0;
    uint32_t type = 0;
    bool tcc = true;  // TEX0.TCC

    uint32_t tfx = 0; // TEX0.TFX
    std::shared_ptr<const GSNativeTexture> texture;
    bool envMesh = false;
    uint32_t passes = 1;
    std::shared_ptr<const GSNativeTexture> envTexture;
};

struct GSNativeMesh
{
    std::vector<GSNativeSkinVertex> vertices;
    std::vector<uint32_t> indices;
    std::vector<GSNativeMeshGroup> groups ;
    mutable std::shared_ptr<void> gpu;

};

struct GSNativeModelParams
{
    std::shared_ptr<const GSNativeMesh> mesh;
    uint32_t typeMask = 0;    // bit per group type to draw
    float screen[4][4]{};     // object -> GS window: column vectors (VU0 qwords 0-3)
    float lightDir[3][4]{};   // N.L = lightDir[0] * n.x + lightDir[1] * n.y + lightDir[2] * n.z (qwords 4-6)   
    float lightColor[4][4]{}; // colour = sum L.i * lightColor[i] + lightColor[3] (qwords 8-11)
    float clampMax[4]{};      // qword 12: .w = colour and fog maximum
    float fog[4]{};           // qword 13: fog = x * w + y
    float depthBias = 0;      // subtracted from z / w (depth-bias meshes)
    uint32_t alpha = 0x80;    // vertex alpha
    bool squareLight = false; // N.L is squared (mesh flag 0x40)
    float envScale = 0;
    int32_t colorAdd[4]{};
    int context = 1;          // GS drawing context (models: 2)
    bool noShadow = false;    // drawn for an off-screen picture (far soldier impostor): no real-time shadow
    bool placed = false;      // screen = camera * placement * D (far-soldier 3D copies), not camera * D
    std::vector<std::array<float, 16>> bones; // 4 columns of 4 floats each
    std::vector<std::array<float, 32>> instances;

    struct InstancePose
    {
        uint64_t id = 0;

        std::shared_ptr<const std::vector<std::array<float, 16>>> bones;

    };
    std::vector<InstancePose> instancePoses;

};

namespace NativeDraw
{
    std::unique_ptr<RenderCmd> makeModelDraw(GSNativeModelParams params);
}
