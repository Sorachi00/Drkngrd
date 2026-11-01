#ifndef PS2_RUNTIME_MACROS_H
#define PS2_RUNTIME_MACROS_H
#include <cstdint>
#include <cmath>
#include <cstring>
#include <bit>
#if defined(_MSC_VER)
#include <intrin.h>
#elif defined(USE_SSE2NEON)
#include "sse2neon.h"
#else
#include <immintrin.h> // For SSE/AVX intrinsics
#endif

#include "ps2_runtime.h"

static inline int32_t Ps2ExtractEpi32(__m128i v, int index)
{
    switch (index & 3)
    {
    case 0:
        return _mm_extract_epi32(v, 0);
    case 1:
        return _mm_extract_epi32(v, 1);
    case 2:
        return _mm_extract_epi32(v, 2);
    default:
        return _mm_extract_epi32(v, 3);
    }
}

static inline int64_t Ps2ExtractEpi64(__m128i v, int index)
{
    if ((index & 1) == 0)
    {
        return _mm_cvtsi128_si64(v);
    }
    else
    {
        return _mm_extract_epi64(v, 1);
    }
}

static inline uint32_t ps2_clz32(uint32_t x)
{
    return static_cast<uint32_t>(std::countl_zero(x));
}

static inline uint64_t Ps2HiLoToU64(uint64_t hi, uint64_t lo)
{
    return ((hi & 0xFFFFFFFFull) << 32) | (lo & 0xFFFFFFFFull);
}

static inline uint64_t Ps2SignExt32ToU64(uint32_t v)
{
    return (uint64_t)(int64_t)(int32_t)v;
}

// PLZCW: Count leading bits that match the sign bit, minus 1.
// For positive values: count leading zeros minus 1 (excludes sign bit).
// For negative values: count leading ones minus 1 (excludes sign bit).
// Special cases: 0x00000000 -> 31, 0xFFFFFFFF -> 31.
static inline uint32_t ps2_plzcw32(uint32_t x)
{
    if (x == 0 || x == 0xFFFFFFFF)
        return 31;
    if (x & 0x80000000u)
        x = ~x; // If sign bit set, invert to count leading ones as zeros
    return static_cast<uint32_t>(std::countl_zero(x)) - 1;
}

#define PS2_BLENDV_PS(a, b, mask) _mm_blendv_ps((a), (b), (mask))
#define PS2_MIN_EPI32(a, b) _mm_min_epi32((a), (b))
#define PS2_MAX_EPI32(a, b) _mm_max_epi32((a), (b))
#define PS2_SHUFFLE_EPI8(v, mask) _mm_shuffle_epi8((v), (mask))

#define PS2_EXTRACT_EPI32(v, i) Ps2ExtractEpi32((v), (i))
#define PS2_EXTRACT_EPI64(v, i) Ps2ExtractEpi64((v), (i))

#define PS2_EXTRACT_EPI32_0(v) Ps2ExtractEpi32((v), 0)
#define PS2_EXTRACT_EPI32_1(v) Ps2ExtractEpi32((v), 1)
#define PS2_EXTRACT_EPI32_2(v) Ps2ExtractEpi32((v), 2)
#define PS2_EXTRACT_EPI32_3(v) Ps2ExtractEpi32((v), 3)

#define PS2_EXTRACT_EPI64_0(v) Ps2ExtractEpi64((v), 0)
#define PS2_EXTRACT_EPI64_1(v) Ps2ExtractEpi64((v), 1)

// Basic MIPS arithmetic operations
#define ADD32(a, b) ((uint32_t)((a) + (b)))
#define ADD32_OV(rs, rt, result32, overflow)              \
    do                                                    \
    {                                                     \
        int32_t _a = (int32_t)(rs);                       \
        int32_t _b = (int32_t)(rt);                       \
        int32_t _r = _a + _b;                             \
        overflow = (((_a ^ _b) >= 0) && ((_a ^ _r) < 0)); \
        result32 = (uint32_t)_r;                          \
    } while (0);
#define SUB32(a, b) ((uint32_t)((a) - (b)))
#define SUB32_OV(rs, rt, result32, overflow)             \
    do                                                   \
    {                                                    \
        int32_t _a = (int32_t)(rs);                      \
        int32_t _b = (int32_t)(rt);                      \
        int32_t _r = _a - _b;                            \
        overflow = (((_a ^ _b) < 0) && ((_a ^ _r) < 0)); \
        result32 = (uint32_t)_r;                         \
    } while (0);
#define MUL32(a, b) ((uint32_t)((a) * (b)))
#define DIV32(a, b) ((uint32_t)((a) / (b)))
#define AND32(a, b) ((uint32_t)((a) & (b)))
#define OR32(a, b) ((uint32_t)((a) | (b)))
#define XOR32(a, b) ((uint32_t)((a) ^ (b)))
#define NOR32(a, b) ((uint32_t)(~((a) | (b))))
#define SLL32(a, b) ((uint32_t)((a) << (b)))
#define SRL32(a, b) ((uint32_t)((a) >> (b)))
#define SRA32(a, b) ((uint32_t)((int32_t)(a) >> (b)))
#define SLT32(a, b) ((uint32_t)((int32_t)(a) < (int32_t)(b) ? 1 : 0))
#define SLTU32(a, b) ((uint32_t)((a) < (b) ? 1 : 0))

// PS2-specific 128-bit MMI operations
#define PS2_PEXTLW(a, b) _mm_unpacklo_epi32((__m128i)(b), (__m128i)(a))
#define PS2_PEXTUW(a, b) _mm_unpackhi_epi32((__m128i)(b), (__m128i)(a))
#define PS2_PEXTLH(a, b) _mm_unpacklo_epi16((__m128i)(b), (__m128i)(a))
#define PS2_PEXTUH(a, b) _mm_unpackhi_epi16((__m128i)(b), (__m128i)(a))
#define PS2_PEXTLB(a, b) _mm_unpacklo_epi8((__m128i)(b), (__m128i)(a))
#define PS2_PEXTUB(a, b) _mm_unpackhi_epi8((__m128i)(b), (__m128i)(a))
#define PS2_PADDW(a, b) _mm_add_epi32((__m128i)(a), (__m128i)(b))
#define PS2_PSUBW(a, b) _mm_sub_epi32((__m128i)(a), (__m128i)(b))
#define PS2_PMAXW(a, b) PS2_MAX_EPI32((__m128i)(a), (__m128i)(b))
#define PS2_PMINW(a, b) PS2_MIN_EPI32((__m128i)(a), (__m128i)(b))
#define PS2_PADDH(a, b) _mm_add_epi16((__m128i)(a), (__m128i)(b))
#define PS2_PSUBH(a, b) _mm_sub_epi16((__m128i)(a), (__m128i)(b))
#define PS2_PMAXH(a, b) _mm_max_epi16((__m128i)(a), (__m128i)(b))
#define PS2_PMINH(a, b) _mm_min_epi16((__m128i)(a), (__m128i)(b))
#define PS2_PADDB(a, b) _mm_add_epi8((__m128i)(a), (__m128i)(b))
#define PS2_PSUBB(a, b) _mm_sub_epi8((__m128i)(a), (__m128i)(b))
#define PS2_PAND(a, b) _mm_and_si128((__m128i)(a), (__m128i)(b))
#define PS2_POR(a, b) _mm_or_si128((__m128i)(a), (__m128i)(b))
#define PS2_PXOR(a, b) _mm_xor_si128((__m128i)(a), (__m128i)(b))
#define PS2_PNOR(a, b) _mm_xor_si128(_mm_or_si128((__m128i)(a), (__m128i)(b)), _mm_set1_epi32(0xFFFFFFFF))


#define PS2_FLOAT_MAX_BITS 0x7F7FFFFFu
#define PS2_FLOAT_EXP_MASK 0x7F800000u
#define PS2_FLOAT_SIGN_MASK 0x80000000u

static inline __m128 Ps2VuNormalize(__m128 v)
{
    const __m128i bits = _mm_castps_si128(v);
    const __m128i expMask = _mm_set1_epi32((int)PS2_FLOAT_EXP_MASK);
    const __m128i sign = _mm_and_si128(bits, _mm_set1_epi32((int)PS2_FLOAT_SIGN_MASK));
    const __m128i exponent = _mm_and_si128(bits, expMask);
    const __m128i isSubnormal = _mm_cmpeq_epi32(exponent, _mm_setzero_si128());
    const __m128i isOverflow = _mm_cmpeq_epi32(exponent, expMask);
    const __m128i saturated = _mm_or_si128(sign, _mm_set1_epi32((int)PS2_FLOAT_MAX_BITS));

    __m128i out = _mm_or_si128(_mm_andnot_si128(isSubnormal, bits),
                               _mm_and_si128(isSubnormal, sign));
    out = _mm_or_si128(_mm_andnot_si128(isOverflow, out),
                       _mm_and_si128(isOverflow, saturated));
    return _mm_castsi128_ps(out);
}

