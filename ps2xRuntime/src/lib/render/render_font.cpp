
#include "render_font.h"
#include "render_translate.h"
#include "runtime/gs/gs_widescreen.h"

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector> 

namespace
{
    GSTex0Reg decodeTex0(uint64_t v)
    {
        GSTex0Reg t;
        t.tbp0 = uint32_t(v & 0x3FFF);  
        t.tbw = uint8_t((v >> 14) & 0x3F) ;
        t.psm = uint8_t((v >> 20) & 0x3F);
        t.tw = uint8_t((v >> 26) & 0xF);
        t.th = uint8_t((v >> 30) & 0xF);
        t.tcc = uint8_t((v >> 34) & 1);   
        t.tfx = uint8_t((v >> 35) & 3);
        t.cbp = uint32_t((v >> 37) & 0x3FFF);
        t.cpsm = uint8_t((v >> 51) & 0xF);
        t.csm = uint8_t((v >> 55) & 1); 
        t.csa = uint8_t((v >> 56) & 0x1F);
        t.cld = uint8_t((v >> 61) & 7);
        return t;
    }

    bool validPsm(uint32_t psm)
    {
        return rtrans::validPsm(psm);
    }

    void uploadGlyph(RenderFontHost &target, const GSNativeFontBatch &b, const GSNativeFontGlyph &g)
    {

        const GSNativeFontData &f = *b.font;
        GSTransferCommand c{};
        c.bitbltbuf.sbp = uint32_t(b.bitbltbuf & 0x3FFF);
        c.bitbltbuf.sbw = uint8_t((b.bitbltbuf >> 16) & 0x3F);

        c.bitbltbuf.spsm = uint8_t((b.bitbltbuf >> 24) & 0x3F);
        c.bitbltbuf.dbp = uint32_t((b.bitbltbuf >> 32) & 0x3FFF);
        c.bitbltbuf.dbw = uint8_t((b.bitbltbuf >> 48) & 0x3F);
        c.bitbltbuf.dpsm = uint8_t((b.bitbltbuf >> 56) & 0x3F);
        c.trxpos.ssax = uint16_t(b.trxpos & 0x7FF);
        c.trxpos.ssay = uint16_t((b.trxpos >> 16) & 0x7FF);
        c.trxpos.dsax = uint16_t((b.trxpos >> 32) & 0x7FF);
        c.trxpos.dsay = uint16_t((b.trxpos >> 48) & 0x7FF);
        c.trxpos.dir = uint8_t((b.trxpos >> 59) & 3);
        c.trxreg.rrw = uint16_t(b.trxreg & 0xFFF);

        c.trxreg.rrh = uint16_t((b.trxreg >> 32) & 0xFFF);
        c.direction = 0;
        target.transfer( c);
        const uint32_t qw = (f.cellBytes + 15) / 16 ;
        std::vector<uint8_t> data(size_t(qw) * 16, 0);
        std::memcpy(data.data(), f.bitmap.data() + size_t(g.cell) * f.cellBytes, f.cellBytes);
        target.upload(data.data(), uint32_t(data.size()));
    }

    GSPrimReg decodePrim(uint64_t value)
    {
        GSPrimReg prim{};
        prim.type = static_cast<GSPrimType>(value & 0x7u);
        prim.iip =  ((value >> 3) & 1u) != 0u;   
        prim.tme = ((value >> 4) & 1u) != 0u;
        prim.fge = ((value >> 5) & 1u) != 0u;
        prim.abe = ((value >> 6) & 1u) != 0u;
        prim.aa1 = ((value >> 7) & 1u) != 0u;
        prim.fst = ((value >> 8) & 1u) != 0u;   

        prim.ctxt = ((value >> 9) & 1u) != 0u;
        prim.fix = ((value >> 10) & 1u) != 0u;
        return prim;
    }

