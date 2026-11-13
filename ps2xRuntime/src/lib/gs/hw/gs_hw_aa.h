#pragma once
#define NOMINMAX
#include <d3d11.h>
#include <cstdint>
#include <memory>

class GSHwAntiAlias
{
  public:
    GSHwAntiAlias();
    ~GSHwAntiAlias();
    ID3D11Texture2D *apply(ID3D11Device *device, ID3D11DeviceContext *ctx, ID3D11Texture2D *image, uint32_t width, uint32_t height, uint32_t mode);

  private:
    struct Impl;
    std::unique_ptr<Impl> m;
};  
