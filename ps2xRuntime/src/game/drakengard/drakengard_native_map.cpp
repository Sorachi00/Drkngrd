#include "drakengard_return_hook.h"
#include "drakengard_loads.h"
#include "game_overrides.h" 
#include "ps2_runtime.h"
#include "ps2_runtime_macros.h"
#include "dk_port_macros.h"
#include "runtime/gs/render_cmd.h"

#include "runtime/gs/gs_native_map.h"
#include "runtime/gs/gs_native_post.h"
#include "runtime/gs/gs_hw_quality.h"
#include <algorithm>
#include <cstdlib>

#include <cstring>
#include <unordered_map>
#include <vector>

void FUN_00251454_0x251454(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime);   
void FUN_0025279c_0x25279c(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime);
void FUN_00252dc4_0x252dc4(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime);
void FUN_0027f774_0x27f774(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime);
void FUN_0027f830_0x27f830(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime);
bool dkPacketHeapRoom(uint8_t *rdram, uint32_t bytes);
void dkAppendNative(uint8_t *rdram, uint32_t layer, std::shared_ptr<RenderCmd> cmd);

void frameRecorderPinAnchorRepeat(uint64_t id, uint32_t tagAddr, uint32_t tagWord);
bool dkStepB2();
void dkOwnState(const uint8_t *rdram, RenderCmd &cmd, uint32_t blobContext2);
void dkBTrackAnchor(const std::shared_ptr<RenderCmd> &cmd, uint32_t fn, uint32_t tagAddr);
namespace dk_native_map
{
    constexpr uint32_t kPacketHeap = 0x4F9254u;
    constexpr uint32_t kMapEnv = 0x484B10u;

    struct Ram
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
        uint64_t u64(uint32_t a) const
        {
            uint64_t v;

            std::memcpy(&v, at(a), 8);
            return v;
        }
        float f32(uint32_t a) const
        {
            float v;
            std::memcpy(&v, at(a), 4);
            return v ;
        }
        uint64_t hash(uint32_t a, uint32_t bytes) const
        {
            uint64_t h = 1469598103934665603ull;
            for (uint32_t i = 0; i < bytes; ++i)
                h = (h ^ at(a)[i]) * 1099511628211ull;
            return h;   
        }
    };

    constexpr uint32_t kScene = 0x484CC0u;
    struct LayerVu 
    {
        bool init = false;
        bool world = false; // no re-init since it (no prop's own matrix)
        float matrix[4][4]{}, camera[3]{}, fog[2]{}, ramp[3]{};  
    };
    LayerVu g_layerVu[3];
    float sceneF(const uint8_t *rdram, uint32_t offset)
    {
        float f;
        std::memcpy(&f, rdram + kScene + offset, 4);
        return f;
    }
    float rampNear(const uint8_t *rdram, uint32_t lo, uint32_t hi, float scale)
    {
        const float d = Ps2FpuSubFast(sceneF(rdram, hi), sceneF(rdram, lo));
        if (FPU_C_EQ_S(d, 0.0f))
            return scale;
        return Ps2FpuDivExact(Ps2FpuMulFast(sceneF(rdram, hi), scale), d);
    }
    float rampFar(const uint8_t *rdram, uint32_t lo, uint32_t hi, float scale)
    {
        const float d = Ps2FpuSubFast(sceneF(rdram, hi), sceneF(rdram, lo));
        if (FPU_C_EQ_S(d, 0.0f))
            return 0.0f;
        return Ps2FpuDivExact(-scale, d);
    }
    void layerMatrix(const uint8_t *rdram, LayerVu &v)
    {
        for(int c = 0; c < 4; ++c) // VU1 903-906: FUN_00264c18 (scene +0x100)

            for (int r = 0; r < 4; ++r)

                v.matrix[c][r] = sceneF(rdram, 0x100u + 16u * c + 4u * r);
    }
}

