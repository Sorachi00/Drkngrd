#include "ps2recomp/code_generator.h"
#include "ps2recomp/codegen_helpers.h"
#include "ps2recomp/instructions.h"
#include "ps2recomp/types.h"
#include <fmt/format.h>
#include <sstream>
#include <cmath>

namespace ps2recomp
{
    std::string CodeGenerator::translateVU_VADD_Field(const Instruction &inst)
    {
        uint8_t vfd = inst.sa;
        uint8_t vfs = inst.rd;
        uint8_t vft = inst.rt;
        uint8_t dest_mask = inst.vectorInfo.vectorField;
        uint8_t field = inst.function & 0x3;
        std::string shuffle_pattern = fmt::format("_MM_SHUFFLE({},{},{},{})", field, field, field, field);
        return fmt::format("{{ __m128 res = PS2_VADD(ctx->vu0_vf[{}], _mm_shuffle_ps(ctx->vu0_vf[{}], ctx->vu0_vf[{}], {})); __m128i mask = _mm_set_epi32({}, {}, {}, {}); ctx->vu0_vf[{}] = _mm_blendv_ps(ctx->vu0_vf[{}], res, _mm_castsi128_ps(mask)); }}", vfs, vft, vft, shuffle_pattern, (dest_mask & 0x1) ? -1 : 0, (dest_mask & 0x2) ? -1 : 0, (dest_mask & 0x4) ? -1 : 0, (dest_mask & 0x8) ? -1 : 0, vfd, vfd);
    }

    std::string CodeGenerator::translateVU_VSUB_Field(const Instruction &inst)
    {
        uint8_t vfd = inst.sa;
        uint8_t vfs = inst.rd;
        uint8_t vft = inst.rt;
        uint8_t dest_mask = inst.vectorInfo.vectorField;
        uint8_t field = inst.function & 0x3;
        std::string shuffle_pattern = fmt::format("_MM_SHUFFLE({},{},{},{})", field, field, field, field);
        return fmt::format("{{ __m128 res = PS2_VSUB(ctx->vu0_vf[{}], _mm_shuffle_ps(ctx->vu0_vf[{}], ctx->vu0_vf[{}], {})); __m128i mask = _mm_set_epi32({}, {}, {}, {}); ctx->vu0_vf[{}] = _mm_blendv_ps(ctx->vu0_vf[{}], res, _mm_castsi128_ps(mask)); }}", vfs, vft, vft, shuffle_pattern, (dest_mask & 0x1) ? -1 : 0, (dest_mask & 0x2) ? -1 : 0, (dest_mask & 0x4) ? -1 : 0, (dest_mask & 0x8) ? -1 : 0, vfd, vfd);
    }

    std::string CodeGenerator::translateVU_VMUL_Field(const Instruction &inst)
    {
        uint8_t vfd = inst.sa;
        uint8_t vfs = inst.rd;
        uint8_t vft = inst.rt;
        uint8_t dest_mask = inst.vectorInfo.vectorField;
        uint8_t field = inst.function & 0x3;
        std::string shuffle_pattern = fmt::format("_MM_SHUFFLE({},{},{},{})", field, field, field, field);
        return fmt::format("{{ __m128 res = PS2_VMUL(ctx->vu0_vf[{}], _mm_shuffle_ps(ctx->vu0_vf[{}], ctx->vu0_vf[{}], {})); __m128i mask = _mm_set_epi32({}, {}, {}, {}); ctx->vu0_vf[{}] = _mm_blendv_ps(ctx->vu0_vf[{}], res, _mm_castsi128_ps(mask)); }}", vfs, vft, vft, shuffle_pattern, (dest_mask & 0x1) ? -1 : 0, (dest_mask & 0x2) ? -1 : 0, (dest_mask & 0x4) ? -1 : 0, (dest_mask & 0x8) ? -1 : 0, vfd, vfd);
    }

    std::string CodeGenerator::translateVU_VADD(const Instruction &inst)
    {
        uint8_t vfd = inst.sa;
        uint8_t vfs = inst.rd;
        uint8_t vft = inst.rt;
        uint8_t dest_mask = inst.vectorInfo.vectorField;
        return fmt::format("{{ __m128 res = PS2_VADD(ctx->vu0_vf[{}], ctx->vu0_vf[{}]); __m128i mask = _mm_set_epi32({}, {}, {}, {}); ctx->vu0_vf[{}] = PS2_VBLEND(ctx->vu0_vf[{}], res, _mm_castsi128_ps(mask)); }}", vfs, vft, (dest_mask & 0x1) ? -1 : 0, (dest_mask & 0x2) ? -1 : 0, (dest_mask & 0x4) ? -1 : 0, (dest_mask & 0x8) ? -1 : 0, vfd, vfd);
    }

    std::string CodeGenerator::translateVU_VSUB(const Instruction &inst)
    {
        uint8_t vfd = inst.sa;
        uint8_t vfs = inst.rd;
        uint8_t vft = inst.rt;
        uint8_t dest_mask = inst.vectorInfo.vectorField;
        return fmt::format("{{ __m128 res = PS2_VSUB(ctx->vu0_vf[{}], ctx->vu0_vf[{}]); __m128i mask = _mm_set_epi32({}, {}, {}, {}); ctx->vu0_vf[{}] = PS2_VBLEND(ctx->vu0_vf[{}], res, _mm_castsi128_ps(mask)); }}", vfs, vft, (dest_mask & 0x1) ? -1 : 0, (dest_mask & 0x2) ? -1 : 0, (dest_mask & 0x4) ? -1 : 0, (dest_mask & 0x8) ? -1 : 0, vfd, vfd);
    }

    std::string CodeGenerator::translateVU_VMUL(const Instruction &inst)
    {
        uint8_t vfd = inst.sa;
        uint8_t vfs = inst.rd;
        uint8_t vft = inst.rt;
        uint8_t dest_mask = inst.vectorInfo.vectorField;
        return fmt::format("{{ __m128 res = PS2_VMUL(ctx->vu0_vf[{}], ctx->vu0_vf[{}]); __m128i mask = _mm_set_epi32({}, {}, {}, {}); ctx->vu0_vf[{}] = PS2_VBLEND(ctx->vu0_vf[{}], res, _mm_castsi128_ps(mask)); }}", vfs, vft, (dest_mask & 0x1) ? -1 : 0, (dest_mask & 0x2) ? -1 : 0, (dest_mask & 0x4) ? -1 : 0, (dest_mask & 0x8) ? -1 : 0, vfd, vfd);
    }

    std::string CodeGenerator::translateVU_VDIV(const Instruction &inst)
    {
        uint8_t fsf = inst.vectorInfo.fsf;
        uint8_t ftf = inst.vectorInfo.ftf;
        uint8_t fs_reg = inst.rd;
        uint8_t ft_reg = inst.rt;

        // 0/0 sets I, x/0 sets D, plus sticky bits (VU p.129, p.40).
        return fmt::format("{{ float fs = _mm_cvtss_f32(_mm_shuffle_ps(ctx->vu0_vf[{}], ctx->vu0_vf[{}], _MM_SHUFFLE(0,0,0,{}))); float ft = _mm_cvtss_f32(_mm_shuffle_ps(ctx->vu0_vf[{}], ctx->vu0_vf[{}], _MM_SHUFFLE(0,0,0,{}))); ctx->vu0_q = Ps2VuDivide(fs, ft); "
                           "const uint16_t di = (ft == 0.0f) ? ((fs == 0.0f) ? 0x10u : 0x20u) : 0u; ctx->vu0_status = (uint16_t)((ctx->vu0_status & ~0x30u) | di | (di << 6)); }}", fs_reg, fs_reg, fsf, ft_reg, ft_reg, ftf);
    }

