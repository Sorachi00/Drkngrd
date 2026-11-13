#include "render_backend.h"
#include "dk_render_abi.h"

#include "render_core.h"
#include "render_font.h"
#include "render_gs_layout.h"
#include "render_translate.h"
#include "runtime/gs/gs_async_presenter.h"
#include "runtime/gs/gs_backend.h"
#include "runtime/gs/gs_hw_scale.h"
#include "runtime/gs/gs_widescreen.h"
#include "runtime/gs/gs_window_present.h"
#include "runtime/gs/ps2_gs_common.h"
#include "runtime/gs/render_cmd.h"
#include "../gs/hw/gs_hw_quality_internal.h"
#include <bit>
#include <execution>
#include <atomic>
#include <algorithm>

#include <functional>
#include <chrono>
#include <array>
#include <bitset>
#include <cmath>
#include <cstdio>   
#include <cstdlib>
#include <cstring>
#include <deque>
#include <map>   
#include <memory>
#include <mutex>
#include <stdexcept>
#include <string>
#include <typeinfo>
#include <unordered_map>
#include <vector>

namespace render_detail

{
constexpr uint32_t VramBytes = 4u << 20;
constexpr uint32_t TargetHeight = rdraw::kTargetHeight; // GS coordinates are 0..2047
using Params = std::array<uint32_t, 192>;

struct Range
{
    uint64_t first, last;
};
Range range(uint32_t psm, uint32_t base, uint32_t bw, uint32_t x, uint32_t y)
{
    const uint32_t ws = psm == 19 || psm == 20 ? 7 : 6,
                   hs = psm == 20 ? 7 : psm == 19 || psm == 2 || psm == 10 || psm == 50 || psm == 58 ? 6 : 5;
    const uint64_t begin = uint64_t(base) * 256,
                   end = begin + (uint64_t(y >> hs) * ((bw * 64) >> ws) + (x >> ws) + 1) * 8192;
    return end - begin >= VramBytes ? Range{0, VramBytes} : Range{begin, end};
}
Range rowsRange(uint32_t psm, uint32_t base, uint32_t bw, uint32_t y0, uint32_t y1)   
{ 
    const uint32_t ws = psm == 19 || psm == 20 ? 7 : 6,
                   hs = psm == 20 ? 7 : psm == 19 || psm == 2 || psm == 10 || psm == 50 || psm == 58 ? 6 : 5;
    const uint64_t perRow = std::max<uint64_t>(1, (bw * 64) >> ws) * 8192,
                   begin = uint64_t(base) * 256 + (y0 >> hs) * perRow, end = uint64_t(base) * 256 + ((y1 >> hs) + 1) * perRow;
    return end - begin >= VramBytes ? Range{0, VramBytes} : Range{begin % VramBytes, begin % VramBytes + (end - begin)};
}
bool overlaps(Range a, Range b)
{
    const Range aa[] = {{a.first, std::min<uint64_t>(a.last, VramBytes)}, {0, a.last > VramBytes ? a.last - VramBytes : 0}};
    const Range bb[] = {{b.first, std::min<uint64_t>(b.last, VramBytes)}, {0, b.last > VramBytes ? b.last - VramBytes : 0}};  
    for (auto x : aa)
        for (auto y : bb)

            if (x.first < x.last && y.first < y.last && x.first < y.last && y.first < x.last)
                return true;
    return false;
}
bool validPsm(uint32_t psm)
{
    return rtrans::validPsm(psm);
}
uint32_t rgba(const GSVertex &v)
{
    return v.r | (uint32_t(v.g) << 8) | (uint32_t(v.b) << 16) | (uint32_t(v.a) << 24);

}

using HwVertex = rdraw::Vertex;

struct Surface
{
    bool depth = false;
    uint32_t base = 0, bw = 0, psm = 0;

    uint32_t rows = 0;      // rows drawn (scissor), for presentation and texture reads
    uint32_t sx = 1, sy = 1;

    uint64_t drawnAt =  0;

    uint64_t tallAt = 0;
    void grow(uint32_t bottom, uint64_t at)
    {
        rows = std::max(rows, bottom);
        if (bottom > 272)
            tallAt = at;
    }
    uint64_t serial = 0;
    uint64_t id = 0;
    uint64_t markEpoch = 0;

    uint32_t markRect[4] = {};
    rdraw::TargetId target = 0;
    uint32_t width() const { return bw * 64; }
    // Its blocks: [base, base + blockCount()) (whole pages of its format).
    uint32_t blockCount() const

    {
        uint32_t pw, ph;
        pageSize(psm, pw, ph);
        return ((width() + pw - 1) / pw) * ((rows + ph - 1) / ph) * 32;
    }
    bool holdsBlock(uint32_t block) const { return ((block - base) & 16383) < blockCount(); }
    std::vector<std::array<uint32_t, 4>> memRects;
    std::vector<uint32_t> staged;

    std::vector<std::array<uint32_t, 4>> stagedRects;
    std::vector<uint32_t> memBlocks;
    std::array<uint32_t, 512> memPending{};
    Range range() const
    {
        if (!rows)
            return Range{0, 0};
        Range r = ::render_detail::range(psm, base, bw, width() - 1, rows - 1);
        r.last = std::min<uint64_t>(r.last, VramBytes);   
        return r;
    }
};

uint32_t textureExtent(uint32_t mode, uint32_t size, uint32_t lo, uint32_t hi)
{
    return mode >= 2 ? (std::max(lo, hi) | lo | hi) + 1 : size;
}
int textureRanges(const Params &p, Range out[2])
{
    out[0] = range(p[22], p[20], std::max(1u, p[21]), textureExtent(p[37], p[23], p[39], p[40]) - 1, textureExtent(p[38], p[24], p[41], p[42]) - 1);
    if (!rtrans::paletted(p[22])) 
        return 1;
    out[1] = range(p[28], p[27], std::max(1u, p[31]), p[32] + 15, p[33] + 31);
    return 2;
}
using TexKey = std::array<uint32_t, 23>; // p[20..42]
struct TexKeyHash
{
    size_t operator()(const TexKey &k) const
    {
        uint64_t h = 1469598103934665603ull;

        for (uint32_t v : k)
            h = ( h ^ v) * 1099511628211ull;
        return size_t(h);
    }
};
struct TexRect
{

    uint32_t x0 = 0, y0 = 0, x1 = 0, y1 = 0;
    bool empty() const { return x0 >= x1 || y0 >= y1; }
    bool contains(const TexRect &r) const
    {
        return r.empty() || (r.x0 >= x0 && r.y0 >= y0 && r.x1 <= x1 && r.y1 <= y1);
    }
};
// Texels a batch reads on one axis: [lo, hi] before wrapping -> [first, end).   

uint32_t wrapAxis(float lo, float hi, bool bilinear, uint32_t size, uint32_t mode, uint32_t minv, uint32_t maxv, uint32_t extent, uint32_t &first, uint32_t &end)
{
    const double a = std::floor(double(lo) - (bilinear ? 0.5 : 0.0)), b = std::floor(double(hi) ) + 1;
    if (mode == 1)
    {

        first = uint32_t(std::clamp(a, 0.0, double(size - 1)));
        end = uint32_t(std::clamp(b, 0.0, double(size - 1))) + 1;
    }
    else if (mode == 2)
    {
        first = uint32_t(std::clamp(a, double(minv), double(std::max(minv, maxv))));
        end = uint32_t(std::clamp(b, double(minv), double(std::max(minv, maxv)))) + 1; 
    }
    else if (mode == 0 && a >= 0 && b < double(size))
    {
        first = uint32_t(a);
        end = uint32_t(b) + 1;
    }
    else
    {
        first = 0;
        end = extent;
        return mode == 0 ? uint32_t(std::clamp(b - a, 1.0, double(extent))) : extent;

    }
    end = std::min(end, extent);
    return end > first ? end - first : 0;
}

class WriteStamps
{
  public:
    WriteStamps() : m_pageStamp(VramBytes / 8192) {}
    void touched(Range r)
    {
        ++m_stamp;
        auto mark = [&](uint64_t first, uint64_t last) {
            for (uint64_t page = first / 8192; page * 8192 < last && page < m_pageStamp.size(); ++page)
                m_pageStamp[size_t(page)] = m_stamp;

        };
        mark(r.first, std::min<uint64_t>(r.last, VramBytes));
        if (r.last > VramBytes)
            mark(0, r.last - VramBytes);
    }
    uint64_t newest(Range r) const   
    {
        uint64_t s = 0;
        auto scan = [&](uint64_t first, uint64_t last) {   
            for (uint64_t page = first / 8192; page * 8192 < last && page < m_pageStamp.size(); ++page)
                s = std::max(s, m_pageStamp[size_t(page)]);
        };
        scan(r.first, std::min<uint64_t>(r.last, VramBytes));

        if (r.last > VramBytes)
            scan(0, r.last - VramBytes);
        return s;
    }
    uint64_t stamp() const { return m_stamp; }

  private:
    std::vector<uint64_t> m_pageStamp;  
    uint64_t m_stamp = 1;
};

template <class T> struct NoInitAllocator : std::allocator<T>
{
    template <class U> struct rebind
    {
        using other = NoInitAllocator<U>;
    };
    NoInitAllocator() = default;
    template <class U> NoInitAllocator(const NoInitAllocator<U> &) noexcept {}
    template <class U> void construct(U *) noexcept {}
    template <class U, class... A> void construct(U *p, A &&...a) { ::new (static_cast<void *>(p)) U(std::forward<A>(a)...); }
};
using PixelRows = std::vector<uint32_t, NoInitAllocator<uint32_t>>;

class UploadStore
{
   public:
    struct Image
    {
        uint32_t psm, base, bw, x0, y0, w, h;   
        PixelRows pixels;
        uint32_t written = 0;
        uint64_t serial = 0;
        mutable bool dropped = false;
        bool holds(uint32_t x, uint32_t y) const { return x - x0 < w && y - y0 < h; }
        uint32_t at(uint32_t x, uint32_t y) const { return pixels[size_t(y - y0) * w + (x - x0)]; }
    };
    uint64_t fromImages = 0, fromBits = 0, prepared = 0;
    uint64_t paintImages = 0, paintPagesSkipped = 0, paintFastPixels = 0, paintSlowPixels = 0, paintCalls = 0, paintRectPixels = 0;

    void clear()
    {
        m_current = nullptr;
        m_layouts.clear();
        for (auto &l : m_pages)
            l.clear();
        for (auto &f : m_pageFull)
            f.reset();
        m_fast = false;
    }
    std::shared_ptr<Image> add(uint32_t psm, uint32_t base, uint32_t bw, uint32_t x0, uint32_t y0, uint32_t w, uint32_t h)
    {
        finish();
        if (!w || !h)  
            return nullptr;
        auto img = std::make_shared<Image>();
        Image &n = *img;

        n.psm = psm, n.base = base, n.bw = std::max(1u, bw), n.x0 = x0, n.y0 = y0, n.w = w, n.h = h;
        n.pixels.resize( size_t(w) * h);
        m_current = img;
        return img;
    }
    void finish()
    {
        if (!m_current)
            return;
        const std::shared_ptr<Image> img = std::move( m_current);
        m_current = nullptr;
        m_fast = false;
        Image &n = *img ;
        for (uint32_t i = n.written; i < n.w * n.h; ++i)   
            n.pixels[i] = load(n.psm, n.base, n.bw, n.x0 + i % n.w, n.y0 + i / n.w);
        n.serial = ++m_serial;
        auto &list = m_layouts[key(n.psm, n.base, n.bw)];

        std::erase_if(list, [&](const std::shared_ptr<const Image> &e) {
            const bool inside = (n.psm == e->psm || n.psm == 0) && e->x0 >= n.x0 && e->y0 >= n.y0 && e->x0 + e->w <= n.x0 + n.w &&

                                e->y0 + e->h <= n.y0 + n.h;
            if (inside)
                e->dropped = true; 
            return inside;
        });
        list.push_back(img);
        if (list.size() > kMaxPerLayout)
        {
            list.front()->dropped = true;
            list.erase(list.begin());
        }
        uint32_t pw, ph;
        pageSize(n.psm, pw, ph);
        const uint32_t perRow = std::max(1u, n.bw * 64 / pw), first = n.base >> 5, spill = (n.base & 31) ? 2 : 1;

        for (uint32_t py = (n.y0 & 2047) / ph; py <= ((n.y0 + n.h - 1) & 2047) / ph; ++py)
            for (uint32_t px = n.x0 / pw; px <= (n.x0 + n.w - 1) / pw; ++px)
                for (uint32_t k = 0; k < spill; ++k)
                {
                    if (spill == 1 && pixelBits(n.psm) * pw * ph == 65536u && n.x0 <= px * pw && n.x0 + n.w >= (px + 1) * pw && (n.y0 & 2047) <= py * ph && (n.y0 & 2047) + n.h >= (py + 1) * ph )
                        m_pageFull[(first + py * perRow + px) & 511] = img;
                    auto &pageList = m_pages[(first + py * perRow + px + k) & 511];
                    if (!pageList.empty() && pageList.back() == img)
                        continue;
                    std::erase_if(pageList, [](const std::shared_ptr<const Image> &e) { return e->dropped; });
                    pageList.push_back(img);
                }
    }
    uint32_t load(uint32_t psm, uint32_t base, uint32_t bw, uint32_t x, uint32_t y)
    {
        finish() ;
        x &= 2047, y &= 2047;
        bw = std::max(1u, bw);
        const Image *e = newestOfLayout(psm, base, bw, x, y);
        if (e && !(psm == 0 && e->psm == 1) && !overwritten(*e, psm, base, bw, x, y)) // (24 bits under a 32-bit read: the bits)
        {
            ++fromImages;
            return valueOf(*e, psm, base, bw, x, y);
        }
        ++fromBits;
        return bits(psm, base, bw, x, y );
    }  
    void prepare(uint32_t psm, uint32_t base, uint32_t bw, uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1)
    {
        finish();
        m_fast = false;
        m_direct = nullptr;
        bw = std::max(1u, bw);
        if (x1 <= x0 || y1 <= y0 || x1 > 2048 || y1 > 2048)
            return;
        const uint32_t w = x1 - x0, h = y1 - y0;
        if (const auto it = m_layouts.find(key(psm, base, bw)); it != m_layouts.end())
            for (auto r = it->second.rbegin(); r != it->second.rend(); ++r)
            {
                const Image &e = **r;
                if (e.x0 >= x1 || e.y0 >= y1 || e.x0 + e.w <= x0 || e.y0 + e.h <= y0)
                    continue;
                if (e.x0 <= x0 && e.y0 <= y0 && e.x0 + e.w >= x1 && e.y0 + e.h >= y1 && !(psm == 0 && e.psm == 1) && newestOtherInRect(psm, base, bw, x0, y0, x1, y1) < e.serial)
                {
                    m_direct = &e;
                    m_fast = true;
                    m_psm = psm, m_base = base, m_bw = bw, m_x0 = x0, m_y0 = y0, m_w = w, m_h = h;
                    ++prepared;
                    return;
                }
                break;
            }
        m_scratch.assign(size_t(w) * h, 0);  
        m_from.assign(size_t(w) * h, 0);
        // The layout's images, oldest first (each texel: the newest that holds it).
        uint64_t oldest = ~0ull;
        bool covered = true;
        std::vector<const Image *> &onRect = m_onRect ;
        onRect.clear();
        if (const auto it = m_layouts.find(key(psm, base, bw)); it != m_layouts.end())
            for (const auto &e : it->second)
                if (!(e->x0 >= x1 || e->y0 >= y1 || e->x0 + e->w <= x0 || e->y0 + e->h <= y0))
                    onRect.push_back(e.get());
        const auto rows = [&](uint32_t ya, uint32_t yb) { 
            for ( const Image *e : onRect)
            {
                const uint32_t ax = std::max(x0, e->x0), ay = std::max(ya, e->y0), bx = std::min(x1, e->x0 + e->w),
                               by = std::min(yb, e->y0 + e->h);
                const bool rgbOnly = psm == 0 && e->psm == 1; // (24 bits under a 32-bit read: the bits)

                for (uint32_t y =  ay; y < by; ++y)
                {
                    const uint32_t *src = &e->pixels[size_t(y - e->y0) * e->w + (ax - e->x0)];
                    uint32_t *dst = &m_scratch[size_t(y - y0) * w + (ax - x0)];
                    uint64_t *from = &m_from[size_t(y - y0) * w + (ax - x0)];
                    for ( uint32_t i = 0; i < bx - ax; ++i)
                        dst[i] = src[i], from[i] = rgbOnly ? 0 : e->serial;
                }
            }
        };
        rows(y0, y1 );
        for (uint64_t f : m_from)
        {
            covered &= f != 0;
            oldest = std::min(oldest, f ? f : oldest);
        }
        const uint64_t newest = newestOtherInRect(psm, base, bw, x0, y0, x1, y1);
        if (!covered || newest > (oldest == ~0ull ? 0 : oldest))
        {
            if (size_t(std::count(m_from.begin(), m_from.end(), uint64_t(0))) >= 512)
            {
                prepareBits(psm, base, bw, x0, y0, x1, y1);
                return;
            }
            m_pageKnown.reset();
            const uint64_t k = key(psm, base, bw);
            std::vector<uint32_t> &fromMemory = m_fromMemory;
            fromMemory.clear();   
            for (uint32_t y = y0; y < y1; ++y)
                for (uint32_t x = x0; x < x1; ++x)
                {
                    const size_t i = size_t(y - y0) * w + (x - x0);

                    if (m_from[i] && newest < m_from[i])

                        continue;
                    if (m_from[i] && newestOtherOnPage((bitAddress(psm, base, bw, x, y) >> 16) & 511, k) <= m_from[i])
                        continue;
                    if (m_from[i] && !overwrittenSince(m_from[i], psm, base, bw, x, y))
                        continue;
                    fromMemory.push_back(uint32_t(i)); 
                }
            if (fromMemory.size() >= 512) 
            {  
                prepareBits(psm, base, bw, x0, y0, x1, y1);
                return;
            }
            for (uint32_t i : fromMemory)

            {
                m_scratch[i] = bits(psm, base, bw, x0 + i % w, y0 + i / w);
                ++fromBits;
            }
        }
        if (psm == 1)
            for (uint32_t &v : m_scratch)
                v &= 0xffffff;
        m_fast = true;
        m_psm = psm, m_base = base, m_bw = bw, m_x0 = x0, m_y0 = y0, m_w = w, m_h = h;
        ++prepared;
    }
    void prepareBits(uint32_t psm, uint32_t base, uint32_t bw, uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1,

                    const uint8_t *need = nullptr)
    {
        finish();
        m_fast = false;
        m_direct = nullptr;
        bw = std::max(1u, bw);
        if (x1 <= x0 || y1 <= y0 || x1 > 2048 || y1 > 2048)
            return;  

        const uint32_t w = x1 - x0, h = y1 - y0 ;
        ++paintCalls;
        paintRectPixels += uint64_t(w) * h;
        m_scratch.assign(size_t(w) * h, 0);
        m_set.assign(size_t(w) * h, 0);
        m_x0 = x0, m_y0 = y0, m_w = w;
        {
            const LayoutInfo &r = layoutInfo(psm);
            m_fullBits = r.bits >= 32 ? 0xffffffffu : (1u << r.bits) - 1;
            m_coverShx = r.table->shx, m_coverShy = r.table->shy;
            m_coverPerRow = std::max(1u, (bw * 64) >> m_coverShx);
            const uint32_t rows = ((y1 - 1) >> m_coverShy) + 1 ;

            m_cover.assign(size_t(rows) * m_coverPerRow, 0);
            m_coverTotal.assign(size_t(rows) * m_coverPerRow, 0);  
            for (uint32_t py = y0 >> m_coverShy; py < rows; ++py)

                for (uint32_t px = x0 >> m_coverShx; px <= std::min((x1 - 1) >> m_coverShx, m_coverPerRow - 1); ++px)
                { 
                    const uint32_t cx0 = std::max(x0, px << m_coverShx), cx1 = std::min(x1, (px + 1) << m_coverShx);
                    const uint32_t cy0 = std::max(y0, py << m_coverShy), cy1 = std::min(y1, (py + 1) << m_coverShy);
                    m_coverTotal[size_t(py) * m_coverPerRow + px] = (cx1 - cx0) * (cy1 - cy0);
                }
            // A texel not needed counts as set (painting skips it and its page sooner).
            if(need)
                for (uint32_t y = y0; y < y1; ++y)
                    for (uint32_t x = x0; x < x1; ++x)
                        if (!need[size_t(y - y0) * w + (x - x0)])
                        {
                            m_set[size_t(y - y0) * w + (x - x0)] = 0xffffffffu;
                            if ((x >> m_coverShx) < m_coverPerRow)
                                ++m_cover[size_t(y >> m_coverShy) * m_coverPerRow + (x >> m_coverShx)];
                        }

        }
        uint32_t pw, ph;
        pageSize(psm, pw, ph);
        const uint32_t perRow = std::max(1u, bw * 64 / pw), first = base >> 5, spill = (base & 31) ? 2 : 1;
        m_rectPages.reset();
        for (uint32_t py = y0 / ph; py <= (y1 - 1) / ph; ++py)
            for (uint32_t px = x0 / pw; px <= (x1 - 1) / pw; ++px)
                for (uint32_t s = 0; s < spill; ++s)
                    m_rectPages.set((first + py * perRow + px + s) & 511);
        m_paint.clear();   
        for (uint32_t p = 0; p < 512; ++p)
            if ( m_rectPages.test(p))
                for (const auto &e : m_pages[p])
                    if (!e->dropped )
                        m_paint.push_back(e.get());

        std::sort(m_paint.begin(), m_paint.end(), [](const Image *a, const Image *b) { return a->serial < b->serial; });   
        m_paint.erase(std::unique(m_paint.begin(), m_paint.end()), m_paint.end());
        const uint64_t k = key(psm, base, bw);
        static const double paintLogMs = [] {
            const char *v = std::getenv("PS2_PAINT_LOG");
            return v ? std::atof(v) : 0.0 ;
        }();
        const auto paintStart = std::chrono::steady_clock::now();
        const uint64_t fastBefore = paintFastPixels, slowBefore = paintSlowPixels, skipBefore = paintPagesSkipped;
        const bool byPage = paintByPage(psm, base, bw, x0, y0, x1, y1, k);
        for (auto it = m_paint.rbegin(); !byPage && it != m_paint.rend(); ++it)
        {
            const Image *e = *it;
            if (key(e->psm, e->base, e->bw) != k)
            {
                ++paintImages;
                paintBits(*e, psm, base, bw, x0, y0, x1, y1);
                continue;
            }

            if (e->x0 >= x1 || e->y0 >= y1 || e->x0 + e->w <= x0 || e->y0 + e->h <= y0) 
                continue;
            const uint32_t ax = std::max(x0, e->x0), ay = std::max(y0, e->y0), bx = std::min(x1, e->x0 + e->w),
                           by = std::min(y1, e->y0 + e->h);
            const bool rgbOnly = psm == 0 && e->psm == 1; // (a 24-bit upload keeps the alpha below)
            const uint32_t mask = rgbOnly ? 0xffffffu : 0xffffffffu;
            for (uint32_t y = ay; y < by; ++y)
            {
                const uint32_t *src = &e->pixels[size_t(y - e->y0) * e->w + (ax - e->x0)];
                for ( uint32_t i = 0; i < bx - ax; ++i)
                    put(ax + i, y, mask, src[i]);
            }
        }
        if(paintLogMs > 0)
        {
            const double ms = std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - paintStart).count();
            if (ms >= paintLogMs)
            {
                std::fprintf(stderr, "[paint] %.2f ms read psm %u base %x bw %u rect %u,%u-%u,%u images %zu fast %llu slow %llu skipped %llu:", ms, psm, base, bw, x0, y0, x1, y1, m_paint.size(), (unsigned long long)(paintFastPixels - fastBefore), (unsigned long long)(paintSlowPixels - slowBefore), (unsigned long long)(paintPagesSkipped - skipBefore));
                for (size_t i = 0; i < m_paint.size() && i < 12; ++i)
                {
                    const Image *e = m_paint[m_paint.size() - 1 - i];
                    std::fprintf(stderr, " [psm %u base %x bw %u %u,%u %ux%u]", e->psm, e->base, e->bw, e->x0, e->y0, e->w, e->h);
                }
                std::fputc('\n', stderr);
            }
        }
        if (psm == 1)
            for (uint32_t &v : m_scratch)
                v &= 0xffffff;
        fromImages += uint64_t(w) * h;
        m_fast = true;
        m_psm = psm, m_base = base, m_bw = bw, m_x0 = x0, m_y0 = y0, m_w = w, m_h = h;
        ++prepared;

    }
    void done()
    {
        m_fast = false;
        m_direct = nullptr;
    }   
    void loadRow(uint32_t psm, uint32_t base, uint32_t bw, uint32_t x0, uint32_t y, uint32_t count, uint32_t *out)
    {
        bw = std::max(1u, bw);
        if (m_fast && psm == m_psm && base == m_base && bw == m_bw && x0 - m_x0 < m_w && x0 + count - m_x0 <= m_w && y - m_y0 < m_h)
        {
            if (const Image *e = m_direct)
            {  
                const uint32_t *src = &e->pixels[size_t(y - e->y0) * e->w + (x0 - e->x0)];
                if (psm == 1) 
                    for (uint32_t i = 0; i < count; ++i)
                        out[i] = src[i] & 0xffffff;
                else
                    std::memcpy(out, src, size_t(count) * 4);
            }
            else
                std::memcpy(out, &m_scratch[size_t(y - m_y0) * m_w + (x0 - m_x0)], size_t(count) * 4);   
            fromImages += count;
            return;
        }
        for (uint32_t i = 0; i < count; ++i)
            out[i] = load(psm, base, bw, x0 + i, y);
    }

