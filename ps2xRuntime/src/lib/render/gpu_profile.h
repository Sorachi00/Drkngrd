#pragma once

#ifndef NOMINMAX
#define NOMINMAX
#endif

#include <d3d11.h>

namespace GpuProfile
{  
bool on();
void begin(const char *part);
void end();
void frameEnd(ID3D11Device *device, ID3D11DeviceContext *ctx);

struct Zone
{
    explicit Zone(const char *part) { begin(part); }
    ~Zone() { end(); }
    Zone(const Zone &) = delete;
    Zone &operator=(const Zone &) = delete;
};

}
