#include "dk2d/dk2d.h"
#include "game_overrides.h"  
#include "ps2_runtime.h"
#include "ps2_runtime_macros.h"
#include "runtime/gs/render_cmd.h"
#include "runtime/gs/gs_native_font.h"
#include "runtime/gs/gs_widescreen.h"
#include "runtime/ps2_det.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>

uint32_t dkDrawOwner();
void frameRecorderPinAnchor(uint64_t id, uint32_t tagAddr);
bool dkStepB2();
void dkBTrackAnchor(const std::shared_ptr<RenderCmd> &cmd, uint32_t fn, uint32_t tagAddr);


namespace dk_native_font
{
    constexpr uint32_t kGlyph = 0x2A6708u;
    constexpr uint64_t kAdTag = 0x1000000000000000ull; // GIF tag: A+D, NREG 1 (NLOOP added)
    enum Slot
    {
        BitBltBuf,
        TrxPos,
        TrxReg,
        Tex0,
        Tex1,
        Alpha,
        Prim,
        Rgbaq,
        Uv,
        SlotCount

    };
    constexpr uint8_t kSlotReg[SlotCount] = {GS_REG_BITBLTBUF, GS_REG_TRXPOS, GS_REG_TRXREG, GS_REG_TEX0_2,
                                            GS_REG_TEX1_2,    GS_REG_ALPHA_2, GS_REG_PRIM,   GS_REG_RGBAQ,
                                            GS_REG_UV};

    constexpr uint64_t kTex1 = 0x61, kAlpha = 0x8000000044ull, kPrim = 0x356, kUv0 = 0x80008;

    PS2Runtime::RecompiledFunction g_original =  nullptr;

    struct Ram
    {
        uint8_t *rdram;
        bool ok(uint32_t a, uint32_t bytes ) const
        {  
            const uint32_t p = a & 0x1FFFFFFFu;
            return p < PS2_RAM_SIZE && bytes <= PS2_RAM_SIZE - p;
        }
        uint8_t *at(uint32_t a) const { return rdram + (a & 0x1FFFFFFFu); }
        template <typename T> T get(uint32_t a) const
        {
            T v;
            std::memcpy(&v, at(a), sizeof(T));
            return v;
        }
        template <typename T> void put(uint32_t a, T v) const { std::memcpy(at(a), &v, sizeof(T) ); }
    };

    std::map<uint32_t, std::shared_ptr<const GSNativeFontData>> g_fonts;
    std::shared_ptr<const GSNativeFontData> fontAt(const Ram &m, uint32_t font)
    { 
        auto it = g_fonts.find(font);
        if (it != g_fonts.end())
            return it->second;
        std::shared_ptr<GSNativeFontData> f;
        const uint32_t glyphs = m.get<uint16_t>(font + 4), cell = m.get<uint16_t>(font + 6);

        const uint32_t offset = m.get<uint32_t>(font + 8), cellBytes = m.get<uint32_t>(font + 0xC) ;
        const uint32_t cells = (glyphs + 1) / 2;
        if (cell && cell <= 64 && cellBytes == cell * cell / 2 && !(cellBytes & 15) && cells && cells <= 4096 && m.ok(font + offset, cells * cellBytes))
        {
            f = std::make_shared<GSNativeFontData>();
            f->cell = cell;
            f->cellBytes = cellBytes;
            f->cells = cells;
            f->bitmap.assign(m.at(font + offset), m.at(font + offset) + size_t(cells) * cellBytes);
        }
        return g_fonts[font] = f;
    }

    struct Open
    {
        std::shared_ptr<GSNativeFontBatch> batch;
        std::shared_ptr<RenderCmd> cmd;
        uint64_t id = 0, tick = 0;
        uint32_t builder = 0, tag = 0, regs = 0, placeholder = 0, end = 0; // tag: the packet's anchor; regs: its A+D writes
        uint64_t tagWords[2] = {}; // (the tag as written: a later glyph joins only while it is unchanged)
    };
    Open g_open;

