#pragma once
#include "runtime/render/rdraw.h"
#define NOMINMAX
#include <d3d11_1.h>
#include <cstdint>

struct GSNativeView
{
    uint32_t width = 0, height = 0;
    float scaleX = 1, scaleY = 1;     // texels per pixel (not whole with dynamic resolution)
    ID3D11RenderTargetView *rtv = nullptr;
    ID3D11DepthStencilView *dsv = nullptr;
};

struct GSNativeTarget
{
    virtual ID3D11Device *device() = 0;
    virtual ID3D11DeviceContext *context() = 0;

    virtual bool bind(const rdraw::NativeContext &c, bool depth, GSNativeView &view) = 0;

    virtual void drawn(bool depthWritten) = 0;
    virtual ID3D11ShaderResourceView *texture(uint32_t context, uint32_t slot, uint32_t &width, uint32_t &height) = 0;

  protected:

    ~GSNativeTarget() = default;
};

void nativeWorldDrawn(uint32_t frame);
// 3D models drawn into `frame`: keeps the world on screen if it is its buffer.
void nativeModelsDrawn(uint32_t frame);
