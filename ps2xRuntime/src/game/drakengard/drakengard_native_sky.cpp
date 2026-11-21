#include "dk2d/dk2d.h"
#include "game_overrides.h" 
#include "ps2_runtime.h"
#include "ps2_runtime_macros.h"
#include "runtime/gs/render_cmd.h"
#include "runtime/gs/gs_native_map.h"
#include <algorithm>
#include <cstring>
#include <unordered_map>

#include <vector>

void FUN_0022ac6c_0x22ac6c(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime);
void FUN_0022aa08_0x22aa08(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime);

void FUN_0022a7bc_0x22a7bc(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime);

void frameRecorderPinAnchorRepeat(uint64_t id, uint32_t tagAddr, uint32_t tagWord);
bool dkStepB2();
void dkOwnState(const uint8_t *rdram, RenderCmd &cmd, uint32_t blobContext2);
void dkSetSceneFog(uint64_t fogcol);
void dkBTrackAnchor(const std::shared_ptr<RenderCmd> &cmd, uint32_t fn, uint32_t tagAddr);
void dkNativeAtTag(uint32_t tagAddr, std::shared_ptr<RenderCmd> cmd);
namespace dk_native_sky
{
    struct Ram
    {
        const uint8_t *rdram;  
        bool ok(uint32_t a, uint32_t bytes ) const
        {
            const uint32_t p = a & 0x1FFFFFFFu;
            return a && p < PS2_RAM_SIZE && bytes <= PS2_RAM_SIZE - p;
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
            return v;
        }
        uint64_t hash(uint32_t a, uint32_t qwords) const
        {
            uint64_t h = 1469598103934665603ull;
            for (uint32_t i = 0; i < qwords * 2; ++i)
                h = (h ^ u64(a + i * 8)) * 1099511628211ull;
            return h;
        }
    };

    // Data of a RET chain packet at `addr` (the tag's data follows it).
    bool retPacket(const Ram &m, uint32_t addr, uint32_t &qwc)
    {
        if (!m.ok(addr, 16))
            return false;
        const uint64_t tag = m.u64(addr);
        qwc = uint32_t(tag & 0xFFFF);
        return ((tag >> 28) & 7) == 6 && qwc && m.ok(addr, 16 + qwc * 16);

    }

    struct Batch
    {
        uint32_t mem[64][4];
        uint64_t written;
    };

    bool addBatch(GSNativeSkyMesh &mesh, const Batch &b)
    {
        for (uint32_t s : {2u, 27u})
        {

            if (!((b.written >> s) & 1))
                return false;
            const uint32_t h = b.mem[s][0] & 0xFFFF; // ILW: 16 bits
            if (!h)
                return true;
            const uint32_t prim = (b.mem[s][1] >> 15) & 0x7FF;

            if ((h & 0x7FFF) != 6 || !((b.mem[s][1] >> 14) & 1) || (prim & 0x78F) != 0x0C || (b.mem[s][1] >> 26) != 0xC || b.mem[s][2] != 0x412)
                return false;
            const uint32_t base = uint32_t(mesh.vertices.size() );
            for (uint32_t k = 0; k < 6; ++k) 
            {
                const uint32_t v = s + 1 + 4 * k; // position, normal, uv, colour
                if (((b.written >> v) & 0xD) != 0xD)
                    return false;
                GSNativeSkyVertex out{};
                for (int i = 0; i < 4; ++i)
                {
                    const int32_t p = int32_t(b.mem[v][i]);
                    if (p < -32768 || p > 32767)
                        return false;
                    out.pos[i] = int16_t(p);
                    out.rgba[i] = uint8_t(std::min<uint32_t>(b.mem[v + 3][i], 255));
                }
                out.uv[0] = uint16_t(b.mem[v + 2][0]);
                out.uv[1] =  uint16_t(b.mem[v + 2][1]);   
                out.prim[0] = uint8_t(prim);
                mesh.vertices.push_back(out);
            }
            for (uint32_t k = 2; k < 6; ++k)  
                for (uint32_t i : {base + k - 2, base + k - 1, base + k})
                    mesh.indices.push_back(i);
            if (s == 27 && (!((b.written >> 52) & 1) || (b.mem[52][0] & 0xFFFF)))
                return false;   

        }
        return true;
    }

