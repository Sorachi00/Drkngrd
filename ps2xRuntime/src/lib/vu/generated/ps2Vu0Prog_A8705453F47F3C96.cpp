#include "../ps2_vu1_recomp.h"
#include "../ps2_vu1_detail.h"

#include <cmath>
#include <cstring>
#include <limits>

#if defined(_MSC_VER) && !defined(__clang__)
#pragma fp_contract(off)
#else
#pragma STDC FP_CONTRACT OFF
#endif

namespace
{
    alignas(16) thread_local uint8_t s_kickBuf[65536];
}

int ps2Vu0Prog_A8705453F47F3C96(Vu1ProgArgs &a)
{
    switch (a.startPC)
    {
    case 0x0u:
    case 0x8u:
    case 0x10u:
    case 0x18u:
    case 0x20u:
    case 0x28u:
    case 0x30u:
    case 0x38u:
    case 0x40u:
    case 0x48u:
    case 0x50u:
    case 0x58u:
    case 0x60u:
    case 0x68u:
    case 0x70u:
    case 0x78u:
    case 0x80u:
    case 0x88u:
    case 0x90u:
    case 0x98u:
    case 0xA0u:
    case 0xA8u:
    case 0xB0u:
    case 0xB8u:
    case 0xC0u:
    case 0xC8u:
    case 0xD0u:
    case 0xD8u:
    case 0xE0u:
    case 0xE8u:
    case 0xF0u:
    case 0xF8u:
    case 0x100u:
    case 0x108u:
    case 0x110u:
    case 0x118u:
    case 0x120u:
    case 0x128u:
    case 0x130u:
    case 0x138u:
    case 0x140u:
    case 0x148u:
    case 0x150u:
    case 0x158u:
    case 0x160u:
    case 0x168u:
    case 0x170u:
    case 0x178u:
    case 0x180u:
    case 0x188u:
    case 0x190u:
    case 0x198u:
    case 0x1A0u:
    case 0x1A8u:
    case 0x1B0u:
    case 0x1B8u:
    case 0x1C0u:
    case 0x1C8u:
    case 0x1D0u:
    case 0x1D8u:
    case 0x1E0u:
    case 0x1E8u:
    case 0x1F0u:
    case 0x1F8u:
    case 0x200u:
    case 0x208u:
    case 0x210u:
    case 0x218u:
    case 0x220u:
    case 0x228u:
    case 0x230u:
    case 0x238u:
    case 0x240u:
    case 0x248u:
    case 0x250u:
    case 0x258u:
    case 0x260u:
    case 0x268u:
    case 0x270u:
    case 0x278u:
    case 0x280u:
    case 0x288u:
    case 0x290u:
    case 0x298u:
    case 0x2A0u:
    case 0x2A8u:
    case 0x2B0u:
    case 0x2B8u:
    case 0x2C0u:
    case 0x2C8u:
    case 0x2D0u:
    case 0x2D8u:
    case 0x2E0u:
    case 0x2E8u:
    case 0x2F0u:
    case 0x2F8u:
    case 0x300u:
        break;
    default:
        return kVu1ProgNoEntry;
    }

    VU1State &st = *a.state;
    uint8_t *vm = a.vuData;
    vu1gen::RunCtx cx;
    cx.init(st, true, true);
    cx.vm = vm; cx.undo = a.undo; cx.kickBuffer = s_kickBuf; cx.gs = a.gs; cx.memory = a.memory;
    st.pc = a.startPC & 0xFFFu;
    st.ebit = false;
    st.haltAfterDelaySlot = false;
    st.stoppedByD = false;
    st.stoppedByT = false;
    st.top = a.top;
    st.itop = a.itop;
    st.branchPending = false;
    st.branchTarget = 0;
    st.branchDelay = 0;
    st.vf[0][0] = 0.0f; st.vf[0][1] = 0.0f; st.vf[0][2] = 0.0f; st.vf[0][3] = 1.0f;
    st.vi[0] = 0;
    uint64_t c = 0;
    int32_t bvReg = -1;
    int32_t bvOld = 0;
    uint32_t jt = 0;
    (void)jt;

    switch (a.startPC)
    {
    case 0x0u: goto L0000;
    case 0x8u: goto L0008;
    case 0x10u: goto L0010;
    case 0x18u: goto L0018;
    case 0x20u: goto L0020;
    case 0x28u: goto L0028;
    case 0x30u: goto L0030;
    case 0x38u: goto L0038;
    case 0x40u: goto L0040;
    case 0x48u: goto L0048;
    case 0x50u: goto L0050;
    case 0x58u: goto L0058;
    case 0x60u: goto L0060;
    case 0x68u: goto L0068;
    case 0x70u: goto L0070;
    case 0x78u: goto L0078;
    case 0x80u: goto L0080;
    case 0x88u: goto L0088;
    case 0x90u: goto L0090;
    case 0x98u: goto L0098;
    case 0xA0u: goto L00A0;
    case 0xA8u: goto L00A8;
    case 0xB0u: goto L00B0;
    case 0xB8u: goto L00B8;
    case 0xC0u: goto L00C0;
    case 0xC8u: goto L00C8;
    case 0xD0u: goto L00D0;
    case 0xD8u: goto L00D8;
    case 0xE0u: goto L00E0;
    case 0xE8u: goto L00E8;
    case 0xF0u: goto L00F0;
    case 0xF8u: goto L00F8;
    case 0x100u: goto L0100;
    case 0x108u: goto L0108;
    case 0x110u: goto L0110;
    case 0x118u: goto L0118;
    case 0x120u: goto L0120;
    case 0x128u: goto L0128;
    case 0x130u: goto L0130;
    case 0x138u: goto L0138;
    case 0x140u: goto L0140;
    case 0x148u: goto L0148;
    case 0x150u: goto L0150;
    case 0x158u: goto L0158;
    case 0x160u: goto L0160;
    case 0x168u: goto L0168;
    case 0x170u: goto L0170;
    case 0x178u: goto L0178;
    case 0x180u: goto L0180;
    case 0x188u: goto L0188;
    case 0x190u: goto L0190;
    case 0x198u: goto L0198;
    case 0x1A0u: goto L01A0;
    case 0x1A8u: goto L01A8;
    case 0x1B0u: goto L01B0;
    case 0x1B8u: goto L01B8;
    case 0x1C0u: goto L01C0;
    case 0x1C8u: goto L01C8;
    case 0x1D0u: goto L01D0;
    case 0x1D8u: goto L01D8;
    case 0x1E0u: goto L01E0;
    case 0x1E8u: goto L01E8;
    case 0x1F0u: goto L01F0;
    case 0x1F8u: goto L01F8;
    case 0x200u: goto L0200;
    case 0x208u: goto L0208;
    case 0x210u: goto L0210;
    case 0x218u: goto L0218;
    case 0x220u: goto L0220;
    case 0x228u: goto L0228;
    case 0x230u: goto L0230;
    case 0x238u: goto L0238;
    case 0x240u: goto L0240;
    case 0x248u: goto L0248;
    case 0x250u: goto L0250;
    case 0x258u: goto L0258;
    case 0x260u: goto L0260;
    case 0x268u: goto L0268;
    case 0x270u: goto L0270;
    case 0x278u: goto L0278;
    case 0x280u: goto L0280;
    case 0x288u: goto L0288;
    case 0x290u: goto L0290;
    case 0x298u: goto L0298;
    case 0x2A0u: goto L02A0;
    case 0x2A8u: goto L02A8;
    case 0x2B0u: goto L02B0;
    case 0x2B8u: goto L02B8;
    case 0x2C0u: goto L02C0;
    case 0x2C8u: goto L02C8;
    case 0x2D0u: goto L02D0;
    case 0x2D8u: goto L02D8;
    case 0x2E0u: goto L02E0;
    case 0x2E8u: goto L02E8;
    case 0x2F0u: goto L02F0;
    case 0x2F8u: goto L02F8;
    case 0x300u: goto L0300;
    default: return kVu1ProgNoEntry;
    }

    L0000:;
    { // pair 0 pc=0x0 up=0x000002FF lo=0x1002000E
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[0] + 14); bvOld = st.vi[2]; bvReg = 2; st.vi[2] = nv; }
      }
      c += 1u;
    }
    L0008:;
    { // pair 1 pc=0x8 up=0x000002FF lo=0x10030036
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[0] + 54); bvOld = st.vi[3]; bvReg = 3; st.vi[3] = nv; }
      }
      c += 1u;
    }
    L0010:;
    { // pair 2 pc=0x10 up=0x000002FF lo=0x1004005E
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[0] + 94); bvOld = st.vi[4]; bvReg = 4; st.vi[4] = nv; }
      }
      c += 1u;
    }
    L0018:;
    { // pair 3 pc=0x18 up=0x000002FF lo=0x10060086
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[0] + 134); bvOld = st.vi[6]; bvReg = 6; st.vi[6] = nv; }
      }
      c += 1u;
    }
    L0020:;
    { // pair 4 pc=0x20 up=0x000002FF lo=0x11E707FF
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[0] + 32767); bvOld = st.vi[7]; bvReg = 7; st.vi[7] = nv; }
      }
      c += 1u;
    }
    L0028:;
    { // pair 5 pc=0x28 up=0x000002FF lo=0x11873801
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[7] + 24577); bvOld = st.vi[7]; bvReg = 7; st.vi[7] = nv; }
      }
      c += 1u;
    }
    L0030:;
    { // pair 6 pc=0x30 up=0x01E00240 lo=0x81FE137C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = _mm_setr_ps(0.0f, 0.0f, 0.0f, 1.0f);
        const __m128 bv = _mm_set1_ps(0.0f);
        const __m128 rv = _mm_add_ps(vsv, bv);
        uint32_t mac = 0u, stf = 0u, stk = 0u;
        __m128 rvn = rv;
        { uint32_t sgn; uint32_t plain = vu1gen::classify4(rv, sgn);
          if ((plain & 0xFu) == 0xFu) {
            mac = vu1gen::kMacSign.word[sgn & 0xFu];
            stf = (sgn & 0xFu) != 0u ? 0x2u : 0u;
          } else {
            float rr[4]; _mm_storeu_ps(rr, rv);
            { uint8_t lf;
              if (plain & 1u) lf = ((sgn >> 0) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[0], (double)_mm_cvtss_f32(vsv) + (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[0] = vu1gen::normResult(rr[0], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[0][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 2u) lf = ((sgn >> 1) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[1], (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(1, 1, 1, 1))) + (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[1] = vu1gen::normResult(rr[1], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[1][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 4u) lf = ((sgn >> 2) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[2], (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(2, 2, 2, 2))) + (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[2] = vu1gen::normResult(rr[2], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[2][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 8u) lf = ((sgn >> 3) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[3], (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(3, 3, 3, 3))) + (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[3] = vu1gen::normResult(rr[3], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[3][lf & 0xFu]; stf |= lf & 0xFu; }
            rvn = _mm_loadu_ps(rr);
          } }
        cx.pushFmac(c, mac, stf, stk);
        urv = rvn;
      }
      {
        { const uint32_t addr = ((uint32_t)(uint16_t)st.vi[2] * 16u) & 0xFFFu;
          std::memcpy(&st.vf[30][0], vm + addr + 0u, 16);
        }
        { const int32_t nv = (int32_t)(int16_t)(st.vi[2] + 1); bvOld = st.vi[2]; bvReg = 2; st.vi[2] = nv; }
      }
      vu1gen::storeLanes(st.vf[9], urv, 0xFu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[9] = rt;
        _mm_store_si128((__m128i *)cx.vfR[9], _mm_set1_epi32((int)rt));
      }
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[30] = rt;
        _mm_store_si128((__m128i *)cx.vfR[30], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L0038:;
    { // pair 7 pc=0x38 up=0x000002FF lo=0x81EA237C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(uint16_t)st.vi[4] * 16u) & 0xFFFu;
          std::memcpy(&st.vf[10][0], vm + addr + 0u, 16);
        }
        { const int32_t nv = (int32_t)(int16_t)(st.vi[4] + 1); bvOld = st.vi[4]; bvReg = 4; st.vi[4] = nv; }
      }
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[10] = rt;
        _mm_store_si128((__m128i *)cx.vfR[10], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L0040:;
    { // pair 8 pc=0x40 up=0x000002FF lo=0x81FF1B7C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(uint16_t)st.vi[3] * 16u) & 0xFFFu;
          std::memcpy(&st.vf[31][0], vm + addr + 0u, 16);
        }
        { const int32_t nv = (int32_t)(int16_t)(st.vi[3] + 1); bvOld = st.vi[3]; bvReg = 3; st.vi[3] = nv; }
      }
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[31] = rt;
        _mm_store_si128((__m128i *)cx.vfR[31], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L0048:;
    { // pair 9 pc=0x48 up=0x000002FF lo=0x12010801
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[1] - 1); bvOld = st.vi[1]; bvReg = 1; st.vi[1] = nv; }
      }
      c += 1u;
    }
    L0050:;
    { // pair 10 pc=0x50 up=0x01DEF13C lo=0x8000033C
      c = vu1gen::vmax(c, cx.vfR[30][0]);
      c = vu1gen::vmax(c, cx.vfR[30][1]);
      c = vu1gen::vmax(c, cx.vfR[30][2]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      float ur0 = 0.0f;
      float ur1 = 0.0f;
      float ur2 = 0.0f;
      {
        { int32_t iv; std::memcpy(&iv, &st.vf[30][0], 4);
          ur0 = static_cast<float>(iv); }
        { int32_t iv; std::memcpy(&iv, &st.vf[30][1], 4);
          ur1 = static_cast<float>(iv); }
        { int32_t iv; std::memcpy(&iv, &st.vf[30][2], 4);
          ur2 = static_cast<float>(iv); }
      }
      bvReg = -1;
      st.vf[30][0] = ur0;
      st.vf[30][1] = ur1;
      st.vf[30][2] = ur2;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[30] = rt;
        cx.vfR[30][0] = rt;
        cx.vfR[30][1] = rt;
        cx.vfR[30][2] = rt;
      }
      c += 1u;
    }
    L0058:;
    { // pair 11 pc=0x58 up=0x01FD513C lo=0x800C53FC
      c = vu1gen::vmax(c, cx.vfRAny[10]);
      c = vu1gen::vmax(c, cx.vfR[10][0]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      float ur0 = 0.0f;
      float ur1 = 0.0f;
      float ur2 = 0.0f;
      float ur3 = 0.0f;
      {
        { int32_t iv; std::memcpy(&iv, &st.vf[10][0], 4);
          ur0 = static_cast<float>(iv); }
        { int32_t iv; std::memcpy(&iv, &st.vf[10][1], 4);
          ur1 = static_cast<float>(iv); }
        { int32_t iv; std::memcpy(&iv, &st.vf[10][2], 4);
          ur2 = static_cast<float>(iv); }
        { int32_t iv; std::memcpy(&iv, &st.vf[10][3], 4);
          ur3 = static_cast<float>(iv); }
      }
      {
        { uint32_t fv = 0u; std::memcpy(&fv, &st.vf[10][0], 4);
          bvOld = st.vi[12]; bvReg = 12;
          st.vi[12] = (int32_t)(int16_t)(fv & 0xFFFFu);
        }
      }
      st.vf[29][0] = ur0;
      st.vf[29][1] = ur1;
      st.vf[29][2] = ur2;
      st.vf[29][3] = ur3;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[29] = rt;
        _mm_store_si128((__m128i *)cx.vfR[29], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L0060:;
    { // pair 12 pc=0x60 up=0x01DFF93C lo=0x802D53FC
      c = vu1gen::vmax(c, cx.vfR[31][0]);
      c = vu1gen::vmax(c, cx.vfR[31][1]);
      c = vu1gen::vmax(c, cx.vfR[31][2]);
      c = vu1gen::vmax(c, cx.vfR[10][1]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      float ur0 = 0.0f;
      float ur1 = 0.0f;
      float ur2 = 0.0f;
      {
        { int32_t iv; std::memcpy(&iv, &st.vf[31][0], 4);
          ur0 = static_cast<float>(iv); }
        { int32_t iv; std::memcpy(&iv, &st.vf[31][1], 4);
          ur1 = static_cast<float>(iv); }
        { int32_t iv; std::memcpy(&iv, &st.vf[31][2], 4);
          ur2 = static_cast<float>(iv); }
      }
      {
        { uint32_t fv = 0u; std::memcpy(&fv, &st.vf[10][1], 4);
          bvOld = st.vi[13]; bvReg = 13;
          st.vi[13] = (int32_t)(int16_t)(fv & 0xFFFFu);
        }
      }
      st.vf[31][0] = ur0;
      st.vf[31][1] = ur1;
      st.vf[31][2] = ur2;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[31] = rt;
        cx.vfR[31][0] = rt;
        cx.vfR[31][1] = rt;
        cx.vfR[31][2] = rt;
      }
      c += 1u;
    }
    L0068:;
    { // pair 13 pc=0x68 up=0x000002FF lo=0x804E53FC
      c = vu1gen::vmax(c, cx.vfR[10][2]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { uint32_t fv = 0u; std::memcpy(&fv, &st.vf[10][2], 4);
          bvOld = st.vi[14]; bvReg = 14;
          st.vi[14] = (int32_t)(int16_t)(fv & 0xFFFFu);
        }
      }
      c += 1u;
    }
    L0070:;
    { const bool bt = (int16_t)(bvReg == 12 ? bvOld : st.vi[12]) <= 0;
    { // pair 14 pc=0x70 up=0x01FE69BC lo=0x5C006006
      c = vu1gen::vmax(c, cx.vfRAny[13]);
      c = vu1gen::vmax(c, cx.vfR[30][0]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[13]);
        const __m128 bv = vu1gen::nrmbc(st.vf[30], 0);
        const __m128 rv = _mm_mul_ps(vsv, bv);
        uint32_t mac = 0u, stf = 0u, stk = 0u;
        __m128 rvn = rv;
        { uint32_t sgn; uint32_t plain = vu1gen::classify4(rv, sgn);
          if ((plain & 0xFu) == 0xFu) {
            mac = vu1gen::kMacSign.word[sgn & 0xFu];
            stf = (sgn & 0xFu) != 0u ? 0x2u : 0u;
          } else {
            float rr[4]; _mm_storeu_ps(rr, rv);
            { uint8_t lf;
              if (plain & 1u) lf = ((sgn >> 0) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[0], (double)_mm_cvtss_f32(vsv) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[0] = vu1gen::normResult(rr[0], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[0][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 2u) lf = ((sgn >> 1) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[1], (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(1, 1, 1, 1))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[1] = vu1gen::normResult(rr[1], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[1][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 4u) lf = ((sgn >> 2) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[2], (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(2, 2, 2, 2))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[2] = vu1gen::normResult(rr[2], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[2][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 8u) lf = ((sgn >> 3) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[3], (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(3, 3, 3, 3))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[3] = vu1gen::normResult(rr[3], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[3][lf & 0xFu]; stf |= lf & 0xFu; }
            rvn = _mm_loadu_ps(rr);
          } }
        cx.pushFmac(c, mac, stf, stk);
        vu1gen::storeLanes(st.acc, rvn, 0xFu);
      }
      bvReg = -1;
      c += 1u;
    }
    { // pair 15 pc=0x78 up=0x01FE70BD lo=0x018700FF
      c = vu1gen::vmax(c, cx.vfRAny[14]);
      c = vu1gen::vmax(c, cx.vfR[30][1]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[14]);
        const __m128 bv = vu1gen::nrmbc(st.vf[30], 1);
        const __m128 av = vu1gen::nrm4(st.acc);
        const __m128 product = _mm_mul_ps(vsv, bv);
        const __m128 rv = _mm_add_ps(av, product);
        uint32_t mac = 0u, stf = 0u, stk = 0u;
        __m128 rvn = rv;
        { uint32_t sgn; uint32_t plain = vu1gen::classify4(rv, sgn);
          const __m128i pm = _mm_and_si128(_mm_castps_si128(product), _mm_set1_epi32(0x7FFFFFFF));
          plain &= ~uint32_t(_mm_movemask_ps(_mm_castsi128_ps(_mm_cmpgt_epi32(pm, _mm_set1_epi32(0x7F7FFFFE)))));
          if ((plain & 0xFu) == 0xFu) {
            mac = vu1gen::kMacSign.word[sgn & 0xFu];
            stf = (sgn & 0xFu) != 0u ? 0x2u : 0u;
          } else {
            float rr[4]; _mm_storeu_ps(rr, rv);
            { uint8_t lf;
              if (plain & 1u) lf = ((sgn >> 0) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[0], (double)_mm_cvtss_f32(av) + (double)_mm_cvtss_f32(vsv) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[0] = vu1gen::normResult(rr[0], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[0][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 2u) lf = ((sgn >> 1) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[1], (double)_mm_cvtss_f32(_mm_shuffle_ps(av, av, _MM_SHUFFLE(1, 1, 1, 1))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(1, 1, 1, 1))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[1] = vu1gen::normResult(rr[1], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[1][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 4u) lf = ((sgn >> 2) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[2], (double)_mm_cvtss_f32(_mm_shuffle_ps(av, av, _MM_SHUFFLE(2, 2, 2, 2))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(2, 2, 2, 2))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[2] = vu1gen::normResult(rr[2], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[2][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 8u) lf = ((sgn >> 3) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[3], (double)_mm_cvtss_f32(_mm_shuffle_ps(av, av, _MM_SHUFFLE(3, 3, 3, 3))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(3, 3, 3, 3))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[3] = vu1gen::normResult(rr[3], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[3][lf & 0xFu]; stf |= lf & 0xFu; }
            rvn = _mm_loadu_ps(rr);
          } }
        if (cx.sticky) stk = vu1gen::sticky4(vsv, bv, product, 0xFu);
        cx.pushFmac(c, mac, stf, stk);
        vu1gen::storeLanes(st.acc, rvn, 0xFu);
      }
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 255) * 16u) & 0xFFFu;
          std::memcpy(&st.vf[7][0], vm + addr + 0u, 8);
        }
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[7] = rt;
        cx.vfR[7][0] = rt;
        cx.vfR[7][1] = rt;
      }
      c += 1u;
    }
    if (bt) {
      st.branchTarget = 0xA8u;
      goto L00A8;
    } }
    goto LC0080;
    L0078:;
    { // pair 15 pc=0x78 up=0x01FE70BD lo=0x018700FF
      c = vu1gen::vmax(c, cx.vfRAny[14]);
      c = vu1gen::vmax(c, cx.vfR[30][1]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[14]);
        const __m128 bv = vu1gen::nrmbc(st.vf[30], 1);
        const __m128 av = vu1gen::nrm4(st.acc);
        const __m128 product = _mm_mul_ps(vsv, bv);
        const __m128 rv = _mm_add_ps(av, product);
        uint32_t mac = 0u, stf = 0u, stk = 0u;
        __m128 rvn = rv;
        { uint32_t sgn; uint32_t plain = vu1gen::classify4(rv, sgn);
          const __m128i pm = _mm_and_si128(_mm_castps_si128(product), _mm_set1_epi32(0x7FFFFFFF));
          plain &= ~uint32_t(_mm_movemask_ps(_mm_castsi128_ps(_mm_cmpgt_epi32(pm, _mm_set1_epi32(0x7F7FFFFE)))));
          if ((plain & 0xFu) == 0xFu) {
            mac = vu1gen::kMacSign.word[sgn & 0xFu];
            stf = (sgn & 0xFu) != 0u ? 0x2u : 0u;
          } else {
            float rr[4]; _mm_storeu_ps(rr, rv);
            { uint8_t lf;
              if (plain & 1u) lf = ((sgn >> 0) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[0], (double)_mm_cvtss_f32(av) + (double)_mm_cvtss_f32(vsv) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[0] = vu1gen::normResult(rr[0], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[0][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 2u) lf = ((sgn >> 1) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[1], (double)_mm_cvtss_f32(_mm_shuffle_ps(av, av, _MM_SHUFFLE(1, 1, 1, 1))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(1, 1, 1, 1))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[1] = vu1gen::normResult(rr[1], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[1][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 4u) lf = ((sgn >> 2) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[2], (double)_mm_cvtss_f32(_mm_shuffle_ps(av, av, _MM_SHUFFLE(2, 2, 2, 2))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(2, 2, 2, 2))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[2] = vu1gen::normResult(rr[2], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[2][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 8u) lf = ((sgn >> 3) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[3], (double)_mm_cvtss_f32(_mm_shuffle_ps(av, av, _MM_SHUFFLE(3, 3, 3, 3))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(3, 3, 3, 3))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[3] = vu1gen::normResult(rr[3], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[3][lf & 0xFu]; stf |= lf & 0xFu; }
            rvn = _mm_loadu_ps(rr);
          } }
        if (cx.sticky) stk = vu1gen::sticky4(vsv, bv, product, 0xFu);
        cx.pushFmac(c, mac, stf, stk);
        vu1gen::storeLanes(st.acc, rvn, 0xFu);
      }
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 255) * 16u) & 0xFFFu;
          std::memcpy(&st.vf[7][0], vm + addr + 0u, 8);
        }
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[7] = rt;
        cx.vfR[7][0] = rt;
        cx.vfR[7][1] = rt;
      }
      c += 1u;
    }
    LC0080:;
    L0080:;
    { // pair 16 pc=0x80 up=0x01FE78BE lo=0x8000033C
      c = vu1gen::vmax(c, cx.vfRAny[15]);
      c = vu1gen::vmax(c, cx.vfR[30][2]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[15]);
        const __m128 bv = vu1gen::nrmbc(st.vf[30], 2);
        const __m128 av = vu1gen::nrm4(st.acc);
        const __m128 product = _mm_mul_ps(vsv, bv);
        const __m128 rv = _mm_add_ps(av, product);
        uint32_t mac = 0u, stf = 0u, stk = 0u;
        __m128 rvn = rv;
        { uint32_t sgn; uint32_t plain = vu1gen::classify4(rv, sgn);
          const __m128i pm = _mm_and_si128(_mm_castps_si128(product), _mm_set1_epi32(0x7FFFFFFF));
          plain &= ~uint32_t(_mm_movemask_ps(_mm_castsi128_ps(_mm_cmpgt_epi32(pm, _mm_set1_epi32(0x7F7FFFFE)))));
          if ((plain & 0xFu) == 0xFu) {
            mac = vu1gen::kMacSign.word[sgn & 0xFu];
            stf = (sgn & 0xFu) != 0u ? 0x2u : 0u;
          } else {
            float rr[4]; _mm_storeu_ps(rr, rv);
            { uint8_t lf;
              if (plain & 1u) lf = ((sgn >> 0) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[0], (double)_mm_cvtss_f32(av) + (double)_mm_cvtss_f32(vsv) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[0] = vu1gen::normResult(rr[0], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[0][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 2u) lf = ((sgn >> 1) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[1], (double)_mm_cvtss_f32(_mm_shuffle_ps(av, av, _MM_SHUFFLE(1, 1, 1, 1))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(1, 1, 1, 1))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[1] = vu1gen::normResult(rr[1], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[1][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 4u) lf = ((sgn >> 2) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[2], (double)_mm_cvtss_f32(_mm_shuffle_ps(av, av, _MM_SHUFFLE(2, 2, 2, 2))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(2, 2, 2, 2))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[2] = vu1gen::normResult(rr[2], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[2][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 8u) lf = ((sgn >> 3) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[3], (double)_mm_cvtss_f32(_mm_shuffle_ps(av, av, _MM_SHUFFLE(3, 3, 3, 3))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(3, 3, 3, 3))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[3] = vu1gen::normResult(rr[3], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[3][lf & 0xFu]; stf |= lf & 0xFu; }
            rvn = _mm_loadu_ps(rr);
          } }
        if (cx.sticky) stk = vu1gen::sticky4(vsv, bv, product, 0xFu);
        cx.pushFmac(c, mac, stf, stk);
        vu1gen::storeLanes(st.acc, rvn, 0xFu);
      }
      bvReg = -1;
      c += 1u;
    }
    L0088:;
    { // pair 17 pc=0x88 up=0x01FE824B lo=0x8000033C
      c = vu1gen::vmax(c, cx.vfRAny[16]);
      c = vu1gen::vmax(c, cx.vfR[30][3]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[16]);
        const __m128 bv = vu1gen::nrmbc(st.vf[30], 3);
        const __m128 av = vu1gen::nrm4(st.acc);
        const __m128 product = _mm_mul_ps(vsv, bv);
        const __m128 rv = _mm_add_ps(av, product);
        uint32_t mac = 0u, stf = 0u, stk = 0u;
        __m128 rvn = rv;
        { uint32_t sgn; uint32_t plain = vu1gen::classify4(rv, sgn);
          const __m128i pm = _mm_and_si128(_mm_castps_si128(product), _mm_set1_epi32(0x7FFFFFFF));
          plain &= ~uint32_t(_mm_movemask_ps(_mm_castsi128_ps(_mm_cmpgt_epi32(pm, _mm_set1_epi32(0x7F7FFFFE)))));
          if ((plain & 0xFu) == 0xFu) {
            mac = vu1gen::kMacSign.word[sgn & 0xFu];
            stf = (sgn & 0xFu) != 0u ? 0x2u : 0u;
          } else {
            float rr[4]; _mm_storeu_ps(rr, rv);
            { uint8_t lf;
              if (plain & 1u) lf = ((sgn >> 0) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[0], (double)_mm_cvtss_f32(av) + (double)_mm_cvtss_f32(vsv) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[0] = vu1gen::normResult(rr[0], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[0][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 2u) lf = ((sgn >> 1) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[1], (double)_mm_cvtss_f32(_mm_shuffle_ps(av, av, _MM_SHUFFLE(1, 1, 1, 1))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(1, 1, 1, 1))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[1] = vu1gen::normResult(rr[1], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[1][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 4u) lf = ((sgn >> 2) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[2], (double)_mm_cvtss_f32(_mm_shuffle_ps(av, av, _MM_SHUFFLE(2, 2, 2, 2))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(2, 2, 2, 2))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[2] = vu1gen::normResult(rr[2], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[2][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 8u) lf = ((sgn >> 3) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[3], (double)_mm_cvtss_f32(_mm_shuffle_ps(av, av, _MM_SHUFFLE(3, 3, 3, 3))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(3, 3, 3, 3))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[3] = vu1gen::normResult(rr[3], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[3][lf & 0xFu]; stf |= lf & 0xFu; }
            rvn = _mm_loadu_ps(rr);
          } }
        if (cx.sticky) stk = vu1gen::sticky4(vsv, bv, product, 0xFu);
        cx.pushFmac(c, mac, stf, stk);
        urv = rvn;
      }
      bvReg = -1;
      vu1gen::storeLanes(st.vf[9], urv, 0xFu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[9] = rt;
        _mm_store_si128((__m128i *)cx.vfR[9], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L0090:;
    { // pair 18 pc=0x90 up=0x01FF69BC lo=0x8000033C
      c = vu1gen::vmax(c, cx.vfRAny[13]);
      c = vu1gen::vmax(c, cx.vfR[31][0]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[13]);
        const __m128 bv = vu1gen::nrmbc(st.vf[31], 0);
        const __m128 rv = _mm_mul_ps(vsv, bv);
        uint32_t mac = 0u, stf = 0u, stk = 0u;
        __m128 rvn = rv;
        { uint32_t sgn; uint32_t plain = vu1gen::classify4(rv, sgn);
          if ((plain & 0xFu) == 0xFu) {
            mac = vu1gen::kMacSign.word[sgn & 0xFu];
            stf = (sgn & 0xFu) != 0u ? 0x2u : 0u;
          } else {
            float rr[4]; _mm_storeu_ps(rr, rv);
            { uint8_t lf;
              if (plain & 1u) lf = ((sgn >> 0) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[0], (double)_mm_cvtss_f32(vsv) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[0] = vu1gen::normResult(rr[0], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[0][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 2u) lf = ((sgn >> 1) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[1], (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(1, 1, 1, 1))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[1] = vu1gen::normResult(rr[1], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[1][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 4u) lf = ((sgn >> 2) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[2], (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(2, 2, 2, 2))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[2] = vu1gen::normResult(rr[2], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[2][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 8u) lf = ((sgn >> 3) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[3], (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(3, 3, 3, 3))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[3] = vu1gen::normResult(rr[3], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[3][lf & 0xFu]; stf |= lf & 0xFu; }
            rvn = _mm_loadu_ps(rr);
          } }
        cx.pushFmac(c, mac, stf, stk);
        vu1gen::storeLanes(st.acc, rvn, 0xFu);
      }
      bvReg = -1;
      c += 1u;
    }
    L0098:;
    { // pair 19 pc=0x98 up=0x01FF70BD lo=0x8000033C
      c = vu1gen::vmax(c, cx.vfRAny[14]);
      c = vu1gen::vmax(c, cx.vfR[31][1]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[14]);
        const __m128 bv = vu1gen::nrmbc(st.vf[31], 1);
        const __m128 av = vu1gen::nrm4(st.acc);
        const __m128 product = _mm_mul_ps(vsv, bv);
        const __m128 rv = _mm_add_ps(av, product);
        uint32_t mac = 0u, stf = 0u, stk = 0u;
        __m128 rvn = rv;
        { uint32_t sgn; uint32_t plain = vu1gen::classify4(rv, sgn);
          const __m128i pm = _mm_and_si128(_mm_castps_si128(product), _mm_set1_epi32(0x7FFFFFFF));
          plain &= ~uint32_t(_mm_movemask_ps(_mm_castsi128_ps(_mm_cmpgt_epi32(pm, _mm_set1_epi32(0x7F7FFFFE)))));
          if ((plain & 0xFu) == 0xFu) {
            mac = vu1gen::kMacSign.word[sgn & 0xFu];
            stf = (sgn & 0xFu) != 0u ? 0x2u : 0u;
          } else {
            float rr[4]; _mm_storeu_ps(rr, rv);
            { uint8_t lf;
              if (plain & 1u) lf = ((sgn >> 0) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[0], (double)_mm_cvtss_f32(av) + (double)_mm_cvtss_f32(vsv) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[0] = vu1gen::normResult(rr[0], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[0][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 2u) lf = ((sgn >> 1) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[1], (double)_mm_cvtss_f32(_mm_shuffle_ps(av, av, _MM_SHUFFLE(1, 1, 1, 1))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(1, 1, 1, 1))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[1] = vu1gen::normResult(rr[1], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[1][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 4u) lf = ((sgn >> 2) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[2], (double)_mm_cvtss_f32(_mm_shuffle_ps(av, av, _MM_SHUFFLE(2, 2, 2, 2))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(2, 2, 2, 2))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[2] = vu1gen::normResult(rr[2], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[2][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 8u) lf = ((sgn >> 3) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[3], (double)_mm_cvtss_f32(_mm_shuffle_ps(av, av, _MM_SHUFFLE(3, 3, 3, 3))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(3, 3, 3, 3))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[3] = vu1gen::normResult(rr[3], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[3][lf & 0xFu]; stf |= lf & 0xFu; }
            rvn = _mm_loadu_ps(rr);
          } }
        if (cx.sticky) stk = vu1gen::sticky4(vsv, bv, product, 0xFu);
        cx.pushFmac(c, mac, stf, stk);
        vu1gen::storeLanes(st.acc, rvn, 0xFu);
      }
      bvReg = -1;
      c += 1u;
    }
    L00A0:;
    { // pair 20 pc=0xA0 up=0x01FF784A lo=0x8000033C
      c = vu1gen::vmax(c, cx.vfRAny[15]);
      c = vu1gen::vmax(c, cx.vfR[31][2]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[15]);
        const __m128 bv = vu1gen::nrmbc(st.vf[31], 2);
        const __m128 av = vu1gen::nrm4(st.acc);
        const __m128 product = _mm_mul_ps(vsv, bv);
        const __m128 rv = _mm_add_ps(av, product);
        uint32_t mac = 0u, stf = 0u, stk = 0u;
        __m128 rvn = rv;
        { uint32_t sgn; uint32_t plain = vu1gen::classify4(rv, sgn);
          const __m128i pm = _mm_and_si128(_mm_castps_si128(product), _mm_set1_epi32(0x7FFFFFFF));
          plain &= ~uint32_t(_mm_movemask_ps(_mm_castsi128_ps(_mm_cmpgt_epi32(pm, _mm_set1_epi32(0x7F7FFFFE)))));
          if ((plain & 0xFu) == 0xFu) {
            mac = vu1gen::kMacSign.word[sgn & 0xFu];
            stf = (sgn & 0xFu) != 0u ? 0x2u : 0u;
          } else {
            float rr[4]; _mm_storeu_ps(rr, rv);
            { uint8_t lf;
              if (plain & 1u) lf = ((sgn >> 0) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[0], (double)_mm_cvtss_f32(av) + (double)_mm_cvtss_f32(vsv) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[0] = vu1gen::normResult(rr[0], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[0][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 2u) lf = ((sgn >> 1) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[1], (double)_mm_cvtss_f32(_mm_shuffle_ps(av, av, _MM_SHUFFLE(1, 1, 1, 1))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(1, 1, 1, 1))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[1] = vu1gen::normResult(rr[1], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[1][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 4u) lf = ((sgn >> 2) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[2], (double)_mm_cvtss_f32(_mm_shuffle_ps(av, av, _MM_SHUFFLE(2, 2, 2, 2))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(2, 2, 2, 2))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[2] = vu1gen::normResult(rr[2], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[2][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 8u) lf = ((sgn >> 3) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[3], (double)_mm_cvtss_f32(_mm_shuffle_ps(av, av, _MM_SHUFFLE(3, 3, 3, 3))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(3, 3, 3, 3))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[3] = vu1gen::normResult(rr[3], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[3][lf & 0xFu]; stf |= lf & 0xFu; }
            rvn = _mm_loadu_ps(rr);
          } }
        if (cx.sticky) stk = vu1gen::sticky4(vsv, bv, product, 0xFu);
        cx.pushFmac(c, mac, stf, stk);
        urv = rvn;
      }
      bvReg = -1;
      vu1gen::storeLanes(st.vf[1], urv, 0xFu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[1] = rt;
        _mm_store_si128((__m128i *)cx.vfR[1], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L00A8:;
    { const bool bt = (int16_t)(bvReg == 13 ? bvOld : st.vi[13]) <= 0;
    { // pair 21 pc=0xA8 up=0x01FE89BC lo=0x5C006806
      c = vu1gen::vmax(c, cx.vfRAny[17]);
      c = vu1gen::vmax(c, cx.vfR[30][0]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[17]);
        const __m128 bv = vu1gen::nrmbc(st.vf[30], 0);
        const __m128 rv = _mm_mul_ps(vsv, bv);
        uint32_t mac = 0u, stf = 0u, stk = 0u;
        __m128 rvn = rv;
        { uint32_t sgn; uint32_t plain = vu1gen::classify4(rv, sgn);
          if ((plain & 0xFu) == 0xFu) {
            mac = vu1gen::kMacSign.word[sgn & 0xFu];
            stf = (sgn & 0xFu) != 0u ? 0x2u : 0u;
          } else {
            float rr[4]; _mm_storeu_ps(rr, rv);
            { uint8_t lf;
              if (plain & 1u) lf = ((sgn >> 0) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[0], (double)_mm_cvtss_f32(vsv) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[0] = vu1gen::normResult(rr[0], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[0][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 2u) lf = ((sgn >> 1) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[1], (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(1, 1, 1, 1))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[1] = vu1gen::normResult(rr[1], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[1][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 4u) lf = ((sgn >> 2) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[2], (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(2, 2, 2, 2))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[2] = vu1gen::normResult(rr[2], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[2][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 8u) lf = ((sgn >> 3) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[3], (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(3, 3, 3, 3))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[3] = vu1gen::normResult(rr[3], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[3][lf & 0xFu]; stf |= lf & 0xFu; }
            rvn = _mm_loadu_ps(rr);
          } }
        cx.pushFmac(c, mac, stf, stk);
        vu1gen::storeLanes(st.acc, rvn, 0xFu);
      }
      bvReg = -1;
      c += 1u;
    }
    { // pair 22 pc=0xB0 up=0x01FE90BD lo=0x806F53FC
      c = vu1gen::vmax(c, cx.vfRAny[18]);
      c = vu1gen::vmax(c, cx.vfR[30][1]);
      c = vu1gen::vmax(c, cx.vfR[10][3]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[18]);
        const __m128 bv = vu1gen::nrmbc(st.vf[30], 1);
        const __m128 av = vu1gen::nrm4(st.acc);
        const __m128 product = _mm_mul_ps(vsv, bv);
        const __m128 rv = _mm_add_ps(av, product);
        uint32_t mac = 0u, stf = 0u, stk = 0u;
        __m128 rvn = rv;
        { uint32_t sgn; uint32_t plain = vu1gen::classify4(rv, sgn);
          const __m128i pm = _mm_and_si128(_mm_castps_si128(product), _mm_set1_epi32(0x7FFFFFFF));
          plain &= ~uint32_t(_mm_movemask_ps(_mm_castsi128_ps(_mm_cmpgt_epi32(pm, _mm_set1_epi32(0x7F7FFFFE)))));
          if ((plain & 0xFu) == 0xFu) {
            mac = vu1gen::kMacSign.word[sgn & 0xFu];
            stf = (sgn & 0xFu) != 0u ? 0x2u : 0u;
          } else {
            float rr[4]; _mm_storeu_ps(rr, rv);
            { uint8_t lf;
              if (plain & 1u) lf = ((sgn >> 0) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[0], (double)_mm_cvtss_f32(av) + (double)_mm_cvtss_f32(vsv) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[0] = vu1gen::normResult(rr[0], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[0][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 2u) lf = ((sgn >> 1) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[1], (double)_mm_cvtss_f32(_mm_shuffle_ps(av, av, _MM_SHUFFLE(1, 1, 1, 1))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(1, 1, 1, 1))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[1] = vu1gen::normResult(rr[1], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[1][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 4u) lf = ((sgn >> 2) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[2], (double)_mm_cvtss_f32(_mm_shuffle_ps(av, av, _MM_SHUFFLE(2, 2, 2, 2))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(2, 2, 2, 2))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[2] = vu1gen::normResult(rr[2], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[2][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 8u) lf = ((sgn >> 3) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[3], (double)_mm_cvtss_f32(_mm_shuffle_ps(av, av, _MM_SHUFFLE(3, 3, 3, 3))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(3, 3, 3, 3))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[3] = vu1gen::normResult(rr[3], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[3][lf & 0xFu]; stf |= lf & 0xFu; }
            rvn = _mm_loadu_ps(rr);
          } }
        if (cx.sticky) stk = vu1gen::sticky4(vsv, bv, product, 0xFu);
        cx.pushFmac(c, mac, stf, stk);
        vu1gen::storeLanes(st.acc, rvn, 0xFu);
      }
      {
        { uint32_t fv = 0u; std::memcpy(&fv, &st.vf[10][3], 4);
          bvOld = st.vi[15]; bvReg = 15;
          st.vi[15] = (int32_t)(int16_t)(fv & 0xFFFFu);
        }
      }
      c += 1u;
    }
    if (bt) {
      st.branchTarget = 0xE0u;
      goto L00E0;
    } }
    goto LC00B8;
    L00B0:;
    { // pair 22 pc=0xB0 up=0x01FE90BD lo=0x806F53FC
      c = vu1gen::vmax(c, cx.vfRAny[18]);
      c = vu1gen::vmax(c, cx.vfR[30][1]);
      c = vu1gen::vmax(c, cx.vfR[10][3]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[18]);
        const __m128 bv = vu1gen::nrmbc(st.vf[30], 1);
        const __m128 av = vu1gen::nrm4(st.acc);
        const __m128 product = _mm_mul_ps(vsv, bv);
        const __m128 rv = _mm_add_ps(av, product);
        uint32_t mac = 0u, stf = 0u, stk = 0u;
        __m128 rvn = rv;
        { uint32_t sgn; uint32_t plain = vu1gen::classify4(rv, sgn);
          const __m128i pm = _mm_and_si128(_mm_castps_si128(product), _mm_set1_epi32(0x7FFFFFFF));
          plain &= ~uint32_t(_mm_movemask_ps(_mm_castsi128_ps(_mm_cmpgt_epi32(pm, _mm_set1_epi32(0x7F7FFFFE)))));
          if ((plain & 0xFu) == 0xFu) {
            mac = vu1gen::kMacSign.word[sgn & 0xFu];
            stf = (sgn & 0xFu) != 0u ? 0x2u : 0u;
          } else {
            float rr[4]; _mm_storeu_ps(rr, rv);
            { uint8_t lf;
              if (plain & 1u) lf = ((sgn >> 0) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[0], (double)_mm_cvtss_f32(av) + (double)_mm_cvtss_f32(vsv) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[0] = vu1gen::normResult(rr[0], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[0][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 2u) lf = ((sgn >> 1) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[1], (double)_mm_cvtss_f32(_mm_shuffle_ps(av, av, _MM_SHUFFLE(1, 1, 1, 1))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(1, 1, 1, 1))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[1] = vu1gen::normResult(rr[1], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[1][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 4u) lf = ((sgn >> 2) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[2], (double)_mm_cvtss_f32(_mm_shuffle_ps(av, av, _MM_SHUFFLE(2, 2, 2, 2))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(2, 2, 2, 2))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[2] = vu1gen::normResult(rr[2], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[2][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 8u) lf = ((sgn >> 3) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[3], (double)_mm_cvtss_f32(_mm_shuffle_ps(av, av, _MM_SHUFFLE(3, 3, 3, 3))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(3, 3, 3, 3))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[3] = vu1gen::normResult(rr[3], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[3][lf & 0xFu]; stf |= lf & 0xFu; }
            rvn = _mm_loadu_ps(rr);
          } }
        if (cx.sticky) stk = vu1gen::sticky4(vsv, bv, product, 0xFu);
        cx.pushFmac(c, mac, stf, stk);
        vu1gen::storeLanes(st.acc, rvn, 0xFu);
      }
      {
        { uint32_t fv = 0u; std::memcpy(&fv, &st.vf[10][3], 4);
          bvOld = st.vi[15]; bvReg = 15;
          st.vi[15] = (int32_t)(int16_t)(fv & 0xFFFFu);
        }
      }
      c += 1u;
    }
    LC00B8:;
    L00B8:;
    { // pair 23 pc=0xB8 up=0x01FE98BE lo=0x8000033C
      c = vu1gen::vmax(c, cx.vfRAny[19]);
      c = vu1gen::vmax(c, cx.vfR[30][2]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[19]);
        const __m128 bv = vu1gen::nrmbc(st.vf[30], 2);
        const __m128 av = vu1gen::nrm4(st.acc);
        const __m128 product = _mm_mul_ps(vsv, bv);
        const __m128 rv = _mm_add_ps(av, product);
        uint32_t mac = 0u, stf = 0u, stk = 0u;
        __m128 rvn = rv;
        { uint32_t sgn; uint32_t plain = vu1gen::classify4(rv, sgn);
          const __m128i pm = _mm_and_si128(_mm_castps_si128(product), _mm_set1_epi32(0x7FFFFFFF));
          plain &= ~uint32_t(_mm_movemask_ps(_mm_castsi128_ps(_mm_cmpgt_epi32(pm, _mm_set1_epi32(0x7F7FFFFE)))));
          if ((plain & 0xFu) == 0xFu) {
            mac = vu1gen::kMacSign.word[sgn & 0xFu];
            stf = (sgn & 0xFu) != 0u ? 0x2u : 0u;
          } else {
            float rr[4]; _mm_storeu_ps(rr, rv);
            { uint8_t lf;
              if (plain & 1u) lf = ((sgn >> 0) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[0], (double)_mm_cvtss_f32(av) + (double)_mm_cvtss_f32(vsv) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[0] = vu1gen::normResult(rr[0], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[0][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 2u) lf = ((sgn >> 1) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[1], (double)_mm_cvtss_f32(_mm_shuffle_ps(av, av, _MM_SHUFFLE(1, 1, 1, 1))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(1, 1, 1, 1))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[1] = vu1gen::normResult(rr[1], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[1][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 4u) lf = ((sgn >> 2) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[2], (double)_mm_cvtss_f32(_mm_shuffle_ps(av, av, _MM_SHUFFLE(2, 2, 2, 2))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(2, 2, 2, 2))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[2] = vu1gen::normResult(rr[2], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[2][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 8u) lf = ((sgn >> 3) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[3], (double)_mm_cvtss_f32(_mm_shuffle_ps(av, av, _MM_SHUFFLE(3, 3, 3, 3))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(3, 3, 3, 3))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[3] = vu1gen::normResult(rr[3], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[3][lf & 0xFu]; stf |= lf & 0xFu; }
            rvn = _mm_loadu_ps(rr);
          } }
        if (cx.sticky) stk = vu1gen::sticky4(vsv, bv, product, 0xFu);
        cx.pushFmac(c, mac, stf, stk);
        vu1gen::storeLanes(st.acc, rvn, 0xFu);
      }
      bvReg = -1;
      c += 1u;
    }
    L00C0:;
    { // pair 24 pc=0xC0 up=0x01FEA28B lo=0x8000033C
      c = vu1gen::vmax(c, cx.vfRAny[20]);
      c = vu1gen::vmax(c, cx.vfR[30][3]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[20]);
        const __m128 bv = vu1gen::nrmbc(st.vf[30], 3);
        const __m128 av = vu1gen::nrm4(st.acc);
        const __m128 product = _mm_mul_ps(vsv, bv);
        const __m128 rv = _mm_add_ps(av, product);
        uint32_t mac = 0u, stf = 0u, stk = 0u;
        __m128 rvn = rv;
        { uint32_t sgn; uint32_t plain = vu1gen::classify4(rv, sgn);
          const __m128i pm = _mm_and_si128(_mm_castps_si128(product), _mm_set1_epi32(0x7FFFFFFF));
          plain &= ~uint32_t(_mm_movemask_ps(_mm_castsi128_ps(_mm_cmpgt_epi32(pm, _mm_set1_epi32(0x7F7FFFFE)))));
          if ((plain & 0xFu) == 0xFu) {
            mac = vu1gen::kMacSign.word[sgn & 0xFu];
            stf = (sgn & 0xFu) != 0u ? 0x2u : 0u;
          } else {
            float rr[4]; _mm_storeu_ps(rr, rv);
            { uint8_t lf;
              if (plain & 1u) lf = ((sgn >> 0) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[0], (double)_mm_cvtss_f32(av) + (double)_mm_cvtss_f32(vsv) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[0] = vu1gen::normResult(rr[0], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[0][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 2u) lf = ((sgn >> 1) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[1], (double)_mm_cvtss_f32(_mm_shuffle_ps(av, av, _MM_SHUFFLE(1, 1, 1, 1))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(1, 1, 1, 1))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[1] = vu1gen::normResult(rr[1], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[1][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 4u) lf = ((sgn >> 2) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[2], (double)_mm_cvtss_f32(_mm_shuffle_ps(av, av, _MM_SHUFFLE(2, 2, 2, 2))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(2, 2, 2, 2))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[2] = vu1gen::normResult(rr[2], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[2][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 8u) lf = ((sgn >> 3) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[3], (double)_mm_cvtss_f32(_mm_shuffle_ps(av, av, _MM_SHUFFLE(3, 3, 3, 3))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(3, 3, 3, 3))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[3] = vu1gen::normResult(rr[3], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[3][lf & 0xFu]; stf |= lf & 0xFu; }
            rvn = _mm_loadu_ps(rr);
          } }
        if (cx.sticky) stk = vu1gen::sticky4(vsv, bv, product, 0xFu);
        cx.pushFmac(c, mac, stf, stk);
        urv = rvn;
      }
      bvReg = -1;
      vu1gen::storeLanes(st.vf[10], urv, 0xFu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[10] = rt;
        _mm_store_si128((__m128i *)cx.vfR[10], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L00C8:;
    { // pair 25 pc=0xC8 up=0x01FF89BC lo=0x8000033C
      c = vu1gen::vmax(c, cx.vfRAny[17]);
      c = vu1gen::vmax(c, cx.vfR[31][0]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[17]);
        const __m128 bv = vu1gen::nrmbc(st.vf[31], 0);
        const __m128 rv = _mm_mul_ps(vsv, bv);
        uint32_t mac = 0u, stf = 0u, stk = 0u;
        __m128 rvn = rv;
        { uint32_t sgn; uint32_t plain = vu1gen::classify4(rv, sgn);
          if ((plain & 0xFu) == 0xFu) {
            mac = vu1gen::kMacSign.word[sgn & 0xFu];
            stf = (sgn & 0xFu) != 0u ? 0x2u : 0u;
          } else {
            float rr[4]; _mm_storeu_ps(rr, rv);
            { uint8_t lf;
              if (plain & 1u) lf = ((sgn >> 0) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[0], (double)_mm_cvtss_f32(vsv) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[0] = vu1gen::normResult(rr[0], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[0][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 2u) lf = ((sgn >> 1) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[1], (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(1, 1, 1, 1))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[1] = vu1gen::normResult(rr[1], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[1][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 4u) lf = ((sgn >> 2) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[2], (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(2, 2, 2, 2))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[2] = vu1gen::normResult(rr[2], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[2][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 8u) lf = ((sgn >> 3) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[3], (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(3, 3, 3, 3))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[3] = vu1gen::normResult(rr[3], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[3][lf & 0xFu]; stf |= lf & 0xFu; }
            rvn = _mm_loadu_ps(rr);
          } }
        cx.pushFmac(c, mac, stf, stk);
        vu1gen::storeLanes(st.acc, rvn, 0xFu);
      }
      bvReg = -1;
      c += 1u;
    }
    L00D0:;
    { // pair 26 pc=0xD0 up=0x01FF90BD lo=0x8000033C
      c = vu1gen::vmax(c, cx.vfRAny[18]);
      c = vu1gen::vmax(c, cx.vfR[31][1]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[18]);
        const __m128 bv = vu1gen::nrmbc(st.vf[31], 1);
        const __m128 av = vu1gen::nrm4(st.acc);
        const __m128 product = _mm_mul_ps(vsv, bv);
        const __m128 rv = _mm_add_ps(av, product);
        uint32_t mac = 0u, stf = 0u, stk = 0u;
        __m128 rvn = rv;
        { uint32_t sgn; uint32_t plain = vu1gen::classify4(rv, sgn);
          const __m128i pm = _mm_and_si128(_mm_castps_si128(product), _mm_set1_epi32(0x7FFFFFFF));
          plain &= ~uint32_t(_mm_movemask_ps(_mm_castsi128_ps(_mm_cmpgt_epi32(pm, _mm_set1_epi32(0x7F7FFFFE)))));
          if ((plain & 0xFu) == 0xFu) {
            mac = vu1gen::kMacSign.word[sgn & 0xFu];
            stf = (sgn & 0xFu) != 0u ? 0x2u : 0u;
          } else {
            float rr[4]; _mm_storeu_ps(rr, rv);
            { uint8_t lf;
              if (plain & 1u) lf = ((sgn >> 0) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[0], (double)_mm_cvtss_f32(av) + (double)_mm_cvtss_f32(vsv) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[0] = vu1gen::normResult(rr[0], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[0][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 2u) lf = ((sgn >> 1) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[1], (double)_mm_cvtss_f32(_mm_shuffle_ps(av, av, _MM_SHUFFLE(1, 1, 1, 1))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(1, 1, 1, 1))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[1] = vu1gen::normResult(rr[1], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[1][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 4u) lf = ((sgn >> 2) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[2], (double)_mm_cvtss_f32(_mm_shuffle_ps(av, av, _MM_SHUFFLE(2, 2, 2, 2))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(2, 2, 2, 2))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[2] = vu1gen::normResult(rr[2], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[2][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 8u) lf = ((sgn >> 3) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[3], (double)_mm_cvtss_f32(_mm_shuffle_ps(av, av, _MM_SHUFFLE(3, 3, 3, 3))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(3, 3, 3, 3))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[3] = vu1gen::normResult(rr[3], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[3][lf & 0xFu]; stf |= lf & 0xFu; }
            rvn = _mm_loadu_ps(rr);
          } }
        if (cx.sticky) stk = vu1gen::sticky4(vsv, bv, product, 0xFu);
        cx.pushFmac(c, mac, stf, stk);
        vu1gen::storeLanes(st.acc, rvn, 0xFu);
      }
      bvReg = -1;
      c += 1u;
    }
    L00D8:;
    { // pair 27 pc=0xD8 up=0x01FF988A lo=0x8000033C
      c = vu1gen::vmax(c, cx.vfRAny[19]);
      c = vu1gen::vmax(c, cx.vfR[31][2]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[19]);
        const __m128 bv = vu1gen::nrmbc(st.vf[31], 2);
        const __m128 av = vu1gen::nrm4(st.acc);
        const __m128 product = _mm_mul_ps(vsv, bv);
        const __m128 rv = _mm_add_ps(av, product);
        uint32_t mac = 0u, stf = 0u, stk = 0u;
        __m128 rvn = rv;
        { uint32_t sgn; uint32_t plain = vu1gen::classify4(rv, sgn);
          const __m128i pm = _mm_and_si128(_mm_castps_si128(product), _mm_set1_epi32(0x7FFFFFFF));
          plain &= ~uint32_t(_mm_movemask_ps(_mm_castsi128_ps(_mm_cmpgt_epi32(pm, _mm_set1_epi32(0x7F7FFFFE)))));
          if ((plain & 0xFu) == 0xFu) {
            mac = vu1gen::kMacSign.word[sgn & 0xFu];
            stf = (sgn & 0xFu) != 0u ? 0x2u : 0u;
          } else {
            float rr[4]; _mm_storeu_ps(rr, rv);
            { uint8_t lf;
              if (plain & 1u) lf = ((sgn >> 0) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[0], (double)_mm_cvtss_f32(av) + (double)_mm_cvtss_f32(vsv) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[0] = vu1gen::normResult(rr[0], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[0][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 2u) lf = ((sgn >> 1) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[1], (double)_mm_cvtss_f32(_mm_shuffle_ps(av, av, _MM_SHUFFLE(1, 1, 1, 1))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(1, 1, 1, 1))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[1] = vu1gen::normResult(rr[1], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[1][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 4u) lf = ((sgn >> 2) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[2], (double)_mm_cvtss_f32(_mm_shuffle_ps(av, av, _MM_SHUFFLE(2, 2, 2, 2))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(2, 2, 2, 2))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[2] = vu1gen::normResult(rr[2], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[2][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 8u) lf = ((sgn >> 3) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[3], (double)_mm_cvtss_f32(_mm_shuffle_ps(av, av, _MM_SHUFFLE(3, 3, 3, 3))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(3, 3, 3, 3))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[3] = vu1gen::normResult(rr[3], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[3][lf & 0xFu]; stf |= lf & 0xFu; }
            rvn = _mm_loadu_ps(rr);
          } }
        if (cx.sticky) stk = vu1gen::sticky4(vsv, bv, product, 0xFu);
        cx.pushFmac(c, mac, stf, stk);
        urv = rvn;
      }
      bvReg = -1;
      vu1gen::storeLanes(st.vf[2], urv, 0xFu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[2] = rt;
        _mm_store_si128((__m128i *)cx.vfR[2], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L00E0:;
    { const bool bt = (int16_t)(bvReg == 14 ? bvOld : st.vi[14]) <= 0;
    { // pair 28 pc=0xE0 up=0x01FEA9BC lo=0x5C007006
      c = vu1gen::vmax(c, cx.vfRAny[21]);
      c = vu1gen::vmax(c, cx.vfR[30][0]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[21]);
        const __m128 bv = vu1gen::nrmbc(st.vf[30], 0);
        const __m128 rv = _mm_mul_ps(vsv, bv);
        uint32_t mac = 0u, stf = 0u, stk = 0u;
        __m128 rvn = rv;
        { uint32_t sgn; uint32_t plain = vu1gen::classify4(rv, sgn);
          if ((plain & 0xFu) == 0xFu) {
            mac = vu1gen::kMacSign.word[sgn & 0xFu];
            stf = (sgn & 0xFu) != 0u ? 0x2u : 0u;
          } else {
            float rr[4]; _mm_storeu_ps(rr, rv);
            { uint8_t lf;
              if (plain & 1u) lf = ((sgn >> 0) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[0], (double)_mm_cvtss_f32(vsv) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[0] = vu1gen::normResult(rr[0], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[0][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 2u) lf = ((sgn >> 1) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[1], (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(1, 1, 1, 1))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[1] = vu1gen::normResult(rr[1], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[1][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 4u) lf = ((sgn >> 2) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[2], (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(2, 2, 2, 2))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[2] = vu1gen::normResult(rr[2], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[2][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 8u) lf = ((sgn >> 3) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[3], (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(3, 3, 3, 3))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[3] = vu1gen::normResult(rr[3], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[3][lf & 0xFu]; stf |= lf & 0xFu; }
            rvn = _mm_loadu_ps(rr);
          } }
        cx.pushFmac(c, mac, stf, stk);
        vu1gen::storeLanes(st.acc, rvn, 0xFu);
      }
      bvReg = -1;
      c += 1u;
    }
    { // pair 29 pc=0xE8 up=0x01FEB0BD lo=0x8000033C
      c = vu1gen::vmax(c, cx.vfRAny[22]);
      c = vu1gen::vmax(c, cx.vfR[30][1]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[22]);
        const __m128 bv = vu1gen::nrmbc(st.vf[30], 1);
        const __m128 av = vu1gen::nrm4(st.acc);
        const __m128 product = _mm_mul_ps(vsv, bv);
        const __m128 rv = _mm_add_ps(av, product);
        uint32_t mac = 0u, stf = 0u, stk = 0u;
        __m128 rvn = rv;
        { uint32_t sgn; uint32_t plain = vu1gen::classify4(rv, sgn);
          const __m128i pm = _mm_and_si128(_mm_castps_si128(product), _mm_set1_epi32(0x7FFFFFFF));
          plain &= ~uint32_t(_mm_movemask_ps(_mm_castsi128_ps(_mm_cmpgt_epi32(pm, _mm_set1_epi32(0x7F7FFFFE)))));
          if ((plain & 0xFu) == 0xFu) {
            mac = vu1gen::kMacSign.word[sgn & 0xFu];
            stf = (sgn & 0xFu) != 0u ? 0x2u : 0u;
          } else {
            float rr[4]; _mm_storeu_ps(rr, rv);
            { uint8_t lf;
              if (plain & 1u) lf = ((sgn >> 0) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[0], (double)_mm_cvtss_f32(av) + (double)_mm_cvtss_f32(vsv) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[0] = vu1gen::normResult(rr[0], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[0][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 2u) lf = ((sgn >> 1) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[1], (double)_mm_cvtss_f32(_mm_shuffle_ps(av, av, _MM_SHUFFLE(1, 1, 1, 1))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(1, 1, 1, 1))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[1] = vu1gen::normResult(rr[1], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[1][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 4u) lf = ((sgn >> 2) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[2], (double)_mm_cvtss_f32(_mm_shuffle_ps(av, av, _MM_SHUFFLE(2, 2, 2, 2))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(2, 2, 2, 2))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[2] = vu1gen::normResult(rr[2], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[2][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 8u) lf = ((sgn >> 3) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[3], (double)_mm_cvtss_f32(_mm_shuffle_ps(av, av, _MM_SHUFFLE(3, 3, 3, 3))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(3, 3, 3, 3))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[3] = vu1gen::normResult(rr[3], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[3][lf & 0xFu]; stf |= lf & 0xFu; }
            rvn = _mm_loadu_ps(rr);
          } }
        if (cx.sticky) stk = vu1gen::sticky4(vsv, bv, product, 0xFu);
        cx.pushFmac(c, mac, stf, stk);
        vu1gen::storeLanes(st.acc, rvn, 0xFu);
      }
      bvReg = -1;
      c += 1u;
    }
    if (bt) {
      st.branchTarget = 0x118u;
      goto L0118;
    } }
    goto LC00F0;
    L00E8:;
    { // pair 29 pc=0xE8 up=0x01FEB0BD lo=0x8000033C
      c = vu1gen::vmax(c, cx.vfRAny[22]);
      c = vu1gen::vmax(c, cx.vfR[30][1]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[22]);
        const __m128 bv = vu1gen::nrmbc(st.vf[30], 1);
        const __m128 av = vu1gen::nrm4(st.acc);
        const __m128 product = _mm_mul_ps(vsv, bv);
        const __m128 rv = _mm_add_ps(av, product);
        uint32_t mac = 0u, stf = 0u, stk = 0u;
        __m128 rvn = rv;
        { uint32_t sgn; uint32_t plain = vu1gen::classify4(rv, sgn);
          const __m128i pm = _mm_and_si128(_mm_castps_si128(product), _mm_set1_epi32(0x7FFFFFFF));
          plain &= ~uint32_t(_mm_movemask_ps(_mm_castsi128_ps(_mm_cmpgt_epi32(pm, _mm_set1_epi32(0x7F7FFFFE)))));
          if ((plain & 0xFu) == 0xFu) {
            mac = vu1gen::kMacSign.word[sgn & 0xFu];
            stf = (sgn & 0xFu) != 0u ? 0x2u : 0u;
          } else {
            float rr[4]; _mm_storeu_ps(rr, rv);
            { uint8_t lf;
              if (plain & 1u) lf = ((sgn >> 0) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[0], (double)_mm_cvtss_f32(av) + (double)_mm_cvtss_f32(vsv) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[0] = vu1gen::normResult(rr[0], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[0][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 2u) lf = ((sgn >> 1) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[1], (double)_mm_cvtss_f32(_mm_shuffle_ps(av, av, _MM_SHUFFLE(1, 1, 1, 1))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(1, 1, 1, 1))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[1] = vu1gen::normResult(rr[1], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[1][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 4u) lf = ((sgn >> 2) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[2], (double)_mm_cvtss_f32(_mm_shuffle_ps(av, av, _MM_SHUFFLE(2, 2, 2, 2))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(2, 2, 2, 2))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[2] = vu1gen::normResult(rr[2], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[2][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 8u) lf = ((sgn >> 3) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[3], (double)_mm_cvtss_f32(_mm_shuffle_ps(av, av, _MM_SHUFFLE(3, 3, 3, 3))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(3, 3, 3, 3))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[3] = vu1gen::normResult(rr[3], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[3][lf & 0xFu]; stf |= lf & 0xFu; }
            rvn = _mm_loadu_ps(rr);
          } }
        if (cx.sticky) stk = vu1gen::sticky4(vsv, bv, product, 0xFu);
        cx.pushFmac(c, mac, stf, stk);
        vu1gen::storeLanes(st.acc, rvn, 0xFu);
      }
      bvReg = -1;
      c += 1u;
    }
    LC00F0:;
    L00F0:;
    { // pair 30 pc=0xF0 up=0x01FEB8BE lo=0x8000033C
      c = vu1gen::vmax(c, cx.vfRAny[23]);
      c = vu1gen::vmax(c, cx.vfR[30][2]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[23]);
        const __m128 bv = vu1gen::nrmbc(st.vf[30], 2);
        const __m128 av = vu1gen::nrm4(st.acc);
        const __m128 product = _mm_mul_ps(vsv, bv);
        const __m128 rv = _mm_add_ps(av, product);
        uint32_t mac = 0u, stf = 0u, stk = 0u;
        __m128 rvn = rv;
        { uint32_t sgn; uint32_t plain = vu1gen::classify4(rv, sgn);
          const __m128i pm = _mm_and_si128(_mm_castps_si128(product), _mm_set1_epi32(0x7FFFFFFF));
          plain &= ~uint32_t(_mm_movemask_ps(_mm_castsi128_ps(_mm_cmpgt_epi32(pm, _mm_set1_epi32(0x7F7FFFFE)))));
          if ((plain & 0xFu) == 0xFu) {
            mac = vu1gen::kMacSign.word[sgn & 0xFu];
            stf = (sgn & 0xFu) != 0u ? 0x2u : 0u;
          } else {
            float rr[4]; _mm_storeu_ps(rr, rv);
            { uint8_t lf;
              if (plain & 1u) lf = ((sgn >> 0) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[0], (double)_mm_cvtss_f32(av) + (double)_mm_cvtss_f32(vsv) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[0] = vu1gen::normResult(rr[0], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[0][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 2u) lf = ((sgn >> 1) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[1], (double)_mm_cvtss_f32(_mm_shuffle_ps(av, av, _MM_SHUFFLE(1, 1, 1, 1))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(1, 1, 1, 1))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[1] = vu1gen::normResult(rr[1], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[1][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 4u) lf = ((sgn >> 2) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[2], (double)_mm_cvtss_f32(_mm_shuffle_ps(av, av, _MM_SHUFFLE(2, 2, 2, 2))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(2, 2, 2, 2))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[2] = vu1gen::normResult(rr[2], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[2][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 8u) lf = ((sgn >> 3) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[3], (double)_mm_cvtss_f32(_mm_shuffle_ps(av, av, _MM_SHUFFLE(3, 3, 3, 3))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(3, 3, 3, 3))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[3] = vu1gen::normResult(rr[3], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[3][lf & 0xFu]; stf |= lf & 0xFu; }
            rvn = _mm_loadu_ps(rr);
          } }
        if (cx.sticky) stk = vu1gen::sticky4(vsv, bv, product, 0xFu);
        cx.pushFmac(c, mac, stf, stk);
        vu1gen::storeLanes(st.acc, rvn, 0xFu);
      }
      bvReg = -1;
      c += 1u;
    }
    L00F8:;
    { // pair 31 pc=0xF8 up=0x01FEC2CB lo=0x8000033C
      c = vu1gen::vmax(c, cx.vfRAny[24]);
      c = vu1gen::vmax(c, cx.vfR[30][3]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[24]);
        const __m128 bv = vu1gen::nrmbc(st.vf[30], 3);
        const __m128 av = vu1gen::nrm4(st.acc);
        const __m128 product = _mm_mul_ps(vsv, bv);
        const __m128 rv = _mm_add_ps(av, product);
        uint32_t mac = 0u, stf = 0u, stk = 0u;
        __m128 rvn = rv;
        { uint32_t sgn; uint32_t plain = vu1gen::classify4(rv, sgn);
          const __m128i pm = _mm_and_si128(_mm_castps_si128(product), _mm_set1_epi32(0x7FFFFFFF));
          plain &= ~uint32_t(_mm_movemask_ps(_mm_castsi128_ps(_mm_cmpgt_epi32(pm, _mm_set1_epi32(0x7F7FFFFE)))));
          if ((plain & 0xFu) == 0xFu) {
            mac = vu1gen::kMacSign.word[sgn & 0xFu];
            stf = (sgn & 0xFu) != 0u ? 0x2u : 0u;
          } else {
            float rr[4]; _mm_storeu_ps(rr, rv);
            { uint8_t lf;
              if (plain & 1u) lf = ((sgn >> 0) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[0], (double)_mm_cvtss_f32(av) + (double)_mm_cvtss_f32(vsv) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[0] = vu1gen::normResult(rr[0], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[0][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 2u) lf = ((sgn >> 1) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[1], (double)_mm_cvtss_f32(_mm_shuffle_ps(av, av, _MM_SHUFFLE(1, 1, 1, 1))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(1, 1, 1, 1))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[1] = vu1gen::normResult(rr[1], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[1][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 4u) lf = ((sgn >> 2) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[2], (double)_mm_cvtss_f32(_mm_shuffle_ps(av, av, _MM_SHUFFLE(2, 2, 2, 2))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(2, 2, 2, 2))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[2] = vu1gen::normResult(rr[2], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[2][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 8u) lf = ((sgn >> 3) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[3], (double)_mm_cvtss_f32(_mm_shuffle_ps(av, av, _MM_SHUFFLE(3, 3, 3, 3))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(3, 3, 3, 3))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[3] = vu1gen::normResult(rr[3], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[3][lf & 0xFu]; stf |= lf & 0xFu; }
            rvn = _mm_loadu_ps(rr);
          } }
        if (cx.sticky) stk = vu1gen::sticky4(vsv, bv, product, 0xFu);
        cx.pushFmac(c, mac, stf, stk);
        urv = rvn;
      }
      bvReg = -1;
      vu1gen::storeLanes(st.vf[11], urv, 0xFu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[11] = rt;
        _mm_store_si128((__m128i *)cx.vfR[11], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L0100:;
    { // pair 32 pc=0x100 up=0x01FFA9BC lo=0x8000033C
      c = vu1gen::vmax(c, cx.vfRAny[21]);
      c = vu1gen::vmax(c, cx.vfR[31][0]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[21]);
        const __m128 bv = vu1gen::nrmbc(st.vf[31], 0);
        const __m128 rv = _mm_mul_ps(vsv, bv);
        uint32_t mac = 0u, stf = 0u, stk = 0u;
        __m128 rvn = rv;
        { uint32_t sgn; uint32_t plain = vu1gen::classify4(rv, sgn);
          if ((plain & 0xFu) == 0xFu) {
            mac = vu1gen::kMacSign.word[sgn & 0xFu];
            stf = (sgn & 0xFu) != 0u ? 0x2u : 0u;
          } else {
            float rr[4]; _mm_storeu_ps(rr, rv);
            { uint8_t lf;
              if (plain & 1u) lf = ((sgn >> 0) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[0], (double)_mm_cvtss_f32(vsv) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[0] = vu1gen::normResult(rr[0], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[0][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 2u) lf = ((sgn >> 1) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[1], (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(1, 1, 1, 1))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[1] = vu1gen::normResult(rr[1], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[1][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 4u) lf = ((sgn >> 2) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[2], (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(2, 2, 2, 2))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[2] = vu1gen::normResult(rr[2], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[2][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 8u) lf = ((sgn >> 3) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[3], (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(3, 3, 3, 3))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[3] = vu1gen::normResult(rr[3], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[3][lf & 0xFu]; stf |= lf & 0xFu; }
            rvn = _mm_loadu_ps(rr);
          } }
        cx.pushFmac(c, mac, stf, stk);
        vu1gen::storeLanes(st.acc, rvn, 0xFu);
      }
      bvReg = -1;
      c += 1u;
    }
    L0108:;
    { // pair 33 pc=0x108 up=0x01FFB0BD lo=0x8000033C
      c = vu1gen::vmax(c, cx.vfRAny[22]);
      c = vu1gen::vmax(c, cx.vfR[31][1]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[22]);
        const __m128 bv = vu1gen::nrmbc(st.vf[31], 1);
        const __m128 av = vu1gen::nrm4(st.acc);
        const __m128 product = _mm_mul_ps(vsv, bv);
        const __m128 rv = _mm_add_ps(av, product);
        uint32_t mac = 0u, stf = 0u, stk = 0u;
        __m128 rvn = rv;
        { uint32_t sgn; uint32_t plain = vu1gen::classify4(rv, sgn);
          const __m128i pm = _mm_and_si128(_mm_castps_si128(product), _mm_set1_epi32(0x7FFFFFFF));
          plain &= ~uint32_t(_mm_movemask_ps(_mm_castsi128_ps(_mm_cmpgt_epi32(pm, _mm_set1_epi32(0x7F7FFFFE)))));
          if ((plain & 0xFu) == 0xFu) {
            mac = vu1gen::kMacSign.word[sgn & 0xFu];
            stf = (sgn & 0xFu) != 0u ? 0x2u : 0u;
          } else {
            float rr[4]; _mm_storeu_ps(rr, rv);
            { uint8_t lf;
              if (plain & 1u) lf = ((sgn >> 0) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[0], (double)_mm_cvtss_f32(av) + (double)_mm_cvtss_f32(vsv) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[0] = vu1gen::normResult(rr[0], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[0][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 2u) lf = ((sgn >> 1) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[1], (double)_mm_cvtss_f32(_mm_shuffle_ps(av, av, _MM_SHUFFLE(1, 1, 1, 1))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(1, 1, 1, 1))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[1] = vu1gen::normResult(rr[1], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[1][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 4u) lf = ((sgn >> 2) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[2], (double)_mm_cvtss_f32(_mm_shuffle_ps(av, av, _MM_SHUFFLE(2, 2, 2, 2))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(2, 2, 2, 2))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[2] = vu1gen::normResult(rr[2], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[2][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 8u) lf = ((sgn >> 3) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[3], (double)_mm_cvtss_f32(_mm_shuffle_ps(av, av, _MM_SHUFFLE(3, 3, 3, 3))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(3, 3, 3, 3))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[3] = vu1gen::normResult(rr[3], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[3][lf & 0xFu]; stf |= lf & 0xFu; }
            rvn = _mm_loadu_ps(rr);
          } }
        if (cx.sticky) stk = vu1gen::sticky4(vsv, bv, product, 0xFu);
        cx.pushFmac(c, mac, stf, stk);
        vu1gen::storeLanes(st.acc, rvn, 0xFu);
      }
      bvReg = -1;
      c += 1u;
    }
    L0110:;
    { // pair 34 pc=0x110 up=0x01FFB8CA lo=0x8000033C
      c = vu1gen::vmax(c, cx.vfRAny[23]);
      c = vu1gen::vmax(c, cx.vfR[31][2]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[23]);
        const __m128 bv = vu1gen::nrmbc(st.vf[31], 2);
        const __m128 av = vu1gen::nrm4(st.acc);
        const __m128 product = _mm_mul_ps(vsv, bv);
        const __m128 rv = _mm_add_ps(av, product);
        uint32_t mac = 0u, stf = 0u, stk = 0u;
        __m128 rvn = rv;
        { uint32_t sgn; uint32_t plain = vu1gen::classify4(rv, sgn);
          const __m128i pm = _mm_and_si128(_mm_castps_si128(product), _mm_set1_epi32(0x7FFFFFFF));
          plain &= ~uint32_t(_mm_movemask_ps(_mm_castsi128_ps(_mm_cmpgt_epi32(pm, _mm_set1_epi32(0x7F7FFFFE)))));
          if ((plain & 0xFu) == 0xFu) {
            mac = vu1gen::kMacSign.word[sgn & 0xFu];
            stf = (sgn & 0xFu) != 0u ? 0x2u : 0u;
          } else {
            float rr[4]; _mm_storeu_ps(rr, rv);
            { uint8_t lf;
              if (plain & 1u) lf = ((sgn >> 0) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[0], (double)_mm_cvtss_f32(av) + (double)_mm_cvtss_f32(vsv) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[0] = vu1gen::normResult(rr[0], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[0][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 2u) lf = ((sgn >> 1) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[1], (double)_mm_cvtss_f32(_mm_shuffle_ps(av, av, _MM_SHUFFLE(1, 1, 1, 1))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(1, 1, 1, 1))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[1] = vu1gen::normResult(rr[1], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[1][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 4u) lf = ((sgn >> 2) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[2], (double)_mm_cvtss_f32(_mm_shuffle_ps(av, av, _MM_SHUFFLE(2, 2, 2, 2))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(2, 2, 2, 2))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[2] = vu1gen::normResult(rr[2], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[2][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 8u) lf = ((sgn >> 3) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[3], (double)_mm_cvtss_f32(_mm_shuffle_ps(av, av, _MM_SHUFFLE(3, 3, 3, 3))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(3, 3, 3, 3))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[3] = vu1gen::normResult(rr[3], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[3][lf & 0xFu]; stf |= lf & 0xFu; }
            rvn = _mm_loadu_ps(rr);
          } }
        if (cx.sticky) stk = vu1gen::sticky4(vsv, bv, product, 0xFu);
        cx.pushFmac(c, mac, stf, stk);
        urv = rvn;
      }
      bvReg = -1;
      vu1gen::storeLanes(st.vf[3], urv, 0xFu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[3] = rt;
        _mm_store_si128((__m128i *)cx.vfR[3], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L0118:;
    { const bool bt = (int16_t)(bvReg == 15 ? bvOld : st.vi[15]) <= 0;
    { // pair 35 pc=0x118 up=0x01FEC9BC lo=0x5C007806
      c = vu1gen::vmax(c, cx.vfRAny[25]);
      c = vu1gen::vmax(c, cx.vfR[30][0]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[25]);
        const __m128 bv = vu1gen::nrmbc(st.vf[30], 0);
        const __m128 rv = _mm_mul_ps(vsv, bv);
        uint32_t mac = 0u, stf = 0u, stk = 0u;
        __m128 rvn = rv;
        { uint32_t sgn; uint32_t plain = vu1gen::classify4(rv, sgn);
          if ((plain & 0xFu) == 0xFu) {
            mac = vu1gen::kMacSign.word[sgn & 0xFu];
            stf = (sgn & 0xFu) != 0u ? 0x2u : 0u;
          } else {
            float rr[4]; _mm_storeu_ps(rr, rv);
            { uint8_t lf;
              if (plain & 1u) lf = ((sgn >> 0) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[0], (double)_mm_cvtss_f32(vsv) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[0] = vu1gen::normResult(rr[0], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[0][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 2u) lf = ((sgn >> 1) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[1], (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(1, 1, 1, 1))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[1] = vu1gen::normResult(rr[1], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[1][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 4u) lf = ((sgn >> 2) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[2], (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(2, 2, 2, 2))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[2] = vu1gen::normResult(rr[2], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[2][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 8u) lf = ((sgn >> 3) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[3], (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(3, 3, 3, 3))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[3] = vu1gen::normResult(rr[3], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[3][lf & 0xFu]; stf |= lf & 0xFu; }
            rvn = _mm_loadu_ps(rr);
          } }
        cx.pushFmac(c, mac, stf, stk);
        vu1gen::storeLanes(st.acc, rvn, 0xFu);
      }
      bvReg = -1;
      c += 1u;
    }
    { // pair 36 pc=0x120 up=0x01FED0BD lo=0x8000033C
      c = vu1gen::vmax(c, cx.vfRAny[26]);
      c = vu1gen::vmax(c, cx.vfR[30][1]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[26]);
        const __m128 bv = vu1gen::nrmbc(st.vf[30], 1);
        const __m128 av = vu1gen::nrm4(st.acc);
        const __m128 product = _mm_mul_ps(vsv, bv);
        const __m128 rv = _mm_add_ps(av, product);
        uint32_t mac = 0u, stf = 0u, stk = 0u;
        __m128 rvn = rv;
        { uint32_t sgn; uint32_t plain = vu1gen::classify4(rv, sgn);
          const __m128i pm = _mm_and_si128(_mm_castps_si128(product), _mm_set1_epi32(0x7FFFFFFF));
          plain &= ~uint32_t(_mm_movemask_ps(_mm_castsi128_ps(_mm_cmpgt_epi32(pm, _mm_set1_epi32(0x7F7FFFFE)))));
          if ((plain & 0xFu) == 0xFu) {
            mac = vu1gen::kMacSign.word[sgn & 0xFu];
            stf = (sgn & 0xFu) != 0u ? 0x2u : 0u;
          } else {
            float rr[4]; _mm_storeu_ps(rr, rv);
            { uint8_t lf;
              if (plain & 1u) lf = ((sgn >> 0) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[0], (double)_mm_cvtss_f32(av) + (double)_mm_cvtss_f32(vsv) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[0] = vu1gen::normResult(rr[0], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[0][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 2u) lf = ((sgn >> 1) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[1], (double)_mm_cvtss_f32(_mm_shuffle_ps(av, av, _MM_SHUFFLE(1, 1, 1, 1))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(1, 1, 1, 1))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[1] = vu1gen::normResult(rr[1], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[1][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 4u) lf = ((sgn >> 2) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[2], (double)_mm_cvtss_f32(_mm_shuffle_ps(av, av, _MM_SHUFFLE(2, 2, 2, 2))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(2, 2, 2, 2))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[2] = vu1gen::normResult(rr[2], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[2][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 8u) lf = ((sgn >> 3) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[3], (double)_mm_cvtss_f32(_mm_shuffle_ps(av, av, _MM_SHUFFLE(3, 3, 3, 3))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(3, 3, 3, 3))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[3] = vu1gen::normResult(rr[3], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[3][lf & 0xFu]; stf |= lf & 0xFu; }
            rvn = _mm_loadu_ps(rr);
          } }
        if (cx.sticky) stk = vu1gen::sticky4(vsv, bv, product, 0xFu);
        cx.pushFmac(c, mac, stf, stk);
        vu1gen::storeLanes(st.acc, rvn, 0xFu);
      }
      bvReg = -1;
      c += 1u;
    }
    if (bt) {
      st.branchTarget = 0x150u;
      goto L0150;
    } }
    goto LC0128;
    L0120:;
    { // pair 36 pc=0x120 up=0x01FED0BD lo=0x8000033C
      c = vu1gen::vmax(c, cx.vfRAny[26]);
      c = vu1gen::vmax(c, cx.vfR[30][1]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[26]);
        const __m128 bv = vu1gen::nrmbc(st.vf[30], 1);
        const __m128 av = vu1gen::nrm4(st.acc);
        const __m128 product = _mm_mul_ps(vsv, bv);
        const __m128 rv = _mm_add_ps(av, product);
        uint32_t mac = 0u, stf = 0u, stk = 0u;
        __m128 rvn = rv;
        { uint32_t sgn; uint32_t plain = vu1gen::classify4(rv, sgn);
          const __m128i pm = _mm_and_si128(_mm_castps_si128(product), _mm_set1_epi32(0x7FFFFFFF));
          plain &= ~uint32_t(_mm_movemask_ps(_mm_castsi128_ps(_mm_cmpgt_epi32(pm, _mm_set1_epi32(0x7F7FFFFE)))));
          if ((plain & 0xFu) == 0xFu) {
            mac = vu1gen::kMacSign.word[sgn & 0xFu];
            stf = (sgn & 0xFu) != 0u ? 0x2u : 0u;
          } else {
            float rr[4]; _mm_storeu_ps(rr, rv);
            { uint8_t lf;
              if (plain & 1u) lf = ((sgn >> 0) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[0], (double)_mm_cvtss_f32(av) + (double)_mm_cvtss_f32(vsv) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[0] = vu1gen::normResult(rr[0], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[0][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 2u) lf = ((sgn >> 1) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[1], (double)_mm_cvtss_f32(_mm_shuffle_ps(av, av, _MM_SHUFFLE(1, 1, 1, 1))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(1, 1, 1, 1))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[1] = vu1gen::normResult(rr[1], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[1][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 4u) lf = ((sgn >> 2) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[2], (double)_mm_cvtss_f32(_mm_shuffle_ps(av, av, _MM_SHUFFLE(2, 2, 2, 2))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(2, 2, 2, 2))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[2] = vu1gen::normResult(rr[2], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[2][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 8u) lf = ((sgn >> 3) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[3], (double)_mm_cvtss_f32(_mm_shuffle_ps(av, av, _MM_SHUFFLE(3, 3, 3, 3))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(3, 3, 3, 3))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[3] = vu1gen::normResult(rr[3], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[3][lf & 0xFu]; stf |= lf & 0xFu; }
            rvn = _mm_loadu_ps(rr);
          } }
        if (cx.sticky) stk = vu1gen::sticky4(vsv, bv, product, 0xFu);
        cx.pushFmac(c, mac, stf, stk);
        vu1gen::storeLanes(st.acc, rvn, 0xFu);
      }
      bvReg = -1;
      c += 1u;
    }
    LC0128:;
    L0128:;
    { // pair 37 pc=0x128 up=0x01FED8BE lo=0x8000033C
      c = vu1gen::vmax(c, cx.vfRAny[27]);
      c = vu1gen::vmax(c, cx.vfR[30][2]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[27]);
        const __m128 bv = vu1gen::nrmbc(st.vf[30], 2);
        const __m128 av = vu1gen::nrm4(st.acc);
        const __m128 product = _mm_mul_ps(vsv, bv);
        const __m128 rv = _mm_add_ps(av, product);
        uint32_t mac = 0u, stf = 0u, stk = 0u;
        __m128 rvn = rv;
        { uint32_t sgn; uint32_t plain = vu1gen::classify4(rv, sgn);
          const __m128i pm = _mm_and_si128(_mm_castps_si128(product), _mm_set1_epi32(0x7FFFFFFF));
          plain &= ~uint32_t(_mm_movemask_ps(_mm_castsi128_ps(_mm_cmpgt_epi32(pm, _mm_set1_epi32(0x7F7FFFFE)))));
          if ((plain & 0xFu) == 0xFu) {
            mac = vu1gen::kMacSign.word[sgn & 0xFu];
            stf = (sgn & 0xFu) != 0u ? 0x2u : 0u;
          } else {
            float rr[4]; _mm_storeu_ps(rr, rv);
            { uint8_t lf;
              if (plain & 1u) lf = ((sgn >> 0) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[0], (double)_mm_cvtss_f32(av) + (double)_mm_cvtss_f32(vsv) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[0] = vu1gen::normResult(rr[0], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[0][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 2u) lf = ((sgn >> 1) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[1], (double)_mm_cvtss_f32(_mm_shuffle_ps(av, av, _MM_SHUFFLE(1, 1, 1, 1))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(1, 1, 1, 1))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[1] = vu1gen::normResult(rr[1], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[1][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 4u) lf = ((sgn >> 2) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[2], (double)_mm_cvtss_f32(_mm_shuffle_ps(av, av, _MM_SHUFFLE(2, 2, 2, 2))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(2, 2, 2, 2))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[2] = vu1gen::normResult(rr[2], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[2][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 8u) lf = ((sgn >> 3) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[3], (double)_mm_cvtss_f32(_mm_shuffle_ps(av, av, _MM_SHUFFLE(3, 3, 3, 3))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(3, 3, 3, 3))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[3] = vu1gen::normResult(rr[3], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[3][lf & 0xFu]; stf |= lf & 0xFu; }
            rvn = _mm_loadu_ps(rr);
          } }
        if (cx.sticky) stk = vu1gen::sticky4(vsv, bv, product, 0xFu);
        cx.pushFmac(c, mac, stf, stk);
        vu1gen::storeLanes(st.acc, rvn, 0xFu);
      }
      bvReg = -1;
      c += 1u;
    }
    L0130:;
    { // pair 38 pc=0x130 up=0x01FEE30B lo=0x8000033C
      c = vu1gen::vmax(c, cx.vfRAny[28]);
      c = vu1gen::vmax(c, cx.vfR[30][3]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[28]);
        const __m128 bv = vu1gen::nrmbc(st.vf[30], 3);
        const __m128 av = vu1gen::nrm4(st.acc);
        const __m128 product = _mm_mul_ps(vsv, bv);
        const __m128 rv = _mm_add_ps(av, product);
        uint32_t mac = 0u, stf = 0u, stk = 0u;
        __m128 rvn = rv;
        { uint32_t sgn; uint32_t plain = vu1gen::classify4(rv, sgn);
          const __m128i pm = _mm_and_si128(_mm_castps_si128(product), _mm_set1_epi32(0x7FFFFFFF));
          plain &= ~uint32_t(_mm_movemask_ps(_mm_castsi128_ps(_mm_cmpgt_epi32(pm, _mm_set1_epi32(0x7F7FFFFE)))));
          if ((plain & 0xFu) == 0xFu) {
            mac = vu1gen::kMacSign.word[sgn & 0xFu];
            stf = (sgn & 0xFu) != 0u ? 0x2u : 0u;
          } else {
            float rr[4]; _mm_storeu_ps(rr, rv);
            { uint8_t lf;
              if (plain & 1u) lf = ((sgn >> 0) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[0], (double)_mm_cvtss_f32(av) + (double)_mm_cvtss_f32(vsv) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[0] = vu1gen::normResult(rr[0], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[0][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 2u) lf = ((sgn >> 1) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[1], (double)_mm_cvtss_f32(_mm_shuffle_ps(av, av, _MM_SHUFFLE(1, 1, 1, 1))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(1, 1, 1, 1))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[1] = vu1gen::normResult(rr[1], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[1][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 4u) lf = ((sgn >> 2) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[2], (double)_mm_cvtss_f32(_mm_shuffle_ps(av, av, _MM_SHUFFLE(2, 2, 2, 2))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(2, 2, 2, 2))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[2] = vu1gen::normResult(rr[2], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[2][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 8u) lf = ((sgn >> 3) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[3], (double)_mm_cvtss_f32(_mm_shuffle_ps(av, av, _MM_SHUFFLE(3, 3, 3, 3))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(3, 3, 3, 3))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[3] = vu1gen::normResult(rr[3], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[3][lf & 0xFu]; stf |= lf & 0xFu; }
            rvn = _mm_loadu_ps(rr);
          } }
        if (cx.sticky) stk = vu1gen::sticky4(vsv, bv, product, 0xFu);
        cx.pushFmac(c, mac, stf, stk);
        urv = rvn;
      }
      bvReg = -1;
      vu1gen::storeLanes(st.vf[12], urv, 0xFu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[12] = rt;
        _mm_store_si128((__m128i *)cx.vfR[12], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L0138:;
    { // pair 39 pc=0x138 up=0x01FFC9BC lo=0x8000033C
      c = vu1gen::vmax(c, cx.vfRAny[25]);
      c = vu1gen::vmax(c, cx.vfR[31][0]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[25]);
        const __m128 bv = vu1gen::nrmbc(st.vf[31], 0);
        const __m128 rv = _mm_mul_ps(vsv, bv);
        uint32_t mac = 0u, stf = 0u, stk = 0u;
        __m128 rvn = rv;
        { uint32_t sgn; uint32_t plain = vu1gen::classify4(rv, sgn);
          if ((plain & 0xFu) == 0xFu) {
            mac = vu1gen::kMacSign.word[sgn & 0xFu];
            stf = (sgn & 0xFu) != 0u ? 0x2u : 0u;
          } else {
            float rr[4]; _mm_storeu_ps(rr, rv);
            { uint8_t lf;
              if (plain & 1u) lf = ((sgn >> 0) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[0], (double)_mm_cvtss_f32(vsv) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[0] = vu1gen::normResult(rr[0], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[0][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 2u) lf = ((sgn >> 1) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[1], (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(1, 1, 1, 1))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[1] = vu1gen::normResult(rr[1], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[1][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 4u) lf = ((sgn >> 2) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[2], (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(2, 2, 2, 2))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[2] = vu1gen::normResult(rr[2], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[2][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 8u) lf = ((sgn >> 3) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[3], (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(3, 3, 3, 3))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[3] = vu1gen::normResult(rr[3], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[3][lf & 0xFu]; stf |= lf & 0xFu; }
            rvn = _mm_loadu_ps(rr);
          } }
        cx.pushFmac(c, mac, stf, stk);
        vu1gen::storeLanes(st.acc, rvn, 0xFu);
      }
      bvReg = -1;
      c += 1u;
    }
    L0140:;
    { // pair 40 pc=0x140 up=0x01FFD0BD lo=0x8000033C
      c = vu1gen::vmax(c, cx.vfRAny[26]);
      c = vu1gen::vmax(c, cx.vfR[31][1]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[26]);
        const __m128 bv = vu1gen::nrmbc(st.vf[31], 1);
        const __m128 av = vu1gen::nrm4(st.acc);
        const __m128 product = _mm_mul_ps(vsv, bv);
        const __m128 rv = _mm_add_ps(av, product);
        uint32_t mac = 0u, stf = 0u, stk = 0u;
        __m128 rvn = rv;
        { uint32_t sgn; uint32_t plain = vu1gen::classify4(rv, sgn);
          const __m128i pm = _mm_and_si128(_mm_castps_si128(product), _mm_set1_epi32(0x7FFFFFFF));
          plain &= ~uint32_t(_mm_movemask_ps(_mm_castsi128_ps(_mm_cmpgt_epi32(pm, _mm_set1_epi32(0x7F7FFFFE)))));
          if ((plain & 0xFu) == 0xFu) {
            mac = vu1gen::kMacSign.word[sgn & 0xFu];
            stf = (sgn & 0xFu) != 0u ? 0x2u : 0u;
          } else {
            float rr[4]; _mm_storeu_ps(rr, rv);
            { uint8_t lf;
              if (plain & 1u) lf = ((sgn >> 0) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[0], (double)_mm_cvtss_f32(av) + (double)_mm_cvtss_f32(vsv) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[0] = vu1gen::normResult(rr[0], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[0][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 2u) lf = ((sgn >> 1) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[1], (double)_mm_cvtss_f32(_mm_shuffle_ps(av, av, _MM_SHUFFLE(1, 1, 1, 1))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(1, 1, 1, 1))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[1] = vu1gen::normResult(rr[1], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[1][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 4u) lf = ((sgn >> 2) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[2], (double)_mm_cvtss_f32(_mm_shuffle_ps(av, av, _MM_SHUFFLE(2, 2, 2, 2))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(2, 2, 2, 2))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[2] = vu1gen::normResult(rr[2], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[2][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 8u) lf = ((sgn >> 3) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[3], (double)_mm_cvtss_f32(_mm_shuffle_ps(av, av, _MM_SHUFFLE(3, 3, 3, 3))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(3, 3, 3, 3))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[3] = vu1gen::normResult(rr[3], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[3][lf & 0xFu]; stf |= lf & 0xFu; }
            rvn = _mm_loadu_ps(rr);
          } }
        if (cx.sticky) stk = vu1gen::sticky4(vsv, bv, product, 0xFu);
        cx.pushFmac(c, mac, stf, stk);
        vu1gen::storeLanes(st.acc, rvn, 0xFu);
      }
      bvReg = -1;
      c += 1u;
    }
    L0148:;
    { // pair 41 pc=0x148 up=0x01FFD90A lo=0x8000033C
      c = vu1gen::vmax(c, cx.vfRAny[27]);
      c = vu1gen::vmax(c, cx.vfR[31][2]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[27]);
        const __m128 bv = vu1gen::nrmbc(st.vf[31], 2);
        const __m128 av = vu1gen::nrm4(st.acc);
        const __m128 product = _mm_mul_ps(vsv, bv);
        const __m128 rv = _mm_add_ps(av, product);
        uint32_t mac = 0u, stf = 0u, stk = 0u;
        __m128 rvn = rv;
        { uint32_t sgn; uint32_t plain = vu1gen::classify4(rv, sgn);
          const __m128i pm = _mm_and_si128(_mm_castps_si128(product), _mm_set1_epi32(0x7FFFFFFF));
          plain &= ~uint32_t(_mm_movemask_ps(_mm_castsi128_ps(_mm_cmpgt_epi32(pm, _mm_set1_epi32(0x7F7FFFFE)))));
          if ((plain & 0xFu) == 0xFu) {
            mac = vu1gen::kMacSign.word[sgn & 0xFu];
            stf = (sgn & 0xFu) != 0u ? 0x2u : 0u;
          } else {
            float rr[4]; _mm_storeu_ps(rr, rv);
            { uint8_t lf;
              if (plain & 1u) lf = ((sgn >> 0) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[0], (double)_mm_cvtss_f32(av) + (double)_mm_cvtss_f32(vsv) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[0] = vu1gen::normResult(rr[0], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[0][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 2u) lf = ((sgn >> 1) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[1], (double)_mm_cvtss_f32(_mm_shuffle_ps(av, av, _MM_SHUFFLE(1, 1, 1, 1))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(1, 1, 1, 1))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[1] = vu1gen::normResult(rr[1], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[1][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 4u) lf = ((sgn >> 2) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[2], (double)_mm_cvtss_f32(_mm_shuffle_ps(av, av, _MM_SHUFFLE(2, 2, 2, 2))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(2, 2, 2, 2))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[2] = vu1gen::normResult(rr[2], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[2][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 8u) lf = ((sgn >> 3) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[3], (double)_mm_cvtss_f32(_mm_shuffle_ps(av, av, _MM_SHUFFLE(3, 3, 3, 3))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(3, 3, 3, 3))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[3] = vu1gen::normResult(rr[3], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[3][lf & 0xFu]; stf |= lf & 0xFu; }
            rvn = _mm_loadu_ps(rr);
          } }
        if (cx.sticky) stk = vu1gen::sticky4(vsv, bv, product, 0xFu);
        cx.pushFmac(c, mac, stf, stk);
        urv = rvn;
      }
      bvReg = -1;
      vu1gen::storeLanes(st.vf[4], urv, 0xFu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[4] = rt;
        _mm_store_si128((__m128i *)cx.vfR[4], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L0150:;
    { // pair 42 pc=0x150 up=0x01DFFA2A lo=0x8000033C
      c = vu1gen::vmax(c, cx.vfR[31][0]);
      c = vu1gen::vmax(c, cx.vfR[31][1]);
      c = vu1gen::vmax(c, cx.vfR[31][2]);
      c = vu1gen::vmax(c, cx.vfR[31][0]);
      c = vu1gen::vmax(c, cx.vfR[31][1]);
      c = vu1gen::vmax(c, cx.vfR[31][2]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[31]);
        const __m128 bv = vu1gen::nrm4(st.vf[31]);
        const __m128 rv = _mm_mul_ps(vsv, bv);
        uint32_t mac = 0u, stf = 0u, stk = 0u;
        __m128 rvn = rv;
        { uint32_t sgn; uint32_t plain = vu1gen::classify4(rv, sgn);
          if ((plain & 0x7u) == 0x7u) {
            mac = vu1gen::kMacSign.word[sgn & 0x7u];
            stf = (sgn & 0x7u) != 0u ? 0x2u : 0u;
          } else {
            float rr[4]; _mm_storeu_ps(rr, rv);
            { uint8_t lf;
              if (plain & 1u) lf = ((sgn >> 0) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[0], (double)_mm_cvtss_f32(vsv) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[0] = vu1gen::normResult(rr[0], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[0][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 2u) lf = ((sgn >> 1) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[1], (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(1, 1, 1, 1))) * (double)_mm_cvtss_f32(_mm_shuffle_ps(bv, bv, _MM_SHUFFLE(1, 1, 1, 1))));
              } else {
                uint32_t nf; rr[1] = vu1gen::normResult(rr[1], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[1][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 4u) lf = ((sgn >> 2) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[2], (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(2, 2, 2, 2))) * (double)_mm_cvtss_f32(_mm_shuffle_ps(bv, bv, _MM_SHUFFLE(2, 2, 2, 2))));
              } else {
                uint32_t nf; rr[2] = vu1gen::normResult(rr[2], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[2][lf & 0xFu]; stf |= lf & 0xFu; }
            rvn = _mm_loadu_ps(rr);
          } }
        cx.pushFmac(c, mac, stf, stk);
        urv = rvn;
      }
      bvReg = -1;
      vu1gen::storeLanes(st.vf[8], urv, 0xEu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[8] = rt;
        cx.vfR[8][0] = rt;
        cx.vfR[8][1] = rt;
        cx.vfR[8][2] = rt;
      }
      c += 1u;
    }
    L0158:;
    { // pair 43 pc=0x158 up=0x01DD09BC lo=0x01E50004
      c = vu1gen::vmax(c, cx.vfR[1][0]);
      c = vu1gen::vmax(c, cx.vfR[1][1]);
      c = vu1gen::vmax(c, cx.vfR[1][2]);
      c = vu1gen::vmax(c, cx.vfR[29][0]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[1]);
        const __m128 bv = vu1gen::nrmbc(st.vf[29], 0);
        const __m128 rv = _mm_mul_ps(vsv, bv);
        uint32_t mac = 0u, stf = 0u, stk = 0u;
        __m128 rvn = rv;
        { uint32_t sgn; uint32_t plain = vu1gen::classify4(rv, sgn);
          if ((plain & 0x7u) == 0x7u) {
            mac = vu1gen::kMacSign.word[sgn & 0x7u];
            stf = (sgn & 0x7u) != 0u ? 0x2u : 0u;
          } else {
            float rr[4]; _mm_storeu_ps(rr, rv);
            { uint8_t lf;
              if (plain & 1u) lf = ((sgn >> 0) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[0], (double)_mm_cvtss_f32(vsv) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[0] = vu1gen::normResult(rr[0], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[0][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 2u) lf = ((sgn >> 1) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[1], (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(1, 1, 1, 1))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[1] = vu1gen::normResult(rr[1], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[1][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 4u) lf = ((sgn >> 2) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[2], (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(2, 2, 2, 2))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[2] = vu1gen::normResult(rr[2], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[2][lf & 0xFu]; stf |= lf & 0xFu; }
            rvn = _mm_loadu_ps(rr);
          } }
        cx.pushFmac(c, mac, stf, stk);
        vu1gen::storeLanes(st.acc, rvn, 0xEu);
      }
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 4) * 16u) & 0xFFFu;
          std::memcpy(&st.vf[5][0], vm + addr + 0u, 16);
        }
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[5] = rt;
        _mm_store_si128((__m128i *)cx.vfR[5], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L0160:;
    { // pair 44 pc=0x160 up=0x01DD10BD lo=0x01E60005
      c = vu1gen::vmax(c, cx.vfR[2][0]);
      c = vu1gen::vmax(c, cx.vfR[2][1]);
      c = vu1gen::vmax(c, cx.vfR[2][2]);
      c = vu1gen::vmax(c, cx.vfR[29][1]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[2]);
        const __m128 bv = vu1gen::nrmbc(st.vf[29], 1);
        const __m128 av = vu1gen::nrm4(st.acc);
        const __m128 product = _mm_mul_ps(vsv, bv);
        const __m128 rv = _mm_add_ps(av, product);
        uint32_t mac = 0u, stf = 0u, stk = 0u;
        __m128 rvn = rv;
        { uint32_t sgn; uint32_t plain = vu1gen::classify4(rv, sgn);
          const __m128i pm = _mm_and_si128(_mm_castps_si128(product), _mm_set1_epi32(0x7FFFFFFF));
          plain &= ~uint32_t(_mm_movemask_ps(_mm_castsi128_ps(_mm_cmpgt_epi32(pm, _mm_set1_epi32(0x7F7FFFFE)))));
          if ((plain & 0x7u) == 0x7u) {
            mac = vu1gen::kMacSign.word[sgn & 0x7u];
            stf = (sgn & 0x7u) != 0u ? 0x2u : 0u;
          } else {
            float rr[4]; _mm_storeu_ps(rr, rv);
            { uint8_t lf;
              if (plain & 1u) lf = ((sgn >> 0) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[0], (double)_mm_cvtss_f32(av) + (double)_mm_cvtss_f32(vsv) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[0] = vu1gen::normResult(rr[0], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[0][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 2u) lf = ((sgn >> 1) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[1], (double)_mm_cvtss_f32(_mm_shuffle_ps(av, av, _MM_SHUFFLE(1, 1, 1, 1))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(1, 1, 1, 1))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[1] = vu1gen::normResult(rr[1], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[1][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 4u) lf = ((sgn >> 2) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[2], (double)_mm_cvtss_f32(_mm_shuffle_ps(av, av, _MM_SHUFFLE(2, 2, 2, 2))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(2, 2, 2, 2))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[2] = vu1gen::normResult(rr[2], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[2][lf & 0xFu]; stf |= lf & 0xFu; }
            rvn = _mm_loadu_ps(rr);
          } }
        if (cx.sticky) stk = vu1gen::sticky4(vsv, bv, product, 0x7u);
        cx.pushFmac(c, mac, stf, stk);
        vu1gen::storeLanes(st.acc, rvn, 0xEu);
      }
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 5) * 16u) & 0xFFFu;
          std::memcpy(&st.vf[6][0], vm + addr + 0u, 16);
        }
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[6] = rt;
        _mm_store_si128((__m128i *)cx.vfR[6], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L0168:;
    { // pair 45 pc=0x168 up=0x01DD18BE lo=0x8000033C
      c = vu1gen::vmax(c, cx.vfR[3][0]);
      c = vu1gen::vmax(c, cx.vfR[3][1]);
      c = vu1gen::vmax(c, cx.vfR[3][2]);
      c = vu1gen::vmax(c, cx.vfR[29][2]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[3]);
        const __m128 bv = vu1gen::nrmbc(st.vf[29], 2);
        const __m128 av = vu1gen::nrm4(st.acc);
        const __m128 product = _mm_mul_ps(vsv, bv);
        const __m128 rv = _mm_add_ps(av, product);
        uint32_t mac = 0u, stf = 0u, stk = 0u;
        __m128 rvn = rv;
        { uint32_t sgn; uint32_t plain = vu1gen::classify4(rv, sgn);
          const __m128i pm = _mm_and_si128(_mm_castps_si128(product), _mm_set1_epi32(0x7FFFFFFF));
          plain &= ~uint32_t(_mm_movemask_ps(_mm_castsi128_ps(_mm_cmpgt_epi32(pm, _mm_set1_epi32(0x7F7FFFFE)))));
          if ((plain & 0x7u) == 0x7u) {
            mac = vu1gen::kMacSign.word[sgn & 0x7u];
            stf = (sgn & 0x7u) != 0u ? 0x2u : 0u;
          } else {
            float rr[4]; _mm_storeu_ps(rr, rv);
            { uint8_t lf;
              if (plain & 1u) lf = ((sgn >> 0) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[0], (double)_mm_cvtss_f32(av) + (double)_mm_cvtss_f32(vsv) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[0] = vu1gen::normResult(rr[0], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[0][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 2u) lf = ((sgn >> 1) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[1], (double)_mm_cvtss_f32(_mm_shuffle_ps(av, av, _MM_SHUFFLE(1, 1, 1, 1))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(1, 1, 1, 1))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[1] = vu1gen::normResult(rr[1], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[1][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 4u) lf = ((sgn >> 2) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[2], (double)_mm_cvtss_f32(_mm_shuffle_ps(av, av, _MM_SHUFFLE(2, 2, 2, 2))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(2, 2, 2, 2))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[2] = vu1gen::normResult(rr[2], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[2][lf & 0xFu]; stf |= lf & 0xFu; }
            rvn = _mm_loadu_ps(rr);
          } }
        if (cx.sticky) stk = vu1gen::sticky4(vsv, bv, product, 0x7u);
        cx.pushFmac(c, mac, stf, stk);
        vu1gen::storeLanes(st.acc, rvn, 0xEu);
      }
      bvReg = -1;
      c += 1u;
    }
    L0170:;
    { // pair 46 pc=0x170 up=0x01DD27CB lo=0x8000033C
      c = vu1gen::vmax(c, cx.vfR[4][0]);
      c = vu1gen::vmax(c, cx.vfR[4][1]);
      c = vu1gen::vmax(c, cx.vfR[4][2]);
      c = vu1gen::vmax(c, cx.vfR[29][3]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[4]);
        const __m128 bv = vu1gen::nrmbc(st.vf[29], 3);
        const __m128 av = vu1gen::nrm4(st.acc);
        const __m128 product = _mm_mul_ps(vsv, bv);
        const __m128 rv = _mm_add_ps(av, product);
        uint32_t mac = 0u, stf = 0u, stk = 0u;
        __m128 rvn = rv;
        { uint32_t sgn; uint32_t plain = vu1gen::classify4(rv, sgn);
          const __m128i pm = _mm_and_si128(_mm_castps_si128(product), _mm_set1_epi32(0x7FFFFFFF));
          plain &= ~uint32_t(_mm_movemask_ps(_mm_castsi128_ps(_mm_cmpgt_epi32(pm, _mm_set1_epi32(0x7F7FFFFE)))));
          if ((plain & 0x7u) == 0x7u) {
            mac = vu1gen::kMacSign.word[sgn & 0x7u];
            stf = (sgn & 0x7u) != 0u ? 0x2u : 0u;
          } else {
            float rr[4]; _mm_storeu_ps(rr, rv);
            { uint8_t lf;
              if (plain & 1u) lf = ((sgn >> 0) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[0], (double)_mm_cvtss_f32(av) + (double)_mm_cvtss_f32(vsv) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[0] = vu1gen::normResult(rr[0], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[0][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 2u) lf = ((sgn >> 1) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[1], (double)_mm_cvtss_f32(_mm_shuffle_ps(av, av, _MM_SHUFFLE(1, 1, 1, 1))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(1, 1, 1, 1))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[1] = vu1gen::normResult(rr[1], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[1][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 4u) lf = ((sgn >> 2) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[2], (double)_mm_cvtss_f32(_mm_shuffle_ps(av, av, _MM_SHUFFLE(2, 2, 2, 2))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(2, 2, 2, 2))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[2] = vu1gen::normResult(rr[2], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[2][lf & 0xFu]; stf |= lf & 0xFu; }
            rvn = _mm_loadu_ps(rr);
          } }
        if (cx.sticky) stk = vu1gen::sticky4(vsv, bv, product, 0x7u);
        cx.pushFmac(c, mac, stf, stk);
        urv = rvn;
      }
      bvReg = -1;
      vu1gen::storeLanes(st.vf[31], urv, 0xEu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[31] = rt;
        cx.vfR[31][0] = rt;
        cx.vfR[31][1] = rt;
        cx.vfR[31][2] = rt;
      }
      c += 1u;
    }
    L0178:;
    { // pair 47 pc=0x178 up=0x0108403E lo=0x8000033C
      c = vu1gen::vmax(c, cx.vfR[8][0]);
      c = vu1gen::vmax(c, cx.vfR[8][2]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[8]);
        const __m128 bv = vu1gen::nrmbc(st.vf[8], 2);
        const __m128 rv = _mm_add_ps(vsv, bv);
        uint32_t mac = 0u, stf = 0u, stk = 0u;
        __m128 rvn = rv;
        { uint32_t sgn; uint32_t plain = vu1gen::classify4(rv, sgn);
          if ((plain & 0x1u) == 0x1u) {
            mac = vu1gen::kMacSign.word[sgn & 0x1u];
            stf = (sgn & 0x1u) != 0u ? 0x2u : 0u;
          } else {
            float rr[4]; _mm_storeu_ps(rr, rv);
            { uint8_t lf;
              if (plain & 1u) lf = ((sgn >> 0) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[0], (double)_mm_cvtss_f32(vsv) + (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[0] = vu1gen::normResult(rr[0], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[0][lf & 0xFu]; stf |= lf & 0xFu; }
            rvn = _mm_loadu_ps(rr);
          } }
        cx.pushFmac(c, mac, stf, stk);
        vu1gen::storeLanes(st.acc, rvn, 0x8u);
      }
      bvReg = -1;
      c += 1u;
    }
    L0180:;
    { // pair 48 pc=0x180 up=0x01083A09 lo=0x8000033C
      c = vu1gen::vmax(c, cx.vfR[7][0]);
      c = vu1gen::vmax(c, cx.vfR[8][1]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[7]);
        const __m128 bv = vu1gen::nrmbc(st.vf[8], 1);
        const __m128 av = vu1gen::nrm4(st.acc);
        const __m128 product = _mm_mul_ps(vsv, bv);
        const __m128 rv = _mm_add_ps(av, product);
        uint32_t mac = 0u, stf = 0u, stk = 0u;
        __m128 rvn = rv;
        { uint32_t sgn; uint32_t plain = vu1gen::classify4(rv, sgn);
          const __m128i pm = _mm_and_si128(_mm_castps_si128(product), _mm_set1_epi32(0x7FFFFFFF));
          plain &= ~uint32_t(_mm_movemask_ps(_mm_castsi128_ps(_mm_cmpgt_epi32(pm, _mm_set1_epi32(0x7F7FFFFE)))));
          if ((plain & 0x1u) == 0x1u) {
            mac = vu1gen::kMacSign.word[sgn & 0x1u];
            stf = (sgn & 0x1u) != 0u ? 0x2u : 0u;
          } else {
            float rr[4]; _mm_storeu_ps(rr, rv);
            { uint8_t lf;
              if (plain & 1u) lf = ((sgn >> 0) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[0], (double)_mm_cvtss_f32(av) + (double)_mm_cvtss_f32(vsv) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[0] = vu1gen::normResult(rr[0], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[0][lf & 0xFu]; stf |= lf & 0xFu; }
            rvn = _mm_loadu_ps(rr);
          } }
        if (cx.sticky) stk = vu1gen::sticky4(vsv, bv, product, 0x1u);
        cx.pushFmac(c, mac, stf, stk);
        urv = rvn;
      }
      bvReg = -1;
      vu1gen::storeLanes(st.vf[8], urv, 0x8u);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[8] = rt;
        cx.vfR[8][0] = rt;
      }
      c += 1u;
    }
    L0188:;
    { // pair 49 pc=0x188 up=0x01DD49BC lo=0x01E10000
      c = vu1gen::vmax(c, cx.vfR[9][0]);
      c = vu1gen::vmax(c, cx.vfR[9][1]);
      c = vu1gen::vmax(c, cx.vfR[9][2]);
      c = vu1gen::vmax(c, cx.vfR[29][0]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[9]);
        const __m128 bv = vu1gen::nrmbc(st.vf[29], 0);
        const __m128 rv = _mm_mul_ps(vsv, bv);
        uint32_t mac = 0u, stf = 0u, stk = 0u;
        __m128 rvn = rv;
        { uint32_t sgn; uint32_t plain = vu1gen::classify4(rv, sgn);
          if ((plain & 0x7u) == 0x7u) {
            mac = vu1gen::kMacSign.word[sgn & 0x7u];
            stf = (sgn & 0x7u) != 0u ? 0x2u : 0u;
          } else {
            float rr[4]; _mm_storeu_ps(rr, rv);
            { uint8_t lf;
              if (plain & 1u) lf = ((sgn >> 0) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[0], (double)_mm_cvtss_f32(vsv) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[0] = vu1gen::normResult(rr[0], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[0][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 2u) lf = ((sgn >> 1) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[1], (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(1, 1, 1, 1))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[1] = vu1gen::normResult(rr[1], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[1][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 4u) lf = ((sgn >> 2) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[2], (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(2, 2, 2, 2))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[2] = vu1gen::normResult(rr[2], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[2][lf & 0xFu]; stf |= lf & 0xFu; }
            rvn = _mm_loadu_ps(rr);
          } }
        cx.pushFmac(c, mac, stf, stk);
        vu1gen::storeLanes(st.acc, rvn, 0xEu);
      }
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 0) * 16u) & 0xFFFu;
          std::memcpy(&st.vf[1][0], vm + addr + 0u, 16);
        }
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[1] = rt;
        _mm_store_si128((__m128i *)cx.vfR[1], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L0190:;
    { // pair 50 pc=0x190 up=0x01DD50BD lo=0x01E20001
      c = vu1gen::vmax(c, cx.vfR[10][0]);
      c = vu1gen::vmax(c, cx.vfR[10][1]);
      c = vu1gen::vmax(c, cx.vfR[10][2]);
      c = vu1gen::vmax(c, cx.vfR[29][1]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[10]);
        const __m128 bv = vu1gen::nrmbc(st.vf[29], 1);
        const __m128 av = vu1gen::nrm4(st.acc);
        const __m128 product = _mm_mul_ps(vsv, bv);
        const __m128 rv = _mm_add_ps(av, product);
        uint32_t mac = 0u, stf = 0u, stk = 0u;
        __m128 rvn = rv;
        { uint32_t sgn; uint32_t plain = vu1gen::classify4(rv, sgn);
          const __m128i pm = _mm_and_si128(_mm_castps_si128(product), _mm_set1_epi32(0x7FFFFFFF));
          plain &= ~uint32_t(_mm_movemask_ps(_mm_castsi128_ps(_mm_cmpgt_epi32(pm, _mm_set1_epi32(0x7F7FFFFE)))));
          if ((plain & 0x7u) == 0x7u) {
            mac = vu1gen::kMacSign.word[sgn & 0x7u];
            stf = (sgn & 0x7u) != 0u ? 0x2u : 0u;
          } else {
            float rr[4]; _mm_storeu_ps(rr, rv);
            { uint8_t lf;
              if (plain & 1u) lf = ((sgn >> 0) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[0], (double)_mm_cvtss_f32(av) + (double)_mm_cvtss_f32(vsv) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[0] = vu1gen::normResult(rr[0], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[0][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 2u) lf = ((sgn >> 1) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[1], (double)_mm_cvtss_f32(_mm_shuffle_ps(av, av, _MM_SHUFFLE(1, 1, 1, 1))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(1, 1, 1, 1))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[1] = vu1gen::normResult(rr[1], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[1][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 4u) lf = ((sgn >> 2) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[2], (double)_mm_cvtss_f32(_mm_shuffle_ps(av, av, _MM_SHUFFLE(2, 2, 2, 2))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(2, 2, 2, 2))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[2] = vu1gen::normResult(rr[2], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[2][lf & 0xFu]; stf |= lf & 0xFu; }
            rvn = _mm_loadu_ps(rr);
          } }
        if (cx.sticky) stk = vu1gen::sticky4(vsv, bv, product, 0x7u);
        cx.pushFmac(c, mac, stf, stk);
        vu1gen::storeLanes(st.acc, rvn, 0xEu);
      }
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 1) * 16u) & 0xFFFu;
          std::memcpy(&st.vf[2][0], vm + addr + 0u, 16);
        }
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[2] = rt;
        _mm_store_si128((__m128i *)cx.vfR[2], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L0198:;
    { // pair 51 pc=0x198 up=0x000002FF lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    L01A0:;
    { // pair 52 pc=0x1A0 up=0x000002FF lo=0x80283BBE
      c = vu1gen::vmax(c, cx.vfR[7][1]);
      c = vu1gen::vmax(c, cx.vfR[8][0]);
      if (cx.qValid) c = vu1gen::vmax(c, cx.qReady);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        cx.commitQ(c);
        { const float num = vu1gen::nrm(st.vf[7][1]);
          const float rad = vu1gen::nrm(st.vf[8][0]);
          const float den = std::sqrt(std::fabs(rad));
          uint32_t di = (rad < 0.0f) ? 0x10u : 0u; float r = 0.0f;
          if (den != 0.0f) r = num / den;
          else { di = (num == 0.0f) ? 0x10u : 0x20u;
            r = std::signbit(num) ? -std::numeric_limits<float>::max() : std::numeric_limits<float>::max(); }
          uint32_t ig; r = vu1gen::normResult(r, ig);
          cx.qValid = true; cx.qReady = c + 13u; cx.qVal = r; cx.qDi = di; }
      }
      bvReg = -1;
      c += 1u;
    }
    L01A8:;
    { // pair 53 pc=0x1A8 up=0x01DD58BE lo=0x01E70006
      c = vu1gen::vmax(c, cx.vfR[11][0]);
      c = vu1gen::vmax(c, cx.vfR[11][1]);
      c = vu1gen::vmax(c, cx.vfR[11][2]);
      c = vu1gen::vmax(c, cx.vfR[29][2]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[11]);
        const __m128 bv = vu1gen::nrmbc(st.vf[29], 2);
        const __m128 av = vu1gen::nrm4(st.acc);
        const __m128 product = _mm_mul_ps(vsv, bv);
        const __m128 rv = _mm_add_ps(av, product);
        uint32_t mac = 0u, stf = 0u, stk = 0u;
        __m128 rvn = rv;
        { uint32_t sgn; uint32_t plain = vu1gen::classify4(rv, sgn);
          const __m128i pm = _mm_and_si128(_mm_castps_si128(product), _mm_set1_epi32(0x7FFFFFFF));
          plain &= ~uint32_t(_mm_movemask_ps(_mm_castsi128_ps(_mm_cmpgt_epi32(pm, _mm_set1_epi32(0x7F7FFFFE)))));
          if ((plain & 0x7u) == 0x7u) {
            mac = vu1gen::kMacSign.word[sgn & 0x7u];
            stf = (sgn & 0x7u) != 0u ? 0x2u : 0u;
          } else {
            float rr[4]; _mm_storeu_ps(rr, rv);
            { uint8_t lf;
              if (plain & 1u) lf = ((sgn >> 0) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[0], (double)_mm_cvtss_f32(av) + (double)_mm_cvtss_f32(vsv) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[0] = vu1gen::normResult(rr[0], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[0][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 2u) lf = ((sgn >> 1) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[1], (double)_mm_cvtss_f32(_mm_shuffle_ps(av, av, _MM_SHUFFLE(1, 1, 1, 1))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(1, 1, 1, 1))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[1] = vu1gen::normResult(rr[1], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[1][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 4u) lf = ((sgn >> 2) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[2], (double)_mm_cvtss_f32(_mm_shuffle_ps(av, av, _MM_SHUFFLE(2, 2, 2, 2))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(2, 2, 2, 2))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[2] = vu1gen::normResult(rr[2], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[2][lf & 0xFu]; stf |= lf & 0xFu; }
            rvn = _mm_loadu_ps(rr);
          } }
        if (cx.sticky) stk = vu1gen::sticky4(vsv, bv, product, 0x7u);
        cx.pushFmac(c, mac, stf, stk);
        vu1gen::storeLanes(st.acc, rvn, 0xEu);
      }
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 6) * 16u) & 0xFFFu;
          std::memcpy(&st.vf[7][0], vm + addr + 0u, 16);
        }
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[7] = rt;
        _mm_store_si128((__m128i *)cx.vfR[7], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L01B0:;
    { // pair 54 pc=0x1B0 up=0x01DD624B lo=0x01E30002
      c = vu1gen::vmax(c, cx.vfR[12][0]);
      c = vu1gen::vmax(c, cx.vfR[12][1]);
      c = vu1gen::vmax(c, cx.vfR[12][2]);
      c = vu1gen::vmax(c, cx.vfR[29][3]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[12]);
        const __m128 bv = vu1gen::nrmbc(st.vf[29], 3);
        const __m128 av = vu1gen::nrm4(st.acc);
        const __m128 product = _mm_mul_ps(vsv, bv);
        const __m128 rv = _mm_add_ps(av, product);
        uint32_t mac = 0u, stf = 0u, stk = 0u;
        __m128 rvn = rv;
        { uint32_t sgn; uint32_t plain = vu1gen::classify4(rv, sgn);
          const __m128i pm = _mm_and_si128(_mm_castps_si128(product), _mm_set1_epi32(0x7FFFFFFF));
          plain &= ~uint32_t(_mm_movemask_ps(_mm_castsi128_ps(_mm_cmpgt_epi32(pm, _mm_set1_epi32(0x7F7FFFFE)))));
          if ((plain & 0x7u) == 0x7u) {
            mac = vu1gen::kMacSign.word[sgn & 0x7u];
            stf = (sgn & 0x7u) != 0u ? 0x2u : 0u;
          } else {
            float rr[4]; _mm_storeu_ps(rr, rv);
            { uint8_t lf;
              if (plain & 1u) lf = ((sgn >> 0) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[0], (double)_mm_cvtss_f32(av) + (double)_mm_cvtss_f32(vsv) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[0] = vu1gen::normResult(rr[0], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[0][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 2u) lf = ((sgn >> 1) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[1], (double)_mm_cvtss_f32(_mm_shuffle_ps(av, av, _MM_SHUFFLE(1, 1, 1, 1))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(1, 1, 1, 1))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[1] = vu1gen::normResult(rr[1], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[1][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 4u) lf = ((sgn >> 2) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[2], (double)_mm_cvtss_f32(_mm_shuffle_ps(av, av, _MM_SHUFFLE(2, 2, 2, 2))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(2, 2, 2, 2))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[2] = vu1gen::normResult(rr[2], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[2][lf & 0xFu]; stf |= lf & 0xFu; }
            rvn = _mm_loadu_ps(rr);
          } }
        if (cx.sticky) stk = vu1gen::sticky4(vsv, bv, product, 0x7u);
        cx.pushFmac(c, mac, stf, stk);
        urv = rvn;
      }
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 2) * 16u) & 0xFFFu;
          std::memcpy(&st.vf[3][0], vm + addr + 0u, 16);
        }
      }
      bvReg = -1;
      vu1gen::storeLanes(st.vf[9], urv, 0xEu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[9] = rt;
        cx.vfR[9][0] = rt;
        cx.vfR[9][1] = rt;
        cx.vfR[9][2] = rt;
      }
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[3] = rt;
        _mm_store_si128((__m128i *)cx.vfR[3], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L01B8:;
    { // pair 55 pc=0x1B8 up=0x01FF29BC lo=0x01E40003
      c = vu1gen::vmax(c, cx.vfRAny[5]);
      c = vu1gen::vmax(c, cx.vfR[31][0]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[5]);
        const __m128 bv = vu1gen::nrmbc(st.vf[31], 0);
        const __m128 rv = _mm_mul_ps(vsv, bv);
        uint32_t mac = 0u, stf = 0u, stk = 0u;
        __m128 rvn = rv;
        { uint32_t sgn; uint32_t plain = vu1gen::classify4(rv, sgn);
          if ((plain & 0xFu) == 0xFu) {
            mac = vu1gen::kMacSign.word[sgn & 0xFu];
            stf = (sgn & 0xFu) != 0u ? 0x2u : 0u;
          } else {
            float rr[4]; _mm_storeu_ps(rr, rv);
            { uint8_t lf;
              if (plain & 1u) lf = ((sgn >> 0) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[0], (double)_mm_cvtss_f32(vsv) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[0] = vu1gen::normResult(rr[0], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[0][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 2u) lf = ((sgn >> 1) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[1], (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(1, 1, 1, 1))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[1] = vu1gen::normResult(rr[1], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[1][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 4u) lf = ((sgn >> 2) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[2], (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(2, 2, 2, 2))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[2] = vu1gen::normResult(rr[2], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[2][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 8u) lf = ((sgn >> 3) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[3], (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(3, 3, 3, 3))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[3] = vu1gen::normResult(rr[3], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[3][lf & 0xFu]; stf |= lf & 0xFu; }
            rvn = _mm_loadu_ps(rr);
          } }
        cx.pushFmac(c, mac, stf, stk);
        vu1gen::storeLanes(st.acc, rvn, 0xFu);
      }
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 3) * 16u) & 0xFFFu;
          std::memcpy(&st.vf[4][0], vm + addr + 0u, 16);
        }
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[4] = rt;
        _mm_store_si128((__m128i *)cx.vfR[4], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L01C0:;
    { // pair 56 pc=0x1C0 up=0x01FF30BD lo=0x01E50008
      c = vu1gen::vmax(c, cx.vfRAny[6]);
      c = vu1gen::vmax(c, cx.vfR[31][1]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[6]);
        const __m128 bv = vu1gen::nrmbc(st.vf[31], 1);
        const __m128 av = vu1gen::nrm4(st.acc);
        const __m128 product = _mm_mul_ps(vsv, bv);
        const __m128 rv = _mm_add_ps(av, product);
        uint32_t mac = 0u, stf = 0u, stk = 0u;
        __m128 rvn = rv;
        { uint32_t sgn; uint32_t plain = vu1gen::classify4(rv, sgn);
          const __m128i pm = _mm_and_si128(_mm_castps_si128(product), _mm_set1_epi32(0x7FFFFFFF));
          plain &= ~uint32_t(_mm_movemask_ps(_mm_castsi128_ps(_mm_cmpgt_epi32(pm, _mm_set1_epi32(0x7F7FFFFE)))));
          if ((plain & 0xFu) == 0xFu) {
            mac = vu1gen::kMacSign.word[sgn & 0xFu];
            stf = (sgn & 0xFu) != 0u ? 0x2u : 0u;
          } else {
            float rr[4]; _mm_storeu_ps(rr, rv);
            { uint8_t lf;
              if (plain & 1u) lf = ((sgn >> 0) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[0], (double)_mm_cvtss_f32(av) + (double)_mm_cvtss_f32(vsv) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[0] = vu1gen::normResult(rr[0], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[0][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 2u) lf = ((sgn >> 1) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[1], (double)_mm_cvtss_f32(_mm_shuffle_ps(av, av, _MM_SHUFFLE(1, 1, 1, 1))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(1, 1, 1, 1))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[1] = vu1gen::normResult(rr[1], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[1][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 4u) lf = ((sgn >> 2) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[2], (double)_mm_cvtss_f32(_mm_shuffle_ps(av, av, _MM_SHUFFLE(2, 2, 2, 2))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(2, 2, 2, 2))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[2] = vu1gen::normResult(rr[2], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[2][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 8u) lf = ((sgn >> 3) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[3], (double)_mm_cvtss_f32(_mm_shuffle_ps(av, av, _MM_SHUFFLE(3, 3, 3, 3))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(3, 3, 3, 3))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[3] = vu1gen::normResult(rr[3], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[3][lf & 0xFu]; stf |= lf & 0xFu; }
            rvn = _mm_loadu_ps(rr);
          } }
        if (cx.sticky) stk = vu1gen::sticky4(vsv, bv, product, 0xFu);
        cx.pushFmac(c, mac, stf, stk);
        vu1gen::storeLanes(st.acc, rvn, 0xFu);
      }
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 8) * 16u) & 0xFFFu;
          std::memcpy(&st.vf[5][0], vm + addr + 0u, 16);
        }
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[5] = rt;
        _mm_store_si128((__m128i *)cx.vfR[5], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L01C8:;
    { // pair 57 pc=0x1C8 up=0x01FF3F8A lo=0x01E60009
      c = vu1gen::vmax(c, cx.vfRAny[7]);
      c = vu1gen::vmax(c, cx.vfR[31][2]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[7]);
        const __m128 bv = vu1gen::nrmbc(st.vf[31], 2);
        const __m128 av = vu1gen::nrm4(st.acc);
        const __m128 product = _mm_mul_ps(vsv, bv);
        const __m128 rv = _mm_add_ps(av, product);
        uint32_t mac = 0u, stf = 0u, stk = 0u;
        __m128 rvn = rv;
        { uint32_t sgn; uint32_t plain = vu1gen::classify4(rv, sgn);
          const __m128i pm = _mm_and_si128(_mm_castps_si128(product), _mm_set1_epi32(0x7FFFFFFF));
          plain &= ~uint32_t(_mm_movemask_ps(_mm_castsi128_ps(_mm_cmpgt_epi32(pm, _mm_set1_epi32(0x7F7FFFFE)))));
          if ((plain & 0xFu) == 0xFu) {
            mac = vu1gen::kMacSign.word[sgn & 0xFu];
            stf = (sgn & 0xFu) != 0u ? 0x2u : 0u;
          } else {
            float rr[4]; _mm_storeu_ps(rr, rv);
            { uint8_t lf;
              if (plain & 1u) lf = ((sgn >> 0) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[0], (double)_mm_cvtss_f32(av) + (double)_mm_cvtss_f32(vsv) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[0] = vu1gen::normResult(rr[0], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[0][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 2u) lf = ((sgn >> 1) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[1], (double)_mm_cvtss_f32(_mm_shuffle_ps(av, av, _MM_SHUFFLE(1, 1, 1, 1))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(1, 1, 1, 1))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[1] = vu1gen::normResult(rr[1], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[1][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 4u) lf = ((sgn >> 2) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[2], (double)_mm_cvtss_f32(_mm_shuffle_ps(av, av, _MM_SHUFFLE(2, 2, 2, 2))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(2, 2, 2, 2))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[2] = vu1gen::normResult(rr[2], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[2][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 8u) lf = ((sgn >> 3) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[3], (double)_mm_cvtss_f32(_mm_shuffle_ps(av, av, _MM_SHUFFLE(3, 3, 3, 3))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(3, 3, 3, 3))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[3] = vu1gen::normResult(rr[3], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[3][lf & 0xFu]; stf |= lf & 0xFu; }
            rvn = _mm_loadu_ps(rr);
          } }
        if (cx.sticky) stk = vu1gen::sticky4(vsv, bv, product, 0xFu);
        cx.pushFmac(c, mac, stf, stk);
        urv = rvn;
      }
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 9) * 16u) & 0xFFFu;
          std::memcpy(&st.vf[6][0], vm + addr + 0u, 16);
        }
      }
      bvReg = -1;
      vu1gen::storeLanes(st.vf[30], urv, 0xFu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[30] = rt;
        _mm_store_si128((__m128i *)cx.vfR[30], _mm_set1_epi32((int)rt));
      }
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[6] = rt;
        _mm_store_si128((__m128i *)cx.vfR[6], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L01D0:;
    { // pair 58 pc=0x1D0 up=0x01E909BC lo=0x01E7000A
      c = vu1gen::vmax(c, cx.vfRAny[1]);
      c = vu1gen::vmax(c, cx.vfR[9][0]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[1]);
        const __m128 bv = vu1gen::nrmbc(st.vf[9], 0);
        const __m128 rv = _mm_mul_ps(vsv, bv);
        uint32_t mac = 0u, stf = 0u, stk = 0u;
        __m128 rvn = rv;
        { uint32_t sgn; uint32_t plain = vu1gen::classify4(rv, sgn);
          if ((plain & 0xFu) == 0xFu) {
            mac = vu1gen::kMacSign.word[sgn & 0xFu];
            stf = (sgn & 0xFu) != 0u ? 0x2u : 0u;
          } else {
            float rr[4]; _mm_storeu_ps(rr, rv);
            { uint8_t lf;
              if (plain & 1u) lf = ((sgn >> 0) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[0], (double)_mm_cvtss_f32(vsv) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[0] = vu1gen::normResult(rr[0], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[0][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 2u) lf = ((sgn >> 1) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[1], (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(1, 1, 1, 1))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[1] = vu1gen::normResult(rr[1], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[1][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 4u) lf = ((sgn >> 2) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[2], (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(2, 2, 2, 2))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[2] = vu1gen::normResult(rr[2], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[2][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 8u) lf = ((sgn >> 3) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[3], (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(3, 3, 3, 3))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[3] = vu1gen::normResult(rr[3], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[3][lf & 0xFu]; stf |= lf & 0xFu; }
            rvn = _mm_loadu_ps(rr);
          } }
        cx.pushFmac(c, mac, stf, stk);
        vu1gen::storeLanes(st.acc, rvn, 0xFu);
      }
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 10) * 16u) & 0xFFFu;
          std::memcpy(&st.vf[7][0], vm + addr + 0u, 16);
        }
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[7] = rt;
        _mm_store_si128((__m128i *)cx.vfR[7], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L01D8:;
    { // pair 59 pc=0x1D8 up=0x01E910BD lo=0x01E8000B
      c = vu1gen::vmax(c, cx.vfRAny[2]);
      c = vu1gen::vmax(c, cx.vfR[9][1]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[2]);
        const __m128 bv = vu1gen::nrmbc(st.vf[9], 1);
        const __m128 av = vu1gen::nrm4(st.acc);
        const __m128 product = _mm_mul_ps(vsv, bv);
        const __m128 rv = _mm_add_ps(av, product);
        uint32_t mac = 0u, stf = 0u, stk = 0u;
        __m128 rvn = rv;
        { uint32_t sgn; uint32_t plain = vu1gen::classify4(rv, sgn);
          const __m128i pm = _mm_and_si128(_mm_castps_si128(product), _mm_set1_epi32(0x7FFFFFFF));
          plain &= ~uint32_t(_mm_movemask_ps(_mm_castsi128_ps(_mm_cmpgt_epi32(pm, _mm_set1_epi32(0x7F7FFFFE)))));
          if ((plain & 0xFu) == 0xFu) {
            mac = vu1gen::kMacSign.word[sgn & 0xFu];
            stf = (sgn & 0xFu) != 0u ? 0x2u : 0u;
          } else {
            float rr[4]; _mm_storeu_ps(rr, rv);
            { uint8_t lf;
              if (plain & 1u) lf = ((sgn >> 0) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[0], (double)_mm_cvtss_f32(av) + (double)_mm_cvtss_f32(vsv) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[0] = vu1gen::normResult(rr[0], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[0][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 2u) lf = ((sgn >> 1) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[1], (double)_mm_cvtss_f32(_mm_shuffle_ps(av, av, _MM_SHUFFLE(1, 1, 1, 1))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(1, 1, 1, 1))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[1] = vu1gen::normResult(rr[1], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[1][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 4u) lf = ((sgn >> 2) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[2], (double)_mm_cvtss_f32(_mm_shuffle_ps(av, av, _MM_SHUFFLE(2, 2, 2, 2))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(2, 2, 2, 2))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[2] = vu1gen::normResult(rr[2], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[2][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 8u) lf = ((sgn >> 3) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[3], (double)_mm_cvtss_f32(_mm_shuffle_ps(av, av, _MM_SHUFFLE(3, 3, 3, 3))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(3, 3, 3, 3))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[3] = vu1gen::normResult(rr[3], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[3][lf & 0xFu]; stf |= lf & 0xFu; }
            rvn = _mm_loadu_ps(rr);
          } }
        if (cx.sticky) stk = vu1gen::sticky4(vsv, bv, product, 0xFu);
        cx.pushFmac(c, mac, stf, stk);
        vu1gen::storeLanes(st.acc, rvn, 0xFu);
      }
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 11) * 16u) & 0xFFFu;
          std::memcpy(&st.vf[8][0], vm + addr + 0u, 16);
        }
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[8] = rt;
        _mm_store_si128((__m128i *)cx.vfR[8], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L01E0:;
    { // pair 60 pc=0x1E0 up=0x01E918BE lo=0x01E1000D
      c = vu1gen::vmax(c, cx.vfRAny[3]);
      c = vu1gen::vmax(c, cx.vfR[9][2]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[3]);
        const __m128 bv = vu1gen::nrmbc(st.vf[9], 2);
        const __m128 av = vu1gen::nrm4(st.acc);
        const __m128 product = _mm_mul_ps(vsv, bv);
        const __m128 rv = _mm_add_ps(av, product);
        uint32_t mac = 0u, stf = 0u, stk = 0u;
        __m128 rvn = rv;
        { uint32_t sgn; uint32_t plain = vu1gen::classify4(rv, sgn);
          const __m128i pm = _mm_and_si128(_mm_castps_si128(product), _mm_set1_epi32(0x7FFFFFFF));
          plain &= ~uint32_t(_mm_movemask_ps(_mm_castsi128_ps(_mm_cmpgt_epi32(pm, _mm_set1_epi32(0x7F7FFFFE)))));
          if ((plain & 0xFu) == 0xFu) {
            mac = vu1gen::kMacSign.word[sgn & 0xFu];
            stf = (sgn & 0xFu) != 0u ? 0x2u : 0u;
          } else {
            float rr[4]; _mm_storeu_ps(rr, rv);
            { uint8_t lf;
              if (plain & 1u) lf = ((sgn >> 0) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[0], (double)_mm_cvtss_f32(av) + (double)_mm_cvtss_f32(vsv) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[0] = vu1gen::normResult(rr[0], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[0][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 2u) lf = ((sgn >> 1) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[1], (double)_mm_cvtss_f32(_mm_shuffle_ps(av, av, _MM_SHUFFLE(1, 1, 1, 1))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(1, 1, 1, 1))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[1] = vu1gen::normResult(rr[1], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[1][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 4u) lf = ((sgn >> 2) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[2], (double)_mm_cvtss_f32(_mm_shuffle_ps(av, av, _MM_SHUFFLE(2, 2, 2, 2))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(2, 2, 2, 2))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[2] = vu1gen::normResult(rr[2], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[2][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 8u) lf = ((sgn >> 3) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[3], (double)_mm_cvtss_f32(_mm_shuffle_ps(av, av, _MM_SHUFFLE(3, 3, 3, 3))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(3, 3, 3, 3))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[3] = vu1gen::normResult(rr[3], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[3][lf & 0xFu]; stf |= lf & 0xFu; }
            rvn = _mm_loadu_ps(rr);
          } }
        if (cx.sticky) stk = vu1gen::sticky4(vsv, bv, product, 0xFu);
        cx.pushFmac(c, mac, stf, stk);
        vu1gen::storeLanes(st.acc, rvn, 0xFu);
      }
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 13) * 16u) & 0xFFFu;
          std::memcpy(&st.vf[1][0], vm + addr + 0u, 16);
        }
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[1] = rt;
        _mm_store_si128((__m128i *)cx.vfR[1], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L01E8:;
    { const bool bt = (int16_t)0 == (int16_t)(bvReg == 8 ? bvOld : st.vi[8]);
    { // pair 61 pc=0x1E8 up=0x01E9224B lo=0x50080006
      c = vu1gen::vmax(c, cx.vfRAny[4]);
      c = vu1gen::vmax(c, cx.vfR[9][3]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[4]);
        const __m128 bv = vu1gen::nrmbc(st.vf[9], 3);
        const __m128 av = vu1gen::nrm4(st.acc);
        const __m128 product = _mm_mul_ps(vsv, bv);
        const __m128 rv = _mm_add_ps(av, product);
        uint32_t mac = 0u, stf = 0u, stk = 0u;
        __m128 rvn = rv;
        { uint32_t sgn; uint32_t plain = vu1gen::classify4(rv, sgn);
          const __m128i pm = _mm_and_si128(_mm_castps_si128(product), _mm_set1_epi32(0x7FFFFFFF));
          plain &= ~uint32_t(_mm_movemask_ps(_mm_castsi128_ps(_mm_cmpgt_epi32(pm, _mm_set1_epi32(0x7F7FFFFE)))));
          if ((plain & 0xFu) == 0xFu) {
            mac = vu1gen::kMacSign.word[sgn & 0xFu];
            stf = (sgn & 0xFu) != 0u ? 0x2u : 0u;
          } else {
            float rr[4]; _mm_storeu_ps(rr, rv);
            { uint8_t lf;
              if (plain & 1u) lf = ((sgn >> 0) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[0], (double)_mm_cvtss_f32(av) + (double)_mm_cvtss_f32(vsv) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[0] = vu1gen::normResult(rr[0], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[0][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 2u) lf = ((sgn >> 1) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[1], (double)_mm_cvtss_f32(_mm_shuffle_ps(av, av, _MM_SHUFFLE(1, 1, 1, 1))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(1, 1, 1, 1))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[1] = vu1gen::normResult(rr[1], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[1][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 4u) lf = ((sgn >> 2) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[2], (double)_mm_cvtss_f32(_mm_shuffle_ps(av, av, _MM_SHUFFLE(2, 2, 2, 2))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(2, 2, 2, 2))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[2] = vu1gen::normResult(rr[2], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[2][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 8u) lf = ((sgn >> 3) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[3], (double)_mm_cvtss_f32(_mm_shuffle_ps(av, av, _MM_SHUFFLE(3, 3, 3, 3))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(3, 3, 3, 3))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[3] = vu1gen::normResult(rr[3], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[3][lf & 0xFu]; stf |= lf & 0xFu; }
            rvn = _mm_loadu_ps(rr);
          } }
        if (cx.sticky) stk = vu1gen::sticky4(vsv, bv, product, 0xFu);
        cx.pushFmac(c, mac, stf, stk);
        urv = rvn;
      }
      bvReg = -1;
      vu1gen::storeLanes(st.vf[9], urv, 0xFu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[9] = rt;
        _mm_store_si128((__m128i *)cx.vfR[9], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    { // pair 62 pc=0x1F0 up=0x01E0F790 lo=0x01FD000C
      c = vu1gen::vmax(c, cx.vfRAny[30]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[30]);
        const __m128 bv = _mm_set1_ps(0.0f);
        const __m128 rv = _mm_max_ps(vsv, bv);
        urv = rv;
      }
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 12) * 16u) & 0xFFFu;
          std::memcpy(&st.vf[29][0], vm + addr + 0u, 16);
        }
      }
      bvReg = -1;
      vu1gen::storeLanes(st.vf[30], urv, 0xFu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[30] = rt;
        _mm_store_si128((__m128i *)cx.vfR[30], _mm_set1_epi32((int)rt));
      }
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[29] = rt;
        _mm_store_si128((__m128i *)cx.vfR[29], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    if (bt) {
      st.branchTarget = 0x220u;
      goto L0220;
    } }
    goto LC01F8;
    L01F0:;
    { // pair 62 pc=0x1F0 up=0x01E0F790 lo=0x01FD000C
      c = vu1gen::vmax(c, cx.vfRAny[30]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[30]);
        const __m128 bv = _mm_set1_ps(0.0f);
        const __m128 rv = _mm_max_ps(vsv, bv);
        urv = rv;
      }
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 12) * 16u) & 0xFFFu;
          std::memcpy(&st.vf[29][0], vm + addr + 0u, 16);
        }
      }
      bvReg = -1;
      vu1gen::storeLanes(st.vf[30], urv, 0xFu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[30] = rt;
        _mm_store_si128((__m128i *)cx.vfR[30], _mm_set1_epi32((int)rt));
      }
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[29] = rt;
        _mm_store_si128((__m128i *)cx.vfR[29], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    LC01F8:;
    L01F8:;
    { // pair 63 pc=0x1F8 up=0x000002FF lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    L0200:;
    { // pair 64 pc=0x200 up=0x000002FF lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    L0208:;
    { // pair 65 pc=0x208 up=0x000002FF lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    L0210:;
    { // pair 66 pc=0x210 up=0x01DEF7AA lo=0x8000033C
      c = vu1gen::vmax(c, cx.vfR[30][0]);
      c = vu1gen::vmax(c, cx.vfR[30][1]);
      c = vu1gen::vmax(c, cx.vfR[30][2]);
      c = vu1gen::vmax(c, cx.vfR[30][0]);
      c = vu1gen::vmax(c, cx.vfR[30][1]);
      c = vu1gen::vmax(c, cx.vfR[30][2]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[30]);
        const __m128 bv = vu1gen::nrm4(st.vf[30]);
        const __m128 rv = _mm_mul_ps(vsv, bv);
        uint32_t mac = 0u, stf = 0u, stk = 0u;
        __m128 rvn = rv;
        { uint32_t sgn; uint32_t plain = vu1gen::classify4(rv, sgn);
          if ((plain & 0x7u) == 0x7u) {
            mac = vu1gen::kMacSign.word[sgn & 0x7u];
            stf = (sgn & 0x7u) != 0u ? 0x2u : 0u;
          } else {
            float rr[4]; _mm_storeu_ps(rr, rv);
            { uint8_t lf;
              if (plain & 1u) lf = ((sgn >> 0) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[0], (double)_mm_cvtss_f32(vsv) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[0] = vu1gen::normResult(rr[0], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[0][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 2u) lf = ((sgn >> 1) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[1], (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(1, 1, 1, 1))) * (double)_mm_cvtss_f32(_mm_shuffle_ps(bv, bv, _MM_SHUFFLE(1, 1, 1, 1))));
              } else {
                uint32_t nf; rr[1] = vu1gen::normResult(rr[1], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[1][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 4u) lf = ((sgn >> 2) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[2], (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(2, 2, 2, 2))) * (double)_mm_cvtss_f32(_mm_shuffle_ps(bv, bv, _MM_SHUFFLE(2, 2, 2, 2))));
              } else {
                uint32_t nf; rr[2] = vu1gen::normResult(rr[2], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[2][lf & 0xFu]; stf |= lf & 0xFu; }
            rvn = _mm_loadu_ps(rr);
          } }
        cx.pushFmac(c, mac, stf, stk);
        urv = rvn;
      }
      bvReg = -1;
      vu1gen::storeLanes(st.vf[30], urv, 0xEu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[30] = rt;
        cx.vfR[30][0] = rt;
        cx.vfR[30][1] = rt;
        cx.vfR[30][2] = rt;
      }
      c += 1u;
    }
    L0218:;
    { // pair 67 pc=0x218 up=0x000002FF lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    L0220:;
    { // pair 68 pc=0x220 up=0x0101003D lo=0x8000033C
      c = vu1gen::vmax(c, cx.vfR[1][1]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        const __m128 vsv = _mm_setr_ps(0.0f, 0.0f, 0.0f, 1.0f);
        const __m128 bv = vu1gen::nrmbc(st.vf[1], 1);
        const __m128 rv = _mm_add_ps(vsv, bv);
        uint32_t mac = 0u, stf = 0u, stk = 0u;
        __m128 rvn = rv;
        { uint32_t sgn; uint32_t plain = vu1gen::classify4(rv, sgn);
          if ((plain & 0x1u) == 0x1u) {
            mac = vu1gen::kMacSign.word[sgn & 0x1u];
            stf = (sgn & 0x1u) != 0u ? 0x2u : 0u;
          } else {
            float rr[4]; _mm_storeu_ps(rr, rv);
            { uint8_t lf;
              if (plain & 1u) lf = ((sgn >> 0) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[0], (double)_mm_cvtss_f32(vsv) + (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[0] = vu1gen::normResult(rr[0], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[0][lf & 0xFu]; stf |= lf & 0xFu; }
            rvn = _mm_loadu_ps(rr);
          } }
        cx.pushFmac(c, mac, stf, stk);
        vu1gen::storeLanes(st.acc, rvn, 0x8u);
      }
      bvReg = -1;
      c += 1u;
    }
    L0228:;
    { // pair 69 pc=0x228 up=0x0109084B lo=0x81E903BC
      c = vu1gen::vmax(c, cx.vfR[1][0]);
      c = vu1gen::vmax(c, cx.vfR[9][3]);
      c = vu1gen::vmax(c, cx.vfR[9][3]);
      if (cx.qValid) c = vu1gen::vmax(c, cx.qReady);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[1]);
        const __m128 bv = vu1gen::nrmbc(st.vf[9], 3);
        const __m128 av = vu1gen::nrm4(st.acc);
        const __m128 product = _mm_mul_ps(vsv, bv);
        const __m128 rv = _mm_add_ps(av, product);
        uint32_t mac = 0u, stf = 0u, stk = 0u;
        __m128 rvn = rv;
        { uint32_t sgn; uint32_t plain = vu1gen::classify4(rv, sgn);
          const __m128i pm = _mm_and_si128(_mm_castps_si128(product), _mm_set1_epi32(0x7FFFFFFF));
          plain &= ~uint32_t(_mm_movemask_ps(_mm_castsi128_ps(_mm_cmpgt_epi32(pm, _mm_set1_epi32(0x7F7FFFFE)))));
          if ((plain & 0x1u) == 0x1u) {
            mac = vu1gen::kMacSign.word[sgn & 0x1u];
            stf = (sgn & 0x1u) != 0u ? 0x2u : 0u;
          } else {
            float rr[4]; _mm_storeu_ps(rr, rv);
            { uint8_t lf;
              if (plain & 1u) lf = ((sgn >> 0) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[0], (double)_mm_cvtss_f32(av) + (double)_mm_cvtss_f32(vsv) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[0] = vu1gen::normResult(rr[0], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[0][lf & 0xFu]; stf |= lf & 0xFu; }
            rvn = _mm_loadu_ps(rr);
          } }
        if (cx.sticky) stk = vu1gen::sticky4(vsv, bv, product, 0x1u);
        cx.pushFmac(c, mac, stf, stk);
        urv = rvn;
      }
      {
        cx.commitQ(c);
        { const float num = vu1gen::nrm(st.vf[0][3]);
          const float den = vu1gen::nrm(st.vf[9][3]);
          uint32_t di = 0u; float r;
          if (den == 0.0f) { di = (num == 0.0f) ? 0x10u : 0x20u;
            r = (std::signbit(num) != std::signbit(den)) ? -std::numeric_limits<float>::max() : std::numeric_limits<float>::max(); }
          else r = num / den;
          uint32_t ig; r = vu1gen::normResult(r, ig);
          cx.qValid = true; cx.qReady = c + 7u; cx.qVal = r; cx.qDi = di; }
      }
      bvReg = -1;
      vu1gen::storeLanes(st.vf[1], urv, 0x8u);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[1] = rt;
        cx.vfR[1][0] = rt;
      }
      c += 1u;
    }
    L0230:;
    { // pair 70 pc=0x230 up=0x01FE29BC lo=0x8000033C
      c = vu1gen::vmax(c, cx.vfRAny[5]);
      c = vu1gen::vmax(c, cx.vfR[30][0]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[5]);
        const __m128 bv = vu1gen::nrmbc(st.vf[30], 0);
        const __m128 rv = _mm_mul_ps(vsv, bv);
        uint32_t mac = 0u, stf = 0u, stk = 0u;
        __m128 rvn = rv;
        { uint32_t sgn; uint32_t plain = vu1gen::classify4(rv, sgn);
          if ((plain & 0xFu) == 0xFu) {
            mac = vu1gen::kMacSign.word[sgn & 0xFu];
            stf = (sgn & 0xFu) != 0u ? 0x2u : 0u;
          } else {
            float rr[4]; _mm_storeu_ps(rr, rv);
            { uint8_t lf;
              if (plain & 1u) lf = ((sgn >> 0) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[0], (double)_mm_cvtss_f32(vsv) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[0] = vu1gen::normResult(rr[0], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[0][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 2u) lf = ((sgn >> 1) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[1], (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(1, 1, 1, 1))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[1] = vu1gen::normResult(rr[1], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[1][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 4u) lf = ((sgn >> 2) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[2], (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(2, 2, 2, 2))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[2] = vu1gen::normResult(rr[2], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[2][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 8u) lf = ((sgn >> 3) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[3], (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(3, 3, 3, 3))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[3] = vu1gen::normResult(rr[3], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[3][lf & 0xFu]; stf |= lf & 0xFu; }
            rvn = _mm_loadu_ps(rr);
          } }
        cx.pushFmac(c, mac, stf, stk);
        vu1gen::storeLanes(st.acc, rvn, 0xFu);
      }
      bvReg = -1;
      c += 1u;
    }
    L0238:;
    { // pair 71 pc=0x238 up=0x01FE30BD lo=0x004A00FF
      c = vu1gen::vmax(c, cx.vfRAny[6]);
      c = vu1gen::vmax(c, cx.vfR[30][1]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[6]);
        const __m128 bv = vu1gen::nrmbc(st.vf[30], 1);
        const __m128 av = vu1gen::nrm4(st.acc);
        const __m128 product = _mm_mul_ps(vsv, bv);
        const __m128 rv = _mm_add_ps(av, product);
        uint32_t mac = 0u, stf = 0u, stk = 0u;
        __m128 rvn = rv;
        { uint32_t sgn; uint32_t plain = vu1gen::classify4(rv, sgn);
          const __m128i pm = _mm_and_si128(_mm_castps_si128(product), _mm_set1_epi32(0x7FFFFFFF));
          plain &= ~uint32_t(_mm_movemask_ps(_mm_castsi128_ps(_mm_cmpgt_epi32(pm, _mm_set1_epi32(0x7F7FFFFE)))));
          if ((plain & 0xFu) == 0xFu) {
            mac = vu1gen::kMacSign.word[sgn & 0xFu];
            stf = (sgn & 0xFu) != 0u ? 0x2u : 0u;
          } else {
            float rr[4]; _mm_storeu_ps(rr, rv);
            { uint8_t lf;
              if (plain & 1u) lf = ((sgn >> 0) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[0], (double)_mm_cvtss_f32(av) + (double)_mm_cvtss_f32(vsv) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[0] = vu1gen::normResult(rr[0], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[0][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 2u) lf = ((sgn >> 1) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[1], (double)_mm_cvtss_f32(_mm_shuffle_ps(av, av, _MM_SHUFFLE(1, 1, 1, 1))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(1, 1, 1, 1))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[1] = vu1gen::normResult(rr[1], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[1][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 4u) lf = ((sgn >> 2) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[2], (double)_mm_cvtss_f32(_mm_shuffle_ps(av, av, _MM_SHUFFLE(2, 2, 2, 2))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(2, 2, 2, 2))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[2] = vu1gen::normResult(rr[2], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[2][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 8u) lf = ((sgn >> 3) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[3], (double)_mm_cvtss_f32(_mm_shuffle_ps(av, av, _MM_SHUFFLE(3, 3, 3, 3))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(3, 3, 3, 3))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[3] = vu1gen::normResult(rr[3], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[3][lf & 0xFu]; stf |= lf & 0xFu; }
            rvn = _mm_loadu_ps(rr);
          } }
        if (cx.sticky) stk = vu1gen::sticky4(vsv, bv, product, 0xFu);
        cx.pushFmac(c, mac, stf, stk);
        vu1gen::storeLanes(st.acc, rvn, 0xFu);
      }
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 255) * 16u) & 0xFFFu;
          std::memcpy(&st.vf[10][2], vm + addr + 8u, 4);
        }
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[10] = rt;
        cx.vfR[10][2] = rt;
      }
      c += 1u;
    }
    L0240:;
    { // pair 72 pc=0x240 up=0x01FE38BE lo=0x81EB03FD
      c = vu1gen::vmax(c, cx.vfRAny[7]);
      c = vu1gen::vmax(c, cx.vfR[30][2]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[7]);
        const __m128 bv = vu1gen::nrmbc(st.vf[30], 2);
        const __m128 av = vu1gen::nrm4(st.acc);
        const __m128 product = _mm_mul_ps(vsv, bv);
        const __m128 rv = _mm_add_ps(av, product);
        uint32_t mac = 0u, stf = 0u, stk = 0u;
        __m128 rvn = rv;
        { uint32_t sgn; uint32_t plain = vu1gen::classify4(rv, sgn);
          const __m128i pm = _mm_and_si128(_mm_castps_si128(product), _mm_set1_epi32(0x7FFFFFFF));
          plain &= ~uint32_t(_mm_movemask_ps(_mm_castsi128_ps(_mm_cmpgt_epi32(pm, _mm_set1_epi32(0x7F7FFFFE)))));
          if ((plain & 0xFu) == 0xFu) {
            mac = vu1gen::kMacSign.word[sgn & 0xFu];
            stf = (sgn & 0xFu) != 0u ? 0x2u : 0u;
          } else {
            float rr[4]; _mm_storeu_ps(rr, rv);
            { uint8_t lf;
              if (plain & 1u) lf = ((sgn >> 0) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[0], (double)_mm_cvtss_f32(av) + (double)_mm_cvtss_f32(vsv) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[0] = vu1gen::normResult(rr[0], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[0][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 2u) lf = ((sgn >> 1) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[1], (double)_mm_cvtss_f32(_mm_shuffle_ps(av, av, _MM_SHUFFLE(1, 1, 1, 1))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(1, 1, 1, 1))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[1] = vu1gen::normResult(rr[1], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[1][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 4u) lf = ((sgn >> 2) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[2], (double)_mm_cvtss_f32(_mm_shuffle_ps(av, av, _MM_SHUFFLE(2, 2, 2, 2))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(2, 2, 2, 2))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[2] = vu1gen::normResult(rr[2], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[2][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 8u) lf = ((sgn >> 3) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[3], (double)_mm_cvtss_f32(_mm_shuffle_ps(av, av, _MM_SHUFFLE(3, 3, 3, 3))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(3, 3, 3, 3))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[3] = vu1gen::normResult(rr[3], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[3][lf & 0xFu]; stf |= lf & 0xFu; }
            rvn = _mm_loadu_ps(rr);
          } }
        if (cx.sticky) stk = vu1gen::sticky4(vsv, bv, product, 0xFu);
        cx.pushFmac(c, mac, stf, stk);
        vu1gen::storeLanes(st.acc, rvn, 0xFu);
      }
      {
        float mf0 = 0.0f; float mf1 = 0.0f; float mf2 = 0.0f; float mf3 = 0.0f;
        { const int32_t v = (int32_t)(int16_t)(st.vi[0] & 0xFFFF); std::memcpy(&mf0, &v, 4); }
        { const int32_t v = (int32_t)(int16_t)(st.vi[0] & 0xFFFF); std::memcpy(&mf1, &v, 4); }
        { const int32_t v = (int32_t)(int16_t)(st.vi[0] & 0xFFFF); std::memcpy(&mf2, &v, 4); }
        { const int32_t v = (int32_t)(int16_t)(st.vi[0] & 0xFFFF); std::memcpy(&mf3, &v, 4); }
        st.vf[11][0] = mf0;
        st.vf[11][1] = mf1;
        st.vf[11][2] = mf2;
        st.vf[11][3] = mf3;
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[11] = rt;
        _mm_store_si128((__m128i *)cx.vfR[11], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L0248:;
    { // pair 73 pc=0x248 up=0x01E0478B lo=0x8000033C
      c = vu1gen::vmax(c, cx.vfRAny[8]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[8]);
        const __m128 bv = _mm_set1_ps(1.0f);
        const __m128 av = vu1gen::nrm4(st.acc);
        const __m128 product = _mm_mul_ps(vsv, bv);
        const __m128 rv = _mm_add_ps(av, product);
        uint32_t mac = 0u, stf = 0u, stk = 0u;
        __m128 rvn = rv;
        { uint32_t sgn; uint32_t plain = vu1gen::classify4(rv, sgn);
          const __m128i pm = _mm_and_si128(_mm_castps_si128(product), _mm_set1_epi32(0x7FFFFFFF));
          plain &= ~uint32_t(_mm_movemask_ps(_mm_castsi128_ps(_mm_cmpgt_epi32(pm, _mm_set1_epi32(0x7F7FFFFE)))));
          if ((plain & 0xFu) == 0xFu) {
            mac = vu1gen::kMacSign.word[sgn & 0xFu];
            stf = (sgn & 0xFu) != 0u ? 0x2u : 0u;
          } else {
            float rr[4]; _mm_storeu_ps(rr, rv);
            { uint8_t lf;
              if (plain & 1u) lf = ((sgn >> 0) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[0], (double)_mm_cvtss_f32(av) + (double)_mm_cvtss_f32(vsv) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[0] = vu1gen::normResult(rr[0], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[0][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 2u) lf = ((sgn >> 1) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[1], (double)_mm_cvtss_f32(_mm_shuffle_ps(av, av, _MM_SHUFFLE(1, 1, 1, 1))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(1, 1, 1, 1))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[1] = vu1gen::normResult(rr[1], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[1][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 4u) lf = ((sgn >> 2) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[2], (double)_mm_cvtss_f32(_mm_shuffle_ps(av, av, _MM_SHUFFLE(2, 2, 2, 2))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(2, 2, 2, 2))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[2] = vu1gen::normResult(rr[2], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[2][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 8u) lf = ((sgn >> 3) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[3], (double)_mm_cvtss_f32(_mm_shuffle_ps(av, av, _MM_SHUFFLE(3, 3, 3, 3))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(3, 3, 3, 3))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[3] = vu1gen::normResult(rr[3], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[3][lf & 0xFu]; stf |= lf & 0xFu; }
            rvn = _mm_loadu_ps(rr);
          } }
        if (cx.sticky) stk = vu1gen::sticky4(vsv, bv, product, 0xFu);
        cx.pushFmac(c, mac, stf, stk);
        urv = rvn;
      }
      bvReg = -1;
      vu1gen::storeLanes(st.vf[30], urv, 0xFu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[30] = rt;
        _mm_store_si128((__m128i *)cx.vfR[30], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L0250:;
    { // pair 74 pc=0x250 up=0x011D0857 lo=0x8000033C
      c = vu1gen::vmax(c, cx.vfR[1][0]);
      c = vu1gen::vmax(c, cx.vfR[29][3]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[1]);
        const __m128 bv = vu1gen::nrmbc(st.vf[29], 3);
        const __m128 rv = _mm_min_ps(vsv, bv);
        urv = rv;
      }
      bvReg = -1;
      vu1gen::storeLanes(st.vf[1], urv, 0x8u);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[1] = rt;
        cx.vfR[1][0] = rt;
      }
      c += 1u;
    }
    L0258:;
    { // pair 75 pc=0x258 up=0x0180FFDC lo=0x8000033C
      c = vu1gen::vmax(c, cx.vfR[31][0]);
      c = vu1gen::vmax(c, cx.vfR[31][1]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      cx.commitQ(c);
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[31]);
        const __m128 bv = _mm_set1_ps(vu1gen::nrm(st.q));
        const __m128 rv = _mm_mul_ps(vsv, bv);
        uint32_t mac = 0u, stf = 0u, stk = 0u;
        __m128 rvn = rv;
        { uint32_t sgn; uint32_t plain = vu1gen::classify4(rv, sgn);
          if ((plain & 0x3u) == 0x3u) {
            mac = vu1gen::kMacSign.word[sgn & 0x3u];
            stf = (sgn & 0x3u) != 0u ? 0x2u : 0u;
          } else {
            float rr[4]; _mm_storeu_ps(rr, rv);
            { uint8_t lf;
              if (plain & 1u) lf = ((sgn >> 0) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[0], (double)_mm_cvtss_f32(vsv) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[0] = vu1gen::normResult(rr[0], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[0][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 2u) lf = ((sgn >> 1) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[1], (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(1, 1, 1, 1))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[1] = vu1gen::normResult(rr[1], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[1][lf & 0xFu]; stf |= lf & 0xFu; }
            rvn = _mm_loadu_ps(rr);
          } }
        cx.pushFmac(c, mac, stf, stk);
        urv = rvn;
      }
      bvReg = -1;
      vu1gen::storeLanes(st.vf[31], urv, 0xCu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[31] = rt;
        cx.vfR[31][0] = rt;
        cx.vfR[31][1] = rt;
      }
      c += 1u;
    }
    L0260:;
    { // pair 76 pc=0x260 up=0x01C04A5C lo=0x100E0000
      c = vu1gen::vmax(c, cx.vfR[9][0]);
      c = vu1gen::vmax(c, cx.vfR[9][1]);
      c = vu1gen::vmax(c, cx.vfR[9][2]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      cx.commitQ(c);
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[9]);
        const __m128 bv = _mm_set1_ps(vu1gen::nrm(st.q));
        const __m128 rv = _mm_mul_ps(vsv, bv);
        uint32_t mac = 0u, stf = 0u, stk = 0u;
        __m128 rvn = rv;
        { uint32_t sgn; uint32_t plain = vu1gen::classify4(rv, sgn);
          if ((plain & 0x7u) == 0x7u) {
            mac = vu1gen::kMacSign.word[sgn & 0x7u];
            stf = (sgn & 0x7u) != 0u ? 0x2u : 0u;
          } else {
            float rr[4]; _mm_storeu_ps(rr, rv);
            { uint8_t lf;
              if (plain & 1u) lf = ((sgn >> 0) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[0], (double)_mm_cvtss_f32(vsv) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[0] = vu1gen::normResult(rr[0], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[0][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 2u) lf = ((sgn >> 1) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[1], (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(1, 1, 1, 1))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[1] = vu1gen::normResult(rr[1], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[1][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 4u) lf = ((sgn >> 2) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[2], (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(2, 2, 2, 2))) * (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[2] = vu1gen::normResult(rr[2], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[2][lf & 0xFu]; stf |= lf & 0xFu; }
            rvn = _mm_loadu_ps(rr);
          } }
        cx.pushFmac(c, mac, stf, stk);
        urv = rvn;
      }
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[0] + 0); bvOld = st.vi[14]; bvReg = 14; st.vi[14] = nv; }
      }
      vu1gen::storeLanes(st.vf[9], urv, 0xEu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[9] = rt;
        cx.vfR[9][0] = rt;
        cx.vfR[9][1] = rt;
        cx.vfR[9][2] = rt;
      }
      c += 1u;
    }
    L0268:;
    { // pair 77 pc=0x268 up=0x01FDF797 lo=0x8000033C
      c = vu1gen::vmax(c, cx.vfRAny[30]);
      c = vu1gen::vmax(c, cx.vfR[29][3]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[30]);
        const __m128 bv = vu1gen::nrmbc(st.vf[29], 3);
        const __m128 rv = _mm_min_ps(vsv, bv);
        urv = rv;
      }
      bvReg = -1;
      vu1gen::storeLanes(st.vf[30], urv, 0xFu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[30] = rt;
        _mm_store_si128((__m128i *)cx.vfR[30], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L0270:;
    { // pair 78 pc=0x270 up=0x0100086B lo=0x8000033C
      c = vu1gen::vmax(c, cx.vfR[1][0]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[1]);
        const __m128 bv = _mm_setr_ps(0.0f, 0.0f, 0.0f, 1.0f);
        const __m128 rv = _mm_max_ps(vsv, bv);
        urv = rv;
      }
      bvReg = -1;
      vu1gen::storeLanes(st.vf[1], urv, 0x8u);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[1] = rt;
        cx.vfR[1][0] = rt;
      }
      c += 1u;
    }
    L0278:;
    { // pair 79 pc=0x278 up=0x018AFFC2 lo=0x8000033C
      c = vu1gen::vmax(c, cx.vfR[31][0]);
      c = vu1gen::vmax(c, cx.vfR[31][1]);
      c = vu1gen::vmax(c, cx.vfR[10][2]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[31]);
        const __m128 bv = vu1gen::nrmbc(st.vf[10], 2);
        const __m128 rv = _mm_add_ps(vsv, bv);
        uint32_t mac = 0u, stf = 0u, stk = 0u;
        __m128 rvn = rv;
        { uint32_t sgn; uint32_t plain = vu1gen::classify4(rv, sgn);
          if ((plain & 0x3u) == 0x3u) {
            mac = vu1gen::kMacSign.word[sgn & 0x3u];
            stf = (sgn & 0x3u) != 0u ? 0x2u : 0u;
          } else {
            float rr[4]; _mm_storeu_ps(rr, rv);
            { uint8_t lf;
              if (plain & 1u) lf = ((sgn >> 0) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[0], (double)_mm_cvtss_f32(vsv) + (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[0] = vu1gen::normResult(rr[0], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[0][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 2u) lf = ((sgn >> 1) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[1], (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(1, 1, 1, 1))) + (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[1] = vu1gen::normResult(rr[1], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[1][lf & 0xFu]; stf |= lf & 0xFu; }
            rvn = _mm_loadu_ps(rr);
          } }
        cx.pushFmac(c, mac, stf, stk);
        urv = rvn;
      }
      bvReg = -1;
      vu1gen::storeLanes(st.vf[31], urv, 0xCu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[31] = rt;
        cx.vfR[31][0] = rt;
        cx.vfR[31][1] = rt;
      }
      c += 1u;
    }
    L0280:;
    { // pair 80 pc=0x280 up=0x01C9582C lo=0x100F00E0
      c = vu1gen::vmax(c, cx.vfR[11][0]);
      c = vu1gen::vmax(c, cx.vfR[11][1]);
      c = vu1gen::vmax(c, cx.vfR[11][2]);
      c = vu1gen::vmax(c, cx.vfR[9][0]);
      c = vu1gen::vmax(c, cx.vfR[9][1]);
      c = vu1gen::vmax(c, cx.vfR[9][2]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[11]);
        const __m128 bv = vu1gen::nrm4(st.vf[9]);
        const __m128 rv = _mm_sub_ps(vsv, bv);
        uint32_t mac = 0u, stf = 0u, stk = 0u;
        __m128 rvn = rv;
        { uint32_t sgn; uint32_t plain = vu1gen::classify4(rv, sgn);
          if ((plain & 0x7u) == 0x7u) {
            mac = vu1gen::kMacSign.word[sgn & 0x7u];
            stf = (sgn & 0x7u) != 0u ? 0x2u : 0u;
          } else {
            float rr[4]; _mm_storeu_ps(rr, rv);
            { uint8_t lf;
              if (plain & 1u) lf = ((sgn >> 0) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[0], (double)_mm_cvtss_f32(vsv) - (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[0] = vu1gen::normResult(rr[0], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[0][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 2u) lf = ((sgn >> 1) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[1], (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(1, 1, 1, 1))) - (double)_mm_cvtss_f32(_mm_shuffle_ps(bv, bv, _MM_SHUFFLE(1, 1, 1, 1))));
              } else {
                uint32_t nf; rr[1] = vu1gen::normResult(rr[1], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[1][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 4u) lf = ((sgn >> 2) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[2], (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(2, 2, 2, 2))) - (double)_mm_cvtss_f32(_mm_shuffle_ps(bv, bv, _MM_SHUFFLE(2, 2, 2, 2))));
              } else {
                uint32_t nf; rr[2] = vu1gen::normResult(rr[2], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[2][lf & 0xFu]; stf |= lf & 0xFu; }
            rvn = _mm_loadu_ps(rr);
          } }
        cx.pushFmac(c, mac, stf, stk);
      }
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[0] + 224); bvOld = st.vi[15]; bvReg = 15; st.vi[15] = nv; }
      }
      c += 1u;
    }
    L0288:;
    { // pair 81 pc=0x288 up=0x01DD482C lo=0x8000033C
      c = vu1gen::vmax(c, cx.vfR[9][0]);
      c = vu1gen::vmax(c, cx.vfR[9][1]);
      c = vu1gen::vmax(c, cx.vfR[9][2]);
      c = vu1gen::vmax(c, cx.vfR[29][0]);
      c = vu1gen::vmax(c, cx.vfR[29][1]);
      c = vu1gen::vmax(c, cx.vfR[29][2]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[9]);
        const __m128 bv = vu1gen::nrm4(st.vf[29]);
        const __m128 rv = _mm_sub_ps(vsv, bv);
        uint32_t mac = 0u, stf = 0u, stk = 0u;
        __m128 rvn = rv;
        { uint32_t sgn; uint32_t plain = vu1gen::classify4(rv, sgn);
          if ((plain & 0x7u) == 0x7u) {
            mac = vu1gen::kMacSign.word[sgn & 0x7u];
            stf = (sgn & 0x7u) != 0u ? 0x2u : 0u;
          } else {
            float rr[4]; _mm_storeu_ps(rr, rv);
            { uint8_t lf;
              if (plain & 1u) lf = ((sgn >> 0) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[0], (double)_mm_cvtss_f32(vsv) - (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[0] = vu1gen::normResult(rr[0], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[0][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 2u) lf = ((sgn >> 1) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[1], (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(1, 1, 1, 1))) - (double)_mm_cvtss_f32(_mm_shuffle_ps(bv, bv, _MM_SHUFFLE(1, 1, 1, 1))));
              } else {
                uint32_t nf; rr[1] = vu1gen::normResult(rr[1], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[1][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 4u) lf = ((sgn >> 2) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[2], (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(2, 2, 2, 2))) - (double)_mm_cvtss_f32(_mm_shuffle_ps(bv, bv, _MM_SHUFFLE(2, 2, 2, 2))));
              } else {
                uint32_t nf; rr[2] = vu1gen::normResult(rr[2], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[2][lf & 0xFu]; stf |= lf & 0xFu; }
            rvn = _mm_loadu_ps(rr);
          } }
        cx.pushFmac(c, mac, stf, stk);
      }
      bvReg = -1;
      c += 1u;
    }
    L0290:;
    { // pair 82 pc=0x290 up=0x0101097D lo=0x8000033C
      c = vu1gen::vmax(c, cx.vfR[1][0]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      float ur0 = 0.0f;
      {
        { const int32_t iv = vu1gen::ftoi(vu1gen::nrm(st.vf[1][0]), 16.0f);
          std::memcpy(&ur0, &iv, 4); }
      }
      bvReg = -1;
      st.vf[1][0] = ur0;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[1] = rt;
        cx.vfR[1][0] = rt;
      }
      c += 1u;
    }
    L0298:;
    { // pair 83 pc=0x298 up=0x01FEF17C lo=0x8000033C
      c = vu1gen::vmax(c, cx.vfRAny[30]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      float ur0 = 0.0f;
      float ur1 = 0.0f;
      float ur2 = 0.0f;
      float ur3 = 0.0f;
      {
        { const int32_t iv = vu1gen::ftoi(vu1gen::nrm(st.vf[30][0]), 1.0f);
          std::memcpy(&ur0, &iv, 4); }
        { const int32_t iv = vu1gen::ftoi(vu1gen::nrm(st.vf[30][1]), 1.0f);
          std::memcpy(&ur1, &iv, 4); }
        { const int32_t iv = vu1gen::ftoi(vu1gen::nrm(st.vf[30][2]), 1.0f);
          std::memcpy(&ur2, &iv, 4); }
        { const int32_t iv = vu1gen::ftoi(vu1gen::nrm(st.vf[30][3]), 1.0f);
          std::memcpy(&ur3, &iv, 4); }
      }
      bvReg = -1;
      st.vf[30][0] = ur0;
      st.vf[30][1] = ur1;
      st.vf[30][2] = ur2;
      st.vf[30][3] = ur3;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[30] = rt;
        _mm_store_si128((__m128i *)cx.vfR[30], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L02A0:;
    { // pair 84 pc=0x2A0 up=0x01E9497D lo=0x340C7800
      c = vu1gen::vmax(c, cx.vfRAny[9]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      float ur0 = 0.0f;
      float ur1 = 0.0f;
      float ur2 = 0.0f;
      float ur3 = 0.0f;
      {
        { const int32_t iv = vu1gen::ftoi(vu1gen::nrm(st.vf[9][0]), 16.0f);
          std::memcpy(&ur0, &iv, 4); }
        { const int32_t iv = vu1gen::ftoi(vu1gen::nrm(st.vf[9][1]), 16.0f);
          std::memcpy(&ur1, &iv, 4); }
        { const int32_t iv = vu1gen::ftoi(vu1gen::nrm(st.vf[9][2]), 16.0f);
          std::memcpy(&ur2, &iv, 4); }
        { const int32_t iv = vu1gen::ftoi(vu1gen::nrm(st.vf[9][3]), 16.0f);
          std::memcpy(&ur3, &iv, 4); }
      }
      {
        cx.commitQ(c); cx.drainFlags(c);
        st.vi[12] = (int32_t)(st.mac & (uint32_t)(uint16_t)st.vi[15]);
      }
      bvReg = -1;
      st.vf[9][0] = ur0;
      st.vf[9][1] = ur1;
      st.vf[9][2] = ur2;
      st.vf[9][3] = ur3;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[9] = rt;
        _mm_store_si128((__m128i *)cx.vfR[9], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L02A8:;
    { // pair 85 pc=0x2A8 up=0x004007C3 lo=0x340C6000
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = _mm_setr_ps(0.0f, 0.0f, 0.0f, 1.0f);
        const __m128 bv = _mm_set1_ps(1.0f);
        const __m128 rv = _mm_add_ps(vsv, bv);
        uint32_t mac = 0u, stf = 0u, stk = 0u;
        __m128 rvn = rv;
        { uint32_t sgn; uint32_t plain = vu1gen::classify4(rv, sgn);
          if ((plain & 0x4u) == 0x4u) {
            mac = vu1gen::kMacSign.word[sgn & 0x4u];
            stf = (sgn & 0x4u) != 0u ? 0x2u : 0u;
          } else {
            float rr[4]; _mm_storeu_ps(rr, rv);
            { uint8_t lf;
              if (plain & 4u) lf = ((sgn >> 2) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[2], (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(2, 2, 2, 2))) + (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[2] = vu1gen::normResult(rr[2], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[2][lf & 0xFu]; stf |= lf & 0xFu; }
            rvn = _mm_loadu_ps(rr);
          } }
        cx.pushFmac(c, mac, stf, stk);
        urv = rvn;
      }
      {
        cx.commitQ(c); cx.drainFlags(c);
        st.vi[12] = (int32_t)(st.mac & (uint32_t)(uint16_t)st.vi[12]);
      }
      bvReg = -1;
      vu1gen::storeLanes(st.vf[31], urv, 0x2u);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[31] = rt;
        cx.vfR[31][2] = rt;
      }
      c += 1u;
    }
    L02B0:;
    { // pair 86 pc=0x2B0 up=0x000002FF lo=0x800E0BFC
      c = vu1gen::vmax(c, cx.vfR[1][0]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { uint32_t fv = 0u; std::memcpy(&fv, &st.vf[1][0], 4);
          bvOld = st.vi[14]; bvReg = 14;
          st.vi[14] = (int32_t)(int16_t)(fv & 0xFFFFu);
        }
      }
      c += 1u;
    }
    L02B8:;
    { const bool bt = (int16_t)(bvReg == 12 ? bvOld : st.vi[12]) == (int16_t)(bvReg == 15 ? bvOld : st.vi[15]);
    { // pair 87 pc=0x2B8 up=0x000002FF lo=0x500F6002
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    { // pair 88 pc=0x2C0 up=0x000002FF lo=0x803E2BFD
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        float mf3 = 0.0f;
        { const int32_t v = (int32_t)(int16_t)(st.vi[5] & 0xFFFF); std::memcpy(&mf3, &v, 4); }
        st.vf[30][3] = mf3;
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[30] = rt;
        cx.vfR[30][3] = rt;
      }
      c += 1u;
    }
    if (bt) {
      st.branchTarget = 0x2D0u;
      goto L02D0;
    } }
    goto LC02C8;
    L02C0:;
    { // pair 88 pc=0x2C0 up=0x000002FF lo=0x803E2BFD
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        float mf3 = 0.0f;
        { const int32_t v = (int32_t)(int16_t)(st.vi[5] & 0xFFFF); std::memcpy(&mf3, &v, 4); }
        st.vf[30][3] = mf3;
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[30] = rt;
        cx.vfR[30][3] = rt;
      }
      c += 1u;
    }
    LC02C8:;
    L02C8:;
    { // pair 89 pc=0x2C8 up=0x000002FF lo=0x800773B0
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[14] + st.vi[7]); bvOld = st.vi[14]; bvReg = 14; st.vi[14] = nv; }
      }
      c += 1u;
    }
    L02D0:;
    { // pair 90 pc=0x2D0 up=0x000002FF lo=0x802973FD
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        float mf3 = 0.0f;
        { const int32_t v = (int32_t)(int16_t)(st.vi[14] & 0xFFFF); std::memcpy(&mf3, &v, 4); }
        st.vf[9][3] = mf3;
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[9] = rt;
        cx.vfR[9][3] = rt;
      }
      c += 1u;
    }
    L02D8:;
    { // pair 91 pc=0x2D8 up=0x000002FF lo=0x81E6FB7D
      c = vu1gen::vmax(c, cx.vfRAny[31]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(uint16_t)st.vi[6] * 16u) & 0xFFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[31][0], 16);
        }
        { const int32_t nv = (int32_t)(int16_t)(st.vi[6] + 1); bvOld = st.vi[6]; bvReg = 6; st.vi[6] = nv; }
      }
      c += 1u;
    }
    L02E0:;
    { // pair 92 pc=0x2E0 up=0x000002FF lo=0x81E6F37D
      c = vu1gen::vmax(c, cx.vfRAny[30]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(uint16_t)st.vi[6] * 16u) & 0xFFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[30][0], 16);
        }
        { const int32_t nv = (int32_t)(int16_t)(st.vi[6] + 1); bvOld = st.vi[6]; bvReg = 6; st.vi[6] = nv; }
      }
      c += 1u;
    }
    L02E8:;
    { const bool bt = (int16_t)(bvReg == 1 ? bvOld : st.vi[1]) > 0;
    { // pair 93 pc=0x2E8 up=0x000002FF lo=0x5A000FA8
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    { // pair 94 pc=0x2F0 up=0x000002FF lo=0x81E64B7D
      c = vu1gen::vmax(c, cx.vfRAny[9]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(uint16_t)st.vi[6] * 16u) & 0xFFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[9][0], 16);
        }
        { const int32_t nv = (int32_t)(int16_t)(st.vi[6] + 1); bvOld = st.vi[6]; bvReg = 6; st.vi[6] = nv; }
      }
      c += 1u;
    }
    if (bt) {
      st.branchTarget = 0x30u;
      if (c >= (uint64_t)a.maxCycles) { st.pc = 0x30u; goto BUDGET_OUT; }
      goto L0030;
    } }
    goto LC02F8;
    L02F0:;
    { // pair 94 pc=0x2F0 up=0x000002FF lo=0x81E64B7D
      c = vu1gen::vmax(c, cx.vfRAny[9]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(uint16_t)st.vi[6] * 16u) & 0xFFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[9][0], 16);
        }
        { const int32_t nv = (int32_t)(int16_t)(st.vi[6] + 1); bvOld = st.vi[6]; bvReg = 6; st.vi[6] = nv; }
      }
      c += 1u;
    }
    LC02F8:;
    L02F8:;
    { // pair 95 pc=0x2F8 up=0x400002FF lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    { // pair 96 pc=0x300 up=0x000002FF lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    st.pc = 0x308u; goto END_OUT;
    L0300:;
    { // pair 96 pc=0x300 up=0x000002FF lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    st.pc = 0x308u; goto HAND_OUT;

DISPATCH:
    if (c >= (uint64_t)a.maxCycles) { st.pc = jt; goto BUDGET_OUT; }
    switch (jt)
    {
    case 0x0u: goto L0000;
    case 0x8u: goto L0008;
    case 0x10u: goto L0010;
    case 0x18u: goto L0018;
    case 0x20u: goto L0020;
    case 0x28u: goto L0028;
    case 0x30u: goto L0030;
    case 0x38u: goto L0038;
    case 0x40u: goto L0040;
    case 0x48u: goto L0048;
    case 0x50u: goto L0050;
    case 0x58u: goto L0058;
    case 0x60u: goto L0060;
    case 0x68u: goto L0068;
    case 0x70u: goto L0070;
    case 0x78u: goto L0078;
    case 0x80u: goto L0080;
    case 0x88u: goto L0088;
    case 0x90u: goto L0090;
    case 0x98u: goto L0098;
    case 0xA0u: goto L00A0;
    case 0xA8u: goto L00A8;
    case 0xB0u: goto L00B0;
    case 0xB8u: goto L00B8;
    case 0xC0u: goto L00C0;
    case 0xC8u: goto L00C8;
    case 0xD0u: goto L00D0;
    case 0xD8u: goto L00D8;
    case 0xE0u: goto L00E0;
    case 0xE8u: goto L00E8;
    case 0xF0u: goto L00F0;
    case 0xF8u: goto L00F8;
    case 0x100u: goto L0100;
    case 0x108u: goto L0108;
    case 0x110u: goto L0110;
    case 0x118u: goto L0118;
    case 0x120u: goto L0120;
    case 0x128u: goto L0128;
    case 0x130u: goto L0130;
    case 0x138u: goto L0138;
    case 0x140u: goto L0140;
    case 0x148u: goto L0148;
    case 0x150u: goto L0150;
    case 0x158u: goto L0158;
    case 0x160u: goto L0160;
    case 0x168u: goto L0168;
    case 0x170u: goto L0170;
    case 0x178u: goto L0178;
    case 0x180u: goto L0180;
    case 0x188u: goto L0188;
    case 0x190u: goto L0190;
    case 0x198u: goto L0198;
    case 0x1A0u: goto L01A0;
    case 0x1A8u: goto L01A8;
    case 0x1B0u: goto L01B0;
    case 0x1B8u: goto L01B8;
    case 0x1C0u: goto L01C0;
    case 0x1C8u: goto L01C8;
    case 0x1D0u: goto L01D0;
    case 0x1D8u: goto L01D8;
    case 0x1E0u: goto L01E0;
    case 0x1E8u: goto L01E8;
    case 0x1F0u: goto L01F0;
    case 0x1F8u: goto L01F8;
    case 0x200u: goto L0200;
    case 0x208u: goto L0208;
    case 0x210u: goto L0210;
    case 0x218u: goto L0218;
    case 0x220u: goto L0220;
    case 0x228u: goto L0228;
    case 0x230u: goto L0230;
    case 0x238u: goto L0238;
    case 0x240u: goto L0240;
    case 0x248u: goto L0248;
    case 0x250u: goto L0250;
    case 0x258u: goto L0258;
    case 0x260u: goto L0260;
    case 0x268u: goto L0268;
    case 0x270u: goto L0270;
    case 0x278u: goto L0278;
    case 0x280u: goto L0280;
    case 0x288u: goto L0288;
    case 0x290u: goto L0290;
    case 0x298u: goto L0298;
    case 0x2A0u: goto L02A0;
    case 0x2A8u: goto L02A8;
    case 0x2B0u: goto L02B0;
    case 0x2B8u: goto L02B8;
    case 0x2C0u: goto L02C0;
    case 0x2C8u: goto L02C8;
    case 0x2D0u: goto L02D0;
    case 0x2D8u: goto L02D8;
    case 0x2E0u: goto L02E0;
    case 0x2E8u: goto L02E8;
    case 0x2F0u: goto L02F0;
    case 0x2F8u: goto L02F8;
    case 0x300u: goto L0300;
    default: st.pc = jt; goto HAND_OUT;
    }

END_OUT:
    a.branchReg = bvReg; a.branchOld = bvOld;
    cx.flush(c);
    if (cx.kickInvalid) return kVu1ProgHandOff;
    st.ebit = false;
    st.haltAfterDelaySlot = false;
    st.cycles += c;
    return kVu1ProgRan;

BUDGET_OUT:
    return kVu1ProgHandOff;

HAND_OUT:
    return kVu1ProgHandOff;
}
