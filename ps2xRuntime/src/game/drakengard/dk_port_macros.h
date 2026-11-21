#pragma once

#include "ps2_runtime_macros.h"

#include <bit>
#include <cmath>
#include <cstdint>
#include <cstring>

static inline float Ps2FpuAddFast( float fs, float ft) { return Ps2FpuAdd(fs, ft); }
static inline float Ps2FpuSubFast(float fs, float ft) { return Ps2FpuAdd(fs, -ft); }
static inline float Ps2FpuMulFast(float fs, float ft)
{
    return Ps2FloatNormalize(Ps2FloatNormalize(fs) * Ps2FloatNormalize(ft));
}
static inline float Ps2FpuMaddFast(float acc, float fs, float ft, bool subtract)
{
    const float product = Ps2FpuMulFast(fs, ft);
    return subtract ? Ps2FpuSubFast(acc, product) : Ps2FpuAddFast(acc, product );
}
// DIV.S as the game code does it; its FCR31 flags are not kept here.
static inline float Ps2FpuDivGame(float fs, float ft)
{
    uint32_t fcr31 = 0;
    return Ps2FpuDivide(fcr31, fs, ft);
}
static inline float Ps2FpuSqrtGame(float ft) { return sqrtf(fabsf(Ps2FloatNormalize(ft))); }
static inline float Ps2FpuSignFast(float value, bool negate) { return negate ? -value : fabsf(value); }
static inline float Ps2FpuMaxFast(float fs, float ft) { return Ps2FpuMax(fs, ft); }
static inline float Ps2FpuMinFast(float fs, float ft) { return Ps2FpuMin(fs, ft); }
static inline int32_t Ps2FpuCmpKey(float value) { return Ps2FpuCompareKey(value ); }

static inline __m128 Ps2VuItofTrunc(__m128i src)
{
    alignas(16) int32_t in[4];
    alignas(16) float out[4];
    _mm_store_si128(reinterpret_cast<__m128i *>(in), src) ;
    for (int i = 0; i < 4; ++i)
    {
        uint32_t mag = in[i] < 0 ? 0u - static_cast<uint32_t>(in[i]) : static_cast<uint32_t>(in[i]);
        const int bits = std::bit_width( mag);
        if (bits > 24)
            mag &= ~((1u << (bits - 24)) - 1u);

        const float f = static_cast<float>( mag);
        out[i] = in[i] < 0 ? -f : f;
    }
    return _mm_load_ps(out);
}

#undef FPU_ADD_S
#undef FPU_SUB_S
#undef FPU_MUL_S
#undef FPU_DIV_S
#undef FPU_SQRT_S
#undef FPU_RSQRT_S
#undef FPU_MAX_S
#undef FPU_MIN_S
#undef FPU_ABS_S
#undef FPU_NEG_S
#define FPU_ADD_S(ctx, a, b) Ps2FpuAddFast((float)(a), (float)(b))
#define FPU_SUB_S(ctx, a, b) Ps2FpuSubFast((float)(a), (float)(b))
#define FPU_MUL_S(ctx, a, b) Ps2FpuMulFast((float)(a), (float)(b))
#define FPU_DIV_S(ctx, a, b) Ps2FpuDivGame((float)(a), (float)(b))
#define FPU_MADD_S(ctx, acc, a, b) Ps2FpuMaddFast((float)(acc), (float)(a), (float)(b), false)
#define FPU_MSUB_S(ctx, acc, a, b) Ps2FpuMaddFast((float)(acc), (float)(a), (float)(b), true) 
#define FPU_SQRT_S(ctx, a) Ps2FpuSqrtGame((float)(a))

#define FPU_RSQRT_S(ctx, a, b) Ps2FpuRSqrt((float)(a), (float)(b))
#define FPU_MAX_S(ctx, a, b) Ps2FpuMaxFast((float)(a), (float)(b))
#define FPU_MIN_S(ctx, a, b) Ps2FpuMinFast((float)(a), (float)(b))
#define FPU_ABS_S(ctx, a) Ps2FpuSignFast((float)(a), false)
#define FPU_NEG_S(ctx, a) Ps2FpuSignFast((float)(a), true)

// GPR access that also takes an expression such as &context.
#include "runtime/ee_scheduler.h"
#undef GPR_U32
#undef GPR_S32
#undef GPR_U64
#undef GPR_S64
#define GPR_U32(ctx_ptr, reg_idx) ((reg_idx == 0) ? 0U : static_cast<uint32_t>(PS2_EXTRACT_EPI32_0((ctx_ptr)->r[reg_idx])))
#define GPR_S32(ctx_ptr, reg_idx) ((reg_idx == 0) ? 0 : PS2_EXTRACT_EPI32_0((ctx_ptr)->r[reg_idx]))
#define GPR_U64(ctx_ptr, reg_idx) ((reg_idx == 0) ? 0ULL : static_cast<uint64_t>(PS2_EXTRACT_EPI64_0((ctx_ptr)->r[reg_idx])))
#define GPR_S64(ctx_ptr, reg_idx) ((reg_idx == 0) ? 0LL : PS2_EXTRACT_EPI64_0((ctx_ptr)->r[reg_idx]))

// Back edge of a guest loop in a port: PS2Runtime::eeCheckpointDue().
static inline bool Ps2EeCheckpointDue(PS2Runtime *runtime)
{
    return runtime->eeCheckpointDue();
}