static inline float Ps2FloatNormalize(float value)
{
    uint32_t bits = 0;
    std::memcpy(&bits, &value, sizeof(bits));

    const uint32_t sign = bits & PS2_FLOAT_SIGN_MASK;
    const uint32_t exponent = bits & PS2_FLOAT_EXP_MASK;

    if (exponent == 0u)
    {
        bits = sign;
    }
    else if (exponent == PS2_FLOAT_EXP_MASK)
    {
        bits = sign | PS2_FLOAT_MAX_BITS;
    }
    else
    {
        return value;
    }

    std::memcpy(&value, &bits, sizeof(value));
    return value;
}

static inline float Ps2FloatMaxWithSign(bool negative)
{
    const uint32_t bits = PS2_FLOAT_MAX_BITS | (negative ? PS2_FLOAT_SIGN_MASK : 0u);
    float out = 0.0f;
    std::memcpy(&out, &bits, sizeof(out));
    return out;
}

static inline float Ps2VuDivide(float fs, float ft)
{
    if (ft == 0.0f)
    {
        return Ps2FloatMaxWithSign(std::signbit(fs) != std::signbit(ft));
    }
    return Ps2FloatNormalize(fs / ft);
}

static inline float Ps2VuSqrt(float ft)
{
    return Ps2FloatNormalize(sqrtf(fabsf(ft)));
}

static inline float Ps2VuRSqrt(float fs, float ft)
{
    const float root = sqrtf(fabsf(ft));
    if (root == 0.0f)
    {
        return Ps2FloatMaxWithSign(std::signbit(fs) != std::signbit(ft));
    }
    return Ps2FloatNormalize(fs / root);
}

static inline void Ps2Vu0MacUpdate(uint32_t &macFlags, uint16_t &status, __m128 res, uint8_t destMask)
{
    alignas(16) float lanes[4];
    _mm_store_ps(lanes, res);
    uint32_t mac = 0u, st = 0u;
    for (int c = 0; c < 4; ++c)
    {
        const uint32_t lane = 1u << (3 - c);
        if ((destMask & lane) == 0u)
            continue;
        uint32_t bits = 0u;
        std::memcpy(&bits, &lanes[c], sizeof(bits));
        uint32_t f = (bits & 0x80000000u) ? 2u : 0u;
        if ((bits & 0x7FFFFFFFu) == 0u)
            f |= 1u;
        if (f & 1u)
            mac |= lane;
        if (f & 2u)
            mac |= lane << 4;
        st |= f;
    }
    macFlags = mac;
    status = (uint16_t)((status & 0xFF0u) | st | (st << 6));
}

static inline __m128i Ps2VuOrderKey(__m128i bits)
{
    return _mm_xor_si128(bits, _mm_and_si128(_mm_srai_epi32(bits, 31), _mm_set1_epi32(0x7FFFFFFF)));
}

static inline __m128 Ps2VuMax(__m128 a, __m128 b)
{
    const __m128i ia = _mm_castps_si128(a);
    const __m128i ib = _mm_castps_si128(b);
    const __m128i keep = _mm_cmpgt_epi32(Ps2VuOrderKey(ia), Ps2VuOrderKey(ib));
    return _mm_castsi128_ps(_mm_blendv_epi8(ib, ia, keep));
}

static inline __m128 Ps2VuMin(__m128 a, __m128 b)
{
    const __m128i ia = _mm_castps_si128(a);
    const __m128i ib = _mm_castps_si128(b);
    const __m128i keep = _mm_cmpgt_epi32(Ps2VuOrderKey(ib), Ps2VuOrderKey(ia));
    return _mm_castsi128_ps(_mm_blendv_epi8(ib, ia, keep));
}

#define PS2_VU0_MAC_UPDATE(ctx, res, mask) Ps2Vu0MacUpdate((ctx)->vu0_mac_flags, (ctx)->vu0_status, (res), (mask))

// The VU adder keeps one guard bit: the smaller operand loses its bits below it
// (real PS2: ps2autotests vu/games/triace; PCSX2 PR #12001 PS2Float::Add).
static inline uint32_t Ps2VuDropBitsBelowGuard(uint32_t bits, int shift)
{
    if (shift >= 25)
        return bits & PS2_FLOAT_SIGN_MASK;
    if (shift >= 2)
        return bits & (~0u << (shift - 1));
    return bits;
}

static inline __m128 Ps2VuAdd(__m128 a, __m128 b)
{
    alignas(16) uint32_t x[4];
    alignas(16) uint32_t y[4];
    _mm_store_si128(reinterpret_cast<__m128i *>(x), _mm_castps_si128(a));
    _mm_store_si128(reinterpret_cast<__m128i *>(y), _mm_castps_si128(b));
    for (int i = 0; i < 4; ++i)
    {
        const int difference = static_cast<int>((x[i] >> 23) & 0xFFu) - static_cast<int>((y[i] >> 23) & 0xFFu);
        if (difference > 0)
            y[i] = Ps2VuDropBitsBelowGuard(y[i], difference);
        else
            x[i] = Ps2VuDropBitsBelowGuard(x[i], -difference);
    }
    const __m128 alignedA = _mm_castsi128_ps(_mm_load_si128(reinterpret_cast<const __m128i *>(x)));
    const __m128 alignedB = _mm_castsi128_ps(_mm_load_si128(reinterpret_cast<const __m128i *>(y)));
    return Ps2VuNormalize(_mm_add_ps(alignedA, alignedB));
}

// PS2 VU (Vector Unit) operations
#define PS2_VADD(a, b) Ps2VuAdd((__m128)(a), (__m128)(b))
#define PS2_VSUB(a, b) Ps2VuAdd((__m128)(a), _mm_xor_ps((__m128)(b), _mm_set1_ps(-0.0f)))
#define PS2_VMUL(a, b) Ps2VuNormalize(_mm_mul_ps((__m128)(a), (__m128)(b)))
#define PS2_VDIV(a, b) _mm_div_ps((__m128)(a), (__m128)(b))
#define PS2_VMULQ(a, q) _mm_mul_ps((__m128)(a), _mm_set1_ps(q))
#define PS2_VBLEND(a, b, mask) PS2_BLENDV_PS((__m128)(a), (__m128)(b), (__m128)(mask))

// Memory access helpers - Hybrid Fast/Slow Path
// Fast path: Direct RDRAM access (masked).
// Slow path: Full runtime->Load/Store

static inline bool Ps2FastRangeIsContiguous(uint32_t offset, uint32_t bytes)
{
    return offset <= (PS2_RAM_SIZE - bytes);
}

static inline uint8_t Ps2FastRead8(const uint8_t *rdram, uint32_t addr)
{
    return rdram[addr & PS2_RAM_MASK];
}

static inline uint16_t Ps2FastRead16(const uint8_t *rdram, uint32_t addr)
{
    const uint32_t offset = addr & PS2_RAM_MASK;
    if (!Ps2FastRangeIsContiguous(offset, sizeof(uint16_t)))
    {
        uint8_t wrapped[sizeof(uint16_t)];
        for (uint32_t i = 0; i < sizeof(uint16_t); ++i)
        {
            wrapped[i] = rdram[(offset + i) & PS2_RAM_MASK];
        }
        uint16_t value;
        std::memcpy(&value, wrapped, sizeof(value));
        return value;
    }

    uint16_t value;
    std::memcpy(&value, rdram + offset, sizeof(value));
    return value;
}

static inline uint32_t Ps2FastRead32(const uint8_t *rdram, uint32_t addr)
{
    const uint32_t offset = addr & PS2_RAM_MASK;
    if (!Ps2FastRangeIsContiguous(offset, sizeof(uint32_t)))
    {
        uint8_t wrapped[sizeof(uint32_t)];
        for (uint32_t i = 0; i < sizeof(uint32_t); ++i)
        {
            wrapped[i] = rdram[(offset + i) & PS2_RAM_MASK];
        }
        uint32_t value;
        std::memcpy(&value, wrapped, sizeof(value));
        return value;
    }

    uint32_t value;
    std::memcpy(&value, rdram + offset, sizeof(value));
    return value;
}