    std::string CodeGenerator::translateVU_VSQRT(const Instruction &inst)
    {
        uint8_t ftf = inst.vectorInfo.ftf;
        uint8_t ft_reg = inst.rt;
        // Negative input sets I; D is cleared (VU p.193, p.40).
        return fmt::format("{{ float ft = _mm_cvtss_f32(_mm_shuffle_ps(ctx->vu0_vf[{}], ctx->vu0_vf[{}], _MM_SHUFFLE(0,0,0,{}))); ctx->vu0_q = Ps2VuSqrt(ft); "
                           "const uint16_t di = (ft < 0.0f) ? 0x10u : 0u; ctx->vu0_status = (uint16_t)((ctx->vu0_status & ~0x30u) | di | (di << 6)); }}", ft_reg, ft_reg, ftf);
    }

    std::string CodeGenerator::translateVU_VRSQRT(const Instruction &inst)
    {
        uint8_t fsf = inst.vectorInfo.fsf;
        uint8_t ftf = inst.vectorInfo.ftf;
        uint8_t fs_reg = inst.rd;
        uint8_t ft_reg = inst.rt;
        // ft = 0 sets D (I for 0/0), negative ft sets I (VU p.188, p.40).
        return fmt::format("{{ float fs = _mm_cvtss_f32(_mm_shuffle_ps(ctx->vu0_vf[{}], ctx->vu0_vf[{}], _MM_SHUFFLE(0,0,0,{}))); float ft = _mm_cvtss_f32(_mm_shuffle_ps(ctx->vu0_vf[{}], ctx->vu0_vf[{}], _MM_SHUFFLE(0,0,0,{}))); ctx->vu0_q = Ps2VuRSqrt(fs, ft); "
                           "const uint16_t di = (ft == 0.0f) ? ((fs == 0.0f) ? 0x10u : 0x20u) : ((ft < 0.0f) ? 0x10u : 0u); ctx->vu0_status = (uint16_t)((ctx->vu0_status & ~0x30u) | di | (di << 6)); }}", fs_reg, fs_reg, fsf, ft_reg, ft_reg, ftf);
    }

    std::string CodeGenerator::translateVU_VMTIR(const Instruction &inst)
    {
        uint8_t fsf = inst.vectorInfo.fsf;
        return fmt::format("{{ uint32_t bits; float src = _mm_cvtss_f32(_mm_shuffle_ps(ctx->vu0_vf[{}], ctx->vu0_vf[{}], _MM_SHUFFLE(0,0,0,{}))); std::memcpy(&bits, &src, sizeof(bits)); ctx->vi[{}] = (uint16_t)(bits & 0xFFFF); }}", inst.rd, inst.rd, fsf, inst.rt);
    }

    std::string CodeGenerator::translateVU_VMFIR(const Instruction &inst)
    {
        uint8_t dest_mask = inst.vectorInfo.vectorField;
        return fmt::format("{{ uint32_t tmp = (uint32_t)(int32_t)(int16_t)ctx->vi[{}]; float val; std::memcpy(&val, &tmp, sizeof(val)); "
                           "__m128 res = _mm_set1_ps(val); "
                           "__m128i mask = _mm_set_epi32({}, {}, {}, {}); "
                           "ctx->vu0_vf[{}] = _mm_blendv_ps(ctx->vu0_vf[{}], res, _mm_castsi128_ps(mask)); }}",
                           inst.rd,
                           (dest_mask & 0x1) ? -1 : 0, (dest_mask & 0x2) ? -1 : 0,
                           (dest_mask & 0x4) ? -1 : 0, (dest_mask & 0x8) ? -1 : 0,
                           inst.rt, inst.rt);
    }

    static int vuIlwrFieldOffset(uint8_t destMask)
    {
        if (destMask & 0x8) return 0;   // x
        if (destMask & 0x4) return 4;   // y
        if (destMask & 0x2) return 8;   // z
        return 12;                       // w
    }

    std::string CodeGenerator::translateVU_VILWR(const Instruction &inst)
    {
        return fmt::format("{{ uint32_t addr = 0x11004000u + (((uint32_t)(ctx->vi[{}] & 0xFF)) << 4) + {}u; ctx->vi[{}] = static_cast<uint16_t>(READ32(addr) & 0xFFFFu); }}",
                           inst.rd, vuIlwrFieldOffset(inst.vectorInfo.vectorField), inst.rt); // VILWR.<f> vit, (vis)
    }

    std::string CodeGenerator::translateVU_VISWR(const Instruction &inst)
    {
        // Every dest field gets VI[it], upper 16 bits zero (VU p.174, p.263).
        const uint8_t dest = inst.vectorInfo.vectorField;
        std::string code = fmt::format("{{ uint32_t base = 0x11004000u + (((uint32_t)(ctx->vi[{}] & 0xFF)) << 4); uint32_t v = (uint32_t)(ctx->vi[{}] & 0xFFFFu);", inst.rd, inst.rt);
        if (dest & 0x8) code += " WRITE32(base + 0u, v);";
        if (dest & 0x4) code += " WRITE32(base + 4u, v);";
        if (dest & 0x2) code += " WRITE32(base + 8u, v);";
        if (dest & 0x1) code += " WRITE32(base + 12u, v);";
        return code + " }";
    }

    std::string CodeGenerator::translateVU_VIADD(const Instruction &inst)
    {
        return fmt::format("ctx->vi[{}] = ctx->vi[{}] + ctx->vi[{}];", inst.sa, inst.rd, inst.rt); // vid, vis, vit
    }

    std::string CodeGenerator::translateVU_VISUB(const Instruction &inst)
    {
        return fmt::format("ctx->vi[{}] = ctx->vi[{}] - ctx->vi[{}];", inst.sa, inst.rd, inst.rt); // vid, vis, vit
    }

    std::string CodeGenerator::translateVU_VIADDI(const Instruction &inst)
    {
        int32_t imm5 = (inst.sa & 0x10) ? static_cast<int32_t>(inst.sa | ~0x1F) : static_cast<int32_t>(inst.sa);
        return fmt::format("ctx->vi[{}] = ctx->vi[{}] + {};", inst.rt, inst.rd, imm5); // vit, vis, imm5
    }

    std::string CodeGenerator::translateVU_VIAND(const Instruction &inst)
    {
        return fmt::format("ctx->vi[{}] = ctx->vi[{}] & ctx->vi[{}];", inst.sa, inst.rd, inst.rt); // vid, vis, vit
    }

    std::string CodeGenerator::translateVU_VIOR(const Instruction &inst)
    {
        return fmt::format("ctx->vi[{}] = ctx->vi[{}] | ctx->vi[{}];", inst.sa, inst.rd, inst.rt); // vid, vis, vit
    }

    std::string CodeGenerator::translateVU_VCALLMS(const Instruction &inst)
    {
        // VCALLMS calls a VU0 microprogram at the specified immediate address.
        // VU0 micro memory is 4KB = 512 instructions (8 bytes each). Index is 0-511.
        uint16_t instr_index = static_cast<uint16_t>((inst.raw >> 6) & 0x1FF); // imm15[8:0]
        uint32_t target_byte_addr = static_cast<uint32_t>(instr_index) << 3;   // Convert instruction index to byte address

        return fmt::format(
            "{{ "
            "    ctx->vu0_tpc = 0x{:X}; " // Set target program counter
            "    runtime->executeVU0Microprogram(rdram, ctx, 0x{:X}); "
            "}}",
            target_byte_addr, target_byte_addr);
    }

    std::string CodeGenerator::translateVU_VCALLMSR(const Instruction &inst)
    {
        // Start address is CMSAR0 x 8 bytes (VU p.250, p.202).
        return fmt::format(
            "{{ "
            "    uint16_t instr_index = ctx->vu0_cmsar0 & 0x1FF; "
            "    uint32_t target_byte_addr = (uint32_t)instr_index << 3; "
            "    ctx->vu0_pc = target_byte_addr; "
            "    runtime->vu0StartMicroProgram(rdram, ctx, target_byte_addr); "
            "}}");
    }

