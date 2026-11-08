#include "dk_formats.h"

#include <algorithm>
#include <cstring>

 #include <unordered_map>
#include <unordered_set>

namespace
{
    constexpr uint32_t kMagic = 0x4D495A77u; // "wZIM"
    constexpr size_t kHeaderSize = 0x20u;
    constexpr size_t kImageDescSize = 0x28u;
    constexpr size_t kClutDescSize = 0x10u;
    constexpr uint32_t kMaxCount = 4096u;
    constexpr uint32_t kMaxDim =  4096u;
    constexpr int kMaxDmaTags = 4096;

    // GS pixel formats (TEX0.PSM / BITBLTBUF.DPSM)
    constexpr uint32_t kPsmCt32 = 0x00u;
    constexpr uint32_t kPsmCt24 = 0x01u;
    constexpr uint32_t kPsmCt16 = 0x02u;
    constexpr uint32_t kPsmCt16s = 0x0Au;

    constexpr uint32_t kPsmT8 = 0x13u;
    constexpr uint32_t kPsmT4 = 0x14u;

    // GS registers written by A+D in the upload packets
    constexpr uint32_t kRegBitbltbuf = 0x50u;
    constexpr uint32_t kRegTrxpos = 0x51u;
    constexpr uint32_t kRegTrxreg = 0x52u;

    uint16_t rd16(const uint8_t *p)
    {
        return static_cast<uint16_t>(p[0] | (p[1] << 8)) ;

    }

    uint32_t rd32(const uint8_t *p)
     {
        return static_cast<uint32_t>(p[0]) | (static_cast<uint32_t>(p[1]) << 8) |
               (static_cast<uint32_t>(p[2]) << 16) | (static_cast<uint32_t>(p[3]) << 24);
    }

    uint64_t rd64(const uint8_t *p)

    {
        return static_cast<uint64_t>(rd32(p)) | (static_cast<uint64_t>(rd32(p + 4)) << 32);
    }

    std::string hex(uint64_t v)
    {  
        static const char digits[] = "0123456789ABCDEF";
        std::string s;
        do
        {
            s.insert(s.begin(), digits[v & 0xF]);
            v >>= 4;
        } while (v != 0);

        return "0x" + s;
    }

    // One GS host->local transfer (BITBLTBUF/TRXPOS/TRXREG + IMAGE data).
    struct Transfer
    {  
        uint32_t dbp = 0;
        uint32_t psm = 0;
        uint32_t x = 0; // TRXPOS.DSAX
         uint32_t y = 0; // TRXPOS.DSAY
        uint32_t w = 0; // TRXREG.RRW 
        uint32_t h = 0; // TRXREG.RRH
        size_t offset = 0; // IMAGE data in the record
        size_t size = 0;
    };

    struct ImageInfo
    {
        uint32_t width = 0;  
        uint32_t height = 0 ;
        uint32_t x = 0; // position in the texture
        uint32_t y = 0;
        uint32_t psm = 0;
        uint32_t csm = 0;
         uint32_t csa = 0;
        int clut = -1;
        std::vector<Transfer> transfers;   
    };

    struct Layout
    {
        std::vector<ImageInfo> images;
        std::vector<std::vector<Transfer>> cluts;
    };

    uint32_t bitsPerPixel(uint32_t psm)
    {
        switch (psm)
        { 
        case kPsmCt32: return 32;
        case kPsmCt24: return 24;
        case kPsmCt16:
        case kPsmCt16s: return 16;
        case kPsmT8: return 8;
        case kPsmT4: return 4;
        default: return 0;
        }
    }  

    bool isPalette(uint32_t psm)
    {
        return psm == kPsmT8 || psm == kPsmT4;
    }

    // Texture alpha <-> PC alpha, see the top of the file.
    uint8_t alphaToPc(uint8_t a, bool gsScale)
    {
        return gsScale ? static_cast<uint8_t>(std::min(255, a * 2)) : a;
    }

    uint8_t alphaToPs2(uint8_t a, bool gsScale)  
    {
        return gsScale ? static_cast<uint8_t>((a + 1) / 2) : a ;
     }