static inline uint64_t Ps2FastRead64(const uint8_t *rdram, uint32_t addr)
{
    const uint32_t offset = addr & PS2_RAM_MASK;
    if (!Ps2FastRangeIsContiguous(offset, sizeof(uint64_t)))
    {
        uint8_t wrapped[sizeof(uint64_t)];
        for (uint32_t i = 0; i < sizeof(uint64_t); ++i)
        {
            wrapped[i] = rdram[(offset + i) & PS2_RAM_MASK];
        }
        uint64_t value;
        std::memcpy(&value, wrapped, sizeof(value));
        return value;
    }

    uint64_t value;
    std::memcpy(&value, rdram + offset, sizeof(value));
    return value;
}

static inline __m128i Ps2FastRead128(const uint8_t *rdram, uint32_t addr)
{
    const uint32_t offset = addr & PS2_RAM_MASK;
    if (!Ps2FastRangeIsContiguous(offset, sizeof(__m128i)))
    {
        alignas(16) uint8_t wrapped[sizeof(__m128i)];
        for (uint32_t i = 0; i < sizeof(__m128i); ++i)
        {
            wrapped[i] = rdram[(offset + i) & PS2_RAM_MASK];
        }
        __m128i value;
        std::memcpy(&value, wrapped, sizeof(value));
        return value;
    }

    __m128i value;
    std::memcpy(&value, rdram + offset, sizeof(value));
    return value;
}

static inline void Ps2FastWrite8(uint8_t *rdram, uint32_t addr, uint8_t value)
{
    rdram[addr & PS2_RAM_MASK] = value;
}

static inline void Ps2FastWrite16(uint8_t *rdram, uint32_t addr, uint16_t value)
{
    const uint32_t offset = addr & PS2_RAM_MASK;
    if (!Ps2FastRangeIsContiguous(offset, sizeof(uint16_t)))
    {
        uint8_t wrapped[sizeof(uint16_t)];
        std::memcpy(wrapped, &value, sizeof(value));
        for (uint32_t i = 0; i < sizeof(uint16_t); ++i)
        {
            rdram[(offset + i) & PS2_RAM_MASK] = wrapped[i];
        }
        return;
    }
    std::memcpy(rdram + offset, &value, sizeof(value));
}

static inline void Ps2FastWrite32(uint8_t *rdram, uint32_t addr, uint32_t value)
{
    const uint32_t offset = addr & PS2_RAM_MASK;
    if (!Ps2FastRangeIsContiguous(offset, sizeof(uint32_t)))
    {
        uint8_t wrapped[sizeof(uint32_t)];
        std::memcpy(wrapped, &value, sizeof(value));
        for (uint32_t i = 0; i < sizeof(uint32_t); ++i)
        {
            rdram[(offset + i) & PS2_RAM_MASK] = wrapped[i];
        }
        return;
    }
    std::memcpy(rdram + offset, &value, sizeof(value));
}

static inline void Ps2FastWrite64(uint8_t *rdram, uint32_t addr, uint64_t value)
{
    const uint32_t offset = addr & PS2_RAM_MASK;
    if (!Ps2FastRangeIsContiguous(offset, sizeof(uint64_t)))
    {
        uint8_t wrapped[sizeof(uint64_t)];
        std::memcpy(wrapped, &value, sizeof(value));
        for (uint32_t i = 0; i < sizeof(uint64_t); ++i)
        {
            rdram[(offset + i) & PS2_RAM_MASK] = wrapped[i];
        }
        return;
    }
    std::memcpy(rdram + offset, &value, sizeof(value));
}

static inline void Ps2FastWrite128(uint8_t *rdram, uint32_t addr, __m128i value)
{
    const uint32_t offset = addr & PS2_RAM_MASK;
    if (!Ps2FastRangeIsContiguous(offset, sizeof(__m128i)))
    {
        alignas(16) uint8_t wrapped[sizeof(__m128i)];
        std::memcpy(wrapped, &value, sizeof(value));
        for (uint32_t i = 0; i < sizeof(__m128i); ++i)
        {
            rdram[(offset + i) & PS2_RAM_MASK] = wrapped[i];
        }
        return;
    }
    std::memcpy(rdram + offset, &value, sizeof(value));
}

#define FAST_READ8(addr) Ps2FastRead8(rdram, (uint32_t)(addr))
#define FAST_READ16(addr) Ps2FastRead16(rdram, (uint32_t)(addr))
#define FAST_READ32(addr) Ps2FastRead32(rdram, (uint32_t)(addr))
#define FAST_READ64(addr) Ps2FastRead64(rdram, (uint32_t)(addr))
#define FAST_READ128(addr) Ps2FastRead128(rdram, (uint32_t)(addr))

#define FAST_WRITE8(addr, val) Ps2FastWrite8(rdram, (uint32_t)(addr), (uint8_t)(val))
#define FAST_WRITE16(addr, val) Ps2FastWrite16(rdram, (uint32_t)(addr), (uint16_t)(val))
#define FAST_WRITE32(addr, val) Ps2FastWrite32(rdram, (uint32_t)(addr), (uint32_t)(val))
#define FAST_WRITE64(addr, val) Ps2FastWrite64(rdram, (uint32_t)(addr), (uint64_t)(val))
#define FAST_WRITE128(addr, val) Ps2FastWrite128(rdram, (uint32_t)(addr), (val))

#define READ8(addr) ([&]() -> uint8_t {                       \
    uint32_t _addr = (uint32_t)(addr);                        \
    return PS2Runtime::isSpecialAddress(_addr)                \
        ? runtime->Load8(rdram, ctx, _addr)                   \
        : FAST_READ8(_addr); }())

#define READ16(addr) ([&]() -> uint16_t {                     \
    uint32_t _addr = (uint32_t)(addr);                        \
    return PS2Runtime::isSpecialAddress(_addr)                \
        ? runtime->Load16(rdram, ctx, _addr)                  \
        : FAST_READ16(_addr); }())

#define READ32(addr) ([&]() -> uint32_t {                     \
    uint32_t _addr = (uint32_t)(addr);                        \
    return PS2Runtime::isSpecialAddress(_addr)                \
        ? runtime->Load32(rdram, ctx, _addr)                  \
        : FAST_READ32(_addr); }())

#define READ64(addr) ([&]() -> uint64_t {                     \
    uint32_t _addr = (uint32_t)(addr);                        \
    return PS2Runtime::isSpecialAddress(_addr)                \
        ? runtime->Load64(rdram, ctx, _addr)                  \
        : FAST_READ64(_addr); }())

#define READ128(addr) ([&]() -> __m128i {                     \
    uint32_t _addr = (uint32_t)(addr);                        \
    return PS2Runtime::isSpecialAddress(_addr)                \
        ? runtime->Load128(rdram, ctx, _addr)                 \
        : FAST_READ128(_addr); }())

#define WRITE8(addr, val)                                                            \
    do                                                                               \
    {                                                                                \
        uint32_t _addr = (addr);                                                     \
        if (PS2Runtime::isSpecialAddress(_addr))                                     \
            runtime->Store8(rdram, ctx, _addr, (val));                               \
        else                                                                         \
        {                                                                            \
            ps2TraceGuestWrite(rdram, _addr, 1u, (uint8_t)(val), 0u, "WRITE8", ctx); \
            FAST_WRITE8(_addr, (val));                                               \
        }                                                                            \
    } while (0)

#define WRITE16(addr, val)                                                             \
    do                                                                                 \
    {                                                                                  \
        uint32_t _addr = (addr);                                                       \
        if (PS2Runtime::isSpecialAddress(_addr))                                       \
            runtime->Store16(rdram, ctx, _addr, (val));                                \
        else                                                                           \
        {                                                                              \
            ps2TraceGuestWrite(rdram, _addr, 2u, (uint16_t)(val), 0u, "WRITE16", ctx); \
            FAST_WRITE16(_addr, (val));                                                \
        }                                                                              \
    } while (0)

#define WRITE32(addr, val)                                                             \
    do                                                                                 \
    {                                                                                  \
        uint32_t _addr = (addr);                                                       \
        if (PS2Runtime::isSpecialAddress(_addr))                                       \
            runtime->Store32(rdram, ctx, _addr, (val));                                \
        else                                                                           \
        {                                                                              \
            ps2TraceGuestWrite(rdram, _addr, 4u, (uint32_t)(val), 0u, "WRITE32", ctx); \
            FAST_WRITE32(_addr, (val));                                                \
        }                                                                              \
    } while (0)