    std::string CodeGenerator::translateVU_VRNEXT(const Instruction &inst)
    {
        // R = next(R), p(x) = x^23 + x^5 + 1; dest fields get 0x3F800000 | R (VU p.187, p.309, p.17).
        return fmt::format("{{ uint32_t r = (uint32_t)_mm_cvtsi128_si32(_mm_castps_si128(ctx->vu0_r)); "
                           "r = (((r << 1) ^ ((r >> 4) & 1u) ^ ((r >> 22) & 1u)) & 0x007FFFFFu) | 0x3F800000u; "
                           "ctx->vu0_r = _mm_castsi128_ps(_mm_set1_epi32((int32_t)r)); "
                           "ctx->vu0_vf[{}] = _mm_blendv_ps(ctx->vu0_vf[{}], ctx->vu0_r, {}); }}",
                           inst.rt, inst.rt, codegen::vuMaskExpr(inst.vectorInfo.vectorField));
    }

    std::string CodeGenerator::translateVU_VMADD_Field(const Instruction &inst)
    {
        uint8_t vfd = inst.sa;
        uint8_t vfs = inst.rd;
        uint8_t vft = inst.rt;
        uint8_t dest_mask = inst.vectorInfo.vectorField;
        uint8_t field = inst.function & 0x3; // Extract field from function code

        // Pre-construct the shuffle pattern to avoid format string issues
        std::string shuffle_pattern = fmt::format("_MM_SHUFFLE({},{},{},{})", field, field, field, field);

        return fmt::format("{{ __m128 mul_res = PS2_VMUL(ctx->vu0_vf[{}], _mm_shuffle_ps(ctx->vu0_vf[{}], ctx->vu0_vf[{}], {})); "
                           "__m128 res = PS2_VADD(ctx->vu0_acc, mul_res); "
                           "__m128i mask = _mm_set_epi32({}, {}, {}, {}); "
                           "ctx->vu0_vf[{}] = _mm_blendv_ps(ctx->vu0_vf[{}], res, _mm_castsi128_ps(mask)); }}",
                           vfs, vft, vft, shuffle_pattern,
                           (dest_mask & 0x1) ? -1 : 0, (dest_mask & 0x2) ? -1 : 0,
                           (dest_mask & 0x4) ? -1 : 0, (dest_mask & 0x8) ? -1 : 0,
                           vfd, vfd);
    }

    std::string CodeGenerator::translateVU_VMSUB_Field(const Instruction &inst)
    {
        uint8_t vfd = inst.sa;
        uint8_t vfs = inst.rd;
        uint8_t vft = inst.rt;
        uint8_t dest_mask = inst.vectorInfo.vectorField;
        uint8_t field = inst.function & 0x3; // Extract field from function code

        std::string shuffle_pattern = fmt::format("_MM_SHUFFLE({},{},{},{})", field, field, field, field);

        return fmt::format("{{ __m128 mul_res = PS2_VMUL(ctx->vu0_vf[{}], _mm_shuffle_ps(ctx->vu0_vf[{}], ctx->vu0_vf[{}], {})); "
                           "__m128 res = PS2_VSUB(ctx->vu0_acc, mul_res); "
                           "__m128i mask = _mm_set_epi32({}, {}, {}, {}); "
                           "ctx->vu0_vf[{}] = _mm_blendv_ps(ctx->vu0_vf[{}], res, _mm_castsi128_ps(mask)); }}",
                           vfs, vft, vft, shuffle_pattern,
                           (dest_mask & 0x1) ? -1 : 0, (dest_mask & 0x2) ? -1 : 0,
                           (dest_mask & 0x4) ? -1 : 0, (dest_mask & 0x8) ? -1 : 0,
                           vfd, vfd);
    }

    std::string CodeGenerator::translateVU_VMINI_Field(const Instruction &inst)
    {
        uint8_t vfd = inst.sa;
        uint8_t vfs = inst.rd;
        uint8_t vft = inst.rt;
        uint8_t dest_mask = inst.vectorInfo.vectorField;
        uint8_t field = inst.function & 0x3;

        std::string shuffle_pattern = fmt::format("_MM_SHUFFLE({},{},{},{})", field, field, field, field);

        return fmt::format("{{ __m128 res = Ps2VuMin(ctx->vu0_vf[{}], _mm_shuffle_ps(ctx->vu0_vf[{}], ctx->vu0_vf[{}], {})); "
                           "__m128i mask = _mm_set_epi32({}, {}, {}, {}); "
                           "ctx->vu0_vf[{}] = _mm_blendv_ps(ctx->vu0_vf[{}], res, _mm_castsi128_ps(mask)); }}",
                           vfs, vft, vft, shuffle_pattern,
                           (dest_mask & 0x1) ? -1 : 0, (dest_mask & 0x2) ? -1 : 0,
                           (dest_mask & 0x4) ? -1 : 0, (dest_mask & 0x8) ? -1 : 0,
                           vfd, vfd);
    }

    std::string CodeGenerator::translateVU_VMAX_Field(const Instruction &inst)
    {
        uint8_t vfd = inst.sa;
        uint8_t vfs = inst.rd;
        uint8_t vft = inst.rt;
        uint8_t dest_mask = inst.vectorInfo.vectorField;
        uint8_t field = inst.function & 0x3;

        std::string shuffle_pattern = fmt::format("_MM_SHUFFLE({},{},{},{})", field, field, field, field);

        return fmt::format("{{ __m128 res = Ps2VuMax(ctx->vu0_vf[{}], _mm_shuffle_ps(ctx->vu0_vf[{}], ctx->vu0_vf[{}], {})); "
                           "__m128i mask = _mm_set_epi32({}, {}, {}, {}); "
                           "ctx->vu0_vf[{}] = _mm_blendv_ps(ctx->vu0_vf[{}], res, _mm_castsi128_ps(mask)); }}",
                           vfs, vft, vft, shuffle_pattern,
                           (dest_mask & 0x1) ? -1 : 0, (dest_mask & 0x2) ? -1 : 0,
                           (dest_mask & 0x4) ? -1 : 0, (dest_mask & 0x8) ? -1 : 0,
                           vfd, vfd);
    }

    std::string CodeGenerator::translateVU_VMADD(const Instruction &inst)
    {
        uint8_t vfd = inst.sa;
        uint8_t vfs = inst.rd;
        uint8_t vft = inst.rt;
        uint8_t dest_mask = inst.vectorInfo.vectorField;
        return fmt::format("{{ __m128 mul_res = PS2_VMUL(ctx->vu0_vf[{}], ctx->vu0_vf[{}]); "
                           "__m128 res = PS2_VADD(ctx->vu0_acc, mul_res); "
                           "__m128i mask = _mm_set_epi32({}, {}, {}, {}); "
                           "ctx->vu0_vf[{}] = _mm_blendv_ps(ctx->vu0_vf[{}], res, _mm_castsi128_ps(mask)); }}",
                           vfs, vft,
                           (dest_mask & 0x1) ? -1 : 0, (dest_mask & 0x2) ? -1 : 0,
                           (dest_mask & 0x4) ? -1 : 0, (dest_mask & 0x8) ? -1 : 0,
                           vfd, vfd);
    }