    struct Stats
    {
        uint64_t glyphs = 0, batches = 0, original = 0;

    };
    Stats g_stats;
    void logStats()
    {
        static const bool on = [] {
            const char *v = std::getenv("PS2_NATIVE_FONT_LOG");
            return v && std::strcmp(v, "0") != 0;
        }();
        static uint64_t lastTick = 0;
        const uint64_t tick = PS2Det::vsyncTick();
        if (!on || tick < lastTick + 600) 
            return;

        lastTick = tick;
        std::fprintf(stderr, "[font] tick %llu: glyphs %llu batches %llu game %llu\n", (unsigned long long)tick, (unsigned long long)g_stats.glyphs, (unsigned long long)g_stats.batches, (unsigned long long)g_stats.original);
        g_stats = {};
    }

    void closePacket(const Ram &m, uint32_t b)   
    {
        const uint32_t tag = m.get<uint32_t>(b + 8), qwc = m.get<uint32_t>(b + 0xC), mode = m.get<uint32_t>(b + 0x10);  
        m.put<uint16_t>(tag, uint16_t(qwc));
        m.put<uint64_t>(tag, (m.get<uint64_t>(tag) & 0xFFFFFFFF03FFFFFFull) | uint64_t((mode << 2) & 0x3C) << 26);
        m.put<uint32_t>(tag + 8, 0);
        m.put<uint32_t>(tag + 12, qwc ? qwc | 0x50000000u : 0);
        const uint32_t ptr = m.get<uint32_t>(b + 4);
        m.put<uint32_t>(b + 8, ptr);
        m.put<uint32_t>(b + 4, ptr + 16);
        m.put<uint32_t>(b + 0xC, 0);
    }