  private:
    static constexpr size_t kMaxPerLayout = 256;
    // A 24-bit layout reads the 32-bit uploads of its base and width too.
    static uint64_t key(uint32_t psm, uint32_t base, uint32_t bw)
    {
        return uint64_t(psm == 1 ? 0 : psm) | uint64_t(base) << 8 | uint64_t(bw) << 24;
    } 
    const Image *newestOfLayout(uint32_t psm, uint32_t base, uint32_t bw, uint32_t x, uint32_t y) const
    {
        const auto it = m_layouts.find(key(psm, base, bw));
        if (it == m_layouts.end())
            return nullptr;
        for (auto e = it->second.rbegin(); e != it->second.rend(); ++e)
            if ((*e)->holds(x, y))
                return e->get();
        return nullptr;
    }
    uint32_t valueOf( const Image &e, uint32_t psm, uint32_t, uint32_t, uint32_t x, uint32_t y) const
    {
        const uint32_t v = e.at(x, y);
        return psm == 1 ? v & 0xffffff : v;
    }
    bool overwritten(const Image &e, uint32_t psm, uint32_t base, uint32_t bw, uint32_t x, uint32_t y) const
    {   
        return overwrittenSince(e.serial, psm, base, bw, x, y);
    }
    bool overwrittenSince(uint64_t serial, uint32_t psm, uint32_t base, uint32_t bw, uint32_t x, uint32_t y) const
    {
        const uint32_t a = bitAddress(psm, base, bw, x, y), n = pixelBits(psm);
        const auto &list = m_pages[(a >> 16) & 511];
        const uint64_t k = key(psm, base, bw);
        for (auto it =  list.rbegin(); it != list.rend() && (*it)->serial > serial; ++it)
        {
            const Image &m = **it;
            if (m.dropped || key(m.psm, m.base, m.bw) == k)
                continue;
            for (uint32_t b = 0; b < n; b += 4)
            {
                uint32_t mx, my, index;
                if(pixelOfBit(m.psm, m.base, m.bw, (a + b) & 0x1ffffff, mx, my, index) && m.holds(mx, my))
                    return true;
            }
        }
        return false;
    } 
    uint64_t newestOtherOnPage(uint32_t page, uint64_t k)
    {
        if (!m_pageKnown.test(page))
        {
            uint64_t newest = 0;
            for (const auto &e : m_pages[page])
                if (!e->dropped && key(e->psm, e->base, e->bw) != k)
                    newest = std::max(newest, e->serial);
            m_pageNewest[page] = newest;

            m_pageKnown.set( page);
        }
        return m_pageNewest[page];
    }
    uint64_t newestOtherInRect(uint32_t psm, uint32_t base, uint32_t bw, uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1) const
    {
        uint32_t pw, ph ;
        pageSize(psm, pw, ph);
        const uint32_t perRow = std::max(1u, bw * 64 / pw), first = base >> 5, spill = (base & 31) ? 2 : 1;
        const uint64_t k = key(psm, base, bw);
        uint64_t newest = 0;
        for (uint32_t py = y0 / ph; py <= (y1 - 1) / ph; ++py)
            for (uint32_t px = x0 / pw; px <= (x1 - 1) / pw; ++px)
                for(uint32_t s = 0; s < spill; ++s)
                    for (const auto &e : m_pages[(first + py * perRow + px + s) & 511])

                        if (!e->dropped && key(e->psm, e->base, e->bw) != k)
                            newest = std::max(newest, e->serial);
        return newest;
    }
    struct PairTable   
    {
        std::vector<uint32_t> first; // per texel (y << shx | x): its pieces [first[i], first[i + 1])
        std::vector<uint32_t> pieces; // sx | sy << 7 | index << 14 | at << 19 | len << 24
    };
    static const PairTable &pairTable(uint32_t readPsm, uint32_t uploadPsm)
    {  
        static std::array<std::unique_ptr<PairTable>, 64 * 64> tables;
        std::unique_ptr<PairTable> &slot = tables[(readPsm & 63) * 64 + (uploadPsm & 63)];
        if (!slot )
        {
            auto tab = std::make_unique<PairTable>();
            const LayoutInfo &r = layoutInfo(readPsm), &le = layoutInfo(uploadPsm);
            const PageTable &tr = *r.table;
            const uint32_t texels = 1u << (tr.shx + tr.shy), unitShiftE = uint32_t(std::countr_zero(le.unit));
            tab->first.resize(texels + 1);
            for (uint32_t i = 0; i < texels; ++i)
            {
                tab->first[i] = uint32_t(tab->pieces.size());
                const uint32_t start = tr.offsets[i] + r.low;
                for (uint32_t done = 0; done < r.bits;)
                {
                    const uint32_t b = start + done, inUnit = b & (le.unit - 1) ;
                    if ( inUnit < le.low || inUnit >= le.low + le.bits)
                    {  
                        done += inUnit < le.low ? le.low - inUnit : le.unit - inUnit;
                        continue;
                    }
                    const uint32_t xy = le.inverse[b >> unitShiftE], index = inUnit - le.low,
                                   len = std::min(r.bits - done, le.bits - index);
                    tab->pieces.push_back((xy & 0x7f) | ((xy >> 16) & 0x7f) << 7 | index << 14 | done << 19 | len << 24);
                    done += len;
                }
            }
            tab->first[texels] = uint32_t(tab->pieces.size() );
            slot = std::move(tab);
        }
        return *slot;
    }

    bool paintByPage(uint32_t psm, uint32_t base, uint32_t bw, uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, uint64_t k)
    {
        if((base & 31) != 0)
            return false;
        const LayoutInfo &r = layoutInfo(psm);
        const PageTable &tr = *r.table;
        struct Source
        {
            const Image *e;
            const LayoutInfo *le;
            uint32_t absPage0, perRow, shx, shy, unitShift;
            bool own;
            const PairTable *pair;
        };
        std::vector<Source> sources;
        for (auto it = m_paint.rbegin(); it != m_paint.rend(); ++it)  
        {
            const Image *e = *it;
            const bool own = key( e->psm, e->base, e->bw) == k;
            const PageTable &te = pageTable(e->psm);
            const uint32_t perRowE = (e->bw * 64) >> te.shx;
            if (!own && ((e->base & 31) != 0 || perRowE == 0 || e->x0 + e->w > (perRowE << te.shx) || e->y0 + e->h > 2048))
                return false;
            const LayoutInfo &le = layoutInfo(e->psm);
            sources.push_back({e, &le, e->base >> 5, perRowE, te.shx, te.shy, uint32_t(std::countr_zero(le.unit)), own,
                               own ? nullptr : &pairTable(psm, e->psm)}); // (made here: the pages below run in parallel)
        }
        std::vector<uint32_t> pages;
        for (uint32_t py = y0 >> tr.shy; py <= (y1 - 1) >> tr.shy; ++py)
            for (uint32_t px = x0 >> tr.shx; px <= std::min((x1 - 1) >> tr.shx, m_coverPerRow - 1); ++px)
                pages.push_back(py * m_coverPerRow + px);
        const uint32_t mxR = (1u << tr.shx) - 1, myR = (1u << tr.shy) - 1, w = x1 - x0 ;
        std::atomic<uint64_t> painted{0};
        auto paintPage = [&](uint32_t P) {
            const uint32_t abs = ((base >> 5) + P) & 511;
            const uint32_t ox = (P % m_coverPerRow) << tr.shx, oy = (P / m_coverPerRow) << tr.shy;
            const uint32_t cx0 = std::max(x0, ox), cx1 = std::min(x1, ox + (1u << tr.shx)), cy0 = std::max(y0, oy),
                           cy1 = std::min(y1, oy + (1u << tr.shy));
            if (cx0 >= cx1 || cy0 >= cy1)
                return;

            struct On
            {
                const Source *s;
                uint32_t sx0, sy0, ax, bx, ay, by;
            };
            std::vector<On> on;
            for(const Source &s : sources)
            {
                const Image &e = *s.e;
                if (s.own)
                {
                    const uint32_t ax = std::max(cx0, e.x0), bx = std::min(cx1, e.x0 + e.w), ay = std::max(cy0, e.y0),
                                   by = std::min(cy1, e.y0 + e.h);
                    if (ax < bx && ay < by)
                        on.push_back({&s, 0, 0, ax, bx, ay, by});
                    continue;
                }
                const auto full = m_pageFull[abs].lock();
                if (full && !full->dropped && full->serial > e.serial)

                    continue;
                const uint32_t ep = (abs - s.absPage0) & 511, sx0 = (ep % s.perRow) << s.shx, sy0 = (ep / s.perRow) << s.shy;
                const uint32_t ax = std::max(e.x0, sx0), bx = std::min(e.x0 + e.w, sx0 + (1u << s.shx)), ay = std::max(e.y0, sy0),
                               by = std::min(e.y0 + e.h, sy0 + (1u << s.shy) );
                if (ax < bx && ay < by)   
                    on.push_back({&s, sx0, sy0, ax, bx, ay, by});

            }
            if (on.empty())
                return;

            uint64_t n = 0;
            for (uint32_t ry =  cy0; ry < cy1; ++ry)
                for (uint32_t rx =  cx0; rx < cx1; ++rx)
                {
                    const size_t i = size_t(ry - y0) * w + (rx - x0);

                    const uint32_t texel = ( (ry & myR) << tr.shx) | (rx & mxR);
                    for (const On &o : on)
                    {
                        if ((m_set[i] & m_fullBits) == m_fullBits)  
                            break;
                        const Image &e = *o.s->e;

                        if (o.s->own)  
                        {
                            if (rx >= o.ax && rx < o.bx && ry >= o.ay && ry < o.by)
                                put( rx, ry, psm == 0 && e.psm == 1 ? 0xffffffu : 0xffffffffu, e.at(rx, ry));
                            continue;
                        }
                        const PairTable &pt = *o.s->pair;
                        uint32_t mask = 0, value = 0;
                        for (uint32_t k = pt.first[texel]; k < pt.first[texel + 1]; ++k)
                        {
                            const uint32_t c = pt.pieces[k], sx = o.sx0 | (c & 0x7f), sy = o.sy0 | ((c >> 7) & 0x7f);
                            if (sx < o.ax || sx >= o.bx || sy < o.ay || sy >= o.by)
                                continue;
                            const uint32_t index = (c >> 14) & 31, at = (c >> 19) & 31, len = c >> 24;
                            const uint32_t m = (len >= 32 ? 0xffffffffu : (1u << len) - 1) << at;
                            mask |= m;
                            value |= ( (e.at(sx, sy) >> index) << at) & m;
                        }
                        if (mask)
                            put(rx, ry, mask, value);
                    }
                    ++n;
                }

            painted += n;
        };
        // (threads only for a big rectangle: a small one is slower in parallel)
        if (pages.size() >= 4 && uint64_t(x1 - x0) * (y1 - y0) >= 16384)
            std::for_each(std::execution::par, pages.begin(), pages.end(), paintPage);
        else  
            std::for_each(pages.begin(), pages.end(), paintPage);
        paintFastPixels += painted;
        return true;
    }
    void put(uint32_t rx, uint32_t ry, uint32_t mask, uint32_t value)
    {
        const size_t i = size_t(ry - m_y0) * m_w + (rx - m_x0);
        uint32_t &set = m_set[i];
        const uint32_t write = mask & ~set;
        if (!write)
            return;
        m_scratch[i] = (m_scratch[i] & ~write) | (value & write);
        const bool was = (set & m_fullBits) == m_fullBits;
        set |= write;

        if (!was && (set & m_fullBits) == m_fullBits && (rx >> m_coverShx) < m_coverPerRow)
            ++m_cover[(ry >> m_coverShy) * m_coverPerRow + (rx >> m_coverShx)];
    }
    void paintBits(const Image &e, uint32_t psm, uint32_t base, uint32_t bw, uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1)
    {
        const LayoutInfo &r = layoutInfo(psm);
        const uint32_t n = pixelBits(e.psm), w = x1 - x0;
        uint32_t pw, ph;
        pageSize(e.psm, pw, ph);
        const PageTable &te = pageTable(e.psm), &tr = *r.table;
        const uint32_t mxE = (1u << te.shx) - 1, myE = (1u << te.shy) - 1, shiftE = e.psm == 27 || e.psm == 36 ? 24 : e.psm == 44 ? 28 : 0;
        const uint32_t perRowR = std::max(1u, (std::max(1u, bw) * 64) >> tr.shx), unitShift = uint32_t(std::countr_zero(r.unit));
        const bool aligned = (e.base & 31) == 0 && (base & 31) == 0;
        const LayoutInfo &le = layoutInfo(e.psm);
        const uint32_t unitShiftE = uint32_t( std::countr_zero(le.unit));
        const uint32_t perRow = std::max(1u, e.bw * 64 / pw), first = e.base >> 5, spill = (e.base & 31) ? 2 : 1;
        for (uint32_t py = e.y0 / ph; py <= (e.y0 + e.h - 1) / ph; ++py)
            for (uint32_t px = e.x0 / pw; px <= (e.x0 + e.w - 1) / pw; ++px)
            {
                const uint32_t page = first + py * perRow + px;
                bool on = false, gone = true;
                for (uint32_t s = 0; s < spill; ++s)  
                {
                    on |= m_rectPages.test((page + s) & 511);
                    const auto full = m_pageFull[(page + s) & 511].lock();   
                    gone &= full && !full->dropped && full->serial > e.serial;
                }
                if (!on || gone)
                {
                    paintPagesSkipped += on;
                    continue;
                }
                const uint32_t ax = std::max(e.x0, px * pw), bx = std::min(e.x0 + e.w, (px + 1) * pw), ay = std::max(e.y0, py * ph),
                               by = std::min(e.y0 + e.h, (py + 1) * ph);
                if (aligned && ax < bx && ay < by && (ax & 2047) >> te.shx == ((bx - 1) & 2047) >> te.shx && (ay & 2047) >> te.shy == ((by - 1) & 2047) >> te.shy)
                {
                    const uint32_t pageE = ((ay & 2047) >> te.shy) * ((e.bw * 64) >> te.shx) + ((ax & 2047) >> te.shx);
                    const uint32_t rel = ((e.base * 2048 + pageE * 65536) - base * 2048) & 0x1ffffff, pageR = rel >> 16;
                    if (pageR >= m_coverTotal.size() || m_cover[pageR] >= m_coverTotal[pageR])
                    {
                        ++paintPagesSkipped;
                        continue;

                    }
                    const uint32_t ox = (pageR % perRowR) << tr.shx, oy = (pageR / perRowR) << tr.shy;
                    const uint32_t cx0 = std::max(x0, ox), cx1 = std::min(x1, ox + (1u << tr.shx)), cy0 = std::max(y0, oy),
                                   cy1 = std::min(y1, oy + (1u << tr.shy));
                    const uint32_t sx0 = (ax & ~mxE), sy0 = (ay & ~myE), mxR = (1u << tr.shx) - 1, myR = (1u << tr.shy ) - 1;
                    paintFastPixels += uint64_t(cx1 > cx0 ? cx1 - cx0 : 0) * (cy1 > cy0 ? cy1 - cy0 : 0);
                    for (uint32_t ry = cy0; ry < cy1; ++ry)
                        for (uint32_t rx = cx0; rx < cx1; ++rx)
                        {
                            const size_t i = size_t(ry - y0) * w + (rx - x0);
                            if ((m_set[i] & m_fullBits) == m_fullBits)
                                continue;
                            const uint32_t start = tr.offsets[((ry & myR) << tr.shx) | (rx & mxR)] + r.low;
                            for (uint32_t done = 0; done < r.bits;)
                            {
                                const uint32_t b = start + done, inUnit = b & (le.unit - 1);   
                                if (inUnit < le.low || inUnit >= le.low + le.bits) // (bits no pixel of the upload's layout has)
                                {
                                    done += inUnit < le.low ? le.low - inUnit : le.unit - inUnit;
                                    continue;
                                }
                                const uint32_t xy = le.inverse[b >> unitShiftE], sx = sx0 | (xy & 0xffff), sy = sy0 | (xy >> 16),
                                                index =  inUnit - le.low, len = std::min(r.bits - done, le.bits - index);
                                if (sx >= ax && sx < bx && sy >= ay && sy < by)
                                    put(rx, ry, (len >= 32 ? 0xffffffffu : (1u << len) - 1) << done, (e.at(sx, sy) >> index) << done);
                                done += len;
                            } 
                        }
                    continue;
                }
                paintSlowPixels += uint64_t(bx - ax) * (by - ay);
                for (uint32_t y = ay; y < by; ++y)

                    for (uint32_t x = ax; x < bx; ++x)
                    {
                        const uint32_t v = e.at(x, y), a = bitAddress(e.psm, e.base, e.bw, x & 2047, y & 2047);
                        for (uint32_t done = 0; done < n;)
                        {
                            uint32_t rx, ry, index;
                            if (!pixelOfBit(r, base, bw, (a + done) & 0x1ffffff, rx, ry, index))
                            {

                                done += 4;
                                continue;   
                            }
                            const uint32_t len = std::min(n - done, r.bits - index);
                            if (rx - x0 < w && ry - y0 < y1 - y0)
                                put(rx, ry, (len >= 32 ? 0xffffffffu : (1u << len) - 1) << index, (v >> done) << index);
                            done += len;
                        } 
                    }
            }

    }
    uint32_t bits(uint32_t psm, uint32_t base, uint32_t bw, uint32_t x, uint32_t y) const
    {
        const uint32_t a = bitAddress(psm, base, bw, x, y), n = pixelBits(psm);
        uint32_t value = 0;
        for (uint32_t done = 0; done < n;)
        {
            const uint32_t b = ( a + done) & 0x1ffffff;
            uint32_t got = std::min(n - done, 4 - (b & 3));
            const auto &list = m_pages[(b >> 16) & 511] ;
            for (auto it = list.rbegin(); it != list.rend(); ++it )
            {
                const Image &m = **it;
                uint32_t mx, my, index;
                if (m.dropped || !pixelOfBit(layoutInfo(m.psm), m.base, m.bw, b, mx, my, index) || !m.holds(mx, my))
                    continue;
                got = std::min(n - done, pixelBits(m.psm) - index);
                const uint32_t mask = got >= 32 ? 0xffffffffu : (1u << got) - 1;
                value |= ((m.at(mx, my) >> index) & mask) << done;
                break ;
            }
            done += got;
        }
        return value;
    }

