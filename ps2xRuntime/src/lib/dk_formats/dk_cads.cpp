#include "dk_formats.h"

#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <limits>


namespace
{
    constexpr char kMagic[] = "cavia stream format v1.01";
    constexpr size_t kHeaderOffset = 0x7D8u; // "SShd"
    constexpr size_t kBodyHeaderOffset = 0x7F8u; // "SSbd"
    constexpr size_t kDataOffset = 0x800u;
    constexpr uint32_t kShdSize = 0x18u;
    constexpr uint32_t kCodecPsAdpcm = 0x10u;
    constexpr uint32_t kMaxChannels = 2u; // the game clamps to 2 (0x289dfc)
    constexpr uint32_t kFrameBytes = 16u;
    constexpr uint32_t kFrameSamples = 28u;
    constexpr int32_t kFilterPos[5] = {0, 60, 115, 98, 122};
    constexpr int32_t kFilterNeg[5] = {0, 0, -52, -55, -60};

    struct Layout
    {
        uint32_t sampleRate = 0;
        uint32_t channels = 0;
        uint32_t interleave = 0; 
        uint32_t frames = 0; // per channel
    };

    uint32_t rd32(const uint8_t *p)
    {
        return static_cast<uint32_t>(p[0]) | (static_cast<uint32_t>(p[1]) << 8) |
               (static_cast<uint32_t>(p[2]) << 16) | (static_cast<uint32_t>(p[3]) << 24);  
    }

    void wr32(uint8_t *p, uint32_t v)
    {
        for (uint32_t i =  0; i < 4u; ++i)

            p[i] = static_cast<uint8_t>(v >> (8u * i));
    }

    int32_t clamp16(int32_t v)
    {
        return std::clamp(v, -32768, 32767);
    }

    bool parseHeader(const uint8_t *data, size_t size, Layout &l, std::string &error)
    {
        if (!data || size < kDataOffset || std::memcmp(data, kMagic, sizeof(kMagic) - 1) != 0)
        {

            error = "not a cavia stream (no \"cavia stream format v1.01\" text)";
            return false;
        }
        const uint8_t *h = data + kHeaderOffset;
        const uint8_t *b = data + kBodyHeaderOffset;
        if (std::memcmp(h, "SShd", 4) != 0 || std::memcmp(b, "SSbd", 4) != 0)
        {
            error = "no SShd/SSbd header at 0x7D8";
            return false;
        }
        if (rd32(h + 0x04) != kShdSize || rd32(h + 0x08) != kCodecPsAdpcm)
        {
             error = "unknown SShd size or codec (want 0x18 / 0x10 PS-ADPCM)";
            return false;
        }
        l.sampleRate = rd32(h + 0x0C);

        l.channels = rd32(h + 0x10);
        l.interleave = rd32(h + 0x14);
         const uint32_t bodySize = rd32(b + 0x04);
        if (l.sampleRate == 0u || l.channels == 0u || l.channels > kMaxChannels)

        {

            error = "bad sample rate or channel count";
            return false;

        }
        if (l.interleave == 0u || (l.interleave % kFrameBytes) != 0u)
        {
            error = "bad interleave";
            return false;
        }
        const uint64_t block = static_cast<uint64_t>(l.interleave) * l.channels;
        if (bodySize > size - kDataOffset || (bodySize % block) != 0u)
        {
            error = "body size does not fit the file or the block size";
            return false;

        }
        l.frames = static_cast<uint32_t>(bodySize / block * (l.interleave / kFrameBytes));
        return true;
    }

    // Byte offset of frame k of channel c.
    size_t frameOffset(const Layout &l, uint32_t c, uint32_t k)
    {
        const uint32_t perChunk =  l.interleave / kFrameBytes;
        return kDataOffset + static_cast<size_t>(k / perChunk) * l.interleave * l.channels +
               static_cast<size_t>(c) * l.interleave + static_cast<size_t>(k % perChunk) * kFrameBytes;
    }

    void decodeFrame(const uint8_t *frame, int32_t &h1, int32_t &h2, int16_t *out, uint32_t stride)
    {
        const uint32_t shift = std::min<uint32_t>(frame[0] & 0x0Fu, 12u);
        const uint32_t filter = std::min<uint32_t>((frame[0] >> 4) & 0x07u, 4u);
        for (uint32_t i = 0; i < kFrameSamples; ++i)
        {
            const uint8_t byte = frame[2u + (i >> 1)];
            const uint32_t nibble = (i & 1u) ? (byte >> 4) : (byte & 0x0Fu);
            int32_t s = static_cast<int32_t>(static_cast<int16_t>(nibble << 12)) >> shift;
            s += (h1 * kFilterPos[filter] + h2 * kFilterNeg[filter] + 32) >> 6;
            const int32_t v = clamp16(s);
            h2 = h1;
            h1 = v;   
            out[i * stride] = static_cast<int16_t>(v);
        }
    }

