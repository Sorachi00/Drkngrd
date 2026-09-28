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

int ps2Vu1Prog_513B4D4A44BE8C92(Vu1ProgArgs &a)
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
    case 0x308u:
    case 0x310u:
    case 0x318u:
    case 0x320u:
    case 0x328u:
    case 0x330u:
    case 0x338u:
    case 0x340u:
    case 0x348u:
    case 0x350u:
    case 0x358u:
    case 0x360u:
    case 0x368u:
    case 0x370u:
    case 0x378u:
    case 0x380u:
    case 0x388u:
    case 0x390u:
    case 0x398u:
    case 0x3A0u:
    case 0x3A8u:
    case 0x3B0u:
    case 0x3B8u:
    case 0x3C0u:
    case 0x3C8u:
    case 0x3D0u:
    case 0x3D8u:
    case 0x3E0u:
    case 0x3E8u:
    case 0x3F0u:
    case 0x3F8u:
    case 0x400u:
    case 0x408u:
    case 0x410u:
    case 0x418u:
    case 0x420u:
    case 0x428u:
    case 0x430u:
    case 0x438u:
        break;
    default:
        return kVu1ProgNoEntry;
    }

    VU1State &st = *a.state;
    uint8_t *vm = a.vuData;
    vu1gen::RunCtx cx;
    cx.init(st, true, true);
    cx.vm = vm; cx.undo = a.undo; cx.kickBuffer = s_kickBuf; cx.gs = a.gs; cx.memory = a.memory;
    st.pc = a.startPC & 0x3FFFu;
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
    case 0x308u: goto L0308;
    case 0x310u: goto L0310;
    case 0x318u: goto L0318;
    case 0x320u: goto L0320;
    case 0x328u: goto L0328;
    case 0x330u: goto L0330;
    case 0x338u: goto L0338;
    case 0x340u: goto L0340;
    case 0x348u: goto L0348;
    case 0x350u: goto L0350;
    case 0x358u: goto L0358;
    case 0x360u: goto L0360;
    case 0x368u: goto L0368;
    case 0x370u: goto L0370;
    case 0x378u: goto L0378;
    case 0x380u: goto L0380;
    case 0x388u: goto L0388;
    case 0x390u: goto L0390;
    case 0x398u: goto L0398;
    case 0x3A0u: goto L03A0;
    case 0x3A8u: goto L03A8;
    case 0x3B0u: goto L03B0;
    case 0x3B8u: goto L03B8;
    case 0x3C0u: goto L03C0;
    case 0x3C8u: goto L03C8;
    case 0x3D0u: goto L03D0;
    case 0x3D8u: goto L03D8;
    case 0x3E0u: goto L03E0;
    case 0x3E8u: goto L03E8;
    case 0x3F0u: goto L03F0;
    case 0x3F8u: goto L03F8;
    case 0x400u: goto L0400;
    case 0x408u: goto L0408;
    case 0x410u: goto L0410;
    case 0x418u: goto L0418;
    case 0x420u: goto L0420;
    case 0x428u: goto L0428;
    case 0x430u: goto L0430;
    case 0x438u: goto L0438;
    default: return kVu1ProgNoEntry;
    }

    L0000:;
    { // pair 0 pc=0x0 up=0x400002FF lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    { // pair 1 pc=0x8 up=0x000002FF lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    st.pc = 0x10u; goto END_OUT;
    L0008:;
    { // pair 1 pc=0x8 up=0x000002FF lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    L0010:;
    st.branchTarget = 0x50u;
    { // pair 2 pc=0x10 up=0x000002FF lo=0x40000007
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    { // pair 3 pc=0x18 up=0x000002FF lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    goto L0050;
    L0018:;
    { // pair 3 pc=0x18 up=0x000002FF lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    L0020:;
    st.branchTarget = 0xB8u;
    { // pair 4 pc=0x20 up=0x000002FF lo=0x40000012
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    { // pair 5 pc=0x28 up=0x000002FF lo=0x0901038D
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 909) * 16u) & 0x3FFFu;
          uint32_t v = 0u; std::memcpy(&v, vm + addr + 0u, 4);
          st.vi[1] = (int32_t)(int16_t)(v & 0xFFFFu);
        }
      }
      bvReg = -1;
      cx.viR[1] = (uint32_t)(c + 4u);
      c += 1u;
    }
    goto L00B8;
    L0028:;
    { // pair 5 pc=0x28 up=0x000002FF lo=0x0901038D
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 909) * 16u) & 0x3FFFu;
          uint32_t v = 0u; std::memcpy(&v, vm + addr + 0u, 4);
          st.vi[1] = (int32_t)(int16_t)(v & 0xFFFFu);
        }
      }
      bvReg = -1;
      cx.viR[1] = (uint32_t)(c + 4u);
      c += 1u;
    }
    L0030:;
    st.branchTarget = 0x1C8u;
    { // pair 6 pc=0x30 up=0x000002FF lo=0x40000032
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    { // pair 7 pc=0x38 up=0x000002FF lo=0x0881038D
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 909) * 16u) & 0x3FFFu;
          uint32_t v = 0u; std::memcpy(&v, vm + addr + 4u, 4);
          st.vi[1] = (int32_t)(int16_t)(v & 0xFFFFu);
        }
      }
      bvReg = -1;
      cx.viR[1] = (uint32_t)(c + 4u);
      c += 1u;
    }
    goto L01C8;
    L0038:;
    { // pair 7 pc=0x38 up=0x000002FF lo=0x0881038D
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 909) * 16u) & 0x3FFFu;
          uint32_t v = 0u; std::memcpy(&v, vm + addr + 4u, 4);
          st.vi[1] = (int32_t)(int16_t)(v & 0xFFFFu);
        }
      }
      bvReg = -1;
      cx.viR[1] = (uint32_t)(c + 4u);
      c += 1u;
    }
    L0040:;
    st.branchTarget = 0x2E0u;
    { // pair 8 pc=0x40 up=0x000002FF lo=0x40000053
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    { // pair 9 pc=0x48 up=0x000002FF lo=0x0841038D
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 909) * 16u) & 0x3FFFu;
          uint32_t v = 0u; std::memcpy(&v, vm + addr + 8u, 4);
          st.vi[1] = (int32_t)(int16_t)(v & 0xFFFFu);
        }
      }
      bvReg = -1;
      cx.viR[1] = (uint32_t)(c + 4u);
      c += 1u;
    }
    goto L02E0;
    L0048:;
    { // pair 9 pc=0x48 up=0x000002FF lo=0x0841038D
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 909) * 16u) & 0x3FFFu;
          uint32_t v = 0u; std::memcpy(&v, vm + addr + 8u, 4);
          st.vi[1] = (int32_t)(int16_t)(v & 0xFFFFu);
        }
      }
      bvReg = -1;
      cx.viR[1] = (uint32_t)(c + 4u);
      c += 1u;
    }
    L0050:;
    { // pair 10 pc=0x50 up=0x000002FF lo=0x10010387
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[0] + 903); bvOld = st.vi[1]; bvReg = 1; st.vi[1] = nv; }
      }
      cx.viR[1] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L0058:;
    { // pair 11 pc=0x58 up=0x000002FF lo=0x088D0390
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 912) * 16u) & 0x3FFFu;
          uint32_t v = 0u; std::memcpy(&v, vm + addr + 4u, 4);
          st.vi[13] = (int32_t)(int16_t)(v & 0xFFFFu);
        }
      }
      bvReg = -1;
      cx.viR[13] = (uint32_t)(c + 4u);
      c += 1u;
    }
    L0060:;
    { // pair 12 pc=0x60 up=0x000002FF lo=0x100E03D3
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[0] + 979); bvOld = st.vi[14]; bvReg = 14; st.vi[14] = nv; }
      }
      c += 1u;
    }
    L0068:;
    { // pair 13 pc=0x68 up=0x000002FF lo=0x007A0391
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 913) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[26][2], vm + addr + 8u, 8);
        }
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[26] = rt;
        cx.vfR[26][2] = rt;
        cx.vfR[26][3] = rt;
      }
      c += 1u;
    }
    L0070:;
    { // pair 14 pc=0x70 up=0x000002FF lo=0x01D70395
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 917) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[23][0], vm + addr + 0u, 12);
        }
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[23] = rt;
        cx.vfR[23][0] = rt;
        cx.vfR[23][1] = rt;
        cx.vfR[23][2] = rt;
      }
      c += 1u;
    }
    L0078:;
    { // pair 15 pc=0x78 up=0x000002FF lo=0x01F803AC
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 940) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[24][0], vm + addr + 0u, 16);
        }
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[24] = rt;
        _mm_store_si128((__m128i *)cx.vfR[24], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L0080:;
    { // pair 16 pc=0x80 up=0x000002FF lo=0x01FB038E
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 910) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[27][0], vm + addr + 0u, 16);
        }
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[27] = rt;
        _mm_store_si128((__m128i *)cx.vfR[27], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L0088:;
    { // pair 17 pc=0x88 up=0x003A065A lo=0x01FC0800
      c = vu1gen::vmax(c, cx.vfR[26][2]);
      c = vu1gen::vmax(c, cx.viR[1]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = _mm_setr_ps(0.0f, 0.0f, 0.0f, 1.0f);
        const __m128 bv = vu1gen::nrmbc(st.vf[26], 2);
        const __m128 rv = _mm_mul_ps(vsv, bv);
        uint32_t mac = 0u, stf = 0u, stk = 0u;
        __m128 rvn = rv;
        { uint32_t sgn; uint32_t plain = vu1gen::classify4(rv, sgn);
          if ((plain & 0x8u) == 0x8u) {
            mac = vu1gen::kMacSign.word[sgn & 0x8u];
            stf = (sgn & 0x8u) != 0u ? 0x2u : 0u;
          } else {
            float rr[4]; _mm_storeu_ps(rr, rv);
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
        urv = rvn;
      }
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[1] + 0) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[28][0], vm + addr + 0u, 16);
        }
      }
      bvReg = -1;
      vu1gen::storeLanes(st.vf[25], urv, 0x1u);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[25] = rt;
        cx.vfR[25][3] = rt;
      }
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[28] = rt;
        _mm_store_si128((__m128i *)cx.vfR[28], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L0090:;
    { // pair 18 pc=0x90 up=0x01D7B93D lo=0x01DA038C
      c = vu1gen::vmax(c, cx.vfR[23][0]);
      c = vu1gen::vmax(c, cx.vfR[23][1]);
      c = vu1gen::vmax(c, cx.vfR[23][2]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      float ur0 = 0.0f;
      float ur1 = 0.0f;
      float ur2 = 0.0f;
      {
        { int32_t iv; std::memcpy(&iv, &st.vf[23][0], 4);
          ur0 = static_cast<float>(iv) / 16.0f; }
        { int32_t iv; std::memcpy(&iv, &st.vf[23][1], 4);
          ur1 = static_cast<float>(iv) / 16.0f; }
        { int32_t iv; std::memcpy(&iv, &st.vf[23][2], 4);
          ur2 = static_cast<float>(iv) / 16.0f; }
      }
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 908) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[26][0], vm + addr + 0u, 12);
        }
      }
      bvReg = -1;
      st.vf[23][0] = ur0;
      st.vf[23][1] = ur1;
      st.vf[23][2] = ur2;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[23] = rt;
        cx.vfR[23][0] = rt;
        cx.vfR[23][1] = rt;
        cx.vfR[23][2] = rt;
      }
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[26] = rt;
        cx.vfR[26][0] = rt;
        cx.vfR[26][1] = rt;
        cx.vfR[26][2] = rt;
      }
      c += 1u;
    }
    L0098:;
    { // pair 19 pc=0x98 up=0x000002FF lo=0x01FD0801
      c = vu1gen::vmax(c, cx.viR[1]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[1] + 1) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[29][0], vm + addr + 0u, 16);
        }
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[29] = rt;
        _mm_store_si128((__m128i *)cx.vfR[29], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L00A0:;
    { // pair 20 pc=0xA0 up=0x000002FF lo=0x01FE0802
      c = vu1gen::vmax(c, cx.viR[1]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[1] + 2) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[30][0], vm + addr + 0u, 16);
        }
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[30] = rt;
        _mm_store_si128((__m128i *)cx.vfR[30], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L00A8:;
    { // pair 21 pc=0xA8 up=0x400002FF lo=0x01FF0803
      c = vu1gen::vmax(c, cx.viR[1]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[1] + 3) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[31][0], vm + addr + 0u, 16);
        }
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[31] = rt;
        _mm_store_si128((__m128i *)cx.vfR[31], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    { // pair 22 pc=0xB0 up=0x000002FF lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    st.pc = 0xB8u; goto END_OUT;
    L00B0:;
    { // pair 22 pc=0xB0 up=0x000002FF lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    L00B8:;
    { // pair 23 pc=0xB8 up=0x000002FF lo=0x800806BC
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        st.vi[8] = (int32_t)(st.top & 0x3FFu);
      }
      bvReg = -1;
      c += 1u;
    }
    L00C0:;
    { // pair 24 pc=0xC0 up=0x000002FF lo=0x08224127
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[8] + 295) * 16u) & 0x3FFFu;
          uint32_t v = 0u; std::memcpy(&v, vm + addr + 12u, 4);
          st.vi[2] = (int32_t)(int16_t)(v & 0xFFFFu);
        }
      }
      bvReg = -1;
      cx.viR[2] = (uint32_t)(c + 4u);
      c += 1u;
    }
    L00C8:;
    { // pair 25 pc=0xC8 up=0x000002FF lo=0x10830000
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[0] + 8192); bvOld = st.vi[3]; bvReg = 3; st.vi[3] = nv; }
      }
      c += 1u;
    }
    L00D0:;
    { const bool bt = (int16_t)0 == (int16_t)(bvReg == 1 ? bvOld : st.vi[1]);
    { // pair 26 pc=0xD0 up=0x000002FF lo=0x50010005
      c = vu1gen::vmax(c, cx.viR[1]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    { // pair 27 pc=0xD8 up=0x000002FF lo=0x009603CF
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 975) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[22][1], vm + addr + 4u, 4);
        }
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[22] = rt;
        cx.vfR[22][1] = rt;
      }
      c += 1u;
    }
    if (bt) {
      st.branchTarget = 0x100u;
      goto L0100;
    } }
    goto LC00E0;
    L00D8:;
    { // pair 27 pc=0xD8 up=0x000002FF lo=0x009603CF
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 975) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[22][1], vm + addr + 4u, 4);
        }
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[22] = rt;
        cx.vfR[22][1] = rt;
      }
      c += 1u;
    }
    LC00E0:;
    L00E0:;
    { // pair 28 pc=0xE0 up=0x000002FF lo=0x800310F4
      c = vu1gen::vmax(c, cx.viR[2]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[2] & st.vi[3]); bvOld = st.vi[3]; bvReg = 3; st.vi[3] = nv; }
      }
      c += 1u;
    }
    L00E8:;
    { // pair 29 pc=0xE8 up=0x000002FF lo=0x01E103A6
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 934) * 16u) & 0x3FFFu;
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
    L00F0:;
    { const bool bt = (int16_t)0 == (int16_t)(bvReg == 3 ? bvOld : st.vi[3]);
    { // pair 30 pc=0xF0 up=0x000002FF lo=0x50030003
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    { // pair 31 pc=0xF8 up=0x000002FF lo=0x01E203AA
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 938) * 16u) & 0x3FFFu;
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
    if (bt) {
      st.branchTarget = 0x110u;
      goto L0110;
    } }
    goto LC0100;
    L00F8:;
    { // pair 31 pc=0xF8 up=0x000002FF lo=0x01E203AA
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 938) * 16u) & 0x3FFFu;
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
    LC0100:;
    L0100:;
    { // pair 32 pc=0x100 up=0x400002FF lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    { // pair 33 pc=0x108 up=0x000002FF lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    st.pc = 0x110u; goto END_OUT;
    L0108:;
    { // pair 33 pc=0x108 up=0x000002FF lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    L0110:;
    { // pair 34 pc=0x110 up=0x000002FF lo=0x100940FA
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[8] + 250); bvOld = st.vi[9]; bvReg = 9; st.vi[9] = nv; }
      }
      c += 1u;
    }
    L0118:;
    { // pair 35 pc=0x118 up=0x000002FF lo=0x10084127
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[8] + 295); bvOld = st.vi[8]; bvReg = 8; st.vi[8] = nv; }
      }
      c += 1u;
    }
    L0120:;
    { // pair 36 pc=0x120 up=0x000002FF lo=0x090A4004
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[8] + 4) * 16u) & 0x3FFFu;
          uint32_t v = 0u; std::memcpy(&v, vm + addr + 0u, 4);
          st.vi[10] = (int32_t)(int16_t)(v & 0xFFFFu);
        }
      }
      bvReg = -1;
      cx.viR[10] = (uint32_t)(c + 4u);
      c += 1u;
    }
    L0128:;
    { // pair 37 pc=0x128 up=0x000002FF lo=0x81D54B7C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(uint16_t)st.vi[9] * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[21][0], vm + addr + 0u, 12);
        }
        { const int32_t nv = (int32_t)(int16_t)(st.vi[9] + 1); bvOld = st.vi[9]; bvReg = 9; st.vi[9] = nv; }
      }
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[21] = rt;
        cx.vfR[21][0] = rt;
        cx.vfR[21][1] = rt;
        cx.vfR[21][2] = rt;
      }
      c += 1u;
    }
    L0130:;
    { // pair 38 pc=0x130 up=0x000002FF lo=0x03E80802
      c = vu1gen::vmax(c, cx.vfRAny[1]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[8] + 2) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[1][0], 16);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L0138:;
    { // pair 39 pc=0x138 up=0x000002FF lo=0x03E81003
      c = vu1gen::vmax(c, cx.vfRAny[2]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[8] + 3) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[2][0], 16);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L0140:;
    { // pair 40 pc=0x140 up=0x000002FF lo=0x0288B004
      c = vu1gen::vmax(c, cx.vfR[22][1]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[8] + 4) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 4u, &st.vf[22][1], 4);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L0148:;
    { // pair 41 pc=0x148 up=0x01D4A97C lo=0x11EC07FF
      c = vu1gen::vmax(c, cx.vfR[21][0]);
      c = vu1gen::vmax(c, cx.vfR[21][1]);
      c = vu1gen::vmax(c, cx.vfR[21][2]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      float ur0 = 0.0f;
      float ur1 = 0.0f;
      float ur2 = 0.0f;
      {
        { const int32_t iv = vu1gen::ftoi(vu1gen::nrm(st.vf[21][0]), 1.0f);
          std::memcpy(&ur0, &iv, 4); }
        { const int32_t iv = vu1gen::ftoi(vu1gen::nrm(st.vf[21][1]), 1.0f);
          std::memcpy(&ur1, &iv, 4); }
        { const int32_t iv = vu1gen::ftoi(vu1gen::nrm(st.vf[21][2]), 1.0f);
          std::memcpy(&ur2, &iv, 4); }
      }
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[0] + 32767); bvOld = st.vi[12]; bvReg = 12; st.vi[12] = nv; }
      }
      st.vf[20][0] = ur0;
      st.vf[20][1] = ur1;
      st.vf[20][2] = ur2;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[20] = rt;
        cx.vfR[20][0] = rt;
        cx.vfR[20][1] = rt;
        cx.vfR[20][2] = rt;
      }
      c += 1u;
    }
    L0150:;
    { // pair 42 pc=0x150 up=0x000002FF lo=0x800C52B4
      c = vu1gen::vmax(c, cx.viR[10]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[10] & st.vi[12]); bvOld = st.vi[10]; bvReg = 10; st.vi[10] = nv; }
      }
      cx.viR[10] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L0158:;
    { // pair 43 pc=0x158 up=0x000002FF lo=0x100B4005
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[8] + 5); bvOld = st.vi[11]; bvReg = 11; st.vi[11] = nv; }
      }
      c += 1u;
    }
    L0160:;
    { // pair 44 pc=0x160 up=0x000002FF lo=0x81D54B7C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(uint16_t)st.vi[9] * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[21][0], vm + addr + 0u, 12);
        }
        { const int32_t nv = (int32_t)(int16_t)(st.vi[9] + 1); bvOld = st.vi[9]; bvReg = 9; st.vi[9] = nv; }
      }
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[21] = rt;
        cx.vfR[21][0] = rt;
        cx.vfR[21][1] = rt;
        cx.vfR[21][2] = rt;
      }
      c += 1u;
    }
    L0168:;
    { // pair 45 pc=0x168 up=0x000002FF lo=0x09015803
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[11] + 3) * 16u) & 0x3FFFu;
          uint32_t v = 0u; std::memcpy(&v, vm + addr + 0u, 4);
          st.vi[1] = (int32_t)(int16_t)(v & 0xFFFFu);
        }
      }
      bvReg = -1;
      cx.viR[1] = (uint32_t)(c + 4u);
      c += 1u;
    }
    L0170:;
    { // pair 46 pc=0x170 up=0x000002FF lo=0x120A5001
      c = vu1gen::vmax(c, cx.viR[10]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[10] - 1); bvOld = st.vi[10]; bvReg = 10; st.vi[10] = nv; }
      }
      cx.viR[10] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L0178:;
    { // pair 47 pc=0x178 up=0x000002FF lo=0x100B5803
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[11] + 3); bvOld = st.vi[11]; bvReg = 11; st.vi[11] = nv; }
      }
      c += 1u;
    }
    L0180:;
    { const bool bt = (int16_t)(bvReg == 10 ? bvOld : st.vi[10]) > 0;
    { // pair 48 pc=0x180 up=0x000002FF lo=0x5A0057FB
      c = vu1gen::vmax(c, cx.viR[10]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    { // pair 49 pc=0x188 up=0x01D4A97C lo=0x03CBA7FE
      c = vu1gen::vmax(c, cx.vfR[21][0]);
      c = vu1gen::vmax(c, cx.vfR[21][1]);
      c = vu1gen::vmax(c, cx.vfR[21][2]);
      c = vu1gen::vmax(c, cx.vfR[20][0]);
      c = vu1gen::vmax(c, cx.vfR[20][1]);
      c = vu1gen::vmax(c, cx.vfR[20][2]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      float ur0 = 0.0f;
      float ur1 = 0.0f;
      float ur2 = 0.0f;
      {
        { const int32_t iv = vu1gen::ftoi(vu1gen::nrm(st.vf[21][0]), 1.0f);
          std::memcpy(&ur0, &iv, 4); }
        { const int32_t iv = vu1gen::ftoi(vu1gen::nrm(st.vf[21][1]), 1.0f);
          std::memcpy(&ur1, &iv, 4); }
        { const int32_t iv = vu1gen::ftoi(vu1gen::nrm(st.vf[21][2]), 1.0f);
          std::memcpy(&ur2, &iv, 4); }
      }
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[11] + -2) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[20][0], 12);
        }
      }
      bvReg = -1;
      st.vf[20][0] = ur0;
      st.vf[20][1] = ur1;
      st.vf[20][2] = ur2;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[20] = rt;
        cx.vfR[20][0] = rt;
        cx.vfR[20][1] = rt;
        cx.vfR[20][2] = rt;
      }
      c += 1u;
    }
    if (bt) {
      st.branchTarget = 0x160u;
      if (c >= (uint64_t)a.maxCycles) { st.pc = 0x160u; goto BUDGET_OUT; }
      goto L0160;
    } }
    goto LC0190;
    L0188:;
    { // pair 49 pc=0x188 up=0x01D4A97C lo=0x03CBA7FE
      c = vu1gen::vmax(c, cx.vfR[21][0]);
      c = vu1gen::vmax(c, cx.vfR[21][1]);
      c = vu1gen::vmax(c, cx.vfR[21][2]);
      c = vu1gen::vmax(c, cx.vfR[20][0]);
      c = vu1gen::vmax(c, cx.vfR[20][1]);
      c = vu1gen::vmax(c, cx.vfR[20][2]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      float ur0 = 0.0f;
      float ur1 = 0.0f;
      float ur2 = 0.0f;
      {
        { const int32_t iv = vu1gen::ftoi(vu1gen::nrm(st.vf[21][0]), 1.0f);
          std::memcpy(&ur0, &iv, 4); }
        { const int32_t iv = vu1gen::ftoi(vu1gen::nrm(st.vf[21][1]), 1.0f);
          std::memcpy(&ur1, &iv, 4); }
        { const int32_t iv = vu1gen::ftoi(vu1gen::nrm(st.vf[21][2]), 1.0f);
          std::memcpy(&ur2, &iv, 4); }
      }
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[11] + -2) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[20][0], 12);
        }
      }
      bvReg = -1;
      st.vf[20][0] = ur0;
      st.vf[20][1] = ur1;
      st.vf[20][2] = ur2;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[20] = rt;
        cx.vfR[20][0] = rt;
        cx.vfR[20][1] = rt;
        cx.vfR[20][2] = rt;
      }
      c += 1u;
    }
    LC0190:;
    L0190:;
    { // pair 50 pc=0x190 up=0x000002FF lo=0x800C0AB4
      c = vu1gen::vmax(c, cx.viR[1]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[1] & st.vi[12]); bvOld = st.vi[10]; bvReg = 10; st.vi[10] = nv; }
      }
      cx.viR[10] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L0198:;
    { // pair 51 pc=0x198 up=0x000002FF lo=0x028BB000
      c = vu1gen::vmax(c, cx.vfR[22][1]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[11] + 0) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 4u, &st.vf[22][1], 4);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L01A0:;
    { const bool bt = (int16_t)(bvReg == 10 ? bvOld : st.vi[10]) > 0;
    { // pair 52 pc=0x1A0 up=0x000002FF lo=0x5A0057F7
      c = vu1gen::vmax(c, cx.viR[10]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    { // pair 53 pc=0x1A8 up=0x000002FF lo=0x100B5801
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[11] + 1); bvOld = st.vi[11]; bvReg = 11; st.vi[11] = nv; }
      }
      c += 1u;
    }
    if (bt) {
      st.branchTarget = 0x160u;
      if (c >= (uint64_t)a.maxCycles) { st.pc = 0x160u; goto BUDGET_OUT; }
      goto L0160;
    } }
    goto LC01B0;
    L01A8:;
    { // pair 53 pc=0x1A8 up=0x000002FF lo=0x100B5801
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[11] + 1); bvOld = st.vi[11]; bvReg = 11; st.vi[11] = nv; }
      }
      c += 1u;
    }
    LC01B0:;
    L01B0:;
    { // pair 54 pc=0x1B0 up=0x000002FF lo=0x800046FC
      cx.waitKick(c);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        cx.startKick(c, (uint32_t)(uint16_t)st.vi[8]);
      }
      bvReg = -1;
      c += 1u;
    }
    L01B8:;
    { // pair 55 pc=0x1B8 up=0x400002FF lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    { // pair 56 pc=0x1C0 up=0x000002FF lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    st.pc = 0x1C8u; goto END_OUT;
    L01C0:;
    { // pair 56 pc=0x1C0 up=0x000002FF lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    L01C8:;
    { // pair 57 pc=0x1C8 up=0x000002FF lo=0x800806BC
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        st.vi[8] = (int32_t)(st.top & 0x3FFu);
      }
      bvReg = -1;
      c += 1u;
    }
    L01D0:;
    { // pair 58 pc=0x1D0 up=0x000002FF lo=0x08224127
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[8] + 295) * 16u) & 0x3FFFu;
          uint32_t v = 0u; std::memcpy(&v, vm + addr + 12u, 4);
          st.vi[2] = (int32_t)(int16_t)(v & 0xFFFFu);
        }
      }
      bvReg = -1;
      cx.viR[2] = (uint32_t)(c + 4u);
      c += 1u;
    }
    L01D8:;
    { // pair 59 pc=0x1D8 up=0x000002FF lo=0x10830000
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[0] + 8192); bvOld = st.vi[3]; bvReg = 3; st.vi[3] = nv; }
      }
      c += 1u;
    }
    L01E0:;
    { const bool bt = (int16_t)0 == (int16_t)(bvReg == 1 ? bvOld : st.vi[1]);
    { // pair 60 pc=0x1E0 up=0x000002FF lo=0x50010005
      c = vu1gen::vmax(c, cx.viR[1]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    { // pair 61 pc=0x1E8 up=0x000002FF lo=0x005603CF
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 975) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[22][2], vm + addr + 8u, 4);
        }
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[22] = rt;
        cx.vfR[22][2] = rt;
      }
      c += 1u;
    }
    if (bt) {
      st.branchTarget = 0x210u;
      goto L0210;
    } }
    goto LC01F0;
    L01E8:;
    { // pair 61 pc=0x1E8 up=0x000002FF lo=0x005603CF
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 975) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[22][2], vm + addr + 8u, 4);
        }
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[22] = rt;
        cx.vfR[22][2] = rt;
      }
      c += 1u;
    }
    LC01F0:;
    L01F0:;
    { // pair 62 pc=0x1F0 up=0x000002FF lo=0x800310F4
      c = vu1gen::vmax(c, cx.viR[2]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[2] & st.vi[3]); bvOld = st.vi[3]; bvReg = 3; st.vi[3] = nv; }
      }
      c += 1u;
    }
    L01F8:;
    { // pair 63 pc=0x1F8 up=0x000002FF lo=0x01E103A7
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 935) * 16u) & 0x3FFFu;
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
    L0200:;
    { const bool bt = (int16_t)0 == (int16_t)(bvReg == 3 ? bvOld : st.vi[3]);
    { // pair 64 pc=0x200 up=0x000002FF lo=0x50030003
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    { // pair 65 pc=0x208 up=0x000002FF lo=0x01E203AA
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 938) * 16u) & 0x3FFFu;
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
    if (bt) {
      st.branchTarget = 0x220u;
      goto L0220;
    } }
    goto LC0210;
    L0208:;
    { // pair 65 pc=0x208 up=0x000002FF lo=0x01E203AA
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 938) * 16u) & 0x3FFFu;
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
    LC0210:;
    L0210:;
    { // pair 66 pc=0x210 up=0x400002FF lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    { // pair 67 pc=0x218 up=0x000002FF lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    st.pc = 0x220u; goto END_OUT;
    L0218:;
    { // pair 67 pc=0x218 up=0x000002FF lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    L0220:;
    { // pair 68 pc=0x220 up=0x000002FF lo=0x8096B33D
      c = vu1gen::vmax(c, cx.vfRAny[22]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        const float mv1 = st.vf[22][2];
        st.vf[22][1] = mv1;
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[22] = rt;
        cx.vfR[22][1] = rt;
      }
      c += 1u;
    }
    L0228:;
    { // pair 69 pc=0x228 up=0x000002FF lo=0x100940FA
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[8] + 250); bvOld = st.vi[9]; bvReg = 9; st.vi[9] = nv; }
      }
      c += 1u;
    }
    L0230:;
    { // pair 70 pc=0x230 up=0x000002FF lo=0x10084127
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[8] + 295); bvOld = st.vi[8]; bvReg = 8; st.vi[8] = nv; }
      }
      c += 1u;
    }
    L0238:;
    { // pair 71 pc=0x238 up=0x000002FF lo=0x090A4004
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[8] + 4) * 16u) & 0x3FFFu;
          uint32_t v = 0u; std::memcpy(&v, vm + addr + 0u, 4);
          st.vi[10] = (int32_t)(int16_t)(v & 0xFFFFu);
        }
      }
      bvReg = -1;
      cx.viR[10] = (uint32_t)(c + 4u);
      c += 1u;
    }
    L0240:;
    { // pair 72 pc=0x240 up=0x000002FF lo=0x81D54B7C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(uint16_t)st.vi[9] * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[21][0], vm + addr + 0u, 12);
        }
        { const int32_t nv = (int32_t)(int16_t)(st.vi[9] + 1); bvOld = st.vi[9]; bvReg = 9; st.vi[9] = nv; }
      }
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[21] = rt;
        cx.vfR[21][0] = rt;
        cx.vfR[21][1] = rt;
        cx.vfR[21][2] = rt;
      }
      c += 1u;
    }
    L0248:;
    { // pair 73 pc=0x248 up=0x000002FF lo=0x03E80802
      c = vu1gen::vmax(c, cx.vfRAny[1]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[8] + 2) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[1][0], 16);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L0250:;
    { // pair 74 pc=0x250 up=0x000002FF lo=0x03E81003
      c = vu1gen::vmax(c, cx.vfRAny[2]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[8] + 3) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[2][0], 16);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L0258:;
    { // pair 75 pc=0x258 up=0x000002FF lo=0x0288B004
      c = vu1gen::vmax(c, cx.vfR[22][1]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[8] + 4) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 4u, &st.vf[22][1], 4);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L0260:;
    { // pair 76 pc=0x260 up=0x01D4A97C lo=0x11EC07FF
      c = vu1gen::vmax(c, cx.vfR[21][0]);
      c = vu1gen::vmax(c, cx.vfR[21][1]);
      c = vu1gen::vmax(c, cx.vfR[21][2]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      float ur0 = 0.0f;
      float ur1 = 0.0f;
      float ur2 = 0.0f;
      {
        { const int32_t iv = vu1gen::ftoi(vu1gen::nrm(st.vf[21][0]), 1.0f);
          std::memcpy(&ur0, &iv, 4); }
        { const int32_t iv = vu1gen::ftoi(vu1gen::nrm(st.vf[21][1]), 1.0f);
          std::memcpy(&ur1, &iv, 4); }
        { const int32_t iv = vu1gen::ftoi(vu1gen::nrm(st.vf[21][2]), 1.0f);
          std::memcpy(&ur2, &iv, 4); }
      }
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[0] + 32767); bvOld = st.vi[12]; bvReg = 12; st.vi[12] = nv; }
      }
      st.vf[20][0] = ur0;
      st.vf[20][1] = ur1;
      st.vf[20][2] = ur2;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[20] = rt;
        cx.vfR[20][0] = rt;
        cx.vfR[20][1] = rt;
        cx.vfR[20][2] = rt;
      }
      c += 1u;
    }
    L0268:;
    { // pair 77 pc=0x268 up=0x000002FF lo=0x800C52B4
      c = vu1gen::vmax(c, cx.viR[10]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[10] & st.vi[12]); bvOld = st.vi[10]; bvReg = 10; st.vi[10] = nv; }
      }
      cx.viR[10] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L0270:;
    { // pair 78 pc=0x270 up=0x000002FF lo=0x100B4005
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[8] + 5); bvOld = st.vi[11]; bvReg = 11; st.vi[11] = nv; }
      }
      c += 1u;
    }
    L0278:;
    { // pair 79 pc=0x278 up=0x000002FF lo=0x81D54B7C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(uint16_t)st.vi[9] * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[21][0], vm + addr + 0u, 12);
        }
        { const int32_t nv = (int32_t)(int16_t)(st.vi[9] + 1); bvOld = st.vi[9]; bvReg = 9; st.vi[9] = nv; }
      }
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[21] = rt;
        cx.vfR[21][0] = rt;
        cx.vfR[21][1] = rt;
        cx.vfR[21][2] = rt;
      }
      c += 1u;
    }
    L0280:;
    { // pair 80 pc=0x280 up=0x000002FF lo=0x09015803
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[11] + 3) * 16u) & 0x3FFFu;
          uint32_t v = 0u; std::memcpy(&v, vm + addr + 0u, 4);
          st.vi[1] = (int32_t)(int16_t)(v & 0xFFFFu);
        }
      }
      bvReg = -1;
      cx.viR[1] = (uint32_t)(c + 4u);
      c += 1u;
    }
    L0288:;
    { // pair 81 pc=0x288 up=0x000002FF lo=0x120A5001
      c = vu1gen::vmax(c, cx.viR[10]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[10] - 1); bvOld = st.vi[10]; bvReg = 10; st.vi[10] = nv; }
      }
      cx.viR[10] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L0290:;
    { // pair 82 pc=0x290 up=0x000002FF lo=0x100B5803
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[11] + 3); bvOld = st.vi[11]; bvReg = 11; st.vi[11] = nv; }
      }
      c += 1u;
    }
    L0298:;
    { const bool bt = (int16_t)(bvReg == 10 ? bvOld : st.vi[10]) > 0;
    { // pair 83 pc=0x298 up=0x000002FF lo=0x5A0057FB
      c = vu1gen::vmax(c, cx.viR[10]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    { // pair 84 pc=0x2A0 up=0x01D4A97C lo=0x03CBA7FE
      c = vu1gen::vmax(c, cx.vfR[21][0]);
      c = vu1gen::vmax(c, cx.vfR[21][1]);
      c = vu1gen::vmax(c, cx.vfR[21][2]);
      c = vu1gen::vmax(c, cx.vfR[20][0]);
      c = vu1gen::vmax(c, cx.vfR[20][1]);
      c = vu1gen::vmax(c, cx.vfR[20][2]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      float ur0 = 0.0f;
      float ur1 = 0.0f;
      float ur2 = 0.0f;
      {
        { const int32_t iv = vu1gen::ftoi(vu1gen::nrm(st.vf[21][0]), 1.0f);
          std::memcpy(&ur0, &iv, 4); }
        { const int32_t iv = vu1gen::ftoi(vu1gen::nrm(st.vf[21][1]), 1.0f);
          std::memcpy(&ur1, &iv, 4); }
        { const int32_t iv = vu1gen::ftoi(vu1gen::nrm(st.vf[21][2]), 1.0f);
          std::memcpy(&ur2, &iv, 4); }
      }
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[11] + -2) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[20][0], 12);
        }
      }
      bvReg = -1;
      st.vf[20][0] = ur0;
      st.vf[20][1] = ur1;
      st.vf[20][2] = ur2;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[20] = rt;
        cx.vfR[20][0] = rt;
        cx.vfR[20][1] = rt;
        cx.vfR[20][2] = rt;
      }
      c += 1u;
    }
    if (bt) {
      st.branchTarget = 0x278u;
      if (c >= (uint64_t)a.maxCycles) { st.pc = 0x278u; goto BUDGET_OUT; }
      goto L0278;
    } }
    goto LC02A8;
    L02A0:;
    { // pair 84 pc=0x2A0 up=0x01D4A97C lo=0x03CBA7FE
      c = vu1gen::vmax(c, cx.vfR[21][0]);
      c = vu1gen::vmax(c, cx.vfR[21][1]);
      c = vu1gen::vmax(c, cx.vfR[21][2]);
      c = vu1gen::vmax(c, cx.vfR[20][0]);
      c = vu1gen::vmax(c, cx.vfR[20][1]);
      c = vu1gen::vmax(c, cx.vfR[20][2]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      float ur0 = 0.0f;
      float ur1 = 0.0f;
      float ur2 = 0.0f;
      {
        { const int32_t iv = vu1gen::ftoi(vu1gen::nrm(st.vf[21][0]), 1.0f);
          std::memcpy(&ur0, &iv, 4); }
        { const int32_t iv = vu1gen::ftoi(vu1gen::nrm(st.vf[21][1]), 1.0f);
          std::memcpy(&ur1, &iv, 4); }
        { const int32_t iv = vu1gen::ftoi(vu1gen::nrm(st.vf[21][2]), 1.0f);
          std::memcpy(&ur2, &iv, 4); }
      }
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[11] + -2) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[20][0], 12);
        }
      }
      bvReg = -1;
      st.vf[20][0] = ur0;
      st.vf[20][1] = ur1;
      st.vf[20][2] = ur2;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[20] = rt;
        cx.vfR[20][0] = rt;
        cx.vfR[20][1] = rt;
        cx.vfR[20][2] = rt;
      }
      c += 1u;
    }
    LC02A8:;
    L02A8:;
    { // pair 85 pc=0x2A8 up=0x000002FF lo=0x800C0AB4
      c = vu1gen::vmax(c, cx.viR[1]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[1] & st.vi[12]); bvOld = st.vi[10]; bvReg = 10; st.vi[10] = nv; }
      }
      cx.viR[10] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L02B0:;
    { // pair 86 pc=0x2B0 up=0x000002FF lo=0x028BB000
      c = vu1gen::vmax(c, cx.vfR[22][1]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[11] + 0) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 4u, &st.vf[22][1], 4);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L02B8:;
    { const bool bt = (int16_t)(bvReg == 10 ? bvOld : st.vi[10]) > 0;
    { // pair 87 pc=0x2B8 up=0x000002FF lo=0x5A0057F7
      c = vu1gen::vmax(c, cx.viR[10]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    { // pair 88 pc=0x2C0 up=0x000002FF lo=0x100B5801
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[11] + 1); bvOld = st.vi[11]; bvReg = 11; st.vi[11] = nv; }
      }
      c += 1u;
    }
    if (bt) {
      st.branchTarget = 0x278u;
      if (c >= (uint64_t)a.maxCycles) { st.pc = 0x278u; goto BUDGET_OUT; }
      goto L0278;
    } }
    goto LC02C8;
    L02C0:;
    { // pair 88 pc=0x2C0 up=0x000002FF lo=0x100B5801
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[11] + 1); bvOld = st.vi[11]; bvReg = 11; st.vi[11] = nv; }
      }
      c += 1u;
    }
    LC02C8:;
    L02C8:;
    { // pair 89 pc=0x2C8 up=0x000002FF lo=0x800046FC
      cx.waitKick(c);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        cx.startKick(c, (uint32_t)(uint16_t)st.vi[8]);
      }
      bvReg = -1;
      c += 1u;
    }
    L02D0:;
    { // pair 90 pc=0x2D0 up=0x400002FF lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    { // pair 91 pc=0x2D8 up=0x000002FF lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    st.pc = 0x2E0u; goto END_OUT;
    L02D8:;
    { // pair 91 pc=0x2D8 up=0x000002FF lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    L02E0:;
    { // pair 92 pc=0x2E0 up=0x000002FF lo=0x800806BC
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        st.vi[8] = (int32_t)(st.top & 0x3FFu);
      }
      bvReg = -1;
      c += 1u;
    }
    L02E8:;
    { // pair 93 pc=0x2E8 up=0x000002FF lo=0x08224127
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[8] + 295) * 16u) & 0x3FFFu;
          uint32_t v = 0u; std::memcpy(&v, vm + addr + 12u, 4);
          st.vi[2] = (int32_t)(int16_t)(v & 0xFFFFu);
        }
      }
      bvReg = -1;
      cx.viR[2] = (uint32_t)(c + 4u);
      c += 1u;
    }
    L02F0:;
    { // pair 94 pc=0x2F0 up=0x000002FF lo=0x10830000
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[0] + 8192); bvOld = st.vi[3]; bvReg = 3; st.vi[3] = nv; }
      }
      c += 1u;
    }
    L02F8:;
    { const bool bt = (int16_t)0 == (int16_t)(bvReg == 1 ? bvOld : st.vi[1]);
    { // pair 95 pc=0x2F8 up=0x000002FF lo=0x50010005
      c = vu1gen::vmax(c, cx.viR[1]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    { // pair 96 pc=0x300 up=0x000002FF lo=0x009603CF
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 975) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[22][1], vm + addr + 4u, 4);
        }
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[22] = rt;
        cx.vfR[22][1] = rt;
      }
      c += 1u;
    }
    if (bt) {
      st.branchTarget = 0x328u;
      goto L0328;
    } }
    goto LC0308;
    L0300:;
    { // pair 96 pc=0x300 up=0x000002FF lo=0x009603CF
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 975) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[22][1], vm + addr + 4u, 4);
        }
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[22] = rt;
        cx.vfR[22][1] = rt;
      }
      c += 1u;
    }
    LC0308:;
    L0308:;
    { // pair 97 pc=0x308 up=0x000002FF lo=0x800310F4
      c = vu1gen::vmax(c, cx.viR[2]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[2] & st.vi[3]); bvOld = st.vi[3]; bvReg = 3; st.vi[3] = nv; }
      }
      c += 1u;
    }
    L0310:;
    { // pair 98 pc=0x310 up=0x000002FF lo=0x01F503AB
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 939) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[21][0], vm + addr + 0u, 16);
        }
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[21] = rt;
        _mm_store_si128((__m128i *)cx.vfR[21], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L0318:;
    { const bool bt = (int16_t)0 == (int16_t)(bvReg == 3 ? bvOld : st.vi[3]);
    { // pair 99 pc=0x318 up=0x000002FF lo=0x50030003
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    { // pair 100 pc=0x320 up=0x000002FF lo=0x01E103A8
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 936) * 16u) & 0x3FFFu;
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
    if (bt) {
      st.branchTarget = 0x338u;
      goto L0338;
    } }
    goto LC0328;
    L0320:;
    { // pair 100 pc=0x320 up=0x000002FF lo=0x01E103A8
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 936) * 16u) & 0x3FFFu;
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
    LC0328:;
    L0328:;
    { // pair 101 pc=0x328 up=0x400002FF lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    { // pair 102 pc=0x330 up=0x000002FF lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    st.pc = 0x338u; goto END_OUT;
    L0330:;
    { // pair 102 pc=0x330 up=0x000002FF lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    L0338:;
    { // pair 103 pc=0x338 up=0x000002FF lo=0x01E203AA
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 938) * 16u) & 0x3FFFu;
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
    L0340:;
    { // pair 104 pc=0x340 up=0x000002FF lo=0x01E30397
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 919) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[3][0], vm + addr + 0u, 16);
        }
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[3] = rt;
        _mm_store_si128((__m128i *)cx.vfR[3], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L0348:;
    { // pair 105 pc=0x348 up=0x000002FF lo=0x100940CD
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[8] + 205); bvOld = st.vi[9]; bvReg = 9; st.vi[9] = nv; }
      }
      c += 1u;
    }
    L0350:;
    { // pair 106 pc=0x350 up=0x000002FF lo=0x10084127
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[8] + 295); bvOld = st.vi[8]; bvReg = 8; st.vi[8] = nv; }
      }
      c += 1u;
    }
    L0358:;
    { // pair 107 pc=0x358 up=0x000002FF lo=0x100B4005
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[8] + 5); bvOld = st.vi[11]; bvReg = 11; st.vi[11] = nv; }
      }
      c += 1u;
    }
    L0360:;
    { // pair 108 pc=0x360 up=0x000002FF lo=0x090A4004
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[8] + 4) * 16u) & 0x3FFFu;
          uint32_t v = 0u; std::memcpy(&v, vm + addr + 0u, 4);
          st.vi[10] = (int32_t)(int16_t)(v & 0xFFFFu);
        }
      }
      bvReg = -1;
      cx.viR[10] = (uint32_t)(c + 4u);
      c += 1u;
    }
    L0368:;
    { // pair 109 pc=0x368 up=0x000002FF lo=0x03E80802
      c = vu1gen::vmax(c, cx.vfRAny[1]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[8] + 2) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[1][0], 16);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L0370:;
    { // pair 110 pc=0x370 up=0x000002FF lo=0x03E81003
      c = vu1gen::vmax(c, cx.vfRAny[2]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[8] + 3) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[2][0], 16);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L0378:;
    { // pair 111 pc=0x378 up=0x000002FF lo=0x03E81801
      c = vu1gen::vmax(c, cx.vfRAny[3]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[8] + 1) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[3][0], 16);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L0380:;
    { // pair 112 pc=0x380 up=0x000002FF lo=0x00545800
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[11] + 0) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[20][2], vm + addr + 8u, 4);
        }
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[20] = rt;
        cx.vfR[20][2] = rt;
      }
      c += 1u;
    }
    L0388:;
    { // pair 113 pc=0x388 up=0x000002FF lo=0x81944B7C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(uint16_t)st.vi[9] * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[20][0], vm + addr + 0u, 8);
        }
        { const int32_t nv = (int32_t)(int16_t)(st.vi[9] + 1); bvOld = st.vi[9]; bvReg = 9; st.vi[9] = nv; }
      }
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[20] = rt;
        cx.vfR[20][0] = rt;
        cx.vfR[20][1] = rt;
      }
      c += 1u;
    }
    L0390:;
    { // pair 114 pc=0x390 up=0x000002FF lo=0x100B5803
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[11] + 3); bvOld = st.vi[11]; bvReg = 11; st.vi[11] = nv; }
      }
      c += 1u;
    }
    L0398:;
    { // pair 115 pc=0x398 up=0x000002FF lo=0x0288B004
      c = vu1gen::vmax(c, cx.vfR[22][1]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[8] + 4) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 4u, &st.vf[22][1], 4);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L03A0:;
    { // pair 116 pc=0x3A0 up=0x000002FF lo=0x11EC07FF
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[0] + 32767); bvOld = st.vi[12]; bvReg = 12; st.vi[12] = nv; }
      }
      c += 1u;
    }
    L03A8:;
    { // pair 117 pc=0x3A8 up=0x0194A4DA lo=0x800C52B4
      c = vu1gen::vmax(c, cx.vfR[20][0]);
      c = vu1gen::vmax(c, cx.vfR[20][1]);
      c = vu1gen::vmax(c, cx.vfR[20][2]);
      c = vu1gen::vmax(c, cx.viR[10]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[20]);
        const __m128 bv = vu1gen::nrmbc(st.vf[20], 2);
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
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[10] & st.vi[12]); bvOld = st.vi[10]; bvReg = 10; st.vi[10] = nv; }
      }
      vu1gen::storeLanes(st.vf[19], urv, 0xCu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[19] = rt;
        cx.vfR[19][0] = rt;
        cx.vfR[19][1] = rt;
      }
      cx.viR[10] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L03B0:;
    { // pair 118 pc=0x3B0 up=0x000002FF lo=0x00545800
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[11] + 0) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[20][2], vm + addr + 8u, 4);
        }
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[20] = rt;
        cx.vfR[20][2] = rt;
      }
      c += 1u;
    }
    L03B8:;
    { // pair 119 pc=0x3B8 up=0x000002FF lo=0x81944B7C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(uint16_t)st.vi[9] * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[20][0], vm + addr + 0u, 8);
        }
        { const int32_t nv = (int32_t)(int16_t)(st.vi[9] + 1); bvOld = st.vi[9]; bvReg = 9; st.vi[9] = nv; }
      }
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[20] = rt;
        cx.vfR[20][0] = rt;
        cx.vfR[20][1] = rt;
      }
      c += 1u;
    }
    L03C0:;
    { // pair 120 pc=0x3C0 up=0x000002FF lo=0x100B5803
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[11] + 3); bvOld = st.vi[11]; bvReg = 11; st.vi[11] = nv; }
      }
      c += 1u;
    }
    L03C8:;
    { // pair 121 pc=0x3C8 up=0x000002FF lo=0x120A5001
      c = vu1gen::vmax(c, cx.viR[10]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[10] - 1); bvOld = st.vi[10]; bvReg = 10; st.vi[10] = nv; }
      }
      cx.viR[10] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L03D0:;
    { // pair 122 pc=0x3D0 up=0x000002FF lo=0x03EBAFFB
      c = vu1gen::vmax(c, cx.vfRAny[21]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[11] + -5) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[21][0], 16);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L03D8:;
    { const bool bt = (int16_t)(bvReg == 10 ? bvOld : st.vi[10]) > 0;
    { // pair 123 pc=0x3D8 up=0x000002FF lo=0x5A0057FA
      c = vu1gen::vmax(c, cx.viR[10]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    { // pair 124 pc=0x3E0 up=0x0194A4DA lo=0x038B9FFA
      c = vu1gen::vmax(c, cx.vfR[20][0]);
      c = vu1gen::vmax(c, cx.vfR[20][1]);
      c = vu1gen::vmax(c, cx.vfR[20][2]);
      c = vu1gen::vmax(c, cx.vfR[19][0]);
      c = vu1gen::vmax(c, cx.vfR[19][1]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[20]);
        const __m128 bv = vu1gen::nrmbc(st.vf[20], 2);
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
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[11] + -6) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[19][0], 8);
        }
      }
      bvReg = -1;
      vu1gen::storeLanes(st.vf[19], urv, 0xCu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[19] = rt;
        cx.vfR[19][0] = rt;
        cx.vfR[19][1] = rt;
      }
      c += 1u;
    }
    if (bt) {
      st.branchTarget = 0x3B0u;
      if (c >= (uint64_t)a.maxCycles) { st.pc = 0x3B0u; goto BUDGET_OUT; }
      goto L03B0;
    } }
    goto LC03E8;
    L03E0:;
    { // pair 124 pc=0x3E0 up=0x0194A4DA lo=0x038B9FFA
      c = vu1gen::vmax(c, cx.vfR[20][0]);
      c = vu1gen::vmax(c, cx.vfR[20][1]);
      c = vu1gen::vmax(c, cx.vfR[20][2]);
      c = vu1gen::vmax(c, cx.vfR[19][0]);
      c = vu1gen::vmax(c, cx.vfR[19][1]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[20]);
        const __m128 bv = vu1gen::nrmbc(st.vf[20], 2);
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
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[11] + -6) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[19][0], 8);
        }
      }
      bvReg = -1;
      vu1gen::storeLanes(st.vf[19], urv, 0xCu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[19] = rt;
        cx.vfR[19][0] = rt;
        cx.vfR[19][1] = rt;
      }
      c += 1u;
    }
    LC03E8:;
    L03E8:;
    { // pair 125 pc=0x3E8 up=0x000002FF lo=0x09015FFD
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[11] + -3) * 16u) & 0x3FFFu;
          uint32_t v = 0u; std::memcpy(&v, vm + addr + 0u, 4);
          st.vi[1] = (int32_t)(int16_t)(v & 0xFFFFu);
        }
      }
      bvReg = -1;
      cx.viR[1] = (uint32_t)(c + 4u);
      c += 1u;
    }
    L03F0:;
    { // pair 126 pc=0x3F0 up=0x000002FF lo=0x00545FFE
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[11] + -2) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[20][2], vm + addr + 8u, 4);
        }
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[20] = rt;
        cx.vfR[20][2] = rt;
      }
      c += 1u;
    }
    L03F8:;
    { // pair 127 pc=0x3F8 up=0x000002FF lo=0x01944FFF
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[9] + -1) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[20][0], vm + addr + 0u, 8);
        }
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[20] = rt;
        cx.vfR[20][0] = rt;
        cx.vfR[20][1] = rt;
      }
      c += 1u;
    }
    L0400:;
    { // pair 128 pc=0x400 up=0x000002FF lo=0x028BB7FD
      c = vu1gen::vmax(c, cx.vfR[22][1]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[11] + -3) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 4u, &st.vf[22][1], 4);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L0408:;
    { // pair 129 pc=0x408 up=0x000002FF lo=0x800C0AB4
      c = vu1gen::vmax(c, cx.viR[1]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[1] & st.vi[12]); bvOld = st.vi[10]; bvReg = 10; st.vi[10] = nv; }
      }
      cx.viR[10] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L0410:;
    { // pair 130 pc=0x410 up=0x000002FF lo=0x100B5801
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[11] + 1); bvOld = st.vi[11]; bvReg = 11; st.vi[11] = nv; }
      }
      c += 1u;
    }
    L0418:;
    { const bool bt = (int16_t)(bvReg == 10 ? bvOld : st.vi[10]) > 0;
    { // pair 131 pc=0x418 up=0x0194A4DA lo=0x5A0057F2
      c = vu1gen::vmax(c, cx.vfR[20][0]);
      c = vu1gen::vmax(c, cx.vfR[20][1]);
      c = vu1gen::vmax(c, cx.vfR[20][2]);
      c = vu1gen::vmax(c, cx.viR[10]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[20]);
        const __m128 bv = vu1gen::nrmbc(st.vf[20], 2);
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
      vu1gen::storeLanes(st.vf[19], urv, 0xCu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[19] = rt;
        cx.vfR[19][0] = rt;
        cx.vfR[19][1] = rt;
      }
      c += 1u;
    }
    { // pair 132 pc=0x420 up=0x000002FF lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    if (bt) {
      st.branchTarget = 0x3B0u;
      if (c >= (uint64_t)a.maxCycles) { st.pc = 0x3B0u; goto BUDGET_OUT; }
      goto L03B0;
    } }
    goto LC0428;
    L0420:;
    { // pair 132 pc=0x420 up=0x000002FF lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    LC0428:;
    L0428:;
    { // pair 133 pc=0x428 up=0x000002FF lo=0x800046FC
      cx.waitKick(c);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        cx.startKick(c, (uint32_t)(uint16_t)st.vi[8]);
      }
      bvReg = -1;
      c += 1u;
    }
    L0430:;
    { // pair 134 pc=0x430 up=0x400002FF lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    { // pair 135 pc=0x438 up=0x000002FF lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    st.pc = 0x440u; goto END_OUT;
    L0438:;
    { // pair 135 pc=0x438 up=0x000002FF lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    st.pc = 0x440u; goto HAND_OUT;

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
    case 0x308u: goto L0308;
    case 0x310u: goto L0310;
    case 0x318u: goto L0318;
    case 0x320u: goto L0320;
    case 0x328u: goto L0328;
    case 0x330u: goto L0330;
    case 0x338u: goto L0338;
    case 0x340u: goto L0340;
    case 0x348u: goto L0348;
    case 0x350u: goto L0350;
    case 0x358u: goto L0358;
    case 0x360u: goto L0360;
    case 0x368u: goto L0368;
    case 0x370u: goto L0370;
    case 0x378u: goto L0378;
    case 0x380u: goto L0380;
    case 0x388u: goto L0388;
    case 0x390u: goto L0390;
    case 0x398u: goto L0398;
    case 0x3A0u: goto L03A0;
    case 0x3A8u: goto L03A8;
    case 0x3B0u: goto L03B0;
    case 0x3B8u: goto L03B8;
    case 0x3C0u: goto L03C0;
    case 0x3C8u: goto L03C8;
    case 0x3D0u: goto L03D0;
    case 0x3D8u: goto L03D8;
    case 0x3E0u: goto L03E0;
    case 0x3E8u: goto L03E8;
    case 0x3F0u: goto L03F0;
    case 0x3F8u: goto L03F8;
    case 0x400u: goto L0400;
    case 0x408u: goto L0408;
    case 0x410u: goto L0410;
    case 0x418u: goto L0418;
    case 0x420u: goto L0420;
    case 0x428u: goto L0428;
    case 0x430u: goto L0430;
    case 0x438u: goto L0438;
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