#define WRITE64(addr, val)                                                             \
    do                                                                                 \
    {                                                                                  \
        uint32_t _addr = (addr);                                                       \
        if (PS2Runtime::isSpecialAddress(_addr))                                       \
            runtime->Store64(rdram, ctx, _addr, (val));                                \
        else                                                                           \
        {                                                                              \
            ps2TraceGuestWrite(rdram, _addr, 8u, (uint64_t)(val), 0u, "WRITE64", ctx); \
            FAST_WRITE64(_addr, (val));                                                \
        }                                                                              \
    } while (0)

#define WRITE128(addr, val)                                                          \
    do                                                                               \
    {                                                                                \
        uint32_t _addr = (addr);                                                     \
        __m128i _value = (val);                                                      \
        if (PS2Runtime::isSpecialAddress(_addr))                                     \
            runtime->Store128(rdram, ctx, _addr, _value);                            \
        else                                                                         \
        {                                                                            \
            const uint64_t _lo = static_cast<uint64_t>(PS2_EXTRACT_EPI64_0(_value)); \
            const uint64_t _hi = static_cast<uint64_t>(PS2_EXTRACT_EPI64_1(_value)); \
            ps2TraceGuestWrite(rdram, _addr, 16u, _lo, _hi, "WRITE128", ctx);        \
            FAST_WRITE128(_addr, _value);                                            \
        }                                                                            \
    } while (0)

static inline void Ps2SlowPathEnter(R5900Context *ctx, uint32_t pc, uint32_t branchPc)
{
    ctx->pc = pc;
    if (branchPc != 0u)
    {
        ctx->in_delay_slot = true;
        ctx->branch_pc = branchPc;
    }
}

static inline void Ps2SlowPathLeave(R5900Context *ctx, uint32_t branchPc)
{
    if (branchPc != 0u)
        ctx->in_delay_slot = false;
}

#define PS2_READ_AT(BITS, TYPE, addr, pc, bpc) ([&]() -> TYPE {       \
    uint32_t _addr = (uint32_t)(addr);                                \
    if (!PS2Runtime::isSpecialAddress(_addr))                         \
        return FAST_READ##BITS(_addr);                                \
    Ps2SlowPathEnter(ctx, (pc), (bpc));                               \
    const TYPE _value = runtime->Load##BITS(rdram, ctx, _addr);       \
    Ps2SlowPathLeave(ctx, (bpc));                                     \
    return _value; }())

#define PS2_WRITE_AT(BITS, TYPE, addr, val, pc, bpc)                  \
    do                                                                \
    {                                                                 \
        uint32_t _addr = (uint32_t)(addr);                            \
        const TYPE _value = (TYPE)(val);                              \
        if (PS2Runtime::isSpecialAddress(_addr))                      \
        {                                                             \
            Ps2SlowPathEnter(ctx, (pc), (bpc));                       \
            runtime->Store##BITS(rdram, ctx, _addr, _value);          \
            Ps2SlowPathLeave(ctx, (bpc));                             \
        }                                                             \
        else                                                          \
        {                                                             \
            FAST_WRITE##BITS(_addr, _value);                          \
        }                                                             \
    } while (0)

#define READ8_AT(addr, pc, bpc) PS2_READ_AT(8, uint8_t, addr, pc, bpc)
#define READ16_AT(addr, pc, bpc) PS2_READ_AT(16, uint16_t, addr, pc, bpc)
#define READ32_AT(addr, pc, bpc) PS2_READ_AT(32, uint32_t, addr, pc, bpc)
#define READ64_AT(addr, pc, bpc) PS2_READ_AT(64, uint64_t, addr, pc, bpc)
#define READ128_AT(addr, pc, bpc) PS2_READ_AT(128, __m128i, addr, pc, bpc)

#define WRITE8_AT(addr, val, pc, bpc) PS2_WRITE_AT(8, uint8_t, addr, val, pc, bpc)
#define WRITE16_AT(addr, val, pc, bpc) PS2_WRITE_AT(16, uint16_t, addr, val, pc, bpc)
#define WRITE32_AT(addr, val, pc, bpc) PS2_WRITE_AT(32, uint32_t, addr, val, pc, bpc)
#define WRITE64_AT(addr, val, pc, bpc) PS2_WRITE_AT(64, uint64_t, addr, val, pc, bpc)
#define WRITE128_AT(addr, val, pc, bpc) PS2_WRITE_AT(128, __m128i, addr, val, pc, bpc)

// Packed Compare Greater Than (PCGT)
#define PS2_PCGTW(a, b) _mm_cmpgt_epi32((__m128i)(a), (__m128i)(b))
#define PS2_PCGTH(a, b) _mm_cmpgt_epi16((__m128i)(a), (__m128i)(b))
#define PS2_PCGTB(a, b) _mm_cmpgt_epi8((__m128i)(a), (__m128i)(b))

// Packed Add with Signed Saturation Word (PADDSW)
inline __m128i ps2_paddsw(__m128i a, __m128i b)
{

    __m128i sum = _mm_add_epi32(a, b);
    // Check for over/underflow. Clamp to either INT32_MIN/INT32_MAX.
    __m128i overflow = _mm_and_si128(_mm_xor_si128(a, sum),
                                     _mm_xor_si128(b, sum));
    // Extract input sign.
    overflow = _mm_srai_epi32(overflow, 31);
    __m128i input_sign = _mm_srai_epi32(a, 31);
    // Select saturation value based on overflow sign.
    #if defined(__SSE4_1__)
    __m128i sat = _mm_blendv_epi8(
        _mm_set1_epi32(INT32_MAX),
        _mm_set1_epi32(INT32_MIN),
        input_sign);
    return _mm_blendv_epi8(sum, sat, overflow);
    #else
    __m128i sat = _mm_or_si128(_mm_and_si128(input_sign, _mm_set1_epi32(INT32_MIN)),
                               _mm_andnot_si128(input_sign, _mm_set1_epi32(INT32_MAX)));
    return _mm_or_si128(_mm_and_si128(overflow, sat),
                        _mm_andnot_si128(overflow, sum));
    #endif
}
#define PS2_PADDSW(a, b) ps2_paddsw((__m128i)(a), (__m128i)(b))

// Packed Subtract with Signed Saturation Word (PSUBSW)
inline __m128i ps2_psubsw(__m128i a, __m128i b)
{
    __m128i diff = _mm_sub_epi32(a, b);
    // Check for over/underflow. Clamp to either INT32_MIN/INT32_MAX.
    __m128i overflow = _mm_and_si128(_mm_xor_si128(a, b),
                                     _mm_xor_si128(a, diff));
    // Extract input sign.
    overflow = _mm_srai_epi32(overflow, 31);
    __m128i input_sign = _mm_srai_epi32(a, 31);
    // Select saturation value based on overflow sign.
    #if defined(__SSE4_1__)
    __m128i sat = _mm_blendv_epi8(
        _mm_set1_epi32(INT32_MAX),
        _mm_set1_epi32(INT32_MIN),
        input_sign);
    return _mm_blendv_epi8(diff, sat, overflow);
    #else
    __m128i sat = _mm_or_si128(_mm_and_si128(input_sign, _mm_set1_epi32(INT32_MIN)),
                               _mm_andnot_si128(input_sign, _mm_set1_epi32(INT32_MAX)));
    return _mm_or_si128(_mm_and_si128(overflow, sat),
                        _mm_andnot_si128(overflow, diff));
    #endif

}
#define PS2_PSUBSW(a, b) ps2_psubsw((__m128i)(a), (__m128i)(b))

// Packed Compare Equal (PCEQ)
#define PS2_PCEQW(a, b) _mm_cmpeq_epi32((__m128i)(a), (__m128i)(b))
#define PS2_PCEQH(a, b) _mm_cmpeq_epi16((__m128i)(a), (__m128i)(b))
#define PS2_PCEQB(a, b) _mm_cmpeq_epi8((__m128i)(a), (__m128i)(b))

// Packed Absolute (PABS)
// 0x80000000 / 0x8000 saturate to 0x7FFFFFFF / 0x7FFF (p.158, p.159).
#define PS2_PABSW(a) _mm_min_epu32(_mm_abs_epi32((__m128i)(a)), _mm_set1_epi32(0x7FFFFFFF))
#define PS2_PABSH(a) _mm_min_epu16(_mm_abs_epi16((__m128i)(a)), _mm_set1_epi16(0x7FFF))
#define PS2_PABSB(a) _mm_abs_epi8((__m128i)(a))

