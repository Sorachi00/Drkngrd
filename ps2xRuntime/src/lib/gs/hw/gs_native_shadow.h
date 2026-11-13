#pragma once
#include "runtime/gs/render_cmd.h"
#define NOMINMAX   
#include <d3d11.h>
#include <cstdint>
#include <vector>

class GSNativeShadowFrame
{
  public:
    struct Reference
    {
        int priority = -1; // 2: map block with the camera matrix, 1: sky terrain   
        uint32_t frameKey = 0;
        double matrix[4][4]{}; // world -> GS window, columns
        double fogFar = 0;     // view w at which fog is complete (0: unknown)
        double rect[4]{};      // drawn window rectangle x0, y0, x1, y1 (GS window pixels)
    };
    struct Caster
    {  

        RenderCmd *draw = nullptr ;
        rdraw::NativeEnv env{};
        uint32_t frameKey = 0;
        double localToWindow[4][4]{};
        float boundsMin[3]{}, boundsMax[3]{};
        bool isStatic = false;
        bool ownCamera = false;
        uint64_t identity = 0;
        std::shared_ptr<RenderCmd> owner;     // the command (kept for static casters out of view)
    };
    struct Light  
    {
        uint32_t frameKey = 0;
        double localToWindow[4][4]{};
        double dir[3]{};     // towards the light, in local space (N.L > 0: lit)
        double key = 0;
        double ambient = 0;
    };   

    explicit GSNativeShadowFrame( ID3D11Device *device) : m_device(device) {}
    ID3D11Device *device() const { return m_device; }

    void reference(const Reference &r)
    {
        if (r.priority > m_reference.priority)
            m_reference = r;
        m_references.push_back(r);
    }
    void caster(const Caster &c) { m_casters.push_back(c); }
    size_t casterCount() const { return m_casters.size(); }
    void ownerFrom(size_t first, const std::shared_ptr<RenderCmd> &owner)
    {
        for (size_t i = first; i < m_casters.size(); ++i)
            m_casters[i].owner = owner;   
    }
    void light(const Light &l) { m_lights.push_back(l ); }   

    const Reference &reference() const { return m_reference; }
    // Every reference of the frame (its draws can come from two game frames: two cameras).
    const std::vector<Reference> &references() const { return m_references; }
    const std::vector<Caster> &casters() const { return m_casters; }
    const std::vector<Light> &lights() const { return m_lights; }

  private:
    ID3D11Device *m_device;
    Reference m_reference;
    std::vector<Reference> m_references;
    std::vector<Caster> m_casters;
    std::vector<Light> m_lights;
};

// Constant buffer b4 of the caster shaders (render/native_draw.hlsl cbuffer ShadowCast).
struct GSNativeShadowCastConstants
{  
    float matrix[4][4]; // local -> cascade clip, columns
    float origin[4];    // map: block origin / 16

    float row[4];       // sky: VIF ROW x, 0, z, 0
    float scale[4];     // sky: VU1 16
    uint32_t tex[4];    // map: texture width, height; z: 1 = alpha test; w: texel alpha > w passes
    float alpha[4];     // model: x texel alpha scale, y reference (pass: alpha * x >= y); zw: UV scale
};

struct GSNativeShadowCastContext
{
    ID3D11Device *device = nullptr;
    ID3D11DeviceContext *context = nullptr;
    bool firstCascade = false;

    ID3D11VertexShader *mapVS =  nullptr, *skyVS = nullptr, *modelVS = nullptr;
    ID3D11PixelShader *mapPS = nullptr, *modelPS = nullptr; // alpha test (null PS: depth only)
    ID3D11InputLayout *mapLayout = nullptr, *skyLayout = nullptr, *modelLayout = nullptr;
    ID3D11Buffer *constants = nullptr;
    ID3D11SamplerState *sampler = nullptr;
    double clipFromWorld[4][4]{};
    double worldFromWindow[4][4]{};

    void matrixFor(const float localToWindow[4][4], float out[4][4]) const;
    void upload(const GSNativeShadowCastConstants &k) const;
};

namespace GSNativeShadow
{
    void frame(ID3D11Device *device, ID3D11DeviceContext *context, const RenderExec::FrameItem *items, size_t count);
    bool wanted();

    bool receiver(const rdraw::NativeContext &c, const float localToWindow[4][4], float out[4][4], bool ownCamera = false);
    bool windowToLight(const rdraw::NativeContext &c, float out[4][4]);
    void bindReceiver(ID3D11DeviceContext *context);
    void unbindReceiver(ID3D11DeviceContext *context);

    inline double brightness(const float c[4]) { return double(c[0]) + double(c[1]) + double(c[2]); }
}