    void glyph(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        const Ram m{rdram};
        const uint32_t fs = GPR_U32(ctx, 4), b = GPR_U32(ctx, 5), str = GPR_U32(ctx, 9), sp = GPR_U32(ctx, 29);
        auto original = [&] {
            ++g_stats.original;
            g_original(rdram, ctx, runtime);
        };
        if (!m.ok(fs, 0x20) || !m.ok(b, 0x34) || !m.ok(str, 1) || !m.ok(sp, 0x18) || !m.ok(m.get<uint32_t>(fs), 0x410))
            return original();
        const uint32_t font = m.get<uint32_t>(fs); 
        const uint32_t entry = font + uint32_t(m.get<uint8_t>(str)) * 4 + 0x10;
        const int32_t advance = m.get<int16_t>(entry), index = m.get<int16_t>(entry + 2);
        const int32_t cell = m.get<int16_t>(font + 6);
        if (index == -1)
        {
            SET_GPR_U64(ctx, 2, 0); // no glyph: nothing drawn, x 0
            ctx->pc = GPR_U32(ctx, 31);
            return;
        }
        const std::shared_ptr<const GSNativeFontData> data = fontAt(m, font);
        const uint32_t ptr = m.get<uint32_t>(b + 4), tagAt = m.get<uint32_t>(b + 8), gifTag = m.get<uint32_t>(b + 0x20);
        const int32_t qwc = m.get<int32_t>(b + 0xC);
        if (!data || index < 0 || uint32_t(index) / 2 >= data->cells || cell <= 0 || (ptr & 15) || (tagAt & 15) ||

            qwc < 0 || m.get<uint32_t>(b + 0x10) != 1 || !m.ok(ptr, 32 * 16) || !m.ok(tagAt, 16) ||
            (gifTag && !m.ok(gifTag, 8)))
            return original();

        // The values FUN_002a6708 writes (64-bit register arithmetic as the game's code).
        const uint64_t x = GPR_U64(ctx, 6), y = GPR_U64(ctx, 7), z = GPR_U64(ctx, 8), a = GPR_U64(ctx, 11);
        const int32_t size = GPR_S32( ctx, 10);
        const uint64_t side = uint64_t(int64_t(int32_t(uint32_t(size) << 4)));
        auto sx = [](uint64_t v) { return uint64_t(int64_t(int32_t(uint32_t(v)))); };
        GSNativeFontGlyph g;

        g.xyz0 = x | y << 16 | z << 32;
        g.xyz1 = sx(x + side) | sx(y + side) << 16 | z << 32;
        g.rgbaq = sx(m.get<uint32_t>(sp)) | a << 24 | sx(m.get<uint32_t>(sp + 0x10)) << 16 | sx(m.get<uint32_t>(sp + 8)) << 8 ;
        g.cell = uint32_t(index) / 2;
        g.odd = uint32_t(index) & 1;
        const uint64_t uvEnd = sx(uint32_t(cell) * 16u - 8u);
        const uint64_t uv1 = uvEnd | uvEnd << 16;
        const uint64_t tex0[2] =  {m.get<uint64_t>(fs + 8), m.get<uint64_t>(fs + 0x10)} ;
        const uint64_t bitbltbuf = uint64_t(m.get<uint32_t>(fs + 0x18)) << 32 | 0x1401000000000000ull;
        const uint64_t trxreg = sx(uint32_t(cell)) | sx(uint32_t(cell)) << 32;
        const uint64_t tick = PS2Det::vsyncTick();
        const uint32_t owner = dkDrawOwner();


        Open &o = g_open;
        const bool join = o.batch && o.cmd && (o.batch->owner == owner || !GSWidescreen::enabled()) && o.builder == b && o.placeholder == tagAt && o.end == ptr && qwc == 0 && !gifTag &&
                          !m.get<uint32_t>(b + 0x30) && !m.get<uint64_t>(b + 0x28) && o.tick == tick &&
                          m.get<uint64_t>(o.tag) == o.tagWords[0] && m.get<uint64_t>(o.tag + 8) == o.tagWords[1] &&
                          o.batch->font == data && o.batch->tex0[0] == tex0[0] && o.batch->tex0[1] == tex0[1] &&
                          o.batch->uv1 == uv1 && o.batch->bitbltbuf == bitbltbuf && o.batch->trxreg == trxreg;
        if (join)

        {
            NativeDraw::fontAddGlyph(*o.cmd, *o.batch, g);
            m.put<uint64_t>(o.regs + Tex0 * 16, tex0[g.odd]);
            m.put<uint64_t>(o.regs + Rgbaq * 16, g.rgbaq);
        }
        else
        {

            auto batch = std::make_shared<GSNativeFontBatch>();
            batch->font = data;
            batch->tex0[0] = tex0[0];
            batch->tex0[1] = tex0[1];
            batch->tex1 = kTex1;
            batch->alpha = kAlpha;
            batch->prim = kPrim;
            batch->uv0 = kUv0;
            batch->uv1 = uv1;
            batch->bitbltbuf = bitbltbuf;
            batch->trxpos = 0;  
            batch->trxreg = trxreg;
            batch->owner = owner;
            batch->glyphs.push_back(g);
            // The open GIF tag gets its NLOOP; the DMA packet so far is closed.
            if (gifTag)

                m.put<uint64_t>(gifTag, m.get<uint64_t>(b + 0x28) | m.get<uint32_t>(b + 0x30));
            m.put<uint32_t>(b + 0x20, 0);
            m.put<uint64_t>( b + 0x28, 0);
            m.put<uint32_t>(b + 0x30, 0);
            if (qwc > 0)
                closePacket(m, b );
            // This batch's packet: GIF A+D registers; its DMA tag is the anchor.
            const uint32_t tag = m.get<uint32_t>(b + 8), at = m.get<uint32_t>(b + 4);
            const uint64_t values[SlotCount] = {bitbltbuf, 0, trxreg, tex0[g.odd], kTex1, kAlpha, kPrim, g.rgbaq, uv1};
            m.put<uint64_t>(at, kAdTag | SlotCount);
            m.put<uint64_t>(at + 8, 0xE); 
            for (int s = 0; s < SlotCount; ++s)

            {
                m.put<uint64_t>(at + 16 + s * 16, values[s]);
                m.put<uint64_t>(at + 24 + s * 16, kSlotReg[s]);
            }
            m.put<uint32_t>(b + 4, at + 16 + SlotCount * 16);

            m.put<uint32_t>(b + 0xC, 1 + SlotCount) ;

            closePacket(m, b );
            std::shared_ptr<RenderCmd> fontDraw = NativeDraw::makeFontDraw(batch);
            o.cmd = fontDraw;
            dkBTrackAnchor(fontDraw, batch->owner, tag);
            const uint64_t id = FrameRecorder::record(std::move(fontDraw));
            if (!dkStepB2())
            {
                frameRecorderPinAnchor(id, tag);
                m.put<uint32_t>(tag + 8, FrameRecorder::anchorWord0(id)); // the tag's first VIF code (closePacket: NOP)
            }
            o.tagWords[0] = m.get<uint64_t>(tag);   
            o.tagWords[1] = m.get<uint64_t>(tag + 8);
            o.batch = std::move(batch);
            o.id = id;
            o.tick = tick;
            o.builder = b;
            o.tag = tag;
            o.regs = at + 16;

            o.placeholder = m.get<uint32_t>(b + 8);

            o.end = m.get<uint32_t>(b + 4);
            ++g_stats.batches;
        }
        ++g_stats.glyphs;

        logStats();
        // Next x: x + (advance * size / cell + 1) * 16 (32-bit, as the game's code).
        const int32_t step = int32_t(uint32_t(advance) * uint32_t(size)) / cell + 1;

        SET_GPR_S32(ctx, 2, int32_t(uint32_t(x) + (uint32_t(step) << 4)));
        ctx->pc = GPR_U32(ctx, 31);   
    }
}