// FUN_0025279c's values for map layer `layer` (now).
extern "C" void dkMapLayerVuInit(const uint8_t *rdram, uint32_t layer)
{
    using namespace dk_native_map;
    if (layer >= 3)
        return;
    LayerVu &v = g_layerVu[layer]; 
    layerMatrix(rdram, v);
    for (int i = 0; i < 3; ++i) // VU1 907: FUN_00264bf0 (scene +0)
        v.camera[i] = sceneF(rdram, 4u * i);
    v.fog[0] = rampNear(rdram, 0x29Cu, 0x2A0u, 255.0f); // VU1 910.z (FUN_00264d48)
    v.fog[1] = rampFar(rdram, 0x29Cu, 0x2A0u, 255.0f);  // VU1 910.w (FUN_00264d10)
    v.ramp[0] = rampNear(rdram, 0x2C0u, 0x2C4u, 128.0f); // VU1 911.z (FUN_00264dd4)

    v.ramp[1] = rampFar(rdram, 0x2C0u, 0x2C4u, 128.0f);  // VU1 911.w (FUN_00264d9c)
    v.ramp[2] = 128.0f;                                  // VU1 911.y
    v.init = true;
    v.world = true;

}
// FUN_00252dc4's matrix for map layer `layer` (now).
extern "C" void dkMapLayerVuMatrix(const uint8_t *rdram, uint32_t layer)
{
    using namespace dk_native_map;
    if (layer >= 3)
        return;
    layerMatrix(rdram, g_layerVu[layer]);
    g_layerVu[layer].world = false;
}

namespace dk_native_map
{
    // FUN_0025279c(packet a0, layer a1): the layer's VU1 init packet.
    void dkMapLayerInit(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        dkMapLayerVuInit(rdram, GPR_U32(ctx, 5));
        FUN_0025279c_0x25279c(rdram, ctx, runtime);
    }
    void dkDrawPass(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        FrameRecorder::beginFrame();
        FUN_0027f774_0x27f774(rdram, ctx, runtime);

    }
    constexpr uint32_t kPostLayer = 142;
    void dkAfterDrawPass(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        FrameRecorder::endFrame();
        if (GSHwQuality::postWanted())
            dkAppendNative( rdram, kPostLayer, GSNativePost::makeDraw()) ;
        FUN_0027f830_0x27f830(rdram, ctx, runtime);
    }

    // FUN_00252dc4(packet a0, layer a1): the matrices again.
    void dkMapLayerReinit(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        dkMapLayerVuMatrix(rdram, GPR_U32(ctx, 5)); 
        FUN_00252dc4_0x252dc4(rdram, ctx, runtime) ;
    }

    constexpr uint32_t kSmallMap = 1u << 10, kSmallMap2 = 1u << 17, kBigMap = 1u << 1, kBigMap2 = 1u << 8; 
    // A block with other bits stays with the game's code (VU1).
    constexpr uint32_t kSupportedTypes =  kSmallMap | kSmallMap2 | kBigMap | kBigMap2;

    struct MeshEntry
    {
        uint64_t check = 0 ;

        std::shared_ptr<const GSNativeMapMesh> mesh; // null: draw with the game's code
    };

    // VU1 memory of one batch (TOPS-relative qwords, 4 words each).
    struct Batch
    {
        uint32_t mem[450][4];
    };

    void addStrip(GSNativeMapMesh &mesh, const Batch &b, uint32_t row, const uint32_t *plane, uint32_t first, uint32_t n, uint32_t posAt, uint32_t uvAt, uint32_t rgbAt, int uv2At, int rgba2At)
    {
        const uint32_t base = uint32_t(mesh.vertices.size() );
        const bool hasPlane = (b.mem[row][3] & 0x1000u) == 0;   
        const uint8_t prim = uint8_t(b.mem[row][1] >> 15);
        for ( uint32_t k = 0; k < n; ++k)
        {
            const uint32_t v = first + k;
            GSNativeMapVertex out{};
            for (int i = 0; i < 3; ++i)
                out.pos[i] = int16_t(b.mem[posAt + v][i]);
            out.uv[0] = int16_t( b.mem[uvAt + v][0]);
            out.uv[1] = int16_t(b.mem[uvAt + v][1]);
            for (int i = 0; i < 3; ++i)
                out.rgb[i] =  uint8_t(b.mem[rgbAt + v][i]);
            out.rgb[3] = prim;
            if (uv2At >= 0)
            {
                out.uv2[0] = int16_t(b.mem[uv2At + v][0]);
                out.uv2[1] = int16_t(b.mem[uv2At + v][1]);
            }
            if (rgba2At >= 0)
                for (int i = 0; i < 4; ++i)
                    out.rgba2[i] = uint8_t(b.mem[rgba2At + v][i]);
            if (hasPlane)
                std::memcpy(out.plane, plane, 16);
            else
                out.plane[3] = 1.0f;
            mesh.vertices.push_back(out);
        }
        for (uint32_t k = 2; k < n; ++k)
            for (uint32_t i : {base + k - 2, base + k - 1, base + k})
                mesh.indices.push_back(i);
    }