    std::string CodeGenerator::translateVU_VMADDq(const Instruction &inst)
    {
        uint8_t vfd = inst.sa;
        uint8_t vfs = inst.rd;
        uint8_t dest_mask = inst.vectorInfo.vectorField;
        return fmt::format("{{ __m128 mul_res = PS2_VMUL(ctx->vu0_vf[{}], _mm_set1_ps(ctx->vu0_q)); "
                           "__m128 res = PS2_VADD(ctx->vu0_acc, mul_res); "
                           "__m128i mask = _mm_set_epi32({}, {}, {}, {}); "
                           "ctx->vu0_vf[{}] = _mm_blendv_ps(ctx->vu0_vf[{}], res, _mm_castsi128_ps(mask)); }}",
                           vfs,
                           (dest_mask & 0x1) ? -1 : 0, (dest_mask & 0x2) ? -1 : 0,
                           (dest_mask & 0x4) ? -1 : 0, (dest_mask & 0x8) ? -1 : 0,
                           vfd, vfd);
    }

    std::string CodeGenerator::translateVU_VMADDi(const Instruction &inst)
    {
        uint8_t vfd = inst.sa;
        uint8_t vfs = inst.rd;
        uint8_t dest_mask = inst.vectorInfo.vectorField;
        return fmt::format("{{ __m128 mul_res = PS2_VMUL(ctx->vu0_vf[{}], _mm_set1_ps(ctx->vu0_i)); "
                           "__m128 res = PS2_VADD(ctx->vu0_acc, mul_res); "
                           "__m128i mask = _mm_set_epi32({}, {}, {}, {}); "
                           "ctx->vu0_vf[{}] = _mm_blendv_ps(ctx->vu0_vf[{}], res, _mm_castsi128_ps(mask)); }}",
                           vfs,
                           (dest_mask & 0x1) ? -1 : 0, (dest_mask & 0x2) ? -1 : 0,
                           (dest_mask & 0x4) ? -1 : 0, (dest_mask & 0x8) ? -1 : 0,
                           vfd, vfd);
    }

    std::string CodeGenerator::translateVU_VMAX(const Instruction &inst)
    {
        uint8_t vfd = inst.sa;
        uint8_t vfs = inst.rd;
        uint8_t vft = inst.rt;
        uint8_t dest_mask = inst.vectorInfo.vectorField;
        return fmt::format("{{ __m128 res = Ps2VuMax(ctx->vu0_vf[{}], ctx->vu0_vf[{}]); "
                           "__m128i mask = _mm_set_epi32({}, {}, {}, {}); "
                           "ctx->vu0_vf[{}] = _mm_blendv_ps(ctx->vu0_vf[{}], res, _mm_castsi128_ps(mask)); }}",
                           vfs, vft,
                           (dest_mask & 0x1) ? -1 : 0, (dest_mask & 0x2) ? -1 : 0,
                           (dest_mask & 0x4) ? -1 : 0, (dest_mask & 0x8) ? -1 : 0,
                           vfd, vfd);
    }

    std::string CodeGenerator::translateVU_VMAXi(const Instruction &inst)
    {
        uint8_t vfd = inst.sa;
        uint8_t vfs = inst.rd;
        uint8_t dest_mask = inst.vectorInfo.vectorField;
        return fmt::format("{{ __m128 res = Ps2VuMax(ctx->vu0_vf[{}], _mm_set1_ps(ctx->vu0_i)); "
                           "__m128i mask = _mm_set_epi32({}, {}, {}, {}); "
                           "ctx->vu0_vf[{}] = _mm_blendv_ps(ctx->vu0_vf[{}], res, _mm_castsi128_ps(mask)); }}",
                           vfs,
                           (dest_mask & 0x1) ? -1 : 0, (dest_mask & 0x2) ? -1 : 0,
                           (dest_mask & 0x4) ? -1 : 0, (dest_mask & 0x8) ? -1 : 0,
                           vfd, vfd);
    }

    std::string CodeGenerator::translateVU_VMINIi(const Instruction &inst)
    {
        uint8_t vfd = inst.sa;
        uint8_t vfs = inst.rd;
        uint8_t dest_mask = inst.vectorInfo.vectorField;
        return fmt::format("{{ __m128 res = Ps2VuMin(ctx->vu0_vf[{}], _mm_set1_ps(ctx->vu0_i)); "
                           "__m128i mask = _mm_set_epi32({}, {}, {}, {}); "
                           "ctx->vu0_vf[{}] = _mm_blendv_ps(ctx->vu0_vf[{}], res, _mm_castsi128_ps(mask)); }}",
                           vfs,
                           (dest_mask & 0x1) ? -1 : 0, (dest_mask & 0x2) ? -1 : 0,
                           (dest_mask & 0x4) ? -1 : 0, (dest_mask & 0x8) ? -1 : 0,
                           vfd, vfd);
    }

    std::string CodeGenerator::translateVU_VMULi(const Instruction &inst)
    {
        uint8_t vfd = inst.sa;
        uint8_t vfs = inst.rd;
        uint8_t dest_mask = inst.vectorInfo.vectorField;
        return fmt::format("{{ __m128 res = PS2_VMUL(ctx->vu0_vf[{}], _mm_set1_ps(ctx->vu0_i)); "
                           "__m128i mask = _mm_set_epi32({}, {}, {}, {}); "
                           "ctx->vu0_vf[{}] = _mm_blendv_ps(ctx->vu0_vf[{}], res, _mm_castsi128_ps(mask)); }}",
                           vfs,
                           (dest_mask & 0x1) ? -1 : 0, (dest_mask & 0x2) ? -1 : 0,
                           (dest_mask & 0x4) ? -1 : 0, (dest_mask & 0x8) ? -1 : 0,
                           vfd, vfd);
    }

    std::string CodeGenerator::translateVU_VMULq(const Instruction &inst)
    {
        uint8_t vfd = inst.sa;
        uint8_t vfs = inst.rd;
        uint8_t dest_mask = inst.vectorInfo.vectorField;
        return fmt::format("{{ __m128 res = PS2_VMUL(ctx->vu0_vf[{}], _mm_set1_ps(ctx->vu0_q)); "
                           "__m128i mask = _mm_set_epi32({}, {}, {}, {}); "
                           "ctx->vu0_vf[{}] = _mm_blendv_ps(ctx->vu0_vf[{}], res, _mm_castsi128_ps(mask)); }}",
                           vfs,
                           (dest_mask & 0x1) ? -1 : 0, (dest_mask & 0x2) ? -1 : 0,
                           (dest_mask & 0x4) ? -1 : 0, (dest_mask & 0x8) ? -1 : 0,
                           vfd, vfd);
    }

    std::string CodeGenerator::translateVU_VOPMSUB(const Instruction &inst)
    {
        uint8_t vfd = inst.sa;
        uint8_t vfs = inst.rd;
        uint8_t vft = inst.rt;
        uint8_t dest_mask = inst.vectorInfo.vectorField;
        return fmt::format("{{ __m128 fs_yzx = _mm_shuffle_ps(ctx->vu0_vf[{}], ctx->vu0_vf[{}], _MM_SHUFFLE(3,0,2,1)); "
                           "__m128 ft_zxy = _mm_shuffle_ps(ctx->vu0_vf[{}], ctx->vu0_vf[{}], _MM_SHUFFLE(3,1,0,2)); "
                           "__m128 mul_res = PS2_VMUL(fs_yzx, ft_zxy); "
                           "__m128 res = PS2_VSUB(ctx->vu0_acc, mul_res); "
                           "__m128i mask = _mm_set_epi32({}, {}, {}, {}); "
                           "ctx->vu0_vf[{}] = _mm_blendv_ps(ctx->vu0_vf[{}], res, _mm_castsi128_ps(mask)); }}",
                           vfs, vfs, vft, vft,
                           (dest_mask & 0x1) ? -1 : 0, (dest_mask & 0x2) ? -1 : 0,
                           (dest_mask & 0x4) ? -1 : 0, (dest_mask & 0x8) ? -1 : 0,
                           vfd, vfd);
    }

