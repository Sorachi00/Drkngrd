// Drakengard (SLES_523.22) specific hooks.
#include "runtime/gs/gs_frontend.h"
#include "game_overrides.h"   

#include "runtime/gs/gs_state_values.h"
#include "ps2_runtime.h"
#include "ps2_runtime_macros.h"
#include "runtime/ee_scheduler.h"
#include "runtime/ps2_perf.h"
#include "ps2_runtime_hooks.h"
#include "runtime/ps2_det.h"
#include "runtime/ps2_graphics_thread.h"
#include "runtime/ps2_video_timing.h"
#include "runtime/gs/render_cmd.h"
#include "runtime/gs/gs_native_model.h"

#include "runtime/gs/gs_hw_quality.h"
#include "runtime/gs/gs_perf.h"
#include "drakengard_loads.h"
#include <algorithm>
#include <atomic>

#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <unordered_map>  
#include <vector>
#include <utility>

void FUN_002983e8_0x2983e8(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime);
void FUN_0012e328_0x12e328(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime);
void FUN_002e80b4_0x2e80b4(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime);
void FUN_0014b61c_0x14b61c(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime);
void applyDrakengardNativeMap(PS2Runtime &runtime);
void applyDrakengardNativeSky(PS2Runtime &runtime);
void applyDrakengardNativeBlob(PS2Runtime &runtime);
void applyDrakengardDrawOwners(PS2Runtime &runtime);
void applyDrakengardNativeFont(PS2Runtime &runtime);
void applyDrakengardNativeLoad(PS2Runtime &runtime);
void applyDrakengardSquadSort(PS2Runtime &runtime);
void FUN_003157c4_0x3157c4(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime);
void FUN_00315874_0x315874(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime) ;
void FUN_00315978_0x315978(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime);

void FUN_0027f49c_0x27f49c(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime);

namespace
{
    // The native movie picture goes to the renderer, not through guest RAM.
    bool dkMoviePicture(std::shared_ptr<const std::vector<uint8_t>> rgba, uint32_t width, uint32_t height)
    {
        if (rgba && !RenderExec::directMovies())
            return false;
        FrameRecorder::insertNow(RenderExec::makeMoviePicture(std::move(rgba), width, height));
        return true;
    }
}

namespace
{
    std::unordered_map<uint32_t, uint32_t> g_packetBufferBytes;

    void dkPacketBuffers(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        const uint32_t bytes = GPR_U32(ctx, 7) * 16u;
        g_packetBufferBytes[GPR_U32(ctx, 5) & PS2_RAM_MASK] = bytes;
        g_packetBufferBytes[GPR_U32(ctx, 6) & PS2_RAM_MASK] =  bytes;  
        FUN_0027f49c_0x27f49c(rdram, ctx, runtime);
    }
}

bool dkPacketHeapRoom(uint8_t *rdram, uint32_t bytes)
{
    uint32_t start, heap;
    std::memcpy(&start, rdram + 0x4F9250u, 4);
    std::memcpy(&heap, rdram + 0x4F9254u, 4);

    start &= PS2_RAM_MASK;
    heap &= PS2_RAM_MASK;
    const auto it = g_packetBufferBytes.find(start);
    if (it == g_packetBufferBytes.end())
        return true;
    if (heap >= start && heap + bytes <= start + it->second)
        return true;
    static uint32_t s_full = 0;
    if (s_full++ < 4)
        std::fprintf(stderr, "[packet-heap] full: buffer %08X size %X heap %08X +%X\n", start, it->second, heap, bytes);
    return false;

}

std::unique_ptr<GS> makeRenderRecorder();
static const bool g_dkNativeRenderer = ( gsSetFrontendFactory(&makeRenderRecorder), true);