    bool addBatch(GSNativeMapMesh &mesh, const Batch &b, uint32_t type)
    {
        if (type == kBigMap || type == kBigMap2)
        {
            const bool map2 = type == kBigMap2;
            const uint32_t strips = map2 ? 11 : 12, verts = map2 ? 41 : 45;
            uint32_t v =  0;
            for (uint32_t s = 0; s < strips; ++s)
            {
                const uint32_t n = b.mem[s][0] & 0x7FFFu;
                if (!n)
                    return true;
                if (n < 3 || v + n > verts)
                    return false;
                if ( map2)
                    addStrip(mesh, b, s, b.mem[12 + s], v, n, 23, 64, 146, 105, 187);
                else
                    addStrip(mesh, b, s, b.mem[13 + s], v, n, 25, 115, 160, -1, -1);

                v += n;
            }
            return (b.mem[strips][0] & 0x7FFFu) == 0;
        }
        // Small MAP / MAP2: row 0, plane 1, pos 2, (MAP2: uv2 11), uv 20, rgb 29, (MAP2: rgba2 38).
        const uint32_t n = b.mem[0][0] & 0x7FFFu;
        if (n < 3 || n > 9)
            return false;
        const bool map2 = type == kSmallMap2;
        addStrip(mesh, b, 0, b.mem[1], 0, n, 2, 20, 29, map2 ? 11 : -1, map2 ? 38 : -1);
        return true;

    }

    bool readChain(const Ram &m, uint32_t addr, uint32_t qwc, uint32_t type, GSNativeMapMesh &mesh)
    {
        const uint32_t words = qwc * 4;
        if (!m.ok(addr, qwc * 16))
            return false;
        auto word = [&]( uint32_t i) { return m.u32(addr + i * 4); };
        static thread_local Batch batch;
        std::memset( &batch, 0, sizeof(batch));
        uint32_t tex[2] = {0, 0} ;
        const GSNativeMapGroup::Kind kind = type == kBigMap      ? GSNativeMapGroup::BigMap
                                            : type == kBigMap2   ? GSNativeMapGroup::BigMap2
                                            : type == kSmallMap2 ? GSNativeMapGroup::Map2

                                                                : GSNativeMapGroup::Map;
        for (uint32_t i = 0; i < words;)
        {  
            const uint32_t code = word(i++);
            const uint32_t cmd = (code >> 24) & 0x7F, num = (code >> 16) & 0xFF, imm = code & 0xFFFF;
            if (cmd >= 0x60) // UNPACK
            {   
                const uint32_t vn = (cmd >> 2) & 3, vl = cmd & 3, count = num ? num : 256;
                const bool usn = (imm >> 14) & 1;

                const uint32_t bits = vl == 3 ? 16 : (32u >> vl) * (vn + 1);
                const uint32_t dataWords = (count * bits + 31) / 32;
                if (i + dataWords > words || (cmd & 0x10) || vl == 3)
                    return false; // masked or V4-5 unpacks are not used by map chains
                const uint32_t dst = imm & 0x3FF;
                const uint8_t *data = m.at(addr + i * 4);
                for (uint32_t v = 0; v < count; ++v)
                {
                    uint32_t out[4] = {0, 0, 0, 0};
                    for (uint32_t c = 0; c <= vn; ++c)
                    {
                        const uint32_t e = v * (vn + 1) + c;
                        if (vl == 0)
                            std::memcpy(&out[c], data + e * 4, 4);
                        else if (vl == 1)

                        {
                            uint16_t h;
                            std::memcpy(&h, data + e * 2, 2);
                            out[c] = usn ? h : uint32_t(int32_t(int16_t(h)));
                        }
                        else
                            out[c] = usn ? data[e] : uint32_t(int32_t(int8_t(data[e])));
                    }
                    if (dst + v == 0x398) // texture indices (above the batch buffers)
                    {
                        tex[0] = out[0];
                        tex[1] =  out[1];
                    }
                    else if (dst + v < 450)
                        std::memcpy(batch.mem[dst + v], out, 16) ;
                }
                i += dataWords;
                continue;
            }
            switch(cmd)
            {
            case 0x14: // MSCAL 0x200: one batch (0: end sync, 0xa: MAP2 pass 2)
            case 0x15:
            {
                if (imm != 0x200)

                    break;
                if (mesh.groups.empty() || mesh.groups.back().kind != kind || mesh.groups.back().texIndex != tex[0] || mesh.groups.back().texIndex2 != tex[1])
                {
                    GSNativeMapGroup g;
                    g.kind = kind;
                    g.texIndex = tex[0];
                    g.texIndex2 = tex[1] ;
                    g.firstIndex = uint32_t(mesh.indices.size());
                    mesh.groups.push_back(g);
                }
                if (!addBatch(mesh, batch, type))
                    return false;
                mesh.groups.back().indexCount = uint32_t(mesh.indices.size()) - mesh.groups.back().firstIndex;
                std::memset( &batch, 0, sizeof(batch));
                break;
            }
            case 0x20: // STMASK
                i += 1;
                break;
            case 0x30: // STROW
            case 0x31: // STCOL
                i += 4;
                break;
            case 0x4A: // MPG
                i += (num ? num : 256) * 2;

                break;
            case 0x50: // DIRECT, DIRECTHL
            case 0x51:
                return false;
            default: // NOP, STCYCL, OFFSET, BASE, ITOP, STMOD, MSKPATH3, MARK, FLUSH*, MSCNT
                break;
            }
        }
        return true;
    }