    std::string CodeGenerator::translateVU_VADDq(const Instruction &inst)
    {
        uint8_t vfd = inst.sa;
        uint8_t vfs = inst.rd;
        uint8_t dest_mask = inst.vectorInfo.vectorField;
        return fmt::format("{{ __m128 res = PS2_VADD(ctx->vu0_vf[{}], _mm_set1_ps(ctx->vu0_q)); "
                           "__m128i mask = _mm_set_epi32({}, {}, {}, {}); "
                           "ctx->vu0_vf[{}] = _mm_blendv_ps(ctx->vu0_vf[{}], res, _mm_castsi128_ps(mask)); }}",
                           vfs,
                           (dest_mask & 0x1) ? -1 : 0, (dest_mask & 0x2) ? -1 : 0,
                           (dest_mask & 0x4) ? -1 : 0, (dest_mask & 0x8) ? -1 : 0,
                           vfd, vfd);
    }

    std::string CodeGenerator::translateVU_VADDi(const Instruction &inst)
    {
        uint8_t vfd = inst.sa;
        uint8_t vfs = inst.rd;
        uint8_t dest_mask = inst.vectorInfo.vectorField;
        return fmt::format("{{ __m128 res = PS2_VADD(ctx->vu0_vf[{}], _mm_set1_ps(ctx->vu0_i)); "
                           "__m128i mask = _mm_set_epi32({}, {}, {}, {}); "
                           "ctx->vu0_vf[{}] = _mm_blendv_ps(ctx->vu0_vf[{}], res, _mm_castsi128_ps(mask)); }}",
                           vfs,
                           (dest_mask & 0x1) ? -1 : 0, (dest_mask & 0x2) ? -1 : 0,
                           (dest_mask & 0x4) ? -1 : 0, (dest_mask & 0x8) ? -1 : 0,
                           vfd, vfd);
    }

    std::string CodeGenerator::translateVU_VMSUB(const Instruction &inst)
    {
        uint8_t vfd = inst.sa;
        uint8_t vfs = inst.rd;
        uint8_t vft = inst.rt;
        uint8_t dest_mask = inst.vectorInfo.vectorField;
        return fmt::format("{{ __m128 mul_res = PS2_VMUL(ctx->vu0_vf[{}], ctx->vu0_vf[{}]); "
                           "__m128 res = PS2_VSUB(ctx->vu0_acc, mul_res); "
                           "__m128i mask = _mm_set_epi32({}, {}, {}, {}); "
                           "ctx->vu0_vf[{}] = _mm_blendv_ps(ctx->vu0_vf[{}], res, _mm_castsi128_ps(mask)); }}",
                           vfs, vft,
                           (dest_mask & 0x1) ? -1 : 0, (dest_mask & 0x2) ? -1 : 0,
                           (dest_mask & 0x4) ? -1 : 0, (dest_mask & 0x8) ? -1 : 0,
                           vfd, vfd);
    }

    std::string CodeGenerator::translateVU_VMINI(const Instruction &inst)
    {
        uint8_t vfd = inst.sa;
        uint8_t vfs = inst.rd;
        uint8_t vft = inst.rt;
        uint8_t dest_mask = inst.vectorInfo.vectorField;
        return fmt::format("{{ __m128 res = Ps2VuMin(ctx->vu0_vf[{}], ctx->vu0_vf[{}]); "
                           "__m128i mask = _mm_set_epi32({}, {}, {}, {}); "
                           "ctx->vu0_vf[{}] = _mm_blendv_ps(ctx->vu0_vf[{}], res, _mm_castsi128_ps(mask)); }}",
                           vfs, vft,
                           (dest_mask & 0x1) ? -1 : 0, (dest_mask & 0x2) ? -1 : 0,
                           (dest_mask & 0x4) ? -1 : 0, (dest_mask & 0x8) ? -1 : 0,
                           vfd, vfd);
    }

    std::string CodeGenerator::translateVU_VSUBi(const Instruction &inst)
    {
        uint8_t vfd = inst.sa;
        uint8_t vfs = inst.rd;
        uint8_t dest_mask = inst.vectorInfo.vectorField;
        return fmt::format("{{ __m128 res = PS2_VSUB(ctx->vu0_vf[{}], _mm_set1_ps(ctx->vu0_i)); "
                           "__m128i mask = _mm_set_epi32({}, {}, {}, {}); "
                           "ctx->vu0_vf[{}] = _mm_blendv_ps(ctx->vu0_vf[{}], res, _mm_castsi128_ps(mask)); }}",
                           vfs,
                           (dest_mask & 0x1) ? -1 : 0, (dest_mask & 0x2) ? -1 : 0,
                           (dest_mask & 0x4) ? -1 : 0, (dest_mask & 0x8) ? -1 : 0,
                           vfd, vfd);
    }

    std::string CodeGenerator::translateVU_VSUBq(const Instruction &inst)
    {
        uint8_t vfd = inst.sa;
        uint8_t vfs = inst.rd;
        uint8_t dest_mask = inst.vectorInfo.vectorField;
        return fmt::format("{{ __m128 res = PS2_VSUB(ctx->vu0_vf[{}], _mm_set1_ps(ctx->vu0_q)); "
                           "__m128i mask = _mm_set_epi32({}, {}, {}, {}); "
                           "ctx->vu0_vf[{}] = _mm_blendv_ps(ctx->vu0_vf[{}], res, _mm_castsi128_ps(mask)); }}",
                           vfs,
                           (dest_mask & 0x1) ? -1 : 0, (dest_mask & 0x2) ? -1 : 0,
                           (dest_mask & 0x4) ? -1 : 0, (dest_mask & 0x8) ? -1 : 0,
                           vfd, vfd);
    }

    std::string CodeGenerator::translateVU_VMSUBq(const Instruction &inst)
    {
        uint8_t vfd = inst.sa;
        uint8_t vfs = inst.rd;
        uint8_t dest_mask = inst.vectorInfo.vectorField;
        return fmt::format("{{ __m128 mul_res = PS2_VMUL(ctx->vu0_vf[{}], _mm_set1_ps(ctx->vu0_q)); "
                           "__m128 res = PS2_VSUB(ctx->vu0_acc, mul_res); "
                           "__m128i mask = _mm_set_epi32({}, {}, {}, {}); "
                           "ctx->vu0_vf[{}] = _mm_blendv_ps(ctx->vu0_vf[{}], res, _mm_castsi128_ps(mask)); }}",
                           vfs,
                           (dest_mask & 0x1) ? -1 : 0, (dest_mask & 0x2) ? -1 : 0,
                           (dest_mask & 0x4) ? -1 : 0, (dest_mask & 0x8) ? -1 : 0,
                           vfd, vfd);
    }

    std::string CodeGenerator::translateVU_VMSUBi(const Instruction &inst)
    {
        uint8_t vfd = inst.sa;
        uint8_t vfs = inst.rd;
        uint8_t dest_mask = inst.vectorInfo.vectorField;
        return fmt::format("{{ __m128 mul_res = PS2_VMUL(ctx->vu0_vf[{}], _mm_set1_ps(ctx->vu0_i)); "
                           "__m128 res = PS2_VSUB(ctx->vu0_acc, mul_res); "
                           "__m128i mask = _mm_set_epi32({}, {}, {}, {}); "
                           "ctx->vu0_vf[{}] = _mm_blendv_ps(ctx->vu0_vf[{}], res, _mm_castsi128_ps(mask)); }}",
                           vfs,
                           (dest_mask & 0x1) ? -1 : 0, (dest_mask & 0x2) ? -1 : 0,
                           (dest_mask & 0x4) ? -1 : 0, (dest_mask & 0x8) ? -1 : 0,
                           vfd, vfd);
    }