    std::shared_ptr<GSNativeSkyMesh> readCell(const Ram &m, uint32_t chain)
    {
        uint32_t qwc;
        if (!retPacket(m, chain, qwc))
            return nullptr;
        const uint32_t words = 2 + qwc * 4;
        auto word = [&](uint32_t i) { return m.u32(chain + 8 + i * 4); };
        auto mesh = std::make_shared<GSNativeSkyMesh>();
        static thread_local Batch batch;
        std::memset( &batch, 0, sizeof(batch));
        uint32_t cl =  1, wl = 1, stmod = 0;
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
                if (i + dataWords > words || (cmd & 0x10) || vl == 3 || !(imm & 0x8000) || wl > cl || !wl ||

                    stmod > 1)
                    return nullptr;
                const uint8_t *data = m.at(chain + 8 + i * 4);
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
                    const uint32_t q = (imm & 0x3FF) + (v / wl) * cl + v % wl;
                    if (q >= 64)
                        return nullptr;
                    // Offset mode: only the positions (slots 3 + 4k of a strip).
                    const bool position = q >= 3 && q < 52 && q != 27 && (q - (q < 27 ? 3 : 28)) % 4 == 0;
                    if (stmod == 1 && !position)
                        return nullptr;
                    if (stmod == 0 && position)
                        return nullptr;
                    // V2 / V3 unpacks leave the other fields as they were.
                    std::memcpy(batch.mem[q], out, (vn + 1) * 4);
                    batch.written |= 1ull << q;

                }
                i += dataWords;
                continue;
            }
            switch (cmd)
            {
            case 0x01: // STCYCL
                cl = imm & 0xFF;
                wl = imm >> 8;
                break;
            case 0x05: // STMOD
                stmod = imm & 3;
                break;
            case 0x17: // MSCNT: one batch
                if (!addBatch(*mesh, batch))  
                    return nullptr;
                std::memset( &batch, 0, sizeof(batch));
                break;
            case 0x00: // NOP
                break;
            default: // anything else (MSCAL, DIRECT, STROW, MPG, ...) is not expected here
                return nullptr;
            }
        } 
        if (mesh->indices.empty())
            return nullptr;
        return mesh;
    }  


    std::shared_ptr<const GSNativeSkyMesh> cellMesh( const Ram &m, uint32_t chain)
    {
        struct Entry
        {
            uint64_t check = 0;
            std::shared_ptr<const GSNativeSkyMesh> mesh;
        };
        static std::unordered_map<uint32_t, Entry> cache;
        uint32_t qwc;
        if (!retPacket(m, chain, qwc))
            return nullptr;
        // A newly loaded chunk can put other data at the same addresses.
        const uint64_t check = m.hash(chain, qwc + 1 ) | 1;

        Entry &e = cache[chain];
        if (e.check != check)

        {
            e.check = check;
            e.mesh = readCell(m, chain);
        }
        return e.mesh;
    }

    bool readImage(const Ram &m, uint32_t chain, uint32_t &width, uint32_t &height, std::vector<uint8_t> &data)
    {
        uint32_t qwc;
        if (!retPacket(m, chain, qwc))
            return false;
        width = height = 0;
        data.clear();
        for (uint32_t q = 1; q <= qwc; ++q)
        {
            const uint32_t a = chain + q * 16;
            if (m.u64(a + 8) == 0x52) // A+D TRXREG
            {
                const uint64_t v = m.u64(a);  
                width = uint32_t(v & 0xFFF);

                height = uint32_t(v >> 32) & 0xFFF;
            }
            const uint64_t gif = m.u64(a);
            if (width && ((gif >> 58) & 3) == 2) // GIF tag IMAGE
            {
                const uint32_t n = std::min<uint32_t>(uint32_t(gif & 0x7FFF), qwc - q);
                data.insert(data.end(), m.at(a + 16), m.at(a + 16) + n * 16);
                q += n;   
            }
        }
        return width && height && !data.empty();
    }


    std::shared_ptr<const GSNativeTexture> decodeTexture(const Ram &m, uint32_t rec, uint32_t clutBlock, uint64_t tex0)
    {
        const uint32_t psm = uint32_t(tex0 >> 20) & 63, cpsm = uint32_t(tex0 >> 51) & 15, csm = uint32_t(tex0 >> 55) & 1,

                       csa = uint32_t(tex0 >> 56) & 31;
        const uint32_t tw = uint32_t(tex0 >> 26) & 15, th = uint32_t(tex0 >> 30) & 15;
        if ((psm != 0x13 && psm != 0x14) || cpsm != 0 || csm != 0 || csa != 0 || tw > 10 || th > 10)
            return nullptr;
        uint32_t w, h, cw, ch;
        std::vector<uint8_t> image, clut;
        if (!m.ok(rec, 0x20) || !readImage(m, m.u32(rec + 4) + 0x30, w, h, image) || !readImage(m, clutBlock + 0x30, cw, ch, clut))
            return nullptr;
        const uint32_t colours = psm == 0x14 ? 16 : 256;
        if (cw * ch < colours || clut.size() < colours * 4 || image.size() < (size_t(w) * h * (psm == 0x14 ? 1 : 2) + 1) / 2)
            return nullptr;
        uint32_t palette[256];
        for (uint32_t i = 0; i < colours; ++i)
        {
            // CSM1: a 256-colour CLUT has bits 3 and 4 of the index swapped.
            const uint32_t at =  colours == 256 ? (i & ~24u) | ((i & 8) << 1) | ((i & 16) >> 1) : i;
            std::memcpy(&palette[i], clut.data() + at * 4, 4);
        }
        auto tex = std::make_shared<GSNativeTexture>();
        tex->width = 1u << tw;
        tex->height = 1u << th;
        tex->rgba.assign(size_t(tex->width) * tex->height, 0);   
        for (uint32_t y = 0; y < std::min(h, tex->height); ++y)   
            for (uint32_t x = 0; x < std::min(w, tex->width); ++x)
            {
                const uint32_t p = y * w + x;
                const uint32_t index = psm == 0x14 ? (image[p >> 1] >> ((p & 1) * 4)) & 15 : image[p];
                tex->rgba[size_t(y) * tex->width + x] = palette[index];
            }
        return tex;
    }

    struct TextureEntry
    {
        uint64_t check = 0;
        uint64_t tex0 = 0, tex1 = 0;
        std::shared_ptr<const GSNativeTexture> texture;
    };
    const TextureEntry *cellTexture(const Ram &m, uint32_t rec, uint32_t clutBlock)
    {
        static std::unordered_map<uint64_t, TextureEntry> cache;
        if (!m.ok(rec, 0x20) || !m.ok(clutBlock, 0x40))
            return nullptr;
        const uint32_t tmpl = m.u32(rec + 0xC), block = m.u32(rec + 4);
        uint32_t qwc, imageQwc, clutQwc;
        if (!retPacket(m, tmpl, qwc) || qwc != 3 || !retPacket(m, block + 0x30, imageQwc) || !retPacket(m, clutBlock + 0x30, clutQwc))
            return nullptr;
        const uint64_t check = (m.hash(rec, 2) ^ m.hash(tmpl, 4) * 3 ^ m.hash(block + 0x30, imageQwc + 1) * 5 ^ m.hash(clutBlock + 0x30, clutQwc + 1) * 7) |
                               1;
        TextureEntry &e = cache[uint64_t(rec) << 32 | clutBlock];
        if (e.check != check)
        {
            e = TextureEntry{};
            e.check = check;
            // VU 17 GIF tag (NLOOP 2, A+D), 18 / 19 A+D TEX1_1 and TEX0_1.
            for (uint32_t a = tmpl + 0x20; a < tmpl + 0x40; a += 16)
            {
                if (m.u64(a + 8) == 0x14)
                    e.tex1 = m.u64(a);
                else if (m.u64(a + 8) == 0x06)
                    e.tex0 = m.u64(a);
            }
            if (e.tex0)
                e.texture = decodeTexture(m, rec, clutBlock, e.tex0);
        }
        return e.texture ? &e : nullptr;
    }

    uint32_t g_terrain = 0, g_cellsStart = 0, g_cellsList = 0;

    // FUN_0022ac6c(terrain a0, packet a1).
    void dkSkyTerrain(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        g_terrain = GPR_U32(ctx, 4);
        g_cellsStart = g_cellsList = 0;
        FUN_0022ac6c_0x22ac6c(rdram, ctx, runtime); 
    }

    // FUN_0022aa08(packet a0, cell list a1, texture buffers a2 / a3).
    void dkSkyCells(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {

        g_cellsStart = GPR_U32(ctx, 4);
        g_cellsList = GPR_U32(ctx, 5);
        FUN_0022aa08_0x22aa08(rdram, ctx, runtime);
    }

    void writeAnchor(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime, uint32_t at, std::shared_ptr<RenderCmd> cmd)
    {
        if ( cmd)
            dkOwnState(rdram, *cmd, 0);
        dkBTrackAnchor(cmd, 0x19B430u, at );
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

    bool readCells(const Ram &m, uint32_t T, uint32_t list, GSNativeSkyParams &p)
    {
        if (!m.ok(T, 0x2B0))
            return false;
        for (uint32_t e = list; m.ok(e, 28) && m.u32(e + 12); e += 28)
        {
            if (p.cells.size() >= 4096)
                return false;
            const uint32_t cellRec = m.u32(e + 12), texRec = m.u32(e + 16), cbp = m.u32(e + 20);
            if (!m.ok(cellRec, 0x30) || !texRec)
                return false;
            uint32_t clutBlock = 0;
            for (uint32_t i = 0; i < 16 && !clutBlock; ++i)
            {
                const uint32_t chunk = T + 16 * i;
                if (m.u32(chunk + 8) != cbp || !m.u32(chunk + 4))
                    continue;
                const uint32_t container = m.u32(chunk + 4);
                if (!m.ok(container, 16))
                    return false;
                const uint32_t records = m.u32(container + 8), count = m.u32(container + 4);
                if(!m.ok(records, 0x20) || texRec < records || texRec >= records + count * 0x20u)
                    return false;
                clutBlock = m.u32(records + 8);
            }
            GSNativeSkyCell cell;
            cell.mesh = cellMesh(m, m.u32(cellRec + 8));
            const TextureEntry *tex = clutBlock ? cellTexture(m, texRec, clutBlock) : nullptr;
            if (!cell.mesh || !tex)
                return false;
            cell.texture = tex->texture;
            cell.tex0 = tex->tex0;
            cell.tex1 = tex->tex1;

            cell.row[0] = int32_t(m.u32(e));  
            cell.row[1] = int32_t(m.u32(e + 8));
            p.cells.push_back(std::move(cell));
        }
        if (p.cells.empty() )
            return false;
        // VU1 0-7 (T + 0x180), 15 (T + 0x280), 16 (T + 0x2a0): FUN_0022a84c.
        for (int c = 0; c < 4; ++c)
            for (int r = 0; r < 4; ++r)
            {
                p.m1[c][r] = m.f32(T + 0x180u + 16u * c + 4u * r);
                p.m2[c][r] = m.f32( T + 0x1C0u + 16u * c + 4u * r);
            }
        for (int i = 0; i < 4; ++i)
        {
            p.fog[i] = m.f32(T + 0x280u + 4u * i);
            p.scale[i] = m.f32(T + 0x2A0u + 4u * i);
        }
        return true;
    }

    void dkSkyEnd(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        const Ram m{rdram};
        const uint32_t start = g_cellsStart, at = GPR_U32(ctx, 4), flush = at - 0x10u;   
        g_cellsStart = 0;
        if (start && flush >= start + 0x30u && m.ok(flush, 16) && m.u64(flush) == 0x0034320050000000ull &&

                m.u32(flush + 8) == 0x13000000u)
        {
            GSNativeSkyParams p;
            const bool native = readCells(m, g_terrain, g_cellsList, p);
            if (dkStepB2())
            {
                auto state = std::make_shared<Native2D>();
                state->function = 0x19B430u;
                {
                    dk2d::Draw2D d(*state);
                    d.fogColor(m.u64(g_terrain + 0x290u));
                    d.tests(dk2d::kCtx1, 0x50000);
                    d.blend(dk2d::kCtx1, 0x44) ;
                    d.wrap(dk2d::kCtx1, 5); 
                }
                dkSetSceneFog(m.u64(g_terrain + 0x290u));
                dkNativeAtTag(start, RenderExec::makeNative2D(std::move(state)));
                if (!native)
                    dk2d::fallback(rdram, *ctx, 0x19B430u, "sky-game", {}, {});
            }
            if(native)
            {
                const uint64_t call[2] = {m.u64(flush), m.u64(flush + 8)};
                writeAnchor(rdram, ctx, runtime, start, NativeDraw::makeSkyDraw(std::move(p)));
                WRITE64(start + 0x10u, call[0]);
                WRITE64( start + 0x18u, call[1]);  
                SET_GPR_U32(ctx, 4, start + 0x20u);
            }
        }  
        FUN_0022a7bc_0x22a7bc(rdram, ctx, runtime);

    }
}

void applyDrakengardNativeSky(PS2Runtime &runtime)
{
    using namespace dk_native_sky; 
    runtime.replaceFunction(0x22AC6Cu, &dkSkyTerrain);   
    runtime.replaceFunction(0x22AA08u, &dkSkyCells);
    runtime.replaceFunction(0x22A7BCu, &dkSkyEnd);
}