// Packed Pack (PPAC) - Packs larger elements into smaller ones
inline __m128i ps2_paddu32(__m128i a, __m128i b)
{
    __m128i sum = _mm_add_epi32(a, b);
    __m128i overflow = _mm_cmpgt_epi32(_mm_xor_si128(a, _mm_set1_epi32(INT32_MIN)),
                                       _mm_xor_si128(sum, _mm_set1_epi32(INT32_MIN)));
    return _mm_or_si128(sum, overflow); // overflow lanes become all-1s
}
inline __m128i ps2_psubu32(__m128i a, __m128i b)
{
    __m128i diff = _mm_sub_epi32(a, b);
    // Underflow if a < b (unsigned). Clamp to 0.
    __m128i underflow = _mm_cmpgt_epi32(_mm_xor_si128(b, _mm_set1_epi32(INT32_MIN)),
                                        _mm_xor_si128(a, _mm_set1_epi32(INT32_MIN)));
    return _mm_andnot_si128(underflow, diff); // underflow lanes become 0
}

inline __m128i ps2_ppacw(__m128i rs, __m128i rt)
{
    // rs = [rs3 rs2 rs1 rs0], rt = [rt3 rt2 rt1 rt0]
    return _mm_castps_si128(_mm_shuffle_ps(_mm_castsi128_ps(rt), _mm_castsi128_ps(rs), _MM_SHUFFLE(2, 0, 2, 0)));
}
#define PS2_PPACW(a, b) ps2_ppacw((__m128i)(a), (__m128i)(b))

inline __m128i ps2_ppach(__m128i rs, __m128i rt)
{
    const __m128i mask = _mm_setr_epi8(
        0, 1, 4, 5, 8, 9, 12, 13,  // from rt: halfwords 0,2,4,6
        0, 1, 4, 5, 8, 9, 12, 13); // from rs: halfwords 0,2,4,6
    __m128i lo = _mm_shuffle_epi8(rt, mask);
    __m128i hi = _mm_shuffle_epi8(rs, mask);
    return _mm_unpacklo_epi64(lo, hi);
}
#define PS2_PPACH(a, b) ps2_ppach((__m128i)(a), (__m128i)(b))

inline __m128i ps2_ppacb(__m128i rs, __m128i rt)
{
    const __m128i mask = _mm_setr_epi8(
        0, 2, 4, 6, 8, 10, 12, 14,  // from rt: bytes 0,2,4,6,8,10,12,14
        0, 2, 4, 6, 8, 10, 12, 14); // from rs
    __m128i lo = _mm_shuffle_epi8(rt, mask);
    __m128i hi = _mm_shuffle_epi8(rs, mask);
    return _mm_unpacklo_epi64(lo, hi);
}
#define PS2_PPACB(a, b) ps2_ppacb((__m128i)(a), (__m128i)(b))

// Packed Interleave (PINT)
// PINTH p.214: low half of rt interleaved with the high half of rs.
#define PS2_PINTH(a, b) _mm_unpacklo_epi16((__m128i)(b), _mm_unpackhi_epi64((__m128i)(a), (__m128i)(a)))
// PINTEH p.213: each word is rs.h(2i) || rt.h(2i).
#define PS2_PINTEH(a, b) _mm_or_si128(_mm_and_si128((__m128i)(b), _mm_set1_epi32(0x0000FFFF)), _mm_slli_epi32((__m128i)(a), 16))

// Packed Multiply-Add (PMADD)
#define PS2_PMADDW(a, b) _mm_add_epi32(_mm_mullo_epi32(_mm_shuffle_epi32((__m128i)(a), _MM_SHUFFLE(1, 0, 3, 2)), _mm_shuffle_epi32((__m128i)(b), _MM_SHUFFLE(1, 0, 3, 2))), _mm_mullo_epi32(_mm_shuffle_epi32((__m128i)(a), _MM_SHUFFLE(3, 2, 1, 0)), _mm_shuffle_epi32((__m128i)(b), _MM_SHUFFLE(3, 2, 1, 0))))

// Packed Variable Shifts
// rt shifted by rs, words 0 and 2 only, sign-extended to 64 bits (p.262, p.265, p.268).
#define PS2_PSLLVW(a, b) ps2_psllvw((__m128i)(b), (__m128i)(a))
#define PS2_PSRLVW(a, b) ps2_psrlvw((__m128i)(b), (__m128i)(a))
#define PS2_PSRAVW(a, b) ps2_psravw((__m128i)(b), (__m128i)(a))

inline __m128i ps2_psllvw(__m128i rt, __m128i rs)
{
    const uint32_t w0 = (uint32_t)_mm_cvtsi128_si32(rt) << (_mm_cvtsi128_si32(rs) & 0x1F);
    const uint32_t w2 = (uint32_t)_mm_extract_epi32(rt, 2) << (_mm_extract_epi32(rs, 2) & 0x1F);
    return _mm_set_epi64x((int32_t)w2, (int32_t)w0);
}

inline __m128i ps2_psrlvw(__m128i rt, __m128i rs)
{
    const uint32_t w0 = (uint32_t)_mm_cvtsi128_si32(rt) >> (_mm_cvtsi128_si32(rs) & 0x1F);
    const uint32_t w2 = (uint32_t)_mm_extract_epi32(rt, 2) >> (_mm_extract_epi32(rs, 2) & 0x1F);
    return _mm_set_epi64x((int32_t)w2, (int32_t)w0);
}

inline __m128i ps2_psravw(__m128i rt, __m128i rs)
{
    const int32_t w0 = _mm_cvtsi128_si32(rt) >> (_mm_cvtsi128_si32(rs) & 0x1F);
    const int32_t w2 = _mm_extract_epi32(rt, 2) >> (_mm_extract_epi32(rs, 2) & 0x1F);
    return _mm_set_epi64x(w2, w0);
}

// PMFHL reads all 128 bits: hi/lo = bits 63..0, hi1/lo1 = bits 127..64 (pp.227-233).
#define PS2_HL128(hi, lo) _mm_set_epi64x((int64_t)(hi), (int64_t)(lo)) // [LO.w0, LO.w1, HI.w0, HI.w1]

// PMFHL.SLW: HI.w0 || LO.w0 saturated to a signed word, sign-extended to 64 bits.
inline int64_t ps2_pmfhl_slw(uint64_t hi, uint64_t lo)
{
    const int64_t value = (int64_t)Ps2HiLoToU64(hi, lo);
    if (value >= INT32_MAX)
        return INT32_MAX;
    if (value <= INT32_MIN)
        return INT32_MIN;
    return (int32_t)(uint32_t)lo;
}

#define PS2_PMFHL_LW(hi, lo, hi1, lo1) _mm_castps_si128(_mm_shuffle_ps(_mm_castsi128_ps(PS2_HL128(hi, lo)), _mm_castsi128_ps(PS2_HL128(hi1, lo1)), _MM_SHUFFLE(2, 0, 2, 0)))
#define PS2_PMFHL_UW(hi, lo, hi1, lo1) _mm_castps_si128(_mm_shuffle_ps(_mm_castsi128_ps(PS2_HL128(hi, lo)), _mm_castsi128_ps(PS2_HL128(hi1, lo1)), _MM_SHUFFLE(3, 1, 3, 1)))
#define PS2_PMFHL_SLW(hi, lo, hi1, lo1) _mm_set_epi64x(ps2_pmfhl_slw((hi1), (lo1)), ps2_pmfhl_slw((hi), (lo)))
#define PS2_PMFHL_LH(hi, lo, hi1, lo1) ps2_ppach(PS2_HL128(hi1, lo1), PS2_HL128(hi, lo))
#define PS2_PMFHL_SH(hi, lo, hi1, lo1) _mm_packs_epi32(PS2_HL128(hi, lo), PS2_HL128(hi1, lo1))

// FPU (COP1) operations
#define PS2_FCR31_I 0x00020000u
#define PS2_FCR31_D 0x00010000u
#define PS2_FCR31_SI 0x00000040u
#define PS2_FCR31_SD 0x00000020u

static inline bool Ps2FpuIsZero(float value)
{
    return (std::bit_cast<uint32_t>(value) & PS2_FLOAT_EXP_MASK) == 0u;
}

static inline float Ps2FpuMaxWithSign(uint32_t sign)
{
    return std::bit_cast<float>(sign | 0x7FFFFFFFu);
}