void frameRecorderPinAnchor(uint64_t id, uint32_t tagAddr);
bool dkStepB2();
bool dkAppendAnchor(uint8_t *rdram, uint32_t layer, std::shared_ptr<RenderCmd> cmd)
{
    if (dkStepB2())
    {
        FrameRecorder::record(std::move(cmd));
        return false;
    }
    constexpr uint32_t kPacketHeap = 0x4F9254u, kOtTails = 0x4F9258u;
    if (!dkPacketHeapRoom(rdram, 0x20u))
        return false;
    uint32_t heap, tail;
    std::memcpy(&heap, rdram + kPacketHeap, 4);
    std::memcpy(&tail, rdram + kOtTails + 4u * layer, 4);
    const uint64_t id = FrameRecorder::record(std::move(cmd));  
    frameRecorderPinAnchor(id, heap);
    const uint64_t anchor[4] = {0x10000000ull, // CNT, no data
                                uint64_t(FrameRecorder::anchorWord1(id)) << 32 | FrameRecorder::anchorWord0(id),
                                0, 0}; // the layer's new tail
    const uint64_t link[2] = {uint64_t(heap & 0x0FFFFFFFu) << 32 | 0x20000000u, 0}; // old tail: NEXT to the anchor, VIF NOP, NOP
    std::memcpy(rdram + (heap & PS2_RAM_MASK), anchor, sizeof anchor);
    std::memcpy(rdram + (tail & PS2_RAM_MASK), link, sizeof link);
    const uint32_t newTail = heap + 0x10u, newHeap = heap + 0x20u;
    std::memcpy(rdram + kOtTails + 4u * layer, &newTail, 4);
    std::memcpy(rdram + kPacketHeap, &newHeap, 4);
    return true;
}

bool dkOffscreenPass();
namespace
{
    uint32_t g_sceneFog = 0;
    struct PassTarget
    {
        bool on = false;
        uint64_t frame = 0, zbuf = 0, xyoffset = 0, scissor = 0;
    } g_pass;
}
void dkSetSceneFog(uint64_t fogcol)

{  
    g_sceneFog = uint32_t(fogcol & 0xFFFFFFu);

}
uint32_t dkSceneFog()
{  
    return g_sceneFog; 
}
void dkSetPassTarget(bool on, uint64_t frame, uint64_t zbuf, uint64_t xyoffset, uint64_t scissor)
{
    g_pass = PassTarget{on, frame, zbuf, xyoffset, scissor};
}
void dkOwnState(const uint8_t *rdram, RenderCmd &cmd, uint32_t blobContext2)
{
    if (cmd.ownState() || (dkOffscreenPass() && !g_pass.on))
        return;
    auto s = std::make_shared<NativeDraws::State>();
    for (int i = 0; i < 2; ++i)
    {
        const uint32_t base = i ? 0x4F69D8u : 0x4F69A0u;
        auto q =  [&](uint32_t o) {
            uint64_t v; 
            std::memcpy(&v, rdram + base + o, 8 );
            return v;
        };

        GSContext &c = s->values.ctx[i];
        c.zbuf = GSStateValues::zbuf(q(0x08));
        c.frame = GSStateValues::frame(q(0x10));
        c.scissor = GSStateValues::scissor(q(0x18)) ;
        c.xyoffset = GSStateValues::xyoffset(q(0x20));
        s->set[i] = NativeDraws::kFrame | NativeDraws::kZbuf | NativeDraws::kScissor | NativeDraws::kXyoffset;
    }
    if (g_pass.on )
    {
        // Inside the pass: context 2 is its target.
        GSContext &c = s->values.ctx[1];
        c.frame = GSStateValues::frame(g_pass.frame);
        c.zbuf = GSStateValues::zbuf(g_pass.zbuf);
        c.xyoffset = GSStateValues::xyoffset(g_pass.xyoffset) ;
        c.scissor = GSStateValues::scissor(g_pass.scissor);
    }
    // TEXA: the screen draw environment's (0x4F6960).
    {
        uint64_t texa;  
        std::memcpy(&texa, rdram + 0x4F6960u, 8);
        s->values.texa = GSStateValues::texa(texa);
        s->set[2] |= NativeDraws::kTexa;
    }
    s->values.fogcol = g_sceneFog;
    s->set[2] |= NativeDraws::kFogcol;
    if (blobContext2 )
    {
        GSContext &c = s->values.ctx[1];
        c.zbuf.zmask = true;
        c.test = 0x70000;  
        c.tex1 = 0x60;
        c.fba = 0; // (the GS state chain 0x4F6B80 the frame's draws restore)
        s->set[1] |= NativeDraws::kTest | NativeDraws::kTex1 | NativeDraws::kFba;
    }
    cmd.setOwnState(std::move(s));
}

void frameRecorderRecordAt(std::shared_ptr<RenderCmd> cmd, uint32_t tagAddr);
void dkBListAdd(uint32_t layer, const std::shared_ptr<RenderCmd> &cmd, uint32_t tailAddr);
void dkAppendNative(uint8_t *rdram, uint32_t layer, std::shared_ptr<RenderCmd> cmd) 
{
    if ( cmd)
        dkOwnState(rdram, *cmd, 0);
    {
        uint32_t tail;
        std::memcpy(&tail, rdram + 0x4F9258u + 4u * layer, 4);
        dkBListAdd(layer, cmd, tail);
    }

    if (dkStepB2())
    {
        FrameRecorder::record(std::move(cmd));
        return;
    }
    constexpr uint32_t kOtTails = 0x4F9258u;

    static const bool anchors = [] {
        const char *v = std::getenv("PS2_DK_ANCHORS");
        return v && std::strcmp(v, "0") != 0;
    }();
    if (anchors)
    {
        dkAppendAnchor(rdram, layer, std::move(cmd));
        return;
    }
    uint32_t tail;
    std::memcpy(&tail, rdram + kOtTails + 4u * layer, 4);
    frameRecorderRecordAt(std::move(cmd), tail);
}

