#include "dk2d/dk2d.h"
#include "game_overrides.h"
#include "ps2_runtime.h"
#include "ps2_runtime_macros.h"
#include "runtime/gs/gs_hw_quality.h"
#include "runtime/gs/render_cmd.h" 
#include "runtime/gs/gs_native_blob.h"
#include "runtime/ps2_det.h"
#include <cmath>
#include <cstdio>
#include <cstdlib>

#include <cstring>

void FUN_002838d0_0x2838d0(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime);

void frameRecorderPinAnchorRepeat(uint64_t id, uint32_t tagAddr, uint32_t tagWord);
bool dkStepB2();
void dkOwnState(const uint8_t *rdram, RenderCmd &cmd, uint32_t blobContext2);
void dkBTrackAnchor(const std::shared_ptr<RenderCmd> &cmd, uint32_t fn, uint32_t tagAddr);
void dkNativeAtTag(uint32_t tagAddr, std::shared_ptr<RenderCmd> cmd);
namespace dk_native_blob
{
    constexpr uint32_t kCloseReturn = 0x23543Cu; // FUN_00235278's call of FUN_002838d0
    constexpr uint32_t kSpr = 0x70000000u;       // FUN_002347d0's scratchpad block
    constexpr uint64_t kAdTag5 = 0x1000000000000005ull;

    struct Vec
    {
        float x, y, z, w;
    };

    float f32(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime, uint32_t a)
    {
        const uint32_t bits = READ32(a);

        float f;
        std::memcpy(&f, &bits, 4);
        return f;

    }
    Vec vec(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime, uint32_t a)
    {
        return {f32(rdram, ctx, runtime, a), f32(rdram, ctx, runtime, a + 4), f32(rdram, ctx, runtime, a + 8),
                f32(rdram, ctx, runtime, a + 12)};
    }
    // VOPMULA / VOPMSUB: a x b.
    Vec cross(const Vec &a, const Vec &b)
    {   
        return {a.y * b.z - b.y * a.z, a.z * b.x - b.z * a.x, a.x * b.y - b.x * a.y, 0};
    }
    // VMUL, VADDY.x, VADDZ.x, VRSQRT, VMULQ.xyz.
    Vec normalize(const Vec &v)
    {
        const float q = 1.0f / std::sqrt((v.x * v.x + v.y * v.y) + v.z * v.z);
        return {v.x * q, v.y * q, v.z * q, v.w};
    }
    // VMULAx, VMADDAy, VMADDAz, VMADDw: c0 * v.x + c1 * v.y + c2 * v.z + c3 * v.w.
    Vec mul(const Vec c[4], const Vec &v)
    {
        auto row = [&](float Vec::*e) { return ((c[0].*e * v.x + c[1].*e * v.y) + c[2].*e * v.z) + c[3].*e * v.w; };
        return {row(&Vec::x), row(&Vec::y), row(&Vec::z), row(&Vec::w)};
    }
    // VFTOI4: round towards zero, saturated.
    int32_t ftoi4(float f)
    {
        const double v = double(f) * 16.0;
        return v >= 2147483647.0 ? INT32_MAX : v <= -2147483648.0 ? INT32_MIN : int32_t(v);
    }