     bool parseUpload(const uint8_t *data, size_t size, size_t offset, std::vector<Transfer> &out, std::string &error)  

    {
        uint64_t bitbltbuf = 0;
        uint64_t trxpos = 0;
        uint64_t trxreg = 0;
        size_t pos = offset;

        for (int tags = 0; tags < kMaxDmaTags; ++tags)
        {
            if (pos > size || size - pos < 16)
            {
                error = "upload packet at " + hex(offset) + " runs past the end";
                return false;
            }
            const uint64_t tag = rd64(data + pos);
            const size_t qwc = static_cast<size_t>(tag & 0xFFFFu);
            const uint32_t id = static_cast<uint32_t>((tag >> 28) & 7u);
             const uint32_t vifCmd = (rd32(data + pos + 12) >> 24) & 0x7Fu;
            size_t p = pos + 16;
            const size_t end = p + qwc * 16;
            if (end > size)
            {
                error = "DMA tag at " + hex(pos) + " runs past the end";
                return false;
            }
            if (qwc != 0 && vifCmd != 0x50u && vifCmd != 0x51u)
            {
                error = "DMA tag at " + hex(pos) + " is not VIF DIRECT";
                return false;
             }
            while(p < end)
            {
                if (end - p < 16)
                {
                    error = "GIF tag at " + hex(p) + " runs past its DMA packet";
                    return false;
                }
                const uint64_t lo = rd64(data + p);
                const uint64_t regs = rd64(data + p + 8);
                p += 16;
                const size_t nloop = static_cast<size_t>(lo & 0x7FFFu);
                const uint32_t flg = static_cast<uint32_t>((lo >> 58) & 3u);
                 size_t nreg = static_cast<size_t>(lo >> 60);
                if (nreg == 0)

                    nreg = 16;
                if (flg == 0) // PACKED
                {
                    if ((end - p) / 16 < nloop * nreg)
                    {
                        error = "GIF PACKED data at " + hex(p) + " runs past its DMA packet";
                        return false;
                    }
                    for (size_t i =  0; i < nloop * nreg; ++i, p += 16)
                    {
                        if(((regs >> ((i % nreg) * 4)) & 0xFu) != 0xEu)
                            continue; // only A+D sets the transfer registers
                        const uint64_t value = rd64(data + p);

                        switch (data[p + 8])
                        {
                        case kRegBitbltbuf: bitbltbuf = value; break;
                        case kRegTrxpos: trxpos = value; break;
                        case kRegTrxreg: trxreg = value; break;
                        default: break;
                        }
                    }
                }
                else if (flg == 1) // REGLIST: 64-bit words, padded to a qword
                 {
                    const size_t bytes = ((nloop * nreg * 8) + 15) & ~static_cast<size_t>(15);
                    if (end - p < bytes)
                    {
                        error = "GIF REGLIST data at " + hex(p) + " runs past its DMA packet";

                        return false ;   
                    }
                     p += bytes;
                }
                else // IMAGE (and the disabled mode 3, same layout)
                {
                    if ((end - p) / 16 < nloop)
                    {
                        error = "GIF IMAGE data at " + hex(p) + " runs past its DMA packet";
                        return false;
                    }

                    Transfer t;
                    t.dbp = static_cast<uint32_t>((bitbltbuf >> 32) & 0x3FFFu);
                    t.psm = static_cast<uint32_t>((bitbltbuf >> 56) & 0x3Fu);
                    t.x = static_cast<uint32_t>((trxpos >> 32) & 0x7FFu);
                    t.y = static_cast<uint32_t>((trxpos >> 48) & 0x7FFu);
                    t.w = static_cast<uint32_t>(trxreg & 0xFFFu);
                    t.h = static_cast<uint32_t>((trxreg >> 32) & 0xFFFu);
                    t.offset = p;
                    t.size = nloop * 16;
                    const uint32_t bpp = bitsPerPixel(t.psm);
                     if (bpp == 0)
                    {
                        error = "transfer at " + hex(p) + " has unsupported PSM " + hex(t.psm);
                        return false;
                     }
                    if ((static_cast<uint64_t>(t.w) * t.h * bpp + 7) / 8 > t.size)
                    {
                        error = "transfer at " + hex(p) + " has less data than TRXREG";

                        return false;
                    }
                    out.push_back(t);   

                    p += nloop * 16;
                }
            }
            pos = end;
            if (id == 1) // CNT: next tag follows the data
                 continue;
            if (id == 6 || id == 7) // RET / END
                return true;
            error = "unsupported DMA tag id " + std::to_string(id) + " at " + hex(pos);
            return false;
        }
        error = "upload packet at " + hex(offset) + " has too many DMA tags";
        return false;
    }  

