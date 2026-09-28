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

int ps2Vu1Prog_4F9E7E58F7514FFB(Vu1ProgArgs &a)
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
    st.branchTarget = 0x20u;
    { // pair 2 pc=0x10 up=0x000002FF lo=0x40000001
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
    goto L0020;
    L0018:;
    { // pair 3 pc=0x18 up=0x000002FF lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    L0020:;
    { // pair 4 pc=0x20 up=0x000002FF lo=0x03E003DC
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 988) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[0][0], 16);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L0028:;
    { // pair 5 pc=0x28 up=0x000002FF lo=0x03E00BDD
      c = vu1gen::vmax(c, cx.vfRAny[1]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 989) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[1][0], 16);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L0030:;
    { // pair 6 pc=0x30 up=0x000002FF lo=0x03E013DE
      c = vu1gen::vmax(c, cx.vfRAny[2]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 990) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[2][0], 16);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L0038:;
    { // pair 7 pc=0x38 up=0x000002FF lo=0x03E01BDF
      c = vu1gen::vmax(c, cx.vfRAny[3]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 991) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[3][0], 16);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L0040:;
    { // pair 8 pc=0x40 up=0x000002FF lo=0x03E023E0
      c = vu1gen::vmax(c, cx.vfRAny[4]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 992) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[4][0], 16);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L0048:;
    { // pair 9 pc=0x48 up=0x000002FF lo=0x03E02BE1
      c = vu1gen::vmax(c, cx.vfRAny[5]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 993) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[5][0], 16);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L0050:;
    { // pair 10 pc=0x50 up=0x000002FF lo=0x03E033E2
      c = vu1gen::vmax(c, cx.vfRAny[6]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 994) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[6][0], 16);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L0058:;
    { // pair 11 pc=0x58 up=0x000002FF lo=0x03E03BE3
      c = vu1gen::vmax(c, cx.vfRAny[7]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 995) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[7][0], 16);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L0060:;
    { // pair 12 pc=0x60 up=0x000002FF lo=0x03E043E4
      c = vu1gen::vmax(c, cx.vfRAny[8]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 996) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[8][0], 16);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L0068:;
    { // pair 13 pc=0x68 up=0x000002FF lo=0x03E04BE5
      c = vu1gen::vmax(c, cx.vfRAny[9]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 997) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[9][0], 16);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L0070:;
    { // pair 14 pc=0x70 up=0x000002FF lo=0x03E053E6
      c = vu1gen::vmax(c, cx.vfRAny[10]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 998) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[10][0], 16);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L0078:;
    { // pair 15 pc=0x78 up=0x000002FF lo=0x03E05BE7
      c = vu1gen::vmax(c, cx.vfRAny[11]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 999) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[11][0], 16);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L0080:;
    { // pair 16 pc=0x80 up=0x000002FF lo=0x03E063E8
      c = vu1gen::vmax(c, cx.vfRAny[12]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 1000) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[12][0], 16);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L0088:;
    { // pair 17 pc=0x88 up=0x000002FF lo=0x03E06BE9
      c = vu1gen::vmax(c, cx.vfRAny[13]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 1001) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[13][0], 16);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L0090:;
    { // pair 18 pc=0x90 up=0x000002FF lo=0x03E073EA
      c = vu1gen::vmax(c, cx.vfRAny[14]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 1002) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[14][0], 16);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L0098:;
    { // pair 19 pc=0x98 up=0x000002FF lo=0x03E07BEB
      c = vu1gen::vmax(c, cx.vfRAny[15]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 1003) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[15][0], 16);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L00A0:;
    { // pair 20 pc=0xA0 up=0x000002FF lo=0x03E083EC
      c = vu1gen::vmax(c, cx.vfRAny[16]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 1004) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[16][0], 16);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L00A8:;
    { // pair 21 pc=0xA8 up=0x000002FF lo=0x03E08BED
      c = vu1gen::vmax(c, cx.vfRAny[17]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 1005) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[17][0], 16);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L00B0:;
    { // pair 22 pc=0xB0 up=0x000002FF lo=0x03E093EE
      c = vu1gen::vmax(c, cx.vfRAny[18]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 1006) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[18][0], 16);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L00B8:;
    { // pair 23 pc=0xB8 up=0x000002FF lo=0x03E09BEF
      c = vu1gen::vmax(c, cx.vfRAny[19]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 1007) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[19][0], 16);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L00C0:;
    { // pair 24 pc=0xC0 up=0x000002FF lo=0x03E0A3F0
      c = vu1gen::vmax(c, cx.vfRAny[20]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 1008) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[20][0], 16);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L00C8:;
    { // pair 25 pc=0xC8 up=0x000002FF lo=0x03E0ABF1
      c = vu1gen::vmax(c, cx.vfRAny[21]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 1009) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[21][0], 16);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L00D0:;
    { // pair 26 pc=0xD0 up=0x000002FF lo=0x03E0B3F2
      c = vu1gen::vmax(c, cx.vfRAny[22]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 1010) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[22][0], 16);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L00D8:;
    { // pair 27 pc=0xD8 up=0x000002FF lo=0x03E0BBF3
      c = vu1gen::vmax(c, cx.vfRAny[23]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 1011) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[23][0], 16);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L00E0:;
    { // pair 28 pc=0xE0 up=0x000002FF lo=0x03E0C3F4
      c = vu1gen::vmax(c, cx.vfRAny[24]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 1012) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[24][0], 16);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L00E8:;
    { // pair 29 pc=0xE8 up=0x000002FF lo=0x03E0CBF5
      c = vu1gen::vmax(c, cx.vfRAny[25]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 1013) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[25][0], 16);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L00F0:;
    { // pair 30 pc=0xF0 up=0x000002FF lo=0x03E0D3F6
      c = vu1gen::vmax(c, cx.vfRAny[26]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 1014) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[26][0], 16);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L00F8:;
    { // pair 31 pc=0xF8 up=0x000002FF lo=0x03E0DBF7
      c = vu1gen::vmax(c, cx.vfRAny[27]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 1015) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[27][0], 16);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L0100:;
    { // pair 32 pc=0x100 up=0x000002FF lo=0x03E0E3F8
      c = vu1gen::vmax(c, cx.vfRAny[28]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 1016) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[28][0], 16);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L0108:;
    { // pair 33 pc=0x108 up=0x000002FF lo=0x03E0EBF9
      c = vu1gen::vmax(c, cx.vfRAny[29]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 1017) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[29][0], 16);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L0110:;
    { // pair 34 pc=0x110 up=0x000002FF lo=0x03E0F3FA
      c = vu1gen::vmax(c, cx.vfRAny[30]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 1018) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[30][0], 16);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L0118:;
    { // pair 35 pc=0x118 up=0x000002FF lo=0x03E0FBFB
      c = vu1gen::vmax(c, cx.vfRAny[31]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 1019) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[31][0], 16);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L0120:;
    { // pair 36 pc=0x120 up=0x000002FF lo=0x0B0003FC
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 1020) * 16u) & 0x3FFFu;
          const uint32_t v = (uint32_t)(uint16_t)(st.vi[0] & 0xFFFF);
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &v, 4);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L0128:;
    { // pair 37 pc=0x128 up=0x000002FF lo=0x0A8103FC
      c = vu1gen::vmax(c, cx.viR[1]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 1020) * 16u) & 0x3FFFu;
          const uint32_t v = (uint32_t)(uint16_t)(st.vi[1] & 0xFFFF);
          cx.markStore(addr);
          std::memcpy(vm + addr + 4u, &v, 4);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L0130:;
    { // pair 38 pc=0x130 up=0x000002FF lo=0x0A4203FC
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 1020) * 16u) & 0x3FFFu;
          const uint32_t v = (uint32_t)(uint16_t)(st.vi[2] & 0xFFFF);
          cx.markStore(addr);
          std::memcpy(vm + addr + 8u, &v, 4);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L0138:;
    { // pair 39 pc=0x138 up=0x000002FF lo=0x0A2303FC
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 1020) * 16u) & 0x3FFFu;
          const uint32_t v = (uint32_t)(uint16_t)(st.vi[3] & 0xFFFF);
          cx.markStore(addr);
          std::memcpy(vm + addr + 12u, &v, 4);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L0140:;
    { // pair 40 pc=0x140 up=0x000002FF lo=0x0B0403FD
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 1021) * 16u) & 0x3FFFu;
          const uint32_t v = (uint32_t)(uint16_t)(st.vi[4] & 0xFFFF);
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &v, 4);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L0148:;
    { // pair 41 pc=0x148 up=0x000002FF lo=0x0A8503FD
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 1021) * 16u) & 0x3FFFu;
          const uint32_t v = (uint32_t)(uint16_t)(st.vi[5] & 0xFFFF);
          cx.markStore(addr);
          std::memcpy(vm + addr + 4u, &v, 4);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L0150:;
    { // pair 42 pc=0x150 up=0x000002FF lo=0x0A4603FD
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 1021) * 16u) & 0x3FFFu;
          const uint32_t v = (uint32_t)(uint16_t)(st.vi[6] & 0xFFFF);
          cx.markStore(addr);
          std::memcpy(vm + addr + 8u, &v, 4);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L0158:;
    { // pair 43 pc=0x158 up=0x000002FF lo=0x0A2703FD
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 1021) * 16u) & 0x3FFFu;
          const uint32_t v = (uint32_t)(uint16_t)(st.vi[7] & 0xFFFF);
          cx.markStore(addr);
          std::memcpy(vm + addr + 12u, &v, 4);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L0160:;
    { // pair 44 pc=0x160 up=0x000002FF lo=0x0B0803FE
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 1022) * 16u) & 0x3FFFu;
          const uint32_t v = (uint32_t)(uint16_t)(st.vi[8] & 0xFFFF);
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &v, 4);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L0168:;
    { // pair 45 pc=0x168 up=0x000002FF lo=0x0A8903FE
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 1022) * 16u) & 0x3FFFu;
          const uint32_t v = (uint32_t)(uint16_t)(st.vi[9] & 0xFFFF);
          cx.markStore(addr);
          std::memcpy(vm + addr + 4u, &v, 4);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L0170:;
    { // pair 46 pc=0x170 up=0x000002FF lo=0x0A4A03FE
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 1022) * 16u) & 0x3FFFu;
          const uint32_t v = (uint32_t)(uint16_t)(st.vi[10] & 0xFFFF);
          cx.markStore(addr);
          std::memcpy(vm + addr + 8u, &v, 4);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L0178:;
    { // pair 47 pc=0x178 up=0x000002FF lo=0x0A2B03FE
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 1022) * 16u) & 0x3FFFu;
          const uint32_t v = (uint32_t)(uint16_t)(st.vi[11] & 0xFFFF);
          cx.markStore(addr);
          std::memcpy(vm + addr + 12u, &v, 4);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L0180:;
    { // pair 48 pc=0x180 up=0x000002FF lo=0x0B0C03FF
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 1023) * 16u) & 0x3FFFu;
          const uint32_t v = (uint32_t)(uint16_t)(st.vi[12] & 0xFFFF);
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &v, 4);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L0188:;
    { // pair 49 pc=0x188 up=0x000002FF lo=0x090103DB
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 987) * 16u) & 0x3FFFu;
          uint32_t v = 0u; std::memcpy(&v, vm + addr + 0u, 4);
          st.vi[1] = (int32_t)(int16_t)(v & 0xFFFFu);
        }
      }
      bvReg = -1;
      cx.viR[1] = (uint32_t)(c + 4u);
      c += 1u;
    }
    L0190:;
    { // pair 50 pc=0x190 up=0x000002FF lo=0x0A8D03FF
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 1023) * 16u) & 0x3FFFu;
          const uint32_t v = (uint32_t)(uint16_t)(st.vi[13] & 0xFFFF);
          cx.markStore(addr);
          std::memcpy(vm + addr + 4u, &v, 4);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L0198:;
    { // pair 51 pc=0x198 up=0x000002FF lo=0x0A4E03FF
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 1023) * 16u) & 0x3FFFu;
          const uint32_t v = (uint32_t)(uint16_t)(st.vi[14] & 0xFFFF);
          cx.markStore(addr);
          std::memcpy(vm + addr + 8u, &v, 4);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L01A0:;
    { // pair 52 pc=0x1A0 up=0x000002FF lo=0x0A2F03FF
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 1023) * 16u) & 0x3FFFu;
          const uint32_t v = (uint32_t)(uint16_t)(st.vi[15] & 0xFFFF);
          cx.markStore(addr);
          std::memcpy(vm + addr + 12u, &v, 4);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L01A8:;
    { // pair 53 pc=0x1A8 up=0x000002FF lo=0x10010801
      c = vu1gen::vmax(c, cx.viR[1]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[1] + 1); bvOld = st.vi[1]; bvReg = 1; st.vi[1] = nv; }
      }
      cx.viR[1] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L01B0:;
    { // pair 54 pc=0x1B0 up=0x000002FF lo=0x0B0103DB
      c = vu1gen::vmax(c, cx.viR[1]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 987) * 16u) & 0x3FFFu;
          const uint32_t v = (uint32_t)(uint16_t)(st.vi[1] & 0xFFFF);
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &v, 4);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L01B8:;
    { // pair 55 pc=0x1B8 up=0x01E00058 lo=0x10010000
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = _mm_setr_ps(0.0f, 0.0f, 0.0f, 1.0f);
        const __m128 bv = _mm_set1_ps(0.0f);
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
        urv = rvn;
      }
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[0] + 0); bvOld = st.vi[1]; bvReg = 1; st.vi[1] = nv; }
      }
      vu1gen::storeLanes(st.vf[1], urv, 0xFu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[1] = rt;
        _mm_store_si128((__m128i *)cx.vfR[1], _mm_set1_epi32((int)rt));
      }
      cx.viR[1] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L01C0:;
    { // pair 56 pc=0x1C0 up=0x01E00098 lo=0x10020000
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = _mm_setr_ps(0.0f, 0.0f, 0.0f, 1.0f);
        const __m128 bv = _mm_set1_ps(0.0f);
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
        urv = rvn;
      }
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[0] + 0); bvOld = st.vi[2]; bvReg = 2; st.vi[2] = nv; }
      }
      vu1gen::storeLanes(st.vf[2], urv, 0xFu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[2] = rt;
        _mm_store_si128((__m128i *)cx.vfR[2], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L01C8:;
    { // pair 57 pc=0x1C8 up=0x01E000D8 lo=0x10030000
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = _mm_setr_ps(0.0f, 0.0f, 0.0f, 1.0f);
        const __m128 bv = _mm_set1_ps(0.0f);
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
        urv = rvn;
      }
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[0] + 0); bvOld = st.vi[3]; bvReg = 3; st.vi[3] = nv; }
      }
      vu1gen::storeLanes(st.vf[3], urv, 0xFu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[3] = rt;
        _mm_store_si128((__m128i *)cx.vfR[3], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L01D0:;
    { // pair 58 pc=0x1D0 up=0x01E00118 lo=0x10040000
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = _mm_setr_ps(0.0f, 0.0f, 0.0f, 1.0f);
        const __m128 bv = _mm_set1_ps(0.0f);
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
        urv = rvn;
      }
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[0] + 0); bvOld = st.vi[4]; bvReg = 4; st.vi[4] = nv; }
      }
      vu1gen::storeLanes(st.vf[4], urv, 0xFu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[4] = rt;
        _mm_store_si128((__m128i *)cx.vfR[4], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L01D8:;
    { // pair 59 pc=0x1D8 up=0x01E00158 lo=0x10050000
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = _mm_setr_ps(0.0f, 0.0f, 0.0f, 1.0f);
        const __m128 bv = _mm_set1_ps(0.0f);
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
        urv = rvn;
      }
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[0] + 0); bvOld = st.vi[5]; bvReg = 5; st.vi[5] = nv; }
      }
      vu1gen::storeLanes(st.vf[5], urv, 0xFu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[5] = rt;
        _mm_store_si128((__m128i *)cx.vfR[5], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L01E0:;
    { // pair 60 pc=0x1E0 up=0x01E00198 lo=0x10060000
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = _mm_setr_ps(0.0f, 0.0f, 0.0f, 1.0f);
        const __m128 bv = _mm_set1_ps(0.0f);
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
        urv = rvn;
      }
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[0] + 0); bvOld = st.vi[6]; bvReg = 6; st.vi[6] = nv; }
      }
      vu1gen::storeLanes(st.vf[6], urv, 0xFu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[6] = rt;
        _mm_store_si128((__m128i *)cx.vfR[6], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L01E8:;
    { // pair 61 pc=0x1E8 up=0x01E001D8 lo=0x10070000
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = _mm_setr_ps(0.0f, 0.0f, 0.0f, 1.0f);
        const __m128 bv = _mm_set1_ps(0.0f);
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
        urv = rvn;
      }
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[0] + 0); bvOld = st.vi[7]; bvReg = 7; st.vi[7] = nv; }
      }
      vu1gen::storeLanes(st.vf[7], urv, 0xFu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[7] = rt;
        _mm_store_si128((__m128i *)cx.vfR[7], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L01F0:;
    { // pair 62 pc=0x1F0 up=0x01E00218 lo=0x10080000
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = _mm_setr_ps(0.0f, 0.0f, 0.0f, 1.0f);
        const __m128 bv = _mm_set1_ps(0.0f);
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
        urv = rvn;
      }
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[0] + 0); bvOld = st.vi[8]; bvReg = 8; st.vi[8] = nv; }
      }
      vu1gen::storeLanes(st.vf[8], urv, 0xFu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[8] = rt;
        _mm_store_si128((__m128i *)cx.vfR[8], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L01F8:;
    { // pair 63 pc=0x1F8 up=0x01E00258 lo=0x10090000
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = _mm_setr_ps(0.0f, 0.0f, 0.0f, 1.0f);
        const __m128 bv = _mm_set1_ps(0.0f);
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
        urv = rvn;
      }
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[0] + 0); bvOld = st.vi[9]; bvReg = 9; st.vi[9] = nv; }
      }
      vu1gen::storeLanes(st.vf[9], urv, 0xFu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[9] = rt;
        _mm_store_si128((__m128i *)cx.vfR[9], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L0200:;
    { // pair 64 pc=0x200 up=0x01E00298 lo=0x100A0000
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = _mm_setr_ps(0.0f, 0.0f, 0.0f, 1.0f);
        const __m128 bv = _mm_set1_ps(0.0f);
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
        urv = rvn;
      }
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[0] + 0); bvOld = st.vi[10]; bvReg = 10; st.vi[10] = nv; }
      }
      vu1gen::storeLanes(st.vf[10], urv, 0xFu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[10] = rt;
        _mm_store_si128((__m128i *)cx.vfR[10], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L0208:;
    { // pair 65 pc=0x208 up=0x01E002D8 lo=0x100B0000
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = _mm_setr_ps(0.0f, 0.0f, 0.0f, 1.0f);
        const __m128 bv = _mm_set1_ps(0.0f);
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
        urv = rvn;
      }
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[0] + 0); bvOld = st.vi[11]; bvReg = 11; st.vi[11] = nv; }
      }
      vu1gen::storeLanes(st.vf[11], urv, 0xFu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[11] = rt;
        _mm_store_si128((__m128i *)cx.vfR[11], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L0210:;
    { // pair 66 pc=0x210 up=0x01E00318 lo=0x100C0000
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = _mm_setr_ps(0.0f, 0.0f, 0.0f, 1.0f);
        const __m128 bv = _mm_set1_ps(0.0f);
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
        urv = rvn;
      }
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[0] + 0); bvOld = st.vi[12]; bvReg = 12; st.vi[12] = nv; }
      }
      vu1gen::storeLanes(st.vf[12], urv, 0xFu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[12] = rt;
        _mm_store_si128((__m128i *)cx.vfR[12], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L0218:;
    { // pair 67 pc=0x218 up=0x01E00358 lo=0x100D0000
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = _mm_setr_ps(0.0f, 0.0f, 0.0f, 1.0f);
        const __m128 bv = _mm_set1_ps(0.0f);
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
        urv = rvn;
      }
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[0] + 0); bvOld = st.vi[13]; bvReg = 13; st.vi[13] = nv; }
      }
      vu1gen::storeLanes(st.vf[13], urv, 0xFu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[13] = rt;
        _mm_store_si128((__m128i *)cx.vfR[13], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L0220:;
    { // pair 68 pc=0x220 up=0x01E00398 lo=0x100E0000
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = _mm_setr_ps(0.0f, 0.0f, 0.0f, 1.0f);
        const __m128 bv = _mm_set1_ps(0.0f);
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
        urv = rvn;
      }
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[0] + 0); bvOld = st.vi[14]; bvReg = 14; st.vi[14] = nv; }
      }
      vu1gen::storeLanes(st.vf[14], urv, 0xFu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[14] = rt;
        _mm_store_si128((__m128i *)cx.vfR[14], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L0228:;
    { // pair 69 pc=0x228 up=0x01E003D8 lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = _mm_setr_ps(0.0f, 0.0f, 0.0f, 1.0f);
        const __m128 bv = _mm_set1_ps(0.0f);
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
        urv = rvn;
      }
      bvReg = -1;
      vu1gen::storeLanes(st.vf[15], urv, 0xFu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[15] = rt;
        _mm_store_si128((__m128i *)cx.vfR[15], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L0230:;
    { // pair 70 pc=0x230 up=0x01E00418 lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = _mm_setr_ps(0.0f, 0.0f, 0.0f, 1.0f);
        const __m128 bv = _mm_set1_ps(0.0f);
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
        urv = rvn;
      }
      bvReg = -1;
      vu1gen::storeLanes(st.vf[16], urv, 0xFu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[16] = rt;
        _mm_store_si128((__m128i *)cx.vfR[16], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L0238:;
    { // pair 71 pc=0x238 up=0x01E00458 lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = _mm_setr_ps(0.0f, 0.0f, 0.0f, 1.0f);
        const __m128 bv = _mm_set1_ps(0.0f);
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
        urv = rvn;
      }
      bvReg = -1;
      vu1gen::storeLanes(st.vf[17], urv, 0xFu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[17] = rt;
        _mm_store_si128((__m128i *)cx.vfR[17], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L0240:;
    { // pair 72 pc=0x240 up=0x01E00498 lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = _mm_setr_ps(0.0f, 0.0f, 0.0f, 1.0f);
        const __m128 bv = _mm_set1_ps(0.0f);
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
        urv = rvn;
      }
      bvReg = -1;
      vu1gen::storeLanes(st.vf[18], urv, 0xFu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[18] = rt;
        _mm_store_si128((__m128i *)cx.vfR[18], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L0248:;
    { // pair 73 pc=0x248 up=0x01E004D8 lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = _mm_setr_ps(0.0f, 0.0f, 0.0f, 1.0f);
        const __m128 bv = _mm_set1_ps(0.0f);
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
        urv = rvn;
      }
      bvReg = -1;
      vu1gen::storeLanes(st.vf[19], urv, 0xFu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[19] = rt;
        _mm_store_si128((__m128i *)cx.vfR[19], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L0250:;
    { // pair 74 pc=0x250 up=0x01E00518 lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = _mm_setr_ps(0.0f, 0.0f, 0.0f, 1.0f);
        const __m128 bv = _mm_set1_ps(0.0f);
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
        urv = rvn;
      }
      bvReg = -1;
      vu1gen::storeLanes(st.vf[20], urv, 0xFu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[20] = rt;
        _mm_store_si128((__m128i *)cx.vfR[20], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L0258:;
    { // pair 75 pc=0x258 up=0x01E00558 lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = _mm_setr_ps(0.0f, 0.0f, 0.0f, 1.0f);
        const __m128 bv = _mm_set1_ps(0.0f);
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
        urv = rvn;
      }
      bvReg = -1;
      vu1gen::storeLanes(st.vf[21], urv, 0xFu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[21] = rt;
        _mm_store_si128((__m128i *)cx.vfR[21], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L0260:;
    { // pair 76 pc=0x260 up=0x01E00598 lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = _mm_setr_ps(0.0f, 0.0f, 0.0f, 1.0f);
        const __m128 bv = _mm_set1_ps(0.0f);
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
        urv = rvn;
      }
      bvReg = -1;
      vu1gen::storeLanes(st.vf[22], urv, 0xFu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[22] = rt;
        _mm_store_si128((__m128i *)cx.vfR[22], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L0268:;
    { // pair 77 pc=0x268 up=0x01E005D8 lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = _mm_setr_ps(0.0f, 0.0f, 0.0f, 1.0f);
        const __m128 bv = _mm_set1_ps(0.0f);
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
        urv = rvn;
      }
      bvReg = -1;
      vu1gen::storeLanes(st.vf[23], urv, 0xFu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[23] = rt;
        _mm_store_si128((__m128i *)cx.vfR[23], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L0270:;
    { // pair 78 pc=0x270 up=0x01E00618 lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = _mm_setr_ps(0.0f, 0.0f, 0.0f, 1.0f);
        const __m128 bv = _mm_set1_ps(0.0f);
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
        urv = rvn;
      }
      bvReg = -1;
      vu1gen::storeLanes(st.vf[24], urv, 0xFu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[24] = rt;
        _mm_store_si128((__m128i *)cx.vfR[24], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L0278:;
    { // pair 79 pc=0x278 up=0x01E00658 lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = _mm_setr_ps(0.0f, 0.0f, 0.0f, 1.0f);
        const __m128 bv = _mm_set1_ps(0.0f);
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
        urv = rvn;
      }
      bvReg = -1;
      vu1gen::storeLanes(st.vf[25], urv, 0xFu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[25] = rt;
        _mm_store_si128((__m128i *)cx.vfR[25], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L0280:;
    { // pair 80 pc=0x280 up=0x01E00698 lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = _mm_setr_ps(0.0f, 0.0f, 0.0f, 1.0f);
        const __m128 bv = _mm_set1_ps(0.0f);
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
        urv = rvn;
      }
      bvReg = -1;
      vu1gen::storeLanes(st.vf[26], urv, 0xFu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[26] = rt;
        _mm_store_si128((__m128i *)cx.vfR[26], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L0288:;
    { // pair 81 pc=0x288 up=0x01E006D8 lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = _mm_setr_ps(0.0f, 0.0f, 0.0f, 1.0f);
        const __m128 bv = _mm_set1_ps(0.0f);
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
        urv = rvn;
      }
      bvReg = -1;
      vu1gen::storeLanes(st.vf[27], urv, 0xFu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[27] = rt;
        _mm_store_si128((__m128i *)cx.vfR[27], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L0290:;
    { // pair 82 pc=0x290 up=0x01E00718 lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = _mm_setr_ps(0.0f, 0.0f, 0.0f, 1.0f);
        const __m128 bv = _mm_set1_ps(0.0f);
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
        urv = rvn;
      }
      bvReg = -1;
      vu1gen::storeLanes(st.vf[28], urv, 0xFu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[28] = rt;
        _mm_store_si128((__m128i *)cx.vfR[28], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L0298:;
    { // pair 83 pc=0x298 up=0x01E00758 lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = _mm_setr_ps(0.0f, 0.0f, 0.0f, 1.0f);
        const __m128 bv = _mm_set1_ps(0.0f);
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
        urv = rvn;
      }
      bvReg = -1;
      vu1gen::storeLanes(st.vf[29], urv, 0xFu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[29] = rt;
        _mm_store_si128((__m128i *)cx.vfR[29], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L02A0:;
    { // pair 84 pc=0x2A0 up=0x01E00798 lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = _mm_setr_ps(0.0f, 0.0f, 0.0f, 1.0f);
        const __m128 bv = _mm_set1_ps(0.0f);
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
    L02A8:;
    { // pair 85 pc=0x2A8 up=0x01E007D8 lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = _mm_setr_ps(0.0f, 0.0f, 0.0f, 1.0f);
        const __m128 bv = _mm_set1_ps(0.0f);
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
        urv = rvn;
      }
      bvReg = -1;
      vu1gen::storeLanes(st.vf[31], urv, 0xFu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[31] = rt;
        _mm_store_si128((__m128i *)cx.vfR[31], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L02B0:;
    { // pair 86 pc=0x2B0 up=0x400002FF lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    { // pair 87 pc=0x2B8 up=0x000002FF lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    st.pc = 0x2C0u; goto END_OUT;
    L02B8:;
    { // pair 87 pc=0x2B8 up=0x000002FF lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    st.pc = 0x2C0u; goto HAND_OUT;

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
