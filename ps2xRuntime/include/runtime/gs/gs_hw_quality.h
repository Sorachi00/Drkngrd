#pragma once

#include <cstdint> 

namespace GSHwQuality
{
    // Anti-aliasing of the final picture: 0 off, 1 FXAA, 2 SMAA.
    enum AntiAlias : uint32_t
    {
        kAaOff = 0,
        kAaFxaa = 1,

        kAaSmaa = 2,
    };   

    void setAntiAlias(uint32_t mode);
    uint32_t antiAlias();

    void setTextureFilter(uint32_t level);
    uint32_t textureFilter();

    void setDeflicker(bool on);
    bool deflicker();

    enum Shadows : uint32_t
    {
        kShadowsOriginal = 0,  
        kShadowsRealtime = 1,
    };
    void setShadows(uint32_t mode);
    uint32_t shadows();

    enum Characters : uint32_t
    {
        kCharactersOriginal = 0,
        kCharactersCel = 1,
    };
    void setCharacters(uint32_t mode);
    uint32_t characters();  

    struct CelParams
    {
        float edge = 0.5f;      // where the key light turns from dark to lit (0..1)
        float softness =  0.08f;
        float keyLevel = 0.9f;
        float rimLevel = 0.5f;
        float rimPower = 4.0f;  // rim width: higher = thinner
        float darkLevel = 1.0f;
    };

    void setCelParams(const CelParams &params);
    CelParams celParams();

    struct PostParams
    {
        bool ao = true;
        float aoRadius = 3.0f;
        float aoIntensity = 0.8f;
        float aoDistance = 150.0f;  // fades out up to this distance
        bool grade = true;
        float exposure = 1.0f;
        float contrast = 1.0f;
        float saturation = 1.0f;

        float temperature = 0.0f;   // < 0 cooler, > 0 warmer
        float tint[3] = {1.0f, 1.0f, 1.0f};
        float tintAmount = 0.0f;
        float vignette = 0.0f;
    };
    void setPostParams( const PostParams &params);
    PostParams postParams();
    bool postWanted();

    void setSaveHandler(void (*save)());
    void save();
}