    std::string CodeGenerator::translateVU_VADDA_Field(const Instruction &inst)
    {
        uint8_t vfs = inst.rd;
        uint8_t vft = inst.rt;
        uint8_t dest_mask = inst.vectorInfo.vectorField;
        uint8_t field = inst.function & 0x3;
        std::string shuffle_pattern = fmt::format("_MM_SHUFFLE({},{},{},{})", field, field, field, field);

        return fmt::format("{{ __m128 res = PS2_VADD(ctx->vu0_vf[{}], _mm_shuffle_ps(ctx->vu0_vf[{}], ctx->vu0_vf[{}], {})); "
                           "ctx->vu0_acc = _mm_blendv_ps(ctx->vu0_acc, res, {}); }}",
                           vfs, vft, vft, shuffle_pattern, codegen::vuMaskExpr(dest_mask));
    }

    std::string CodeGenerator::translateVU_VSUBA_Field(const Instruction &inst)
    {
        uint8_t vfs = inst.rd;
        uint8_t vft = inst.rt;
        uint8_t dest_mask = inst.vectorInfo.vectorField;
        uint8_t field = inst.function & 0x3;
        std::string shuffle_pattern = fmt::format("_MM_SHUFFLE({},{},{},{})", field, field, field, field);

        return fmt::format("{{ __m128 res = PS2_VSUB(ctx->vu0_vf[{}], _mm_shuffle_ps(ctx->vu0_vf[{}], ctx->vu0_vf[{}], {})); "
                           "ctx->vu0_acc = _mm_blendv_ps(ctx->vu0_acc, res, {}); }}",
                           vfs, vft, vft, shuffle_pattern, codegen::vuMaskExpr(dest_mask));
    }

    std::string CodeGenerator::translateVU_VMADDA_Field(const Instruction &inst)
    {
        uint8_t vfs = inst.rd;
        uint8_t vft = inst.rt;
        uint8_t dest_mask = inst.vectorInfo.vectorField;
        uint8_t field = inst.function & 0x3;
        std::string shuffle_pattern = fmt::format("_MM_SHUFFLE({},{},{},{})", field, field, field, field);

        return fmt::format("{{ __m128 mul_res = PS2_VMUL(ctx->vu0_vf[{}], _mm_shuffle_ps(ctx->vu0_vf[{}], ctx->vu0_vf[{}], {})); "
                           "__m128 res = PS2_VADD(ctx->vu0_acc, mul_res); "
                           "ctx->vu0_acc = _mm_blendv_ps(ctx->vu0_acc, res, {}); }}",
                           vfs, vft, vft, shuffle_pattern, codegen::vuMaskExpr(dest_mask));
    }

    std::string CodeGenerator::translateVU_VMSUBA_Field(const Instruction &inst)
    {
        uint8_t vfs = inst.rd;
        uint8_t vft = inst.rt;
        uint8_t dest_mask = inst.vectorInfo.vectorField;
        uint8_t field = inst.function & 0x3;
        std::string shuffle_pattern = fmt::format("_MM_SHUFFLE({},{},{},{})", field, field, field, field);

        return fmt::format("{{ __m128 mul_res = PS2_VMUL(ctx->vu0_vf[{}], _mm_shuffle_ps(ctx->vu0_vf[{}], ctx->vu0_vf[{}], {})); "
                           "__m128 res = PS2_VSUB(ctx->vu0_acc, mul_res); "
                           "ctx->vu0_acc = _mm_blendv_ps(ctx->vu0_acc, res, {}); }}",
                           vfs, vft, vft, shuffle_pattern, codegen::vuMaskExpr(dest_mask));
    }

    std::string CodeGenerator::translateVU_VMULA_Field(const Instruction &inst)
    {
        uint8_t vfs = inst.rd;
        uint8_t vft = inst.rt;
        uint8_t dest_mask = inst.vectorInfo.vectorField;
        uint8_t field = inst.function & 0x3;
        std::string shuffle_pattern = fmt::format("_MM_SHUFFLE({},{},{},{})", field, field, field, field);

        return fmt::format("{{ __m128 res = PS2_VMUL(ctx->vu0_vf[{}], _mm_shuffle_ps(ctx->vu0_vf[{}], ctx->vu0_vf[{}], {})); "
                           "ctx->vu0_acc = _mm_blendv_ps(ctx->vu0_acc, res, {}); }}",
                           vfs, vft, vft, shuffle_pattern, codegen::vuMaskExpr(dest_mask));
    }

    std::string CodeGenerator::translateVU_VADDA(const Instruction &inst)
    {
        uint8_t vfs = inst.rd;
        uint8_t vft = inst.rt;
        uint8_t dest_mask = inst.vectorInfo.vectorField;
        return fmt::format("{{ __m128 res = PS2_VADD(ctx->vu0_vf[{}], ctx->vu0_vf[{}]); ctx->vu0_acc = _mm_blendv_ps(ctx->vu0_acc, res, {}); }}",
                           vfs, vft, codegen::vuMaskExpr(dest_mask));
    }

    std::string CodeGenerator::translateVU_VADDAq(const Instruction &inst)
    {
        uint8_t vfs = inst.rd;
        uint8_t dest_mask = inst.vectorInfo.vectorField;
        return fmt::format("{{ __m128 res = PS2_VADD(ctx->vu0_vf[{}], _mm_set1_ps(ctx->vu0_q)); ctx->vu0_acc = _mm_blendv_ps(ctx->vu0_acc, res, {}); }}",
                           vfs, codegen::vuMaskExpr(dest_mask));
    }

    std::string CodeGenerator::translateVU_VADDAi(const Instruction &inst)
    {
        uint8_t vfs = inst.rd;
        uint8_t dest_mask = inst.vectorInfo.vectorField;
        return fmt::format("{{ __m128 res = PS2_VADD(ctx->vu0_vf[{}], _mm_set1_ps(ctx->vu0_i)); ctx->vu0_acc = _mm_blendv_ps(ctx->vu0_acc, res, {}); }}",
                           vfs, codegen::vuMaskExpr(dest_mask));
    }

    std::string CodeGenerator::translateVU_VSUBA(const Instruction &inst)
    {
        uint8_t vfs = inst.rd;
        uint8_t vft = inst.rt;
        uint8_t dest_mask = inst.vectorInfo.vectorField;
        return fmt::format("{{ __m128 res = PS2_VSUB(ctx->vu0_vf[{}], ctx->vu0_vf[{}]); ctx->vu0_acc = _mm_blendv_ps(ctx->vu0_acc, res, {}); }}",
                           vfs, vft, codegen::vuMaskExpr(dest_mask));
    }

    std::string CodeGenerator::translateVU_VSUBAq(const Instruction &inst)
    {
        uint8_t vfs = inst.rd;
        uint8_t dest_mask = inst.vectorInfo.vectorField;
        return fmt::format("{{ __m128 res = PS2_VSUB(ctx->vu0_vf[{}], _mm_set1_ps(ctx->vu0_q)); ctx->vu0_acc = _mm_blendv_ps(ctx->vu0_acc, res, {}); }}",
                           vfs, codegen::vuMaskExpr(dest_mask));
    }

    std::string CodeGenerator::translateVU_VSUBAi(const Instruction &inst)
    {
        uint8_t vfs = inst.rd;
        uint8_t dest_mask = inst.vectorInfo.vectorField;
        return fmt::format("{{ __m128 res = PS2_VSUB(ctx->vu0_vf[{}], _mm_set1_ps(ctx->vu0_i)); ctx->vu0_acc = _mm_blendv_ps(ctx->vu0_acc, res, {}); }}",
                           vfs, codegen::vuMaskExpr(dest_mask));
    }