    void drawGlyph(RenderFontHost &target, const RenderState &env, const GSNativeFontBatch &b, const GSNativeFontGlyph &g)
    {
        GSContext ctx[2] = {env.ctx[0], env.ctx[1]};
        ctx[1].tex0 = decodeTex0( b.tex0[g.odd]);
        ctx[1].tex1 = b.tex1;
        ctx[1].alpha = b.alpha;
        const GSPrimReg written = decodePrim(b.prim );
        GSPrimReg prim = env.prmodecont ? written : env.prmodeRegister;
        prim.type = written.type;
        GSPrimitiveBatch batch{};
        GSDrawState &st = batch.state;
        st.context = ctx[prim.ctxt ? 1 : 0];
        st.prim = prim; 
        st.texa = env.texa;

        st.texclut = env.texclut;
        st.pabe = env.pabe;
        st.scanmsk = env.scanmsk;
        st.dimx = env.dimx;
        st.dthe = env.dthe;
        st.colclamp = env.colclamp;
        st.fogR = uint8_t(env.fogcol & 0xFF);
        st.fogG = uint8_t((env.fogcol >> 8) & 0xFF);
        st.fogB = uint8_t((env.fogcol >> 16) & 0xFF);
        st.textureWidth = uint16_t(1u << std::min<uint32_t>(st.context.tex0.tw, 10u));
        st.textureHeight = uint16_t(1u << std::min<uint32_t>(st.context.tex0.th, 10u));
        const uint8_t mmag = uint8_t((st.context.tex1 >> 5u) & 0x1u), mmin = uint8_t((st.context.tex1 >> 6u) & 0x7u);
        st.linearFilter = mmag != 0u || mmin == 1u || (mmin & 0x4u) != 0u;
        uint32_t q;
        const uint32_t qBits = uint32_t(g.rgbaq >> 32);

        std::memcpy(&q, &qBits, 4);
        float qf ;
        std::memcpy(&qf, &q, 4);
        const uint64_t uv[2] = {b.uv0, b.uv1}, xyz[2] = {g.xyz0, g.xyz1};
        for (int i = 0; i < 2; ++i)
        {
            GSVertex &v = batch.vertices[size_t(i)];
            v.x = float(xyz[i] & 0xFFFF) / 16.0f;

            v.y = float((xyz[i] >> 16) & 0xFFFF) / 16.0f;
            v.z = double((xyz[i] >> 32) & 0xFFFFFF);
            v.fog = uint8_t((xyz[i] >> 56) & 0xFF);
            v.r = uint8_t(g.rgbaq & 0xFF);
            v.g = uint8_t((g.rgbaq >> 8) & 0xFF);
            v.b = uint8_t( (g.rgbaq >> 16) & 0xFF);
            v.a = uint8_t((g.rgbaq >> 24) & 0xFF);
            v.q = qf == 0.0f ? 1.0f : qf; 
            v.u = uint16_t(uv[i] & 0x3FFF);
            v.v = uint16_t((uv[i] >> 16) & 0x3FFF);
        }
        batch.vertexCount = 2;
        target.submit(batch);
    }

    void logDraw(bool native, const RenderState &env)
    {
        static const bool on = [] {
            const char *v = std::getenv("PS2_NATIVE_FONT_LOG");
            return v && std::strcmp(v, "0") != 0;
        }();
        if (!on)

            return;
        static uint64_t counts[2]{};
        static bool shown = false;
        ++counts[native];
        if (!native && !shown)  
        {
            shown = true;
            const GSContext &c = env.ctx[1];
            std::fprintf(stderr, "[font] replayed: frame psm %u fbmsk %08x test %llx alpha %llx clamp %llx texclut %u/%u pabe %d prmodecont %d\n", c.frame.psm, c.frame.fbmsk, (unsigned long long)c.test, (unsigned long long)c.alpha, (unsigned long long)c.clamp, env.texclut.cou, env.texclut.cov, env.pabe, env.prmodecont);
        }
        if ((counts[0] + counts[1]) % 600 == 0)
            std::fprintf(stderr, "[font] GS batches: native %llu replayed %llu\n", (unsigned long long)counts[1], (unsigned long long)counts[0]);

    }