    std::unordered_map<uint64_t, std::vector<std::shared_ptr<const Image>>> m_layouts;
    std::array<std::vector<std::shared_ptr<const Image>>, 512> m_pages;
    std::array<std::weak_ptr<const Image>, 512> m_pageFull; // per page: the newest upload that wrote all of it
    std::shared_ptr<Image> m_current;
    uint64_t m_serial = 0;
    std::vector<uint32_t> m_scratch;
    std::vector<uint64_t> m_from;
    std::vector<uint32_t> m_fromMemory;
    std::vector<const Image *> m_onRect;
    std::bitset<512> m_rectPages;
    std::bitset<512> m_pageKnown;
    std::vector<uint32_t> m_set, m_cover, m_coverTotal;
    uint32_t m_fullBits = 0, m_coverShx = 0, m_coverShy = 0, m_coverPerRow = 1;
    std::array<uint64_t, 512> m_pageNewest{};
    std::vector<const Image *> m_paint;
    bool m_fast = false;
    const Image *m_direct = nullptr;
    uint32_t m_psm = 0, m_base = 0, m_bw = 0, m_x0 = 0, m_y0 = 0, m_w = 0, m_h = 0;
};

uint32_t pack4(uint32_t r, uint32_t g, uint32_t b, uint32_t a) { return r | g << 8 | b << 16 | a << 24; }
uint32_t decode16(uint32_t c)
{
    return pack4((c & 31) << 3, ((c >> 5) & 31) << 3, ((c >> 10) & 31) << 3, ((c >> 15) & 1) << 7);
} 
uint32_t texaAlpha(const Params &p, uint32_t psm, uint32_t v)
{
    uint32_t a = v >> 24;
    const bool zero = (v & 0xffffff) == 0;
    if (psm == 1)  
        a = p[35] && zero ? 0 : p[34];
    if (psm == 2 || psm == 10)
        a = ( a & 128) ? p[36] : p[35] && zero ? 0 : p[34];
    return (v & 0xffffff) | (a << 24);
}
// CLUT entry of texel index `index` of TEX0 (p[20..42]), with TEXA.
template <class Mem> uint32_t clutColor(Mem &mem, const Params &p, uint32_t index)
{
    const bool pal16 = p[28] == 2 || p[28] == 10;
    const uint32_t mask = pal16 ? 511 : 255;
    if (p[29] == 0)
    {
        const uint32_t base = (p[30] & (pal16 ? 31 : 15)) << 4;
        index = (index + base) & mask;
        index = (index & ~24u) | ((index & 8) << 1) | ((index & 16) >> 1);
    }
    const uint32_t c = mem.load(p[28], p[27], std::max(1u, p[31]), p[32] + (index & 15), p[33] + (index >> 4));
    return texaAlpha(p, p[28], pal16 ? decode16(c) : c);
}
// GS texel (x, y) of TEX0 (p[20..42]) after CLUT and TEXA (the texel rules of render_draw.hlsl).
template <class Mem> uint32_t rawTexel(Mem &mem, const Params &p, uint32_t x, uint32_t y)
{
    auto texa = [&](uint32_t psm, uint32_t v) { return texaAlpha(p, psm, v); };
    const uint32_t psm = p[22], v = mem.load(psm, p[20], p[21], x, y);
    if (psm == 0 || psm == 1 || psm == 48 || psm == 49)

        return texa(psm, v) ;
    if (storageBits(psm) == 16)
        return texa( psm, decode16(v));
    if (psm == 19 || psm == 20 || psm == 27 || psm == 36 || psm == 44)
        return clutColor(mem, p, psm == 20 || psm == 36 || psm == 44 ? v & 15 : v);
    return 0xffff00ff;
}

struct TexEntry
{
    uint32_t width = 0, height = 0;
    Range ranges[2]{};
    int rangeCount = 0;
    uint64_t stamp = 0;
    TexRect decoded;
    uint64_t lastUse = 0;
    uint64_t ownerEpoch = 0, ownerSurface = 0;
    TexRect ownerRect;
    rdraw::TextureId tex = 0;

    struct Version
    {
        uint64_t hash = 0, lastUse = 0;
        TexRect rect;
        rdraw::TextureId tex = 0;
    };
    std::array<Version, 4> versions{};
};

struct DrawKey
{
    Params p{};
    Surface *color = nullptr, *depth = nullptr;
    bool lines = false, feedback = false;
    rdraw::Rect scissor{};
    bool operator==(const DrawKey &o) const
    {
        return p == o.p && color == o.color && depth == o.depth && lines == o.lines && feedback == o.feedback &&
               scissor.x0 == o.scissor.x0 && scissor.y0 == o.scissor.y0 && scissor.x1 == o.scissor.x1 && scissor.y1 == o.scissor.y1;
    }
};

rdraw::Format formatOf(uint32_t psm)
{
    switch (psm)
    {
    case 1: return rdraw::Format::Color24;
    case 2:
    case 10: return rdraw::Format::Color16;   

    case 48: return rdraw::Format::Depth32;
    case 49: return rdraw::Format::Depth24;
    case 50:
    case 58: return rdraw::Format::Depth16;
    default: return rdraw::Format::Color32;
    }
}

struct NativeKeys
{
    std::vector<uint64_t> frames, colors, depths; // key = index + 1
    static uint32_t key(std::vector<uint64_t> &list, uint64_t value )

    {
        for (size_t i = 0; i < list.size(); ++i)
            if (list[i] == value)

                return uint32_t(i + 1);
        list.push_back(value);
        return uint32_t(list.size());

    }
};
NativeKeys g_nativeKeys;

rdraw::NativeContext nativeContextOf(const GSContext &g)
{
    rdraw::NativeContext c;
    c.frame = NativeKeys::key(g_nativeKeys.frames, g.frame.fbp);
    c.color = NativeKeys::key(g_nativeKeys.colors, uint64_t(g.frame.fbp) | uint64_t(g.frame.fbw) << 32 | uint64_t(g.frame.psm) << 40);
    c.depth = NativeKeys::key(g_nativeKeys.depths, uint64_t(g.zbuf.zbp) | uint64_t(g.zbuf.psm) << 32);
    c.colorKnown = rtrans::colorFormat(g.frame.psm, c.colorFormat);
    c.depthFormat = rtrans::depthFormat(g.zbuf.psm);
    c.keepMask = g.frame.fbmsk;
    c.depthWrite = !g.zbuf.zmask;
    c.depthOn = ((g.test >> 16) & 1) != 0;
    c.depthTest = rdraw::DepthTest((g.test >> 17) & 3) ;
    c.offsetX = float(g.xyoffset.ofx) / 16.0f;
    c.offsetY = float(g.xyoffset.ofy) / 16.0f;
    c.scissor = {g.scissor.x0, g.scissor.y0, uint32_t(g.scissor.x1) + 1, uint32_t(g.scissor.y1) + 1};
    c.wrapU = rtrans::wrapU(g.clamp);
    c.wrapV = rtrans::wrapV(g.clamp);
    c.bilinear = rtrans::bilinear(g.tex1);
    c.alphaHigh = (g.fba & 1) != 0;
    return c;
}
rdraw::NativeEnv nativeEnvOf(const RenderState &s)
{
    rdraw::NativeEnv e;
    e.ctx[0] = nativeContextOf(s.ctx[0]);
    e.ctx[1] = nativeContextOf(s.ctx[1]);
    e.fogColor = s.fogcol;
    return e;
}
GSContext bindContextOf(const rdraw::NativeContext &c)
{

    GSContext g{};
    if (c.color && c.color <= g_nativeKeys.colors.size())
    {

        const uint64_t v = g_nativeKeys.colors[c.color - 1];
        g.frame.fbp = uint32_t(v & 0xFFFFFFFFu);
        g.frame.fbw = uint8_t((v >> 32) & 0xFF) ;
        g.frame.psm = uint8_t((v >> 40) & 0xFF);
    }
    if (c.depth && c.depth <= g_nativeKeys.depths.size())
    {
        const uint64_t v = g_nativeKeys.depths[c.depth - 1];
        g.zbuf.zbp = uint32_t(v & 0xFFFFFFFFu);
        g.zbuf.psm = uint8_t((v >> 32) & 0xFF);
    }
    g.scissor.x0 = uint16_t(c.scissor.x0);
    g.scissor.y0 = uint16_t(c.scissor.y0);
    g.scissor.x1 = uint16_t(c.scissor.x1 - 1);
    g.scissor.y1 = uint16_t(c.scissor.y1 - 1);
    return g;
}
struct DisplayDesc
{
    uint32_t fbp = 0, base = 0, bw = 0, psm = 0; // the shown buffer (pages, blocks, 64-pixel units, format)
    uint32_t x = 0, y = 0, w = 0, h = 0;         // its shown rectangle (pixels; h: the whole picture)
    bool fields = false;                         // interlaced fields: one picture is h / 2 rows
    uint32_t contextBases[2] = {};
    bool preferred = false;
    uint32_t preferredFbp = 0, preferredBw = 0, preferredDest = 0;   
    uint64_t vsyncTick = 0;
};

bool displayOf(const GSPresentationRequest &r, DisplayDesc &out)
{
    struct Source
    {
        uint32_t fbp, fbw, psm, x, y, w, h;
        bool valid;
    };
    auto decode = [&](uint64_t f, uint64_t d, bool enabled ) {
        Source s{uint32_t(f & 511 ),
                uint32_t((f >> 9) & 63),
                uint32_t((f >> 15) & 31),

                uint32_t((f >> 32) & 2047),
                uint32_t((f >> 43) & 2047),
                uint32_t(((d >> 32) & 4095) + 1) / uint32_t(((d >> 23) & 15) + 1),
                uint32_t(((d >> 44) & 2047) + 1),  
                false};
        s.valid = enabled && (s.fbw || ((d >> 32) & 4095) || ((d >> 44) & 2047) || ((d >> 23) & 15));
        if (s.w < GSGameHeuristics::kDisplayMinSize || s.h < GSGameHeuristics::kDisplayMinSize)
        {

            s.w = GSGameHeuristics::kDisplayDefaultWidth; 
            s.h =  GSGameHeuristics::kDisplayDefaultHeight; 
        }
        s.w = std::min(s.w, GSGameHeuristics::kDisplayMaxWidth);
        s.h = std::min(s.h, GSGameHeuristics::kDisplayMaxHeight);
        return s;
    };
    const Source a = decode( r.dispfb1, r.display1, r.pmode & 1), b = decode(r.dispfb2, r.display2, r.pmode & 2);

    if (!a.valid && !b.valid)
        return false;
    const Source &s = a.valid ? a : b;
    out =  {};  
    out.fbp = s.fbp;

    out.base = s.fbp * 32;   
    out.bw = s.fbw;
    out.psm = s.psm;
    out.x = s.x, out.y = s.y, out.w = s.w, out.h = s.h;
    out.fields = (r.smode2 & 3) == 3;
    for (int i = 0; i < 2; ++i)
        out.contextBases[i] = r.contextFrames[i].fbp * 32;
    out.preferred = r.hasPreferredSource;
    out.preferredFbp = r.preferredSource.fbp;
    out.preferredBw = r.preferredSource.fbw;
    out.preferredDest = r.preferredDestFbp;
    out.vsyncTick =  r.vsyncTick;
    return true;
}

GSTex0Reg tex0Of(uint64_t v)
{

    GSTex0Reg t;  
    t.tbp0 = uint32_t(v & 0x3FFF);
    t.tbw = uint8_t((v >> 14) & 0x3F);
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


rdraw::DrawSetup drawStateOf(const Params &p)
{
    using namespace rdraw;
    DrawSetup s;
    s.primitive = p[0] == 0 ? Primitive::Point : p[0] <= 2 ? Primitive::Line : p[0] <= 5 ? Primitive::Triangle : Primitive::Sprite;
    s.gouraud = (p[1] & 1) != 0;
    s.fog = ( p[1] & 4) != 0;
    s.fogColor = p[13];
    s.colorFormat = formatOf(p[4]);
    s.keepMask = p[5];
    s.alphaHigh = p[12] != 0;
    s.depthFormat = formatOf(p[7]);
    s.depthWrite = !p[8];
    const uint32_t test = p[9];
    s.depthTest = DepthTest((test >> 17) & 3);
    s.alphaTest.on = (test & 1) != 0;
    s.alphaTest.compare =  Compare((test >> 1) & 7);
    s.alphaTest.reference = uint8_t((test >> 4) & 255);
    s.alphaTest.fail = AlphaFail((test >> 12) & 3);
    s.targetAlphaTest.on = (test & 16384) != 0;
    s.targetAlphaTest.bit = ((test >> 15) & 1) != 0;
    auto input = [](uint32_t v) { return v == 0 ? BlendInput::Source : v == 1 ? BlendInput::Target : BlendInput::Zero; };
    const uint32_t alpha = p[10], c = (alpha >> 4) & 3;
    s.blend.on = (p[1] & 8) != 0;
    s.blend.a = input(alpha & 3);
    s.blend.b = input((alpha >> 2) & 3);

    s.blend.c = c == 0 ? BlendFactor::SourceAlpha : c == 1 ? BlendFactor::TargetAlpha : BlendFactor::Fixed;
    s.blend.d = input((alpha >> 6) & 3);
    s.blend.fixed = uint8_t(p[11]);
    s.blend.onlyHighAlpha = (p[1] & 64) != 0;
    if (p[1] & 2)
    {
        Texturing &t = s.texture;
        t.on = true;
        t.width = uint16_t(p[23]);

        t.height = uint16_t(p[24]);
        t.function = TexFunction(p[26] & 3);
        t.textureAlpha = p[25] != 0;
        t.fixedUv = (p[1] & 16) != 0;
        t.bilinear = (p[1] & 32) != 0;
        t.wrapU =  Wrap(p[37] & 3);
        t.wrapV = Wrap(p[38] & 3);
        t.minU = uint16_t(p[39]);
        t.maxU = uint16_t(p[40]);
        t.minV = uint16_t(p[41]); 
        t.maxV = uint16_t(p[42]);
        t.alphaMode = p[22] == 1 ? TexAlpha::Rgb24 : (p[22] == 2 || p[22] == 10) ? TexAlpha::Rgba16 : TexAlpha::AsIs;
        t.alpha0 = uint8_t(p[34]);
        t.blackClear = p[35] != 0;
        t.alpha1 = uint8_t(p[36]);
    }
    return s;   
}

const char *targetName(bool depth, uint32_t base, uint32_t bw)
{
    if (depth)
        return "depth buffer";
    switch (base)
    {   
    case 0x0000: return bw == 10 ? "display buffer 0" : "target 0x0000";
    case 0x0A00: return bw == 10 ? "scene buffer" : "target 0x0A00";
    case 0x1400: return bw == 10 ? "display buffer 1" : "target 0x1400";
    case 0x2760: return "hit ring buffer";
    case 0x2800: return "glow buffer";
    case 0x2C00: return "glow buffer 2";
    case 0x3000:
    case 0x3100:
    case 0x3200:   
    case 0x3300: return "blur step buffer";
    default: return "target";
    }
}

constexpr uint32_t kEffectMaxScale = 2;
bool effectBuffer(uint32_t base)
{
    return base == 0x2760 || base == 0x2800 || base == 0x2C00 || base == 0x3000 || base == 0x3100 || base == 0x3200 ||
           base == 0x3300;
}

const char *reinterpretPass(uint32_t texturePsm, uint32_t targetPsm)
{
    const bool colour = targetPsm <= 1, depth = targetPsm == 48 || targetPsm == 49;
    if (colour && (texturePsm == 0 || texturePsm == 1))

        return "colour copy";
    if (colour && texturePsm == 0x14)
        return "colour as 4-bit indices";
    if (colour && texturePsm == 0x13)
        return "colour as 8-bit indices";
    if (depth && texturePsm == 0x14)
        return "depth as 4-bit indices";
    if (depth && texturePsm == 0x13)
        return "depth as 8-bit indices";
    if (depth && (texturePsm == 0 || texturePsm == 1))
        return "depth as colour";  

    return nullptr;
}

void warn(uint64_t &count, const char *what)
{
    if ((++count & (count - 1)) == 0)
        std::fprintf(stderr, "[render] %s (%llu so far)\n", what, (unsigned long long)count);
}
}

using namespace render_detail;

class RenderBackend final : public GSRasterBackend, public GSAsyncPresenter
{
  public:
    RenderBackend();
    ~RenderBackend() override;

    void Initialize(uint8_t *vram, uint32_t vramSize) override;
    void Reset() override;
    void Submit(const GSPrimitiveBatch &batch) override;
    void BeginTransfer(const GSTransferCommand &command) override;
    void UploadImage(const uint8_t *data, uint32_t sizeBytes) override;
    void Flush() override;
    void TextureFlush() override {}
    void Sync(GSSyncReason reason) override;
    PresentationFrame Present(const GSPresentationRequest &request) override;
    bool ClearFramebuffer(const GSContext &context, uint32_t rgba) override;
    uint32_t ConsumeLocalToHostBytes(uint8_t *dst, uint32_t maxBytes) override;
    uint32_t ReadVram(uint32_t psm, uint32_t base, uint32_t bw, uint32_t x, uint32_t y) const override;
    void WriteVram(uint32_t psm, uint32_t base, uint32_t bw, uint32_t x, uint32_t y, uint32_t value) override;
    void SnapshotVram(std::vector<uint8_t> &out) const override;
    GSTransferSnapshot GetTransferSnapshot() const override;
    bool PresentBegin(const GSPresentationRequest &request) override ;
    bool PresentPoll(PresentationFrame &out) override;
    void runCommand(RenderCmd &cmd, const RenderState &state);

  private:
    void submitLocked(const GSPrimitiveBatch &batch);
    void beginTransferLocked(const GSTransferCommand &command);
    void uploadImageLocked(const uint8_t *data, uint32_t sizeBytes);

    struct Impl;
    std::unique_ptr<Impl> m;
};

struct RenderBackend::Impl
{
    mutable std::mutex mutex;
    RenderBackend *self = nullptr;
    bool initialized = false;
    rdraw::Core core;
    uint32_t scale() const { return core.scale(); }
    std::vector<uint32_t> layoutTable;

    std::vector<std::unique_ptr<Surface>> surfaces;
    std::vector<uint32_t> fullScaleEffects;
    WriteStamps stamps;
    // The uploads, the texture source (no GS memory).
    UploadStore tex;
    std::shared_ptr<UploadStore::Image> upload;
    void writeImage(uint32_t psm, uint32_t base, uint32_t bw, uint32_t x0, uint32_t y0, uint32_t w, uint32_t h, const uint32_t *pixels)
    {
        auto img = tex.add(psm, base, bw, x0, y0, w, h);
        if (!img)

            return;
        std::memcpy(img->pixels.data(), pixels, size_t(w) * h * 4);
        img->written = w * h;
        tex.finish();
    }
    std::unordered_map<TexKey, TexEntry, TexKeyHash> textures;

    uint64_t useClock = 0;
    static constexpr size_t MaxTextures = 1024;
    uint64_t writeSerial = 0;
    uint64_t surfaceIds = 0;
    std::vector<uint64_t> blockOwner = std::vector<uint64_t>(16384, 0);
    uint64_t ownerEpoch = 1;
    std::vector<uint32_t> ownerScratch ;
    std::vector<std::pair<Surface *, uint32_t>> directScratch;
    std::shared_ptr<const std::vector<uint8_t>> movie;
    uint32_t movieWidth = 0, movieHeight = 0, movieX = 0, movieY = 0;
    uint32_t moviePlaced = 0;
    bool movieOrigin = false;
    uint64_t movieAt = 0;
    uint8_t movieBlock[16 * 16 * 4];
    void markDrawn(Surface &t, uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1) 
    {
        const ZoneTimer zone(this, ZMark);
        x1 = std::min(x1, 2048u);

        y1 = std::min(y1, 2048u);
        if (x0 >= x1 || y0 >= y1)
            return;

        uint32_t *m = t.markRect;
        if (t.markEpoch == ownerEpoch && x0 >= m[0] && y0 >= m[1] && x1 <= m[2] && y1 <= m[3])
            return;

        blocksOf(t.psm, t.base, t.bw, x0, y0, x1, y1, ownerScratch);
        bool changed = false;
        for (uint32_t blk : ownerScratch)
            if (blockOwner[blk] != t.id)
            {
                blockOwner[blk] = t.id;
                changed = true;
            }
        if (changed)   
            ++ownerEpoch;

        m[0] = x0;
        m[1] = y0;
        m[2] = x1;
        m[3] = y1;
        t.markEpoch = ownerEpoch;
    }
    std::vector<uint32_t> decodeScratch;

    GSTransferCommand command{};
    GSTransferSnapshot snapshot{};
    std::vector<uint8_t> hostBytes;
    size_t hostOffset = 0;
    struct UploadRecord
    {
        uint64_t hash = 0, stamp = 0;
        Range range{};
    };
    std::unordered_map<uint64_t, UploadRecord> uploadRecords;

    DrawKey pendingKey;
    std::vector<HwVertex> pendingVertices;

    GSDrawState lastState{};
    bool lastStateValid = false;

    float pendingUvMin[2]{}, pendingUvMax[2]{};   
    bool pendingUvAll = false;
    TexRect copyRead, copyWritten;

    uint32_t displayBases[2] = {~0u, ~0u};