namespace
{
    void dkPollVblankFlag(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        ctx->pc = 0x2800E0u;
        const uint32_t flag = READ32(ADD32(GPR_U32(ctx, 4), 0));
        SET_GPR_U64(ctx, 2, flag == 0u ? 1u : 0u);
        PS2Perf::spinWait(flag == 0u);
        if (flag == 0u)
            runtime->eeScheduler().skipIdleToNextDeadline();
        ctx->branch_pc = 0x2800E4u;

        ctx->pc = GPR_U32(ctx, 31);
    }

    float guestFloat(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime, uint32_t address) 
    {
        const uint32_t bits = READ32(address);
        float value;
        std::memcpy(&value, &bits, 4);
        return value;  
    }

    constexpr uint32_t kPacketHeap = 0x4F9254u, kOtTails = 0x4F9258u;

    constexpr uint32_t kPlainMeshMask = 0x5BCu;
    constexpr uint32_t kEnvMeshMask = 0x5B0u;
    constexpr uint32_t kOpaqueLayer = 0x571468u, kBlendLayer = 0x57146Cu, kVu0Data = 0x11004000u;

    struct GuestRam
    {
        const uint8_t *rdram;
        bool ok(uint32_t a, uint32_t bytes ) const
        {
            const uint32_t p = a & 0x1FFFFFFFu;  
            return p < PS2_RAM_SIZE && bytes <= PS2_RAM_SIZE - p;
        }
        const uint8_t *at(uint32_t a) const { return rdram + (a & 0x1FFFFFFFu); }
        uint32_t u32(uint32_t a) const
        {
            uint32_t v;
            std::memcpy(&v, at(a), 4);
            return v;
        }
        uint16_t u16(uint32_t a) const
        {
            uint16_t v;
            std::memcpy(&v, at(a), 2);
            return v;
        }
        uint64_t u64(uint32_t a) const
        {
            uint64_t v;
            std::memcpy(&v, at(a), 8);
            return v;
        }
        uint64_t hash(uint32_t a, uint32_t bytes) const  
        {
            uint64_t h = 1469598103934665603ull;
            if (!ok(a, bytes))

                return h;
            for (const uint8_t *p = at(a), *e = p + bytes; p < e; ++p)
                h = (h ^ *p) * 1099511628211ull;

            return h;
        }
    };

    bool chainImage(const GuestRam &m, uint32_t chain, uint32_t base, bool relocated, uint32_t &w, uint32_t &h,

                    std::vector<uint8_t> &data)
    {
        uint32_t a = chain;
        for (int tags = 0; tags < 64; ++tags)
        {
            if(!m.ok(a, 16))
                return false;
            const uint64_t tag = m.u64(a);
            const uint32_t qwc = uint32_t(tag & 0xFFFFu), id = uint32_t(tag >> 28) & 7u;  
            uint32_t src = a + 16;  

            if (id == 0 || id == 3 || id == 4) // REFE, REF, REFS: data elsewhere

                src = uint32_t(tag >> 32) & 0x7FFFFFFFu, src += relocated ? 0u : base;
            const uint32_t end = src + qwc * 16u;
            if(!m.ok(src, qwc * 16u))
                return false;
            for (uint32_t p = src; p + 16 <= end;)
            {
                const uint64_t gif = m.u64(p);
                const uint32_t nloop = uint32_t(gif & 0x7FFFu), flg = uint32_t(gif >> 58) & 3u;
                const uint32_t nreg = uint32_t(gif >> 60) ? uint32_t(gif >> 60) : 16u;
                p += 16;   
                if (flg == 0)
                {
                    for (uint32_t i = 0; i < nloop * nreg && p + 16 <= end; ++i, p += 16)
                        if ((m.u64(p + 8) & 0xFF) == 0x52) // TRXREG
                        {
                            const uint64_t v = m.u64(p);
                            w = uint32_t(v & 0xFFF);
                            h = uint32_t(v >> 32) & 0xFFF;
                        }
                }
                else if (flg == 2)
                {
                    const uint32_t bytes = std::min( nloop * 16u, end - p);
                    data.insert(data.end(), m.at(p), m.at(p) + bytes);
                    p += bytes;
                }
                else
                    break;
            }
            if (id == 0 || id == 6 || id == 7) // REFE, RET, END
                return true;

            a = id == 1 ? end : a + 16; // CNT continues after its data
        }  
        return false;
    }