    bool buildQuads(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime, uint32_t list, GSNativeBlobParams &p)
    {
        const int32_t count = int32_t(READ32(list));   
        if (count <= 0 || count > 256)
            return false;
        Vec m[4], corner[4];
        float uv[4][2];
        for (int i = 0; i < 4; ++i)
        {
            m[i] = vec(rdram, ctx, runtime, kSpr + 16u * i);
            corner[i] =  vec(rdram, ctx, runtime, kSpr + 0x270u + 16u * i);
            uv[i][0] = f32(rdram, ctx, runtime, kSpr + 0x2B0u + 8u * i);
            uv[i][1] = f32(rdram, ctx, runtime, kSpr + 0x2B4u + 8u * i);
        }
        const int32_t x0 = int32_t(READ32(kSpr + 0x50u)), y0 = int32_t(READ32(kSpr + 0x54u)),
                      x1 = int32_t(READ32(kSpr + 0x58u)), y1 = int32_t(READ32(kSpr + 0x5Cu));
        for (int32_t e = 0; e < count; ++e)
        {
            const uint32_t a = list + 0x10u + 0x20u * uint32_t(e);
            const Vec pos = vec(rdram, ctx, runtime, a), nrm = vec(rdram, ctx, runtime, a + 16);
            const float size = pos.w;
            // FUN_00234688(0, ...): the reference direction (cos 0, sin 0, 0).
            const Vec n = normalize(nrm);
            const Vec t = normalize(cross(n, Vec{1, 0, 0, 0}));
            const Vec A = cross(n, t);
            const Vec B = n;
            const Vec C = cross(B, A);

            const Vec axes[4] = {{C.x * size, C.y * size, C.z * size, 0},
                                {A.x * size, A.y * size, A.z * size, 0},
                                {B.x * size, B.y * size, B.z * size, 0},
                                {pos.x, pos.y, pos.z, 1}};
            Vec s[4];
            for (int i = 0; i < 4; ++i)
                s[i] = mul(m, axes[i]);
            GSNativeBlobQuad quad{};

            uint32_t outside = ~0u;
            bool culled = false;
            for (int k = 0; k < 4 && !culled; ++k)
            {
                const Vec c = mul(s, corner[k]);

                const float q = 1.0f / c.w;
                const int32_t xi = ftoi4(c.x * q), yi = ftoi4(c.y * q), zi = ftoi4(c.z * q), wi = ftoi4(c.w);
                if ((uint32_t(xi) >> 16) || (uint32_t(yi) >> 16) || zi < 0 || wi < 0)
                {
                    culled = true;
                    break;
                }

                outside &= (x0 > xi ? 1u : 0u) | (xi > x1 ? 2u : 0u) | (y0 > yi ? 4u : 0u) | (yi > y1 ? 8u : 0u);
                quad.pos[k][0] = c.x;
                quad.pos[k][1] = c.y;
                quad.pos[k][2] = c.z;
                quad.pos[k][3] = c.w;
                quad.z[k] = (uint32_t(zi) >> 4) + 16u;
                quad.uv[k][0] = uv[k][0];  
                quad.uv[k][1] = uv[k][1];
            }
            if (culled || outside)
                continue;
            quad.rgba = READ32(a + 0x1Cu );
            p.quads.push_back(quad);
        }
        return true;
    }

    bool sameQuads(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime, uint32_t q, const GSNativeBlobParams &p)
    {
        for (size_t i = 0; i < p.quads.size(); ++i, q += 0x80u)
        {
            const GSNativeBlobQuad &quad = p.quads[i];
            if (READ64(q) != 0xE400000000000001ull)
                return false;
            for (int k = 0; k < 4; ++k)

            {
                const uint32_t v = q + 0x20u + 24u * k;   
                const uint64_t xyz = READ64(v + 16 );
                if (uint32_t(READ64(v + 8)) != quad.rgba)
                    return false;
                const float w = quad.pos[k][3] ;
                const int32_t x = ftoi4(quad.pos[k][0] * (1.0f / w)) & 0xFFFF, y = ftoi4(quad.pos[k][1] * (1.0f / w)) & 0xFFFF;
                if (std::abs(int32_t(xyz & 0xFFFF) - x) > 2 || std::abs(int32_t((xyz >> 16) & 0xFFFF) - y) > 2 || std::abs(int64_t(xyz >> 32) - int64_t(quad.z[k])) > 2)

                    return false;
            }
        }
        return true;
    }

    void stepBState(uint8_t *rdram, uint32_t start, uint32_t postAt, bool quads, uint64_t prim, uint64_t tex0)
    {
        auto pre = std::make_shared<Native2D>(), post = std::make_shared<Native2D>();
        pre->function = post->function = 0x235278u;
        uint32_t texture;
        uint64_t zbuf;
        std::memcpy(&texture, rdram + 0x466CCCu, 4);
        std::memcpy(&zbuf, rdram + 0x4F6BB0u, 8);
        bool ok;
        {
            dk2d::Draw2D p(*pre), q(*post);
            if (quads)
            {
                q.primitive(prim);
                q.texture(dk2d::kCtx2, tex0);
            }
            ok =  dk2d::uploadChain(rdram, texture, p) && dk2d::stateChain(rdram, 0x4F6B80u, q);
            p.textureFlush();
            p.depth(dk2d::kCtx2, zbuf | 0x100000000ull); // (ZMSK)
            p.tests(dk2d::kCtx2, 0x70000);
            p.filter(dk2d::kCtx2, 0x60);
            p.blend(dk2d::kCtx2, 0x42);
        }
        if (!ok)
        {
            std::fprintf(stderr, "[step-b] blob shadow t%llu: texture or state chain not handled%c", (unsigned long long)PS2Det::vsyncTick(), 10);
            return;
        }
        dkNativeAtTag(start, RenderExec::makeNative2D(std::move(pre))) ;
        dkNativeAtTag(postAt, RenderExec::makeNative2D(std::move(post)));
    }

