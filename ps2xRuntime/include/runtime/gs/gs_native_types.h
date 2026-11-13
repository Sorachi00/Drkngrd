#pragma once
#include <cstdint>

struct GSNativeSkinVertex
{
    int16_t pos[4];
    int16_t nrm[4];
    uint8_t weight[4]; // bone weights (not normalised; the divide by w cancels the sum)
    uint8_t bone[4];
    uint16_t uv[2];    // GS UV units (texel * 16)
};
static_assert(sizeof(GSNativeSkinVertex) == 28);

struct GSNativeMapVertex
{
    int16_t pos[4];   // x, y, z (block units * 16), 0
    int16_t uv[2];    // texture coordinates * 4096   
    int16_t uv2[2];   // MAP2 second layer coordinates * 4096
    uint8_t rgb[4];   // vertex colour; [3] = PRIM bits of the strip's GIF tag (TME 0x10, FGE 0x20, ABE 0x40)
    uint8_t rgba2[4]; // MAP2 second layer colour
    float plane[4];   // strip drawn if plane.xyz . camera + plane.w >= 0 ((0, 0, 0, 1): always)
};
static_assert(sizeof(GSNativeMapVertex) == 40);

struct GSNativeMapGroup
{
    enum Kind : uint32_t
    {
        Map,    // small MAP: alpha 0x80
        Map2,   // small MAP2: + second pass with uv2 / rgba2 and texture texIndex2
        BigMap, // big MAP: alpha from the w ramp
        BigMap2, // big MAP2 (batch type bit 8): big MAP with alpha 0x80 + the MAP2 second pass
    } ;
    uint32_t firstIndex = 0, indexCount = 0;
    Kind kind = Map;
    uint32_t texIndex = 0, texIndex2 = 0; // TEX0 list entries of pass 1 / pass 2
};

struct GSNativeSkyVertex
{
    int16_t pos[4];   // grid x, height, grid z, w (VIF ROW not added)
    uint16_t uv[2];   // texture coordinates * 4096
    uint8_t rgba[4];
    uint8_t prim[4];  // [0] PRIM bits of the strip's GIF tag (TME 0x10, FGE 0x20, ABE 0x40)
};
static_assert(sizeof(GSNativeSkyVertex) == 20);

struct GSNativeBlobQuad
{
    float pos[4][4]; // corners: GS window x, y, z times w, and w
    uint32_t z[4];   // GS Z of the corners: FTOI4(z / w) >> 4, + 16
    float uv[4][2];  // texture coordinates (0..1)
    uint32_t rgba;   // vertex colour, R in the low byte
};
