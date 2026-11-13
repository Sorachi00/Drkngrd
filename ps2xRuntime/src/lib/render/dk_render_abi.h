#pragma once
#include "runtime/gs/gs_hw_quality.h"

#include "runtime/gs/gs_native_types.h"
#include "render_core.h"
#include <cstddef>
#include <cstdint>

struct ID3D11Device;
struct ID3D11DeviceContext;

constexpr uint32_t kDkRenderVersion = 11;

extern "C"

{
    struct DkRes; // a resource of the renderer (opaque)
    struct DkCmd; // a render command (opaque)

    struct DkBytesView
    {
        const uint8_t *data;
        uint32_t size;
    };
    // A decoded texture (gs_native_model.h GSNativeTexture): RGBA8 GS bytes.
    struct DkTextureView
    {
        uint32_t width, height;
        const uint32_t *rgba;
        uint32_t count; // texels in rgba
    };
    // A group of a skinned mesh (GSNativeMeshGroup); textures by handle (may be null).
    struct DkMeshGroupView
    {
        uint32_t firstIndex, indexCount, type, tfx, passes;
        bool tcc, envMesh;
        DkRes *texture, *envTexture;
    };
    struct DkMeshView // GSNativeMesh
    {
        const GSNativeSkinVertex *vertices;
        uint32_t vertexCount;
        const uint32_t *indices ;
        uint32_t indexCount;
        const DkMeshGroupView *groups;
        uint32_t groupCount;
    };

    struct DkMapMeshView // GSNativeMapMesh
    {
        const GSNativeMapVertex *vertices;
        uint32_t vertexCount;
        const uint32_t *indices;
        uint32_t indexCount;
        const GSNativeMapGroup *groups;
        uint32_t groupCount;
    } ;
    struct DkSkyMeshView // GSNativeSkyMesh
    {
        const GSNativeSkyVertex *vertices;
        uint32_t vertexCount;
        const uint32_t *indices;
        uint32_t indexCount;
    };
    struct DkFontView // GSNativeFontData
    {

        uint32_t cell, cellBytes, cells;
        DkBytesView bitmap;
    };
    // A model draw (gs_native_model.h GSNativeModelParams).
    struct DkPoseView   
    {
        uint64_t id;
        DkRes *bones; // resBones
    };
    struct DkModelView
    {
        DkRes *mesh ;
        uint32_t typeMask;
        float screen[4][4], lightDir[3][4], lightColor[4][4], clampMax[4], fog[4];
        float depthBias;
        uint32_t alpha;
        bool squareLight, noShadow, placed;
        float envScale;
        int32_t colorAdd[4];
        int32_t context;
        const float (*bones)[16];
        uint32_t boneCount;
        const float (*instances)[32];
        uint32_t instanceCount;
        const DkPoseView *poses ;
        uint32_t poseCount;
    };
    struct DkMapView

    {
        DkRes *mesh;
        const rdraw::TexMode *slots;
        uint32_t slotCount;
        DkRes *const *textures;
        uint32_t textureCount;
        float matrix[4][4];
        int32_t origin[3];
        float camera[3], fog[2], ramp[3];
        uint32_t aref;

        bool colourOnly, worldMatrix;

    };
    // A sky terrain draw (GSNativeSkyParams).
    struct DkSkyCellView
    {
        DkRes *mesh, *texture;
        rdraw::TexMode mode;
        bool bilinear;
        int32_t row[2];
    };
    struct DkSkyView
    {
        const DkSkyCellView *cells;
        uint32_t cellCount;
        float m1[4][4], m2[4][4], scale[4], fog[4];
    };
    struct DkNativeTexture
    {
        rdraw::TextureId texture;
        rdraw::TargetId target; // texels [0, width) x [0, height) of this target at 1x
        uint64_t serial;        // the target's content
        uint32_t width, height;
    };
    struct DkFontInstance
    {
        float rect[4];    // corners x0, y0, x1, y1 (target pixels)
        float uv[4];      // texel coordinates at the corners
        float uvRange[4]; // texel range of the 1x pixel centres
        float depth;      // depth / 2^32

        uint32_t color;   // RGBA bytes, R low
        uint32_t glyph;   // atlas x | y << 12 of the cell, odd << 24   
        uint32_t pad;
    };   
    struct DkFontTexture
    {
        uint32_t width, height; // the texture's size (the cell repeats or clamps in it)
        rdraw::TexMode mode ;
        rdraw::Wrap wrapU, wrapV;
        uint32_t paletteBase, paletteMask; // palette entry = (index + base) & mask
        DkNativeTexture palette;
    };
    struct DkFontDraw
    {
        DkRes *font; // resFont
        const DkFontInstance *instances;
        uint32_t count; 
        rdraw::Blend blend;
        uint8_t writeMask; // channels written: R 1, G 2, B 4, A 8
        rdraw::AlphaTest alphaTest;
        bool depthOn, depthWrite;
        rdraw::DepthTest depthTest;
        bool bilinear, alphaHigh, color24;
        DkFontTexture tex[2];
    };
    struct DkNativeHost
    {
        void *user;
        bool (*bind)(void *user, const rdraw::NativeContext *context, bool depth);
        void (*drawn)(void *user, bool depthWritten);

        bool (*texture)(void *user, uint32_t context, uint32_t slot, DkNativeTexture *out);
        void (*flush)(void *user); // before the frame pass (real-time shadows): the draws so far go out
        void (*begin)(void *user); // before the command draws
    };

    // Exe functions the renderer uses.
    struct DkHostApi
    {
        uint32_t size; // sizeof(DkHostApi) 

        uint64_t (*detVsyncTick)();                      // PS2Det::vsyncTick
        uint64_t (*perfNow)();                           // PS2Perf::now
        void (*perfCount)(uint32_t counter, uint32_t n); // PS2Perf::count
        void (*perfEnter)(uint32_t zone);                // PS2Perf::enter
        void (*perfLeave)();                             // PS2Perf::leave
        void (*wsWorldDrawn)(uint32_t frame);
        void (*wsModelsDrawn)(uint32_t frame);
    };

    // Renderer functions the exe uses.

    struct DkRenderApi
    {
        uint32_t size; // sizeof(DkRenderApi)

        // Picture quality (OPTIONS screen, F2 overlay; GSHwQuality, GSHwScale).
        void (*setAntiAlias)(uint32_t mode);

        uint32_t (*antiAlias)();
        void (*setTextureFilter)(uint32_t level);
        uint32_t (*textureFilter)();
        void (*setDeflicker)(bool on);
        bool (*deflicker)();
        void (*setShadows)(uint32_t mode);
        uint32_t (*shadows)();
        void (*setCharacters)(uint32_t mode);   
        uint32_t (*characters)();
        void (*setCelParams)(const GSHwQuality::CelParams *params);
        void (*celParams)(GSHwQuality::CelParams *out);
        void (*setPostParams)(const GSHwQuality::PostParams *params);
        void (*postParams)(GSHwQuality::PostParams *out);
        bool (*postWanted)(); 
        void (*setSaveHandler)(void (*save)());
        void (*save)();
        void (*scaleRequest)(uint32_t scale);

        uint32_t (*scaleRequested)();
        void (*scaleSetDynamic)(float minFraction);

        void (*setWindow)(void *hwnd);
        void (*setClientSize)(uint32_t width, uint32_t height);
        void (*setAspect)(float aspect);
        void (*setVsync)(bool on);
        bool (*active)();
        uint64_t (*presentedFrames)();
        void (*setUiRenderer)(void (*draw)(void *user), void *user);
        void ( *uiLock)();
        void ( *uiUnlock)();

        ID3D11Device *(*device)();
        ID3D11DeviceContext *(*uiContext)();
        void (*setPresentedCallback)(void (*callback)(int64_t presentNs, uint64_t frame));

        void (*perfSetEnabled)(bool on);


        void (*coreCreate)();
        bool (*coreReady)();
        uint32_t (*coreScale)() ;
        bool (*coreSetScale)(uint32_t scale) ;
        uint32_t (*coreCreateTarget)(uint32_t width, bool depth, uint32_t scale) ;
        void (*coreReleaseTarget)(uint32_t target);
        void (*coreTargetScale)(uint32_t target, uint32_t *sx, uint32_t *sy);
        void (*coreCopyTexels)(uint32_t dst, uint32_t src, uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1);
        void (*coreWritePixels)(uint32_t target, const rdraw::Rect *r, const uint32_t *pixels, uint32_t movie);
        void (*coreWritePixelsMasked)(uint32_t target, const rdraw::Rect *r, const uint32_t *pixels, const uint8_t *mask);
        void (*coreClearPixels)(uint32_t target, const rdraw::Rect *r, uint32_t rgba);

        uint32_t (*coreCreateTexture)(uint32_t width, uint32_t height);
        void (*coreReleaseTexture)(uint32_t texture);
        void (*coreUpdateTexture)(uint32_t texture, const rdraw::Rect *r, const uint32_t *pixels);  
        void (*coreGather)(uint32_t out, const rdraw::Rect *area, const rdraw::Gather *g);
        void ( *coreDraw)(const rdraw::Batch *batch);
        bool ( *coreBindNative)(uint32_t color, uint32_t depth, const rdraw::Rect *scissor);
        void (*coreUnbind)();
        void (*coreRestoreState)();
        void (*corePresent)(const rdraw::Present *p);
        void (*coreFlush)();
        void (*coreStats)(rdraw::Stats *out, bool reset);

        // The picture quality of the frame being drawn (GSHwQualityFrame).
        void (*qualityLatch)(uint64_t vsyncTick);
        bool ( *qualityDeflicker)();

        DkRes *(*resTexture)(const DkTextureView *texture);
        DkRes *( *resMesh)(const DkMeshView *mesh);
        DkRes *(*resMapMesh)(const DkMapMeshView *mesh);
        DkRes *(*resSkyMesh)(const DkSkyMeshView *mesh);
        DkRes *(*resFont)(const DkFontView *font);
        DkRes *(*resBones)(const float (*bones)[16], uint32_t count); // a pose (4 columns of 4 floats per bone)
        void (*resRelease)(DkRes *res);

        DkCmd *(*cmdModel)(const DkModelView *model);
        DkCmd *(*cmdMap)(const DkMapView *map);  
        DkCmd *(*cmdSky)(const DkSkyView *sky);
        DkCmd *(*cmdBlob)(const GSNativeBlobQuad *quads, uint32_t count); // its texture: slot 0
        DkCmd *(*cmdPost)();
        void (*cmdRelease)(DkCmd *cmd);
        const char *(*cmdTypeName)(DkCmd *cmd);
        void (*cmdRun)(DkCmd *cmd, const rdraw::NativeEnv *env, const DkNativeHost *host);
        bool (*fontBlend)(const rdraw::Blend *blend);
        void (*fontDraw)(const DkFontDraw *draw);

        void (*frameRecord)(DkCmd *cmd, uint64_t frameId, bool ended);
        void (*frameEnd)(uint64_t frameId);
    };

    using DkRenderInitFn = bool (*)(const DkHostApi *host, DkRenderApi *out, uint32_t version);
#ifdef DK_RENDER_DLL // defined only when building dk_render.dll
    __declspec(dllexport) bool dk_render_init(const DkHostApi *host, DkRenderApi *out, uint32_t version);
#endif

}

#ifndef DK_RENDER_DLL
const DkRenderApi &dkRender(); // the exe: the DLL's table (dk_render_client.cpp)
#endif