    std::shared_ptr<GSNativeTexture> decodeTexture(const GuestRam &m, uint32_t T, uint64_t &tex0)
    {
        if (!m.ok(T, 0x20))
            return nullptr;
        const uint32_t desc = T + m.u32(T + 0x10);
        if (!m.ok(desc, 0x28))
            return nullptr;
        tex0 = m.u64(desc + 0x18);
        const uint32_t psm = uint32_t(tex0 >> 20) & 0x3F, cpsm = uint32_t(tex0 >> 51) & 0xF;
        const uint32_t tw = 1u << (uint32_t(tex0 >> 26) & 15), th = 1u << (uint32_t(tex0 >> 30) & 15);

        if ((psm != 0x13 && psm != 0x14 && psm != 0x00) || (psm != 0x00 && cpsm != 0) || tw > 1024 || th > 1024)
            return nullptr;
        const bool relocated = m.u32(T + 0x1C) == 1 ;
        uint32_t w = 0, h = 0; 
        std::vector<uint8_t> image;
        if (!chainImage(m, T + m.u32(desc) + 0x30, T, relocated, w, h, image) || !w || !h) 
            return nullptr;
        std::vector<uint32_t> clut(256, 0);
        if (psm != 0x00)
        {
            uint32_t cw = 0, ch = 0;
            std::vector<uint8_t> raw;
            const uint32_t clutDesc = T + m.u32(T + 0x14);
            if(!m.ok(clutDesc, 4) || !chainImage(m, T + m.u32(clutDesc) + 0x30, T, relocated, cw, ch, raw) )
                return nullptr;
            const uint32_t entries = std::min<uint32_t>(uint32_t(raw.size() / 4), 256);   
            for (uint32_t i = 0; i < 256; ++i)
            {
                // CSM1 order for 8-bit indices: bits 3 and 4 swapped.
                const uint32_t k = psm == 0x13 ? ((i & 0xE7u) | ((i & 8u) << 1) | ((i & 16u) >> 1)) : i;
                if (k < entries)
                    std::memcpy(&clut[i], raw.data() + k * 4, 4);
            } 
        }
        auto tex = std::make_shared<GSNativeTexture>();
        tex->width = tw;
        tex->height = th;
        tex->rgba.assign(size_t(tw) * th, 0 );
        const uint32_t bpp = psm == 0x13 ? 8 : psm == 0x14 ? 4 : 32;
        for (uint32_t y = 0; y < std::min(h, th); ++y)
            for ( uint32_t x = 0; x < std::min(w, tw); ++x)
            {
                const size_t i =  size_t(y) * w + x;
                uint32_t texel = 0;
                if (bpp == 8 && i < image.size())
                    texel = clut[image[i]];
                else if (bpp == 4 && i / 2 < image.size())
                    texel = clut[(image[i / 2] >> ((i & 1) * 4)) & 15];
                else if (bpp == 32 && i * 4 + 4 <= image.size())  
                    std::memcpy(&texel, image.data() + i * 4, 4) ;
                tex->rgba[size_t(y) * tw + x] = texel;
            }
        return tex;
    }

    struct NativeMeshEntry
    {
        uint64_t check = 0;
        std::shared_ptr<const GSNativeMesh> mesh; // null: draw with the game's code

        uint32_t bones = 0;                       // palette entries used
    };
    struct TextureEntry
    {
        uint64_t check = 0;
        std::shared_ptr<GSNativeTexture> texture;
        uint64_t tex0 = 0;
    };

    std::shared_ptr<GSNativeTexture> nativeTexture(const GuestRam &m, uint32_t T, uint64_t &tex0)
    {
        static std::unordered_map<uint32_t, TextureEntry> cache;
        static size_t loadsSeen = 0;
        dk_loads::dropLoaded(cache, loadsSeen, [](const auto &e) { return e.first; });
        const uint64_t check = m.hash(T, 0x20) ^ (m.ok(T, 0x20) ? m.hash(T + m.u32(T + 0x10), 0x28) * 31 : 0);
        TextureEntry &e = cache[T];
        if (e.check != check || !e.texture)
        {
            e.check = check;
            e.texture = decodeTexture(m, T, e.tex0);
        }
        tex0 = e.tex0;
        return e.texture;
    }   

