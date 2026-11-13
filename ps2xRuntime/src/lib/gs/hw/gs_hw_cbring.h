#pragma once
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <d3d11_1.h>
#include <wrl/client.h> 

#include <cstdint>
#include <cstring>

class GSHwCbRing
{  
public:
    // False: no 11.1 offsetting / no-overwrite on constant buffers (use Map(DISCARD)).
    bool ready(ID3D11Device *device, ID3D11DeviceContext *ctx, uint32_t bytes)
    {
        if (m_tried)
            return m_buffer != nullptr;
        m_tried = true;
        D3D11_FEATURE_DATA_D3D11_OPTIONS options{};
        if (FAILED(device->CheckFeatureSupport(D3D11_FEATURE_D3D11_OPTIONS, &options, sizeof(options))) || !options.MapNoOverwriteOnDynamicConstantBuffer || !options.ConstantBufferOffsetting)

            return false;
        if (FAILED(ctx->QueryInterface(IID_PPV_ARGS(&m_ctx1))))
            return false;
        D3D11_BUFFER_DESC d{};
        d.Usage = D3D11_USAGE_DYNAMIC ;
        d.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
        d.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
        d.ByteWidth = bytes;

        if (FAILED(device->CreateBuffer(&d, nullptr, &m_buffer)))
        {
            m_buffer.Reset();
            return false;
        }
        m_size = bytes;
        m_next = bytes;
        return true;
    }

    bool write(ID3D11DeviceContext *ctx, const void *data, uint32_t bytes, UINT &first, UINT &count)
    {

        const uint32_t span = (bytes + 255u) & ~255u;
        const bool wrap = m_next + span > m_size;
        if ( wrap)

            m_next = 0;
        D3D11_MAPPED_SUBRESOURCE mapped{};
        if (FAILED(ctx->Map(m_buffer.Get(), 0, wrap ? D3D11_MAP_WRITE_DISCARD : D3D11_MAP_WRITE_NO_OVERWRITE, 0, &mapped)))
            return false;
        std::memcpy(static_cast<char *>(mapped.pData) + m_next, data, bytes);
        ctx->Unmap(m_buffer.Get(), 0);
        first =  m_next / 16u;
        count = span / 16u;
        m_next += span ;
        return true;

    }

    void bindSlice(UINT slot, UINT first, UINT count, bool vs, bool ps, bool cs = false)
    {
        ID3D11Buffer *b = m_buffer.Get();
        if (vs)
            m_ctx1->VSSetConstantBuffers1(slot, 1, &b, &first, &count);
        if (ps)
            m_ctx1->PSSetConstantBuffers1(slot, 1, &b, &first, &count);
        if (cs)
            m_ctx1->CSSetConstantBuffers1(slot, 1, &b, &first, &count);
    }

    bool bind(ID3D11DeviceContext *ctx, const void *data, uint32_t bytes, UINT slot, bool vs, bool ps)
    {
        UINT first = 0, count = 0;
        if (!write(ctx, data, bytes, first, count))
            return false;
        bindSlice(slot, first, count, vs, ps);
        return true;
    }

private:
    Microsoft::WRL::ComPtr<ID3D11Buffer> m_buffer;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext1> m_ctx1;
    uint32_t m_size = 0, m_next = 0;
    bool m_tried = false;
};