// ADD.S, SUB.S (p.343, p.377): the EE adder keeps one guard bit. The smaller operand loses its bits below that bit before the add (PCSX2 x86/iFPUd.cpp FPU_ADD_SUB).
static inline uint32_t Ps2FpuDropBitsBelowGuard(uint32_t bits, int shift)
{
    if (shift >= 25)
        return bits & PS2_FLOAT_SIGN_MASK;
    if (shift >= 2)
        return bits & (~0u << (shift - 1));
    return bits;
}

static inline float Ps2FpuAdd(float fs, float ft)
{
    uint32_t a = std::bit_cast<uint32_t>(Ps2FloatNormalize(fs));
    uint32_t b = std::bit_cast<uint32_t>(Ps2FloatNormalize(ft));
    const int difference = static_cast<int>((a >> 23) & 0xFFu) - static_cast<int>((b >> 23) & 0xFFu);
    if (difference > 0)
        b = Ps2FpuDropBitsBelowGuard(b, difference);
    else
        a = Ps2FpuDropBitsBelowGuard(a, -difference);
    return Ps2FloatNormalize(std::bit_cast<float>(a) + std::bit_cast<float>(b));
}

// DIV.S (p.357): x/0 sets D, 0/0 sets I; both give +/-0x7FFFFFFF.
static inline float Ps2FpuDivide(uint32_t &fcr31, float fs, float ft)
{
    fcr31 &= ~(PS2_FCR31_I | PS2_FCR31_D);
    if (Ps2FpuIsZero(ft))
    {
        fcr31 |= Ps2FpuIsZero(fs) ? (PS2_FCR31_I | PS2_FCR31_SI) : (PS2_FCR31_D | PS2_FCR31_SD);
        return Ps2FpuMaxWithSign((std::bit_cast<uint32_t>(fs) ^ std::bit_cast<uint32_t>(ft)) & PS2_FLOAT_SIGN_MASK);
    }
    return Ps2FloatNormalize(Ps2FloatNormalize(fs) / Ps2FloatNormalize(ft));
}

// RSQRT.S (p.375): ft = 0 gives +/-0x7FFFFFFF with the sign of fs.
static inline float Ps2FpuRSqrt(float fs, float ft)
{
    if (Ps2FpuIsZero(ft))
        return Ps2FpuMaxWithSign(std::bit_cast<uint32_t>(fs) & PS2_FLOAT_SIGN_MASK);
    return Ps2FloatNormalize(Ps2FloatNormalize(fs) / sqrtf(fabsf(Ps2FloatNormalize(ft))));
}

// MAX.S, MIN.S (p.363, p.365): compare the raw bits, return one operand unchanged (PCSX2 fp_max).
static inline bool Ps2FpuGreater(float fs, float ft)
{
    const int32_t a = std::bit_cast<int32_t>(fs);
    const int32_t b = std::bit_cast<int32_t>(ft);
    return (a < 0 && b < 0) ? (a < b) : (a > b);
}

static inline float Ps2FpuMax(float fs, float ft) { return Ps2FpuGreater(fs, ft) ? fs : ft; }
static inline float Ps2FpuMin(float fs, float ft) { return Ps2FpuGreater(ft, fs) ? fs : ft; }

static inline double Ps2FpuToWide(uint32_t v)
{
    const uint64_t sign = static_cast<uint64_t>(v & PS2_FLOAT_SIGN_MASK) << 32;
    const uint32_t e = (v >> 23) & 0xFFu;
    const uint64_t bits = e == 0u ? sign
                                  : sign | (static_cast<uint64_t>(e - 127u + 1023u) << 52) |
                                        (static_cast<uint64_t>(v & 0x7FFFFFu) << 29);
    double out;
    std::memcpy(&out, &bits, sizeof(out));
    return out;
}
static inline float Ps2FpuFromWide(double value, bool nearest)
{
    uint64_t d;
    std::memcpy(&d, &value, sizeof(d));
    const uint32_t sign = static_cast<uint32_t>(d >> 32) & PS2_FLOAT_SIGN_MASK;
    const int de = static_cast<int>((d >> 52) & 0x7FFu);
    uint32_t bits = sign;
    if (de != 0)
    {
        int exponent = de - 1023 + 127;
        uint64_t mant = (d & 0xFFFFFFFFFFFFFull) | 0x10000000000000ull; // 53 bits
        if (nearest)
            mant += 1ull << 28;
        uint32_t m24 = static_cast<uint32_t>(mant >> 29);
        if (m24 >> 24)
        {
            m24 >>= 1;
            ++exponent;
        }
        if (exponent >= 256)
            bits = sign | 0x7FFFFFFFu;
        else if (exponent > 0)
            bits = sign | (static_cast<uint32_t>(exponent) << 23) | (m24 & 0x7FFFFFu);
    }
    float out;
    std::memcpy(&out, &bits, sizeof(out));
    return out;
}
static inline float Ps2FpuAddWide(uint32_t a, uint32_t b)
{
    return Ps2FpuFromWide(Ps2FpuToWide(a) + Ps2FpuToWide(b), false);
}

static inline void Ps2FpuBooth(uint32_t a, uint32_t b, uint32_t bit, uint32_t &data, uint32_t &negate)
{
    const uint32_t test = (bit ? b >> (bit * 2 - 1) : b << 1) & 7u;
    a <<= (bit * 2);
    a += (test == 3u || test == 4u) ? a : 0u;
    const uint32_t neg = (test >= 4u && test <= 6u) ? ~0u : 0u;
    const uint32_t pos = 1u << (bit * 2);
    a ^= (neg & (0u - pos));
    a &= (test >= 1u && test <= 6u) ? ~0u : 0u;
    data = a;
    negate = neg & pos;
}
static inline uint64_t Ps2FpuMulMantissa(uint32_t a, uint32_t b)
{
    const uint64_t full = static_cast<uint64_t>(a) * static_cast<uint64_t>(b);
    uint32_t d[8], n[8];
    for (uint32_t i = 0; i < 8u; ++i)
        Ps2FpuBooth(a, b, i, d[i], n[i]);
    auto add3 = [](uint32_t x, uint32_t y, uint32_t z, uint32_t &lo, uint32_t &hi)
    {
        const uint32_t u = x ^ y;
        lo = u ^ z;
        hi = ((u & z) | (x & y)) << 1;
    };
    uint32_t t0l, t0h, t1l, t1h, t2l, t2h, t3l, t3h, t4l, t4h, t5l, t5h;
    add3(d[1], d[2], d[3], t0l, t0h);
    add3(d[4] & ~0x7FFu, d[5] & ~0xFFFu, d[6], t1l, t1h);
    t1h |= n[6] | (d[5] & 0x800u);
    d[7] |= (d[5] & 0x400u) + n[5];
    add3(d[0], t0l, t0h, t2l, t2h);
    add3(d[7], t1l, t1h, t3l, t3h);
    add3(t2h, t3l, t3h, t4l, t4h);
    add3(t2l, t4l, t4h, t5l, t5h);
    t5h += n[7];
    t5l &= ~0x7FFFu;
    t5h &= ~0x7FFFu;
    const uint32_t ps2lo = t5l + t5h;
    return full - ((ps2lo ^ static_cast<uint32_t>(full)) & 0x8000u);
}
// MUL.S from the multiplier model above: truncated product, exponent 255 is a normal number, overflow gives +/-0x7FFFFFFF and underflow +/-0.
static inline float Ps2FpuMulSoft(uint32_t a, uint32_t b)
{
    const uint32_t sign = (a ^ b) & PS2_FLOAT_SIGN_MASK;
    uint32_t bits = sign;
    if ((a & PS2_FLOAT_EXP_MASK) && (b & PS2_FLOAT_EXP_MASK))
    {
        int exponent = static_cast<int>((a >> 23) & 0xFFu) + static_cast<int>((b >> 23) & 0xFFu) - 127;
        uint32_t m = static_cast<uint32_t>(Ps2FpuMulMantissa((a & 0x7FFFFFu) | 0x800000u, (b & 0x7FFFFFu) | 0x800000u) >> 23);
        if (m > 0xFFFFFFu)
        {
            m >>= 1;
            ++exponent;
        }
        if (exponent > 255)
            bits = sign | 0x7FFFFFFFu;
        else if (exponent >= 1)
            bits = sign | (static_cast<uint32_t>(exponent) << 23) | (m & 0x7FFFFFu);
    }
    float out;
    std::memcpy(&out, &bits, sizeof(out));
    return out;
}