    rdraw::Blend blendOf(uint64_t alpha)
    {
        rdraw::Blend b;
        b.on = true;
        b.a = rdraw::BlendInput( alpha & 3);
        b.b = rdraw::BlendInput((alpha >> 2) & 3);

        b.c = rdraw::BlendFactor((alpha >> 4) & 3) ;
        b.d = rdraw::BlendInput((alpha >> 6) & 3);
        b.fixed = uint8_t(alpha >> 32);
        return b;
    }

    bool drawNative(RenderFontHost &host, const GSNativeFontBatch &b, DkRes *font, const RenderState &env)
    {
        const GSNativeFontData &f = *b.font;  
        GSContext c = env.ctx[(b.prim >> 9) & 1]; // a copy: widescreen squeezes its scissor
        GSWidescreen::Squeeze squeeze; 
        if (GSWidescreen::active() && c.frame.fbp == GSWidescreen::worldFbp() && !(((c.test >> 16) & 1) != 0 && ((c.test >> 17) & 3) >= 2) )
        {
            const uint32_t anchor = GSWidescreen::uiAnchor(b.owner);
            float x0 =  1e30f, x1 = -1e30f;
            const float ofx = float(c.xyoffset.ofx) / 16.0f;
            for (const GSNativeFontGlyph &g : b.glyphs)
                for (const uint64_t xyz : {g.xyz0, g.xyz1})
                {
                    x0 = std::min(x0, float(uint16_t(xyz & 0xFFFF)) / 16.0f - ofx);

                    x1 = std::max(x1, float(uint16_t(xyz & 0xFFFF)) / 16.0f - ofx);
                }
            squeeze = GSWidescreen::squeezeFor(anchor ? anchor : uint32_t(GSWidescreen::kCentre), x0, x1);
            if (squeeze.on && float(c.scissor.x1 - c.scissor.x0) < GSWidescreen::kScreenWidth * 0.95f)
            {
                c.scissor.x0 = uint16_t(std::max(0.0f, std::floor(squeeze.apply(float(c.scissor.x0))))) ;
                c.scissor.x1 = uint16_t(std::max(0.0f, std::ceil(squeeze.apply(float(c.scissor.x1)))));
            }
        } 
        // Sprite, textured, blended, UV, no fog / antialiasing, from PRIM.
        if ((b.prim & 0x7FF & ~0x200ull) != 0x156 || !env.prmodecont || env.pabe)
            return false;
        const uint32_t test = uint32_t(c.test);
        DkFontDraw draw{};
        draw.blend = blendOf(c.alpha);
        if ((c.frame.psm != 0 && c.frame.psm != 1) || (test & 0x4000) || !dkRender().fontBlend(&draw.blend))
            return false;
        bool wholeBytes = true;
        uint8_t mask = 0;
        for (int i = 0; i < 4; ++i)
        {
            const uint32_t byte = (c.frame.fbmsk >> (i * 8)) & 0xff;
            wholeBytes &= byte == 0 || byte == 0xff;
            if (byte != 0xff)
                mask |= uint8_t(1u << i);
        }
        if (c.frame.psm == 1 )
            mask &= ~8u;
        if (!wholeBytes || (c.clamp & 3) >= 2 || ((c.clamp >> 2) & 3) >= 2 || env.texclut.cou || env.texclut.cov)
            return false;
        // The upload: cell x cell PSMT4 at (0, 0) of the texture.
        const uint32_t dbp = uint32_t((b.bitbltbuf >> 32) & 0x3FFF), dbw = uint32_t((b.bitbltbuf >> 48) & 0x3F), 
                       dpsm = uint32_t((b.bitbltbuf >> 56) & 0x3F);
        if (dpsm != 0x14 || (b.trxpos & 0x07FF07FF07FF07FFull) || b.trxreg != (uint64_t(f.cell) | uint64_t(f.cell) << 32))

            return false;
        GSTex0Reg tex[2];
        uint32_t clutW[2]{}, clutH[2]{} ;
        for (int i = 0; i < 2; ++i)
        {
            const GSTex0Reg &t = tex[i] = decodeTex0(b.tex0[i]);
            if (t.psm != 0x14 || t.tbp0 != dbp || t.tbw != dbw || t.csm != 0 || (t.cpsm != 0 && t.cpsm != 2) ||

                (1u << std::min<uint32_t>(t.tw, 10u)) < f.cell || (1u << std::min<uint32_t>(t.th, 10u)) < f.cell)
                return false;
            const bool pal16 = t.cpsm == 2;
            const uint32_t mask16 = pal16 ? 511 : 255, base = (t.csa & (pal16 ? 31u : 15u)) << 4;
            if (base + 15 > mask16)
                return false;
            // CLUT entries base .. base + 15 at their places (CSM1 layout).
            uint32_t cols = 0, rows = 0;
            for (uint32_t e = base; e < base + 16; ++e)
            {
                const uint32_t s = (e & ~24u) | ((e & 8) << 1) | ((e & 16) >> 1);
                cols = std::max(cols, (s & 15) + 1);
                rows = std::max(rows, (s >> 4) + 1);
            }
            clutW[i] = cols > 8 ? 16 : 8;
            for (clutH[i] = 1; clutH[i] < rows;)
                clutH[i] *= 2;
            DkFontTexture &o = draw.tex[i];
            o.width = 1u << std::min<uint32_t>(t.tw, 10u );
            o.height = 1u << std::min<uint32_t>(t.th, 10u);
            o.mode = rtrans::texMode(b.tex0[i]);
            o.wrapU = rtrans::wrapU(c.clamp);
            o.wrapV = rtrans::wrapV(c.clamp);
            o.paletteBase = base;
            o.paletteMask = mask16;
        }  
        // ZTST NEVER / invalid buffers: the renderer draws nothing.
        const uint32_t zm = (test >> 17) & 3;
        if (!validPsm(c.frame.psm) || !validPsm(c.zbuf.psm) || !c.frame.fbw || zm == 0)
            return true;
        for (int i = 0; i < 2; ++i)
        { 
            if (i && b.tex0[1] == b.tex0[0])
            {
                draw.tex[1].palette = draw.tex[0].palette;
                continue;
            }
            GSTex0Reg ct{};
            ct.tbp0 = tex[i].cbp;
            ct.tbw = uint8_t(std::max(1u, uint32_t(env.texclut.cbw)));
            ct.psm = tex[i].cpsm;
            ct.tw = uint8_t(clutW[i] == 16 ? 4 : 3);
            for (ct.th = 0; (1u << ct.th) < clutH[i]; ++ct.th)
            {
            }

            if (!host.texture(ct, 0, env.texa, env.texclut, draw.tex[i].palette))
                return false;

        }
        const bool zUsed = !c.zbuf.zmask || zm >= 2;
        if (!host.bind(c, zUsed))
            return true;


        const uint64_t tex1 = b.tex1;
        const uint32_t mmag = uint32_t((tex1 >> 5) & 1), mmin = uint32_t((tex1 >> 6) & 7);
        draw.font = font;
        draw.writeMask = mask;
        draw.alphaTest.on = (test & 1) != 0;
        draw.alphaTest.compare = rdraw::Compare((test >> 1) & 7);
        draw.alphaTest.reference = uint8_t((test >> 4) & 255);  
        draw.alphaTest.fail = rdraw::AlphaFail((test >> 12) & 3);
        draw.depthOn = zUsed;
        draw.depthWrite = !c.zbuf.zmask;
        draw.depthTest = rdraw::DepthTest(zm);
        draw.bilinear = mmag != 0 || mmin == 1 || (mmin & 4) != 0;
        draw.alphaHigh = (c.fba & 1) != 0;
        draw.color24 = c.frame.psm == 1;

        const int ofx = c.xyoffset.ofx >> 4, ofy = c.xyoffset.ofy >> 4;
        const double zMax = c.zbuf.psm == 48 ? 4294967295.0 : c.zbuf.psm == 49 ? 16777215.0 : 65535.0;
        const float su0 = float(uint16_t(b.uv0 & 0x3FFF)) / 16.0f, sv0 = float(uint16_t((b.uv0 >> 16) & 0x3FFF)) / 16.0f,
                    su1 = float(uint16_t(b.uv1 & 0x3FFF)) / 16.0f, sv1 = float(uint16_t((b.uv1 >> 16) & 0x3FFF)) / 16.0f;
        auto edge = [](float t0, float t1, float p0, float p1, float at) {
            return p1 > p0 ? t0 + (t1 - t0) * (at - .5f - p0) / (p1 - p0) : t0;
        };
        thread_local std::vector<DkFontInstance> instances;
        instances.resize(b.glyphs.size());
        for (size_t i = 0; i < b.glyphs.size(); ++i)
        {
            const GSNativeFontGlyph &g = b.glyphs[i];
            const float x0v = float(uint16_t(g.xyz0 & 0xFFFF)) / 16.0f, y0v = float(uint16_t((g.xyz0 >> 16) & 0xFFFF)) / 16.0f,
                        x1v = float(uint16_t(g.xyz1 & 0xFFFF)) / 16.0f, y1v = float(uint16_t((g.xyz1 >> 16) & 0xFFFF)) / 16.0f;
            const double z1 = double((g.xyz1 >> 32) & 0xFFFFFF); 
            const float ax = squeeze.apply(x0v - ofx), ay = y0v - ofy, bx = squeeze.apply(x1v - ofx), by = y1v - ofy;
            const float x0 = std::min(ax, bx), y0 = std::min(ay, by), x1 = std::max(ax, bx), y1 = std::max(ay, by);
            const float lx = std::ceil(x0), ly = std::ceil(y0), hx = std::max(lx + 1, std::ceil(x1)), hy = std::max(ly + 1, std::ceil(y1));
            const float eu0 = edge(su0, su1, x0, x1, lx), eu1 = edge(su0, su1, x0, x1, hx), ev0 = edge(sv0, sv1, y0, y1, ly),
                        ev1 = edge(sv0, sv1, y0, y1, hy);
            const float du = ( eu1 - eu0) / (hx - lx) * .5f, dv = (ev1 - ev0) / (hy - ly) * .5f;
            DkFontInstance &o = instances[i];
            o.rect[0] = lx;
            o.rect[1] = ly;
            o.rect[2] = hx;
            o.rect[3] = hy;
            o.uv[0] = eu0;
            o.uv[1] = ev0;
            o.uv[2] = eu1;
            o.uv[3] = ev1;
            o.uvRange[0] = std::min(eu0 + du, eu1 - du);
            o.uvRange[1] = std::min(ev0 + dv, ev1 - dv);
            o.uvRange[2] = std::max(eu0 + du, eu1 - du);
            o.uvRange[3] = std::max(ev0 + dv, ev1 - dv);
            o.depth = float(std::min(z1, zMax) / 4294967296.0);
            o.color = uint32_t(g.rgbaq & 0xFFFFFFFFu);
            o.glyph = (g.cell % 16) * f.cell | ((g.cell / 16) * f.cell) << 12 | g.odd << 24;
            o.pad = 0;
        }
        draw.instances = instances.data();
        draw.count = uint32_t(instances.size());
        dkRender().fontDraw(&draw); 
        host.drawn(zUsed && !c.zbuf.zmask);
        return true;
    }
}

void renderFont(RenderFontHost &host, const GSNativeFontBatch &b, DkRes *font, const RenderState &env)
{
    std::lock_guard lock(b.mutex);
    if (b.glyphs.empty() || !b.font)
        return;
    const bool native = font && drawNative(host, b, font, env);
    logDraw(native, env);
    if(!native)
    {
        for (const GSNativeFontGlyph &g : b.glyphs)

        {
            uploadGlyph(host, b, g);
            drawGlyph(host, env, b, g);
        }
        return;
    }

    uploadGlyph(host, b, b.glyphs.back());
}
