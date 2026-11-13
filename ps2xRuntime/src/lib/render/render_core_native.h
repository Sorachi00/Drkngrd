#pragma once
#include "render_core.h"

#define NOMINMAX
#include <d3d11_1.h>
#include <memory>

struct GSNativeView;

namespace rdraw
{
    Core &dllCore();
    ID3D11Device *coreDevice();
    ID3D11DeviceContext *coreContext();
    const GSNativeView &coreNativeView();
    ID3D11ShaderResourceView *coreTextureView(TextureId texture);
    ID3D11ShaderResourceView *coreTargetAt1x(TargetId target, uint32_t w, uint32_t h, uint64_t serial);
}
