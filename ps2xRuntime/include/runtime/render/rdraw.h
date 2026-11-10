#pragma once
#include <cstdint>

namespace rdraw
{
    using TargetId = uint32_t;  // a render target or depth buffer (0: none)
    using TextureId = uint32_t; // a texture (0: none)


    // Texel formats of a target as the draws see them. 
    enum class Format : uint8_t
    { 
        Color32, // RGBA, 8 bits each
        Color24, // RGB, the alpha byte is not written and reads as 0x80
        Color16, // RGB 5 bits, alpha 1 bit
        Depth32,   
        Depth24,
        Depth16,
    };
    inline bool isDepth(Format f) { return f >= Format::Depth32; }

    enum class Primitive : uint8_t
    {
        Point,
        Line,     // two vertices; colour interpolated (gouraud)
        Triangle, // three vertices; colour interpolated (gouraud)
        Sprite,   // two corners; flat colour, texels interpolated linearly
    };

    enum class BlendInput : uint8_t
    {
        Source,
        Target,
        Zero,
    };
    enum class BlendFactor : uint8_t
    {
        SourceAlpha,
        TargetAlpha,

        Fixed,
    };
    struct Blend
    {

        bool on = false;
        BlendInput a = BlendInput::Source, b = BlendInput::Source, d = BlendInput::Source;
        BlendFactor c = BlendFactor::SourceAlpha;  
        uint8_t fixed =  0;
        bool onlyHighAlpha = false; // pixels with source alpha < 0x80 are written unblended
    };

    // Comparisons in this order (the shader takes the number).
    enum class Compare : uint8_t
    {
        Never,

        Always,
        Less,
        LessEqual,
        Equal,
        GreaterEqual,
        Greater,
        NotEqual,
    };
    // What a pixel that fails the alpha test still writes.
    enum class AlphaFail : uint8_t
    {
        Nothing,
        ColorOnly, // colour and alpha, no depth
        DepthOnly,
        RgbOnly, // colour without alpha, no depth
    };
    struct AlphaTest
    {
        bool on = false;
        Compare compare = Compare::Always;
        uint8_t reference = 0;
        AlphaFail fail = AlphaFail::Nothing;
    };
    // Depth: larger is nearer.
    enum class DepthTest : uint8_t
    {
        Never,
        Always,
        GreaterEqual,
        Greater,
    };
    // Destination alpha test: only pixels whose target alpha bit 7 is `bit`.
    struct TargetAlphaTest
    {
        bool on = false;
        bool bit = false ;
    };

    // Texture coordinates outside the texture.
    enum class Wrap : uint8_t
    {
        Repeat,
        Clamp,
        RegionClamp,  // clamped to [min, max]

        RegionRepeat, // (texel & min) | max
    };
    // How the texel combines with the vertex colour.
    enum class TexFunction : uint8_t
    {
        Modulate,
        Decal,
        Highlight,
        Highlight2,
    };
    // A texture's combine rule (a native command's texture slot).

    struct TexMode
    {
        TexFunction function =  TexFunction::Modulate;
        bool textureAlpha = false; // the texel's alpha (else the vertex alpha)
    };
    // A target's texels read as a texture: the alpha the read gives.
    enum class TexAlpha : uint8_t
    {
        AsIs,
        Rgb24, // alpha = (black && blackClear) ? 0 : alpha0
        Rgba16, // alpha = bit 7 ? alpha1 : (black && blackClear) ? 0 : alpha0
    };
    struct Texturing
    {   
        bool on = false;
        uint16_t width = 1, height = 1; // texels (powers of two)
        TexFunction function = TexFunction::Modulate;
        bool textureAlpha = false; // the texel's alpha (else the vertex alpha)
        bool fixedUv =  false;      // vertices give texel coordinates (u, v in 1/16 texels), else s / q, t / q
        bool bilinear = false;
        Wrap wrapU = Wrap::Repeat, wrapV = Wrap::Repeat;
        uint16_t minU = 0, maxU = 0, minV = 0, maxV = 0;
        TexAlpha alphaMode = TexAlpha::AsIs; // target texels only

        uint8_t alpha0 = 0, alpha1 = 0;
        bool blackClear = false;
    };

    struct Rect

    {
        uint32_t x0 = 0, y0 = 0, x1 = 0, y1 = 0; // [x0, x1) x [y0, y1)
    };

    // The state of a batch of primitives (POD: compared with memcmp).
    struct DrawSetup
    {
        Primitive primitive = Primitive::Point;
        bool gouraud = false ;
        bool fog = false;
        uint32_t fogColor = 0; // R | G << 8 | B << 16   
        Format colorFormat = Format::Color32;
        uint32_t keepMask = 0;        // target bits a draw keeps (RGBA8 byte order)
        bool alphaHigh = false;       // alpha bit 7 set on every written pixel (not Color24)
        Format depthFormat = Format::Depth32;
        bool depthWrite = false;
        DepthTest depthTest = DepthTest::Always;
        AlphaTest alphaTest;
        TargetAlphaTest targetAlphaTest;
        Blend blend;
        Texturing texture;

    } ;

    // Vertex of a batch (target pixels; texel coordinates as the primitive kind says).
    struct Vertex
    {
        float x, y, depth; // depth: z / 2^32 (z the integer depth value)
        uint32_t color;    // R | G << 8 | B << 16 | A << 24
        float s, t, q, u, v, fog;
        float uvLo[2]{1, 1}, uvHi[2]{0, 0};
        uint32_t desc = 0;
    };

    // Where a batch's texels come from.
    enum class TexSource : uint8_t
    {
        None,
        Texture,    // `texture` (RGBA8, the texture's own size)
        Target,     // `target`'s texels at its scale
        TargetCopy, // a copy of the drawn target's `copyArea` made before the batch
    };

    struct NativeContext
    {
        uint32_t frame = 0;      // the colour buffer (a key of the exe: the same buffer, the same key)
        uint32_t color = 0;      // the colour target as bound (buffer, width, format; a key of the exe)
        uint32_t depth = 0;      // the depth target (a key of the exe)
        bool colorKnown = false; // colorFormat is one of the formats (else the target cannot be drawn)
        Format colorFormat = Format::Color32;
        Format depthFormat = Format::Depth32;
        uint32_t keepMask = 0;  // target bits a draw keeps (RGBA8 byte order)
        bool depthWrite = true ;
        bool depthOn =  false;   // depth test on (off: always passes, the depth target is not needed)
        DepthTest depthTest = DepthTest::Always;
        float offsetX = 0, offsetY = 0; // window coordinates minus these = target pixels
        Rect scissor;                   // target pixels
        Wrap wrapU = Wrap::Repeat, wrapV = Wrap::Repeat;
        bool bilinear =  false;  // magnified texels are filtered
        bool alphaHigh = false; // alpha bit 7 set on every written pixel
    };
    struct NativeEnv
    {
        NativeContext ctx[2];
        uint32_t fogColor = 0; // R | G << 8 | B << 16
    };
    // The largest depth value of a depth format.
    inline double depthMax(Format f) { return f == Format::Depth32 ? 4294967295.0 : f == Format::Depth24 ? 16777215.0 : 65535.0; } 
}