    void dkBlobClose(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        const uint32_t start = GPR_U32(ctx, 4), end = GPR_U32(ctx, 5);

        const uint32_t quads = start + 0x70u; // after the tag and the 5 A+D writes
        const bool blobPacket = GPR_U32(ctx, 31) == kCloseReturn && READ64(start + 0x10u) == kAdTag5 && READ64(start + 0x18u) == 0xEull;
        auto gamePacket = [&](bool hasQuads) {
            const uint64_t lastPrim = hasQuads ? READ64(end - 0x80u + 0x10u) : 0, lastTex0 = hasQuads ? READ64(end - 0x80u + 0x18u) : 0;
            const uint64_t unwinds = ps2_game_overrides::guestUnwindCount();
            FUN_002838d0_0x2838d0(rdram, ctx, runtime);
            if (blobPacket && dkStepB2() && ps2_game_overrides::guestUnwindCount() == unwinds)
                stepBState(rdram, start, GPR_U32(ctx, 2), hasQuads, lastPrim, lastTex0);
        };
        if (!blobPacket || end <= quads || (end - quads) % 0x80u)
        {
            gamePacket(false);
            return;
        }
        const uint32_t last = end - 0x80u;

        const uint64_t prim = READ64(last + 0x10u), tex0 = READ64(last + 0x18u);
        const bool realtime = GSHwQuality::shadows() == GSHwQuality::kShadowsRealtime;
        std::shared_ptr<RenderCmd> cmd;
        if (!realtime)
        {
            GSNativeBlobParams p;
            const uint32_t list = GPR_U32(ctx, 21); // s5: FUN_00235278's list
            if (!buildQuads(rdram, ctx, runtime, list, p) || p.quads.size() != (end - quads) / 0x80u || !sameQuads(rdram, ctx, runtime, quads, p))
            {
                if (dkStepB2())
                    dk2d::fallback(rdram, *ctx, 0x235278u, "blob-game", {}, {});

                gamePacket(true); // the game draws this frame's shadows
                return;
            }  
            p.tex0 = tex0;
            cmd =  NativeDraw::makeBlobDraw(std::move(p));
        }
        SET_GPR_U32(ctx, 5, quads);
        const uint64_t unwinds = ps2_game_overrides::guestUnwindCount();
        FUN_002838d0_0x2838d0(rdram, ctx, runtime);
        if (ps2_game_overrides::guestUnwindCount() != unwinds || GPR_U32(ctx, 2) != quads)
            return; // (a packet of up to 0xFFFF qwords is closed without a scheduler checkpoint)
        if (dkStepB2())  
            stepBState(rdram, start, quads + 64u, true, prim, tex0);
        if ( cmd)
        {
            dkOwnState(rdram, *cmd, 1);
            dkBTrackAnchor(cmd, 0x235278u, quads);
        }
        const bool lists = dkStepB2();
        const uint64_t id =  cmd ? FrameRecorder::record(std::move(cmd)) : 0;
        if (id && !lists)
            frameRecorderPinAnchorRepeat(id, quads, 0x10000003u);
        WRITE64(quads, 0x10000003ull);                                   // CNT, 3 qwords
        WRITE32(quads + 8u, id && !lists ? FrameRecorder::anchorWord0(id) : 0u);
        WRITE32(quads + 12u, 0x50000003u);                               // VIF DIRECT 3
        WRITE64(quads + 16u, 0x1000000000000002ull);                     // GIF tag: NLOOP 2, PACKED, NREG 1   
        WRITE64(quads + 24u, 0xEull);                                    // REGS: A+D
        WRITE64(quads + 32u, prim);
        WRITE64(quads + 40u, 0x00ull); // PRIM
        WRITE64(quads + 48u, tex0);  
        WRITE64(quads + 56u, 0x07ull); // TEX0_2
        SET_GPR_U32(ctx, 2, quads + 64u);
    }
}

void applyDrakengardNativeBlob(PS2Runtime &runtime)
{
    runtime.replaceFunction(0x2838D0u, &dk_native_blob::dkBlobClose) ;
}