    bool isDisplayBase(uint32_t base) const { return base == displayBases[0] || base == displayBases[1]; }
    Surface *shownSource = nullptr;
    std::unique_ptr<Surface> sceneCopy;
    bool snapTaken = false;
    void takeSceneCopy(Surface &from)
    {

        flushDraws();
        syncSurface(from);

        if (!sceneCopy || sceneCopy->bw != from.bw || sceneCopy->sx != from.sx || sceneCopy->sy != from.sy)  
        {
            if (sceneCopy)
                core.releaseTarget(sceneCopy->target );
            sceneCopy = makeSurface(false, from.base, from.bw, from.psm);

        }
        sceneCopy->base = from.base;
        sceneCopy->psm = from.psm;
        sceneCopy->rows = from.rows;
        sceneCopy->tallAt = from.tallAt;
        core.copyTexels(sceneCopy->target, from.target, 0, 0, from.width() * from.sx, std::max(1u, from.rows) * from.sy);
        snapTaken = true;
        if (hudGapLog)
            gapEvent("SNAP %x (owner %06X)", from.base, owner);

    }
    struct DisplayCopy
    {
        Surface *source = nullptr ;
        uint32_t target = ~0u;
        float u0 = 1e30f, v0 = 1e30f, u1 = -1e30f, v1 = -1e30f;
        float x0 = 1e30f, x1 = -1e30f;
    } displayCopy;
    uint64_t presents = 0;
    struct LastSnap
    {
        bool valid = false;
        uint32_t target = 0, x = 0, y = 0, w = 0, h = 0;
        uint64_t at = 0;
        Surface *source = nullptr;
    } lastSnap;