    // envType: the mesh type of an environment-map mesh, -1 for plain meshes.
    NativeMeshEntry buildNativeMesh(const GuestRam &m, uint32_t strips, uint32_t skin, uint32_t uvTable, uint32_t container, int envType)
    {
        NativeMeshEntry out;
        auto mesh = std::make_shared<GSNativeMesh>();
        struct SkinVertex
        { 
            int16_t pos[3], nrm[3]; 
            uint8_t weight[4], bone[4];
        };
        std::vector<SkinVertex> skinVerts;
        if (!m.ok(skin, 4))
            return out;
        uint32_t p = skin + 4;
        for (uint32_t g =  0, groups = m.u32(skin); g < groups; ++g)
        {
            p = (p + 15) & ~15u; 
            if (!m.ok(p, 16))
                return out;
            const uint32_t n =  m.u32(p);
            int8_t bones[4];
            std::memcpy(bones, m.at(p + 4), 4);   
            p += 16;
            const uint32_t nrmAt = (p + n * 6 + 15) & ~15u, wAt = (nrmAt + n * 6 + 15) & ~15u;
            if (n > 4096 || !m.ok(p, wAt + n * 4 - p))
                return out;
            for (uint32_t v = 0; v < n; ++v)
            {
                SkinVertex s{};
                std::memcpy(s.pos, m.at(p + v * 6), 6);
                std::memcpy(s.nrm, m.at(nrmAt + v * 6), 6);
                std::memcpy(s.weight, m.at(wAt + v * 4), 4);
                for (int k = 0; k < 4; ++k)
                {
                    if (bones[k] < 0)   
                        s.weight[k] = 0;
                    s.bone[k] = uint8_t(std::max<int>(bones[k], 0));
                    if (s.weight[k])
                        out.bones = std::max<uint32_t>(out.bones, s.bone[k] + 1u);
                }
                skinVerts.push_back(s);
            }
            p = wAt + n * 4; 
        }
        if (!m.ok(strips, 4) || !m.ok(container, 0x18))
            return out;
        const uint32_t groups = m.u32(strips);
        uint32_t g = strips + 4;
        for (uint32_t gi = 0; gi < groups; ++gi)
        {
            if (!m.ok(g, 0x1C))
                return out;
            const uint16_t type = envType >= 0 ? uint16_t(envType) : m.u16(g) & 7, stripCount = m.u16(g + 8),
                            texIndex = m.u16(g + 12), passes = m.u16(g + 10), envIndex = m.u16(g + 16) ;
            g += 0x1C ;
            if (type > 3)
                return out;
            GSNativeMeshGroup group;
            group.type = type;
            group.firstIndex = uint32_t(mesh->indices.size());   
            auto texture = [&](uint32_t index) { return m.u32(container + index * 0x10u + m.u32(container + 0x14)); };
            uint64_t tex0 = 0;
            group.texture = nativeTexture(m, texture(texIndex), tex0);
            if (!group.texture)
                return out;
            if (envType >= 0)
            {

                group.envMesh = true;
                group.passes = passes > 1 ? 2 : 1;
                uint64_t envTex0 = 0;
                if (group.passes > 1 && !(group.envTexture = nativeTexture(m, texture(envIndex), envTex0)))

                    return out;  
            }
            group.tcc = ((tex0 >> 34) & 1) != 0;
            group.tfx = uint32_t(tex0 >> 35) & 3;
            for (uint32_t s = 0; s < stripCount; ++s)
            {
                if (!m.ok(g, 2))
                    return out;

                const uint32_t n = m.u16(g);
                g += 2;
                if (!m.ok(g, n * 4))
                    return out;
                const uint32_t first = uint32_t(mesh->vertices.size());
                for (uint32_t v = 0; v < n; ++v, g += 4)
                {
                    const uint32_t index =  m.u16(g), uvOffset = m.u16(g + 2);
                    if (index >= skinVerts.size() || !m.ok(uvTable + 4 + uvOffset, 4))
                        return out;
                    const SkinVertex &sv = skinVerts[index];
                    GSNativeSkinVertex vtx{};
                    std::memcpy(vtx.pos, sv.pos, 6);
                    std::memcpy(vtx.nrm, sv.nrm, 6);
                    std::memcpy(vtx.weight, sv.weight, 4);
                    std::memcpy(vtx.bone, sv.bone, 4);
                    vtx.uv[0] = m.u16(uvTable + 4 + uvOffset);
                    vtx.uv[1] = m.u16(uvTable + 6 + uvOffset) ;
                    mesh->vertices.push_back(vtx);
                }
                for (uint32_t t = 0; t + 2 < n; ++t)
                    for (uint32_t k : {first + t, first + t + 1, first + t + 2})

                        mesh->indices.push_back(k);
            }
            group.indexCount = uint32_t(mesh->indices.size()) - group.firstIndex;
            mesh->groups.push_back(std::move(group));
        }
        if (mesh->indices.empty())
            return out;
        out.mesh = std::move(mesh) ;
        return out;
    }