    template <typename Fn>
    void forEachPixel(const ImageInfo &img, Fn &&fn)

    {
        for (const Transfer &t : img.transfers)
        {
            for (uint32_t ty = 0; ty < t.h; ++ty)
            {

                const int64_t y = static_cast<int64_t>(t.y) + ty - img.y;
                if (y < 0)
                    continue;
                if (y >= img.height)
                    break;   
                for (uint32_t tx = 0; tx < t.w; ++tx)
                {
                    const int64_t x = static_cast<int64_t>(t.x) + tx - img.x;
                    if (x < 0)
                        continue;
                    if (x >= img.width)
                        break;
                    fn(static_cast<uint32_t>(x), static_cast<uint32_t>(y), t, static_cast<size_t>(ty) * t.w + tx);
                }
            }
        }
    }

    bool parseLayout(const uint8_t *data, size_t size, Layout &layout, std::string &error)
    {
        if (data == nullptr || size < kHeaderSize || rd32(data) != kMagic)
         {  
            error = "not a wZIM record";
            return false;
        }

        const uint32_t imageCount = rd32(data + 0x08);
        const uint32_t clutCount = rd32(data + 0x0C);
        const size_t imageDescs = rd32(data + 0x10);
        const size_t clutDescs = rd32(data + 0x14);
        if (imageCount == 0 || imageCount > kMaxCount || clutCount > kMaxCount)
        {
            error = "bad image/CLUT count";
            return false;
        }
        if (imageDescs > size || (size - imageDescs) / kImageDescSize < imageCount ||
            (clutCount != 0 && (clutDescs > size || (size - clutDescs) / kClutDescSize < clutCount)))
        {
            error = "descriptor table runs past the end";
            return false;
        }

        layout.cluts.assign(clutCount, {}) ; 
        for(uint32_t i = 0; i < clutCount; ++i)
        {
            const size_t packet = rd32(data + clutDescs + i * kClutDescSize); 
            if (!parseUpload(data, size, packet, layout.cluts[i], error))
            {
                error = "CLUT " + std::to_string(i) + ": " + error;
                return false;
            }
        }

        layout.images.assign(imageCount, {});
        for (uint32_t i = 0; i < imageCount; ++i)

        {
            const uint8_t *desc = data + imageDescs + i * kImageDescSize;
             const uint64_t tex0 = rd64(desc + 0x18);
            ImageInfo &img = layout.images[i];
            img.width = rd16(desc + 0x0C);
            img.height = rd16(desc + 0x0E);
            img.x = rd16(desc + 0x10);
            img.y = rd16(desc + 0x12);
            img.psm = static_cast<uint32_t>((tex0 >> 20) & 0x3Fu);   
            img.csm = static_cast<uint32_t>((tex0 >> 55) & 1u);
            img.csa = static_cast<uint32_t>((tex0 >> 56) & 0x1Fu);
            img.clut = static_cast<int16_t>(rd16(desc + 0x04));
            const std::string name = "image " + std::to_string(i) + ": ";
            if (img.width == 0 || img.height == 0 || img.width > kMaxDim || img.height > kMaxDim)
            {
                error = name + "bad size";
                return false;
            }
            if (bitsPerPixel(img.psm) == 0)
            {
                error = name + "unsupported PSM " + hex(img.psm);
                return false;
            }
            if (!parseUpload(data, size, rd32(desc), img.transfers, error))
            {
                error = name + error;
                return false;
            }
            if (img.transfers.empty())
            {
                error = name + "no pixel data";
                return false;
            }
            for (const Transfer &t : img.transfers)
            {
                // Several transfers must be rectangles of one texture.
                if (t.psm != img.psm || t.dbp != img.transfers[0].dbp)
                {
                     error = name + "transfer format/address differs from TEX0";
                    return false;
                }
            }
             // Every pixel of the image must come from a transfer.
            std::vector<bool> covered(static_cast<size_t>(img.width) * img.height, false);
            size_t coveredCount = 0;
            forEachPixel(img, [&](uint32_t x, uint32_t y, const Transfer &, size_t) {
                const size_t k = static_cast<size_t>(y) * img.width + x;  
                coveredCount += covered[k] ? 0 : 1;
                covered[k] = true;
            });
            if(coveredCount != covered.size())
            {   
                error = name + "transfers do not cover the image";
                return false;
            }
             if (isPalette(img.psm))
            {
                if (img.clut < 0 || static_cast<uint32_t>(img.clut) >= clutCount)
                {
                    error = name + "bad CLUT index " + std::to_string(img.clut);
                    return false;
                }
                if (img.csm != 0 || img.csa != 0)
                {
                    error = name + "CSM2 / CSA != 0 not supported";
                    return false;
                }
                const std::vector<Transfer> &clut = layout.cluts[img.clut];
                const uint32_t entries = img.psm == kPsmT8 ? 256u : 16u;
                if (clut.size() != 1 || clut[0].psm != kPsmCt32 || clut[0].w * clut[0].h < entries)
                {
                    error = name + "CLUT is not a single PSMCT32 transfer of " + std::to_string(entries) + " colours";
                    return false;
                }
            }
        }
        return true;
    }