    struct Stats
    {
        uint64_t draws = 0, rovDraws = 0, prims = 0, presents = 0, decodes = 0, decodedTexels = 0, cachedDraws = 0,
                targetTextureDraws = 0, uploads = 0, uploadsSkipped = 0, surfaceUploads = 0, directUploads = 0,
                reinterprets = 0, decodesReused = 0;
    } stats;
    const bool statsEnabled = [] {
        const char *v = std::getenv("PS2_GS_HW_STATS");
        return v && *v && std::strcmp(v, "0") != 0;
    }();
    enum Zone { ZSubmit, ZFlush, ZDecode, ZOwner, ZReinterpret, ZMark, ZRefresh, ZUpload, ZPresent, ZNative, ZShadows, ZD3DFlush, ZTransfer, ZWrite, ZMemWritten, ZHash, ZCount };
    uint64_t zoneNs[ZCount] = {} ;
    struct ZoneTimer
    {
        uint64_t *acc;
        std::chrono::steady_clock::time_point t0;
        ZoneTimer(const Impl *m, Zone z) 
            : acc(m->statsEnabled ? const_cast<uint64_t *>(&m->zoneNs[z]) : nullptr), t0(acc ? std::chrono::steady_clock::now() : t0)
        {
        }
        ~ZoneTimer()
        {
            if (acc)
                *acc += uint64_t(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now() - t0).count());
        }
    };

    uint64_t tick = 0;
    const std::vector<std::pair<uint64_t, uint64_t>> traceTicks = [] {
        std::vector<std::pair<uint64_t, uint64_t>> list;
        if (const char *v = std::getenv("PS2_RENDER_TRACE"))
            while (*v)
            {
                char *end = nullptr;
                std::pair<uint64_t, uint64_t> t ;
                t.first = std::strtoull(v, &end, 10);
                t.second = end && *end == ',' ? std::strtoull(end + 1, &end, 10) : t.first;
                list.push_back(t);

                if (!end || *end != ';')
                    break;

                v = end + 1;
            }
        return list;
    }();
    bool tracing() const
    {
        for (const auto &t : traceTicks)
            if (tick >= t.first && tick <= t.second) 
                return true;
        return false;
    }
    struct Warnings

    {

        uint64_t texture = 0, feedback = 0, localCopy = 0, localRead = 0, depthUpload = 0, format = 0, effectDepth = 0;
    } warnings;

    uint32_t owner = 0, ownerAnchor = 0;
    bool ownerDrop = false;
    const bool census = [] {
        const char *v = std::getenv("PS2_DK_DRAW_CENSUS");
        return v && std::strcmp(v, "0") != 0;
    }() ;
    struct CensusEntry
    {
        uint64_t prims = 0, transfers = 0, uploadBytes = 0;
    }; 
    std::map<uint32_t, CensusEntry> censusCounts;
    const bool texCensus = [] {
        const char *v = std::getenv("PS2_DK_TEX_CENSUS");
        return v && *v == '1';
    }();
    struct UploadRec
    {
        uint32_t dbp, dbw, dpsm, x0, y0, x1, y1, owner;
        uint64_t present;
    } ;
    std::vector<UploadRec> uploadRecs{UploadRec{}};

    std::vector<uint32_t> blockUpload = std::vector<uint32_t>(16384, 0u);
    std::map<std::string, uint64_t> texCensusCounts;
    std::vector<uint32_t> texCensusBlocks;
    void texCensusUpload()
    {
        const auto &b = command.bitbltbuf;
        const auto &t = command.trxpos;
        if (uploadRecs.size() >= (1u << 20))
        {
            uploadRecs.resize(1);
            std::fill(blockUpload.begin(), blockUpload.end(), 0u);
        }
        uploadRecs.push_back({uint32_t(b.dbp), std::max(1u, uint32_t(b.dbw)), uint32_t(b.dpsm), uint32_t(t.dsax), uint32_t(t.dsay), uint32_t(t.dsax + command.trxreg.rrw), uint32_t(t.dsay + command.trxreg.rrh), owner, presents});
        blocksOf(b.dpsm, b.dbp, std::max(1u, uint32_t(b.dbw)), t.dsax, t.dsay, t.dsax + command.trxreg.rrw, t.dsay + command.trxreg.rrh, texCensusBlocks);
        for (uint32_t blk : texCensusBlocks)
            blockUpload[blk] = uint32_t(uploadRecs.size() - 1);
    }
    std::string texCensusSource(uint32_t psm, uint32_t base, uint32_t bw, uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1)
    {
        blocksOf(psm, base, bw, x0, y0, x1, y1, texCensusBlocks);
        uint32_t one = 0;
        bool multi = false, none = false;
        for (uint32_t blk : texCensusBlocks)
        {
            const uint32_t u = blockUpload[blk];
            if (!u)
                none = true;
            else if (!one)
                one = u;
            else if (u != one)
                multi = true;
        }
        if (!one)
            return "none";
        const UploadRec &r = uploadRecs[one];
        const bool sameLayout = r.dbp == base && r.dbw == bw && (r.dpsm == psm || (r.dpsm == 0 && psm == 1));
        std::string s = none ? "part" : multi ? "multi" : sameLayout ? "own" : "other";
        s += r.present == presents ? "/now" : "/old";
        s += r.owner == owner ? "/self" : "/oth";
        return s;
    }
    void texCensusDraw(const Params &p, const TexRect &needed, const char *kind)
    {
        char key[160];
        if (kind)
            std::snprintf(key, sizeof key, "%06X %s", owner, kind);
        else
        {
            std::string tex = texCensusSource(p[22], p[20], std::max(1u, p[21]), needed.x0, needed.y0, std::max(needed.x1, needed.x0 + 1), std::max(needed.y1, needed.y0 + 1));
            std::string clut = "-";
            if (rtrans::paletted(p[22]))
            {
                const bool t8 = p[22] == 0x13 || p[22] == 0x1B;
                clut = texCensusSource(p[28], p[27], std::max(1u, p[31]), p[32], p[33], p[32] + (t8 ? 16 : 8), p[33] + (t8 ? 16 : 2));
            }
            std::snprintf(key, sizeof key, "%06X tex %s clut %s", owner, tex.c_str(), clut.c_str());
        }
        ++texCensusCounts[key];
    }
    void texCensusPrint()
    {
        if (texCensus && presents % 600 == 0)
            std::fprintf(stderr, "[texdir] present %llu texels from an upload of their layout %llu, from the uploads' bits %llu, rectangles composed %llu\n", (unsigned long long)presents, (unsigned long long)tex.fromImages, (unsigned long long)tex.fromBits, (unsigned long long)tex.prepared);
        if (!texCensus || presents % 600 != 0)
            return;
        std::fprintf(stderr, "[tex-census] present %llu\n", (unsigned long long)presents); 
        for (const auto &[key, n] : texCensusCounts)
            std::fprintf(stderr, "[tex-census] %8llu %s\n", (unsigned long long)n, key.c_str());
    }   
    const bool hudGapLog = std::getenv("PS2_HUD_GAP_LOG") != nullptr;
    uint64_t hudPrims = 0, framePrims = 0, prevHudPrims = 0, prevFramePrims = 0;
    std::map<uint32_t, uint32_t> ownerPrims, prevOwnerPrims;
    std::deque<std::string> gapRing;
    void gapEvent(const char *fmt, uint32_t a, uint32_t b = 0)
    {

        char t[64];
        std::snprintf(t, sizeof t, fmt, a, b);
        if (!gapRing.empty() && gapRing.back() == t)
            return;
        gapRing.emplace_back(t);
        if (gapRing.size() > 96)
            gapRing.pop_front();  

    }
    std::map<uint64_t, uint64_t> censusKinds;
    std::vector<GSPrimitiveBatch> group;
    bool groupOther = false;
    float groupX0 = 1e30f, groupX1 = -1e30f;

    Surface *nativeColor = nullptr, *nativeDepth = nullptr ;
    static inline thread_local bool t_locked = false;
    static inline thread_local const char *t_dumpPath = nullptr;
    struct LockedScope
    {
        LockedScope() { t_locked = true; }
        ~LockedScope() { t_locked = false; }
        LockedScope(const LockedScope &) = delete;
        LockedScope &operator=(const LockedScope &) = delete ;
    };

    void create()
    {

        core.create();
        if (!layoutTable.empty())
            return;
        static const uint32_t formats[6] = {0, 48, 2, 10, 50, 58};
        layoutTable.assign(6 * 4096, 0);
        for (int f = 0; f < 6; ++f)
        {
            const uint32_t psm = formats[f], bits = storageBits(psm), ph = bits == 16 ? 64 : 32;
            for (uint32_t y = 0; y < ph; ++y)
                for (uint32_t x = 0; x < 64; ++x)
                    layoutTable[f * 4096 + ((bitAddress(psm, 0, 1, x, y) / bits) & 4095)] = x | y << 8;
        }
    }

    void setScale(uint32_t want)
    {
        if (want == scale() || t_locked)
            return;
        flushDraws();
        core.setScale(want);
        surfaces.clear();
        sceneCopy.reset();
        lastSnap = {};
        snapTaken = false;
        shownSource = nullptr;
        displayCopy = {};
        pendingKey = {};
        lastStateValid = false;
    }
    std::unique_ptr<Surface> makeSurface(bool depth, uint32_t base, uint32_t bw, uint32_t psm)
    {
        auto t = std::make_unique<Surface>();
        t->id = ++surfaceIds;
        t->depth = depth;
        t->base = base;
        t->bw = bw;
        t->psm = psm;
        const bool effect = !depth && effectBuffer(base) &&
                            std::find(fullScaleEffects.begin(), fullScaleEffects.end(), base) == fullScaleEffects.end();
        t->target = core.createTarget(t->width(), depth, effect ? std::min(scale(), kEffectMaxScale) : 0) ;
        t->sx = core.targetScaleX(t->target);
        t->sy = core.targetScaleY(t->target);
        return t;
    }
    void fullScaleEffect(Surface &t)  
    {
        flushDraws();
        warn(warnings.effectDepth, "effect buffer drawn with the depth buffer: full scale"); 
        fullScaleEffects.push_back(t.base);
        core.releaseTarget(t.target);
        t.target = core.createTarget(t.width(), false);
        t.sx = core.targetScaleX(t.target);
        t.sy = core.targetScaleY(t.target );
        t.serial = ++writeSerial ; 
    }
    Surface *findSurface(bool depth, uint32_t base)
    {
        for (auto &s : surfaces)
            if (s->depth == depth && s->base == base)
                return s.get();
        return nullptr;
    }
    Surface *surface(bool depth, uint32_t base, uint32_t bw, uint32_t psm, uint32_t rows)
    {
        Surface *t = findSurface(depth, base);
        const bool sameFormat = t && (t->psm == psm || (!depth && (t->psm | psm) == 1));
        if (t && (t->bw != bw || !sameFormat))
        {
            flushDraws();
            auto replacement = makeSurface(depth, base, bw, psm);
            if (replacement->sx != t->sx || replacement->sy != t->sy)
                warn(warnings.format, "surface scale changed: texels dropped");
            else if (sameFormat || (!depth && t->psm <= 1 && psm <= 1))
            {
                core.copyTexels(replacement->target, t->target, 0, 0, std::min(t->bw, bw) * 64 * t->sx, TargetHeight * t->sy);
            }
            else
                warn(warnings.format, "surface format changed: texels dropped");
            replacement->rows = t->rows;
            replacement->tallAt = t->tallAt;

            core.releaseTarget(t->target);
            for (auto &s : surfaces)
                if (s.get() == t)
                    s = std::move(replacement);
            t = findSurface(depth, base);
        }
        if (!t)

        {
            surfaces.push_back(makeSurface(depth, base, bw, psm));
            t = surfaces.back().get();
        }
        t->psm = psm;
        t->grow(std::min<uint32_t>(rows, TargetHeight), presents);
        t->drawnAt = presents;
        syncSurface( *t);
        return t;
    }
    Surface *textureSurface(const Params &p, const TexRect &needed)
    {
        for (auto &t : surfaces)
            if (!t->depth && t->base == p[20] && t->bw == std::max(1u, p[21]) && (t->psm == p[22] || (t->psm == 0 && p[22] == 1)) && needed.x1 <= t->width() + 2 && needed.y1 <= t->rows + 2)
            {
                syncSurface( *t);
                return t.get();
            }
        return nullptr;
    }

    void surfaceFromMemory(Surface &t, uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, bool fromStaged = false)
    {
        const ZoneTimer zone(this, ZRefresh);
        x1 = std::min( x1, t.width());
        y1 = std::min(y1, TargetHeight);
        if (t.depth)
        {
            warn(warnings.depthUpload, "memory write into a depth surface: not drawn");
            return;
        }
        if (x0 >= x1 || y0 >= y1)
            return;  
        flushDraws();
        const uint32_t w = x1 - x0, h = y1 - y0;
        std::vector<uint32_t> pixels(size_t(w) * h);
        if (fromStaged)
            for (uint32_t y = 0; y < h; ++y)
                std::memcpy(&pixels[size_t(y) * w], &t.staged[size_t(y0 + y) * t.width() + x0], size_t(w) * 4);

        else
        {
            tex.prepareBits(t.psm, t.base, t.bw, x0, y0, x1, y1);

            for (uint32_t y = 0; y < h; ++y)
            {
                uint32_t *row = &pixels[size_t(y) * w];
                tex.loadRow(t.psm, t.base, t.bw, x0, y0 + y, w, row);
                if (storageBits(t.psm) == 16)
                    for (uint32_t x = 0; x < w; ++x)
                        row[x] = decode16(row[x]);
            }
            tex.done();
        }
        // A whole movie picture (staged, many blocks): smooth scaling (PS2_MOVIE_SCALE=0: point sampled).
        static const bool movieScale = [] {
            const char *v = std::getenv("PS2_MOVIE_SCALE");
            return !v || std::strcmp(v, "0") != 0;
        }();

        const bool movie = movieScale && fromStaged && w >= 256 && h >= 128;
        core.writePixels(t.target, {x0, y0, x1, y1}, pixels.data(), movie);
        t.grow(y1, presents) ; 
        t.drawnAt = presents;
        t.serial = ++writeSerial;
    }

    std::array<uint32_t, 4> blockRect(const Surface &t, uint32_t block)
    {
        uint32_t pw, ph, bwPx, bhPx;
        pageSize(t.psm, pw, ph );
        blockSize(t.psm, bwPx, bhPx);
        const uint32_t rel = (block - t.base) & 16383, page = rel / 32, inPage = rel % 32,
                       pagesPerRow = std::max(1u, (t.width() + pw - 1) / pw);
        // The block's place in a page: the first pixel of each block of page 0.
        for (uint32_t y = 0; y < ph; y += bhPx)
            for (uint32_t x = 0; x < pw; x += bwPx)
                if (blockOf(t.psm, 0, std::max(1u, t.bw), x, y) == inPage)
                {
                    const uint32_t px = (page % pagesPerRow) * pw + x, py = (page / pagesPerRow) * ph + y;
                    return {px, py, px + bwPx, py + bhPx};
                }
        return {0, 0, 0, 0};

    }
    std::vector<uint32_t> written;
    std::vector<uint32_t> syncBlocks, syncPages;
    std::vector<uint8_t> syncNeed;
    void memoryWritten(Range r, uint32_t base, uint32_t bw, uint32_t psm, uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1)
    {
        const ZoneTimer zone(this, ZMemWritten);
        stamps.touched(r);
        blocksOf(psm, base, bw, x0, y0, x1, y1, written);
        for ( uint32_t blk : written)
            if (blockOwner[blk])
            {
                blockOwner[blk] = 0;
                ++ownerEpoch;
            }
        auto sameLayout = [&](const Surface &t) {
            return !t.depth && t.base == base && t.bw == bw && (t.psm == psm || (t.psm | psm) == 1);
        };
        bool any = false;
        for (auto &t : surfaces)
            any = any || sameLayout(*t) || (t->rows && overlaps(t->range(), r));
        if (!any )
            return;
        for (auto &t : surfaces)
        {
            if (sameLayout(*t))
            {
                t->drawnAt = presents;

                t->memRects.push_back({x0, y0, x1, y1});   
                continue;
            }
            if (!t->rows)
                continue;
            bool hit = false;
            for ( uint32_t blk : written)
                hit = hit || t->holdsBlock(blk);
            if (!hit)
                continue;
            t->drawnAt = presents;
            for ( uint32_t blk : written)
                if (t->holdsBlock(blk) && !((t->memPending[blk >> 5] >> (blk & 31)) & 1))
                {
                    t->memPending[blk >> 5] |= 1u << (blk & 31);
                    t->memBlocks.push_back(blk);
                }
        }
    }
    // Before a surface is drawn, read or shown: GS memory written under it.
    void syncSurface(Surface &t)
    {
        syncMemory(t);
        if (t.stagedRects.empty())
            return;
        std::vector<std::array<uint32_t, 4>> rects;
        rects.swap(t.stagedRects);

        if (rects.size() > 16) // one rectangle (a movie picture: ~900 16 x 16 blocks)
        {

            std::array<uint32_t, 4> all{~0u, ~0u, 0, 0};   
            for (const auto &r : rects)
                all = {std::min(all[0], r[0]), std::min(all[1], r[1]), std::max(all[2], r[2]), std::max(all[3], r[3])};
            rects.assign(1, all);

        }
        for (const auto &r : rects)
            surfaceFromMemory(t, r[0], r[1], r[2], r[3], true);
    }
    void syncMemory(Surface &t)
    {
        syncMemoryBlocks(t);
        if (t.memRects.empty())
            return; 
        std::vector<std::array<uint32_t, 4>> rects;
        rects.swap(t.memRects);
        std::sort(rects.begin(), rects.end());
        rects.erase(std::unique(rects.begin(), rects.end()), rects.end());
        if (rects.size() > 16)
        {
            std::array<uint32_t, 4> all{~0u, ~0u, 0, 0};
            for (const auto &r : rects)
                all = {std::min(all[0], r[0]), std::min(all[1], r[1]), std::max(all[2], r[2]), std::max(all[3], r[3])};
            rects.assign(1, all);
        }
        for (const auto &r : rects)
            surfaceFromMemory(t, r[0], r[1], r[2], r[3]);   
    }

    void syncMemoryBlocks(Surface &t)
    {
        if (t.memBlocks.empty())
            return;
        std::vector<uint32_t> &blocks = syncBlocks;
        blocks.assign(t.memBlocks.begin(), t.memBlocks.end());
        t.memBlocks.clear();
        t.memPending.fill(0);
        if (t.depth)
        {
            warn(warnings.depthUpload, "memory write into a depth surface: not drawn");
            return;
        }
        uint32_t seen[512] = {};
        std::vector<std::array<uint32_t, 4>> rects;
        std::array<uint32_t, 4> all{~0u, ~0u, 0, 0};  
        for (uint32_t blk : blocks)
        {
            if (blockOwner[blk] || ((seen[blk >> 5] >> (blk & 31)) & 1))
                continue;
            seen[blk >> 5] |= 1u << (blk & 31);
            const auto r = blockRect(t, blk) ;
            rects.push_back(r);
            all = {std::min(all[0], r[0]), std::min(all[1], r[1]), std::max(all[2], r[2]), std::max(all[3], r[3])};
        }
        all[2] = std::min(all[2], t.width());
        all[3] =  std::min(all[3], TargetHeight);
        if (rects.empty() || all[0] >= all[2] || all[1] >= all[3])
            return;
        const ZoneTimer zone(this, ZRefresh);

        flushDraws() ;
        const uint32_t w = all[2] - all[0], h = all[3] - all[1];
        std::vector<uint32_t> pixels(size_t(w) * h);  
        std::vector<uint8_t> mask(size_t(w) * h, 0);
        for (const auto &r : rects)
            for (uint32_t y = std::max(r[1], all[1]); y < std::min(r[3], all[3]); ++y )
                for (uint32_t x = std::max(r[0], all[0]); x < std::min(r[2], all[2]); ++x)
                    mask[size_t(y - all[1]) * w + (x - all[0])] = 1;
        uint32_t pw, ph;
        pageSize(t.psm, pw, ph );
        std::vector<uint32_t> &pages = syncPages; 
        pages.clear();
        size_t maskedTexels = 0;
        for (const auto &r : rects)
        {
            pages.push_back((r[1] / ph) << 16 | (r[0] / pw));
            maskedTexels += size_t(r[2] - r[0]) * (r[3] - r[1]);
        }
        std::sort(pages.begin(), pages.end());
        pages.erase( std::unique(pages.begin(), pages.end()), pages.end());
        const auto compose = [&](uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1) {
            const uint32_t cw = x1 - x0;
            std::vector<uint8_t> &need = syncNeed;
            need.resize(size_t(cw) * (y1 - y0));
            for (uint32_t y = y0; y < y1; ++y)
                std::memcpy(&need[size_t(y - y0) * cw], &mask[size_t(y - all[1]) * w + (x0 - all[0])], cw);
            tex.prepareBits(t.psm, t.base, t.bw, x0, y0, x1, y1, need.data());
            for (uint32_t y = y0; y < y1; ++y)
            {
                uint32_t *row = &pixels[size_t(y - all[1]) * w + (x0 - all[0])];
                tex.loadRow(t.psm, t.base, t.bw, x0, y, cw, row);
                if (storageBits(t.psm) == 16)
                    for (uint32_t x = 0; x < cw; ++x)
                        row[x] = decode16(row[x]);
            }
            tex.done();
        };
        if (pages.size() > 1 && maskedTexels * 4 < size_t(w) * h)
            for (uint32_t pg : pages)
            {
                const uint32_t px = (pg & 0xFFFF) * pw, py = (pg >> 16) * ph;
                const uint32_t x0 = std::max(px, all[0]), y0 = std::max(py, all[1]), x1 = std::min(px + pw, all[2]),
                               y1 = std::min(py + ph, all[3]);
                if (x0 < x1 && y0 < y1)
                    compose(x0, y0, x1, y1);
            }  
        else 
            compose(all[0], all[1], all[2], all[3]);
        core.writePixelsMasked(t.target, {all[0], all[1], all[2], all[3]}, pixels.data(), mask.data());
        t.drawnAt = presents;
        t.serial = ++writeSerial;
    }

    TexEntry &texture(const Params &p, const TexRect &needed, bool decode = true)
    {
        const ZoneTimer zone(this, ZDecode);
        TexKey key;
        std::copy(p.begin() + 20, p.begin() + 43, key.begin()); 
        auto it = textures.find(key);
        if (it == textures.end())
        {
            if (textures.size() >= MaxTextures)
            {
                auto oldest = textures.begin();
                for (auto i = textures.begin(); i != textures.end(); ++i)
                    if (i->second.lastUse < oldest->second.lastUse)
                        oldest = i;
                for (const auto &v : oldest->second.versions)
                    if (v.tex)
                        core.releaseTexture(v.tex);

                textures.erase(oldest);
            }
            it = textures.emplace(key, TexEntry{}).first;
            TexEntry &e = it->second;
            e.width = std::min(1024u, textureExtent(p[37], p[23], p[39], p[40])) ;
            e.height = std::min(1024u, textureExtent(p[38], p[24], p[41], p[42]));
            e.rangeCount = textureRanges(p, e.ranges);
            e.tex = core.createTexture(e.width, e.height);
            e.versions[0].tex = e.tex ;
        }
        TexEntry &e = it->second;
        e.lastUse = ++useClock;

        bool valid = e.stamp != 0;
        for (int i = 0; valid && i < e.rangeCount; ++i)
            valid = stamps.newest(e.ranges[i]) <= e.stamp;
        if (!valid)
            e.decoded =  {};
        TexRect want = needed;
        want.x1 = std::min(want.x1, e.width);
        want.y1 = std::min(want.y1, e.height);
        if (!e.decoded.contains(want) && !e.decoded.empty())
            want = {std::min(want.x0, e.decoded.x0), std::min(want.y0, e.decoded.y0), std::max(want.x1, e.decoded.x1),
                    std::max(want.y1, e.decoded.y1)};
        decodeArea = e.decoded.contains(want) ? e.decoded : want; 
        if (!decode)
            return e;
        if (!e.decoded.contains(want))
        {
            const uint32_t w = want.x1 - want.x0, h = want.y1 - want.y0;
            decodeScratch.resize(size_t(w) * h);
            const uint32_t psm = p[22];
            tex.prepare(psm, p[20], std::max(1u, p[21]), want.x0, want.y0, want.x1, want.y1);
            if (psm == 19 || psm == 20 || psm == 27 || psm == 36 || psm == 44)
            {
                const bool four = psm == 20 || psm == 36 || psm == 44;
                uint32_t palette[256];
                for (uint32_t i = 0; i < (four ? 16u : 256u); ++i)
                    palette[i] = clutColor(tex, p, i);  
                const uint32_t bw = std::max(1u, p[21]);
                for (uint32_t y = 0; y < h; ++y)

                {
                    uint32_t *row = &decodeScratch[size_t(y) * w];
                    tex.loadRow(psm, p[20], bw, want.x0, want.y0 + y, w, row);
                    for (uint32_t x = 0; x < w; ++x)

                        row[x] = palette[row[x] & (four ? 15 : 255)];  
                }
            }
            else if (psm == 0 || psm == 1 || psm == 48 || psm == 49 || storageBits(psm) == 16)
            {
                const bool sixteen = storageBits(psm) == 16;
                const uint32_t bw = std::max(1u, p[21]);
                for (uint32_t y = 0; y < h; ++y)
                {
                    uint32_t *row = &decodeScratch[size_t(y) * w];
                    tex.loadRow(psm, p[20], bw, want.x0, want.y0 + y, w, row);
                    for (uint32_t x = 0; x < w; ++x) 
                        row[x] = texaAlpha(p, psm, sixteen ? decode16(row[x]) : row[x]);
                }
            }
            else
                for (uint32_t y = 0; y < h; ++y)
                    for (uint32_t x = 0; x < w; ++x)
                        decodeScratch[size_t(y) * w + x] = rawTexel(tex, p, want.x0 + x, want.y0 + y);
            tex.done();
            const bool whole = want.x0 == 0 && want.y0 == 0 && want.x1 == e.width && want.y1 == e.height;
            uint64_t hash = 1469598103934665603ull; 
            if (whole)
                for (uint32_t v : decodeScratch)
                    hash = (hash ^ v) * 1099511628211ull;
            TexEntry::Version *slot = nullptr;
            for (auto &v : e.versions)   

                if (whole ? v.tex && v.hash == hash && v.rect.x1 == e.width && v.rect.y1 == e.height : v.tex == e.tex)

                    slot = &v;
            if (!whole && slot)
            {
                core.updateTexture(slot->tex, {want.x0, want.y0, want.x1, want.y1}, decodeScratch.data());
                slot->hash =  0;
                slot->rect = {};
            }
            else if (slot)
                ++stats.decodesReused;
            else
            {
                auto rank = [](const TexEntry::Version &v) { return v.tex && !v.lastUse ? 0 : !v.tex ? 1 : 2; };
                slot = &e.versions[0];

                for (auto &v : e.versions)
                    if(rank(v) < rank(*slot) || (rank(v) == 2 && rank(*slot) == 2 && v.lastUse < slot->lastUse))

                        slot = &v;
                if (!slot->tex)
                    slot->tex = core.createTexture(e.width, e.height);
                core.updateTexture(slot->tex, {want.x0, want.y0, want.x1, want.y1}, decodeScratch.data());
                slot->hash = hash;
                slot->rect = want;
            }
            slot->lastUse = useClock;
            e.tex = slot->tex;
            ++stats.decodes;
            stats.decodedTexels += uint64_t(w) * h;
            e.decoded = want;
            e.stamp = stamps.stamp();
            Range all[2];
            e.rangeCount = textureRanges(p, all);  
            e.ranges[0] = rowsRange(p[22], p[20], std::max(1u, p[21]), want.y0, want.y1 - 1);
            if (e.rangeCount > 1)
                e.ranges[1] = all[1];
        }
        return e;
    }

    struct BlockTexels
    {
        uint32_t block;
        TexRect rect;
        uint32_t maxRow;
    };
    std::vector<uint32_t> blockRectAt;
    struct Reinterpreted
    {
        uint32_t width = 0, height = 0;
        const Surface *source = nullptr;
        uint64_t serial = 0, stamp = 0, owned = 0;

        TexRect decoded;
        rdraw::TextureId tex = 0;
        bool fallback = false;
        TexRect fallbackRect;

    };
    struct LayoutMap
    {
        std::vector<uint32_t> full;
        std::vector<uint16_t> blocks;
        std::vector<BlockTexels> blockRects;
        TexRect unmapped;
    }; 
    std::unordered_map<uint64_t, LayoutMap> layoutMaps;
    std::unordered_map<TexKey, Reinterpreted, TexKeyHash> reinterpreted;
    TexRect decodeArea;

    Reinterpreted *reinterpret(const Params &p, const TexEntry &e, Surface &s, const TexRect &area, const std::function<void(const TexRect &)> &decode)
    {
        const ZoneTimer zone(this, ZReinterpret);
        int table = -1;
        switch (s.psm)
        {
        case 0:
        case 1: table = 0; break;
        case 48:
        case 49: table = 1; break;  
        case 2: table = 2; break;
        case 10: table = 3; break;
        case 50: table = 4; break;
        case 58: table = 5; break;
        }
        if (table < 0 || area.empty())
            return nullptr ;
        if (!reinterpretPass(p[22], s.psm))

            warn(warnings.texture, "a target read as a texture of a format no game effect uses: gathered all the same");
        TexKey key;
        std::copy(p.begin() + 20, p.begin() + 43, key.begin());
        if (reinterpreted.size() > 256)
        {
            for (auto &kv : reinterpreted)   
                core.releaseTexture(kv.second.tex);
            reinterpreted.clear();
        }
        Reinterpreted &r = reinterpreted[key];
        uint32_t owned[512] = {};
        uint64_t ownedHash = 1469598103934665603ull;
        for ( uint32_t blk : written) 
            if (blockOwner[blk] == s.id)
            {
                owned[blk >> 5] |= 1u << (blk & 31);
                ownedHash = (ownedHash ^ blk) * 1099511628211ull;
            }
        if (r.tex && r.fallback)
            decode(r.fallbackRect);
        if (r.tex && r.source == &s && r.serial == s.serial && r.stamp == e.stamp && r.owned == ownedHash && r.decoded.contains(area) && r.width == e.width && r.height == e.height)
            return &r;
        if (!r.tex || r.width != e.width || r.height != e.height)
        {
            if (r.tex)
                core.releaseTexture(r.tex);
            r = {};
            r.width = e.width;
            r.height = e.height;
            r.tex = core.createTexture(e.width, e.height);
        }
        const uint32_t tpsm = p[22], tbw = std::max(1u, p[21]), sbw = std::max(1u, s.bw);
        const bool paletted = tpsm == 19 || tpsm == 20 || tpsm == 27 || tpsm == 36 || tpsm == 44;
        uint32_t clut[256];
        if (paletted)
            for (uint32_t i = 0; i < 256; ++i)
                clut[i] = clutColor(tex, p, i);
        const uint32_t eb = storageBits(s.psm), n = pixelBits(tpsm);
        const TexRect &a = area;
        uint64_t layoutKey = 1469598103934665603ull;
        for (uint32_t v : {tpsm, p[20], tbw, s.psm, s.base, sbw, e.width, e.height})
            layoutKey = (layoutKey ^ v) * 1099511628211ull;
        const uint32_t fw = e.width, fh = e.height;
        auto lm = layoutMaps.find(layoutKey);
        if (lm == layoutMaps.end())
        {
            if (layoutMaps.size() >= 64)
                layoutMaps.clear();
            lm = layoutMaps.emplace(layoutKey, LayoutMap{}).first;
            LayoutMap &made = lm->second; 
            made.full.resize(size_t(fw) * fh);
            made.blocks.resize(size_t(fw) * fh); 
            made.blockRects.clear();
            made.unmapped = {~0u, ~0u, 0, 0};
            std::vector<uint32_t> &at = blockRectAt;
            at.assign(16384, 0);
            for (uint32_t y = 0; y < fh; ++y)
                for (uint32_t x =  0; x < fw; ++x)
                {
                    const uint32_t addr =  bitAddress(tpsm, p[20], tbw, x, y), block = (addr >> 11) & 16383;
                    uint32_t v = rdraw::kNoTexel;
                    const uint32_t rel = (addr - s.base * 2048) & 0x1ffffff, page = rel >> 16, inPage = (rel & 0xffff) / eb,
                                   bit = rel % eb;
                    const uint32_t xy = layoutTable[size_t(table) * 4096 + inPage];
                    const uint32_t px = (page % sbw) * 64 + (xy & 255), py = (page / sbw) * (eb == 16 ? 64 : 32) + (xy >> 8);
                    if (bit + n <= eb)
                        v = px | py << 12 | bit << 24;
                    made.full[size_t(y) * fw + x] = v;
                    made.blocks[size_t(y) * fw + x] = uint16_t(block);
                    TexRect *b = &made.unmapped;

                    if (v != rdraw::kNoTexel)
                    {
                        if (!at[block])
                        {  
                            made.blockRects.push_back({block, {~0u, ~0u, 0, 0}, 0});
                            at[block] = uint32_t(made.blockRects.size());
                        }
                        BlockTexels &bt = made.blockRects[at[block] - 1];
                        bt.maxRow = std::max(bt.maxRow, py);
                        b = &bt.rect;
                    }
                    *b = {std::min(b->x0, x), std::min(b->y0, y), std::max(b->x1, x + 1), std::max(b->y1, y + 1)};
                }
        }
        const LayoutMap &lay = lm->second;
        TexRect fb{~0u, ~0u, 0, 0};
        const auto addArea = [&](const TexRect &b) {  
            const TexRect c{std::max(b.x0, a.x0), std::max(b.y0, a.y0), std::min(b.x1, a.x1), std::min(b.y1, a.y1)};
            if (!c.empty())
                fb = {std::min(fb.x0, c.x0), std::min(fb.y0, c.y0), std::max(fb.x1, c.x1), std::max(fb.y1, c.y1)};
        };
        addArea(lay.unmapped);
        for (const BlockTexels &b : lay.blockRects)
            if (!((owned[b.block >> 5] >> (b.block & 31)) & 1) || b.maxRow >= s.rows)
                addArea(b.rect);
        r.fallback = fb.x0 < fb.x1;
        r.fallbackRect = r.fallback ? fb : TexRect{};
        if (r.fallback)

            decode(r.fallbackRect);
        rdraw::Gather g;
        g.source = s.target;
        g.wordBits = eb;
        g.bits =  n;
        g.depthMask = s.psm == 49 ? 0xffffffu : eb == 16 ? 0xffffu : 0xffffffffu;
        g.map =  lay.full.data();
        g.mapKey =  layoutKey;
        g.mapWidth = fw;
        g.mapHeight = fh;
        g.blocks = lay.blocks.data();
        g.owned = owned;

        g.rows = s.rows;   
        g.palette = paletted ? clut : nullptr;
        g.fallback = e.tex;
        g.alphaMode = (tpsm == 1 || tpsm == 49)                               ? rdraw::TexAlpha::Rgb24  
                      : (tpsm == 2 || tpsm == 10 || tpsm == 50 || tpsm == 58) ? rdraw::TexAlpha::Rgba16
                                                                              : rdraw::TexAlpha::AsIs;
        g.alpha0 = uint8_t(p[34]);
        g.blackClear = p[35] != 0;
        g.alpha1 = uint8_t(p[36]);
        core.gather(r.tex, {a.x0, a.y0, a.x1, a.y1}, g);
        r.source = &s;
        r.serial = s.serial;
        r.stamp = e.stamp;

        r.owned = ownedHash;
        r.decoded = area;
        return &r;
    }

    void flushDraws()
    {
        if (pendingVertices.empty())
            return;
        const ZoneTimer zone(this, ZFlush);
        rdraw::Batch batch;

        std::vector<HwVertex> vertices = std::move(spareVertices);
        vertices.clear();
        vertices.swap(pendingVertices);
        batch.vertices = vertices.data();
        batch.vertexCount = uint32_t( vertices.size());
        const DrawKey key = pendingKey;
        const float uvMin[2] = {pendingUvMin[0], pendingUvMin[1]}, uvMax[2] = {pendingUvMax[0], pendingUvMax[1]};
        const bool uvAll = pendingUvAll ;
        const Params &p = key.p;
        const TexRect readArea = copyRead;
        copyRead = copyWritten = {};
        batch.state = drawStateOf(p);
        batch.color = key.color->target;
        batch.depth = key.depth ? key.depth->target : 0;
        batch.depthRows = key.depth ? key.depth->rows : 0;
        batch.scissor = key.scissor;   
        batch.lines = key.lines;
        if (p[103] == 5)
        {
            // Copy of the target texels the batch reads, sampled as a surface.
            batch.source = rdraw::TexSource::TargetCopy;
            batch.copyArea = {readArea.x0, readArea.y0, readArea.x1, readArea.y1};
            if (texCensus )
                texCensusDraw(p, {}, "target-copy");
        }
        else if (p[1] & 2)
        {
            TexRect needed;
            const uint32_t ex = textureExtent(p[37], p[23], p[39], p[40]), ey = textureExtent(p[38], p[24], p[41], p[42]);
            if (uvAll)
                needed = {0, 0, ex, ey};
            else   
            {
                wrapAxis(uvMin[0], uvMax[0], p[1] & 32, p[23], p[37], p[39], p[40], ex, needed.x0, needed.x1 );
                wrapAxis(uvMin[1], uvMax[1], p[1] & 32, p[24], p[38], p[41], p[42], ey, needed.y0, needed.y1);
            }
            Surface *t = !rtrans::paletted(p[22]) && !key.lines
                            ? textureSurface(p, needed)
                            : nullptr;
            if ( t && t != key.color)
            {
                batch.source = rdraw::TexSource::Target;

                batch.sourceTarget = t->target;
                if(texCensus)
                    texCensusDraw(p, needed, "surface");   
            }
            else
            {
                Surface *under = nullptr;
                TexEntry &e = texture(p, needed, false);
                const TexRect area = decodeArea;
                const bool known = e.ownerEpoch == ownerEpoch && !e.ownerSurface && e.ownerRect.x0 == needed.x0 &&
                                   e.ownerRect.y0 == needed.y0 && e.ownerRect.x1 == needed.x1 && e.ownerRect.y1 == needed.y1;
                if(!needed.empty() && !known)
                {
                    const ZoneTimer ownerZone(this, ZOwner);
                    blocksOf(p[22], p[20], std::max(1u, p[21]), needed.x0, needed.y0, std::min(needed.x1, 2048u), std::min(needed.y1, 2048u), written);
                    uint64_t best = 0;
                    size_t bestCount = 0;
                    for (size_t i = 0; i < written.size(); ++i)
                    {
                        const uint64_t id = blockOwner[written[i]];
                        if (!id || id == best)
                            continue;
                        size_t n = 0;
                        for ( uint32_t blk : written)   
                            n += blockOwner[blk] == id;
                        if (n > bestCount)
                        {
                            best = id;
                            bestCount = n;
                        }
                        if (bestCount * 2 >= written.size())
                            break;
                    }
                    if ( best)
                        for (auto &s : surfaces)
                            if (s->id == best && s->rows)
                                under = s.get();
                    e.ownerEpoch = ownerEpoch;

                    e.ownerRect = needed;

                    e.ownerSurface = best;
                }
                batch.source = rdraw::TexSource::Texture;
                if (under && tracing())
                {
                    const char *pass = reinterpretPass(p[22], under->psm);
                    std::fprintf(stderr, "[rtrace] %llu reinterpret (%s) tex %x bw %u psm %u rect %u,%u-%u,%u from %s %x bw %u psm %u rows %u\n", (unsigned long long)tick, pass ? pass : "?", p[20], p[21], p[22], needed.x0, needed.y0, needed.x1, needed.y1, targetName(under->depth, under->base, under->bw), under->base, under->bw, under->psm, under->rows);
                }
                const auto decode = [&](const TexRect &rect) { texture(p, rect); };
                if(Reinterpreted *r = under ? reinterpret(p, e, *under, area, decode) : nullptr)
                    batch.texture = r->tex;
                else
                {
                    decode(needed);
                    batch.texture = e.tex;
                    if (under)
                        warn(warnings.texture, "texture reads the memory of a surface of a format without a layout table: from the uploads");
                }
                if(texCensus)
                    texCensusDraw(p, needed, under ? "reinterpret" : nullptr);

                batch.textureCacheHw = e.width == p[23] && e.height == p[24];
            }
        }

        float x0 = 1e30f, y0 = 1e30f, x1 = -1e30f, y1 = -1e30f;
        for (const HwVertex &h : vertices)
        {
            x0 = std::min(x0, h.x);
            y0 = std::min(y0, h.y);
            x1 = std::max(x1, h.x);
            y1 = std::max(y1, h.y);
        }
        const bool zWrite =  key.depth && !p[8];
        core.draw(batch);
        key.color->serial = ++writeSerial;
        if (key.depth && zWrite)
            key.depth->serial = ++writeSerial;
        const rdraw::Rect &sc = key.scissor;
        const uint32_t bx0 = uint32_t(std::clamp(std::floor(x0) - 1, float(sc.x0), float(sc.x1))),
                        by0 = uint32_t(std::clamp(std::floor(y0) - 1, float(sc.y0), float(sc.y1))),
                       bx1 = uint32_t(std::clamp(std::ceil(x1) + 1, float(sc.x0), float(sc.x1))),
                       by1 = uint32_t(std::clamp(std::ceil(y1) + 1, float(sc.y0), float(sc.y1)));
        markDrawn(*key.color, bx0, by0, bx1, by1);
        if (key.depth && zWrite)
            markDrawn(*key.depth, bx0, by0, bx1, by1);
        vertices.clear();
        spareVertices = std::move(vertices) ;
    }
    std::vector<HwVertex> spareVertices;

    void endGroup()  
    {
        if (group.empty())

            return;
        std::vector<GSPrimitiveBatch> prims;
        prims.swap(group);
        const GSWidescreen::Squeeze squeeze =
            groupOther ? GSWidescreen::Squeeze{} : GSWidescreen::squeezeFor(ownerAnchor, groupX0, groupX1);
        groupOther = false;
        groupX0 =  1e30f;
        groupX1 = -1e30f;
        for(GSPrimitiveBatch &b : prims)  
        {
            float px0 = 1e30f, px1 = -1e30f;   
            for (int i = 0; i < b.vertexCount; ++i)
            {
                px0 = std::min(px0, b.vertices[size_t(i)].x);
                px1 = std::max(px1, b.vertices[size_t(i)].x);
            }
            if (squeeze.on && px1 - px0 < GSWidescreen::kScreenWidth * 0.95f)
            {
                const float ofx = float(b.state.context.xyoffset.ofx ) / 16.0f;
                for (int i = 0; i < b.vertexCount; ++i)
                    b.vertices[size_t(i)].x = squeeze.apply(b.vertices[size_t(i)].x - ofx) + ofx;
                GSScissorReg &sc = b.state.context.scissor;

                if (float(sc.x1 - sc.x0) < GSWidescreen::kScreenWidth * 0.95f) // a clip window of the element
                {
                    sc.x0 = uint16_t(std::max(0.0f, std::floor(squeeze.apply(float(sc.x0))))); 
                    sc.x1 = uint16_t(std::max(0.0f, std::ceil(squeeze.apply(float(sc.x1)))) );  
                }
            }
            self->submitLocked(b);
        }
    }
    void setOwner(uint32_t o, uint32_t flags)
    {
        endGroup();
        if (hudGapLog && o != owner)
            gapEvent("o%06X", o);
        owner = o;
        ownerDrop = (flags & RenderExec::kOwnerDrop) != 0;
        const uint32_t anchor =  GSWidescreen::uiAnchor(o);
        ownerAnchor = !ownerDrop && o && GSWidescreen::active() && anchor != GSWidescreen::kKeep ? anchor : 0;
    }
    void submitOwned(const GSPrimitiveBatch &b)
    {
        if (ownerDrop)  
            return;
        if (!ownerAnchor)
        {
            self->submitLocked(b);

            return;

        }
        const GSContext &c = b.state.context;
        const float ofx = float(c.xyoffset.ofx) / 16.0f;
        for (int i = 0; i < std::min<int>(b.vertexCount, 3); ++i )
        {
            groupX0 = std::min(groupX0, b.vertices[size_t(i)].x - ofx);
            groupX1 = std::max(groupX1, b.vertices[size_t(i)].x - ofx);
        }
        groupOther |= c.frame.fbp != GSWidescreen::worldFbp();
        group.push_back(b);
    }

    bool nativeBind(const GSContext &c, bool useDepth)
    {
        if (!initialized || !c.frame.fbw || !validPsm(c.frame.psm) || (useDepth && !validPsm(c.zbuf.psm)))
            return false;
        flushDraws(); 
        const uint32_t base = c.frame.fbp * 32, bw = c.frame.fbw;
        const uint32_t x1 = std::min<uint32_t>(c.scissor.x1, bw * 64 - 1), y1 = std::min<uint32_t>(c.scissor.y1, TargetHeight - 1);
        if (c.scissor.x0 > x1 || c.scissor.y0 > y1)
            return false;
        if (tracing())
            std::fprintf(stderr, "[rtrace] %llu native fb %x fbw %u psm %u zbp %x depth %d scissor %u,%u-%u,%u owner %x%c", (unsigned long long)tick, base, bw, c.frame.psm, c.zbuf.zbp * 32, int(useDepth), c.scissor.x0, c.scissor.y0, x1, y1, owner, 10);
        nativeColor = surface(false, base, bw, c.frame.psm, y1 + 1);
        nativeDepth = useDepth ? surface(true, c.zbuf.zbp * 32, bw, c.zbuf.psm, y1 + 1) : nullptr;
        if (nativeDepth && nativeDepth->sx != nativeColor->sx)
            fullScaleEffect(*nativeColor);
        nativeColor->serial = ++writeSerial;
        markDrawn( *nativeColor, c.scissor.x0, c.scissor.y0, x1 + 1, y1 + 1);
        if (nativeDepth)
        {
            nativeDepth->serial = ++writeSerial;
            markDrawn(*nativeDepth, c.scissor.x0, c.scissor.y0, x1 + 1, y1 + 1);
        }

        return core.bindNative(nativeColor->target, nativeDepth ? nativeDepth->target : 0, {c.scissor.x0, c.scissor.y0, x1 + 1, y1 + 1});
    }
    void nativeDrawn(bool)
    {
        core.unbind();
        nativeColor = nativeDepth = nullptr;

    }   
    // A native command's texture: a core texture, or a surface's texels at 1x.
    bool nativeTexture(const GSTex0Reg &t, uint64_t clamp, const GSTexaReg &texa, const GSTexClutReg &texclut, DkNativeTexture &out)
    {
        out = {};
        if (!validPsm(t.psm))
            return false;
        if(t.psm == 0 || t.psm == 1)
            for(auto &s : surfaces)  
                if (!s->depth && s->rows && s->base == t.tbp0 && s->bw == std::max(1u, uint32_t(t.tbw)) && (s->psm == t.psm || (s->psm == 0 && t.psm == 1)))
                {
                    flushDraws();
                    syncSurface(*s);
                    out.width = std::min(1u << std::min<uint32_t>(t.tw, 10u), s->width());
                    out.height = std::min(1u << std::min<uint32_t>(t.th, 10u), TargetHeight );
                    out.target = s->target;
                    out.serial = s->serial;
                    return true;
                }
        Params p{};
        p[20] = t.tbp0;
        p[21] = t.tbw;
        p[22] = t.psm;
        p[23] = 1u << std::min<uint32_t>(t.tw, 10u);
        p[24] = 1u << std::min<uint32_t>(t.th, 10u);
        p[25] = t.tcc;
        p[26] = t.tfx;
        p[27] = t.cbp;
        p[28] = t.cpsm;
        p[29] = t.csm;
        p[30] = t.csa;
        p[31] = texclut.cbw;
        p[32] = texclut.cou;
        p[33] = texclut.cov;
        p[34] = texa.ta0;
        p[35] =  texa.aem;
        p[36] = texa.ta1 ;
        p[37] = clamp & 3;
        p[38] = (clamp >> 2) & 3;
        p[39] = (clamp >> 4) & 1023;
        p[40] = (clamp >> 14) & 1023;
        p[41] = (clamp >> 24) & 1023;
        p[42] = (clamp >> 34) & 1023;
        flushDraws();
        const uint32_t ex = textureExtent(p[37], p[23], p[39], p[40]), ey = textureExtent(p[38], p[24], p[41], p[42]);
        TexEntry &e = texture(p, {0, 0, ex, ey});
        out.width = e.width;
        out.height = e.height;
        out.texture = e.tex;
        return e.tex != 0;
    }
    const RenderCmd *runCmd = nullptr;
    const RenderState *runState = nullptr;
    static bool hostBind(void *u, const rdraw::NativeContext *c, bool depth)
    {
        return static_cast<Impl *>(u)->nativeBind(bindContextOf(*c), depth);
    }
    static void hostDrawn(void *u, bool depthWritten) { static_cast<Impl *>(u)->nativeDrawn(depthWritten); }
    static bool hostTexture(void *u, uint32_t context, uint32_t slot, DkNativeTexture *out)

    {
        Impl &m = *static_cast<Impl *>(u);
        *out =  {};
        if (!m.runCmd || !m.runState || slot >= m.runCmd->textures().size())
            return false;
        const RenderState &s = *m.runState ;
        return m.nativeTexture(tex0Of(m.runCmd->textures()[slot]), s.ctx[context & 1].clamp, s.texa, s.texclut, *out) ;
    }
    static void hostFlush(void *u)
    {
        Impl &m = *static_cast<Impl *>(u);
        m.flushDraws();
        m.core.unbind();
    }
    static void hostBegin(void *u) { static_cast<Impl *>(u)->endGroup(); }
    const DkNativeHost host{this, &hostBind, &hostDrawn, &hostTexture, &hostFlush, &hostBegin};

    struct FontHost final : RenderFontHost
    {
        Impl &m;
        explicit FontHost(Impl &impl) : m(impl) {}
        bool bind(const GSContext &c, bool depth) override { return m.nativeBind(c, depth); }
        void drawn(bool depthWritten) override { m.nativeDrawn(depthWritten); }
        bool texture(const GSTex0Reg &tex0, uint64_t clamp, const GSTexaReg &texa, const GSTexClutReg &texclut, DkNativeTexture &out) override
        {
            return m.nativeTexture(tex0, clamp, texa, texclut, out);
        }  
        void submit(const GSPrimitiveBatch &batch) override { m.self->submitLocked(batch); }
        void transfer(const GSTransferCommand &command) override { m.self->beginTransferLocked(command); }
        void upload(const uint8_t *data, uint32_t size) override { m.self->uploadImageLocked(data, size); }

    };

    void runCommand(RenderCmd &cmd, const RenderState &env)
    { 
        std::lock_guard lock(mutex);
        if (!initialized)
            return;   
        const ZoneTimer zone(this, ZNative);
        LockedScope locked; 
        if (uint32_t o, f; cmd.ownerMark(o, f))
        {
            endGroup();
            setOwner(o, f);
        }
        else if ( const RenderCmd::Movie *mv = cmd.movie())

        {
            endGroup();
            const auto &rgba = mv->rgba;
            movie = rgba && mv->width && mv->height && rgba->size() >= size_t(mv->width) * mv->height * 4 ? rgba : nullptr;

            moviePlaced = 0;
            movieWidth = mv->width;
            movieHeight =  mv->height;

            movieOrigin = false;
            movieAt = presents;
        }
        else if (const RenderCmd::Dump *dump = cmd.dump())
        {
            endGroup();   
            t_dumpPath = dump->path.c_str();

            self->PresentBegin(dump->request);
            t_dumpPath = nullptr;
        }
        else if (const GSNativeFontBatch *font = cmd.font())
        {
            endGroup();
            FontHost fontHost(*this);
            renderFont(fontHost, *font, cmd.fontRes(), env);
        }
        else if (DkCmd *h = cmd.handle())
        {
            const rdraw::NativeEnv native = nativeEnvOf(env);
            runCmd = &cmd;
            runState = &env;
            dkRender().cmdRun(h, &native, &host);
            runCmd = nullptr;
            runState = nullptr;
        }
        if (nativeColor)
            nativeDrawn(true);
    }


    void writePixels(const uint8_t *data, uint32_t first, uint32_t count)
    {
        const ZoneTimer zone(this, ZWrite );
        const auto &b = command.bitbltbuf;
        const auto &t = command.trxpos;
        const uint32_t psm = b.dpsm, n = pixelBits(psm), rrw = command.trxreg.rrw, bw = std::max(1u, uint32_t(b.dbw));
        // (the upload's image: made at its first pixel; the pixels go straight into it, in order)
        if (first == 0)
            upload = tex.add(psm, b.dbp, bw, t.dsax, t.dsay, rrw, command.trxreg.rrh);
        if(!upload || first >= upload->w * upload->h)
            return;
        count = std::min(count, upload->w * upload->h - first);
        uint32_t *out = upload->pixels.data() + first;
        switch (n)
        {
        case 32:
            std::memcpy(out, data, size_t(count) * 4);
            break;
        case 24:
            for (uint32_t i =  0; i < count; ++i)
                out[i] = uint32_t(data[size_t(i) * 3]) | uint32_t(data[size_t(i) * 3 + 1]) << 8 | uint32_t(data[size_t(i) * 3 + 2]) << 16;
            break;
        case 16:
            for (uint32_t i = 0; i < count; ++i)
                out[i] = uint32_t(data[size_t(i) * 2]) | uint32_t(data[size_t(i) * 2 + 1]) << 8;
            break;
        case 8:

            for (uint32_t i = 0; i < count; ++i)
                out[i] = data[i];
            break;
        default:
        {
            // (two pixels per byte, low nibble first)
            const uint32_t pairs = count / 2;
            for (uint32_t k = 0; k < pairs; ++k)
            {
                const uint8_t v = data[k];
                out[2 * k] = v & 15u;  
                out[2 * k + 1] = v >> 4;
            }
            if (count & 1)

                out[count - 1] = data[pairs] & 15u;
            break;   
        }  
        }
        upload->written = first + count;
    }
    Range destRange() const
    {
        const auto &b = command.bitbltbuf;
        const auto &t = command.trxpos;
        return range(b.dpsm, b.dbp, std::max(1u, uint32_t(b.dbw)), t.dsax + std::max(1u, uint32_t(command.trxreg.rrw)) - 1, t.dsay + std::max(1u, uint32_t(command.trxreg.rrh)) - 1);
    }
    Range sourceRange() const
    {
        const auto &b = command.bitbltbuf;
        const auto &t = command.trxpos;
        return range(b.spsm, b.sbp, std::max(1u, uint32_t(b.sbw)), t.ssax + std::max(1u, uint32_t(command.trxreg.rrw)) - 1, t.ssay + std::max(1u, uint32_t(command.trxreg.rrh)) - 1);
    }
    void destWritten()
    {
        if (texCensus )
            texCensusUpload();
        const auto &b = command.bitbltbuf;
        const auto &t = command.trxpos;
        memoryWritten(destRange(), b.dbp, std::max(1u, uint32_t(b.dbw)), b.dpsm, t.dsax, t.dsay, t.dsax + command.trxreg.rrw, t.dsay + command.trxreg.rrh);
    }  
    bool sourceIsSurface() const
    {
        const Range r = sourceRange();
        for (auto &s : surfaces)
            if (s->rows && overlaps(s->range(), r))
                return true;
        return false;
    }
};