    struct MapStats
    {
        uint64_t calls = 0, native = 0, pointLight = 0, lod = 0, types = 0, other = 0, unwound = 0;
        uint64_t kept = 0;
        uint64_t bits[32]{};
    } g_mapStats;
    void mapLog()
    {
        static const bool on = [] {
            const char *v = std::getenv("PS2_NATIVE_MAP_LOG");
            return v && std::strcmp(v, "0") != 0;
        }();
        if (!on)
            return;
        static uint64_t lastFallbacks = 0, fallbackLines = 0;
        const uint64_t fallbacks =  g_mapStats.pointLight + g_mapStats.lod + g_mapStats.other + g_mapStats.kept;
        const bool fallback = fallbacks != lastFallbacks && fallbackLines < 50;
        lastFallbacks = fallbacks;
        if (++g_mapStats.calls % 5000 && !fallback)
            return;
        fallbackLines += fallback;

        std::fprintf(stderr, "[map] %llu block layers: native %llu, point lights %llu, lod %llu, types %llu, other %llu, kept %llu, unwound %llu; bits",

                    (unsigned long long)g_mapStats.calls, (unsigned long long)g_mapStats.native, (unsigned long long)g_mapStats.pointLight,
                    (unsigned long long)g_mapStats.lod, (unsigned long long)g_mapStats.types,
                    (unsigned long long)g_mapStats.other, (unsigned long long)g_mapStats.kept, (unsigned long long)g_mapStats.unwound);
        for (int b = 0; b < 32; ++b)
            if (g_mapStats.bits[b])
                std::fprintf(stderr, " %d:%llu", b, (unsigned long long)g_mapStats.bits[b]);
        std::fprintf(stderr, "\n");
    }

    std::shared_ptr<const GSNativeMapMesh> blockMesh(const Ram &m, uint32_t desc)
    {
        if (!m.ok(desc, 16))
            return nullptr;
        const uint32_t mask = m.u32(desc);   
        uint32_t refs = 0;
        for(uint32_t bits = mask; bits; bits &= bits - 1 )
            ++refs;
        if (mask & ~kSupportedTypes)
        {
            ++g_mapStats.types;
            for (int b = 0; b < 32; ++b)
                if ((mask & ~kSupportedTypes) >> b & 1)
                    ++g_mapStats.bits[b];
        }

        if (!refs || (mask & ~kSupportedTypes) || !m.ok(desc, 16 + refs * 16))
            return nullptr;
        uint64_t check = m.hash(desc, 16 + refs * 16);
        for (uint32_t k = 0; k < refs; ++k)
        {
            const uint64_t tag = m.u64( desc + 16 + k * 16);
            const uint32_t addr = uint32_t(tag >> 32) & 0x0FFFFFFFu, qwc = uint32_t(tag & 0xFFFF);
            if (qwc < 2 || !m.ok(addr, qwc * 16))
                return nullptr;
            check = check * 31 + qwc;
            for (uint32_t q = 0; q < qwc; q += 64)
                check = (check ^ m.u64(addr + q * 16) ^ m.u64(addr + q * 16 + 8) * 3) * 1099511628211ull;
            check = (check ^ m.u64(addr + (qwc - 1) * 16) ^ m.u64(addr + (qwc - 1) * 16 + 8) * 3) * 1099511628211ull;
        }
        static std::unordered_map<uint32_t, MeshEntry> cache;
        static size_t loadsSeen = 0;
        dk_loads::dropLoaded(cache, loadsSeen, [](const auto &e) { return e.first; });
        MeshEntry &e = cache[desc];
        if (e.check == check && e.check)
            return e.mesh;
        e.check = check;
        e.mesh = nullptr;

        auto mesh = std::make_shared<GSNativeMapMesh>();
        for (uint32_t k = 0, bit = 0; k < refs; ++k, ++bit)
        {
            while ( !((mask >> bit) & 1))
                ++bit ;
            const uint64_t tag = m.u64( desc + 16 + k * 16);
            if (((tag >> 28) & 7) != 3 || !readChain(m, uint32_t(tag >> 32) & 0x0FFFFFFFu, uint32_t(tag & 0xFFFF), 1u << bit, *mesh))
                return nullptr;
        }

        if (mesh->indices.empty())
            return nullptr;
        e.mesh = std::move(mesh);
        return e.mesh;

    }