namespace dk_native_font
{
    struct PortOpen
    {
        std::shared_ptr<GSNativeFontBatch> batch;
        std::shared_ptr<RenderCmd> cmd;
        const Native2D *out = nullptr;
        uint64_t run = 0, tick = 0;
        uint64_t end = 0;                // the write count after it (a Draw2D caller's: its position)
        size_t tex0 = 0, rgbaq = 0;      // its TEX0_2 and RGBAQ writes (a register list)
    };
    thread_local PortOpen t_portOpen;

    bool glyphPort(const uint8_t *rdram, const R5900Context &e, Native2D &native)
    {
        dk2d::Draw2D out(native);
        Native2D &list = out.list();
        auto at = [&]() -> uint64_t { return out.aliased() ? out.position() : list.writes.size(); };
        const R5900Context *ctx = &e;
        const Ram m{const_cast<uint8_t *>(rdram)};
        const uint32_t fs = GPR_U32(ctx, 4), str = GPR_U32(ctx, 9), sp = GPR_U32(ctx, 29);
        if (!m.ok(fs, 0x20) || !m.ok(str, 1) || !m.ok(sp, 0x18) || !m.ok(m.get<uint32_t>(fs), 0x410))
            return false;
        const uint32_t font = m.get<uint32_t>(fs);
        const uint32_t entry = font + uint32_t(m.get<uint8_t>(str)) * 4 + 0x10;
        const int32_t advance = m.get<int16_t>(entry), index = m.get<int16_t>(entry + 2);
        const int32_t cell = m.get<int16_t>(font + 6);
        if (index == -1)
        {
            dk2d::setReturn(0); // no glyph: nothing drawn, x 0
            return true;
        }
        const std::shared_ptr<const GSNativeFontData> data = fontAt(m, font);
        if (!data || index < 0 || uint32_t(index) / 2 >= data->cells || cell <= 0)
            return false;
        const uint64_t x = GPR_U64(ctx, 6), y = GPR_U64(ctx, 7), z = GPR_U64(ctx, 8), a = GPR_U64(ctx, 11);
        const int32_t size = GPR_S32( ctx, 10);
        const uint64_t side = uint64_t(int64_t(int32_t(uint32_t(size) << 4)));

        auto sx = [](uint64_t v) { return uint64_t(int64_t(int32_t(uint32_t(v)))); };
        GSNativeFontGlyph g;
        g.xyz0 = x | y << 16 | z << 32;
        g.xyz1 = sx(x + side) | sx(y + side) << 16 | z << 32;
        g.rgbaq = sx(m.get<uint32_t>(sp)) | a << 24 | sx(m.get<uint32_t>(sp + 0x10)) << 16 | sx(m.get<uint32_t>(sp + 8)) << 8;   
        g.cell = uint32_t(index) / 2;
        g.odd = uint32_t(index) & 1;
        const uint64_t uvEnd = sx(uint32_t(cell) * 16u - 8u);
        const uint64_t uv1 = uvEnd | uvEnd << 16;
        const uint64_t tex0[2] = {m.get<uint64_t>(fs + 8), m.get<uint64_t>(fs + 0x10)};
        const uint64_t bitbltbuf = uint64_t(m.get<uint32_t>(fs + 0x18)) << 32 | 0x1401000000000000ull;
        const uint64_t trxreg = sx(uint32_t(cell)) | sx(uint32_t(cell)) << 32;

        const uint64_t tick = PS2Det::vsyncTick();
        const uint32_t owner = dkDrawOwner();

        PortOpen &o = t_portOpen;
        const bool join = o.batch && o.cmd && o.out == &list && o.run == dk2d::effects().run && o.end == at() &&
                          o.tick == tick && (o.batch->owner == owner || !GSWidescreen::enabled()) && o.batch->font == data &&
                          o.batch->tex0[0] == tex0[0] && o.batch->tex0[1] == tex0[1] && o.batch->uv1 == uv1 &&

                          o.batch->bitbltbuf == bitbltbuf && o.batch->trxreg == trxreg;

        if (join)
        {
            NativeDraw::fontAddGlyph(*o.cmd, *o.batch, g);
            if (out.legacy())  
            {
                list.writes[o.tex0].value = tex0[g.odd]; 
                list.writes[o.rgbaq].value = g.rgbaq;
            }
            else
            {
                out.texture(dk2d::kCtx2, tex0[g.odd]);
                out.color(g.rgbaq);
            }
        }
        else
        {
            auto batch = std::make_shared<GSNativeFontBatch>();
            batch->font = data;
            batch->tex0[0] = tex0[0];
            batch->tex0[1] = tex0[1];
            batch->tex1 = kTex1;

            batch->alpha = kAlpha;
            batch->prim = kPrim;
            batch->uv0 = kUv0;
            batch->uv1 = uv1;
            batch->bitbltbuf = bitbltbuf;
            batch->trxpos = 0 ;
            batch->trxreg = trxreg;
            batch->owner = owner;  
            batch->glyphs.push_back(g);
            o.cmd = NativeDraw::makeFontDraw(batch);   
            dk2d::command( out, o.cmd);
            const uint64_t values[SlotCount] = {bitbltbuf, 0, trxreg, tex0[g.odd], kTex1, kAlpha, kPrim, g.rgbaq, uv1};
            for (int s = 0; s < SlotCount; ++s)
            {
                if (s == Tex0)
                    o.tex0 = list.writes.size();
                if (s == Rgbaq)
                    o.rgbaq = list.writes.size();
                out.reg( kSlotReg[s], values[s]);

            }
            o.batch = std::move(batch);
            o.out = &list;
            o.run = dk2d::effects().run;
            o.tick = tick;
            ++g_stats.batches;
        }
        o.end = at();
        ++g_stats.glyphs;
        const int32_t step = int32_t(uint32_t(advance) * uint32_t(size)) / cell + 1;
        dk2d::setReturn(uint64_t(int64_t(int32_t(uint32_t(x) + (uint32_t(step) << 4)))));
        return true;   
    }
    const bool s_glyphPort = dk2d::registerPort(kGlyph, &glyphPort) && dk2d::registerReplace(kGlyph);
}

void applyDrakengardNativeFont(PS2Runtime &runtime)
{
    using namespace dk_native_font;
    if (!runtime.hasFunction(kGlyph))
        return;
    g_original = runtime.lookupFunction(kGlyph);
    runtime.replaceFunction(kGlyph, &glyph);
}