RenderBackend::RenderBackend() : m(std::make_unique<Impl>())
{
    m->self = this;
}
RenderBackend::~RenderBackend() = default;

void RenderBackend::Initialize(uint8_t *vram, uint32_t size)
{

    std::lock_guard lock(m->mutex);
    if (!vram || !size)
    {
        m->initialized = false;
        return;
    }
    if (size != VramBytes)
        throw std::runtime_error("Renderer expects 4 MiB GS memory");
    m->create();
    m->pendingVertices.clear() ;
    for (auto &s : m->surfaces) 
        m->core.releaseTarget(s->target);
    m->surfaces.clear();

    for (auto &kv : m->textures)
        for (const auto &v : kv.second.versions)
            if (v.tex)
                m->core.releaseTexture(v.tex);
    m->textures.clear();
    m->uploadRecords.clear();
    m->tex.clear(); // (the GS memory the runtime starts with holds nothing the game reads)
    m->stamps.touched( {0, VramBytes});
    m->initialized = true;
    m->command = {};
    m->snapshot = {};
    m->hostBytes.clear();

    m->hostOffset = 0;
}
void RenderBackend::Reset()
{

    std::lock_guard lock(m->mutex);
    m->flushDraws();
    m->command = {};  
    m->snapshot = {} ;
    m->hostBytes.clear();
    m->hostOffset = 0;
}