    struct Upload  
    {
        uint32_t width = 0, height = 0;
        std::vector<uint8_t> data;
    };
    bool readUpload(const Ram &m, uint32_t entry, Upload &u)
    {
        if (!m.ok(entry, 0x18) )
            return false;
        const uint64_t tag = m.u64(entry + 0x10);
        const uint32_t addr = uint32_t(tag >> 32) & 0x0FFFFFFFu, qwc = uint32_t(tag & 0xFFFF);

        if (((tag >> 28) & 7) != 3 || !qwc || !m.ok(addr, qwc * 16))

            return false;
        for (uint32_t q = 0; q < qwc; ++q)
        {
            const uint32_t a = addr + q * 16;
            if (m.u64(a + 8) == 0x52) // A+D TRXREG
            {

                const uint64_t v = m.u64(a);
                u.width = uint32_t(v & 0xFFF);
                u.height = uint32_t(v >> 32) & 0xFFF;
            }
            const uint64_t gif = m.u64(a);
            if (u.width && ((gif >> 58) & 3) == 2) // GIF tag IMAGE 
            {
                const uint32_t n = std::min<uint32_t>(uint32_t(gif & 0x7FFF), qwc - q - 1);
                u.data.insert(u.data.end(), m.at(a + 16), m.at(a + 16) + n * 16);
                q += n;   
            }
        }
        return !u.data.empty();
    }