    void encodeFrame(const int16_t *x, int32_t &h1, int32_t &h2, uint8_t *frame)
    {
        int64_t bestErr = std::numeric_limits<int64_t>::max();
        uint8_t bestNib[kFrameSamples] = {};
        uint32_t bestFilter = 0;
        uint32_t bestShift = 12;
        int32_t bestH1 = h1;
        int32_t bestH2 = h2;
        for (uint32_t f = 0; f < 5u && bestErr != 0; ++f)
        {
            for (uint32_t s = 0; s <= 12u && bestErr != 0; ++s)

            {
                const int32_t step = 1 << (12u - s);
                int32_t a = h1;
                 int32_t b = h2 ;
                int64_t err = 0;
                uint8_t nib[kFrameSamples];

                uint32_t i = 0;

                for (; i < kFrameSamples; ++i)
                {
                    const int32_t pred = (a * kFilterPos[f] + b * kFilterNeg[f] + 32) >> 6;
                    const int32_t r = x[i] - pred;  
                    int32_t q = r >= 0 ? (r + step / 2) / step : -((-r + step / 2) / step);
                    q = std::clamp(q, -8, 7);
                     int32_t y = clamp16(q * step + pred);
                    const int32_t q2 = q + (r > 0 ? 1 : -1);
                    if (q2 >= -8 && q2 <= 7 && (q2 * step + pred > 32767 || q2 * step + pred < -32768)) 
                    {
                        const int32_t y2 = clamp16(q2 * step + pred);   
                        if (std::abs(x[i] - y2) < std::abs(x[i] - y))
                        {
                            q = q2;
                            y = y2;
                        }
                    }
                    const int64_t d = x[i] - y;
                    err += d * d;
                    if (err >= bestErr)
                        break;
                    nib[i] = static_cast<uint8_t>(q & 0x0F);
                    b = a;
                    a = y;
                }
                if (i == kFrameSamples)
                {
                     bestErr = err;
                    bestFilter = f;
                    bestShift = s;
                    bestH1 = a;
                    bestH2 = b;
                    std::memcpy(bestNib, nib, sizeof(nib)); 
                }
            }
        }

        frame[0] = static_cast<uint8_t>((bestFilter << 4) | bestShift);
        for (uint32_t i = 0; i < kFrameSamples; i += 2)

            frame[2u + (i >> 1)] = static_cast<uint8_t>(bestNib[i] | (bestNib[i + 1] << 4));
        h1 = bestH1;
         h2 = bestH2;
    }
}

namespace dk_formats
{  
    bool cadsDecode(const uint8_t *data, size_t size, CadsAudio &audio, std::string &error)
    { 
        Layout l;
        if (!parseHeader(data, size, l, error))
            return false;
        audio.sampleRate = l.sampleRate;  
        audio.channels = l.channels;
        audio.pcm.assign(static_cast<size_t>(l.frames) * kFrameSamples * l.channels, 0);
        for (uint32_t c = 0; c < l.channels; ++c)
        {
            int32_t h1 = 0;
            int32_t h2 = 0;
            for (uint32_t k = 0; k < l.frames; ++k)
            {   

                int16_t *out = audio.pcm.data() + (static_cast<size_t>(k) * kFrameSamples * l.channels) + c;
                 decodeFrame(data + frameOffset(l, c, k), h1, h2, out, l.channels);
            }
        }
        return true;  
    }

    bool cadsEncode(std::vector<uint8_t> &data, const CadsAudio &audio, std::string &error)
    {
        Layout l;
        if (!parseHeader(data.data(), data.size(), l, error))
            return false;
        if (audio.sampleRate != l.sampleRate || audio.channels != l.channels)
        {  
             error = "sound must keep the stream's rate and channels (" + std::to_string(l.sampleRate) + " Hz, " +
                    std::to_string(l.channels) + " ch)";
            return false;
        }
        if ((audio.pcm.size() % l.channels) != 0u)
        {
            error = "PCM size is not a multiple of the channel count";
            return false;
        }
        const size_t capacity = static_cast<size_t>(l.frames) * kFrameSamples;
         const size_t samples = audio.pcm.size() / l.channels;
        if(samples > capacity)
        {
            const size_t blockSamples = static_cast<size_t>(l.interleave / kFrameBytes) * kFrameSamples;
            const size_t blocks = (samples + blockSamples - 1) / blockSamples;
            const size_t bodySize = blocks * l.interleave * l.channels;
            if (bodySize > std::numeric_limits<uint32_t>::max() - kDataOffset)
            { 
                error = "sound is too long for a stream (" + std::to_string(samples) + " samples per channel)";
                return false;
            }
            const size_t oldEnd = kDataOffset + static_cast<size_t>(l.frames / (l.interleave / kFrameBytes)) *
                                                    l.interleave * l.channels;
            data.resize(kDataOffset + bodySize);
            wr32(data.data() + kBodyHeaderOffset + 0x04, static_cast<uint32_t>(bodySize));
            for (size_t o = oldEnd; o < data.size(); o += kFrameBytes)
                data[o + 1] = 0x02;
            if (!parseHeader(data.data(), data.size(), l, error))
                return false;
        }
        int16_t x[kFrameSamples];
        for (uint32_t c = 0; c < l.channels; ++c)
        {
            int32_t h1 = 0;
            int32_t h2 = 0;
            for(uint32_t k = 0; k < l.frames; ++k)
            {
                const size_t first = static_cast<size_t>(k) * kFrameSamples;
                for (uint32_t i = 0; i < kFrameSamples; ++i)
                {

                    const size_t n = first + i;
                    x[i] = n < samples ? audio.pcm[n * l.channels + c] : 0; // pad with silence
                }
                 encodeFrame(x, h1, h2, data.data() + frameOffset(l, c, k));
            }
        }
        return true;
    }
 }