void RenderBackend::Submit(const GSPrimitiveBatch &b)
{
    std::lock_guard lock(m->mutex);
    if (m->tracing())
    {
        const GSContext &c = b.state.context;
        std::fprintf(stderr, "[rtrace] %llu prim %d fb %x fbw %u fpsm %u tme %d tbp %x tbw %u tpsm %u alpha %llx v0 %.1f,%.1f v1 %.1f,%.1f rgba %02x%02x%02x%02x owner %x\n", (unsigned long long)m->tick, int(b.state.prim.type), c.frame.fbp * 32, c.frame.fbw, c.frame.psm, int(b.state.prim.tme), c.tex0.tbp0, c.tex0.tbw, c.tex0.psm, (unsigned long long)c.alpha, b.vertices[0].x, b.vertices[0].y, b.vertices[1].x, b.vertices[1].y, b.vertices[1].r, b.vertices[1].g, b.vertices[1].b, b.vertices[1].a, m->owner);

    }

    const Impl::ZoneTimer zone( m.get(), Impl::ZSubmit);
    if (m->hudGapLog)
    {
        ++m->framePrims;
        ++m->ownerPrims[m->owner];

        if ( m->owner >= 0x2A6000u && m->owner < 0x2C2000u)
            ++m->hudPrims;
    }   

    if (m->census)

    {
        ++m->censusCounts[m->owner].prims;
        if (!m->owner)
        {
            const GSContext &kc = b.state.context;
            ++m->censusKinds[uint64_t(b.state.prim.type) | uint64_t(b.state.prim.tme) << 3 | uint64_t(b.state.prim.abe) << 4 |
                            uint64_t(b.state.prim.ctxt) << 5 | uint64_t(kc.frame.fbp & 0x1FF) << 8 |
                            uint64_t(kc.tex0.tbp0 & 0x3FFF) << 20 | uint64_t(kc.alpha & 0xFF) << 40];
        }
    }
    m->submitOwned( b);
}
void RenderBackend::submitLocked(const GSPrimitiveBatch &b)  
{
    if (!m->initialized || !b.vertexCount || b.state.prim.type > GS_PRIM_SPRITE)
        return;
    const auto &s = b.state;
    const auto &c = s.context;

    const auto &t = c.tex0;
    const auto &v = b.vertices;
    if (m->pendingVertices.size() > 60000)
        m->flushDraws();
    const bool triangle = s.prim.type == GS_PRIM_TRIANGLE || s.prim.type == GS_PRIM_TRISTRIP || s.prim.type == GS_PRIM_TRIFAN;
    const bool sprite = s.prim.type == GS_PRIM_SPRITE;
    const float texW =  float(s.textureWidth), texH = float(s.textureHeight);
    float uvLo[2] =  {1e30f, 1e30f}, uvHi[2] = {-1e30f, -1e30f};

    bool uvAll = false;
    float su0 = 0, sv0 = 0, su1 = 0, sv1 = 0;
    auto touch = [&](float u, float tt) {
        uvLo[0] = std::min(uvLo[0], u);
        uvHi[0] = std::max(uvHi[0], u);
        uvLo[1] = std::min(uvLo[1], tt);
        uvHi[1] = std::max(uvHi[1], tt);
    };
    if (s.prim.tme)

    {
        if (triangle)
        {
            const bool sameSign = (v[0].q > 0 && v[1].q > 0 && v[2].q > 0) || (v[0].q < 0 && v[1].q < 0 && v[2].q < 0);
            for (int i = 0; i < 3; ++i)

                if (s.prim.fst ) 
                    touch(v[i].u / 16.0f, v[i].v / 16.0f);   
                else if ( sameSign)
                    touch(v[i].s / v[i].q * texW, v[i].t / v[i].q * texH);
            uvAll = !s.prim.fst && !sameSign;
        }
        else if (sprite)
        {
            if (s.prim.fst )
            {
                su0 = v[0].u / 16.0f;
                sv0 = v[0].v / 16.0f;

                su1 = v[1].u / 16.0f;

                sv1 = v[1].v / 16.0f;
            }
            else
            {
                auto q = [](float x) { return std::fabs(x) > 1e-8f ? x : 1.0f; };
                su0 = v[0].s / q(v[0].q) * texW;
                sv0 = v[0].t / q(v[0].q) * texH;
                su1 = v[1].s / q(v[1].q) * texW;
                sv1 = v[1].t / q(v[1].q) * texH;
            }
            touch(su0, sv0);
            touch(su1, sv1) ;
        }
        else
            uvAll = true;  
    }
    TexRect needed;
    bool rect = false;
    if (s.prim.tme && !uvAll)
    {
        const uint32_t mu = c.clamp & 3, mv = (c.clamp >> 2) & 3, minU = (c.clamp >> 4) & 1023, maxU = (c.clamp >> 14) & 1023,
                       minV = (c.clamp >> 24) & 1023, maxV = (c.clamp >> 34) & 1023;
        wrapAxis(uvLo[0], uvHi[0], s.linearFilter, s.textureWidth, mu, minU, maxU, textureExtent(mu, s.textureWidth, minU, maxU), needed.x0, needed.x1);
        wrapAxis(uvLo[1], uvHi[1], s.linearFilter, s.textureHeight, mv, minV, maxV, textureExtent(mv, s.textureHeight, minV, maxV), needed.y0, needed.y1);
        rect = !needed.empty();
    }
    if (s.prim.tme && (sprite || triangle) && m->isDisplayBase(c.frame.fbp * 32) && t.tbp0 != c.frame.fbp * 32 && !uvAll && (t.psm == 0 || t.psm == 1))
        if (Surface *from = m->findSurface(false, t.tbp0); from && from->bw == std::max(1u, uint32_t(t.tbw)))

        {
            constexpr bool skip = false;

            if (!m->snapTaken)
                m->takeSceneCopy(*from);
            Impl::DisplayCopy &dc = m->displayCopy;
            if (dc.source != from || dc.target != c.frame.fbp * 32)
                dc = {from, c.frame.fbp * 32};
            dc.u0 = std::min(dc.u0, uvLo[0]);
            dc.v0 = std::min(dc.v0, uvLo[1] );
            dc.u1 = std::max(dc.u1, uvHi[0]);
            dc.v1 = std::max(dc.v1, uvHi[1]);
            for (int i = 0; i < (sprite ? 2 : 3); ++i)
            {
                dc.x0 = std::min(dc.x0, v[i].x - float(c.xyoffset.ofx) / 16.0f);
                dc.x1 =  std::max(dc.x1, v[i].x - float(c.xyoffset.ofx) / 16.0f);
            }
            if (skip)
                return;
        }
    auto textureRange = [&]() {
        const uint32_t bw = std::max(1u, uint32_t(t.tbw));
        if(rect)
            return range(t.psm, t.tbp0, bw, needed.x1 - 1, needed.y1 - 1);

        const uint32_t mu = c.clamp & 3, mv = (c.clamp >> 2) & 3, minU = (c.clamp >> 4) & 1023, maxU = (c.clamp >> 14) & 1023,   
                       minV = (c.clamp >> 24) & 1023, maxV = (c.clamp >> 34) & 1023;
        const uint32_t tx = mu >= 2 ? std::max(minU, maxU) | minU | maxU : s.textureWidth - 1,
                       ty = mv >= 2 ? std::max(minV, maxV) | minV | maxV : s.textureHeight - 1;
        return range(t.psm, t.tbp0, bw, tx, ty);
    };
    const DrawKey &pk = m->pendingKey;

    bool reuse = !m->pendingVertices.empty() && m->lastStateValid && !std::memcmp(&s, &m->lastState, sizeof(s));  

    if(reuse && s.prim.tme && rect)
    {
        const Range r = textureRange();
        if (overlaps(r, pk.color->range()) || (pk.depth && overlaps(r, pk.depth->range())))
            reuse = false;

    } 
    if (!reuse)
    {
        if (!validPsm(c.frame.psm) || !validPsm(c.zbuf.psm) || !c.frame.fbw)
            return;
        const uint32_t zm = uint32_t(c.test >> 17) & 3;
        if (zm == 0)
            return; // ZTST NEVER
        DrawKey key;

        Params &p = key.p;
        p[0] = s.prim.type;
        p[1] = uint32_t( s.prim.iip) | s.prim.tme << 1 | s.prim.fge << 2 | s.prim.abe << 3 | s.prim.fst << 4 |
               s.linearFilter << 5 | s.pabe << 6;
        p[2] = c.frame.fbp * 32;
        p[3] = c.frame.fbw;
        p[4] = c.frame.psm;

        p[5] = c.frame.fbmsk;
        p[6] = c.zbuf.zbp * 32;
        p[7] = c.zbuf.psm;
        p[8] = c.zbuf.zmask;
        p[9] = uint32_t(c.test);
        p[10] = uint32_t(c.alpha);
        p[11] = uint32_t(c.alpha >> 32) & 255;

        p[12] = c.fba & 1 ;
        p[13] = s.fogR | (uint32_t(s.fogG) << 8) | (uint32_t(s.fogB) << 16);
        if( s.prim.tme)

        {
            p[20] = t.tbp0;

            p[21] = t.tbw;
            p[22] = t.psm;

            p[23] = s.textureWidth;
            p[24] = s.textureHeight;

            p[25] = t.tcc;   
            p[26] = t.tfx;
            p[27] = t.cbp;
            p[28] = t.cpsm;
            p[29] = t.csm;
            p[30] = t.csa;
            p[31] = s.texclut.cbw;
            p[32] = s.texclut.cou;
            p[33] = s.texclut.cov;
            p[34] = s.texa.ta0;
            p[35] = s.texa.aem;
            p[36] = s.texa.ta1;
            p[37] = c.clamp & 3;
            p[38] = (c.clamp >> 2) & 3;
            p[39] = (c.clamp >> 4) & 1023;
            p[40] = (c.clamp >> 14) & 1023;
            p[41] = (c.clamp >> 24) & 1023 ;
            p[42] = (c.clamp >> 34) & 1023;
        }
        const uint32_t x1 = std::min<uint32_t>(c.scissor.x1, c.frame.fbw * 64 - 1), y1 = std::min<uint32_t>(c.scissor.y1, TargetHeight - 1);
        if (c.scissor.x0 > x1 || c.scissor.y0 > y1) 
            return;
        key.scissor = {c.scissor.x0, c.scissor.y0, x1 + 1, y1 + 1};
        const bool zUsed = !c.zbuf.zmask || zm >= 2;
        p[100] = c.frame.fbw * 64;
        p[101] = TargetHeight;
        // 24-bit targets blend with Ad = 0x80 (as FIX).
        if (c.frame.psm == 1 && ((p[10] >> 4) & 3) == 1)
        {
            p[10] = (p[10] & ~0x30u) | 0x20u;
            p[11] = 0x80;
        }
        // Feedback: the texels this primitive reads are in the target being drawn.
        if (s.prim.tme)
        {
            const Range texture = textureRange();
            const Range frame = range(c.frame.psm, p[2], p[3], x1, y1);
            key.feedback = overlaps(texture, frame) || (zUsed && overlaps(texture, range(p[7], p[6], p[3], x1, y1)));
        }
        auto same = [&](const Surface *u, bool used, uint32_t base, uint32_t psm) {
            return used ? u && u->base == base && u->bw == p[3] && (u->psm == psm || (!u->depth && (u->psm | psm) == 1)) : !u;
        }; 
        const bool copyCandidate = key.feedback && rect && (triangle || sprite) && (t.psm == 0 || t.psm == 1) &&
                                   (t.psm == c.frame.psm || (t.psm == 1 && c.frame.psm == 0)) && t.tbp0 == p[2] &&

                                   std::max( 1u, uint32_t(t.tbw)) == p[3];
        if (!m->pendingVertices.empty() && ((key.feedback && !copyCandidate) || !same(m->pendingKey.color, true, p[2], p[4]) || !same(m->pendingKey.depth, zUsed, p[6], p[7])))
            m->flushDraws();
        key.color = m->surface(false, p[2], p[3], p[4], 0);
        key.depth = zUsed ? m->surface(true, p[6], p[3], p[7], 0) : nullptr;

        if(key.depth && key.depth->sx != key.color->sx)
            m->fullScaleEffect(*key.color);
        key.lines = (s.prim.type == GS_PRIM_LINE || s.prim.type == GS_PRIM_LINESTRIP) && key.color->sx == 1;  
        TexRect wrote;  
        bool feedbackCopy = false;
        if (copyCandidate && needed.x1 <= key.color->width() && needed.y1 <= key.color->rows && !(zUsed && overlaps(textureRange(), range(p[7], p[6], p[3], x1, y1))))
        {
            const int ox = c.xyoffset.ofx >> 4, oy = c.xyoffset.ofy >> 4;
            float lx = 1e30f, ly = 1e30f, hx = -1e30f, hy = -1e30f;
            for (int i = 0; i < (sprite ? 2 : 3); ++i)
            {
                lx = std::min(lx, v[i].x - ox);
                ly = std::min(ly, v[i].y - oy);
                hx = std::max(hx, v[i].x - ox);
                hy = std::max( hy, v[i].y - oy);
            }
            wrote = {uint32_t(std::clamp(std::floor(lx) - 1, float(c.scissor.x0), float(x1 + 1))),
                    uint32_t(std::clamp(std::floor(ly) - 1, float(c.scissor.y0), float(y1 + 1))),
                    uint32_t(std::clamp(std::ceil(hx) + 2, float(c.scissor.x0), float(x1 + 1))),
                    uint32_t(std::clamp(std::ceil(hy) + 2, float(c.scissor.y0), float(y1 + 1)))};

            feedbackCopy = true;
            key.feedback = false ;
            key.p[103] = 5;
        }
        else if(key.feedback)
            warn(m->warnings.feedback, "texture reads the target being drawn in another layout: as it was before the batch");
        auto meets = [](const TexRect &a, const TexRect &b) {
            return !a.empty() && !b.empty() && a.x0 < b.x1 && b.x0 < a.x1 && a.y0 < b.y1 && b.y0 < a.y1;
        };
        if (!(key == m->pendingKey) || key.feedback || (feedbackCopy && meets(needed, m->copyWritten)))
            m->flushDraws() ;
        m->pendingKey = key;
        m->lastState = s;
        m->lastStateValid = !key.feedback && !feedbackCopy;
        if (feedbackCopy)
        {

            auto join = [](TexRect &a, const TexRect &b) {
                a = a.empty() ? b : TexRect{std::min(a.x0, b.x0), std::min(a.y0, b.y0), std::max(a.x1, b.x1), std::max(a.y1, b.y1)} ;
            };
            join(m->copyRead, needed);
            join(m->copyWritten, wrote);
        }
    }

    // Vertices (window coordinates minus XYOFFSET).
    const int ofx = c.xyoffset.ofx >> 4, ofy = c.xyoffset.ofy >> 4;
    const double zMax = c.zbuf.psm == 48 ? 4294967295.0 : c.zbuf.psm == 49 ? 16777215.0 : 65535.0;   
    auto depth = [&](const GSVertex &vx) { return float(std::min(vx.z, zMax) / 4294967296.0); };   
    {
        const int n = ( s.prim.type == GS_PRIM_LINE || s.prim.type == GS_PRIM_LINESTRIP || sprite) ? 2 : triangle ? 3 : 1;
        float low = -1e30f;  
        for (int i = 0; i < n; ++i)
            low = std::max(low, v[i].y - float(ofy));
        const float y0 = float(c.scissor.y0), y1 = float(std::min<uint32_t>(c.scissor.y1, TargetHeight - 1));
        const uint32_t rows = uint32_t(std::clamp(std::ceil(low) + 1.0f, y0 + 1.0f, y1 + 1.0f));
        for (Surface *t : {m->pendingKey.color, m->pendingKey.depth})
            if (t)
                t->grow(rows, m->presents);
    }
    auto &out = m->pendingVertices;
    if (out.empty())
    {
        m->pendingUvMin[0] = m->pendingUvMin[1] = 1e30f;
        m->pendingUvMax[0] = m->pendingUvMax[1] = -1e30f;
        m->pendingUvAll = false;
    }
    if (s.prim.tme && (triangle || sprite))
    { 
        for (int i = 0; i < 2; ++i)
        {
            m->pendingUvMin[i] =  std::min(m->pendingUvMin[i], uvLo[i]);
            m->pendingUvMax[i] = std::max(m->pendingUvMax[i], uvHi[i]);
        }
        m->pendingUvAll |= uvAll;
    }
    switch ( s.prim.type)
    {
    case GS_PRIM_TRIANGLE:
    case GS_PRIM_TRISTRIP:
    case GS_PRIM_TRIFAN:
    {
        const uint32_t flat = rgba(v[2]);
        // The GS samples pixel centres at integer coordinates, D3D at + .5.
        for (int i = 0; i < 3; ++i)   
            out.push_back({v[i].x - ofx + .5f, v[i].y - ofy + .5f, depth(v[i]), s.prim.iip ? rgba(v[i]) : flat, v[i].s, v[i].t, v[i].q, float(v[i].u), float(v[i].v), float(v[i].fog)});
        break;

    }
    case GS_PRIM_SPRITE:
    {
        const float ax = v[0].x - ofx, ay = v[0].y - ofy, bx = v[1].x - ofx, by = v[1].y - ofy;
        const float x0 = std::min(ax, bx), y0 = std::min(ay, by), x1 = std::max(ax, bx), y1 = std::max(ay, by);
        const float lx = std::ceil(x0), ly = std::ceil(y0), hx = std::max(lx + 1, std::ceil(x1)), hy = std::max(ly + 1, std::ceil(y1));
        const float u0 = su0, v0 = sv0, u1 = su1, v1 = sv1;
        auto edge = [](float t0, float t1, float p0, float p1, float at) {
            return p1 > p0 ? t0 + (t1 - t0) * (at - .5f - p0) / (p1 - p0) : t0;
        };
        const float eu0 = edge(u0, u1, x0, x1, lx), eu1 = edge(u0, u1, x0, x1, hx), ev0 = edge(v0, v1, y0, y1, ly),
                    ev1 = edge(v0, v1, y0, y1, hy);
        const float d = depth(v[1]), fog = float(v[1].fog);
        const uint32_t color = rgba(v[1]);
        HwVertex corner[4] = {{lx, ly, d, color, 0, 0, 1, eu0, ev0, fog},
                              {hx, ly, d, color, 0, 0, 1, eu1, ev0, fog},
                              {lx, hy, d, color, 0, 0, 1, eu0, ev1, fog},
                              {hx, hy, d, color, 0, 0, 1, eu1, ev1, fog}};
        if (s.prim.tme)
        {
            const float du = ( eu1 - eu0) / (hx - lx) * .5f, dv = (ev1 - ev0) / (hy - ly) * .5f;

            for (HwVertex &q : corner)

            {
                q.uvLo[0] = std::min(eu0 + du, eu1 - du);
                q.uvHi[0] = std::max(eu0 + du, eu1 - du);
                q.uvLo[1] = std::min(ev0 + dv, ev1 - dv);
                q.uvHi[1] = std::max(ev0 + dv, ev1 - dv);
            }  
        }
        for (int i : {0, 1, 2, 2, 1, 3})
            out.push_back(corner[i]);
        break;
    }
    case GS_PRIM_POINT:
    {
        const float x = std::floor(v[0].x - ofx + .5f), y = std::floor(v[0].y - ofy + .5f), d = depth(v[0]);
        const uint32_t color = rgba(v[0]);
        const HwVertex corner[4] = {{x, y, d, color, 0, 0, 1, 0, 0, float(v[0].fog)},
                                    {x + 1, y, d, color, 0, 0, 1, 0, 0, float(v[0].fog)},
                                    {x, y + 1, d, color, 0, 0, 1, 0, 0, float(v[0].fog)},
                                    {x + 1, y + 1, d, color, 0, 0, 1, 0, 0, float(v[0].fog)}};
        for (int i : {0, 1, 2, 2, 1, 3})
            out.push_back(corner[i]);
        break;
    }
    case GS_PRIM_LINE:
    case GS_PRIM_LINESTRIP:
    {
        const float ax = v[0].x - ofx + .5f, ay = v[0].y - ofy + .5f, bx = v[1].x - ofx + .5f, by = v[1].y - ofy + .5f;
        const float dx = bx - ax, dy = by - ay;
        const uint32_t c0 = s.prim.iip ? rgba(v[0]) : rgba(v[1]), c1 = rgba(v[1] );
        const HwVertex a{ax, ay, depth(v[0]), c0, 0, 0, 1, 0, 0, float(v[0].fog)},
            bvx{bx, by, depth(v[1]), c1, 0, 0, 1, 0, 0, float(v[1].fog)} ;
        if (pk.lines)
        {
            out.push_back(a);
            out.push_back(bvx);
            break;
        }

        const bool xMajor = std::fabs(dx) >= std::fabs(dy);
        const float wx = xMajor ? 0 : .5f, wy = xMajor ? .5f : 0;  
        const float back = (xMajor ? dx : dy) < 0 ? 1.0f / 256 : 0;
        HwVertex a0 = a, a1 = a, b0 = bvx, b1 = bvx;
        a0.x -= wx, a0.y -= wy, a1.x += wx, a1.y += wy, b0.x -= wx, b0.y -= wy, b1.x += wx, b1.y += wy;
        for (HwVertex *q : {&a0, &a1, &b0, &b1})

            (xMajor ? q->x : q->y) += back;
        for (const HwVertex &q : {a0, b0, a1, a1, b0, b1})
            out.push_back(q);
        break;
    }
    default:
        break;
    }
    ++m->stats.prims;
    if (pk.feedback)
        m->flushDraws();
}

void RenderBackend::BeginTransfer(const GSTransferCommand &command)
{
    std::lock_guard lock(m->mutex);
    if (m->census)

        ++m->censusCounts[m->owner].transfers;
    beginTransferLocked(command);
} 
void RenderBackend::beginTransferLocked( const GSTransferCommand &command)
{
    const Impl::ZoneTimer zone(m.get(), Impl::ZTransfer);
    m->endGroup();

    m->flushDraws();
    m->command = command;
    m->tex.finish();
    m->upload = nullptr;
    m->snapshot = {command.trxpos.dsax, command.trxpos.dsay, uint32_t(command.trxreg.rrw) * command.trxreg.rrh, 0,
                   command.direction, 0};
    if (!m->initialized)
        return;
    const auto &b = command.bitbltbuf;
    const auto &t = command.trxpos;
    const uint32_t w = command.trxreg.rrw, h = command.trxreg.rrh, total = m->snapshot.totalPixels;
    if (command.direction == 2)
    {
        if (m->sourceIsSurface())

            warn(m->warnings.localCopy, "local copy from a surface: from the uploads");
        std::vector<uint32_t> pixels(size_t(w) * h);
        const uint32_t sbw = std::max(1u, uint32_t(b.sbw)), dbw = std::max(1u, uint32_t(b.dbw));
        for (uint32_t y =  0; y < h; ++y)
            for (uint32_t x = 0; x < w; ++x)
                pixels[size_t(y) * w + x] = m->tex.load(b.spsm, b.sbp, sbw, t.ssax + x, t.ssay + y);
        m->writeImage(b.dpsm, b.dbp, dbw, t.dsax, t.dsay, w, h, pixels.data()); 
        m->destWritten();
        m->snapshot.copiedPixels = total;
        m->snapshot.direction = 3;
    }
    else if (command.direction == 1)
    {
        if (m->sourceIsSurface())
            warn(m->warnings.localRead, "local -> host read of a surface: from the uploads");
        const uint32_t n = pixelBits(b.spsm), sbw = std::max(1u, uint32_t(b.sbw));
        const size_t bytes = (size_t(total) * n + 7) / 8 ;
        m->hostBytes.assign(bytes, 0);
        m->hostOffset = 0;
        for (uint32_t i = 0; i < total; ++i)
        {
            const uint32_t v = m->tex.load( b.spsm, b.sbp, sbw, t.ssax + i % w, t.ssay + i / w);
            const size_t bit = size_t(i) * n;
            for(uint32_t k = 0; k < n; k += 8)
                if (n >= 8)
                    m->hostBytes[(bit + k) / 8] = uint8_t(v >> k);
            if (n == 4)
                m->hostBytes[bit / 8] |= uint8_t((v & 15) << (bit % 8));
        }
        m->snapshot.copiedPixels = total;
        m->snapshot.localToHostPendingBytes = bytes;   
    }
}

void RenderBackend::UploadImage(const uint8_t *data, uint32_t size)