    void dkNativeSubMesh(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime) 
    {
        const GuestRam m{rdram};  
        const uint32_t rec = GPR_U32(ctx, 4), palette = GPR_U32(ctx, 5), texSet = GPR_U32(ctx, 6);
        const uint32_t meshObj = READ32(rec + 4);
        const uint32_t flags = m.ok(meshObj, 0x10) ? m.u32(meshObj + 8) : ~0u;
        const bool envMesh = (flags & 8) != 0;
        if ((flags & (envMesh ? kEnvMeshMask : kPlainMeshMask)) != 0 || (envMesh && (flags & 7) > 3) || !m.ok(texSet, 4))
        {
            FUN_002983e8_0x2983e8(rdram, ctx, runtime);
            return;
        }
        const uint32_t strips = READ32(rec + 0x1C), skin = READ32(rec + 0x24), uvTable = READ32(rec + 0x2C);
        const uint32_t container = m.u32(texSet);
        struct Key
        {
            uint32_t strips, skin, uv, container;
            bool operator==(const Key &o) const
            {
                return strips == o.strips && skin == o.skin && uv == o.uv && container == o.container;
            }
        };
        struct KeyHash 
        {
            size_t operator()(const Key &k) const
            {
                return size_t(k.strips) * 73856093u ^ size_t(k.skin) * 19349663u ^ size_t(k.uv) * 83492791u ^ k.container;
            }
        };

        static std::unordered_map<Key, NativeMeshEntry, KeyHash> cache;
        static size_t loadsSeen = 0;
        dk_loads::dropLoaded(cache, loadsSeen, [](const auto &e) { return e.first.strips; });
        const int envType = envMesh ? int(flags & 7) : -1;
        const uint64_t check = (m.hash(strips, 64) ^ m.hash(skin, 64) * 3 ^ m.hash(uvTable, 16) * 7 ^ m.hash(container, 32) * 11) +
                                uint64_t(envType + 1);
        NativeMeshEntry &entry = cache[Key{strips, skin, uvTable, container}];
        if (entry.check != check)

        {
            entry = buildNativeMesh(m, strips, skin, uvTable, container, envType);
            entry.check = check;
        }
        if (!entry.mesh || !m.ok(palette, entry.bones * 64u))
        {
            FUN_002983e8_0x2983e8(rdram, ctx, runtime);
            return;
        }
        GSNativeModelParams params;
        params.mesh = entry.mesh;
        float vu0[14][4];
        for (uint32_t i = 0; i < 56; ++i)
        {
            const uint32_t bits = READ32(kVu0Data + i * 4);
            std::memcpy(&vu0[i / 4][i % 4], &bits, 4);

        }
        std::memcpy(params.screen, vu0[0], sizeof(params.screen));
        std::memcpy(params.lightDir, vu0[4], sizeof(params.lightDir));
        std::memcpy(params.lightColor, vu0[8], sizeof(params.lightColor));
        std::memcpy(params.clampMax, vu0[12], sizeof(params.clampMax));
        std::memcpy(params.fog, vu0[13], sizeof(params.fog));
        params.alpha = READ32(0x571480u) & 0xFFFFu; // vi5 (ctc2 before the draw)

        params.squareLight = ((flags >> 6) & 1) != 0;
        const float depthBias = envMesh ? 0.0f : float((flags & 0x3800u) >> 11);
        params.depthBias = depthBias;
        if (envMesh)
        {
            const uint32_t scale = READ32(0x56EA88u);
            std::memcpy(&params.envScale, &scale, 4);
            for (int i = 0; i < 4; ++i)
                params.colorAdd[i] = int32_t(READ32(0x4F6EB0u + 4u * i));
        }
        params.bones.resize(entry.bones);
        for (uint32_t b = 0; b < entry.bones; ++b)
            std::memcpy(params.bones[b].data(), m.at(palette + b * 64), 64);

        bool opaque = false, blended = false;
        for (const GSNativeMeshGroup &g : entry.mesh->groups)
            (g.type == 0 ? opaque : blended) = true;
        if (opaque)
        {
            GSNativeModelParams p = params;
            p.typeMask = 1;
            dkAppendNative(rdram, READ32(kOpaqueLayer), NativeDraw::makeModelDraw(std::move(p)));
        }  
        if (blended)
        {

            params.typeMask = 0xE;
            dkAppendNative(rdram, READ32(kBlendLayer), NativeDraw::makeModelDraw(std::move(params)));
        }
        if (!envMesh && (flags & 0x3800u))
        {
            uint32_t bits;
            std::memcpy( &bits, &depthBias, 4);
            WRITE32(0x4F8FD8u, bits);
            WRITE32(kVu0Data + 0xD0u, READ32(0x4F8FD0u));
            WRITE32(kVu0Data + 0xD4u, READ32(0x4F8FD4u));
            WRITE32(kVu0Data + 0xD8u, bits);  
            WRITE32(kVu0Data + 0xDCu, READ32(0x4F8FDCu));
        }
        ctx->pc = GPR_U32(ctx, 31);
    }