    uint32_t readIndex(const uint8_t *data, const Transfer &t, size_t p)

    {
        if (t.psm == kPsmT4)
        {
            const uint8_t b = data[t.offset + p / 2];
            return (p & 1) ? (b >> 4) : (b & 0xFu); // low nibble first
        }
        return data[t.offset + p];
    }

    void writeIndex(uint8_t *data, const Transfer &t, size_t p, uint32_t index)
     {
        if (t.psm == kPsmT4)
        {
            uint8_t &b = data[t.offset + p / 2];
            b = (p & 1) ? static_cast<uint8_t>((b & 0x0Fu) | (index << 4))
                        : static_cast<uint8_t>((b & 0xF0u) | (index & 0xFu));
            return;
        }
        data[t.offset + p] = static_cast<uint8_t>(index);
    }

    uint8_t expand5(uint32_t v)
    {
        return static_cast<uint8_t>((v << 3) | (v >> 2));
    }

    // Direct colour pixel -> PC RGBA.
    void readDirect(const uint8_t *data, const Transfer &t, size_t p, bool gsScale, uint8_t *rgba)
    {  
        if (t.psm == kPsmCt32)
        {
            const uint8_t *s = data + t.offset + p * 4;
            rgba[0] = s[0];
            rgba[1] = s[1];
            rgba[2] = s[2] ;
            rgba[3] = alphaToPc(s[3], gsScale);
        }
        else if (t.psm == kPsmCt24)
        {
            const uint8_t *s = data + t.offset + p * 3;

            rgba[0] = s[0];
            rgba[1] = s[1];
            rgba[2] = s[2];
            rgba[3] = 255; // the GS uses TEXA.TA0 (0x80 in practice)
        }
        else // CT16 / CT16S: A1 B5 G5 R5
        {
            const uint16_t v = rd16(data + t.offset + p * 2);
            rgba[0] = expand5(v & 0x1Fu);
            rgba[1] = expand5((v >> 5) & 0x1Fu);
            rgba[2] = expand5((v >> 10) & 0x1Fu);
            rgba[3] = (v & 0x8000u) ? 255 : 0; // TEXA.TA1 / AEM ignored
        }
    }