    std::string CodeGenerator::translateVU_VMADDA(const Instruction &inst)
    {
        uint8_t vfs = inst.rd;
        uint8_t vft = inst.rt;
        uint8_t dest_mask = inst.vectorInfo.vectorField;
        return fmt::format("{{ __m128 mul_res = PS2_VMUL(ctx->vu0_vf[{}], ctx->vu0_vf[{}]); __m128 res = PS2_VADD(ctx->vu0_acc, mul_res); ctx->vu0_acc = _mm_blendv_ps(ctx->vu0_acc, res, {}); }}",
                           vfs, vft, codegen::vuMaskExpr(dest_mask));
    }

    std::string CodeGenerator::translateVU_VMADDAq(const Instruction &inst)
    {
        uint8_t vfs = inst.rd;
        uint8_t dest_mask = inst.vectorInfo.vectorField;
        return fmt::format("{{ __m128 mul_res = PS2_VMUL(ctx->vu0_vf[{}], _mm_set1_ps(ctx->vu0_q)); __m128 res = PS2_VADD(ctx->vu0_acc, mul_res); ctx->vu0_acc = _mm_blendv_ps(ctx->vu0_acc, res, {}); }}",
                           vfs, codegen::vuMaskExpr(dest_mask));
    }

    std::string CodeGenerator::translateVU_VMADDAi(const Instruction &inst)
    {
        uint8_t vfs = inst.rd;
        uint8_t dest_mask = inst.vectorInfo.vectorField;
        return fmt::format("{{ __m128 mul_res = PS2_VMUL(ctx->vu0_vf[{}], _mm_set1_ps(ctx->vu0_i)); __m128 res = PS2_VADD(ctx->vu0_acc, mul_res); ctx->vu0_acc = _mm_blendv_ps(ctx->vu0_acc, res, {}); }}",
                           vfs, codegen::vuMaskExpr(dest_mask));
    }

    std::string CodeGenerator::translateVU_VMSUBA(const Instruction &inst)
    {
        uint8_t vfs = inst.rd;
        uint8_t vft = inst.rt;
        uint8_t dest_mask = inst.vectorInfo.vectorField;
        return fmt::format("{{ __m128 mul_res = PS2_VMUL(ctx->vu0_vf[{}], ctx->vu0_vf[{}]); __m128 res = PS2_VSUB(ctx->vu0_acc, mul_res); ctx->vu0_acc = _mm_blendv_ps(ctx->vu0_acc, res, {}); }}",
                           vfs, vft, codegen::vuMaskExpr(dest_mask));
    }

    std::string CodeGenerator::translateVU_VMSUBAq(const Instruction &inst)
    {
        uint8_t vfs = inst.rd;
        uint8_t dest_mask = inst.vectorInfo.vectorField;
        return fmt::format("{{ __m128 mul_res = PS2_VMUL(ctx->vu0_vf[{}], _mm_set1_ps(ctx->vu0_q)); __m128 res = PS2_VSUB(ctx->vu0_acc, mul_res); ctx->vu0_acc = _mm_blendv_ps(ctx->vu0_acc, res, {}); }}",
                           vfs, codegen::vuMaskExpr(dest_mask));
    }

    std::string CodeGenerator::translateVU_VMSUBAi(const Instruction &inst)
    {
        uint8_t vfs = inst.rd;
        uint8_t dest_mask = inst.vectorInfo.vectorField;
        return fmt::format("{{ __m128 mul_res = PS2_VMUL(ctx->vu0_vf[{}], _mm_set1_ps(ctx->vu0_i)); __m128 res = PS2_VSUB(ctx->vu0_acc, mul_res); ctx->vu0_acc = _mm_blendv_ps(ctx->vu0_acc, res, {}); }}",
                           vfs, codegen::vuMaskExpr(dest_mask));
    }

    std::string CodeGenerator::translateVU_VMULA(const Instruction &inst)
    {
        uint8_t vfs = inst.rd;
        uint8_t vft = inst.rt;
        uint8_t dest_mask = inst.vectorInfo.vectorField;
        return fmt::format("{{ __m128 res = PS2_VMUL(ctx->vu0_vf[{}], ctx->vu0_vf[{}]); ctx->vu0_acc = _mm_blendv_ps(ctx->vu0_acc, res, {}); }}",
                           vfs, vft, codegen::vuMaskExpr(dest_mask));
    }

    std::string CodeGenerator::translateVU_VMULAq(const Instruction &inst)
    {
        uint8_t vfs = inst.rd;
        uint8_t dest_mask = inst.vectorInfo.vectorField;
        return fmt::format("{{ __m128 res = PS2_VMUL(ctx->vu0_vf[{}], _mm_set1_ps(ctx->vu0_q)); ctx->vu0_acc = _mm_blendv_ps(ctx->vu0_acc, res, {}); }}",
                           vfs, codegen::vuMaskExpr(dest_mask));
    }

    std::string CodeGenerator::translateVU_VMULAi(const Instruction &inst)
    {
        uint8_t vfs = inst.rd;
        uint8_t dest_mask = inst.vectorInfo.vectorField;
        return fmt::format("{{ __m128 res = PS2_VMUL(ctx->vu0_vf[{}], _mm_set1_ps(ctx->vu0_i)); ctx->vu0_acc = _mm_blendv_ps(ctx->vu0_acc, res, {}); }}",
                           vfs, codegen::vuMaskExpr(dest_mask));
    }

    std::string CodeGenerator::translateVU_VOPMULA(const Instruction &inst)
    {
        uint8_t vfs = inst.rd;
        uint8_t vft = inst.rt;
        uint8_t dest_mask = inst.vectorInfo.vectorField;
        return fmt::format("{{ __m128 fs_yzx = _mm_shuffle_ps(ctx->vu0_vf[{}], ctx->vu0_vf[{}], _MM_SHUFFLE(3,0,2,1)); "
                           "__m128 ft_zxy = _mm_shuffle_ps(ctx->vu0_vf[{}], ctx->vu0_vf[{}], _MM_SHUFFLE(3,1,0,2)); "
                           "__m128 res = PS2_VMUL(fs_yzx, ft_zxy); "
                           "ctx->vu0_acc = _mm_blendv_ps(ctx->vu0_acc, res, {}); }}",
                           vfs, vfs, vft, vft, codegen::vuMaskExpr(dest_mask));
    }

    std::string CodeGenerator::translateVU_VITOF(const Instruction &inst, int shift)
    {
        uint8_t vfs = inst.rd;
        uint8_t dest_mask = inst.vectorInfo.vectorField;
        float scale = (shift == 0) ? 1.0f : (1.0f / static_cast<float>(1 << shift));

        return fmt::format("{{ __m128i src = _mm_castps_si128(ctx->vu0_vf[{}]); "
                           "__m128 res = _mm_cvtepi32_ps(src); "
                           "res = _mm_mul_ps(res, _mm_set1_ps({})); "
                           "__m128i mask = _mm_set_epi32({}, {}, {}, {}); "
                           "ctx->vu0_vf[{}] = _mm_blendv_ps(ctx->vu0_vf[{}], res, _mm_castsi128_ps(mask)); }}",
                           vfs, codegen::formatFloatLiteral(scale),
                           (dest_mask & 0x1) ? -1 : 0, (dest_mask & 0x2) ? -1 : 0,
                           (dest_mask & 0x4) ? -1 : 0, (dest_mask & 0x8) ? -1 : 0,
                           inst.rt, inst.rt);
    }