static inline void Ps2FpuCsa(uint32_t a, uint32_t b, uint32_t c, uint32_t &sum, uint32_t &carry)
{
    const uint32_t u = a ^ b;
    sum = u ^ c;
    carry = ((a & b) | (u & c)) << 1;
}
static inline int Ps2FpuQuotientSelect(uint32_t sum, uint32_t carry)
{
    // The binary point is between bits 24 and 25; bit 23 is or'd in.
    const uint32_t mask = (1u << 24) - 1u;
    const int32_t test = static_cast<int32_t>(((sum & ~mask) + carry) | (sum & mask));
    if (test >= (1 << 23))
        return 1;
    if (test < static_cast<int32_t>(~0u << 24))
        return -1;
    return 0;
}
// DIV.S (p.357): x/0 = +/-0x7FFFFFFF; 0/x = +/-0; overflow gives
// +/-0x7FFFFFFF and underflow +/-0.
static inline float Ps2FpuDivExact(float fs, float ft)
{
    uint32_t a, b;
    std::memcpy(&a, &fs, sizeof(a));
    std::memcpy(&b, &ft, sizeof(b));
    const uint32_t sign = (a ^ b) & PS2_FLOAT_SIGN_MASK;
    uint32_t bits = sign;
    if ((b & PS2_FLOAT_EXP_MASK) == 0u)
        bits = sign | 0x7FFFFFFFu;
    else if ((a & PS2_FLOAT_EXP_MASK) != 0u)
    {
        const uint32_t bm = ((b & 0x7FFFFFu) | 0x800000u) << 2;
        uint32_t sum = ((a & 0x7FFFFFu) | 0x800000u) << 2, carry = 0, quotient = 0;
        int quotientBit = 1;
        for (int i = 0; i < 25; ++i)
        {
            quotient = (quotient << 1) + static_cast<uint32_t>(quotientBit);
            const uint32_t add = quotientBit > 0 ? ~bm : quotientBit < 0 ? bm : 0u;
            carry += quotientBit > 0 ? 1u : 0u;
            uint32_t csaSum, csaCarry;
            Ps2FpuCsa(sum, carry, add, csaSum, csaCarry);
            quotientBit = quotientBit ? Ps2FpuQuotientSelect(csaSum, csaCarry) : Ps2FpuQuotientSelect(sum, carry);
            sum = csaSum << 1;
            carry = csaCarry << 1;
        }
        int exponent = static_cast<int>((a >> 23) & 0xFFu) - static_cast<int>((b >> 23) & 0xFFu) + 126;
        if (quotient >= (1u << 24))
        {
            ++exponent;
            quotient >>= 1;
        }
        if (exponent > 255)
            bits = sign | 0x7FFFFFFFu;
        else if (exponent >= 1)
            bits = sign | (static_cast<uint32_t>(exponent) << 23) | (quotient & 0x7FFFFFu);
    }
    float out;
    std::memcpy(&out, &bits, sizeof(out));
    return out;
}
// SQRT.S (p.376) of |ft|; sqrt(+/-0) = +0 (real PS2).
static inline float Ps2FpuSqrtExact(float ft)
{
    uint32_t a;
    std::memcpy(&a, &ft, sizeof(a));
    if ((a & PS2_FLOAT_EXP_MASK) == 0u)
        return 0.0f;
    uint32_t sum = ((a & 0x7FFFFFu) | 0x800000u) << 1, carry = 0, quotient = 0;
    if (!(a & 0x800000u)) // odd exponent after removing the bias
        sum <<= 1;
    int quotientBit = 1;
    for (int i = 0; i < 25; ++i)
    {
        // Adding n to the root adds n * (2 * root + n) to its square.
        const uint32_t adjust = quotient + (static_cast<uint32_t>(quotientBit) << (24 - i));
        quotient += static_cast<uint32_t>(quotientBit) << (25 - i);
        const uint32_t add = quotientBit > 0 ? ~adjust : quotientBit < 0 ? adjust : 0u;
        carry += quotientBit > 0 ? 1u : 0u;
        uint32_t csaSum, csaCarry;
        Ps2FpuCsa(sum, carry, add, csaSum, csaCarry);
        quotientBit = quotientBit ? Ps2FpuQuotientSelect(csaSum, csaCarry) : Ps2FpuQuotientSelect(sum, carry);
        sum = csaSum << 1;
        carry = csaCarry << 1;
    }
    const uint32_t exponent = (((a >> 23) & 0xFFu) + 127u) >> 1;
    const uint32_t bits = ((quotient >> 2) & 0x7FFFFFu) | (exponent << 23);
    float out;
    std::memcpy(&out, &bits, sizeof(out));
    return out;
}

#define FPU_SET_ACC(ctx, res) (ctx->f_acc = res)
#define FPU_ADD_S(a, b) Ps2FpuAdd((float)(a), (float)(b))
#define FPU_SUB_S(a, b) Ps2FpuAdd((float)(a), -(float)(b))
#define FPU_MUL_S(a, b) Ps2FloatNormalize(Ps2FloatNormalize((float)(a)) * Ps2FloatNormalize((float)(b)))
#define FPU_DIV_S(fcr31, a, b) Ps2FpuDivide(fcr31, (float)(a), (float)(b))
#define FPU_SQRT_S(a) sqrtf(fabsf(Ps2FloatNormalize((float)(a))))
#define FPU_RSQRT_S(a, b) Ps2FpuRSqrt((float)(a), (float)(b))
#define FPU_MAX_S(a, b) Ps2FpuMax((float)(a), (float)(b))
#define FPU_MIN_S(a, b) Ps2FpuMin((float)(a), (float)(b))
#define FPU_ABS_S(a) fabsf((float)(a))
#define FPU_MOV_S(a) ((float)(a))
#define FPU_NEG_S(a) (-(float)(a))
#define FPU_ROUND_L_S(a) ((int64_t)roundf((float)(a)))
#define FPU_TRUNC_L_S(a) ((int64_t)(float)(a))
#define FPU_CEIL_L_S(a) ((int64_t)ceilf((float)(a)))
#define FPU_FLOOR_L_S(a) ((int64_t)floorf((float)(a)))
#define FPU_ROUND_W_S(a) ((int32_t)nearbyintf((float)(a)))
#define FPU_TRUNC_W_S(a) ((int32_t)(float)(a))
#define FPU_CEIL_W_S(a) ((int32_t)ceilf((float)(a)))
#define FPU_FLOOR_W_S(a) ((int32_t)floorf((float)(a)))
// CVT.S.W (p.355) rounds toward zero. Keep only the top 24 bits first: then the result is
// also right when the compiler converts a constant at build time (it ignores MXCSR).
static inline float Ps2FpuCvtSW(int32_t value)
{
    uint32_t magnitude = value < 0 ? 0u - static_cast<uint32_t>(value) : static_cast<uint32_t>(value);
    const int width = std::bit_width(magnitude);
    if (width > 24)
        magnitude &= ~0u << (width - 24);
    const float result = static_cast<float>(magnitude);
    return value < 0 ? -result : result;
}
#define FPU_CVT_S_W(a) Ps2FpuCvtSW((int32_t)(a))
#define FPU_CVT_S_L(a) ((float)(int64_t)(a))
// CVT.W.S (p.356): a biased exponent above 0x9D clamps by the sign bit.
inline int32_t ps2CvtWord(float value)
{
    const uint32_t bits = std::bit_cast<uint32_t>(value);
    if (((bits >> 23) & 0xFFu) > 0x9Du)
        return (bits & PS2_FLOAT_SIGN_MASK) ? INT32_MIN : INT32_MAX;
    return static_cast<int32_t>(value);
}
#define FPU_CVT_W_S(a) ps2CvtWord((float)(a))
#define FPU_CVT_L_S(a) ((int64_t)(float)(a))
// C.cond.S (p.349): no NaN, so compare sign-magnitude integers; +0 == -0.
static inline int32_t Ps2FpuCompareKey(float value)
{
    const uint32_t bits = std::bit_cast<uint32_t>(value);
    if ((bits & PS2_FLOAT_EXP_MASK) == 0u)
        return 0;
    const int32_t magnitude = static_cast<int32_t>(bits & ~PS2_FLOAT_SIGN_MASK);
    return (bits & PS2_FLOAT_SIGN_MASK) ? -magnitude : magnitude;
}
#define FPU_C_F_S(a, b) (0)
#define FPU_C_UN_S(a, b) (0)
#define FPU_C_EQ_S(a, b) (Ps2FpuCompareKey((float)(a)) == Ps2FpuCompareKey((float)(b)))
#define FPU_C_UEQ_S(a, b) FPU_C_EQ_S(a, b)
#define FPU_C_OLT_S(a, b) (Ps2FpuCompareKey((float)(a)) < Ps2FpuCompareKey((float)(b)))
#define FPU_C_ULT_S(a, b) FPU_C_OLT_S(a, b)
#define FPU_C_OLE_S(a, b) (Ps2FpuCompareKey((float)(a)) <= Ps2FpuCompareKey((float)(b)))
#define FPU_C_ULE_S(a, b) FPU_C_OLE_S(a, b)
#define FPU_C_SF_S(a, b) (0)
#define FPU_C_NGLE_S(a, b) (0)
#define FPU_C_SEQ_S(a, b) FPU_C_EQ_S(a, b)
#define FPU_C_NGL_S(a, b) FPU_C_EQ_S(a, b)
#define FPU_C_LT_S(a, b) FPU_C_OLT_S(a, b)
#define FPU_C_NGE_S(a, b) FPU_C_OLT_S(a, b)
#define FPU_C_LE_S(a, b) FPU_C_OLE_S(a, b)
#define FPU_C_NGT_S(a, b) FPU_C_OLE_S(a, b)

