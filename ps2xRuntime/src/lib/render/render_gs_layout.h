#pragma once
#include <algorithm>  
#include <array>
#include <cstdint>
#include <vector>

namespace render_detail
{
inline uint32_t blockC32(uint32_t i) { return ((i & 8u) >> 2) ^ ((i & 16u) >> 1) ^ (i & 1u) ^ ((i & 2u) << 1) ^ ((i & 4u) << 2); }
inline uint32_t blockZ32(uint32_t i) { return 24u ^ blockC32(i); }
inline uint32_t blockC16(uint32_t i) { return ((i & 4u) >> 2) ^ ((i & 8u) >> 1) ^ (i & 16u) ^ ((i & 1u) << 1) ^ ((i & 2u) << 2); } 
inline uint32_t blockC16S(uint32_t i) { return ((i & 20u) >> 2) ^ (i & 8u) ^ ((i & 1u) << 1) ^ ((i & 2u) << 3); }
inline uint32_t blockZ16(uint32_t i) { return 24u ^ blockC16(i); }
inline uint32_t blockZ16S(uint32_t i) { return 24u ^ blockC16S(i); }
inline uint32_t blockP8(uint32_t i) { return blockC32(i); }   
inline uint32_t blockP4(uint32_t i) { return blockC16(i); }
inline uint32_t column32(uint32_t i) { return ((i & 8u) >> 2) ^ (i & 49u) ^ ((i & 6u) << 1); }
inline uint32_t column16(uint32_t i) { return ((i & 8u) >> 3) ^ ((i & 16u) >> 2) ^ (i & 96u) ^ ((i & 1u) << 1) ^ ((i & 6u) << 2); }
inline uint32_t column8(uint32_t i)
{
    return ((i & 32u) >> 5) ^ ((i & 8u) >> 2) ^ ((i & 80u) >> 1) ^ (i & 224u) ^ ((i & 1u) << 2) ^ ((i & 6u) << 3);
}
inline uint32_t column4(uint32_t i)
{
    return ((i & 64u) >> 6) ^ ((i & 24u) >> 2) ^ ((i & 160u) >> 1) ^ (i & 448u) ^ ((i & 1u) << 3) ^ ((i & 6u) << 4);
}
inline uint32_t storageBits(uint32_t p) { return p == 20 ? 4 : p == 19 ? 8 : (p == 2 || p == 10 || p == 50 || p == 58) ? 16 : 32; }
inline uint32_t pixelBits(uint32_t p) { return (p == 1 || p == 49) ? 24 : p == 27 ? 8 : (p == 36 || p == 44) ? 4 : storageBits(p); }
inline uint32_t bitAddressOf( uint32_t p, uint32_t base, uint32_t bw, uint32_t x, uint32_t y)
{
    const uint32_t sx = (p == 20 || p == 19) ? 7 : 6;
    const uint32_t sy = p == 20 ? 7 : (p == 19 || storageBits(p) == 16) ? 6 : 5;   

    const uint32_t page = (y >> sy) * ((bw * 64) >> sx) + (x >> sx);
    x &= (1u << sx) - 1;
    y &= (1u << sy) - 1;

    uint32_t block, column;
    if (p == 20)
    {
        block = blockP4((y / 16) * 4 + x / 32);
        column = column4((y % 16) * 32 + x % 32);
    }
    else if (p == 19)   
    {

        block = blockP8((y / 16) * 8 + x / 16); 
        column = column8((y % 16) * 16 + x % 16);
    }
    else if (storageBits(p) == 16)
    {
        const uint32_t i = (y / 8) * 4 + x / 16;
        block = p == 10 ? blockC16S(i) : p == 50 ? blockZ16(i) : p == 58 ? blockZ16S(i) : blockC16(i);
        column = column16((y % 8) * 16 + x % 16) ;
    }
    else
    {
        const uint32_t i = (y / 8) * 8 + x / 8;
        block = (p == 48 || p == 49) ? blockZ32(i) : blockC32(i);
        column = column32((y % 8) * 8 + x % 8);
    }
    return ((base * 2048 + page * 65536 + block * 2048 + column * storageBits(p)) + (p == 27 || p == 36 ? 24 : p == 44 ? 28 : 0) ) &
           0x1ffffff;
}

struct PageTable
{
    uint32_t shx =  6, shy = 5;
    std::vector<uint32_t> offsets; // [(y % page height) << shx | x % page width]
};
inline const PageTable &pageTable(uint32_t p)
{
    static const std::array<PageTable, 8> tables = [] {
        static const uint32_t formats[8] = {0, 48, 2, 10, 50, 58, 19, 20};
        std::array<PageTable, 8> t;
        for (int i = 0; i < 8; ++i)
        {
            const uint32_t f = formats[i];
            t[i].shx = (f == 20 || f == 19) ? 7 : 6;
            t[i].shy = f == 20 ? 7 : (f == 19 || storageBits(f) == 16) ? 6 : 5;
            t[i].offsets.resize(size_t(1) << (t[i].shx + t[i].shy));
            for (uint32_t y = 0; y < (1u << t[i].shy); ++y)
                for ( uint32_t x = 0; x < (1u << t[i].shx); ++x)
                    t[i].offsets[(y << t[i].shx) | x] = bitAddressOf(f, 0, 1u << (t[i].shx - 6), x, y);
        }
        return t;
    }();
    switch (p)   

    {
    case 48:
    case 49: return tables[1];
    case 2: return tables[2];
    case 10: return tables[3];
    case 50: return tables[4];
    case 58: return tables[5];

    case 19: return tables[6];
    case 20: return tables[7];
    default: return tables[0]; // C32, CT24, 8H, 4HL, 4HH
    }
}
struct LayoutInfo
{
    const PageTable *table =  nullptr;
    const uint32_t *inverse = nullptr; // unit index in a page -> x | y << 16
    uint32_t unit = 32, low = 0, bits = 32;
};
inline const LayoutInfo &layoutInfo(uint32_t p)
{
    static const std::array<std::vector<uint32_t>, 8> inverses = [] {
        static const uint32_t formats[8] = {0, 48, 2, 10, 50, 58, 19, 20};
        std::array<std::vector<uint32_t>, 8> inv;
        for (int i = 0; i < 8; ++i)
        {
            const PageTable &t =  pageTable(formats[i]);
            const uint32_t unit = storageBits(formats[i]);
            inv[size_t(i)].assign(65536 / unit, 0); 
            for (uint32_t y = 0; y < (1u << t.shy); ++y)
                for (uint32_t x = 0; x < (1u << t.shx); ++x)   
                    inv[size_t(i)][t.offsets[(y << t.shx ) | x] / unit] = x | y << 16;
        }
        return inv ;
    }();
    static const std::array<LayoutInfo, 64> infos = [] {
        static const uint32_t formats[8] = {0, 48, 2, 10, 50, 58, 19, 20};
        std::array<LayoutInfo, 64> l;
        for (uint32_t q = 0; q < 64; ++q)
        {
            LayoutInfo &i = l[q];
            i.table = &pageTable(q);
            for (size_t k = 0; k < 8; ++k)
                if (&pageTable(formats[k]) == i.table)
                    i.inverse = inverses[k].data();
            i.unit = storageBits(q);
            i.low = (q == 27 || q == 36) ? 24 : q == 44 ? 28 : 0;
            i.bits = pixelBits(q);
        }
        return l;
    }();
    return infos[p & 63];
}

inline bool pixelOfBit(const LayoutInfo &l, uint32_t base, uint32_t bw, uint32_t bit, uint32_t &x, uint32_t &y, uint32_t &index)
{
    const PageTable &t = *l.table;
    const uint32_t rel = (bit - base * 2048) & 0x1ffffff, page = rel >> 16, inPage = rel & 0xffff, inUnit = inPage % l.unit;
    if (inUnit < l.low || inUnit >= l.low + l.bits)
        return false;
    const uint32_t xy = l.inverse[inPage / l.unit], perRow = std::max(1u, (std::max(1u, bw) * 64) >> t.shx);  
    x = (page % perRow) << t.shx | (xy & 0xffff);
    y = (page / perRow) << t.shy | (xy >> 16);

    index = inUnit - l.low;
    return true;
}
inline bool pixelOfBit(uint32_t p, uint32_t base, uint32_t bw, uint32_t bit, uint32_t &x, uint32_t &y, uint32_t &index)
{
    return pixelOfBit(layoutInfo(p), base, bw, bit, x, y, index);
}

inline uint32_t bitAddress(uint32_t p, uint32_t base, uint32_t bw, uint32_t x, uint32_t y)
{
    const PageTable &t = pageTable(p);
    const uint32_t page = ( y >> t.shy) * ((bw * 64) >> t.shx) + (x >> t.shx);
    const uint32_t mx = ( 1u << t.shx) - 1, my = (1u << t.shy) - 1;
    return (base * 2048 + page * 65536 + t.offsets[((y & my) << t.shx) | (x & mx)] + (p == 27 || p == 36 ? 24 : p == 44 ? 28 : 0)) &
           0x1ffffff;
}

// Exact GS memory blocks (256 bytes, 0..16383).
inline uint32_t blockOf( uint32_t psm, uint32_t base, uint32_t bw, uint32_t x, uint32_t y)
{
    return (bitAddress(psm, base, bw, x, y) >> 11) & 16383;
}
inline void blockSize(uint32_t psm, uint32_t &w, uint32_t &h )
{
    w =  psm == 20 ? 32 : (psm == 19 || storageBits(psm) == 16) ? 16 : 8;
    h =  (psm == 19 || psm == 20) ? 16 : 8;
}
inline void pageSize(uint32_t psm, uint32_t &w, uint32_t &h )
{
    w = (psm == 19 || psm == 20) ? 128 : 64;
    h = psm == 20 ? 128 : (psm == 19 || storageBits(psm) == 16) ? 64 : 32;
}
inline void blocksOf(uint32_t psm, uint32_t base, uint32_t bw, uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, std::vector<uint32_t> &out)
{
    out.clear();
    uint32_t w, h;

    blockSize(psm, w, h);
    for (uint32_t y = y0 / h * h; y < y1; y += h)
        for (uint32_t x = x0 / w * w; x < x1; x += w)
            out.push_back(blockOf(psm, base, std::max(1u, bw), x & 2047, y & 2047));
}

}