    std::shared_ptr<GSNativeTexture> decodeMapTexture(const Ram &m, uint32_t texEntry, uint32_t clutEntry, uint64_t tex0)
    {
        const uint32_t psm =  uint32_t(tex0 >> 20) & 63, cpsm = uint32_t(tex0 >> 51) & 15, csm = uint32_t(tex0 >> 55) & 1,
                       csa = uint32_t(tex0 >> 56) & 31;
        const uint32_t tw = uint32_t(tex0 >> 26) & 15, th = uint32_t(tex0 >> 30) & 15;
        if ( (psm != 20 && psm != 19 && psm != 0) || (psm != 0 && (cpsm != 0 || csm != 0 || csa != 0)) || tw > 10 || th > 10)
            return nullptr;
        Upload image, clut; 
        if ( !readUpload(m, texEntry, image))
            return nullptr;
        if (psm == 0) // CT32: RGBA8 texels as stored
        {
            if (image.data.size() < size_t(image.width) * image.height * 4)
                return nullptr;
            auto tex =  std::make_shared<GSNativeTexture>(); 
            tex->width = 1u << tw;
            tex->height = 1u << th;
            tex->rgba.assign(size_t(tex->width) * tex->height, 0);
            for (uint32_t y = 0; y < std::min(image.height, tex->height); ++y)
                std::memcpy(&tex->rgba[size_t(y) * tex->width], image.data.data() + size_t(y) * image.width * 4, std::min(image.width, tex->width) * 4u);
            return tex;
        }
        if (!readUpload(m, clutEntry, clut))
            return nullptr;

        const uint32_t colours = psm == 20 ? 16 : 256;
        if (clut.width * clut.height < colours || clut.data.size() < colours * 4 || image.data.size() < (image.width * image.height * (psm == 20 ? 1 : 2) + 1) / 2)
            return nullptr;
        uint32_t palette[256];
        for (uint32_t i = 0; i < colours; ++i)
        {
            // CSM1: a 256-colour CLUT has bits 3 and 4 of the index swapped.
            const uint32_t at = colours == 256 ? (i & ~24u) | ((i & 8) << 1) | ((i & 16) >> 1) : i;
            std::memcpy(&palette[i], clut.data.data() + at * 4, 4);   
        }
        auto tex = std::make_shared<GSNativeTexture>();
        tex->width = 1u << tw;
        tex->height = 1u << th;
        tex->rgba.assign(size_t(tex->width) * tex->height, 0);
        const uint8_t *src = image.data.data();
        for (uint32_t y = 0; y < std::min(image.height, tex->height); ++y)
            for (uint32_t x = 0; x < std::min(image.width, tex->width); ++x )
            {
                const uint32_t p = y * image.width + x;
                const uint32_t index = psm == 20 ? (src[p >> 1] >> ((p & 1) * 4)) & 15 : src[p];
                tex->rgba[size_t(y) * tex->width + x] = palette[index];
            }
        return tex;
    }
    std::shared_ptr<const GSNativeTexture> mapTexture(const Ram &m, uint32_t texEntry, uint32_t clutEntry, uint64_t tex0)
    {
        struct Entry
        {
            uint64_t check = 0;
            std::shared_ptr<const GSNativeTexture> texture;
            uint32_t texEntry = 0;
        };
        static std::unordered_map<uint64_t, Entry> cache;
        static size_t loadsSeen = 0;
        dk_loads::dropLoaded(cache, loadsSeen, [](const auto &e) { return e.second.texEntry; } );
        if (!m.ok(texEntry, 0x20) || !m.ok(clutEntry, 0x20))
            return nullptr;
        // Key: the two table entries and the format part of TEX0 (not TBP / CBP).
        const uint64_t key = (uint64_t(texEntry) << 32 ^ clutEntry) ^ (tex0 & 0xFFE0001FFFFFC000ull) * 31;
        const uint64_t check = m.hash(texEntry, 0x20) ^ m.hash(clutEntry, 0x20) * 7;
        Entry &e = cache[key];
        if (e.check != check || !e.check)
        {
            e.check = check;
            e.texEntry = texEntry;
            e.texture = decodeMapTexture(m, texEntry, clutEntry, tex0);  
        }
        return e.texture;
    }

    bool isGroupProgram( const Ram &m, uint32_t addr)
    {
        for (uint32_t table : {0x54C300u, 0x54BE00u, 0x54C800u, 0x553400u})
            if (addr == (uint32_t(m.u64(table) >> 32) & 0x0FFFFFFFu))
                return true;
        return false;
    }

    void readTextures(const Ram &m, uint32_t from, uint32_t to, GSNativeMapParams &p )
    {
        for (uint32_t a = from; a + 16 <= to;)

        {
            const uint64_t tag = m.u64(a);   
            const uint32_t id = uint32_t(tag >> 28) & 7, qwc = uint32_t(tag & 0xFFFF); 
            if (id != 1) // REF (texture image): its data is elsewhere
            {
                a += 16;
                continue;
            }   
            // VIF codes: the tag's upper words, then the data.
            const uint32_t words = 2 + qwc * 4;
            auto word = [&](uint32_t i) { return m.u32(a + 8 + i * 4); };

            for (uint32_t i = 0; i < words;)
            {
                const uint32_t code = word(i++);
                const uint32_t cmd = (code >> 24) & 0x7F, num = (code >> 16) & 0xFF, imm = code & 0x3FF;
                if (cmd >= 0x60)
                {
                    const uint32_t vn = (cmd >> 2) & 3, vl = cmd & 3, count = num ? num : 256;
                    const uint32_t bits = vl == 3 ? 16 : (32u >> vl) * (vn + 1);
                    const uint32_t dataWords = (count * bits + 31) / 32;
                    if (vl == 0 && vn == 3 && i + dataWords <= words)
                        for (uint32_t v = 0; v < count; ++v)
                        {
                            const uint32_t q = imm + v, d = i + v * 4;
                            if (q >= 0x399 && q < 0x399 + 32)
                            {
                                const uint32_t index = q - 0x399;
                                if (p.tex0.size() <= index)
                                    p.tex0.resize(index + 1);
                                p.tex0[index] = uint64_t(word(d)) | uint64_t(word(d + 1)) << 32;
                            }
                        }
                    i += dataWords;
                }
                else if (cmd == 0x20)
                    i += 1;
                else if (cmd == 0x30 || cmd == 0x31)

                    i += 4;
                else if (cmd == 0x4A)
                    i += (num ? num : 256) * 2;
                else if (cmd == 0x50 || cmd == 0x51)
                    i += ((code & 0xFFFF) ? (code & 0xFFFF) : 0x10000) * 4; 
            }
            a += 16 * (qwc + 1);
        }
    }