    int g_startChapter = -1, g_startVerse = 0;

    void dkStartMission(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        if (GPR_U32(ctx, 31) == 0x13FBC8u && g_startChapter >= 0) // the New Game call (jal at 0x13FBC0 in FUN_0013faa4)
        {
            SET_GPR_U64(ctx, 5, uint64_t(g_startChapter));
            SET_GPR_U64(ctx, 6, uint64_t(g_startVerse));
            WRITE32(0x3B4E14u, uint32_t(g_startChapter)); // pending scene id
            std::fprintf(stderr, "[dk] start chapter %d verse %d\n", g_startChapter, g_startVerse);
        }
        FUN_002e80b4_0x2e80b4(rdram, ctx, runtime);  
    }

    int g_startScene[3] = {-1, 0, 0};
    uint32_t g_lastScene[3] = {};

    void dkSceneSwitch(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        if (g_startScene[0] >= 0 && GPR_U32(ctx, 4) == 4u)
        {
            for (int i = 0; i < 3; ++i)
                SET_GPR_U64(ctx, 4 + i, uint64_t(g_startScene[i]));
            g_startScene[0] = -1;
        }
        std::fprintf(stderr, "[dk] tick %llu scene %u %u %u\n", (unsigned long long)PS2Det::vsyncTick(), GPR_U32(ctx, 4), GPR_U32(ctx, 5), GPR_U32(ctx, 6));
        for (int i = 0; i < 3; ++i)
            g_lastScene[i] = GPR_U32(ctx, 4 + i);
        FUN_0014b61c_0x14b61c( rdram, ctx, runtime);
    }   

    constexpr uint32_t kGroundTime = 0x3AD310u;
    uint64_t g_groundTick = ~0ull;
    double g_groundSeconds = 0;

    void dkGroundMotion(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)   

    {

        const uint64_t tick = PS2Det::vsyncTick();
        if (tick != g_groundTick)
            g_groundSeconds += std::clamp(guestFloat(rdram, ctx, runtime, kGroundTime + 0xCu), 0.0f, 0.1f);

        g_groundTick = tick;
        FUN_0012e328_0x12e328(rdram, ctx, runtime);
    }
    bool nativeLibc()
    {
        static const bool on = [] {
            const char *v = std::getenv("PS2_DK_NATIVE_LIBC");
            return !v || std::strcmp(v, "0") != 0;
        }();
        return on;
    }
    uint8_t *ramRange(uint8_t *rdram, uint32_t addr, uint32_t size)
    {
        if (addr >= 0x70000000u && addr < 0x80000000u) // scratchpad
            return nullptr;
        const uint32_t phys = addr & 0x1FFFFFFFu;
        return phys < PS2_RAM_SIZE && size <= PS2_RAM_SIZE - phys ? rdram + phys : nullptr;
    }
    template <int Kind, void (*Original)(uint8_t *, R5900Context *, PS2Runtime *)>
    void dkLibcCopy(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        const uint32_t dst = GPR_U32(ctx, 4), src = GPR_U32(ctx, 5), size = GPR_U32(ctx, 6);
        uint8_t *d = ramRange(rdram, dst, size);
        uint8_t *s = Kind == 2 ? d : ramRange(rdram, src, size);
        // newlib memcpy copies forward: an overlap with dst after src smears.
        if (!d || !s || (Kind == 0 && d > s && d < s + size))
        {
            Original(rdram, ctx, runtime);
            return;
        }
        if (Kind == 0)
            std::memcpy(d, s, size);
        else if (Kind == 1)
            std::memmove(d, s, size);
        else
            std::memset(d, int(src & 0xFFu), size);
        SET_GPR_U64(ctx, 2, uint64_t(int64_t(int32_t(dst))));
        ctx->pc = GPR_U32(ctx, 31);
    }

