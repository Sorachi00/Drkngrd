#pragma once
#define NOMINMAX
#include <d3d11.h>
#include <wrl/client.h>
#include <cstdint>
#include <vector>

namespace GSHwQualityFrame
{
    void latch(uint64_t vsyncTick);
    uint32_t antiAlias();
    uint32_t textureFilter(); // 0: PS2 (no mipmaps), else the maximum anisotropy
    bool deflicker() ;
    uint32_t shadows();
    uint32_t characters();
}

namespace GSHwNativeMips
{
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> create(ID3D11Device *d, uint32_t width, uint32_t height, const std::vector<uint32_t> &rgba, int alphaRef);
    ID3D11SamplerState *sampler(ID3D11Device *d, uint32_t level, bool clampU, bool clampV);
}