    void writeAnchor(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime, uint32_t at, std::shared_ptr<RenderCmd> cmd)
    {
        if ( cmd)
        {
            dkOwnState(rdram, *cmd, 0);
            // CLAMP_1 0: the map layer init's A+D writes before every layer (FUN_0024e148)
            if (const NativeDraws::State *own = cmd->ownState())
            {
                auto s = std::make_shared<NativeDraws::State>(*own) ;
                s->values.ctx[0].clamp = 0 ;
                s->set[0] |= NativeDraws::kClamp;
                cmd->setOwnState(std::move(s));
            }
        }
        dkBTrackAnchor(cmd, 0x251758u, at);
        if (dkStepB2())
        {
            FrameRecorder::record(std::move(cmd));
            WRITE64(at + 0x00u, 0x10000000ull);
            WRITE64(at + 0x08u, 0);
            return;
        }
        const uint64_t id = FrameRecorder::record(std::move(cmd));
        frameRecorderPinAnchorRepeat(id, at, 0x10000000u);
        WRITE64(at + 0x00u, 0x10000000ull); // CNT, no data
        WRITE32(at + 0x08u, FrameRecorder::anchorWord0(id));
        WRITE32(at + 0x0Cu, FrameRecorder::anchorWord1(id));
    }

    void blockLayerDone(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime, uint32_t start, uint32_t mapRef, uint32_t block, uint32_t layer, int32_t lod, uint32_t header, std::shared_ptr<const GSNativeMapMesh> mesh)
    {
        const Ram m{rdram};
        const uint32_t end = GPR_U32(ctx, 2);
        // The geometry part: the first REF to a group program after the textures.   
        uint32_t geometry = 0 ;
        for (uint32_t a = start; a + 16 <= end;)
        {
            const uint64_t tag = m.u64(a);

            const uint32_t id = uint32_t(tag >> 28) & 7;
            if (id == 3 && isGroupProgram(m, uint32_t(tag >> 32) & 0x0FFFFFFFu))   
            {
                geometry = a;
                break;
            }
            if (id != 1 && id != 3)
            { 
                ++g_mapStats.kept;
                return; // not a packet of this shape: keep the game's
            }
            a += id == 1 ? 16 * (uint32_t(tag & 0xFFFF) + 1) : 16;
        }
        if (!geometry || geometry + 0x30u > end)
        {
            ++g_mapStats.kept;
            return;
        }
        GSNativeMapParams p;
        p.mesh = std::move(mesh);

        readTextures(m, header, geometry, p);
        {
            // List entry i = texture / CLUT id i of the block's lists.
            const uint32_t entryAt = block + layer * 0x30u + uint32_t(lod) * 0xCu + 0x30u;
            const uint32_t mapHeader = m.u32(mapRef), texList = m.u32(entryAt + 4), clutList = m.u32(entryAt + 8);
            if (m.ok(mapHeader, 0x44) && m.ok(texList, 2) && m.ok(clutList, 2))   
            {   
                const uint32_t n = std::min<uint32_t>(m.at(texList)[0], uint32_t(p.tex0.size()));
                p.textures.resize(p.tex0.size());
                for (uint32_t i = 0; i < n && m.ok(texList + 2 + 2 * i, 2) && m.ok(clutList + 2 + 2 * i, 2); ++i)
                {
                    uint16_t texId, clutId;
                    std::memcpy(&texId, m.at(texList + 2 + 2 * i), 2);
                    std::memcpy(&clutId, m.at(clutList + 2 + 2 * i), 2);
                    p.textures[i] = mapTexture(m, m.u32(mapHeader + 0x38) + texId * 0x20u, m.u32(mapHeader + 0x40) + clutId * 0x20u, p.tex0[i]);
                }   
            }
        }
        for (int c = 0; c < 3; ++c) // VU1 917 (FUN_00251560)
            p.origin[c] = int32_t(m.u32(block + 4u * c));
        const LayerVu &vu = g_layerVu[layer] ;
        if (!vu.init)
        {  
            ++g_mapStats.kept;
            return ;
        }
        std::memcpy(p.matrix, vu.matrix, sizeof p.matrix); // VU1 903-906
        std::memcpy(p.camera, vu.camera, sizeof p.camera); // VU1 907
        std::memcpy(p.fog, vu.fog, sizeof p.fog);          // VU1 910.zw
        std::memcpy(p.ramp, vu.ramp, sizeof p.ramp);       // VU1 911.zw, max 911.y
        p.aref = m.u32(kMapEnv + 0x64u) & 0xFF;
        p.colourOnly = layer == 2; // TEST_1 0x53001 for every type in layer 2
        p.worldMatrix = vu.world;  // a re-init carries a prop's own matrix
        bool allDecoded = geometry > start;
        for (const GSNativeMapGroup &g : p.mesh->groups)
        {
            auto decoded = [&](uint32_t i) { return i < p.textures.size() && p.textures[i]; };
            allDecoded = allDecoded && decoded( g.texIndex) && ((g.kind != GSNativeMapGroup::Map2 && g.kind != GSNativeMapGroup::BigMap2) || decoded(g.texIndex2));
        }
        writeAnchor(rdram, ctx, runtime, geometry, NativeDraw::makeMapDraw(std::move(p)));
        if (allDecoded)
        {
            WRITE64(start, 0x20000000ull | uint64_t(geometry & 0x7FFFFFF0u) << 32); // NEXT, no data
            WRITE64(start + 8u, 0);                                                 // VIF NOP, NOP
        }
        SET_GPR_U32(ctx, 2, geometry + 0x10u);
    }