    std::unordered_map<uint32_t, PS2Runtime::RecompiledFunction> g_probeOriginal;
    double g_probeMs = 2.0;
    void dkProbe(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        const uint32_t pc = ctx->pc;
        const auto it = g_probeOriginal.find(pc);  
        if(it == g_probeOriginal.end())
            return;
        const auto t0 = std::chrono::steady_clock::now();
        it->second(rdram, ctx, runtime);
        const double ms = std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - t0).count();
        if (ms > g_probeMs)
            std::fprintf(stderr, "[probe] tick %llu 0x%06x %.2f ms\n", (unsigned long long)PS2Det::vsyncTick(), pc, ms);
    }
    void applyProbe(PS2Runtime &runtime)
    {
        const char *v = std::getenv("PS2_DK_PROBE");   
        if (!v)
            return;
        if (const char *at = std::strchr(v, '@'))
            g_probeMs = std::atof(at + 1);
        for (const char *p = v; *p && *p != '@';)
        {
            char *end = nullptr;
            const uint32_t addr = uint32_t(std::strtoul(p, &end, 16));
            if (end == p)

                break;
            if(PS2Runtime::RecompiledFunction fn = runtime.lookupFunction(addr))
            {
                g_probeOriginal[addr] = fn;
                runtime.replaceFunction(addr, &dkProbe);
            }
            p = *end == ',' ? end + 1 : end;   
        }
    }


    void dkNewlibRand(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        const uint32_t state = READ32(0x51B278u) + 0xA8u;
        const uint64_t next = READ64(state) * 0x5851F42D4C957F2Dull + 1u;
        WRITE64(state, next);

        SET_GPR_S32(ctx, 2, int32_t(uint32_t(next >> 32) & 0x7FFFFFFFu));
        ctx->pc = GPR_U32(ctx, 31);
    }

    void applyDrakengard(PS2Runtime &runtime)
    {
        if (const char *v = std::getenv("PS2_DK_NEWLIB_RAND"); !v || std::strcmp(v, "0") != 0)
            runtime.replaceFunction(0x3165E0u, &dkNewlibRand);
        GraphicsThread::setCsrNoSyncReadPc(0x2801B4u);
        GraphicsThread::setCsrNoSyncReadPc(0x127490u);
        runtime.replaceFunction(0x2800E0u, &dkPollVblankFlag);
        runtime.replaceFunction(0x2983E8u, &dkNativeSubMesh);
        applyDrakengardNativeMap(runtime);
        applyDrakengardNativeSky(runtime);
        applyDrakengardNativeBlob(runtime);   
        applyDrakengardNativeLoad(runtime);
        if (const char *v = std::getenv("PS2_DK_START_MISSION"); v && std::sscanf(v, "%d.%d", &g_startChapter, &g_startVerse) >= 1)
            runtime.replaceFunction(0x2E80B4u, &dkStartMission);
        if (const char *v = std::getenv("PS2_DK_START_SCENE"))
            (void)std::sscanf(v, "%d.%d.%d", &g_startScene[0], &g_startScene[1], &g_startScene[2]);   
        runtime.replaceFunction(0x14B61Cu, &dkSceneSwitch);
        ps2_runtime_hooks::setMoviePicture(&dkMoviePicture);
        GSPerf::frameSubmitReturnPc.store(0x28C0A8u, std::memory_order_relaxed);
        runtime.replaceFunction(0x27F49Cu, &dkPacketBuffers);
        runtime.replaceFunction(0x12E328u, &dkGroundMotion);
        if (nativeLibc())
        {
            runtime.replaceFunction( 0x3157C4u, &dkLibcCopy<0, &FUN_003157c4_0x3157c4>);
            runtime.replaceFunction(0x315874u, &dkLibcCopy<1, &FUN_00315874_0x315874>);
            runtime.replaceFunction(0x315978u, &dkLibcCopy<2, &FUN_00315978_0x315978>);
        }
        applyDrakengardNativeFont(runtime);
        applyDrakengardDrawOwners(runtime); // after the other draw hooks: wraps them 
        applyDrakengardSquadSort(runtime);
        applyProbe(runtime);
    }
}


double dkGroundSeconds()
{
    return g_groundSeconds;

}

void dkLastScene(uint32_t out[3])
{
    for (int i = 0; i < 3; ++i)
        out[i] = g_lastScene[i];
}

PS2_REGISTER_GAME_OVERRIDE("Drakengard PC port", "SLES_523.22", 0x00120008u, 0x1B248F14u, &applyDrakengard)
