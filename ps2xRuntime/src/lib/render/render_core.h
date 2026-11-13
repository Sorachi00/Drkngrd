#pragma once
#include "runtime/render/rdraw.h"
#include <cstdint>

namespace rdraw
{
    constexpr uint32_t kTargetHeight = 2048;

    struct Batch
    {
        DrawSetup state;
        TargetId color = 0, depth = 0; // depth 0: no depth test or write
        uint32_t depthRows = 0;
        Rect scissor;
        TexSource source =  TexSource::None;
        TextureId texture = 0;
        bool textureCacheHw = false; // the texture is exactly its full size: hardware bilinear at upscale
        TargetId sourceTarget = 0;
        Rect copyArea;               // TexSource::TargetCopy: pixels of `color` copied before the batch
        bool lines = false;
        const Vertex *vertices = nullptr;
        uint32_t vertexCount = 0;  
    };

    enum class PresentMode : uint8_t
    {
        Copy,      // texels as they are
        Scaled,    // drawn into the picture's size (point sampled)
        Deflicker, // each line the mean of itself and the next
    };

    constexpr uint32_t kNoTexel = 0xFFFFFFFFu;
    struct Gather
    {
        TargetId source = 0;
        uint32_t wordBits = 32, bits = 32, depthMask = 0xFFFFFFFFu;
        const uint32_t *map = nullptr;
        uint64_t mapKey = 0; // the same key: the same map (kept on the GPU); 0: uploaded each time

        const uint32_t *palette = nullptr;
        TextureId fallback = 0;
        TexAlpha alphaMode = TexAlpha::AsIs;  
        uint8_t alpha0 = 0, alpha1 = 0;
        bool blackClear = false;
        uint32_t mapWidth = 0, mapHeight = 0;
        const uint16_t *blocks = nullptr;
        const uint32_t *owned = nullptr;
        uint32_t rows = 0; // (not 0: map pixels at or below this row are the fallback's)
    };  

    struct Present
    {
        TargetId target = 0;
        float src[4] =  {};
        PresentMode mode = PresentMode::Copy;
        float deflickerStep =  0;
        const uint32_t *pixels = nullptr;
        uint32_t pixelsWidth = 0, pixelsHeight = 0;
        uint32_t width = 0, height = 0;
        uint64_t vsyncTick = 0;
        const char *dumpPath = nullptr;  
        TargetId dumpTarget = 0;
        uint32_t dumpWidth = 0, dumpHeight = 0;
        bool toWindow = true;
    };

    struct Stats
    {
        uint64_t draws = 0, rovDraws = 0, targetTextureDraws = 0, cachedDraws = 0, surfaceUploads = 0, reinterprets = 0;
        uint64_t d3dFlushes = 0;  
    };

    class Core
    {
    public:
        Core();
        ~Core();
        Core(const Core &) = delete;
        Core &operator=(const Core &) = delete;

        void create(); 
        bool ready() const; 

        uint32_t scale() const;
        bool setScale(uint32_t scale) ;

        TargetId createTarget(uint32_t width, bool depth, uint32_t scale = 0);
        void releaseTarget(TargetId target);
        uint32_t targetScaleX(TargetId target) const;
        uint32_t targetScaleY(TargetId target) const;
        void copyTexels(TargetId dst, TargetId src, uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1);
        // RGBA8 pixels (w x h, rows of w) into pixels `r` of a colour target.
        void writePixels(TargetId target, const Rect &r, const uint32_t *pixels, bool movie = false);
        void writePixelsMasked(TargetId target, const Rect &r, const uint32_t *pixels, const uint8_t *mask);
        void clearPixels(TargetId target, const Rect &r, uint32_t rgba);   

        TextureId createTexture(uint32_t width, uint32_t height);
        void releaseTexture(TextureId texture);
        void updateTexture(TextureId texture, const Rect &r, const uint32_t *pixels);
        void gather(TextureId out, const Rect &area, const Gather &g);

        void draw(const Batch &batch);

        bool bindNative(TargetId color, TargetId depth, const Rect &scissor);
        void unbind();
        void restoreState();

        void present(const Present &p);
        void flush();
        Stats stats(bool reset);

        struct Impl;

    private:
        Impl *m = nullptr; // (the DLL's; null in the exe, whose calls go to the DLL)
    };
}