    void writeDirect(uint8_t *data, const Transfer &t, size_t p, bool gsScale, const uint8_t *rgba)
    {
         if (t.psm == kPsmCt32)

        {
            uint8_t *d = data + t.offset + p * 4;
            d[0] = rgba[0];
            d[1] = rgba[1];
            d[2] = rgba[2];
            d[3] = alphaToPs2(rgba[3], gsScale);
        }
        else if (t.psm == kPsmCt24)
        {
            uint8_t *d = data + t.offset + p * 3;   
            d[0] =  rgba[0];
            d[1] = rgba[1];
            d[2] = rgba[2];
        }
        else
        {
            uint8_t *d = data + t.offset + p * 2;
            const uint16_t old =  rd16(d);   
            uint16_t v = static_cast<uint16_t>((rgba[0] >> 3) | ((rgba[1] >> 3) << 5) | ((rgba[2] >> 3) << 10));

            if (rgba[3] >= 128)
                v |= 0x8000u; 
            // Keep the stored value when it decodes to the same colour.
             uint8_t cur[4];
            readDirect(data, t, p, gsScale, cur);
            if (std::memcmp(cur, rgba, 4) == 0)

                v = old; 
            d[0] = static_cast<uint8_t>(v);
            d[1] =  static_cast<uint8_t>(v >> 8);
        }
    }

    // CLUT entry `i` of an image in the CLUT transfer data (PSMCT32).
     const uint8_t *clutEntry(const uint8_t *data, const Layout &layout, const ImageInfo &img, uint32_t i)
    {
        // CSM1: a 16x16 CLUT stores entries 8..15 and 16..23 of each 32 swapped.
        if (img.psm == kPsmT8)
            i = (i & 0xE7u) | ((i & 0x08u) << 1) | ((i & 0x10u) >> 1);
        return data + layout.cluts[img.clut][0].offset + i * 4;
    }

    // True when every alpha the image uses is <= 0x80 (GS scale).
    bool usesGsScale(const uint8_t *data, const Layout &layout, const ImageInfo &img)
    {
        uint32_t maxAlpha = 0;
        forEachPixel(img, [&](uint32_t, uint32_t, const Transfer &t, size_t p) {
            if (isPalette(img.psm))
                maxAlpha = std::max<uint32_t>(maxAlpha, clutEntry(data, layout, img, readIndex(data, t, p))[3]);
            else if (img.psm == kPsmCt32)
                maxAlpha = std::max<uint32_t>(maxAlpha, data[t.offset + p * 4 + 3]);
        });
        return maxAlpha <= 0x80u;
    }

    // The image's palette as PC RGBA words (R in the low byte), by index.
    std::vector<uint32_t> readPalette(const uint8_t *data, const Layout &layout, const ImageInfo &img, bool gsScale)
    {
        std::vector<uint32_t> pal(img.psm == kPsmT8 ? 256u : 16u);
        for (uint32_t i =  0; i < pal.size(); ++i)
        {
            const uint8_t *s = clutEntry(data, layout, img, i); 
            pal[i] = s[0] | (s[1] << 8) | (s[2] << 16) | (static_cast<uint32_t>(alphaToPc(s[3], gsScale)) << 24);
        }
        return pal;
    }

    uint32_t pack(const uint8_t *rgba)
     {

        return rgba[0] | (rgba[1] << 8) | (rgba[2] << 16) | (static_cast<uint32_t>(rgba[3]) << 24);
    }


    uint32_t distance(uint32_t a, uint32_t b)
    {
        uint32_t sum = 0;
        for (int s =  0; s < 32; s += 8)
        {
            const int d = static_cast<int>((a >> s) & 0xFFu) - static_cast<int>((b >> s) & 0xFFu);
            sum += static_cast<uint32_t>(d * d);
        }
        return sum;
    }