    // FUN_00251454(packet a0, mapRef a1, block a2, layer a3, lod t0, env t1).
    void dkMapBlockLayer(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        const Ram m{rdram};
        const uint32_t start = GPR_U32(ctx, 4), mapRef = GPR_U32(ctx, 5), block = GPR_U32(ctx, 6), layer = GPR_U32(ctx, 7);
        const int32_t lod = int32_t(GPR_U32(ctx, 8));
        const uint32_t env = GPR_U32( ctx, 9), header = READ32(kPacketHeap);
        // Point lights (env+0x14c >= 0) use other VU1 programs.
        std::shared_ptr<const GSNativeMapMesh> mesh;
        if (layer < 3 && lod >= 0 && lod < 4 && m.ok(env, 0x150) && int32_t(m.u32(env + 0x14Cu)) < 0)
        {   
            const uint32_t descAt = block + layer * 0x30u + uint32_t(lod) * 0xCu + 0x30u;
            if (m.ok(descAt, 4))
                mesh = blockMesh(m, m.u32(descAt));
            if (mesh)
                ++g_mapStats.native;
            else
                ++g_mapStats.other; 
        }
        else if (m.ok(env, 0x150) && int32_t(m.u32(env + 0x14Cu)) >= 0)
            ++g_mapStats.pointLight;

        else
            ++g_mapStats.lod;
        mapLog();
        if (!mesh)
        {
            FUN_00251454_0x251454(rdram, ctx, runtime);
            return;
        }
        dk_return::arm(runtime, ctx, [=](uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime) {
            blockLayerDone(rdram, ctx, runtime, start, mapRef, block, layer, lod, header, mesh);
        });
        const uint64_t unwinds = ps2_game_overrides::guestUnwindCount();
        FUN_00251454_0x251454(rdram, ctx, runtime);
        if (ps2_game_overrides::guestUnwindCount() != unwinds)
        {
            ++g_mapStats.unwound;
            return;
        }
        dk_return::finish(rdram, ctx, runtime);
    }
}

void applyDrakengardNativeMap(PS2Runtime &runtime)
{
    using namespace dk_native_map;
    runtime.replaceFunction(0x27F774u, &dkDrawPass);
    runtime.replaceFunction(0x27F830u, &dkAfterDrawPass);
    runtime.replaceFunction(0x25279Cu, &dkMapLayerInit);
    runtime.replaceFunction(0x252DC4u, &dkMapLayerReinit);
    runtime.replaceFunction(0x251454u, &dkMapBlockLayer);
}