    std::string CodeGenerator::translateVU_VFTOI(const Instruction &inst, int shift)
    {
        uint8_t vfs = inst.rd;
        uint8_t dest_mask = inst.vectorInfo.vectorField;
        float scale = (shift == 0) ? 1.0f : static_cast<float>(1 << shift);

        return fmt::format("{{ __m128 src = ctx->vu0_vf[{}]; "
                           "src = _mm_mul_ps(src, _mm_set1_ps({})); "
                           "__m128i res_i = _mm_cvttps_epi32(src); "
                           "res_i = _mm_xor_si128(res_i, _mm_and_si128(_mm_cmpeq_epi32(res_i, _mm_set1_epi32((int)0x80000000)), _mm_cmpgt_epi32(_mm_castps_si128(src), _mm_set1_epi32(-1)))); " // +overflow -> 0x7FFFFFFF (VU p.28)
                           "__m128 res = _mm_castsi128_ps(res_i); "
                           "__m128i mask = _mm_set_epi32({}, {}, {}, {}); "
                           "ctx->vu0_vf[{}] = _mm_blendv_ps(ctx->vu0_vf[{}], res, _mm_castsi128_ps(mask)); }}",
                           vfs, codegen::formatFloatLiteral(scale),
                           (dest_mask & 0x1) ? -1 : 0, (dest_mask & 0x2) ? -1 : 0,
                           (dest_mask & 0x4) ? -1 : 0, (dest_mask & 0x8) ? -1 : 0,
                           inst.rt, inst.rt);
    }

    std::string CodeGenerator::translateVU_VLQI(const Instruction &inst)
    {
        uint8_t vis = inst.rd;
        uint8_t dest_mask = inst.vectorInfo.vectorField;
        return fmt::format("{{ uint32_t addr = 0x11004000u + (((uint32_t)(ctx->vi[{}] & 0xFF)) << 4); "
                           "__m128 res = _mm_castsi128_ps(READ128(addr)); "
                           "__m128i mask = _mm_set_epi32({}, {}, {}, {}); "
                           "ctx->vu0_vf[{}] = _mm_blendv_ps(ctx->vu0_vf[{}], res, _mm_castsi128_ps(mask)); "
                           "ctx->vi[{}] = (uint16_t)(ctx->vi[{}] + 1); }}", // VI is 16 bits (VU p.179)
                           vis,
                           (dest_mask & 0x1) ? -1 : 0, (dest_mask & 0x2) ? -1 : 0,
                           (dest_mask & 0x4) ? -1 : 0, (dest_mask & 0x8) ? -1 : 0,
                           inst.rt, inst.rt,
                           vis, vis);
    }

    std::string CodeGenerator::translateVU_VSQI(const Instruction &inst)
    {
        // VF[fs] (rd) goes to VI[it] (rt); VI is 16 bits (VU p.192, p.313).
        uint8_t vit = inst.rt;
        uint8_t dest_mask = inst.vectorInfo.vectorField;
        return fmt::format("{{ "
                           "uint32_t addr = 0x11004000u + (((uint32_t)(ctx->vi[{}] & 0xFF)) << 4); "
                           "__m128i old_val = READ128(addr); "
                           "__m128 res = _mm_blendv_ps(_mm_castsi128_ps(old_val), ctx->vu0_vf[{}], _mm_castsi128_ps(_mm_set_epi32({}, {}, {}, {}))); "
                           "WRITE128(addr, _mm_castps_si128(res)); "
                           "ctx->vi[{}] = (uint16_t)(ctx->vi[{}] + 1); }}",
                           vit,
                           inst.rd,
                           (dest_mask & 0x1) ? -1 : 0, (dest_mask & 0x2) ? -1 : 0,
                           (dest_mask & 0x4) ? -1 : 0, (dest_mask & 0x8) ? -1 : 0,
                           vit, vit);
    }

    std::string CodeGenerator::translateVU_VLQD(const Instruction &inst)
    {
        uint8_t vis = inst.rd;
        uint8_t dest_mask = inst.vectorInfo.vectorField;
        // VI is 16 bits (VU p.178)
        return fmt::format("{{ ctx->vi[{}] = (uint16_t)(ctx->vi[{}] - 1); "
                           "uint32_t addr = 0x11004000u + (((uint32_t)(ctx->vi[{}] & 0xFF)) << 4); "
                           "__m128 res = _mm_castsi128_ps(READ128(addr)); "
                           "__m128i mask = _mm_set_epi32({}, {}, {}, {}); "
                           "ctx->vu0_vf[{}] = _mm_blendv_ps(ctx->vu0_vf[{}], res, _mm_castsi128_ps(mask)); }}",
                           vis, vis,
                           vis,
                           (dest_mask & 0x1) ? -1 : 0, (dest_mask & 0x2) ? -1 : 0,
                           (dest_mask & 0x4) ? -1 : 0, (dest_mask & 0x8) ? -1 : 0,
                           inst.rt, inst.rt);
    }

    std::string CodeGenerator::translateVU_VSQD(const Instruction &inst)
    {
        // VF[fs] (rd) goes to VI[it] (rt); VI is 16 bits (VU p.191, p.312).
        uint8_t vit = inst.rt;
        uint8_t dest_mask = inst.vectorInfo.vectorField;
        return fmt::format("{{ ctx->vi[{}] = (uint16_t)(ctx->vi[{}] - 1); "
                           "uint32_t addr = 0x11004000u + (((uint32_t)(ctx->vi[{}] & 0xFF)) << 4); "
                           "__m128i old_val = READ128(addr); "
                           "__m128 res = _mm_blendv_ps(_mm_castsi128_ps(old_val), ctx->vu0_vf[{}], _mm_castsi128_ps(_mm_set_epi32({}, {}, {}, {}))); "
                           "WRITE128(addr, _mm_castps_si128(res)); "
                           "}}",
                           vit, vit,
                           vit,
                           inst.rd,
                           (dest_mask & 0x1) ? -1 : 0, (dest_mask & 0x2) ? -1 : 0,
                           (dest_mask & 0x4) ? -1 : 0, (dest_mask & 0x8) ? -1 : 0);
    }

    std::string CodeGenerator::translateVU_VRGET(const Instruction &inst)
    {
        uint8_t dest_mask = inst.vectorInfo.vectorField;
        uint8_t ft_reg = inst.rt;
        return fmt::format("{{ __m128 res = ctx->vu0_r; __m128i mask = _mm_set_epi32({}, {}, {}, {}); ctx->vu0_vf[{}] = _mm_blendv_ps(ctx->vu0_vf[{}], res, _mm_castsi128_ps(mask)); }}", (dest_mask & 0x1) ? -1 : 0, (dest_mask & 0x2) ? -1 : 0, (dest_mask & 0x4) ? -1 : 0, (dest_mask & 0x8) ? -1 : 0, ft_reg, ft_reg);
    }

    std::string CodeGenerator::translateVU_VRINIT(const Instruction &inst)
    {
        uint8_t fs_reg = inst.rd;
        uint8_t fsf = inst.vectorInfo.fsf;
        // R = low 23 bits of VF[fs]fsf (VU p.186, p.308).
        return fmt::format("{{ uint32_t bits = (uint32_t)Ps2ExtractEpi32(_mm_castps_si128(ctx->vu0_vf[{}]), {}); "
                           "ctx->vu0_r = _mm_castsi128_ps(_mm_set1_epi32((int32_t)(0x3F800000u | (bits & 0x007FFFFFu)))); }}",
                           fs_reg, fsf);
    }

    std::string CodeGenerator::translateVU_VRXOR(const Instruction &inst)
    {
        uint8_t fs_reg = inst.rd;
        uint8_t fsf = inst.vectorInfo.fsf;
        // R = R xor low 23 bits of VF[fs]fsf (VU p.189, p.311).
        return fmt::format("{{ uint32_t bits = (uint32_t)Ps2ExtractEpi32(_mm_castps_si128(ctx->vu0_vf[{}]), {}); "
                           "uint32_t r = (uint32_t)_mm_cvtsi128_si32(_mm_castps_si128(ctx->vu0_r)); "
                           "ctx->vu0_r = _mm_castsi128_ps(_mm_set1_epi32((int32_t)(0x3F800000u | ((r ^ bits) & 0x007FFFFFu)))); }}",
                           fs_reg, fsf);
    }

}