    std::vector<uint32_t> medianCut(const std::unordered_map<uint32_t, uint32_t> &counts, size_t size)
    {
        struct Entry
        {
            uint32_t colour;
            uint32_t count;
        } ;
        struct Box
        {
            size_t begin, end;
            uint32_t range; // widest channel range
            int channel;
        };
        std::vector<Entry> all;
        all.reserve(counts.size());
        for (const auto &[colour, count] : counts)
            all.push_back({colour, count});
        auto channel = [](uint32_t c, int s) { return (c >> (s * 8)) & 0xFFu; };
        auto makeBox = [&](size_t begin, size_t end)
        { 
            Box box{begin, end, 0, 0};
            for (int s = 0; s < 4; ++s)
            {
                uint32_t lo = 255, hi = 0;
                for (size_t i = begin; i < end; ++i)
                {
                    lo = std::min(lo, channel(all[i].colour, s));
                    hi = std::max(hi, channel(all[i].colour, s));
                }
                if (hi - lo > box.range || s == 0)
                {
                    box.range = hi - lo;
                    box.channel = s;
                }
            }
            return box;
        };
         std::vector<Box> boxes{makeBox(0, all.size())};
        while (boxes.size() < size)
        {
            size_t pick = boxes.size();   
            for (size_t k = 0; k < boxes.size(); ++k)
            {
                if (boxes[k].end - boxes[k].begin >= 2 && boxes[k].range > 0 &&
                    (pick == boxes.size() || boxes[k].range > boxes[pick].range))
                    pick = k;
            }
            if (pick == boxes.size())
                break;
            const Box box = boxes[pick];
            std::sort(all.begin() + box.begin, all.begin() + box.end, [&](const Entry &a, const Entry &b)
                      { return channel(a.colour, box.channel) < channel(b.colour, box.channel); });

            uint64_t total = 0, acc = 0;
            for (size_t i = box.begin; i < box.end; ++i)
                total += all[i].count;
            size_t mid = box.begin + 1;
            for (size_t i = box.begin; i + 1 < box.end; ++i)
            {

                acc += all[i].count;
                mid = i + 1;
                if (acc * 2 >= total)
                    break;
            }
            boxes[pick] = makeBox(box.begin, mid);  
            boxes.push_back(makeBox(mid, box.end));
         }
        std::vector<uint32_t> pal;   
        for (const Box &box : boxes)
        {
            uint64_t sum[4] = {}, n = 0;
            for (size_t i = box.begin; i < box.end; ++i)
            {
                for (int s = 0; s < 4; ++s)
                    sum[s] += uint64_t(channel(all[i].colour, s)) * all[i].count;
                n += all[i].count;
            }
            uint32_t c = 0;

            for (int s = 0; s < 4; ++s)
                c |= static_cast<uint32_t>(n ? (sum[s] + n / 2) / n : 0) << (s * 8);
            pal.push_back(c);
        }
         pal.resize(size, pal.empty() ? 0u : pal.back());
        return pal;
    } 
}

namespace dk_formats
{
    bool wzimDecode(const uint8_t *data, size_t size, std::vector<WzimImage> &images, std::string &error)
    {
         images.clear();
        Layout layout; 

        if (!parseLayout(data, size, layout, error))
            return false;
        images.resize(layout.images.size());
        for (size_t i = 0; i < layout.images.size(); ++i)
        {
             const ImageInfo &img = layout.images[i];
            WzimImage &out = images[i];
            out.width = img.width;
            out.height = img.height;
            out.rgba.assign(static_cast<size_t>(img.width) * img.height * 4, 0);
            uint8_t *dst = out.rgba.data();
            const bool gsScale = usesGsScale(data, layout, img) ;
            if (isPalette(img.psm))

            {
                const std::vector<uint32_t> pal = readPalette(data, layout, img, gsScale);
                forEachPixel(img, [&](uint32_t x, uint32_t y, const Transfer &t, size_t p) {
                    const uint32_t c = pal[readIndex(data, t, p)];
                    uint8_t *d =  dst + (static_cast<size_t>(y) * img.width + x) * 4;
                    d[0] = static_cast<uint8_t>(c);
                    d[1] = static_cast<uint8_t>(c >> 8);
                    d[2] = static_cast<uint8_t>(c >> 16);
                    d[3] = static_cast<uint8_t>(c >> 24) ;
                });
            }
            else
            {
                forEachPixel(img, [&](uint32_t x, uint32_t y, const Transfer &t, size_t p) {

                    readDirect(data, t, p, gsScale, dst + (static_cast<size_t>(y) * img.width + x) * 4);
                });
            }
        }
        return true;
    }