{
    std::lock_guard lock(m->mutex);
    if (m->census)
        m->censusCounts[m->owner].uploadBytes += size;
    uploadImageLocked(data, size);
}
void RenderBackend::uploadImageLocked(const uint8_t *data, uint32_t size)
{

    const Impl::ZoneTimer zone(m.get(), Impl::ZUpload);
    if (!m->initialized || !data || !size || m->snapshot.direction != 0 || !m->command.trxreg.rrw)
        return;
    if (m->movie && m->movieAt + 30 < m->presents)
        m->movie = nullptr;

    const uint32_t movieBlocks = (m->movieWidth / 16) * (m->movieHeight / 16);
    if (m->movie && m->moviePlaced < movieBlocks && m->command.bitbltbuf.dpsm == 0 && m->command.trxreg.rrw == 16 &&

        m->command.trxreg.rrh == 16 && m->snapshot.copiedPixels == 0 && size >= 16 * 16 * 4)
    {

        const auto &tp = m->command.trxpos;
        if (!m->movieOrigin)
        {
            m->movieX = tp.dsax;
            m->movieY = tp.dsay;
            m->movieOrigin = true;
        }
        const uint32_t px = tp.dsax - m->movieX, py = tp.dsay - m->movieY;
        if (tp.dsax >= m->movieX && tp.dsay >= m->movieY && px + 16 <= m->movieWidth && py + 16 <= m->movieHeight)
        {
            for (uint32_t y = 0; y < 16; ++y )
                std::memcpy(m->movieBlock + y * 64, m->movie->data() + (size_t(py + y) * m->movieWidth + px) * 4, 64);
            data = m->movieBlock;
            size = 16 * 16 * 4;
            ++m->moviePlaced;
        }
    }
    const uint32_t n = pixelBits(m->command.bitbltbuf.dpsm);
    const uint32_t count = std::min(m->snapshot.totalPixels - m->snapshot.copiedPixels, uint32_t(uint64_t(size) * 8 / n));
    if (!count)
        return;
    // The pending batch decodes its texture when it is drawn: before memory changes.
    m->endGroup();
    m->flushDraws();
    ++m->stats.uploads;
    const bool whole = m->snapshot.copiedPixels == 0 && count == m->snapshot.totalPixels;
    bool skip = false;
    uint64_t key = 0, hash = 0;
    if (whole)
    {
        const auto &b = m->command.bitbltbuf;
        const auto &t = m->command.trxpos;
        key = (uint64_t(b.dbp) | uint64_t(b.dbw) << 14 | uint64_t(b.dpsm) << 20 | uint64_t(t.dsax) << 26 | uint64_t(t.dsay) << 37 ) ^
              (uint64_t(m->command.trxreg.rrw) << 48 | uint64_t(m->command.trxreg.rrh) << 36);
        const Impl::ZoneTimer hashZone(m.get(), Impl::ZHash);
        hash = 1469598103934665603ull;

        const size_t bytes = (size_t(count) * n + 7) / 8;
        size_t i = 0;
        for (; i + 8 <= bytes; i += 8)
        {
            uint64_t w;
            std::memcpy(&w, data + i, 8);
            hash = (hash ^ w) * 1099511628211ull;
        }
        for(; i < bytes; ++i)
            hash = (hash ^ data[i]) * 1099511628211ull;
        auto it = m->uploadRecords.find(key);
        skip = it != m->uploadRecords.end() && it->second.hash == hash && m->stamps.newest(it->second.range) == it->second.stamp;
        if (skip)
        {
            blocksOf(b.dpsm, b.dbp, std::max(1u, uint32_t(b.dbw)), t.dsax, t.dsay, t.dsax + m->command.trxreg.rrw, t.dsay + m->command.trxreg.rrh, m->ownerScratch);
            for(uint32_t blk : m->ownerScratch)
                skip = skip && !m->blockOwner[blk];
        }
    }
    if (m->tracing())
        std::fprintf(stderr, "[rtrace] %llu upload dbp %x dbw %u dpsm %u at %u,%u %ux%u skip %d\n", (unsigned long long)m->tick, m->command.bitbltbuf.dbp, m->command.bitbltbuf.dbw, m->command.bitbltbuf.dpsm, m->command.trxpos.dsax, m->command.trxpos.dsay, m->command.trxreg.rrw, m->command.trxreg.rrh, int(skip));
    std::vector<std::pair<Surface *, uint32_t>> &direct = m->directScratch;
    direct.clear();
    if(!skip && m->command.bitbltbuf.dpsm == 0)
    {
        const auto &b = m->command.bitbltbuf;
        const auto &tp = m->command.trxpos;

        const uint32_t bw = std::max(1u, uint32_t(b.dbw)), pageRow = 32 * bw;
        for (auto &t : m->surfaces)
        {
            const uint32_t offset = (t->base - b.dbp) & 16383;
            if (t->depth || t->bw != bw || t->psm > 1 || offset % pageRow || tp.dsax + m->command.trxreg.rrw > t->width())
                continue;
            const uint32_t row = offset / pageRow * 32;
            if (row <= tp.dsay && tp.dsay + m->command.trxreg.rrh <= row + TargetHeight)
                direct.push_back({t.get(), row});
        }
    }
    if (skip)
        ++m->stats.uploadsSkipped;
    else if (!direct.empty())

    {

        const auto &tp = m->command.trxpos;
        const uint32_t rrw = m->command.trxreg.rrw, rrh = m->command.trxreg.rrh;
        for (auto [t, row] : direct)
        {
            const uint32_t W = t->width(), y0 = tp.dsay - row;
            if ( t->staged.size() < size_t(W) * (y0 + rrh))
                t->staged.resize(size_t(W) * (y0 + rrh));
            for (uint32_t i = 0; i < count; ++i)
            {
                const uint32_t index = m->snapshot.copiedPixels + i;
                std::memcpy(&t->staged[size_t(y0 + index / rrw) * W + tp.dsax + index % rrw], data + size_t(i) * 4, 4);
            }
            t->stagedRects.push_back({uint32_t(tp.dsax), y0, uint32_t(tp.dsax) + rrw, y0 + rrh});
            m->markDrawn(*t, tp.dsax, y0, tp.dsax + rrw, y0 + rrh);
            t->drawnAt = m->presents;
        }
        m->stamps.touched(m->destRange());
        ++m->stats.directUploads;
    }
    else
    {
        m->writePixels(data, m->snapshot.copiedPixels, count);
        m->destWritten();   
        if (whole)
        {
            if (m->uploadRecords.size() > 4096)
                m->uploadRecords.clear();
            m->uploadRecords[key] = {hash, m->stamps.stamp(), m->destRange()};
        }
    }
    m->snapshot.copiedPixels += count;
    if (m->snapshot.copiedPixels == m->snapshot.totalPixels)
    {
        m->snapshot.direction = 3;
        m->snapshot.totalPixels = 0;
    }
    else
    {
        m->snapshot.x = m->command.trxpos.dsax + m->snapshot.copiedPixels % m->command.trxreg.rrw;
        m->snapshot.y = m->command.trxpos.dsay + m->snapshot.copiedPixels / m->command.trxreg.rrw;
    }
}
void RenderBackend::Flush()
{
    std::lock_guard lock(m->mutex);
    m->endGroup();
    m->flushDraws();
    if (m->initialized)
    {  
        const Impl::ZoneTimer zone(m.get(), Impl::ZD3DFlush);
        m->core.flush();

    }
}
void RenderBackend::Sync(GSSyncReason reason)
{
    std::lock_guard lock(m->mutex);
    m->flushDraws();
    if (m->initialized && reason == GSSyncReason::Finish)
    {
        const Impl::ZoneTimer zone(m.get(), Impl::ZD3DFlush);
        m->core.flush();
    }
}
uint32_t RenderBackend::ConsumeLocalToHostBytes(uint8_t *dst, uint32_t size)   
{
    std::lock_guard lock(m->mutex);
    if (!dst)
        return 0;
    size = uint32_t(std::min<size_t>(size, m->hostBytes.size() - m->hostOffset));
    std::memcpy(dst, m->hostBytes.data() + m->hostOffset, size);
    m->hostOffset += size;
    m->snapshot.localToHostPendingBytes = m->hostBytes.size() - m->hostOffset;
    return size;
}
GSTransferSnapshot RenderBackend::GetTransferSnapshot() const
{
    std::lock_guard lock(m->mutex);
    return m->snapshot;
}
uint32_t RenderBackend::ReadVram(uint32_t psm, uint32_t base, uint32_t bw, uint32_t x, uint32_t y) const
{

    std::lock_guard lock(m->mutex);
    if (!m->initialized || !validPsm(psm))
        return 0;
    return m->tex.load(psm, base, std::max(1u, bw), x, y);
}
void RenderBackend::WriteVram(uint32_t psm, uint32_t base, uint32_t bw, uint32_t x, uint32_t y, uint32_t v)
{

    std::lock_guard lock(m->mutex);
    if (!m->initialized || !validPsm(psm))
        return;
    m->flushDraws();
    bw = std::max(1u, bw);
    m->writeImage( psm, base, bw, x & 2047, y & 2047, 1, 1, &v);
    m->memoryWritten(range(psm, base, bw, x, y), base, bw, psm, x, y, x + 1, y + 1);   
}
void RenderBackend::SnapshotVram(std::vector<uint8_t> &out) const
{
    std::lock_guard lock(m->mutex);
    if (!m->initialized)
    {
        out.clear();

        return;
    }
    // There is no GS memory: zeros (only debug tools ask).
    out.assign(VramBytes, 0);
}
bool RenderBackend::ClearFramebuffer(const GSContext &c, uint32_t color)
{
    std::lock_guard lock(m->mutex);
    if (!m->initialized || !c.frame.fbw)
        return false;
    if (c.frame.psm != 0 && c.frame.psm != 1 && c.frame.psm != 2 && c.frame.psm != 10)

        return false ;   

    m->flushDraws();
    if ((c.fba & 1) && c.frame.psm != 1)
        color |= 0x80000000;
    const uint32_t x0 = c.scissor.x0, y0 = c.scissor.y0, x1 = std::max(c.scissor.x0, c.scissor.x1) + 1u,
                   y1 = std::max(c.scissor.y0, c.scissor.y1) + 1u;
    Surface *t = m->findSurface(false, c.frame.fbp * 32);
    if (t && t->bw == c.frame.fbw)
    {
        m->core.clearPixels(t->target, {x0, y0, x1, y1}, color);
        t->grow(std::min<uint32_t>(y1, TargetHeight), m->presents);
        return true;
    }   
    uint32_t value = color;
    if (c.frame.psm == 2 || c.frame.psm == 10)
        value = ((color >> 3) & 31) | ((color >> 6) & 0x3e0) | ((color >> 9) & 0x7c00) | ((color >> 24) >= 0x40 ? 0x8000 : 0);

    const std::vector<uint32_t> pixels(size_t(x1 - x0) * (y1 - y0), value);
    m->writeImage(c.frame.psm, c.frame.fbp * 32, c.frame.fbw, x0, y0, x1 - x0, y1 - y0, pixels.data());

    m->stamps.touched(range(c.frame.psm, c.frame.fbp * 32, c.frame.fbw, x1 - 1, y1 - 1));
    return true;
}

PresentationFrame RenderBackend::Present(const GSPresentationRequest &r)
{
    PresentBegin(r);
    return {};
}
bool RenderBackend::PresentPoll(PresentationFrame &out)
{
    out = {};
    return false;
}

bool RenderBackend::PresentBegin(const GSPresentationRequest &r)
{
    std::unique_lock lock(m->mutex, std::defer_lock);
    if (!Impl::t_locked) // a display dump from a native draw holds the lock
        lock.lock();
    if (!m->initialized)
        return false;
    const Impl::ZoneTimer zone(m.get(), Impl::ZPresent);
    m->endGroup();
    m->flushDraws(); 

    if (!Impl::t_locked)
        GSHwQualityFrame::latch( r.vsyncTick);
    if (m->statsEnabled && ++m->stats.presents == 60)
    {

        const auto &t = m->stats;
        const rdraw::Stats c = m->core.stats(true);
        std::fprintf(stderr, "[render] per frame: prims %.0f draws %.1f (ordered %.1f, cached tex %.1f, surface tex %.1f) decodes %.1f " "(%.0f texels, %.1f kept versions) uploads %.1f (same data %.1f, into surfaces %.1f) surface refreshes %.1f reinterprets %.1f surfaces %zu textures %zu\n", t.prims / 60.0, c.draws / 60.0, c.rovDraws / 60.0, c.cachedDraws / 60.0, c.targetTextureDraws / 60.0, t.decodes / 60.0, t.decodedTexels / 60.0, t.decodesReused / 60.0, t.uploads / 60.0, t.uploadsSkipped / 60.0, t.directUploads / 60.0, c.surfaceUploads / 60.0, c.reinterprets / 60.0, m->surfaces.size(), m->textures.size());
        const uint64_t *z = m->zoneNs;
        std::fprintf(stderr, "[render] CPU ms per frame: submit %.2f flush %.2f decode %.2f owner %.2f reinterpret %.2f mark %.2f " "refresh %.2f upload %.2f present %.2f native %.2f shadows %.2f\n", z[0] / 6e7, z[1] / 6e7, z[2] / 6e7, z[3] / 6e7, z[4] / 6e7, z[5] / 6e7, z[6] / 6e7, z[7] / 6e7, z[8] / 6e7, z[9] / 6e7, z[10] / 6e7);
        std::fprintf(stderr, "[render] CPU ms per frame: d3d flush %.2f (%.1f calls) transfer %.2f write %.2f memory %.2f hash %.2f\n", z[11] / 6e7, c.d3dFlushes / 60.0, z[12] / 6e7, z[13] / 6e7, z[14] / 6e7, z[15] / 6e7);
        auto &u = m->tex ;
        std::fprintf(stderr, "[render] refresh paint per frame: calls %.1f rect px %.0f images %.1f pages skipped %.1f fast px %.0f slow px %.0f\n", u.paintCalls / 60.0, u.paintRectPixels / 60.0, u.paintImages / 60.0, u.paintPagesSkipped / 60.0, u.paintFastPixels / 60.0, u.paintSlowPixels / 60.0);
        u.paintCalls = u.paintRectPixels = u.paintImages = u.paintPagesSkipped = u.paintFastPixels = u.paintSlowPixels = 0;
        std::fill(std::begin(m->zoneNs), std::end(m->zoneNs), 0);
        m->stats = {};
    }
    DisplayDesc s;
    if (!displayOf(r, s))
    {

        m->setScale(GSHwScale::requested());
        return false;
    }
    const bool fieldInterlace = s.fields;
    Surface *src = nullptr;
    bool preferred = false;
    char path = '-';
    uint32_t x = s.x, y = s.y, w = s.w, h = fieldInterlace ? s.h / 2 : s.h;
    {
        const Impl::DisplayCopy dc = m->displayCopy;
        m->displayCopy = {};
        if(m->displayBases[0] != s.base)
        {
            m->displayBases[1] = m->displayBases[0];
            m->displayBases[0] = s.base;
        }
        const bool snapped = m->snapTaken;
        m->snapTaken = false;
        if (dc.source && snapped && m->sceneCopy && dc.target == s.base && dc.x1 - dc.x0 >= float(s.w) * 0.9f && dc.u1 > dc.u0 && dc.v1 > dc.v0)
            for (auto &t : m->surfaces)
                if (t.get() == dc.source)
                {
                    m->shownSource = t.get() ;
                    src = m->sceneCopy.get();
                    preferred = true ;
                    path = 'C';
                    x = uint32_t(std::max(0.0f, std::floor(dc.u0)));
                    y = uint32_t(std::max(0.0f, std::floor(dc.v0)) );
                    w = std::min(uint32_t(std::floor(dc.u1)), src->width()) - std::min(x, src->width());
                    h = std::min(uint32_t(std::floor(dc.v1)), src->rows) - std::min(y, src->rows);

                    if (!w || !h)
                        src = nullptr, preferred = false ;
                }
    }
    if (src)
        m->lastSnap = {true, s.base, x, y, w, h, m->presents, m->shownSource};
    else if (m->lastSnap.valid && m->lastSnap.target == s.base && m->sceneCopy)
    {
        Surface *buffer = m->findSurface(false, s.base);
        if (!buffer || buffer->drawnAt <= m->lastSnap.at)
        {
            src = m->sceneCopy.get();
            preferred = true;
            path = 'L';
            x = m->lastSnap.x, y = m->lastSnap.y, w = m->lastSnap.w, h = m->lastSnap.h ;
            for (auto &t : m->surfaces)
                if (t.get() == m->lastSnap.source)
                    m->shownSource = t.get();  
        }
        else
            m->lastSnap.valid = false;
    }
    else
        m->lastSnap.valid = false;
    if (!src )
        m->shownSource = nullptr;
    if (!src && s.preferred && s.preferredDest == s.fbp && (s.preferredBw || s.preferredFbp != s.fbp))
        if(Surface *t = m->findSurface(false, s.preferredFbp); t && t->rows)
        {
            src = t;
            preferred = true;
            path = 'P';
            x = y = 0;
            w = std::min(w, t->width());
            h = std::min(h, t->rows); // (the display's height: in field mode the rows below are old memory)
        }
    Surface *shownBuffer = src ? nullptr : m->findSurface(false, s.base);
    if (shownBuffer)
        m->syncSurface(*shownBuffer);
    if (shownBuffer && !shownBuffer->rows)
        shownBuffer = nullptr;
    if (!src && !shownBuffer)
    {
        const uint32_t bw = std::max(1u, uint32_t(s.bw)), pageRow = 32 * bw;
        for (auto &t : m->surfaces)
        {
            const uint32_t offset = (s.base - t->base) & 16383, row = offset / pageRow * 32;
            if (t->depth || t->bw != bw || (t->psm | s.psm) > 1 || offset % pageRow || !offset)
                continue;
            m->syncSurface(*t) ;
            if ( t->rows > row + y)
            {
                shownBuffer = t.get();
                y += row;
                path = 'T';
                break;
            }
        }
    }
    if (shownBuffer && (s.fbp != 0 || shownBuffer->drawnAt + 2 >= m->presents))
    {  
        src = shownBuffer;
        if (path != 'T')

            path = 'B';
    }   
    if (!src && GSGameHeuristics::tryContextFrames(false, s.fbp))
        for (const uint32_t base : s.contextBases)
            if (Surface *t = m->findSurface(false, base); t && t->rows && t->drawnAt + 2 >= m->presents && t->width() >= w)
            {
                src = t;
                preferred = true;
                path = 'X';
                x = y = 0;
                h = std::min(h, t->rows);
                break ;
            }
    if (!src )
        src = shownBuffer;
    ++m->presents;  
    m->texCensusPrint();
    if (m->hudGapLog)
        m->gapEvent("PRESENT%c", uint32_t(path));
    if (m->hudGapLog)
    {
        if (m->hudPrims == 0 && m->prevHudPrims > 10)
            std::fprintf(stderr, "[hudgap] t%llu present %llu prims %llu (before: %llu, hud %llu) path %c src %x\n", (unsigned long long)s.vsyncTick, (unsigned long long)m->presents, (unsigned long long)m->framePrims, (unsigned long long)m->prevFramePrims, (unsigned long long)m->prevHudPrims, path, src ? src->base : ~0u);
        if (m->hudPrims == 0 && m->prevHudPrims > 10)
        {  
            std::string a, b;
            char t[32];
            for (const auto &[o, n] : m->ownerPrims)
                std::snprintf(t, sizeof t, " %06X:%u", o, n), a += t;
            for (const auto &[o, n] : m->prevOwnerPrims)

                std::snprintf(t, sizeof t, " %06X:%u", o, n), b += t;
            std::fprintf(stderr, "[hudgap]   this frame:%s%c[hudgap]   before:%s%c", a.c_str(), 10, b.c_str(), 10);
            std::string ring;
            for (const std::string &e : m->gapRing)
                ring += " " + e;
            std::fprintf(stderr, "[hudgap]   events:%s%c", ring.c_str(), 10);   
        }
        m->prevHudPrims = m->hudPrims, m->prevFramePrims = m->framePrims;
        m->hudPrims = m->framePrims = 0;
        m->prevOwnerPrims = std::move(m->ownerPrims);
        m->ownerPrims.clear();
    }
    if (m->tracing())

        std::fprintf(stderr, "[rtrace] %llu present dispfb %x src %x rows %u drawn %llu/%llu preferred %d rect %u,%u %ux%u path %c\n", (unsigned long long)s.vsyncTick, s.base, src ? src->base : ~0u, src ? src->rows : 0, (unsigned long long)(src ? src->drawnAt : 0), (unsigned long long)m->presents, int(preferred), x, y, w, h, path);
    m->tick = s.vsyncTick + 1;
    if (m->census && m->presents % 600 == 0)
    {
        std::string line = "[draw-census] per frame (owner:prims/transfers/upload KB):";
        char item[96];
        for (const auto &[o, c] : m->censusCounts)
        {
            std::snprintf(item, sizeof item, " %06X:%.1f/%.1f/%.1f", o, c.prims / 600.0, c.transfers / 600.0, c.uploadBytes / 600.0 / 1024.0);
            line += item;
        }
        std::fprintf(stderr, "%s\n", line.c_str());
        m->censusCounts.clear();
        std::vector<std::pair<uint64_t, uint64_t>> top(m->censusKinds.begin(), m->censusKinds.end());
        std::sort(top.begin(), top.end(), [](auto &x, auto &y) { return x.second > y.second; });
        for (size_t i = 0; i < top.size() && i < 12; ++i)
        {
            const uint64_t k = top[i].first;
            std::fprintf(stderr, "[draw-census]   owner 0: %.1f/frame prim %llu tme %llu abe %llu ctxt %llu fbp %03llX tbp %04llX alpha %02llX\n", top[i].second / 600.0, (unsigned long long)(k & 7), (unsigned long long)((k >> 3) & 1), (unsigned long long)((k >> 4) & 1), (unsigned long long)((k >> 5) & 1), (unsigned long long)((k >> 8) & 0x1FF), (unsigned long long)((k >> 20) & 0x3FFF), (unsigned long long)((k >> 40) & 0xFF));
        }
        m->censusKinds.clear();
    }
    if (src)
        m->syncSurface(*src);
    const uint32_t S = m->scale();
    w = std::max(1u, std::min(w, 2048u));
    h = std::max(1u, std::min(h, 2048u));
    const bool fullHeight = fieldInterlace && !preferred && src && src->rows > s.h / 2 + 16 && src->tallAt + 2 >= m->presents;
    if (fullHeight)
        h = std::min(s.h, src->rows - std::min(y, src->rows));
    const bool doubleLines = fieldInterlace && !preferred && !fullHeight;
    const uint32_t rowsShown = h;
    if (doubleLines)
        h *= 2;
    rdraw::Present shown;
    shown.width = w * S;
    shown.height = h * S;
    shown.vsyncTick = s.vsyncTick;
    shown.dumpPath = Impl::t_dumpPath;
    shown.toWindow = !Impl::t_dumpPath;
    std::vector<uint32_t> pixels;
    auto source = [&](rdraw::PresentMode mode, uint32_t rows) {
        shown.target = src->target;
        shown.mode = mode;
        shown.src[0] = float(x * src->sx);
        shown.src[1] = float(y * src->sy);
        shown.src[2] = float((x + w) * src->sx);
        shown.src[3] = float((y + rows) * src->sy);
    };   
    if (src && doubleLines)
        source(rdraw::PresentMode::Scaled, rowsShown); // (each of its lines is two display lines)
    else if (src && preferred && GSHwQualityFrame::deflicker())
    {
        source(rdraw::PresentMode::Deflicker, h);
        shown.deflickerStep = float(src->sy);
    }
    else if (src && (src->sx != S || src->sy != S))
        source(rdraw::PresentMode::Scaled, h);
    else if (src)
        source( rdraw::PresentMode::Copy, h);   
    else
    {
        // The uploads (a picture uploaded into the display buffer, never drawn).
        pixels.resize(size_t(w) * rowsShown);
        const uint32_t bw = s.bw ? s.bw : 10;
        for (uint32_t yy = 0; yy < rowsShown; ++yy)
            for (uint32_t xx = 0; xx < w; ++xx)
            {
                uint32_t v = m->tex.load(s.psm, s.base, bw, x + xx, y + yy);
                if (storageBits(s.psm) == 16)
                    v = decode16(v);
                pixels[size_t(yy) * w + xx] = v;
            }
        shown.pixels = pixels.data();
        shown.pixelsWidth = w;
        shown.pixelsHeight = rowsShown;   
    }
    static const uint32_t dumpSource = [] {
        const char *v = std::getenv("PS2_GS_HW_DUMP_SOURCE");
        return v ? uint32_t(std::strtoul(v, nullptr, 16) ) : ~0u;
    }();  
    if (dumpSource != ~0u)
        if (Surface *t = m->findSurface(false, dumpSource); t && t->rows )
        {
            m->syncSurface(*t);
            shown.dumpTarget = t->target;
            shown.dumpWidth = std::min(640u, t->width()) * t->sx;
            shown.dumpHeight = t->rows * t->sy;  
        }
    m->core.present(shown); 
    m->setScale(GSHwScale::requested());
    return true;
}

std::unique_ptr<GSRasterBackend> makeRenderBackend()
{

    return std::make_unique<RenderBackend>();
}

void RenderBackend::runCommand(RenderCmd &cmd, const RenderState &state)
{
    m->runCommand(cmd, state);
}

void renderRunCommand(GSRasterBackend &backend, RenderCmd &cmd, const RenderState &state)
{
    static_cast<RenderBackend &>(backend).runCommand(cmd, state);
}

void renderWorldDrawn(uint32_t frame)
{
    if (frame && frame <= g_nativeKeys.frames.size())
        GSWidescreen::worldDrawn(uint32_t(g_nativeKeys.frames[frame - 1])) ;
}

void renderModelsDrawn(uint32_t frame) 
{
    if (frame && frame <= g_nativeKeys.frames.size() && uint32_t(g_nativeKeys.frames[frame - 1]) == GSWidescreen::worldFbp())
        GSWidescreen::worldDrawn(GSWidescreen::worldFbp());
}