// QFSRV: Quadword Funnel Shift Right Variable
// Concatenates rs || rt (256 bits) and right-shifts by SA bits, taking lower 128 bits.
inline __m128i ps2_qfsrv(__m128i rs, __m128i rt, uint32_t sa)
{
    if (sa == 0)
        return rt;
    if (sa >= 128)
    {
        if (sa >= 256)
            return _mm_setzero_si128();
        uint32_t shift = sa - 128;
        if (shift == 0)
            return rs;
        // Shift rs right by (sa-128) bits
        uint32_t byteShift = shift / 8;
        uint32_t bitShift = shift % 8;
        // Byte shift rs right
        alignas(16) uint8_t buf[16] = {};
        alignas(16) uint8_t src[16];
        _mm_store_si128((__m128i *)src, rs);
        for (uint32_t i = 0; i + byteShift < 16; i++)
            buf[i] = src[i + byteShift];
        __m128i result = _mm_load_si128((__m128i *)buf);
        if (bitShift > 0)
            result = _mm_or_si128(_mm_srli_epi64(result, bitShift),
                                  _mm_slli_epi64(_mm_bsrli_si128(result, 8), 64 - bitShift));
        return result;
    }
    // sa is 1..127: result = (rs || rt) >> sa, lower 128 bits
    uint32_t byteShift = sa / 8;
    uint32_t bitShift = sa % 8;
    alignas(16) uint8_t combined[32];
    _mm_store_si128((__m128i *)(combined), rt);      // low 128 bits
    _mm_store_si128((__m128i *)(combined + 16), rs); // high 128 bits
    // Shift right by byteShift bytes
    alignas(16) uint8_t shifted[16];
    for (uint32_t i = 0; i < 16; i++)
        shifted[i] = (i + byteShift < 32) ? combined[i + byteShift] : 0;
    __m128i result = _mm_load_si128((__m128i *)shifted);
    if (bitShift > 0)
    {
        uint8_t extra = (byteShift + 16 < 32) ? combined[byteShift + 16] : 0;
        __m128i hi_byte = _mm_insert_epi8(_mm_setzero_si128(), extra, 15);
        alignas(16) uint8_t src32[32];
        for (uint32_t i = 0; i < 32; i++)
            src32[i] = combined[i];
        uint64_t lo0, lo1, hi0, hi1;
        std::memcpy(&lo0, src32, 8);
        std::memcpy(&lo1, src32 + 8, 8);
        std::memcpy(&hi0, src32 + 16, 8);
        std::memcpy(&hi1, src32 + 24, 8);
        // 256-bit right shift by sa bits
        uint64_t r0, r1;
        if (sa < 64)
        {
            r0 = (lo0 >> sa) | (lo1 << (64 - sa));
            r1 = (lo1 >> sa) | (hi0 << (64 - sa));
        }
        else if (sa < 128)
        {
            uint32_t s = sa - 64;
            if (s == 0)
            {
                r0 = lo1;
                r1 = hi0;
            }
            else
            {
                r0 = (lo1 >> s) | (hi0 << (64 - s));
                r1 = (hi0 >> s) | (hi1 << (64 - s));
            }
        }
        else
        {
            r0 = 0;
            r1 = 0; // handled above
        }
        result = _mm_set_epi64x((long long)r1, (long long)r0);
    }
    return result;
}
#define PS2_QFSRV(rs, rt, sa) ps2_qfsrv((__m128i)(rs), (__m128i)(rt), (uint32_t)(sa))
#define PS2_PCPYLD(rs, rt) _mm_unpacklo_epi64(rt, rs)
// PEXEH p.200 [h2,h1,h0,h3 | h6,h5,h4,h7], PEXEW p.201 [w2,w1,w0,w3], PROT3W p.260 [w1,w2,w0,w3].
#define PS2_PEXEH(rs) _mm_shufflelo_epi16(_mm_shufflehi_epi16(rs, _MM_SHUFFLE(3, 0, 1, 2)), _MM_SHUFFLE(3, 0, 1, 2))
#define PS2_PEXEW(rs) _mm_shuffle_epi32(rs, _MM_SHUFFLE(3, 0, 1, 2))
#define PS2_PROT3W(rs) _mm_shuffle_epi32(rs, _MM_SHUFFLE(3, 0, 2, 1))

// Additional VU0 operations
#define PS2_VSQRT(x) sqrtf(x)
#define PS2_VRSQRT(x) (1.0f / sqrtf(x))

#define GPR_U32(ctx_ptr, reg_idx) ((reg_idx == 0) ? 0U : static_cast<uint32_t>(PS2_EXTRACT_EPI32_0(ctx_ptr->r[reg_idx])))
#define GPR_S32(ctx_ptr, reg_idx) ((reg_idx == 0) ? 0 : PS2_EXTRACT_EPI32_0(ctx_ptr->r[reg_idx]))
#define GPR_U64(ctx_ptr, reg_idx) ((reg_idx == 0) ? 0ULL : static_cast<uint64_t>(PS2_EXTRACT_EPI64_0(ctx_ptr->r[reg_idx])))
#define GPR_S64(ctx_ptr, reg_idx) ((reg_idx == 0) ? 0LL : PS2_EXTRACT_EPI64_0(ctx_ptr->r[reg_idx]))
#define GPR_VEC(ctx_ptr, reg_idx) ((reg_idx == 0) ? _mm_setzero_si128() : ctx_ptr->r[reg_idx])

static inline void Ps2SetGprLow64(R5900Context *ctx, int reg, __m128i new_low)
{
    if (reg != 0)
    {
        ctx->r[reg] = _mm_castpd_si128(_mm_move_sd(_mm_castsi128_pd(ctx->r[reg]), _mm_castsi128_pd(new_low)));
    }
}

#define SET_GPR_U32(ctx_ptr, reg_idx, val)                                \
    do                                                                    \
    {                                                                     \
        if ((reg_idx) != 0)                                               \
        {                                                                 \
            __m128i _newVal = _mm_cvtsi64_si128((int64_t)(int32_t)(val)); \
                                                                          \
            Ps2SetGprLow64(ctx_ptr, reg_idx, _newVal);                    \
        }                                                                 \
    } while (0)

#define SET_GPR_S32(ctx_ptr, reg_idx, val)                                \
    do                                                                    \
    {                                                                     \
        if ((reg_idx) != 0)                                               \
        {                                                                 \
            __m128i _newVal = _mm_cvtsi64_si128((int64_t)(int32_t)(val)); \
            Ps2SetGprLow64(ctx_ptr, reg_idx, _newVal);                    \
        }                                                                 \
    } while (0)

#define SET_GPR_U64(ctx_ptr, reg_idx, val)                       \
    do                                                           \
    {                                                            \
        if ((reg_idx) != 0)                                      \
        {                                                        \
            __m128i _newVal = _mm_cvtsi64_si128((int64_t)(val)); \
            Ps2SetGprLow64(ctx_ptr, reg_idx, _newVal);           \
        }                                                        \
    } while (0)

#define SET_GPR_S64(ctx_ptr, reg_idx, val) SET_GPR_U64(ctx_ptr, reg_idx, val)

#define SET_GPR_VEC(ctx_ptr, reg_idx, val) \
    do                                     \
    {                                      \
        if (reg_idx != 0)                  \
            ctx_ptr->r[reg_idx] = (val);   \
    } while (0)

#endif // PS2_RUNTIME_MACROS_H