    bool wzimEncode(std::vector<uint8_t> &data, const std::vector<WzimImage> &images, std::string &error)
    {
        Layout layout;
        if (!parseLayout(data.data(), data.size(), layout, error))
            return false;
        if (images.size() != layout.images.size())
        {
            error = "image count " + std::to_string(images.size()) + " != " + std::to_string(layout.images.size());
            return false;
        }   
        for (size_t i = 0; i < images.size(); ++i)
        {
            const ImageInfo &img = layout.images[i];
            if (images[i].width != img.width || images[i].height != img.height ||
                images[i].rgba.size() != static_cast<size_t>(img.width) * img.height * 4)

             {
                error = "image " + std::to_string(i) + ": size differs from the record (" + std::to_string(img.width) +
                        "x" + std::to_string(img.height) + ")";
                return false;
            }
        }

        uint8_t *bytes = data.data();
        for (size_t i = 0; i < images.size(); ++i)
        {
            const ImageInfo &img = layout.images[i];
            const uint8_t *src = images[i].rgba.data();
            const bool gsScale = usesGsScale(bytes, layout, img); // from the original data
            if (!isPalette(img.psm))
            {
                forEachPixel(img, [&](uint32_t x, uint32_t y, const Transfer &t, size_t p) {
                    writeDirect(bytes, t, p, gsScale, src + (static_cast<size_t>(y) * img.width + x) * 4);
                });
                continue;
            }

            std::vector<uint32_t> pal = readPalette(bytes, layout, img, gsScale);
            std::unordered_map<uint32_t, uint32_t> counts;
            forEachPixel(img, [&](uint32_t x, uint32_t y, const Transfer &, size_t) {
                 ++counts[pack(src + (static_cast<size_t>(y) * img.width + x) * 4)];
            });
            const std::unordered_set<uint32_t> inPalette(pal.begin(), pal.end());
            const bool fits = std::all_of(counts.begin(), counts.end(),
                                          [&](const auto &kv) { return inPalette.count(kv.first) != 0; }) ;
            const bool ownClut = std::count_if(layout.images.begin(), layout.images.end(),
                                               [&](const ImageInfo &o) { return o.clut == img.clut; }) == 1;
            if (!fits && ownClut)
            {
                const std::vector<uint32_t> fresh = medianCut(counts, pal.size());
                for (uint32_t k = 0; k < fresh.size(); ++k)
                {

                    uint8_t *e = bytes + (clutEntry(bytes, layout, img, k) - bytes);
                    e[0] = static_cast<uint8_t>(fresh[k]);

                    e[1] = static_cast<uint8_t>(fresh[k] >> 8);
                    e[2] = static_cast<uint8_t>(fresh[k] >> 16);
                    e[3] = alphaToPs2(static_cast<uint8_t>(fresh[k] >> 24), gsScale);
                }
                pal = readPalette(bytes, layout, img, gsScale);
            }
            std::vector<bool> used(pal.size(), false);
            forEachPixel(img, [&](uint32_t, uint32_t, const Transfer &t, size_t p) { used[readIndex(bytes, t, p)] = true; });
            std::unordered_map<uint32_t, uint32_t> best;
            for (int pass = 0; pass < 2; ++pass)

                for (uint32_t k = 0; k < pal.size(); ++k)
                    if (used[k] == (pass == 0))
                        best.emplace(pal[k], k);
            auto lookup = [&](uint32_t c) {
                auto it = best.find(c);
                if (it != best.end())

                    return it->second;
                uint32_t bestIndex = 0;
                uint32_t bestDist = UINT32_MAX;

                bool bestUsed = false;
                for (uint32_t k = 0; k < pal.size(); ++k)
                {
                    const uint32_t d = distance(c, pal[k]) ;
                    if (d < bestDist || (d == bestDist && used[k] && !bestUsed))
                    {
                        bestIndex = k;
                        bestDist = d;
                        bestUsed = used[k];
                    }
                }
                best.emplace(c, bestIndex);
                return bestIndex;
            };
            forEachPixel(img, [&](uint32_t x, uint32_t y, const Transfer &t, size_t p) {
                const uint32_t c = pack(src + (static_cast<size_t>(y) * img.width + x) * 4);
                 const uint32_t old =  readIndex(bytes, t, p);
                // An unchanged pixel keeps its index (byte-exact round trip).
                writeIndex(bytes, t, p, pal[old] == c ? old : lookup(c));

            });
        }
        return true;
    }
} 
