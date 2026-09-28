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

int ps2Vu1Prog_A6B7CEEB0D61CE07(Vu1ProgArgs &a)
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
    case 0x440u:
    case 0x448u:
    case 0x450u:
    case 0x458u:
    case 0x460u:
    case 0x468u:
    case 0x470u:
    case 0x478u:
    case 0x480u:
    case 0x488u:
    case 0x490u:
    case 0x498u:
    case 0x4A0u:
    case 0x4A8u:
    case 0x4B0u:
    case 0x4B8u:
    case 0x4C0u:
    case 0x4C8u:
    case 0x4D0u:
    case 0x4D8u:
    case 0x4E0u:
    case 0x4E8u:
    case 0x4F0u:
    case 0x4F8u:
    case 0x500u:
    case 0x508u:
    case 0x510u:
    case 0x518u:
    case 0x520u:
    case 0x528u:
    case 0x530u:
    case 0x538u:
    case 0x540u:
    case 0x548u:
    case 0x550u:
    case 0x558u:
    case 0x560u:
    case 0x568u:
    case 0x570u:
    case 0x578u:
    case 0x580u:
    case 0x588u:
    case 0x590u:
    case 0x598u:
    case 0x5A0u:
    case 0x5A8u:
    case 0x5B0u:
    case 0x5B8u:
    case 0x5C0u:
    case 0x5C8u:
    case 0x5D0u:
    case 0x5D8u:
    case 0x5E0u:
    case 0x5E8u:
    case 0x5F0u:
    case 0x5F8u:
    case 0x600u:
    case 0x608u:
    case 0x610u:
    case 0x618u:
    case 0x620u:
    case 0x628u:
    case 0x630u:
    case 0x638u:
    case 0x640u:
    case 0x648u:
    case 0x650u:
    case 0x658u:
    case 0x660u:
    case 0x668u:
    case 0x670u:
    case 0x678u:
    case 0x680u:
    case 0x688u:
    case 0x690u:
    case 0x698u:
    case 0x6A0u:
    case 0x6A8u:
    case 0x6B0u:
    case 0x6B8u:
    case 0x6C0u:
    case 0x6C8u:
    case 0x6D0u:
    case 0x6D8u:
    case 0x6E0u:
    case 0x6E8u:
    case 0x6F0u:
    case 0x6F8u:
    case 0x700u:
    case 0x708u:
    case 0x710u:
    case 0x718u:
    case 0x720u:
    case 0x728u:
    case 0x730u:
    case 0x738u:
    case 0x740u:
    case 0x748u:
    case 0x750u:
    case 0x758u:
    case 0x760u:
    case 0x768u:
    case 0x770u:
    case 0x778u:
    case 0x780u:
    case 0x788u:
    case 0x790u:
    case 0x798u:
    case 0x7A0u:
    case 0x7A8u:
    case 0x7B0u:
    case 0x7B8u:
    case 0x7C0u:
    case 0x7C8u:
    case 0x7D0u:
    case 0x7D8u:
    case 0x7E0u:
    case 0x7E8u:
    case 0x7F0u:
    case 0x7F8u:
    case 0x800u:
    case 0x808u:
    case 0x810u:
    case 0x818u:
    case 0x820u:
    case 0x828u:
    case 0x830u:
    case 0x838u:
    case 0x840u:
    case 0x848u:
    case 0x850u:
    case 0x858u:
    case 0x860u:
    case 0x868u:
    case 0x870u:
    case 0x878u:
    case 0x880u:
    case 0x888u:
    case 0x890u:
    case 0x898u:
    case 0x8A0u:
    case 0x8A8u:
    case 0x8B0u:
    case 0x8B8u:
    case 0x8C0u:
    case 0x8C8u:
    case 0x8D0u:
    case 0x8D8u:
    case 0x8E0u:
    case 0x8E8u:
    case 0x8F0u:
    case 0x8F8u:
    case 0x900u:
    case 0x908u:
    case 0x910u:
    case 0x918u:
    case 0x920u:
    case 0x928u:
    case 0x930u:
    case 0x938u:
    case 0x940u:
    case 0x948u:
    case 0x950u:
    case 0x958u:
    case 0x960u:
    case 0x968u:
    case 0x970u:
    case 0x978u:
    case 0x980u:
    case 0x988u:
    case 0x990u:
    case 0x998u:
    case 0x9A0u:
    case 0x9A8u:
    case 0x9B0u:
    case 0x9B8u:
    case 0x9C0u:
    case 0x9C8u:
    case 0x9D0u:
    case 0x9D8u:
    case 0x9E0u:
    case 0x9E8u:
    case 0x9F0u:
    case 0x9F8u:
    case 0xA00u:
    case 0xA08u:
    case 0xA10u:
    case 0xA18u:
    case 0xA20u:
    case 0xA28u:
    case 0xA30u:
    case 0xA38u:
    case 0xA40u:
    case 0xA48u:
    case 0xA50u:
    case 0xA58u:
    case 0xA60u:
    case 0xA68u:
    case 0xA70u:
    case 0xA78u:
    case 0xA80u:
    case 0xA88u:
    case 0xA90u:
    case 0xA98u:
    case 0xAA0u:
    case 0xAA8u:
    case 0xAB0u:
    case 0xAB8u:
    case 0xAC0u:
    case 0xAC8u:
    case 0xAD0u:
    case 0xAD8u:
    case 0xAE0u:
    case 0xAE8u:
    case 0xAF0u:
    case 0xAF8u:
    case 0xB00u:
    case 0xB08u:
    case 0xB10u:
    case 0xB18u:
    case 0xB20u:
    case 0xB28u:
    case 0xB30u:
    case 0xB38u:
    case 0xB40u:
    case 0xB48u:
    case 0xB50u:
    case 0xB58u:
    case 0xB60u:
    case 0xB68u:
    case 0xB70u:
    case 0xB78u:
    case 0xB80u:
    case 0xB88u:
    case 0xB90u:
    case 0xB98u:
    case 0xBA0u:
    case 0xBA8u:
    case 0xBB0u:
    case 0xBB8u:
    case 0xBC0u:
    case 0xBC8u:
    case 0xBD0u:
    case 0xBD8u:
    case 0xBE0u:
    case 0xBE8u:
    case 0xBF0u:
    case 0xBF8u:
    case 0xC00u:
    case 0xC08u:
    case 0xC10u:
    case 0xC18u:
    case 0xC20u:
    case 0xC28u:
    case 0xC30u:
    case 0xC38u:
    case 0xC40u:
    case 0xC48u:
    case 0xC50u:
    case 0xC58u:
    case 0xC60u:
    case 0xC68u:
    case 0xC70u:
    case 0xC78u:
    case 0xC80u:
    case 0xC88u:
    case 0xC90u:
    case 0xC98u:
    case 0xCA0u:
    case 0xCA8u:
    case 0xCB0u:
    case 0xCB8u:
    case 0xCC0u:
    case 0xCC8u:
    case 0xCD0u:
    case 0xCD8u:
    case 0xCE0u:
    case 0xCE8u:
    case 0xCF0u:
    case 0xCF8u:
    case 0xD00u:
    case 0xD08u:
    case 0xD10u:
    case 0xD18u:
    case 0xD20u:
    case 0xD28u:
    case 0xD30u:
    case 0xD38u:
    case 0xD40u:
    case 0xD48u:
    case 0xD50u:
    case 0xD58u:
    case 0xD60u:
    case 0xD68u:
    case 0xD70u:
    case 0xD78u:
    case 0xD80u:
    case 0xD88u:
    case 0xD90u:
    case 0xD98u:
    case 0xDA0u:
    case 0xDA8u:
    case 0xDB0u:
    case 0xDB8u:
    case 0xDC0u:
    case 0xDC8u:
    case 0xDD0u:
    case 0xDD8u:
    case 0xDE0u:
    case 0xDE8u:
    case 0xDF0u:
    case 0xDF8u:
    case 0xE00u:
    case 0xE08u:
    case 0xE10u:
    case 0xE18u:
    case 0xE20u:
    case 0xE28u:
    case 0xE30u:
    case 0xE38u:
    case 0xE40u:
    case 0xE48u:
    case 0xE50u:
    case 0xE58u:
    case 0xE60u:
    case 0xE68u:
    case 0xE70u:
    case 0xE78u:
    case 0xE80u:
    case 0xE88u:
    case 0xE90u:
    case 0xE98u:
    case 0xEA0u:
    case 0xEA8u:
    case 0xEB0u:
    case 0xEB8u:
    case 0xEC0u:
    case 0xEC8u:
    case 0xED0u:
    case 0xED8u:
    case 0xEE0u:
    case 0xEE8u:
    case 0xEF0u:
    case 0xEF8u:
    case 0xF00u:
    case 0xF08u:
    case 0xF10u:
    case 0xF18u:
    case 0xF20u:
    case 0xF28u:
    case 0xF30u:
    case 0xF38u:
    case 0xF40u:
    case 0xF48u:
    case 0xF50u:
    case 0xF58u:
    case 0xF60u:
    case 0xF68u:
    case 0xF70u:
    case 0xF78u:
    case 0xF80u:
    case 0xF88u:
    case 0xF90u:
    case 0xF98u:
    case 0xFA0u:
    case 0xFA8u:
    case 0xFB0u:
    case 0xFB8u:
    case 0xFC0u:
    case 0xFC8u:
    case 0xFD0u:
    case 0xFD8u:
    case 0xFE0u:
    case 0xFE8u:
    case 0xFF0u:
    case 0xFF8u:
    case 0x1000u:
    case 0x1008u:
    case 0x1010u:
    case 0x1018u:
    case 0x1020u:
    case 0x1028u:
    case 0x1030u:
    case 0x1038u:
    case 0x1040u:
    case 0x1048u:
    case 0x1050u:
    case 0x1058u:
    case 0x1060u:
    case 0x1068u:
    case 0x1070u:
    case 0x1078u:
    case 0x1080u:
    case 0x1088u:
    case 0x1090u:
    case 0x1098u:
    case 0x10A0u:
    case 0x10A8u:
    case 0x10B0u:
    case 0x10B8u:
    case 0x10C0u:
    case 0x10C8u:
    case 0x10D0u:
    case 0x10D8u:
    case 0x10E0u:
    case 0x10E8u:
    case 0x10F0u:
    case 0x10F8u:
    case 0x1100u:
    case 0x1108u:
    case 0x1110u:
    case 0x1118u:
    case 0x1120u:
    case 0x1128u:
    case 0x1130u:
    case 0x1138u:
    case 0x1140u:
    case 0x1148u:
    case 0x1150u:
    case 0x1158u:
    case 0x1160u:
    case 0x1168u:
    case 0x1170u:
    case 0x1178u:
    case 0x1180u:
    case 0x1188u:
    case 0x1190u:
    case 0x1198u:
    case 0x11A0u:
    case 0x11A8u:
    case 0x11B0u:
    case 0x11B8u:
    case 0x11C0u:
    case 0x11C8u:
    case 0x11D0u:
    case 0x11D8u:
    case 0x11E0u:
    case 0x11E8u:
    case 0x11F0u:
    case 0x11F8u:
    case 0x1200u:
    case 0x1208u:
    case 0x1210u:
    case 0x1218u:
    case 0x1220u:
    case 0x1228u:
    case 0x1230u:
    case 0x1238u:
    case 0x1240u:
    case 0x1248u:
    case 0x1250u:
    case 0x1258u:
    case 0x1260u:
    case 0x1268u:
    case 0x1270u:
    case 0x1278u:
    case 0x1280u:
    case 0x1288u:
    case 0x1290u:
    case 0x1298u:
    case 0x12A0u:
    case 0x12A8u:
    case 0x12B0u:
    case 0x12B8u:
    case 0x12C0u:
    case 0x12C8u:
    case 0x12D0u:
    case 0x12D8u:
    case 0x12E0u:
    case 0x12E8u:
    case 0x12F0u:
    case 0x12F8u:
    case 0x1300u:
    case 0x1308u:
    case 0x1310u:
    case 0x1318u:
    case 0x1320u:
    case 0x1328u:
    case 0x1330u:
    case 0x1338u:
    case 0x1340u:
    case 0x1348u:
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
    case 0x440u: goto L0440;
    case 0x448u: goto L0448;
    case 0x450u: goto L0450;
    case 0x458u: goto L0458;
    case 0x460u: goto L0460;
    case 0x468u: goto L0468;
    case 0x470u: goto L0470;
    case 0x478u: goto L0478;
    case 0x480u: goto L0480;
    case 0x488u: goto L0488;
    case 0x490u: goto L0490;
    case 0x498u: goto L0498;
    case 0x4A0u: goto L04A0;
    case 0x4A8u: goto L04A8;
    case 0x4B0u: goto L04B0;
    case 0x4B8u: goto L04B8;
    case 0x4C0u: goto L04C0;
    case 0x4C8u: goto L04C8;
    case 0x4D0u: goto L04D0;
    case 0x4D8u: goto L04D8;
    case 0x4E0u: goto L04E0;
    case 0x4E8u: goto L04E8;
    case 0x4F0u: goto L04F0;
    case 0x4F8u: goto L04F8;
    case 0x500u: goto L0500;
    case 0x508u: goto L0508;
    case 0x510u: goto L0510;
    case 0x518u: goto L0518;
    case 0x520u: goto L0520;
    case 0x528u: goto L0528;
    case 0x530u: goto L0530;
    case 0x538u: goto L0538;
    case 0x540u: goto L0540;
    case 0x548u: goto L0548;
    case 0x550u: goto L0550;
    case 0x558u: goto L0558;
    case 0x560u: goto L0560;
    case 0x568u: goto L0568;
    case 0x570u: goto L0570;
    case 0x578u: goto L0578;
    case 0x580u: goto L0580;
    case 0x588u: goto L0588;
    case 0x590u: goto L0590;
    case 0x598u: goto L0598;
    case 0x5A0u: goto L05A0;
    case 0x5A8u: goto L05A8;
    case 0x5B0u: goto L05B0;
    case 0x5B8u: goto L05B8;
    case 0x5C0u: goto L05C0;
    case 0x5C8u: goto L05C8;
    case 0x5D0u: goto L05D0;
    case 0x5D8u: goto L05D8;
    case 0x5E0u: goto L05E0;
    case 0x5E8u: goto L05E8;
    case 0x5F0u: goto L05F0;
    case 0x5F8u: goto L05F8;
    case 0x600u: goto L0600;
    case 0x608u: goto L0608;
    case 0x610u: goto L0610;
    case 0x618u: goto L0618;
    case 0x620u: goto L0620;
    case 0x628u: goto L0628;
    case 0x630u: goto L0630;
    case 0x638u: goto L0638;
    case 0x640u: goto L0640;
    case 0x648u: goto L0648;
    case 0x650u: goto L0650;
    case 0x658u: goto L0658;
    case 0x660u: goto L0660;
    case 0x668u: goto L0668;
    case 0x670u: goto L0670;
    case 0x678u: goto L0678;
    case 0x680u: goto L0680;
    case 0x688u: goto L0688;
    case 0x690u: goto L0690;
    case 0x698u: goto L0698;
    case 0x6A0u: goto L06A0;
    case 0x6A8u: goto L06A8;
    case 0x6B0u: goto L06B0;
    case 0x6B8u: goto L06B8;
    case 0x6C0u: goto L06C0;
    case 0x6C8u: goto L06C8;
    case 0x6D0u: goto L06D0;
    case 0x6D8u: goto L06D8;
    case 0x6E0u: goto L06E0;
    case 0x6E8u: goto L06E8;
    case 0x6F0u: goto L06F0;
    case 0x6F8u: goto L06F8;
    case 0x700u: goto L0700;
    case 0x708u: goto L0708;
    case 0x710u: goto L0710;
    case 0x718u: goto L0718;
    case 0x720u: goto L0720;
    case 0x728u: goto L0728;
    case 0x730u: goto L0730;
    case 0x738u: goto L0738;
    case 0x740u: goto L0740;
    case 0x748u: goto L0748;
    case 0x750u: goto L0750;
    case 0x758u: goto L0758;
    case 0x760u: goto L0760;
    case 0x768u: goto L0768;
    case 0x770u: goto L0770;
    case 0x778u: goto L0778;
    case 0x780u: goto L0780;
    case 0x788u: goto L0788;
    case 0x790u: goto L0790;
    case 0x798u: goto L0798;
    case 0x7A0u: goto L07A0;
    case 0x7A8u: goto L07A8;
    case 0x7B0u: goto L07B0;
    case 0x7B8u: goto L07B8;
    case 0x7C0u: goto L07C0;
    case 0x7C8u: goto L07C8;
    case 0x7D0u: goto L07D0;
    case 0x7D8u: goto L07D8;
    case 0x7E0u: goto L07E0;
    case 0x7E8u: goto L07E8;
    case 0x7F0u: goto L07F0;
    case 0x7F8u: goto L07F8;
    case 0x800u: goto L0800;
    case 0x808u: goto L0808;
    case 0x810u: goto L0810;
    case 0x818u: goto L0818;
    case 0x820u: goto L0820;
    case 0x828u: goto L0828;
    case 0x830u: goto L0830;
    case 0x838u: goto L0838;
    case 0x840u: goto L0840;
    case 0x848u: goto L0848;
    case 0x850u: goto L0850;
    case 0x858u: goto L0858;
    case 0x860u: goto L0860;
    case 0x868u: goto L0868;
    case 0x870u: goto L0870;
    case 0x878u: goto L0878;
    case 0x880u: goto L0880;
    case 0x888u: goto L0888;
    case 0x890u: goto L0890;
    case 0x898u: goto L0898;
    case 0x8A0u: goto L08A0;
    case 0x8A8u: goto L08A8;
    case 0x8B0u: goto L08B0;
    case 0x8B8u: goto L08B8;
    case 0x8C0u: goto L08C0;
    case 0x8C8u: goto L08C8;
    case 0x8D0u: goto L08D0;
    case 0x8D8u: goto L08D8;
    case 0x8E0u: goto L08E0;
    case 0x8E8u: goto L08E8;
    case 0x8F0u: goto L08F0;
    case 0x8F8u: goto L08F8;
    case 0x900u: goto L0900;
    case 0x908u: goto L0908;
    case 0x910u: goto L0910;
    case 0x918u: goto L0918;
    case 0x920u: goto L0920;
    case 0x928u: goto L0928;
    case 0x930u: goto L0930;
    case 0x938u: goto L0938;
    case 0x940u: goto L0940;
    case 0x948u: goto L0948;
    case 0x950u: goto L0950;
    case 0x958u: goto L0958;
    case 0x960u: goto L0960;
    case 0x968u: goto L0968;
    case 0x970u: goto L0970;
    case 0x978u: goto L0978;
    case 0x980u: goto L0980;
    case 0x988u: goto L0988;
    case 0x990u: goto L0990;
    case 0x998u: goto L0998;
    case 0x9A0u: goto L09A0;
    case 0x9A8u: goto L09A8;
    case 0x9B0u: goto L09B0;
    case 0x9B8u: goto L09B8;
    case 0x9C0u: goto L09C0;
    case 0x9C8u: goto L09C8;
    case 0x9D0u: goto L09D0;
    case 0x9D8u: goto L09D8;
    case 0x9E0u: goto L09E0;
    case 0x9E8u: goto L09E8;
    case 0x9F0u: goto L09F0;
    case 0x9F8u: goto L09F8;
    case 0xA00u: goto L0A00;
    case 0xA08u: goto L0A08;
    case 0xA10u: goto L0A10;
    case 0xA18u: goto L0A18;
    case 0xA20u: goto L0A20;
    case 0xA28u: goto L0A28;
    case 0xA30u: goto L0A30;
    case 0xA38u: goto L0A38;
    case 0xA40u: goto L0A40;
    case 0xA48u: goto L0A48;
    case 0xA50u: goto L0A50;
    case 0xA58u: goto L0A58;
    case 0xA60u: goto L0A60;
    case 0xA68u: goto L0A68;
    case 0xA70u: goto L0A70;
    case 0xA78u: goto L0A78;
    case 0xA80u: goto L0A80;
    case 0xA88u: goto L0A88;
    case 0xA90u: goto L0A90;
    case 0xA98u: goto L0A98;
    case 0xAA0u: goto L0AA0;
    case 0xAA8u: goto L0AA8;
    case 0xAB0u: goto L0AB0;
    case 0xAB8u: goto L0AB8;
    case 0xAC0u: goto L0AC0;
    case 0xAC8u: goto L0AC8;
    case 0xAD0u: goto L0AD0;
    case 0xAD8u: goto L0AD8;
    case 0xAE0u: goto L0AE0;
    case 0xAE8u: goto L0AE8;
    case 0xAF0u: goto L0AF0;
    case 0xAF8u: goto L0AF8;
    case 0xB00u: goto L0B00;
    case 0xB08u: goto L0B08;
    case 0xB10u: goto L0B10;
    case 0xB18u: goto L0B18;
    case 0xB20u: goto L0B20;
    case 0xB28u: goto L0B28;
    case 0xB30u: goto L0B30;
    case 0xB38u: goto L0B38;
    case 0xB40u: goto L0B40;
    case 0xB48u: goto L0B48;
    case 0xB50u: goto L0B50;
    case 0xB58u: goto L0B58;
    case 0xB60u: goto L0B60;
    case 0xB68u: goto L0B68;
    case 0xB70u: goto L0B70;
    case 0xB78u: goto L0B78;
    case 0xB80u: goto L0B80;
    case 0xB88u: goto L0B88;
    case 0xB90u: goto L0B90;
    case 0xB98u: goto L0B98;
    case 0xBA0u: goto L0BA0;
    case 0xBA8u: goto L0BA8;
    case 0xBB0u: goto L0BB0;
    case 0xBB8u: goto L0BB8;
    case 0xBC0u: goto L0BC0;
    case 0xBC8u: goto L0BC8;
    case 0xBD0u: goto L0BD0;
    case 0xBD8u: goto L0BD8;
    case 0xBE0u: goto L0BE0;
    case 0xBE8u: goto L0BE8;
    case 0xBF0u: goto L0BF0;
    case 0xBF8u: goto L0BF8;
    case 0xC00u: goto L0C00;
    case 0xC08u: goto L0C08;
    case 0xC10u: goto L0C10;
    case 0xC18u: goto L0C18;
    case 0xC20u: goto L0C20;
    case 0xC28u: goto L0C28;
    case 0xC30u: goto L0C30;
    case 0xC38u: goto L0C38;
    case 0xC40u: goto L0C40;
    case 0xC48u: goto L0C48;
    case 0xC50u: goto L0C50;
    case 0xC58u: goto L0C58;
    case 0xC60u: goto L0C60;
    case 0xC68u: goto L0C68;
    case 0xC70u: goto L0C70;
    case 0xC78u: goto L0C78;
    case 0xC80u: goto L0C80;
    case 0xC88u: goto L0C88;
    case 0xC90u: goto L0C90;
    case 0xC98u: goto L0C98;
    case 0xCA0u: goto L0CA0;
    case 0xCA8u: goto L0CA8;
    case 0xCB0u: goto L0CB0;
    case 0xCB8u: goto L0CB8;
    case 0xCC0u: goto L0CC0;
    case 0xCC8u: goto L0CC8;
    case 0xCD0u: goto L0CD0;
    case 0xCD8u: goto L0CD8;
    case 0xCE0u: goto L0CE0;
    case 0xCE8u: goto L0CE8;
    case 0xCF0u: goto L0CF0;
    case 0xCF8u: goto L0CF8;
    case 0xD00u: goto L0D00;
    case 0xD08u: goto L0D08;
    case 0xD10u: goto L0D10;
    case 0xD18u: goto L0D18;
    case 0xD20u: goto L0D20;
    case 0xD28u: goto L0D28;
    case 0xD30u: goto L0D30;
    case 0xD38u: goto L0D38;
    case 0xD40u: goto L0D40;
    case 0xD48u: goto L0D48;
    case 0xD50u: goto L0D50;
    case 0xD58u: goto L0D58;
    case 0xD60u: goto L0D60;
    case 0xD68u: goto L0D68;
    case 0xD70u: goto L0D70;
    case 0xD78u: goto L0D78;
    case 0xD80u: goto L0D80;
    case 0xD88u: goto L0D88;
    case 0xD90u: goto L0D90;
    case 0xD98u: goto L0D98;
    case 0xDA0u: goto L0DA0;
    case 0xDA8u: goto L0DA8;
    case 0xDB0u: goto L0DB0;
    case 0xDB8u: goto L0DB8;
    case 0xDC0u: goto L0DC0;
    case 0xDC8u: goto L0DC8;
    case 0xDD0u: goto L0DD0;
    case 0xDD8u: goto L0DD8;
    case 0xDE0u: goto L0DE0;
    case 0xDE8u: goto L0DE8;
    case 0xDF0u: goto L0DF0;
    case 0xDF8u: goto L0DF8;
    case 0xE00u: goto L0E00;
    case 0xE08u: goto L0E08;
    case 0xE10u: goto L0E10;
    case 0xE18u: goto L0E18;
    case 0xE20u: goto L0E20;
    case 0xE28u: goto L0E28;
    case 0xE30u: goto L0E30;
    case 0xE38u: goto L0E38;
    case 0xE40u: goto L0E40;
    case 0xE48u: goto L0E48;
    case 0xE50u: goto L0E50;
    case 0xE58u: goto L0E58;
    case 0xE60u: goto L0E60;
    case 0xE68u: goto L0E68;
    case 0xE70u: goto L0E70;
    case 0xE78u: goto L0E78;
    case 0xE80u: goto L0E80;
    case 0xE88u: goto L0E88;
    case 0xE90u: goto L0E90;
    case 0xE98u: goto L0E98;
    case 0xEA0u: goto L0EA0;
    case 0xEA8u: goto L0EA8;
    case 0xEB0u: goto L0EB0;
    case 0xEB8u: goto L0EB8;
    case 0xEC0u: goto L0EC0;
    case 0xEC8u: goto L0EC8;
    case 0xED0u: goto L0ED0;
    case 0xED8u: goto L0ED8;
    case 0xEE0u: goto L0EE0;
    case 0xEE8u: goto L0EE8;
    case 0xEF0u: goto L0EF0;
    case 0xEF8u: goto L0EF8;
    case 0xF00u: goto L0F00;
    case 0xF08u: goto L0F08;
    case 0xF10u: goto L0F10;
    case 0xF18u: goto L0F18;
    case 0xF20u: goto L0F20;
    case 0xF28u: goto L0F28;
    case 0xF30u: goto L0F30;
    case 0xF38u: goto L0F38;
    case 0xF40u: goto L0F40;
    case 0xF48u: goto L0F48;
    case 0xF50u: goto L0F50;
    case 0xF58u: goto L0F58;
    case 0xF60u: goto L0F60;
    case 0xF68u: goto L0F68;
    case 0xF70u: goto L0F70;
    case 0xF78u: goto L0F78;
    case 0xF80u: goto L0F80;
    case 0xF88u: goto L0F88;
    case 0xF90u: goto L0F90;
    case 0xF98u: goto L0F98;
    case 0xFA0u: goto L0FA0;
    case 0xFA8u: goto L0FA8;
    case 0xFB0u: goto L0FB0;
    case 0xFB8u: goto L0FB8;
    case 0xFC0u: goto L0FC0;
    case 0xFC8u: goto L0FC8;
    case 0xFD0u: goto L0FD0;
    case 0xFD8u: goto L0FD8;
    case 0xFE0u: goto L0FE0;
    case 0xFE8u: goto L0FE8;
    case 0xFF0u: goto L0FF0;
    case 0xFF8u: goto L0FF8;
    case 0x1000u: goto L1000;
    case 0x1008u: goto L1008;
    case 0x1010u: goto L1010;
    case 0x1018u: goto L1018;
    case 0x1020u: goto L1020;
    case 0x1028u: goto L1028;
    case 0x1030u: goto L1030;
    case 0x1038u: goto L1038;
    case 0x1040u: goto L1040;
    case 0x1048u: goto L1048;
    case 0x1050u: goto L1050;
    case 0x1058u: goto L1058;
    case 0x1060u: goto L1060;
    case 0x1068u: goto L1068;
    case 0x1070u: goto L1070;
    case 0x1078u: goto L1078;
    case 0x1080u: goto L1080;
    case 0x1088u: goto L1088;
    case 0x1090u: goto L1090;
    case 0x1098u: goto L1098;
    case 0x10A0u: goto L10A0;
    case 0x10A8u: goto L10A8;
    case 0x10B0u: goto L10B0;
    case 0x10B8u: goto L10B8;
    case 0x10C0u: goto L10C0;
    case 0x10C8u: goto L10C8;
    case 0x10D0u: goto L10D0;
    case 0x10D8u: goto L10D8;
    case 0x10E0u: goto L10E0;
    case 0x10E8u: goto L10E8;
    case 0x10F0u: goto L10F0;
    case 0x10F8u: goto L10F8;
    case 0x1100u: goto L1100;
    case 0x1108u: goto L1108;
    case 0x1110u: goto L1110;
    case 0x1118u: goto L1118;
    case 0x1120u: goto L1120;
    case 0x1128u: goto L1128;
    case 0x1130u: goto L1130;
    case 0x1138u: goto L1138;
    case 0x1140u: goto L1140;
    case 0x1148u: goto L1148;
    case 0x1150u: goto L1150;
    case 0x1158u: goto L1158;
    case 0x1160u: goto L1160;
    case 0x1168u: goto L1168;
    case 0x1170u: goto L1170;
    case 0x1178u: goto L1178;
    case 0x1180u: goto L1180;
    case 0x1188u: goto L1188;
    case 0x1190u: goto L1190;
    case 0x1198u: goto L1198;
    case 0x11A0u: goto L11A0;
    case 0x11A8u: goto L11A8;
    case 0x11B0u: goto L11B0;
    case 0x11B8u: goto L11B8;
    case 0x11C0u: goto L11C0;
    case 0x11C8u: goto L11C8;
    case 0x11D0u: goto L11D0;
    case 0x11D8u: goto L11D8;
    case 0x11E0u: goto L11E0;
    case 0x11E8u: goto L11E8;
    case 0x11F0u: goto L11F0;
    case 0x11F8u: goto L11F8;
    case 0x1200u: goto L1200;
    case 0x1208u: goto L1208;
    case 0x1210u: goto L1210;
    case 0x1218u: goto L1218;
    case 0x1220u: goto L1220;
    case 0x1228u: goto L1228;
    case 0x1230u: goto L1230;
    case 0x1238u: goto L1238;
    case 0x1240u: goto L1240;
    case 0x1248u: goto L1248;
    case 0x1250u: goto L1250;
    case 0x1258u: goto L1258;
    case 0x1260u: goto L1260;
    case 0x1268u: goto L1268;
    case 0x1270u: goto L1270;
    case 0x1278u: goto L1278;
    case 0x1280u: goto L1280;
    case 0x1288u: goto L1288;
    case 0x1290u: goto L1290;
    case 0x1298u: goto L1298;
    case 0x12A0u: goto L12A0;
    case 0x12A8u: goto L12A8;
    case 0x12B0u: goto L12B0;
    case 0x12B8u: goto L12B8;
    case 0x12C0u: goto L12C0;
    case 0x12C8u: goto L12C8;
    case 0x12D0u: goto L12D0;
    case 0x12D8u: goto L12D8;
    case 0x12E0u: goto L12E0;
    case 0x12E8u: goto L12E8;
    case 0x12F0u: goto L12F0;
    case 0x12F8u: goto L12F8;
    case 0x1300u: goto L1300;
    case 0x1308u: goto L1308;
    case 0x1310u: goto L1310;
    case 0x1318u: goto L1318;
    case 0x1320u: goto L1320;
    case 0x1328u: goto L1328;
    case 0x1330u: goto L1330;
    case 0x1338u: goto L1338;
    case 0x1340u: goto L1340;
    case 0x1348u: goto L1348;
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
    st.branchTarget = 0x60u;
    { // pair 2 pc=0x10 up=0x000002FF lo=0x40000009
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
    goto L0060;
    L0018:;
    { // pair 3 pc=0x18 up=0x000002FF lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    L0020:;
    st.branchTarget = 0xD0u;
    { // pair 4 pc=0x20 up=0x000002FF lo=0x40000015
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
    goto L00D0;
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
    st.branchTarget = 0x200u;
    { // pair 6 pc=0x30 up=0x000002FF lo=0x40000039
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
    goto L0200;
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
    st.branchTarget = 0x340u;
    { // pair 8 pc=0x40 up=0x000002FF lo=0x4000005F
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
    goto L0340;
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
    st.branchTarget = 0x4B8u;
    { // pair 10 pc=0x50 up=0x000002FF lo=0x4000008C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    { // pair 11 pc=0x58 up=0x000002FF lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    goto L04B8;
    L0058:;
    { // pair 11 pc=0x58 up=0x000002FF lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    L0060:;
    { // pair 12 pc=0x60 up=0x000002FF lo=0x10010387
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[0] + 903); bvOld = st.vi[1]; bvReg = 1; st.vi[1] = nv; }
      }
      cx.viR[1] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L0068:;
    { // pair 13 pc=0x68 up=0x000002FF lo=0x088D0390
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
    L0070:;
    { // pair 14 pc=0x70 up=0x000002FF lo=0x100E03D3
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[0] + 979); bvOld = st.vi[14]; bvReg = 14; st.vi[14] = nv; }
      }
      c += 1u;
    }
    L0078:;
    { // pair 15 pc=0x78 up=0x000002FF lo=0x013A0392
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 914) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[26][0], vm + addr + 0u, 4);
          std::memcpy(&st.vf[26][3], vm + addr + 12u, 4);
        }
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[26] = rt;
        cx.vfR[26][0] = rt;
        cx.vfR[26][3] = rt;
      }
      c += 1u;
    }
    L0080:;
    { // pair 16 pc=0x80 up=0x000002FF lo=0x01D70395
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
    L0088:;
    { // pair 17 pc=0x88 up=0x000002FF lo=0x01F803AC
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
    L0090:;
    { // pair 18 pc=0x90 up=0x000002FF lo=0x01FB038E
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
    L0098:;
    { // pair 19 pc=0x98 up=0x000002FF lo=0x81F9D33D
      c = vu1gen::vmax(c, cx.vfRAny[26]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        const float mv0 = st.vf[26][1];
        const float mv1 = st.vf[26][2];
        const float mv2 = st.vf[26][3];
        const float mv3 = st.vf[26][0];
        st.vf[25][0] = mv0;
        st.vf[25][1] = mv1;
        st.vf[25][2] = mv2;
        st.vf[25][3] = mv3;
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[25] = rt;
        _mm_store_si128((__m128i *)cx.vfR[25], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L00A0:;
    { // pair 20 pc=0xA0 up=0x01D7B93D lo=0x01DA038C
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
    L00A8:;
    { // pair 21 pc=0xA8 up=0x000002FF lo=0x01FC0800
      c = vu1gen::vmax(c, cx.viR[1]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[1] + 0) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[28][0], vm + addr + 0u, 16);
        }
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[28] = rt;
        _mm_store_si128((__m128i *)cx.vfR[28], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L00B0:;
    { // pair 22 pc=0xB0 up=0x000002FF lo=0x01FD0801
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
    L00B8:;
    { // pair 23 pc=0xB8 up=0x000002FF lo=0x01FE0802
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
    L00C0:;
    { // pair 24 pc=0xC0 up=0x400002FF lo=0x01FF0803
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
    { // pair 25 pc=0xC8 up=0x000002FF lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    st.pc = 0xD0u; goto END_OUT;
    L00C8:;
    { // pair 25 pc=0xC8 up=0x000002FF lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    L00D0:;
    { // pair 26 pc=0xD0 up=0x000002FF lo=0x800706BC
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        st.vi[7] = (int32_t)(st.top & 0x3FFu);
      }
      bvReg = -1;
      cx.viR[7] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L00D8:;
    { // pair 27 pc=0xD8 up=0x000002FF lo=0x08223800
      c = vu1gen::vmax(c, cx.viR[7]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[7] + 0) * 16u) & 0x3FFFu;
          uint32_t v = 0u; std::memcpy(&v, vm + addr + 12u, 4);
          st.vi[2] = (int32_t)(int16_t)(v & 0xFFFFu);
        }
      }
      bvReg = -1;
      cx.viR[2] = (uint32_t)(c + 4u);
      c += 1u;
    }
    L00E0:;
    { // pair 28 pc=0xE0 up=0x000002FF lo=0x10830000
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[0] + 8192); bvOld = st.vi[3]; bvReg = 3; st.vi[3] = nv; }
      }
      cx.viR[3] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L00E8:;
    { const bool bt = (int16_t)0 == (int16_t)(bvReg == 1 ? bvOld : st.vi[1]);
    { // pair 29 pc=0xE8 up=0x000002FF lo=0x50010005
      c = vu1gen::vmax(c, cx.viR[1]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    { // pair 30 pc=0xF0 up=0x000002FF lo=0x009603CF
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
      st.branchTarget = 0x118u;
      goto L0118;
    } }
    goto LC00F8;
    L00F0:;
    { // pair 30 pc=0xF0 up=0x000002FF lo=0x009603CF
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
    LC00F8:;
    L00F8:;
    { // pair 31 pc=0xF8 up=0x000002FF lo=0x800310F4
      c = vu1gen::vmax(c, cx.viR[2]);
      c = vu1gen::vmax(c, cx.viR[3]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[2] & st.vi[3]); bvOld = st.vi[3]; bvReg = 3; st.vi[3] = nv; }
      }
      cx.viR[3] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L0100:;
    { // pair 32 pc=0x100 up=0x000002FF lo=0x009503D0
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 976) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[21][1], vm + addr + 4u, 4);
        }
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[21] = rt;
        cx.vfR[21][1] = rt;
      }
      c += 1u;
    }
    L0108:;
    { const bool bt = (int16_t)0 == (int16_t)(bvReg == 3 ? bvOld : st.vi[3]);
    { // pair 33 pc=0x108 up=0x000002FF lo=0x50030003
      c = vu1gen::vmax(c, cx.viR[3]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    { // pair 34 pc=0x110 up=0x000002FF lo=0x01E103A6
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
    if (bt) {
      st.branchTarget = 0x128u;
      goto L0128;
    } }
    goto LC0118;
    L0110:;
    { // pair 34 pc=0x110 up=0x000002FF lo=0x01E103A6
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
    LC0118:;
    L0118:;
    { // pair 35 pc=0x118 up=0x400002FF lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    { // pair 36 pc=0x120 up=0x000002FF lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    st.pc = 0x128u; goto END_OUT;
    L0120:;
    { // pair 36 pc=0x120 up=0x000002FF lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    L0128:;
    { // pair 37 pc=0x128 up=0x000002FF lo=0x01E203AA
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
    L0130:;
    { // pair 38 pc=0x130 up=0x000002FF lo=0x100838C8
      c = vu1gen::vmax(c, cx.viR[7]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[7] + 200); bvOld = st.vi[8]; bvReg = 8; st.vi[8] = nv; }
      }
      c += 1u;
    }
    L0138:;
    { // pair 39 pc=0x138 up=0x000002FF lo=0x10073902
      c = vu1gen::vmax(c, cx.viR[7]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[7] + 258); bvOld = st.vi[7]; bvReg = 7; st.vi[7] = nv; }
      }
      cx.viR[7] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L0140:;
    { // pair 40 pc=0x140 up=0x000002FF lo=0x090A3804
      c = vu1gen::vmax(c, cx.viR[7]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[7] + 4) * 16u) & 0x3FFFu;
          uint32_t v = 0u; std::memcpy(&v, vm + addr + 0u, 4);
          st.vi[10] = (int32_t)(int16_t)(v & 0xFFFFu);
        }
      }
      bvReg = -1;
      cx.viR[10] = (uint32_t)(c + 4u);
      c += 1u;
    }
    L0148:;
    { // pair 41 pc=0x148 up=0x000002FF lo=0x03E70802
      c = vu1gen::vmax(c, cx.vfRAny[1]);
      c = vu1gen::vmax(c, cx.viR[7]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[7] + 2) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[1][0], 16);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L0150:;
    { // pair 42 pc=0x150 up=0x000002FF lo=0x03E71003
      c = vu1gen::vmax(c, cx.vfRAny[2]);
      c = vu1gen::vmax(c, cx.viR[7]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[7] + 3) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[2][0], 16);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L0158:;
    { // pair 43 pc=0x158 up=0x000002FF lo=0x0287B004
      c = vu1gen::vmax(c, cx.vfR[22][1]);
      c = vu1gen::vmax(c, cx.viR[7]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[7] + 4) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 4u, &st.vf[22][1], 4);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L0160:;
    { // pair 44 pc=0x160 up=0x000002FF lo=0x81D4437C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(uint16_t)st.vi[8] * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[20][0], vm + addr + 0u, 12);
        }
        { const int32_t nv = (int32_t)(int16_t)(st.vi[8] + 1); bvOld = st.vi[8]; bvReg = 8; st.vi[8] = nv; }
      }
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[20] = rt;
        cx.vfR[20][0] = rt;
        cx.vfR[20][1] = rt;
        cx.vfR[20][2] = rt;
      }
      c += 1u;
    }
    L0168:;
    { // pair 45 pc=0x168 up=0x000002FF lo=0x100B3805
      c = vu1gen::vmax(c, cx.viR[7]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[7] + 5); bvOld = st.vi[11]; bvReg = 11; st.vi[11] = nv; }
      }
      c += 1u;
    }
    L0170:;
    { // pair 46 pc=0x170 up=0x000002FF lo=0x11EC07FF
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[0] + 32767); bvOld = st.vi[12]; bvReg = 12; st.vi[12] = nv; }
      }
      c += 1u;
    }
    L0178:;
    { // pair 47 pc=0x178 up=0x000002FF lo=0x800D5274
      c = vu1gen::vmax(c, cx.viR[10]);
      c = vu1gen::vmax(c, cx.viR[13]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[10] & st.vi[13]); bvOld = st.vi[9]; bvReg = 9; st.vi[9] = nv; }
      }
      cx.viR[9] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L0180:;
    { // pair 48 pc=0x180 up=0x01D3A17C lo=0x800C52B4
      c = vu1gen::vmax(c, cx.vfR[20][0]);
      c = vu1gen::vmax(c, cx.vfR[20][1]);
      c = vu1gen::vmax(c, cx.vfR[20][2]);
      c = vu1gen::vmax(c, cx.viR[10]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      float ur0 = 0.0f;
      float ur1 = 0.0f;
      float ur2 = 0.0f;
      {
        { const int32_t iv = vu1gen::ftoi(vu1gen::nrm(st.vf[20][0]), 1.0f);
          std::memcpy(&ur0, &iv, 4); }
        { const int32_t iv = vu1gen::ftoi(vu1gen::nrm(st.vf[20][1]), 1.0f);
          std::memcpy(&ur1, &iv, 4); }
        { const int32_t iv = vu1gen::ftoi(vu1gen::nrm(st.vf[20][2]), 1.0f);
          std::memcpy(&ur2, &iv, 4); }
      }
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[10] & st.vi[12]); bvOld = st.vi[10]; bvReg = 10; st.vi[10] = nv; }
      }
      st.vf[19][0] = ur0;
      st.vf[19][1] = ur1;
      st.vf[19][2] = ur2;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[19] = rt;
        cx.vfR[19][0] = rt;
        cx.vfR[19][1] = rt;
        cx.vfR[19][2] = rt;
      }
      cx.viR[10] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L0188:;
    { // pair 49 pc=0x188 up=0x000002FF lo=0x81D4437C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(uint16_t)st.vi[8] * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[20][0], vm + addr + 0u, 12);
        }
        { const int32_t nv = (int32_t)(int16_t)(st.vi[8] + 1); bvOld = st.vi[8]; bvReg = 8; st.vi[8] = nv; }
      }
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[20] = rt;
        cx.vfR[20][0] = rt;
        cx.vfR[20][1] = rt;
        cx.vfR[20][2] = rt;
      }
      c += 1u;
    }
    L0190:;
    { // pair 50 pc=0x190 up=0x000002FF lo=0x120A5001
      c = vu1gen::vmax(c, cx.viR[10]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[10] - 1); bvOld = st.vi[10]; bvReg = 10; st.vi[10] = nv; }
      }
      cx.viR[10] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L0198:;
    { // pair 51 pc=0x198 up=0x000002FF lo=0x100B5803
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[11] + 3); bvOld = st.vi[11]; bvReg = 11; st.vi[11] = nv; }
      }
      c += 1u;
    }
    L01A0:;
    { const bool bt = (int16_t)(bvReg == 10 ? bvOld : st.vi[10]) > 0;
    { // pair 52 pc=0x1A0 up=0x000002FF lo=0x5A0057FC
      c = vu1gen::vmax(c, cx.viR[10]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    { // pair 53 pc=0x1A8 up=0x01D3A17C lo=0x03CB9FFE
      c = vu1gen::vmax(c, cx.vfR[20][0]);
      c = vu1gen::vmax(c, cx.vfR[20][1]);
      c = vu1gen::vmax(c, cx.vfR[20][2]);
      c = vu1gen::vmax(c, cx.vfR[19][0]);
      c = vu1gen::vmax(c, cx.vfR[19][1]);
      c = vu1gen::vmax(c, cx.vfR[19][2]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      float ur0 = 0.0f;
      float ur1 = 0.0f;
      float ur2 = 0.0f;
      {
        { const int32_t iv = vu1gen::ftoi(vu1gen::nrm(st.vf[20][0]), 1.0f);
          std::memcpy(&ur0, &iv, 4); }
        { const int32_t iv = vu1gen::ftoi(vu1gen::nrm(st.vf[20][1]), 1.0f);
          std::memcpy(&ur1, &iv, 4); }
        { const int32_t iv = vu1gen::ftoi(vu1gen::nrm(st.vf[20][2]), 1.0f);
          std::memcpy(&ur2, &iv, 4); }
      }
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[11] + -2) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[19][0], 12);
        }
      }
      bvReg = -1;
      st.vf[19][0] = ur0;
      st.vf[19][1] = ur1;
      st.vf[19][2] = ur2;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[19] = rt;
        cx.vfR[19][0] = rt;
        cx.vfR[19][1] = rt;
        cx.vfR[19][2] = rt;
      }
      c += 1u;
    }
    if (bt) {
      st.branchTarget = 0x188u;
      if (c >= (uint64_t)a.maxCycles) { st.pc = 0x188u; goto BUDGET_OUT; }
      goto L0188;
    } }
    goto LC01B0;
    L01A8:;
    { // pair 53 pc=0x1A8 up=0x01D3A17C lo=0x03CB9FFE
      c = vu1gen::vmax(c, cx.vfR[20][0]);
      c = vu1gen::vmax(c, cx.vfR[20][1]);
      c = vu1gen::vmax(c, cx.vfR[20][2]);
      c = vu1gen::vmax(c, cx.vfR[19][0]);
      c = vu1gen::vmax(c, cx.vfR[19][1]);
      c = vu1gen::vmax(c, cx.vfR[19][2]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      float ur0 = 0.0f;
      float ur1 = 0.0f;
      float ur2 = 0.0f;
      {
        { const int32_t iv = vu1gen::ftoi(vu1gen::nrm(st.vf[20][0]), 1.0f);
          std::memcpy(&ur0, &iv, 4); }
        { const int32_t iv = vu1gen::ftoi(vu1gen::nrm(st.vf[20][1]), 1.0f);
          std::memcpy(&ur1, &iv, 4); }
        { const int32_t iv = vu1gen::ftoi(vu1gen::nrm(st.vf[20][2]), 1.0f);
          std::memcpy(&ur2, &iv, 4); }
      }
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[11] + -2) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[19][0], 12);
        }
      }
      bvReg = -1;
      st.vf[19][0] = ur0;
      st.vf[19][1] = ur1;
      st.vf[19][2] = ur2;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[19] = rt;
        cx.vfR[19][0] = rt;
        cx.vfR[19][1] = rt;
        cx.vfR[19][2] = rt;
      }
      c += 1u;
    }
    LC01B0:;
    L01B0:;
    { // pair 54 pc=0x1B0 up=0x000002FF lo=0x090A5800
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[11] + 0) * 16u) & 0x3FFFu;
          uint32_t v = 0u; std::memcpy(&v, vm + addr + 0u, 4);
          st.vi[10] = (int32_t)(int16_t)(v & 0xFFFFu);
        }
      }
      bvReg = -1;
      cx.viR[10] = (uint32_t)(c + 4u);
      c += 1u;
    }
    L01B8:;
    { const bool bt = (int16_t)0 != (int16_t)(bvReg == 9 ? bvOld : st.vi[9]);
    { // pair 55 pc=0x1B8 up=0x000002FF lo=0x52090005
      c = vu1gen::vmax(c, cx.viR[9]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    { // pair 56 pc=0x1C0 up=0x000002FF lo=0x028BA800
      c = vu1gen::vmax(c, cx.vfR[21][1]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[11] + 0) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 4u, &st.vf[21][1], 4);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    if (bt) {
      st.branchTarget = 0x1E8u;
      goto L01E8;
    } }
    goto LC01C8;
    L01C0:;
    { // pair 56 pc=0x1C0 up=0x000002FF lo=0x028BA800
      c = vu1gen::vmax(c, cx.vfR[21][1]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[11] + 0) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 4u, &st.vf[21][1], 4);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    LC01C8:;
    L01C8:;
    { // pair 57 pc=0x1C8 up=0x000002FF lo=0x100B5801
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[11] + 1); bvOld = st.vi[11]; bvReg = 11; st.vi[11] = nv; }
      }
      c += 1u;
    }
    L01D0:;
    { // pair 58 pc=0x1D0 up=0x000002FF lo=0x800D5274
      c = vu1gen::vmax(c, cx.viR[10]);
      c = vu1gen::vmax(c, cx.viR[13]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[10] & st.vi[13]); bvOld = st.vi[9]; bvReg = 9; st.vi[9] = nv; }
      }
      cx.viR[9] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L01D8:;
    st.branchTarget = 0x188u;
    { // pair 59 pc=0x1D8 up=0x000002FF lo=0x400007F5
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    { // pair 60 pc=0x1E0 up=0x000002FF lo=0x800C52B4
      c = vu1gen::vmax(c, cx.viR[10]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[10] & st.vi[12]); bvOld = st.vi[10]; bvReg = 10; st.vi[10] = nv; }
      }
      cx.viR[10] = (uint32_t)(c + 1u);
      c += 1u;
    }
    if (c >= (uint64_t)a.maxCycles) { st.pc = 0x188u; goto BUDGET_OUT; }
    goto L0188;
    L01E0:;
    { // pair 60 pc=0x1E0 up=0x000002FF lo=0x800C52B4
      c = vu1gen::vmax(c, cx.viR[10]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[10] & st.vi[12]); bvOld = st.vi[10]; bvReg = 10; st.vi[10] = nv; }
      }
      cx.viR[10] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L01E8:;
    { // pair 61 pc=0x1E8 up=0x000002FF lo=0x80003EFC
      c = vu1gen::vmax(c, cx.viR[7]);
      cx.waitKick(c);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        cx.startKick(c, (uint32_t)(uint16_t)st.vi[7]);
      }
      bvReg = -1;
      c += 1u;
    }
    L01F0:;
    { // pair 62 pc=0x1F0 up=0x400002FF lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    { // pair 63 pc=0x1F8 up=0x000002FF lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    st.pc = 0x200u; goto END_OUT;
    L01F8:;
    { // pair 63 pc=0x1F8 up=0x000002FF lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    L0200:;
    { // pair 64 pc=0x200 up=0x000002FF lo=0x800706BC
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        st.vi[7] = (int32_t)(st.top & 0x3FFu);
      }
      bvReg = -1;
      cx.viR[7] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L0208:;
    { // pair 65 pc=0x208 up=0x000002FF lo=0x08223800
      c = vu1gen::vmax(c, cx.viR[7]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[7] + 0) * 16u) & 0x3FFFu;
          uint32_t v = 0u; std::memcpy(&v, vm + addr + 12u, 4);
          st.vi[2] = (int32_t)(int16_t)(v & 0xFFFFu);
        }
      }
      bvReg = -1;
      cx.viR[2] = (uint32_t)(c + 4u);
      c += 1u;
    }
    L0210:;
    { // pair 66 pc=0x210 up=0x000002FF lo=0x10830000
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[0] + 8192); bvOld = st.vi[3]; bvReg = 3; st.vi[3] = nv; }
      }
      cx.viR[3] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L0218:;
    { const bool bt = (int16_t)0 == (int16_t)(bvReg == 1 ? bvOld : st.vi[1]);
    { // pair 67 pc=0x218 up=0x000002FF lo=0x50010005
      c = vu1gen::vmax(c, cx.viR[1]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    { // pair 68 pc=0x220 up=0x000002FF lo=0x005603CF
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
      st.branchTarget = 0x248u;
      goto L0248;
    } }
    goto LC0228;
    L0220:;
    { // pair 68 pc=0x220 up=0x000002FF lo=0x005603CF
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
    LC0228:;
    L0228:;
    { // pair 69 pc=0x228 up=0x000002FF lo=0x800310F4
      c = vu1gen::vmax(c, cx.viR[2]);
      c = vu1gen::vmax(c, cx.viR[3]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[2] & st.vi[3]); bvOld = st.vi[3]; bvReg = 3; st.vi[3] = nv; }
      }
      cx.viR[3] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L0230:;
    { // pair 70 pc=0x230 up=0x000002FF lo=0x005503D0
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 976) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[21][2], vm + addr + 8u, 4);
        }
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[21] = rt;
        cx.vfR[21][2] = rt;
      }
      c += 1u;
    }
    L0238:;
    { const bool bt = (int16_t)0 == (int16_t)(bvReg == 3 ? bvOld : st.vi[3]);
    { // pair 71 pc=0x238 up=0x000002FF lo=0x50030003
      c = vu1gen::vmax(c, cx.viR[3]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    { // pair 72 pc=0x240 up=0x000002FF lo=0x01E103A7
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
    if (bt) {
      st.branchTarget = 0x258u;
      goto L0258;
    } }
    goto LC0248;
    L0240:;
    { // pair 72 pc=0x240 up=0x000002FF lo=0x01E103A7
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
    LC0248:;
    L0248:;
    { // pair 73 pc=0x248 up=0x400002FF lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    { // pair 74 pc=0x250 up=0x000002FF lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    st.pc = 0x258u; goto END_OUT;
    L0250:;
    { // pair 74 pc=0x250 up=0x000002FF lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    L0258:;
    { // pair 75 pc=0x258 up=0x000002FF lo=0x01E203AA
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
    L0260:;
    { // pair 76 pc=0x260 up=0x000002FF lo=0x8096B33D
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
    L0268:;
    { // pair 77 pc=0x268 up=0x000002FF lo=0x8095AB3D
      c = vu1gen::vmax(c, cx.vfRAny[21]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        const float mv1 = st.vf[21][2];
        st.vf[21][1] = mv1;
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[21] = rt;
        cx.vfR[21][1] = rt;
      }
      c += 1u;
    }
    L0270:;
    { // pair 78 pc=0x270 up=0x000002FF lo=0x100838C8
      c = vu1gen::vmax(c, cx.viR[7]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[7] + 200); bvOld = st.vi[8]; bvReg = 8; st.vi[8] = nv; }
      }
      c += 1u;
    }
    L0278:;
    { // pair 79 pc=0x278 up=0x000002FF lo=0x10073902
      c = vu1gen::vmax(c, cx.viR[7]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[7] + 258); bvOld = st.vi[7]; bvReg = 7; st.vi[7] = nv; }
      }
      cx.viR[7] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L0280:;
    { // pair 80 pc=0x280 up=0x000002FF lo=0x090A3804
      c = vu1gen::vmax(c, cx.viR[7]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[7] + 4) * 16u) & 0x3FFFu;
          uint32_t v = 0u; std::memcpy(&v, vm + addr + 0u, 4);
          st.vi[10] = (int32_t)(int16_t)(v & 0xFFFFu);
        }
      }
      bvReg = -1;
      cx.viR[10] = (uint32_t)(c + 4u);
      c += 1u;
    }
    L0288:;
    { // pair 81 pc=0x288 up=0x000002FF lo=0x03E70802
      c = vu1gen::vmax(c, cx.vfRAny[1]);
      c = vu1gen::vmax(c, cx.viR[7]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[7] + 2) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[1][0], 16);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L0290:;
    { // pair 82 pc=0x290 up=0x000002FF lo=0x03E71003
      c = vu1gen::vmax(c, cx.vfRAny[2]);
      c = vu1gen::vmax(c, cx.viR[7]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[7] + 3) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[2][0], 16);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L0298:;
    { // pair 83 pc=0x298 up=0x000002FF lo=0x0287B004
      c = vu1gen::vmax(c, cx.vfR[22][1]);
      c = vu1gen::vmax(c, cx.viR[7]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[7] + 4) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 4u, &st.vf[22][1], 4);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L02A0:;
    { // pair 84 pc=0x2A0 up=0x000002FF lo=0x81D4437C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(uint16_t)st.vi[8] * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[20][0], vm + addr + 0u, 12);
        }
        { const int32_t nv = (int32_t)(int16_t)(st.vi[8] + 1); bvOld = st.vi[8]; bvReg = 8; st.vi[8] = nv; }
      }
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[20] = rt;
        cx.vfR[20][0] = rt;
        cx.vfR[20][1] = rt;
        cx.vfR[20][2] = rt;
      }
      c += 1u;
    }
    L02A8:;
    { // pair 85 pc=0x2A8 up=0x000002FF lo=0x100B3805
      c = vu1gen::vmax(c, cx.viR[7]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[7] + 5); bvOld = st.vi[11]; bvReg = 11; st.vi[11] = nv; }
      }
      c += 1u;
    }
    L02B0:;
    { // pair 86 pc=0x2B0 up=0x000002FF lo=0x11EC07FF
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[0] + 32767); bvOld = st.vi[12]; bvReg = 12; st.vi[12] = nv; }
      }
      c += 1u;
    }
    L02B8:;
    { // pair 87 pc=0x2B8 up=0x000002FF lo=0x800D5274
      c = vu1gen::vmax(c, cx.viR[10]);
      c = vu1gen::vmax(c, cx.viR[13]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[10] & st.vi[13]); bvOld = st.vi[9]; bvReg = 9; st.vi[9] = nv; }
      }
      cx.viR[9] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L02C0:;
    { // pair 88 pc=0x2C0 up=0x01D3A17C lo=0x800C52B4
      c = vu1gen::vmax(c, cx.vfR[20][0]);
      c = vu1gen::vmax(c, cx.vfR[20][1]);
      c = vu1gen::vmax(c, cx.vfR[20][2]);
      c = vu1gen::vmax(c, cx.viR[10]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      float ur0 = 0.0f;
      float ur1 = 0.0f;
      float ur2 = 0.0f;
      {
        { const int32_t iv = vu1gen::ftoi(vu1gen::nrm(st.vf[20][0]), 1.0f);
          std::memcpy(&ur0, &iv, 4); }
        { const int32_t iv = vu1gen::ftoi(vu1gen::nrm(st.vf[20][1]), 1.0f);
          std::memcpy(&ur1, &iv, 4); }
        { const int32_t iv = vu1gen::ftoi(vu1gen::nrm(st.vf[20][2]), 1.0f);
          std::memcpy(&ur2, &iv, 4); }
      }
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[10] & st.vi[12]); bvOld = st.vi[10]; bvReg = 10; st.vi[10] = nv; }
      }
      st.vf[19][0] = ur0;
      st.vf[19][1] = ur1;
      st.vf[19][2] = ur2;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[19] = rt;
        cx.vfR[19][0] = rt;
        cx.vfR[19][1] = rt;
        cx.vfR[19][2] = rt;
      }
      cx.viR[10] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L02C8:;
    { // pair 89 pc=0x2C8 up=0x000002FF lo=0x81D4437C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(uint16_t)st.vi[8] * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[20][0], vm + addr + 0u, 12);
        }
        { const int32_t nv = (int32_t)(int16_t)(st.vi[8] + 1); bvOld = st.vi[8]; bvReg = 8; st.vi[8] = nv; }
      }
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[20] = rt;
        cx.vfR[20][0] = rt;
        cx.vfR[20][1] = rt;
        cx.vfR[20][2] = rt;
      }
      c += 1u;
    }
    L02D0:;
    { // pair 90 pc=0x2D0 up=0x000002FF lo=0x120A5001
      c = vu1gen::vmax(c, cx.viR[10]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[10] - 1); bvOld = st.vi[10]; bvReg = 10; st.vi[10] = nv; }
      }
      cx.viR[10] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L02D8:;
    { // pair 91 pc=0x2D8 up=0x000002FF lo=0x100B5803
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[11] + 3); bvOld = st.vi[11]; bvReg = 11; st.vi[11] = nv; }
      }
      c += 1u;
    }
    L02E0:;
    { const bool bt = (int16_t)(bvReg == 10 ? bvOld : st.vi[10]) > 0;
    { // pair 92 pc=0x2E0 up=0x000002FF lo=0x5A0057FC
      c = vu1gen::vmax(c, cx.viR[10]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    { // pair 93 pc=0x2E8 up=0x01D3A17C lo=0x03CB9FFE
      c = vu1gen::vmax(c, cx.vfR[20][0]);
      c = vu1gen::vmax(c, cx.vfR[20][1]);
      c = vu1gen::vmax(c, cx.vfR[20][2]);
      c = vu1gen::vmax(c, cx.vfR[19][0]);
      c = vu1gen::vmax(c, cx.vfR[19][1]);
      c = vu1gen::vmax(c, cx.vfR[19][2]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      float ur0 = 0.0f;
      float ur1 = 0.0f;
      float ur2 = 0.0f;
      {
        { const int32_t iv = vu1gen::ftoi(vu1gen::nrm(st.vf[20][0]), 1.0f);
          std::memcpy(&ur0, &iv, 4); }
        { const int32_t iv = vu1gen::ftoi(vu1gen::nrm(st.vf[20][1]), 1.0f);
          std::memcpy(&ur1, &iv, 4); }
        { const int32_t iv = vu1gen::ftoi(vu1gen::nrm(st.vf[20][2]), 1.0f);
          std::memcpy(&ur2, &iv, 4); }
      }
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[11] + -2) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[19][0], 12);
        }
      }
      bvReg = -1;
      st.vf[19][0] = ur0;
      st.vf[19][1] = ur1;
      st.vf[19][2] = ur2;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[19] = rt;
        cx.vfR[19][0] = rt;
        cx.vfR[19][1] = rt;
        cx.vfR[19][2] = rt;
      }
      c += 1u;
    }
    if (bt) {
      st.branchTarget = 0x2C8u;
      if (c >= (uint64_t)a.maxCycles) { st.pc = 0x2C8u; goto BUDGET_OUT; }
      goto L02C8;
    } }
    goto LC02F0;
    L02E8:;
    { // pair 93 pc=0x2E8 up=0x01D3A17C lo=0x03CB9FFE
      c = vu1gen::vmax(c, cx.vfR[20][0]);
      c = vu1gen::vmax(c, cx.vfR[20][1]);
      c = vu1gen::vmax(c, cx.vfR[20][2]);
      c = vu1gen::vmax(c, cx.vfR[19][0]);
      c = vu1gen::vmax(c, cx.vfR[19][1]);
      c = vu1gen::vmax(c, cx.vfR[19][2]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      float ur0 = 0.0f;
      float ur1 = 0.0f;
      float ur2 = 0.0f;
      {
        { const int32_t iv = vu1gen::ftoi(vu1gen::nrm(st.vf[20][0]), 1.0f);
          std::memcpy(&ur0, &iv, 4); }
        { const int32_t iv = vu1gen::ftoi(vu1gen::nrm(st.vf[20][1]), 1.0f);
          std::memcpy(&ur1, &iv, 4); }
        { const int32_t iv = vu1gen::ftoi(vu1gen::nrm(st.vf[20][2]), 1.0f);
          std::memcpy(&ur2, &iv, 4); }
      }
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[11] + -2) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[19][0], 12);
        }
      }
      bvReg = -1;
      st.vf[19][0] = ur0;
      st.vf[19][1] = ur1;
      st.vf[19][2] = ur2;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[19] = rt;
        cx.vfR[19][0] = rt;
        cx.vfR[19][1] = rt;
        cx.vfR[19][2] = rt;
      }
      c += 1u;
    }
    LC02F0:;
    L02F0:;
    { // pair 94 pc=0x2F0 up=0x000002FF lo=0x090A5800
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[11] + 0) * 16u) & 0x3FFFu;
          uint32_t v = 0u; std::memcpy(&v, vm + addr + 0u, 4);
          st.vi[10] = (int32_t)(int16_t)(v & 0xFFFFu);
        }
      }
      bvReg = -1;
      cx.viR[10] = (uint32_t)(c + 4u);
      c += 1u;
    }
    L02F8:;
    { const bool bt = (int16_t)0 != (int16_t)(bvReg == 9 ? bvOld : st.vi[9]);
    { // pair 95 pc=0x2F8 up=0x000002FF lo=0x52090005
      c = vu1gen::vmax(c, cx.viR[9]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    { // pair 96 pc=0x300 up=0x000002FF lo=0x028BA800
      c = vu1gen::vmax(c, cx.vfR[21][1]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[11] + 0) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 4u, &st.vf[21][1], 4);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    if (bt) {
      st.branchTarget = 0x328u;
      goto L0328;
    } }
    goto LC0308;
    L0300:;
    { // pair 96 pc=0x300 up=0x000002FF lo=0x028BA800
      c = vu1gen::vmax(c, cx.vfR[21][1]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[11] + 0) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 4u, &st.vf[21][1], 4);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    LC0308:;
    L0308:;
    { // pair 97 pc=0x308 up=0x000002FF lo=0x100B5801
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[11] + 1); bvOld = st.vi[11]; bvReg = 11; st.vi[11] = nv; }
      }
      c += 1u;
    }
    L0310:;
    { // pair 98 pc=0x310 up=0x000002FF lo=0x800D5274
      c = vu1gen::vmax(c, cx.viR[10]);
      c = vu1gen::vmax(c, cx.viR[13]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[10] & st.vi[13]); bvOld = st.vi[9]; bvReg = 9; st.vi[9] = nv; }
      }
      cx.viR[9] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L0318:;
    st.branchTarget = 0x2C8u;
    { // pair 99 pc=0x318 up=0x000002FF lo=0x400007F5
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    { // pair 100 pc=0x320 up=0x000002FF lo=0x800C52B4
      c = vu1gen::vmax(c, cx.viR[10]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[10] & st.vi[12]); bvOld = st.vi[10]; bvReg = 10; st.vi[10] = nv; }
      }
      cx.viR[10] = (uint32_t)(c + 1u);
      c += 1u;
    }
    if (c >= (uint64_t)a.maxCycles) { st.pc = 0x2C8u; goto BUDGET_OUT; }
    goto L02C8;
    L0320:;
    { // pair 100 pc=0x320 up=0x000002FF lo=0x800C52B4
      c = vu1gen::vmax(c, cx.viR[10]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[10] & st.vi[12]); bvOld = st.vi[10]; bvReg = 10; st.vi[10] = nv; }
      }
      cx.viR[10] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L0328:;
    { // pair 101 pc=0x328 up=0x000002FF lo=0x80003EFC
      c = vu1gen::vmax(c, cx.viR[7]);
      cx.waitKick(c);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        cx.startKick(c, (uint32_t)(uint16_t)st.vi[7]);
      }
      bvReg = -1;
      c += 1u;
    }
    L0330:;
    { // pair 102 pc=0x330 up=0x400002FF lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    { // pair 103 pc=0x338 up=0x000002FF lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    st.pc = 0x340u; goto END_OUT;
    L0338:;
    { // pair 103 pc=0x338 up=0x000002FF lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    L0340:;
    { // pair 104 pc=0x340 up=0x000002FF lo=0x800706BC
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        st.vi[7] = (int32_t)(st.top & 0x3FFu);
      }
      bvReg = -1;
      cx.viR[7] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L0348:;
    { // pair 105 pc=0x348 up=0x000002FF lo=0x08223800
      c = vu1gen::vmax(c, cx.viR[7]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[7] + 0) * 16u) & 0x3FFFu;
          uint32_t v = 0u; std::memcpy(&v, vm + addr + 12u, 4);
          st.vi[2] = (int32_t)(int16_t)(v & 0xFFFFu);
        }
      }
      bvReg = -1;
      cx.viR[2] = (uint32_t)(c + 4u);
      c += 1u;
    }
    L0350:;
    { // pair 106 pc=0x350 up=0x000002FF lo=0x10830000
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[0] + 8192); bvOld = st.vi[3]; bvReg = 3; st.vi[3] = nv; }
      }
      cx.viR[3] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L0358:;
    { const bool bt = (int16_t)0 == (int16_t)(bvReg == 1 ? bvOld : st.vi[1]);
    { // pair 107 pc=0x358 up=0x000002FF lo=0x50010005
      c = vu1gen::vmax(c, cx.viR[1]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    { // pair 108 pc=0x360 up=0x000002FF lo=0x009603CF
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
      st.branchTarget = 0x388u;
      goto L0388;
    } }
    goto LC0368;
    L0360:;
    { // pair 108 pc=0x360 up=0x000002FF lo=0x009603CF
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
    LC0368:;
    L0368:;
    { // pair 109 pc=0x368 up=0x000002FF lo=0x800310F4
      c = vu1gen::vmax(c, cx.viR[2]);
      c = vu1gen::vmax(c, cx.viR[3]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[2] & st.vi[3]); bvOld = st.vi[3]; bvReg = 3; st.vi[3] = nv; }
      }
      cx.viR[3] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L0370:;
    { // pair 110 pc=0x370 up=0x000002FF lo=0x009503D0
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 976) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[21][1], vm + addr + 4u, 4);
        }
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[21] = rt;
        cx.vfR[21][1] = rt;
      }
      c += 1u;
    }
    L0378:;
    { const bool bt = (int16_t)0 == (int16_t)(bvReg == 3 ? bvOld : st.vi[3]);
    { // pair 111 pc=0x378 up=0x000002FF lo=0x50030003
      c = vu1gen::vmax(c, cx.viR[3]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    { // pair 112 pc=0x380 up=0x000002FF lo=0x01F403AB
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 939) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[20][0], vm + addr + 0u, 16);
        }
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[20] = rt;
        _mm_store_si128((__m128i *)cx.vfR[20], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    if (bt) {
      st.branchTarget = 0x398u;
      goto L0398;
    } }
    goto LC0388;
    L0380:;
    { // pair 112 pc=0x380 up=0x000002FF lo=0x01F403AB
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 939) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[20][0], vm + addr + 0u, 16);
        }
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[20] = rt;
        _mm_store_si128((__m128i *)cx.vfR[20], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    LC0388:;
    L0388:;
    { // pair 113 pc=0x388 up=0x400002FF lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    { // pair 114 pc=0x390 up=0x000002FF lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    st.pc = 0x398u; goto END_OUT;
    L0390:;
    { // pair 114 pc=0x390 up=0x000002FF lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    L0398:;
    { // pair 115 pc=0x398 up=0x000002FF lo=0x01E103A8
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
    L03A0:;
    { // pair 116 pc=0x3A0 up=0x000002FF lo=0x01E203AA
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
    L03A8:;
    { // pair 117 pc=0x3A8 up=0x000002FF lo=0x01E30397
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
    L03B0:;
    { // pair 118 pc=0x3B0 up=0x000002FF lo=0x1008388E
      c = vu1gen::vmax(c, cx.viR[7]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[7] + 142); bvOld = st.vi[8]; bvReg = 8; st.vi[8] = nv; }
      }
      c += 1u;
    }
    L03B8:;
    { // pair 119 pc=0x3B8 up=0x000002FF lo=0x10073902
      c = vu1gen::vmax(c, cx.viR[7]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[7] + 258); bvOld = st.vi[7]; bvReg = 7; st.vi[7] = nv; }
      }
      cx.viR[7] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L03C0:;
    { // pair 120 pc=0x3C0 up=0x000002FF lo=0x100B3805
      c = vu1gen::vmax(c, cx.viR[7]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[7] + 5); bvOld = st.vi[11]; bvReg = 11; st.vi[11] = nv; }
      }
      c += 1u;
    }
    L03C8:;
    { // pair 121 pc=0x3C8 up=0x000002FF lo=0x090A3804
      c = vu1gen::vmax(c, cx.viR[7]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[7] + 4) * 16u) & 0x3FFFu;
          uint32_t v = 0u; std::memcpy(&v, vm + addr + 0u, 4);
          st.vi[10] = (int32_t)(int16_t)(v & 0xFFFFu);
        }
      }
      bvReg = -1;
      cx.viR[10] = (uint32_t)(c + 4u);
      c += 1u;
    }
    L03D0:;
    { // pair 122 pc=0x3D0 up=0x000002FF lo=0x03E70802
      c = vu1gen::vmax(c, cx.vfRAny[1]);
      c = vu1gen::vmax(c, cx.viR[7]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[7] + 2) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[1][0], 16);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L03D8:;
    { // pair 123 pc=0x3D8 up=0x000002FF lo=0x03E71003
      c = vu1gen::vmax(c, cx.vfRAny[2]);
      c = vu1gen::vmax(c, cx.viR[7]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[7] + 3) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[2][0], 16);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L03E0:;
    { // pair 124 pc=0x3E0 up=0x000002FF lo=0x03E71801
      c = vu1gen::vmax(c, cx.vfRAny[3]);
      c = vu1gen::vmax(c, cx.viR[7]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[7] + 1) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[3][0], 16);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L03E8:;
    { // pair 125 pc=0x3E8 up=0x000002FF lo=0x0287B004
      c = vu1gen::vmax(c, cx.vfR[22][1]);
      c = vu1gen::vmax(c, cx.viR[7]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[7] + 4) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 4u, &st.vf[22][1], 4);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L03F0:;
    { // pair 126 pc=0x3F0 up=0x000002FF lo=0x00535800
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[11] + 0) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[19][2], vm + addr + 8u, 4);
        }
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[19] = rt;
        cx.vfR[19][2] = rt;
      }
      c += 1u;
    }
    L03F8:;
    { // pair 127 pc=0x3F8 up=0x000002FF lo=0x8193437C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(uint16_t)st.vi[8] * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[19][0], vm + addr + 0u, 8);
        }
        { const int32_t nv = (int32_t)(int16_t)(st.vi[8] + 1); bvOld = st.vi[8]; bvReg = 8; st.vi[8] = nv; }
      }
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[19] = rt;
        cx.vfR[19][0] = rt;
        cx.vfR[19][1] = rt;
      }
      c += 1u;
    }
    L0400:;
    { // pair 128 pc=0x400 up=0x000002FF lo=0x100B5803
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[11] + 3); bvOld = st.vi[11]; bvReg = 11; st.vi[11] = nv; }
      }
      c += 1u;
    }
    L0408:;
    { // pair 129 pc=0x408 up=0x000002FF lo=0x11EC07FF
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[0] + 32767); bvOld = st.vi[12]; bvReg = 12; st.vi[12] = nv; }
      }
      c += 1u;
    }
    L0410:;
    { // pair 130 pc=0x410 up=0x000002FF lo=0x800D5274
      c = vu1gen::vmax(c, cx.viR[10]);
      c = vu1gen::vmax(c, cx.viR[13]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[10] & st.vi[13]); bvOld = st.vi[9]; bvReg = 9; st.vi[9] = nv; }
      }
      cx.viR[9] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L0418:;
    { // pair 131 pc=0x418 up=0x01939C9A lo=0x800C52B4
      c = vu1gen::vmax(c, cx.vfR[19][0]);
      c = vu1gen::vmax(c, cx.vfR[19][1]);
      c = vu1gen::vmax(c, cx.vfR[19][2]);
      c = vu1gen::vmax(c, cx.viR[10]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[19]);
        const __m128 bv = vu1gen::nrmbc(st.vf[19], 2);
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
      vu1gen::storeLanes(st.vf[18], urv, 0xCu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[18] = rt;
        cx.vfR[18][0] = rt;
        cx.vfR[18][1] = rt;
      }
      cx.viR[10] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L0420:;
    { // pair 132 pc=0x420 up=0x000002FF lo=0x00535800
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[11] + 0) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[19][2], vm + addr + 8u, 4);
        }
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[19] = rt;
        cx.vfR[19][2] = rt;
      }
      c += 1u;
    }
    L0428:;
    { // pair 133 pc=0x428 up=0x000002FF lo=0x8193437C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(uint16_t)st.vi[8] * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[19][0], vm + addr + 0u, 8);
        }
        { const int32_t nv = (int32_t)(int16_t)(st.vi[8] + 1); bvOld = st.vi[8]; bvReg = 8; st.vi[8] = nv; }
      }
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[19] = rt;
        cx.vfR[19][0] = rt;
        cx.vfR[19][1] = rt;
      }
      c += 1u;
    }
    L0430:;
    { // pair 134 pc=0x430 up=0x000002FF lo=0x100B5803
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[11] + 3); bvOld = st.vi[11]; bvReg = 11; st.vi[11] = nv; }
      }
      c += 1u;
    }
    L0438:;
    { // pair 135 pc=0x438 up=0x000002FF lo=0x120A5001
      c = vu1gen::vmax(c, cx.viR[10]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[10] - 1); bvOld = st.vi[10]; bvReg = 10; st.vi[10] = nv; }
      }
      cx.viR[10] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L0440:;
    { // pair 136 pc=0x440 up=0x000002FF lo=0x03EBA7FB
      c = vu1gen::vmax(c, cx.vfRAny[20]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[11] + -5) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[20][0], 16);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L0448:;
    { const bool bt = (int16_t)(bvReg == 10 ? bvOld : st.vi[10]) > 0;
    { // pair 137 pc=0x448 up=0x000002FF lo=0x5A0057FA
      c = vu1gen::vmax(c, cx.viR[10]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    { // pair 138 pc=0x450 up=0x01939C9A lo=0x038B97FA
      c = vu1gen::vmax(c, cx.vfR[19][0]);
      c = vu1gen::vmax(c, cx.vfR[19][1]);
      c = vu1gen::vmax(c, cx.vfR[19][2]);
      c = vu1gen::vmax(c, cx.vfR[18][0]);
      c = vu1gen::vmax(c, cx.vfR[18][1]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[19]);
        const __m128 bv = vu1gen::nrmbc(st.vf[19], 2);
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
          std::memcpy(vm + addr + 0u, &st.vf[18][0], 8);
        }
      }
      bvReg = -1;
      vu1gen::storeLanes(st.vf[18], urv, 0xCu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[18] = rt;
        cx.vfR[18][0] = rt;
        cx.vfR[18][1] = rt;
      }
      c += 1u;
    }
    if (bt) {
      st.branchTarget = 0x420u;
      if (c >= (uint64_t)a.maxCycles) { st.pc = 0x420u; goto BUDGET_OUT; }
      goto L0420;
    } }
    goto LC0458;
    L0450:;
    { // pair 138 pc=0x450 up=0x01939C9A lo=0x038B97FA
      c = vu1gen::vmax(c, cx.vfR[19][0]);
      c = vu1gen::vmax(c, cx.vfR[19][1]);
      c = vu1gen::vmax(c, cx.vfR[19][2]);
      c = vu1gen::vmax(c, cx.vfR[18][0]);
      c = vu1gen::vmax(c, cx.vfR[18][1]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[19]);
        const __m128 bv = vu1gen::nrmbc(st.vf[19], 2);
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
          std::memcpy(vm + addr + 0u, &st.vf[18][0], 8);
        }
      }
      bvReg = -1;
      vu1gen::storeLanes(st.vf[18], urv, 0xCu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[18] = rt;
        cx.vfR[18][0] = rt;
        cx.vfR[18][1] = rt;
      }
      c += 1u;
    }
    LC0458:;
    L0458:;
    { const bool bt = (int16_t)0 != (int16_t)(bvReg == 9 ? bvOld : st.vi[9]);
    { // pair 139 pc=0x458 up=0x000002FF lo=0x52090008
      c = vu1gen::vmax(c, cx.viR[9]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    { // pair 140 pc=0x460 up=0x000002FF lo=0x090A5FFD
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[11] + -3) * 16u) & 0x3FFFu;
          uint32_t v = 0u; std::memcpy(&v, vm + addr + 0u, 4);
          st.vi[10] = (int32_t)(int16_t)(v & 0xFFFFu);
        }
      }
      bvReg = -1;
      cx.viR[10] = (uint32_t)(c + 4u);
      c += 1u;
    }
    if (bt) {
      st.branchTarget = 0x4A0u;
      goto L04A0;
    } }
    goto LC0468;
    L0460:;
    { // pair 140 pc=0x460 up=0x000002FF lo=0x090A5FFD
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[11] + -3) * 16u) & 0x3FFFu;
          uint32_t v = 0u; std::memcpy(&v, vm + addr + 0u, 4);
          st.vi[10] = (int32_t)(int16_t)(v & 0xFFFFu);
        }
      }
      bvReg = -1;
      cx.viR[10] = (uint32_t)(c + 4u);
      c += 1u;
    }
    LC0468:;
    L0468:;
    { // pair 141 pc=0x468 up=0x000002FF lo=0x00535FFE
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[11] + -2) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[19][2], vm + addr + 8u, 4);
        }
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[19] = rt;
        cx.vfR[19][2] = rt;
      }
      c += 1u;
    }
    L0470:;
    { // pair 142 pc=0x470 up=0x000002FF lo=0x019347FF
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[8] + -1) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[19][0], vm + addr + 0u, 8);
        }
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[19] = rt;
        cx.vfR[19][0] = rt;
        cx.vfR[19][1] = rt;
      }
      c += 1u;
    }
    L0478:;
    { // pair 143 pc=0x478 up=0x000002FF lo=0x028BAFFD
      c = vu1gen::vmax(c, cx.vfR[21][1]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[11] + -3) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 4u, &st.vf[21][1], 4);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L0480:;
    { // pair 144 pc=0x480 up=0x000002FF lo=0x800D5274
      c = vu1gen::vmax(c, cx.viR[10]);
      c = vu1gen::vmax(c, cx.viR[13]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[10] & st.vi[13]); bvOld = st.vi[9]; bvReg = 9; st.vi[9] = nv; }
      }
      cx.viR[9] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L0488:;
    { // pair 145 pc=0x488 up=0x000002FF lo=0x800C52B4
      c = vu1gen::vmax(c, cx.viR[10]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[10] & st.vi[12]); bvOld = st.vi[10]; bvReg = 10; st.vi[10] = nv; }
      }
      cx.viR[10] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L0490:;
    st.branchTarget = 0x420u;
    { // pair 146 pc=0x490 up=0x01939C9A lo=0x400007F1
      c = vu1gen::vmax(c, cx.vfR[19][0]);
      c = vu1gen::vmax(c, cx.vfR[19][1]);
      c = vu1gen::vmax(c, cx.vfR[19][2]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[19]);
        const __m128 bv = vu1gen::nrmbc(st.vf[19], 2);
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
      vu1gen::storeLanes(st.vf[18], urv, 0xCu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[18] = rt;
        cx.vfR[18][0] = rt;
        cx.vfR[18][1] = rt;
      }
      c += 1u;
    }
    { // pair 147 pc=0x498 up=0x000002FF lo=0x100B5801
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[11] + 1); bvOld = st.vi[11]; bvReg = 11; st.vi[11] = nv; }
      }
      c += 1u;
    }
    if (c >= (uint64_t)a.maxCycles) { st.pc = 0x420u; goto BUDGET_OUT; }
    goto L0420;
    L0498:;
    { // pair 147 pc=0x498 up=0x000002FF lo=0x100B5801
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[11] + 1); bvOld = st.vi[11]; bvReg = 11; st.vi[11] = nv; }
      }
      c += 1u;
    }
    L04A0:;
    { // pair 148 pc=0x4A0 up=0x000002FF lo=0x80003EFC
      c = vu1gen::vmax(c, cx.viR[7]);
      cx.waitKick(c);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        cx.startKick(c, (uint32_t)(uint16_t)st.vi[7]);
      }
      bvReg = -1;
      c += 1u;
    }
    L04A8:;
    { // pair 149 pc=0x4A8 up=0x400002FF lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    { // pair 150 pc=0x4B0 up=0x000002FF lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    st.pc = 0x4B8u; goto END_OUT;
    L04B0:;
    { // pair 150 pc=0x4B0 up=0x000002FF lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    L04B8:;
    { // pair 151 pc=0x4B8 up=0x000002FF lo=0x800706BC
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        st.vi[7] = (int32_t)(st.top & 0x3FFu);
      }
      bvReg = -1;
      cx.viR[7] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L04C0:;
    { // pair 152 pc=0x4C0 up=0x000002FF lo=0x08223800
      c = vu1gen::vmax(c, cx.viR[7]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[7] + 0) * 16u) & 0x3FFFu;
          uint32_t v = 0u; std::memcpy(&v, vm + addr + 12u, 4);
          st.vi[2] = (int32_t)(int16_t)(v & 0xFFFFu);
        }
      }
      bvReg = -1;
      cx.viR[2] = (uint32_t)(c + 4u);
      c += 1u;
    }
    L04C8:;
    { // pair 153 pc=0x4C8 up=0x000002FF lo=0x10830000
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[0] + 8192); bvOld = st.vi[3]; bvReg = 3; st.vi[3] = nv; }
      }
      cx.viR[3] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L04D0:;
    { const bool bt = (int16_t)0 == (int16_t)(bvReg == 1 ? bvOld : st.vi[1]);
    { // pair 154 pc=0x4D0 up=0x000002FF lo=0x50010005
      c = vu1gen::vmax(c, cx.viR[1]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    { // pair 155 pc=0x4D8 up=0x000002FF lo=0x08860398
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 920) * 16u) & 0x3FFFu;
          uint32_t v = 0u; std::memcpy(&v, vm + addr + 4u, 4);
          st.vi[6] = (int32_t)(int16_t)(v & 0xFFFFu);
        }
      }
      bvReg = -1;
      cx.viR[6] = (uint32_t)(c + 4u);
      c += 1u;
    }
    if (bt) {
      st.branchTarget = 0x500u;
      goto L0500;
    } }
    goto LC04E0;
    L04D8:;
    { // pair 155 pc=0x4D8 up=0x000002FF lo=0x08860398
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 920) * 16u) & 0x3FFFu;
          uint32_t v = 0u; std::memcpy(&v, vm + addr + 4u, 4);
          st.vi[6] = (int32_t)(int16_t)(v & 0xFFFFu);
        }
      }
      bvReg = -1;
      cx.viR[6] = (uint32_t)(c + 4u);
      c += 1u;
    }
    LC04E0:;
    L04E0:;
    { // pair 156 pc=0x4E0 up=0x000002FF lo=0x800310F4
      c = vu1gen::vmax(c, cx.viR[2]);
      c = vu1gen::vmax(c, cx.viR[3]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[2] & st.vi[3]); bvOld = st.vi[3]; bvReg = 3; st.vi[3] = nv; }
      }
      cx.viR[3] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L04E8:;
    { // pair 157 pc=0x4E8 up=0x000002FF lo=0x011603CF
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 975) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[22][0], vm + addr + 0u, 4);
        }
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[22] = rt;
        cx.vfR[22][0] = rt;
      }
      c += 1u;
    }
    L04F0:;
    { const bool bt = (int16_t)0 == (int16_t)(bvReg == 3 ? bvOld : st.vi[3]);
    { // pair 158 pc=0x4F0 up=0x000002FF lo=0x50030003
      c = vu1gen::vmax(c, cx.viR[3]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    { // pair 159 pc=0x4F8 up=0x000002FF lo=0x011503D0
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 976) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[21][0], vm + addr + 0u, 4);
        }
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[21] = rt;
        cx.vfR[21][0] = rt;
      }
      c += 1u;
    }
    if (bt) {
      st.branchTarget = 0x510u;
      goto L0510;
    } }
    goto LC0500;
    L04F8:;
    { // pair 159 pc=0x4F8 up=0x000002FF lo=0x011503D0
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 976) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[21][0], vm + addr + 0u, 4);
        }
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[21] = rt;
        cx.vfR[21][0] = rt;
      }
      c += 1u;
    }
    LC0500:;
    L0500:;
    { // pair 160 pc=0x500 up=0x400002FF lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    { // pair 161 pc=0x508 up=0x000002FF lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    st.pc = 0x510u; goto END_OUT;
    L0508:;
    { // pair 161 pc=0x508 up=0x000002FF lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    L0510:;
    { // pair 162 pc=0x510 up=0x000002FF lo=0x01E103A5
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 933) * 16u) & 0x3FFFu;
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
    L0518:;
    { // pair 163 pc=0x518 up=0x00960580 lo=0x01E203AA
      c = vu1gen::vmax(c, cx.vfR[22][0]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = _mm_setr_ps(0.0f, 0.0f, 0.0f, 1.0f);
        const __m128 bv = vu1gen::nrmbc(st.vf[22], 0);
        const __m128 rv = _mm_add_ps(vsv, bv);
        uint32_t mac = 0u, stf = 0u, stk = 0u;
        __m128 rvn = rv;
        { uint32_t sgn; uint32_t plain = vu1gen::classify4(rv, sgn);
          if ((plain & 0x2u) == 0x2u) {
            mac = vu1gen::kMacSign.word[sgn & 0x2u];
            stf = (sgn & 0x2u) != 0u ? 0x2u : 0u;
          } else {
            float rr[4]; _mm_storeu_ps(rr, rv);
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
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 938) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[2][0], vm + addr + 0u, 16);
        }
      }
      bvReg = -1;
      vu1gen::storeLanes(st.vf[22], urv, 0x4u);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[22] = rt;
        cx.vfR[22][1] = rt;
      }
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[2] = rt;
        _mm_store_si128((__m128i *)cx.vfR[2], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L0520:;
    { // pair 164 pc=0x520 up=0x000002FF lo=0x01E33399
      c = vu1gen::vmax(c, cx.viR[6]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[6] + 921) * 16u) & 0x3FFFu;
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
    L0528:;
    { // pair 165 pc=0x528 up=0x00950540 lo=0x100838C8
      c = vu1gen::vmax(c, cx.vfR[21][0]);
      c = vu1gen::vmax(c, cx.viR[7]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = _mm_setr_ps(0.0f, 0.0f, 0.0f, 1.0f);
        const __m128 bv = vu1gen::nrmbc(st.vf[21], 0);
        const __m128 rv = _mm_add_ps(vsv, bv);
        uint32_t mac = 0u, stf = 0u, stk = 0u;
        __m128 rvn = rv;
        { uint32_t sgn; uint32_t plain = vu1gen::classify4(rv, sgn);
          if ((plain & 0x2u) == 0x2u) {
            mac = vu1gen::kMacSign.word[sgn & 0x2u];
            stf = (sgn & 0x2u) != 0u ? 0x2u : 0u;
          } else {
            float rr[4]; _mm_storeu_ps(rr, rv);
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
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[7] + 200); bvOld = st.vi[8]; bvReg = 8; st.vi[8] = nv; }
      }
      vu1gen::storeLanes(st.vf[21], urv, 0x4u);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[21] = rt;
        cx.vfR[21][1] = rt;
      }
      c += 1u;
    }
    L0530:;
    { // pair 166 pc=0x530 up=0x000002FF lo=0x10073902
      c = vu1gen::vmax(c, cx.viR[7]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[7] + 258); bvOld = st.vi[7]; bvReg = 7; st.vi[7] = nv; }
      }
      cx.viR[7] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L0538:;
    { // pair 167 pc=0x538 up=0x000002FF lo=0x100B3805
      c = vu1gen::vmax(c, cx.viR[7]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[7] + 5); bvOld = st.vi[11]; bvReg = 11; st.vi[11] = nv; }
      }
      c += 1u;
    }
    L0540:;
    { // pair 168 pc=0x540 up=0x000002FF lo=0x090A3804
      c = vu1gen::vmax(c, cx.viR[7]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[7] + 4) * 16u) & 0x3FFFu;
          uint32_t v = 0u; std::memcpy(&v, vm + addr + 0u, 4);
          st.vi[10] = (int32_t)(int16_t)(v & 0xFFFFu);
        }
      }
      bvReg = -1;
      cx.viR[10] = (uint32_t)(c + 4u);
      c += 1u;
    }
    L0548:;
    { // pair 169 pc=0x548 up=0x000002FF lo=0x03E70802
      c = vu1gen::vmax(c, cx.vfRAny[1]);
      c = vu1gen::vmax(c, cx.viR[7]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[7] + 2) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[1][0], 16);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L0550:;
    { // pair 170 pc=0x550 up=0x000002FF lo=0x03E71003
      c = vu1gen::vmax(c, cx.vfRAny[2]);
      c = vu1gen::vmax(c, cx.viR[7]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[7] + 3) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[2][0], 16);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L0558:;
    { // pair 171 pc=0x558 up=0x000002FF lo=0x03E71801
      c = vu1gen::vmax(c, cx.vfRAny[3]);
      c = vu1gen::vmax(c, cx.viR[7]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[7] + 1) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[3][0], 16);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L0560:;
    { // pair 172 pc=0x560 up=0x000002FF lo=0x00535800
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[11] + 0) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[19][2], vm + addr + 8u, 4);
        }
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[19] = rt;
        cx.vfR[19][2] = rt;
      }
      c += 1u;
    }
    L0568:;
    { // pair 173 pc=0x568 up=0x000002FF lo=0x019347C6
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[8] + -58) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[19][0], vm + addr + 0u, 8);
        }
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[19] = rt;
        cx.vfR[19][0] = rt;
        cx.vfR[19][1] = rt;
      }
      c += 1u;
    }
    L0570:;
    { // pair 174 pc=0x570 up=0x000002FF lo=0x81F4437C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(uint16_t)st.vi[8] * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[20][0], vm + addr + 0u, 16);
        }
        { const int32_t nv = (int32_t)(int16_t)(st.vi[8] + 1); bvOld = st.vi[8]; bvReg = 8; st.vi[8] = nv; }
      }
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[20] = rt;
        _mm_store_si128((__m128i *)cx.vfR[20], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L0578:;
    { // pair 175 pc=0x578 up=0x000002FF lo=0x100B5803
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[11] + 3); bvOld = st.vi[11]; bvReg = 11; st.vi[11] = nv; }
      }
      c += 1u;
    }
    L0580:;
    { // pair 176 pc=0x580 up=0x000002FF lo=0x0287B004
      c = vu1gen::vmax(c, cx.vfR[22][1]);
      c = vu1gen::vmax(c, cx.viR[7]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[7] + 4) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 4u, &st.vf[22][1], 4);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L0588:;
    { // pair 177 pc=0x588 up=0x000002FF lo=0x11EC07FF
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[0] + 32767); bvOld = st.vi[12]; bvReg = 12; st.vi[12] = nv; }
      }
      c += 1u;
    }
    L0590:;
    { // pair 178 pc=0x590 up=0x000002FF lo=0x800D5274
      c = vu1gen::vmax(c, cx.viR[10]);
      c = vu1gen::vmax(c, cx.viR[13]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[10] & st.vi[13]); bvOld = st.vi[9]; bvReg = 9; st.vi[9] = nv; }
      }
      cx.viR[9] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L0598:;
    { // pair 179 pc=0x598 up=0x01939C5A lo=0x800C52B4
      c = vu1gen::vmax(c, cx.vfR[19][0]);
      c = vu1gen::vmax(c, cx.vfR[19][1]);
      c = vu1gen::vmax(c, cx.vfR[19][2]);
      c = vu1gen::vmax(c, cx.viR[10]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[19]);
        const __m128 bv = vu1gen::nrmbc(st.vf[19], 2);
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
      vu1gen::storeLanes(st.vf[17], urv, 0xCu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[17] = rt;
        cx.vfR[17][0] = rt;
        cx.vfR[17][1] = rt;
      }
      cx.viR[10] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L05A0:;
    { // pair 180 pc=0x5A0 up=0x01F2A17C lo=0x00535800
      c = vu1gen::vmax(c, cx.vfRAny[20]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      float ur0 = 0.0f;
      float ur1 = 0.0f;
      float ur2 = 0.0f;
      float ur3 = 0.0f;
      {
        { const int32_t iv = vu1gen::ftoi(vu1gen::nrm(st.vf[20][0]), 1.0f);
          std::memcpy(&ur0, &iv, 4); }
        { const int32_t iv = vu1gen::ftoi(vu1gen::nrm(st.vf[20][1]), 1.0f);
          std::memcpy(&ur1, &iv, 4); }
        { const int32_t iv = vu1gen::ftoi(vu1gen::nrm(st.vf[20][2]), 1.0f);
          std::memcpy(&ur2, &iv, 4); }
        { const int32_t iv = vu1gen::ftoi(vu1gen::nrm(st.vf[20][3]), 1.0f);
          std::memcpy(&ur3, &iv, 4); }
      }
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[11] + 0) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[19][2], vm + addr + 8u, 4);
        }
      }
      bvReg = -1;
      st.vf[18][0] = ur0;
      st.vf[18][1] = ur1;
      st.vf[18][2] = ur2;
      st.vf[18][3] = ur3;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[18] = rt;
        _mm_store_si128((__m128i *)cx.vfR[18], _mm_set1_epi32((int)rt));
      }
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[19] = rt;
        cx.vfR[19][2] = rt;
      }
      c += 1u;
    }
    L05A8:;
    { // pair 181 pc=0x5A8 up=0x000002FF lo=0x019347C6
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[8] + -58) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[19][0], vm + addr + 0u, 8);
        }
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[19] = rt;
        cx.vfR[19][0] = rt;
        cx.vfR[19][1] = rt;
      }
      c += 1u;
    }
    L05B0:;
    { // pair 182 pc=0x5B0 up=0x000002FF lo=0x81F4437C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(uint16_t)st.vi[8] * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[20][0], vm + addr + 0u, 16);
        }
        { const int32_t nv = (int32_t)(int16_t)(st.vi[8] + 1); bvOld = st.vi[8]; bvReg = 8; st.vi[8] = nv; }
      }
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[20] = rt;
        _mm_store_si128((__m128i *)cx.vfR[20], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L05B8:;
    { // pair 183 pc=0x5B8 up=0x000002FF lo=0x100B5803
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[11] + 3); bvOld = st.vi[11]; bvReg = 11; st.vi[11] = nv; }
      }
      c += 1u;
    }
    L05C0:;
    { // pair 184 pc=0x5C0 up=0x000002FF lo=0x120A5001
      c = vu1gen::vmax(c, cx.viR[10]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[10] - 1); bvOld = st.vi[10]; bvReg = 10; st.vi[10] = nv; }
      }
      cx.viR[10] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L05C8:;
    { // pair 185 pc=0x5C8 up=0x000002FF lo=0x038B8FFA
      c = vu1gen::vmax(c, cx.vfR[17][0]);
      c = vu1gen::vmax(c, cx.vfR[17][1]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[11] + -6) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[17][0], 8);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L05D0:;
    { const bool bt = (int16_t)(bvReg == 10 ? bvOld : st.vi[10]) > 0;
    { // pair 186 pc=0x5D0 up=0x000002FF lo=0x5A0057F9
      c = vu1gen::vmax(c, cx.viR[10]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    { // pair 187 pc=0x5D8 up=0x01939C5A lo=0x03EB97FB
      c = vu1gen::vmax(c, cx.vfR[19][0]);
      c = vu1gen::vmax(c, cx.vfR[19][1]);
      c = vu1gen::vmax(c, cx.vfR[19][2]);
      c = vu1gen::vmax(c, cx.vfRAny[18]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[19]);
        const __m128 bv = vu1gen::nrmbc(st.vf[19], 2);
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
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[11] + -5) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[18][0], 16);
        }
      }
      bvReg = -1;
      vu1gen::storeLanes(st.vf[17], urv, 0xCu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[17] = rt;
        cx.vfR[17][0] = rt;
        cx.vfR[17][1] = rt;
      }
      c += 1u;
    }
    if (bt) {
      st.branchTarget = 0x5A0u;
      if (c >= (uint64_t)a.maxCycles) { st.pc = 0x5A0u; goto BUDGET_OUT; }
      goto L05A0;
    } }
    goto LC05E0;
    L05D8:;
    { // pair 187 pc=0x5D8 up=0x01939C5A lo=0x03EB97FB
      c = vu1gen::vmax(c, cx.vfR[19][0]);
      c = vu1gen::vmax(c, cx.vfR[19][1]);
      c = vu1gen::vmax(c, cx.vfR[19][2]);
      c = vu1gen::vmax(c, cx.vfRAny[18]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[19]);
        const __m128 bv = vu1gen::nrmbc(st.vf[19], 2);
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
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[11] + -5) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[18][0], 16);
        }
      }
      bvReg = -1;
      vu1gen::storeLanes(st.vf[17], urv, 0xCu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[17] = rt;
        cx.vfR[17][0] = rt;
        cx.vfR[17][1] = rt;
      }
      c += 1u;
    }
    LC05E0:;
    L05E0:;
    { const bool bt = (int16_t)0 != (int16_t)(bvReg == 9 ? bvOld : st.vi[9]);
    { // pair 188 pc=0x5E0 up=0x000002FF lo=0x52090009
      c = vu1gen::vmax(c, cx.viR[9]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    { // pair 189 pc=0x5E8 up=0x000002FF lo=0x090A5FFD
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[11] + -3) * 16u) & 0x3FFFu;
          uint32_t v = 0u; std::memcpy(&v, vm + addr + 0u, 4);
          st.vi[10] = (int32_t)(int16_t)(v & 0xFFFFu);
        }
      }
      bvReg = -1;
      cx.viR[10] = (uint32_t)(c + 4u);
      c += 1u;
    }
    if (bt) {
      st.branchTarget = 0x630u;
      goto L0630;
    } }
    goto LC05F0;
    L05E8:;
    { // pair 189 pc=0x5E8 up=0x000002FF lo=0x090A5FFD
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[11] + -3) * 16u) & 0x3FFFu;
          uint32_t v = 0u; std::memcpy(&v, vm + addr + 0u, 4);
          st.vi[10] = (int32_t)(int16_t)(v & 0xFFFFu);
        }
      }
      bvReg = -1;
      cx.viR[10] = (uint32_t)(c + 4u);
      c += 1u;
    }
    LC05F0:;
    L05F0:;
    { // pair 190 pc=0x5F0 up=0x000002FF lo=0x028BAFFD
      c = vu1gen::vmax(c, cx.vfR[21][1]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[11] + -3) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 4u, &st.vf[21][1], 4);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L05F8:;
    { // pair 191 pc=0x5F8 up=0x000002FF lo=0x00535FFE
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[11] + -2) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[19][2], vm + addr + 8u, 4);
        }
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[19] = rt;
        cx.vfR[19][2] = rt;
      }
      c += 1u;
    }
    L0600:;
    { // pair 192 pc=0x600 up=0x000002FF lo=0x019347C5
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[8] + -59) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[19][0], vm + addr + 0u, 8);
        }
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[19] = rt;
        cx.vfR[19][0] = rt;
        cx.vfR[19][1] = rt;
      }
      c += 1u;
    }
    L0608:;
    { // pair 193 pc=0x608 up=0x000002FF lo=0x01F447FF
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[8] + -1) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[20][0], vm + addr + 0u, 16);
        }
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[20] = rt;
        _mm_store_si128((__m128i *)cx.vfR[20], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L0610:;
    { // pair 194 pc=0x610 up=0x000002FF lo=0x800D5274
      c = vu1gen::vmax(c, cx.viR[10]);
      c = vu1gen::vmax(c, cx.viR[13]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[10] & st.vi[13]); bvOld = st.vi[9]; bvReg = 9; st.vi[9] = nv; }
      }
      cx.viR[9] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L0618:;
    { // pair 195 pc=0x618 up=0x000002FF lo=0x800C52B4
      c = vu1gen::vmax(c, cx.viR[10]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[10] & st.vi[12]); bvOld = st.vi[10]; bvReg = 10; st.vi[10] = nv; }
      }
      cx.viR[10] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L0620:;
    st.branchTarget = 0x5A0u;
    { // pair 196 pc=0x620 up=0x01939C5A lo=0x400007EF
      c = vu1gen::vmax(c, cx.vfR[19][0]);
      c = vu1gen::vmax(c, cx.vfR[19][1]);
      c = vu1gen::vmax(c, cx.vfR[19][2]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[19]);
        const __m128 bv = vu1gen::nrmbc(st.vf[19], 2);
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
      vu1gen::storeLanes(st.vf[17], urv, 0xCu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[17] = rt;
        cx.vfR[17][0] = rt;
        cx.vfR[17][1] = rt;
      }
      c += 1u;
    }
    { // pair 197 pc=0x628 up=0x000002FF lo=0x100B5801
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[11] + 1); bvOld = st.vi[11]; bvReg = 11; st.vi[11] = nv; }
      }
      c += 1u;
    }
    if (c >= (uint64_t)a.maxCycles) { st.pc = 0x5A0u; goto BUDGET_OUT; }
    goto L05A0;
    L0628:;
    { // pair 197 pc=0x628 up=0x000002FF lo=0x100B5801
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[11] + 1); bvOld = st.vi[11]; bvReg = 11; st.vi[11] = nv; }
      }
      c += 1u;
    }
    L0630:;
    { // pair 198 pc=0x630 up=0x000002FF lo=0x80003EFC
      c = vu1gen::vmax(c, cx.viR[7]);
      cx.waitKick(c);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        cx.startKick(c, (uint32_t)(uint16_t)st.vi[7]);
      }
      bvReg = -1;
      c += 1u;
    }
    L0638:;
    { // pair 199 pc=0x638 up=0x400002FF lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    { // pair 200 pc=0x640 up=0x000002FF lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    st.pc = 0x648u; goto END_OUT;
    L0640:;
    { // pair 200 pc=0x640 up=0x000002FF lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    L0648:;
    { // pair 201 pc=0x648 up=0x000002FF lo=0x003203D0
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 976) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[18][3], vm + addr + 12u, 4);
        }
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[18] = rt;
        cx.vfR[18][3] = rt;
      }
      c += 1u;
    }
    L0650:;
    { // pair 202 pc=0x650 up=0x000002FF lo=0x090103D1
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 977) * 16u) & 0x3FFFu;
          uint32_t v = 0u; std::memcpy(&v, vm + addr + 0u, 4);
          st.vi[1] = (int32_t)(int16_t)(v & 0xFFFFu);
        }
      }
      bvReg = -1;
      cx.viR[1] = (uint32_t)(c + 4u);
      c += 1u;
    }
    L0658:;
    { // pair 203 pc=0x658 up=0x000002FF lo=0x800206BC
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        st.vi[2] = (int32_t)(st.top & 0x3FFu);
      }
      bvReg = -1;
      cx.viR[2] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L0660:;
    { // pair 204 pc=0x660 up=0x000002FF lo=0x100B1002
      c = vu1gen::vmax(c, cx.viR[2]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[2] + 2); bvOld = st.vi[11]; bvReg = 11; st.vi[11] = nv; }
      }
      c += 1u;
    }
    L0668:;
    { // pair 205 pc=0x668 up=0x00920483 lo=0x10081002
      c = vu1gen::vmax(c, cx.vfR[18][3]);
      c = vu1gen::vmax(c, cx.viR[2]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = _mm_setr_ps(0.0f, 0.0f, 0.0f, 1.0f);
        const __m128 bv = vu1gen::nrmbc(st.vf[18], 3);
        const __m128 rv = _mm_add_ps(vsv, bv);
        uint32_t mac = 0u, stf = 0u, stk = 0u;
        __m128 rvn = rv;
        { uint32_t sgn; uint32_t plain = vu1gen::classify4(rv, sgn);
          if ((plain & 0x2u) == 0x2u) {
            mac = vu1gen::kMacSign.word[sgn & 0x2u];
            stf = (sgn & 0x2u) != 0u ? 0x2u : 0u;
          } else {
            float rr[4]; _mm_storeu_ps(rr, rv);
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
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[2] + 2); bvOld = st.vi[8]; bvReg = 8; st.vi[8] = nv; }
      }
      vu1gen::storeLanes(st.vf[18], urv, 0x4u);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[18] = rt;
        cx.vfR[18][1] = rt;
      }
      c += 1u;
    }
    L0670:;
    { // pair 206 pc=0x670 up=0x000002FF lo=0x10010804
      c = vu1gen::vmax(c, cx.viR[1]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[1] + 4); bvOld = st.vi[1]; bvReg = 1; st.vi[1] = nv; }
      }
      cx.viR[1] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L0678:;
    { // pair 207 pc=0x678 up=0x000002FF lo=0x09020800
      c = vu1gen::vmax(c, cx.viR[1]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[1] + 0) * 16u) & 0x3FFFu;
          uint32_t v = 0u; std::memcpy(&v, vm + addr + 0u, 4);
          st.vi[2] = (int32_t)(int16_t)(v & 0xFFFFu);
        }
      }
      bvReg = -1;
      cx.viR[2] = (uint32_t)(c + 4u);
      c += 1u;
    }
    L0680:;
    { // pair 208 pc=0x680 up=0x000002FF lo=0x088903D1
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 977) * 16u) & 0x3FFFu;
          uint32_t v = 0u; std::memcpy(&v, vm + addr + 4u, 4);
          st.vi[9] = (int32_t)(int16_t)(v & 0xFFFFu);
        }
      }
      bvReg = -1;
      cx.viR[9] = (uint32_t)(c + 4u);
      c += 1u;
    }
    L0688:;
    { // pair 209 pc=0x688 up=0x000002FF lo=0x0A4103D2
      c = vu1gen::vmax(c, cx.viR[1]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 978) * 16u) & 0x3FFFu;
          const uint32_t v = (uint32_t)(uint16_t)(st.vi[1] & 0xFFFF);
          cx.markStore(addr);
          std::memcpy(vm + addr + 8u, &v, 4);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L0690:;
    { // pair 210 pc=0x690 up=0x000002FF lo=0x11E307FF
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[0] + 32767); bvOld = st.vi[3]; bvReg = 3; st.vi[3] = nv; }
      }
      cx.viR[3] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L0698:;
    { // pair 211 pc=0x698 up=0x000002FF lo=0x00720800
      c = vu1gen::vmax(c, cx.viR[1]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[1] + 0) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[18][2], vm + addr + 8u, 8);
        }
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[18] = rt;
        cx.vfR[18][2] = rt;
        cx.vfR[18][3] = rt;
      }
      c += 1u;
    }
    L06A0:;
    { // pair 212 pc=0x6A0 up=0x000002FF lo=0x0A2203D2
      c = vu1gen::vmax(c, cx.viR[2]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 978) * 16u) & 0x3FFFu;
          const uint32_t v = (uint32_t)(uint16_t)(st.vi[2] & 0xFFFF);
          cx.markStore(addr);
          std::memcpy(vm + addr + 12u, &v, 4);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L06A8:;
    { // pair 213 pc=0x6A8 up=0x000002FF lo=0x800312B4
      c = vu1gen::vmax(c, cx.viR[2]);
      c = vu1gen::vmax(c, cx.viR[3]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[2] & st.vi[3]); bvOld = st.vi[10]; bvReg = 10; st.vi[10] = nv; }
      }
      cx.viR[10] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L06B0:;
    { // pair 214 pc=0x6B0 up=0x00318C6C lo=0x0B0A0800
      c = vu1gen::vmax(c, cx.vfR[17][3]);
      c = vu1gen::vmax(c, cx.vfR[17][3]);
      c = vu1gen::vmax(c, cx.viR[1]);
      c = vu1gen::vmax(c, cx.viR[10]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[17]);
        const __m128 bv = vu1gen::nrm4(st.vf[17]);
        const __m128 rv = _mm_sub_ps(vsv, bv);
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
                lf = vu1gen::normExactLane(rr[3], (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(3, 3, 3, 3))) - (double)_mm_cvtss_f32(_mm_shuffle_ps(bv, bv, _MM_SHUFFLE(3, 3, 3, 3))));
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
          const uint32_t v = (uint32_t)(uint16_t)(st.vi[10] & 0xFFFF);
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &v, 4);
        }
      }
      bvReg = -1;
      vu1gen::storeLanes(st.vf[17], urv, 0x1u);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[17] = rt;
        cx.vfR[17][3] = rt;
      }
      c += 1u;
    }
    L06B8:;
    { // pair 215 pc=0x6B8 up=0x002B5AEC lo=0x120A5002
      c = vu1gen::vmax(c, cx.vfR[11][3]);
      c = vu1gen::vmax(c, cx.vfR[11][3]);
      c = vu1gen::vmax(c, cx.viR[10]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[11]);
        const __m128 bv = vu1gen::nrm4(st.vf[11]);
        const __m128 rv = _mm_sub_ps(vsv, bv);
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
                lf = vu1gen::normExactLane(rr[3], (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(3, 3, 3, 3))) - (double)_mm_cvtss_f32(_mm_shuffle_ps(bv, bv, _MM_SHUFFLE(3, 3, 3, 3))));
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
        { const int32_t nv = (int32_t)(int16_t)(st.vi[10] - 2); bvOld = st.vi[10]; bvReg = 10; st.vi[10] = nv; }
      }
      vu1gen::storeLanes(st.vf[11], urv, 0x1u);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[11] = rt;
        cx.vfR[11][3] = rt;
      }
      cx.viR[10] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L06C0:;
    { // pair 216 pc=0x6C0 up=0x000002FF lo=0x08215814
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[11] + 20) * 16u) & 0x3FFFu;
          uint32_t v = 0u; std::memcpy(&v, vm + addr + 12u, 4);
          st.vi[1] = (int32_t)(int16_t)(v & 0xFFFFu);
        }
      }
      bvReg = -1;
      cx.viR[1] = (uint32_t)(c + 4u);
      c += 1u;
    }
    L06C8:;
    { // pair 217 pc=0x6C8 up=0x000002FF lo=0x120A5001
      c = vu1gen::vmax(c, cx.viR[10]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[10] - 1); bvOld = st.vi[10]; bvReg = 10; st.vi[10] = nv; }
      }
      cx.viR[10] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L06D0:;
    { // pair 218 pc=0x6D0 up=0x000002FF lo=0x100B5801
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[11] + 1); bvOld = st.vi[11]; bvReg = 11; st.vi[11] = nv; }
      }
      c += 1u;
    }
    L06D8:;
    { // pair 219 pc=0x6D8 up=0x000002FF lo=0x10084001
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[8] + 1); bvOld = st.vi[8]; bvReg = 8; st.vi[8] = nv; }
      }
      c += 1u;
    }
    L06E0:;
    { const bool bt = (int16_t)(bvReg == 1 ? bvOld : st.vi[1]) > 0;
    { // pair 220 pc=0x6E0 up=0x000002FF lo=0x5A00080B
      c = vu1gen::vmax(c, cx.viR[1]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    { // pair 221 pc=0x6E8 up=0x000002FF lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    if (bt) {
      st.branchTarget = 0x740u;
      goto L0740;
    } }
    goto LC06F0;
    L06E8:;
    { // pair 221 pc=0x6E8 up=0x000002FF lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    LC06F0:;
    L06F0:;
    { const bool bt = (int16_t)(bvReg == 10 ? bvOld : st.vi[10]) > 0;
    { // pair 222 pc=0x6F0 up=0x000002FF lo=0x5A0057F9
      c = vu1gen::vmax(c, cx.viR[10]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    { // pair 223 pc=0x6F8 up=0x000002FF lo=0x084203D2
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 978) * 16u) & 0x3FFFu;
          uint32_t v = 0u; std::memcpy(&v, vm + addr + 8u, 4);
          st.vi[2] = (int32_t)(int16_t)(v & 0xFFFFu);
        }
      }
      bvReg = -1;
      cx.viR[2] = (uint32_t)(c + 4u);
      c += 1u;
    }
    if (bt) {
      st.branchTarget = 0x6C0u;
      if (c >= (uint64_t)a.maxCycles) { st.pc = 0x6C0u; goto BUDGET_OUT; }
      goto L06C0;
    } }
    goto LC0700;
    L06F8:;
    { // pair 223 pc=0x6F8 up=0x000002FF lo=0x084203D2
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 978) * 16u) & 0x3FFFu;
          uint32_t v = 0u; std::memcpy(&v, vm + addr + 8u, 4);
          st.vi[2] = (int32_t)(int16_t)(v & 0xFFFFu);
        }
      }
      bvReg = -1;
      cx.viR[2] = (uint32_t)(c + 4u);
      c += 1u;
    }
    LC0700:;
    L0700:;
    { // pair 224 pc=0x700 up=0x000002FF lo=0x082303D2
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 978) * 16u) & 0x3FFFu;
          uint32_t v = 0u; std::memcpy(&v, vm + addr + 12u, 4);
          st.vi[3] = (int32_t)(int16_t)(v & 0xFFFFu);
        }
      }
      bvReg = -1;
      cx.viR[3] = (uint32_t)(c + 4u);
      c += 1u;
    }
    L0708:;
    { // pair 225 pc=0x708 up=0x000002FF lo=0x090103D1
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 977) * 16u) & 0x3FFFu;
          uint32_t v = 0u; std::memcpy(&v, vm + addr + 0u, 4);
          st.vi[1] = (int32_t)(int16_t)(v & 0xFFFFu);
        }
      }
      bvReg = -1;
      cx.viR[1] = (uint32_t)(c + 4u);
      c += 1u;
    }
    L0710:;
    { // pair 226 pc=0x710 up=0x000002FF lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    L0718:;
    { // pair 227 pc=0x718 up=0x000002FF lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    L0720:;
    { // pair 228 pc=0x720 up=0x000002FF lo=0x0B031000
      c = vu1gen::vmax(c, cx.viR[2]);
      c = vu1gen::vmax(c, cx.viR[3]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[2] + 0) * 16u) & 0x3FFFu;
          const uint32_t v = (uint32_t)(uint16_t)(st.vi[3] & 0xFFFF);
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &v, 4);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L0728:;
    { // pair 229 pc=0x728 up=0x000002FF lo=0x80000EFC
      c = vu1gen::vmax(c, cx.viR[1]);
      cx.waitKick(c);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        cx.startKick(c, (uint32_t)(uint16_t)st.vi[1]);
      }
      bvReg = -1;
      c += 1u;
    }
    L0730:;
    { // pair 230 pc=0x730 up=0x400002FF lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    { // pair 231 pc=0x738 up=0x000002FF lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    st.pc = 0x740u; goto END_OUT;
    L0738:;
    { // pair 231 pc=0x738 up=0x000002FF lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    L0740:;
    { // pair 232 pc=0x740 up=0x000002FF lo=0x800706BC
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        st.vi[7] = (int32_t)(st.top & 0x3FFu);
      }
      bvReg = -1;
      cx.viR[7] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L0748:;
    { // pair 233 pc=0x748 up=0x000002FF lo=0x10040003
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[0] + 3); bvOld = st.vi[4]; bvReg = 4; st.vi[4] = nv; }
      }
      cx.viR[4] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L0750:;
    { // pair 234 pc=0x750 up=0x000002FF lo=0x0B0403D2
      c = vu1gen::vmax(c, cx.viR[4]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 978) * 16u) & 0x3FFFu;
          const uint32_t v = (uint32_t)(uint16_t)(st.vi[4] & 0xFFFF);
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &v, 4);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L0758:;
    { // pair 235 pc=0x758 up=0x000002FF lo=0x10053887
      c = vu1gen::vmax(c, cx.viR[7]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[7] + 135); bvOld = st.vi[5]; bvReg = 5; st.vi[5] = nv; }
      }
      cx.viR[5] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L0760:;
    { // pair 236 pc=0x760 up=0x000002FF lo=0x0A8503D2
      c = vu1gen::vmax(c, cx.viR[5]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 978) * 16u) & 0x3FFFu;
          const uint32_t v = (uint32_t)(uint16_t)(st.vi[5] & 0xFFFF);
          cx.markStore(addr);
          std::memcpy(vm + addr + 4u, &v, 4);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L0768:;
    { // pair 237 pc=0x768 up=0x000002FF lo=0x10063841
      c = vu1gen::vmax(c, cx.viR[7]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[7] + 65); bvOld = st.vi[6]; bvReg = 6; st.vi[6] = nv; }
      }
      cx.viR[6] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L0770:;
    { // pair 238 pc=0x770 up=0x000002FF lo=0x10073864
      c = vu1gen::vmax(c, cx.viR[7]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[7] + 100); bvOld = st.vi[7]; bvReg = 7; st.vi[7] = nv; }
      }
      cx.viR[7] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L0778:;
    { // pair 239 pc=0x778 up=0x000002FF lo=0x01F05FFF
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[11] + -1) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[16][0], vm + addr + 0u, 16);
        }
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[16] = rt;
        _mm_store_si128((__m128i *)cx.vfR[16], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L0780:;
    { // pair 240 pc=0x780 up=0x000002FF lo=0x01CF5811
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[11] + 17) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[15][0], vm + addr + 0u, 12);
        }
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[15] = rt;
        cx.vfR[15][0] = rt;
        cx.vfR[15][1] = rt;
        cx.vfR[15][2] = rt;
      }
      c += 1u;
    }
    L0788:;
    { // pair 241 pc=0x788 up=0x000002FF lo=0x01EE581A
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[11] + 26) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[14][0], vm + addr + 0u, 16);
        }
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[14] = rt;
        _mm_store_si128((__m128i *)cx.vfR[14], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L0790:;
    { // pair 242 pc=0x790 up=0x000002FF lo=0x01CD408B
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[8] + 139) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[13][0], vm + addr + 0u, 12);
        }
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[13] = rt;
        cx.vfR[13][0] = rt;
        cx.vfR[13][1] = rt;
        cx.vfR[13][2] = rt;
      }
      c += 1u;
    }
    L0798:;
    { // pair 243 pc=0x798 up=0x000002FF lo=0x01EC40C5
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[8] + 197) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[12][0], vm + addr + 0u, 16);
        }
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[12] = rt;
        _mm_store_si128((__m128i *)cx.vfR[12], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L07A0:;
    { // pair 244 pc=0x7A0 up=0x000002FF lo=0x03E68002
      c = vu1gen::vmax(c, cx.vfRAny[16]);
      c = vu1gen::vmax(c, cx.viR[6]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[6] + 2) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[16][0], 16);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L07A8:;
    { // pair 245 pc=0x7A8 up=0x000002FF lo=0x03C67800
      c = vu1gen::vmax(c, cx.vfR[15][0]);
      c = vu1gen::vmax(c, cx.vfR[15][1]);
      c = vu1gen::vmax(c, cx.vfR[15][2]);
      c = vu1gen::vmax(c, cx.viR[6]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[6] + 0) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[15][0], 12);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L07B0:;
    { // pair 246 pc=0x7B0 up=0x000002FF lo=0x03E67001
      c = vu1gen::vmax(c, cx.vfRAny[14]);
      c = vu1gen::vmax(c, cx.viR[6]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[6] + 1) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[14][0], 16);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L07B8:;
    { // pair 247 pc=0x7B8 up=0x000002FF lo=0x03C66803
      c = vu1gen::vmax(c, cx.vfR[13][0]);
      c = vu1gen::vmax(c, cx.vfR[13][1]);
      c = vu1gen::vmax(c, cx.vfR[13][2]);
      c = vu1gen::vmax(c, cx.viR[6]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[6] + 3) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[13][0], 12);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L07C0:;
    { // pair 248 pc=0x7C0 up=0x000002FF lo=0x03E66004
      c = vu1gen::vmax(c, cx.vfRAny[12]);
      c = vu1gen::vmax(c, cx.viR[6]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[6] + 4) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[12][0], 16);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L07C8:;
    { // pair 249 pc=0x7C8 up=0x000002FF lo=0x01F05800
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[11] + 0) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[16][0], vm + addr + 0u, 16);
        }
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[16] = rt;
        _mm_store_si128((__m128i *)cx.vfR[16], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L07D0:;
    { // pair 250 pc=0x7D0 up=0x000002FF lo=0x01CF5812
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[11] + 18) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[15][0], vm + addr + 0u, 12);
        }
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[15] = rt;
        cx.vfR[15][0] = rt;
        cx.vfR[15][1] = rt;
        cx.vfR[15][2] = rt;
      }
      c += 1u;
    }
    L07D8:;
    { // pair 251 pc=0x7D8 up=0x000002FF lo=0x01EE581B
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[11] + 27) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[14][0], vm + addr + 0u, 16);
        }
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[14] = rt;
        _mm_store_si128((__m128i *)cx.vfR[14], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L07E0:;
    { // pair 252 pc=0x7E0 up=0x000002FF lo=0x01CD408C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[8] + 140) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[13][0], vm + addr + 0u, 12);
        }
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[13] = rt;
        cx.vfR[13][0] = rt;
        cx.vfR[13][1] = rt;
        cx.vfR[13][2] = rt;
      }
      c += 1u;
    }
    L07E8:;
    { // pair 253 pc=0x7E8 up=0x000002FF lo=0x01EC40C6
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[8] + 198) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[12][0], vm + addr + 0u, 16);
        }
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[12] = rt;
        _mm_store_si128((__m128i *)cx.vfR[12], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L07F0:;
    { // pair 254 pc=0x7F0 up=0x000002FF lo=0x03E68007
      c = vu1gen::vmax(c, cx.vfRAny[16]);
      c = vu1gen::vmax(c, cx.viR[6]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[6] + 7) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[16][0], 16);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L07F8:;
    { // pair 255 pc=0x7F8 up=0x000002FF lo=0x03C67805
      c = vu1gen::vmax(c, cx.vfR[15][0]);
      c = vu1gen::vmax(c, cx.vfR[15][1]);
      c = vu1gen::vmax(c, cx.vfR[15][2]);
      c = vu1gen::vmax(c, cx.viR[6]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[6] + 5) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[15][0], 12);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L0800:;
    { // pair 256 pc=0x800 up=0x000002FF lo=0x03E67006
      c = vu1gen::vmax(c, cx.vfRAny[14]);
      c = vu1gen::vmax(c, cx.viR[6]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[6] + 6) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[14][0], 16);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L0808:;
    { // pair 257 pc=0x808 up=0x000002FF lo=0x03C66808
      c = vu1gen::vmax(c, cx.vfR[13][0]);
      c = vu1gen::vmax(c, cx.vfR[13][1]);
      c = vu1gen::vmax(c, cx.vfR[13][2]);
      c = vu1gen::vmax(c, cx.viR[6]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[6] + 8) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[13][0], 12);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L0810:;
    { // pair 258 pc=0x810 up=0x000002FF lo=0x03E66009
      c = vu1gen::vmax(c, cx.vfRAny[12]);
      c = vu1gen::vmax(c, cx.viR[6]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[6] + 9) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[12][0], 16);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L0818:;
    { // pair 259 pc=0x818 up=0x000002FF lo=0x01F05801
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[11] + 1) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[16][0], vm + addr + 0u, 16);
        }
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[16] = rt;
        _mm_store_si128((__m128i *)cx.vfR[16], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L0820:;
    { // pair 260 pc=0x820 up=0x000002FF lo=0x01CF5813
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[11] + 19) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[15][0], vm + addr + 0u, 12);
        }
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[15] = rt;
        cx.vfR[15][0] = rt;
        cx.vfR[15][1] = rt;
        cx.vfR[15][2] = rt;
      }
      c += 1u;
    }
    L0828:;
    { // pair 261 pc=0x828 up=0x000002FF lo=0x01EE581C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[11] + 28) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[14][0], vm + addr + 0u, 16);
        }
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[14] = rt;
        _mm_store_si128((__m128i *)cx.vfR[14], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L0830:;
    { // pair 262 pc=0x830 up=0x000002FF lo=0x01CD408D
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[8] + 141) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[13][0], vm + addr + 0u, 12);
        }
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[13] = rt;
        cx.vfR[13][0] = rt;
        cx.vfR[13][1] = rt;
        cx.vfR[13][2] = rt;
      }
      c += 1u;
    }
    L0838:;
    { // pair 263 pc=0x838 up=0x000002FF lo=0x01EC40C7
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[8] + 199) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[12][0], vm + addr + 0u, 16);
        }
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[12] = rt;
        _mm_store_si128((__m128i *)cx.vfR[12], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L0840:;
    { // pair 264 pc=0x840 up=0x000002FF lo=0x03E6800C
      c = vu1gen::vmax(c, cx.vfRAny[16]);
      c = vu1gen::vmax(c, cx.viR[6]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[6] + 12) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[16][0], 16);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L0848:;
    { // pair 265 pc=0x848 up=0x000002FF lo=0x03C6780A
      c = vu1gen::vmax(c, cx.vfR[15][0]);
      c = vu1gen::vmax(c, cx.vfR[15][1]);
      c = vu1gen::vmax(c, cx.vfR[15][2]);
      c = vu1gen::vmax(c, cx.viR[6]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[6] + 10) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[15][0], 12);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L0850:;
    { // pair 266 pc=0x850 up=0x000002FF lo=0x03E6700B
      c = vu1gen::vmax(c, cx.vfRAny[14]);
      c = vu1gen::vmax(c, cx.viR[6]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[6] + 11) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[14][0], 16);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L0858:;
    { // pair 267 pc=0x858 up=0x000002FF lo=0x03C6680D
      c = vu1gen::vmax(c, cx.vfR[13][0]);
      c = vu1gen::vmax(c, cx.vfR[13][1]);
      c = vu1gen::vmax(c, cx.vfR[13][2]);
      c = vu1gen::vmax(c, cx.viR[6]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[6] + 13) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[13][0], 12);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L0860:;
    { // pair 268 pc=0x860 up=0x000002FF lo=0x03E6600E
      c = vu1gen::vmax(c, cx.vfRAny[12]);
      c = vu1gen::vmax(c, cx.viR[6]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[6] + 14) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[12][0], 16);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L0868:;
    { // pair 269 pc=0x868 up=0x000002FF lo=0x100103BF
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[0] + 959); bvOld = st.vi[1]; bvReg = 1; st.vi[1] = nv; }
      }
      cx.viR[1] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L0870:;
    { // pair 270 pc=0x870 up=0x000002FF lo=0x01F30800
      c = vu1gen::vmax(c, cx.viR[1]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[1] + 0) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[19][0], vm + addr + 0u, 16);
        }
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[19] = rt;
        _mm_store_si128((__m128i *)cx.vfR[19], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L0878:;
    st.branchTarget = 0xA88u;
    { // pair 271 pc=0x878 up=0x000002FF lo=0x420F0041
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        st.vi[15] = (int32_t)((0x878u + 16u) / 8u);
      }
      bvReg = -1;
      c += 1u;
    }
    { // pair 272 pc=0x880 up=0x000002FF lo=0x01F40801
      c = vu1gen::vmax(c, cx.viR[1]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[1] + 1) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[20][0], vm + addr + 0u, 16);
        }
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[20] = rt;
        _mm_store_si128((__m128i *)cx.vfR[20], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    goto L0A88;
    L0880:;
    { // pair 272 pc=0x880 up=0x000002FF lo=0x01F40801
      c = vu1gen::vmax(c, cx.viR[1]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[1] + 1) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[20][0], vm + addr + 0u, 16);
        }
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[20] = rt;
        _mm_store_si128((__m128i *)cx.vfR[20], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L0888:;
    { const bool bt = (int16_t)0 == (int16_t)(bvReg == 4 ? bvOld : st.vi[4]);
    { // pair 273 pc=0x888 up=0x000002FF lo=0x500407CC
      c = vu1gen::vmax(c, cx.viR[4]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    { // pair 274 pc=0x890 up=0x000002FF lo=0x0B0403D2
      c = vu1gen::vmax(c, cx.viR[4]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 978) * 16u) & 0x3FFFu;
          const uint32_t v = (uint32_t)(uint16_t)(st.vi[4] & 0xFFFF);
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &v, 4);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    if (bt) {
      st.branchTarget = 0x6F0u;
      if (c >= (uint64_t)a.maxCycles) { st.pc = 0x6F0u; goto BUDGET_OUT; }
      goto L06F0;
    } }
    goto LC0898;
    L0890:;
    { // pair 274 pc=0x890 up=0x000002FF lo=0x0B0403D2
      c = vu1gen::vmax(c, cx.viR[4]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 978) * 16u) & 0x3FFFu;
          const uint32_t v = (uint32_t)(uint16_t)(st.vi[4] & 0xFFFF);
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &v, 4);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    LC0898:;
    L0898:;
    { // pair 275 pc=0x898 up=0x000002FF lo=0x084603D1
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 977) * 16u) & 0x3FFFu;
          uint32_t v = 0u; std::memcpy(&v, vm + addr + 8u, 4);
          st.vi[6] = (int32_t)(int16_t)(v & 0xFFFFu);
        }
      }
      bvReg = -1;
      cx.viR[6] = (uint32_t)(c + 4u);
      c += 1u;
    }
    L08A0:;
    { // pair 276 pc=0x8A0 up=0x000002FF lo=0x082703D1
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 977) * 16u) & 0x3FFFu;
          uint32_t v = 0u; std::memcpy(&v, vm + addr + 12u, 4);
          st.vi[7] = (int32_t)(int16_t)(v & 0xFFFFu);
        }
      }
      bvReg = -1;
      cx.viR[7] = (uint32_t)(c + 4u);
      c += 1u;
    }
    L08A8:;
    { // pair 277 pc=0x8A8 up=0x000002FF lo=0x100103C3
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[0] + 963); bvOld = st.vi[1]; bvReg = 1; st.vi[1] = nv; }
      }
      cx.viR[1] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L08B0:;
    { // pair 278 pc=0x8B0 up=0x000002FF lo=0x01F30800
      c = vu1gen::vmax(c, cx.viR[1]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[1] + 0) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[19][0], vm + addr + 0u, 16);
        }
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[19] = rt;
        _mm_store_si128((__m128i *)cx.vfR[19], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L08B8:;
    st.branchTarget = 0xA88u;
    { // pair 279 pc=0x8B8 up=0x000002FF lo=0x420F0039
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        st.vi[15] = (int32_t)((0x8B8u + 16u) / 8u);
      }
      bvReg = -1;
      c += 1u;
    }
    { // pair 280 pc=0x8C0 up=0x000002FF lo=0x01F40801
      c = vu1gen::vmax(c, cx.viR[1]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[1] + 1) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[20][0], vm + addr + 0u, 16);
        }
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[20] = rt;
        _mm_store_si128((__m128i *)cx.vfR[20], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    goto L0A88;
    L08C0:;
    { // pair 280 pc=0x8C0 up=0x000002FF lo=0x01F40801
      c = vu1gen::vmax(c, cx.viR[1]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[1] + 1) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[20][0], vm + addr + 0u, 16);
        }
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[20] = rt;
        _mm_store_si128((__m128i *)cx.vfR[20], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L08C8:;
    { const bool bt = (int16_t)0 == (int16_t)(bvReg == 4 ? bvOld : st.vi[4]);
    { // pair 281 pc=0x8C8 up=0x000002FF lo=0x500407C4
      c = vu1gen::vmax(c, cx.viR[4]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    { // pair 282 pc=0x8D0 up=0x000002FF lo=0x0B0403D2
      c = vu1gen::vmax(c, cx.viR[4]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 978) * 16u) & 0x3FFFu;
          const uint32_t v = (uint32_t)(uint16_t)(st.vi[4] & 0xFFFF);
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &v, 4);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    if (bt) {
      st.branchTarget = 0x6F0u;
      if (c >= (uint64_t)a.maxCycles) { st.pc = 0x6F0u; goto BUDGET_OUT; }
      goto L06F0;
    } }
    goto LC08D8;
    L08D0:;
    { // pair 282 pc=0x8D0 up=0x000002FF lo=0x0B0403D2
      c = vu1gen::vmax(c, cx.viR[4]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 978) * 16u) & 0x3FFFu;
          const uint32_t v = (uint32_t)(uint16_t)(st.vi[4] & 0xFFFF);
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &v, 4);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    LC08D8:;
    L08D8:;
    { // pair 283 pc=0x8D8 up=0x000002FF lo=0x084603D1
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 977) * 16u) & 0x3FFFu;
          uint32_t v = 0u; std::memcpy(&v, vm + addr + 8u, 4);
          st.vi[6] = (int32_t)(int16_t)(v & 0xFFFFu);
        }
      }
      bvReg = -1;
      cx.viR[6] = (uint32_t)(c + 4u);
      c += 1u;
    }
    L08E0:;
    { // pair 284 pc=0x8E0 up=0x000002FF lo=0x082703D1
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 977) * 16u) & 0x3FFFu;
          uint32_t v = 0u; std::memcpy(&v, vm + addr + 12u, 4);
          st.vi[7] = (int32_t)(int16_t)(v & 0xFFFFu);
        }
      }
      bvReg = -1;
      cx.viR[7] = (uint32_t)(c + 4u);
      c += 1u;
    }
    L08E8:;
    { // pair 285 pc=0x8E8 up=0x000002FF lo=0x100103C7
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[0] + 967); bvOld = st.vi[1]; bvReg = 1; st.vi[1] = nv; }
      }
      cx.viR[1] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L08F0:;
    { // pair 286 pc=0x8F0 up=0x000002FF lo=0x01F30800
      c = vu1gen::vmax(c, cx.viR[1]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[1] + 0) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[19][0], vm + addr + 0u, 16);
        }
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[19] = rt;
        _mm_store_si128((__m128i *)cx.vfR[19], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L08F8:;
    st.branchTarget = 0xA88u;
    { // pair 287 pc=0x8F8 up=0x000002FF lo=0x420F0031
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        st.vi[15] = (int32_t)((0x8F8u + 16u) / 8u);
      }
      bvReg = -1;
      c += 1u;
    }
    { // pair 288 pc=0x900 up=0x000002FF lo=0x01F40801
      c = vu1gen::vmax(c, cx.viR[1]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[1] + 1) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[20][0], vm + addr + 0u, 16);
        }
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[20] = rt;
        _mm_store_si128((__m128i *)cx.vfR[20], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    goto L0A88;
    L0900:;
    { // pair 288 pc=0x900 up=0x000002FF lo=0x01F40801
      c = vu1gen::vmax(c, cx.viR[1]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[1] + 1) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[20][0], vm + addr + 0u, 16);
        }
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[20] = rt;
        _mm_store_si128((__m128i *)cx.vfR[20], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L0908:;
    { const bool bt = (int16_t)0 == (int16_t)(bvReg == 4 ? bvOld : st.vi[4]);
    { // pair 289 pc=0x908 up=0x000002FF lo=0x500407BC
      c = vu1gen::vmax(c, cx.viR[4]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    { // pair 290 pc=0x910 up=0x000002FF lo=0x0B0403D2
      c = vu1gen::vmax(c, cx.viR[4]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 978) * 16u) & 0x3FFFu;
          const uint32_t v = (uint32_t)(uint16_t)(st.vi[4] & 0xFFFF);
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &v, 4);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    if (bt) {
      st.branchTarget = 0x6F0u;
      if (c >= (uint64_t)a.maxCycles) { st.pc = 0x6F0u; goto BUDGET_OUT; }
      goto L06F0;
    } }
    goto LC0918;
    L0910:;
    { // pair 290 pc=0x910 up=0x000002FF lo=0x0B0403D2
      c = vu1gen::vmax(c, cx.viR[4]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 978) * 16u) & 0x3FFFu;
          const uint32_t v = (uint32_t)(uint16_t)(st.vi[4] & 0xFFFF);
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &v, 4);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    LC0918:;
    L0918:;
    { // pair 291 pc=0x918 up=0x000002FF lo=0x084603D1
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 977) * 16u) & 0x3FFFu;
          uint32_t v = 0u; std::memcpy(&v, vm + addr + 8u, 4);
          st.vi[6] = (int32_t)(int16_t)(v & 0xFFFFu);
        }
      }
      bvReg = -1;
      cx.viR[6] = (uint32_t)(c + 4u);
      c += 1u;
    }
    L0920:;
    { // pair 292 pc=0x920 up=0x000002FF lo=0x082703D1
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 977) * 16u) & 0x3FFFu;
          uint32_t v = 0u; std::memcpy(&v, vm + addr + 12u, 4);
          st.vi[7] = (int32_t)(int16_t)(v & 0xFFFFu);
        }
      }
      bvReg = -1;
      cx.viR[7] = (uint32_t)(c + 4u);
      c += 1u;
    }
    L0928:;
    { // pair 293 pc=0x928 up=0x000002FF lo=0x100103CB
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[0] + 971); bvOld = st.vi[1]; bvReg = 1; st.vi[1] = nv; }
      }
      cx.viR[1] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L0930:;
    { // pair 294 pc=0x930 up=0x000002FF lo=0x01F30800
      c = vu1gen::vmax(c, cx.viR[1]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[1] + 0) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[19][0], vm + addr + 0u, 16);
        }
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[19] = rt;
        _mm_store_si128((__m128i *)cx.vfR[19], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L0938:;
    st.branchTarget = 0xA88u;
    { // pair 295 pc=0x938 up=0x000002FF lo=0x420F0029
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        st.vi[15] = (int32_t)((0x938u + 16u) / 8u);
      }
      bvReg = -1;
      c += 1u;
    }
    { // pair 296 pc=0x940 up=0x000002FF lo=0x01F40801
      c = vu1gen::vmax(c, cx.viR[1]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[1] + 1) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[20][0], vm + addr + 0u, 16);
        }
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[20] = rt;
        _mm_store_si128((__m128i *)cx.vfR[20], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    goto L0A88;
    L0940:;
    { // pair 296 pc=0x940 up=0x000002FF lo=0x01F40801
      c = vu1gen::vmax(c, cx.viR[1]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[1] + 1) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[20][0], vm + addr + 0u, 16);
        }
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[20] = rt;
        _mm_store_si128((__m128i *)cx.vfR[20], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L0948:;
    { const bool bt = (int16_t)0 == (int16_t)(bvReg == 4 ? bvOld : st.vi[4]);
    { // pair 297 pc=0x948 up=0x000002FF lo=0x500407B4
      c = vu1gen::vmax(c, cx.viR[4]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    { // pair 298 pc=0x950 up=0x000002FF lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    if (bt) {
      st.branchTarget = 0x6F0u;
      if (c >= (uint64_t)a.maxCycles) { st.pc = 0x6F0u; goto BUDGET_OUT; }
      goto L06F0;
    } }
    goto LC0958;
    L0950:;
    { // pair 298 pc=0x950 up=0x000002FF lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    LC0958:;
    L0958:;
    { // pair 299 pc=0x958 up=0x000002FF lo=0x084603D1
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 977) * 16u) & 0x3FFFu;
          uint32_t v = 0u; std::memcpy(&v, vm + addr + 8u, 4);
          st.vi[6] = (int32_t)(int16_t)(v & 0xFFFFu);
        }
      }
      bvReg = -1;
      cx.viR[6] = (uint32_t)(c + 4u);
      c += 1u;
    }
    L0960:;
    { // pair 300 pc=0x960 up=0x000002FF lo=0x08810390
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 912) * 16u) & 0x3FFFu;
          uint32_t v = 0u; std::memcpy(&v, vm + addr + 4u, 4);
          st.vi[1] = (int32_t)(int16_t)(v & 0xFFFFu);
        }
      }
      bvReg = -1;
      cx.viR[1] = (uint32_t)(c + 4u);
      c += 1u;
    }
    L0968:;
    { // pair 301 pc=0x968 up=0x000002FF lo=0x02EC9000
      c = vu1gen::vmax(c, cx.vfR[18][1]);
      c = vu1gen::vmax(c, cx.vfR[18][2]);
      c = vu1gen::vmax(c, cx.vfR[18][3]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[12] + 0) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 4u, &st.vf[18][1], 12);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L0970:;
    { // pair 302 pc=0x970 up=0x000002FF lo=0x0B046000
      c = vu1gen::vmax(c, cx.viR[4]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[12] + 0) * 16u) & 0x3FFFu;
          const uint32_t v = (uint32_t)(uint16_t)(st.vi[4] & 0xFFFF);
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &v, 4);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L0978:;
    { // pair 303 pc=0x978 up=0x000002FF lo=0x01F03002
      c = vu1gen::vmax(c, cx.viR[6]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[6] + 2) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[16][0], vm + addr + 0u, 16);
        }
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[16] = rt;
        _mm_store_si128((__m128i *)cx.vfR[16], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L0980:;
    { // pair 304 pc=0x980 up=0x000002FF lo=0x01EE3001
      c = vu1gen::vmax(c, cx.viR[6]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[6] + 1) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[14][0], vm + addr + 0u, 16);
        }
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[14] = rt;
        _mm_store_si128((__m128i *)cx.vfR[14], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L0988:;
    { // pair 305 pc=0x988 up=0x000002FF lo=0x80040875
      c = vu1gen::vmax(c, cx.viR[1]);
      c = vu1gen::vmax(c, cx.viR[4]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[1] | st.vi[4]); bvOld = st.vi[1]; bvReg = 1; st.vi[1] = nv; }
      }
      cx.viR[1] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L0990:;
    { // pair 306 pc=0x990 up=0x000002FF lo=0x0A4C03D2
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 978) * 16u) & 0x3FFFu;
          const uint32_t v = (uint32_t)(uint16_t)(st.vi[12] & 0xFFFF);
          cx.markStore(addr);
          std::memcpy(vm + addr + 8u, &v, 4);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L0998:;
    { // pair 307 pc=0x998 up=0x01F0E1BC lo=0x0A2103D2
      c = vu1gen::vmax(c, cx.vfRAny[28]);
      c = vu1gen::vmax(c, cx.vfR[16][0]);
      c = vu1gen::vmax(c, cx.viR[1]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[28]);
        const __m128 bv = vu1gen::nrmbc(st.vf[16], 0);
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
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 978) * 16u) & 0x3FFFu;
          const uint32_t v = (uint32_t)(uint16_t)(st.vi[1] & 0xFFFF);
          cx.markStore(addr);
          std::memcpy(vm + addr + 12u, &v, 4);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L09A0:;
    { // pair 308 pc=0x9A0 up=0x01F0E8BD lo=0x10063005
      c = vu1gen::vmax(c, cx.vfRAny[29]);
      c = vu1gen::vmax(c, cx.vfR[16][1]);
      c = vu1gen::vmax(c, cx.viR[6]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[29]);
        const __m128 bv = vu1gen::nrmbc(st.vf[16], 1);
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
        { const int32_t nv = (int32_t)(int16_t)(st.vi[6] + 5); bvOld = st.vi[6]; bvReg = 6; st.vi[6] = nv; }
      }
      cx.viR[6] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L09A8:;
    { // pair 309 pc=0x9A8 up=0x01F0F0BE lo=0x100C6001
      c = vu1gen::vmax(c, cx.vfRAny[30]);
      c = vu1gen::vmax(c, cx.vfR[16][2]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[30]);
        const __m128 bv = vu1gen::nrmbc(st.vf[16], 2);
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
        { const int32_t nv = (int32_t)(int16_t)(st.vi[12] + 1); bvOld = st.vi[12]; bvReg = 12; st.vi[12] = nv; }
      }
      c += 1u;
    }
    L09B0:;
    { // pair 310 pc=0x9B0 up=0x01F0FC0B lo=0x8000033C
      c = vu1gen::vmax(c, cx.vfRAny[31]);
      c = vu1gen::vmax(c, cx.vfR[16][3]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[31]);
        const __m128 bv = vu1gen::nrmbc(st.vf[16], 3);
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
      vu1gen::storeLanes(st.vf[16], urv, 0xFu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[16] = rt;
        _mm_store_si128((__m128i *)cx.vfR[16], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L09B8:;
    { // pair 311 pc=0x9B8 up=0x000002FF lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    L09C0:;
    { // pair 312 pc=0x9C0 up=0x000002FF lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    L09C8:;
    { // pair 313 pc=0x9C8 up=0x003B01BE lo=0x8000033C
      c = vu1gen::vmax(c, cx.vfR[27][2]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        const __m128 vsv = _mm_setr_ps(0.0f, 0.0f, 0.0f, 1.0f);
        const __m128 bv = vu1gen::nrmbc(st.vf[27], 2);
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
        vu1gen::storeLanes(st.acc, rvn, 0x1u);
      }
      bvReg = -1;
      c += 1u;
    }
    L09D0:;
    { // pair 314 pc=0x9D0 up=0x0030DC29 lo=0x81F003BC
      c = vu1gen::vmax(c, cx.vfR[27][3]);
      c = vu1gen::vmax(c, cx.vfR[16][3]);
      c = vu1gen::vmax(c, cx.vfR[16][3]);
      if (cx.qValid) c = vu1gen::vmax(c, cx.qReady);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[27]);
        const __m128 bv = vu1gen::nrm4(st.vf[16]);
        const __m128 av = vu1gen::nrm4(st.acc);
        const __m128 product = _mm_mul_ps(vsv, bv);
        const __m128 rv = _mm_add_ps(av, product);
        uint32_t mac = 0u, stf = 0u, stk = 0u;
        __m128 rvn = rv;
        { uint32_t sgn; uint32_t plain = vu1gen::classify4(rv, sgn);
          const __m128i pm = _mm_and_si128(_mm_castps_si128(product), _mm_set1_epi32(0x7FFFFFFF));
          plain &= ~uint32_t(_mm_movemask_ps(_mm_castsi128_ps(_mm_cmpgt_epi32(pm, _mm_set1_epi32(0x7F7FFFFE)))));
          if ((plain & 0x8u) == 0x8u) {
            mac = vu1gen::kMacSign.word[sgn & 0x8u];
            stf = (sgn & 0x8u) != 0u ? 0x2u : 0u;
          } else {
            float rr[4]; _mm_storeu_ps(rr, rv);
            { uint8_t lf;
              if (plain & 8u) lf = ((sgn >> 3) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[3], (double)_mm_cvtss_f32(_mm_shuffle_ps(av, av, _MM_SHUFFLE(3, 3, 3, 3))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(3, 3, 3, 3))) * (double)_mm_cvtss_f32(_mm_shuffle_ps(bv, bv, _MM_SHUFFLE(3, 3, 3, 3))));
              } else {
                uint32_t nf; rr[3] = vu1gen::normResult(rr[3], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[3][lf & 0xFu]; stf |= lf & 0xFu; }
            rvn = _mm_loadu_ps(rr);
          } }
        if (cx.sticky) stk = vu1gen::sticky4(vsv, bv, product, 0x8u);
        cx.pushFmac(c, mac, stf, stk);
        urv = rvn;
      }
      {
        cx.commitQ(c);
        { const float num = vu1gen::nrm(st.vf[0][3]);
          const float den = vu1gen::nrm(st.vf[16][3]);
          uint32_t di = 0u; float r;
          if (den == 0.0f) { di = (num == 0.0f) ? 0x10u : 0x20u;
            r = (std::signbit(num) != std::signbit(den)) ? -std::numeric_limits<float>::max() : std::numeric_limits<float>::max(); }
          else r = num / den;
          uint32_t ig; r = vu1gen::normResult(r, ig);
          cx.qValid = true; cx.qReady = c + 7u; cx.qVal = r; cx.qDi = di; }
      }
      bvReg = -1;
      vu1gen::storeLanes(st.vf[16], urv, 0x1u);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[16] = rt;
        cx.vfR[16][3] = rt;
      }
      c += 1u;
    }
    L09D8:;
    { // pair 315 pc=0x9D8 up=0x000002FF lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    L09E0:;
    { // pair 316 pc=0x9E0 up=0x000002FF lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    L09E8:;
    { // pair 317 pc=0x9E8 up=0x01C08140 lo=0x8000033C
      c = vu1gen::vmax(c, cx.vfR[16][0]);
      c = vu1gen::vmax(c, cx.vfR[16][1]);
      c = vu1gen::vmax(c, cx.vfR[16][2]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[16]);
        const __m128 bv = _mm_set1_ps(0.0f);
        const __m128 rv = _mm_add_ps(vsv, bv);
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
            rvn = _mm_loadu_ps(rr);
          } }
        cx.pushFmac(c, mac, stf, stk);
        urv = rvn;
      }
      bvReg = -1;
      vu1gen::storeLanes(st.vf[5], urv, 0xEu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[5] = rt;
        cx.vfR[5][0] = rt;
        cx.vfR[5][1] = rt;
        cx.vfR[5][2] = rt;
      }
      c += 1u;
    }
    L09F0:;
    { // pair 318 pc=0x9F0 up=0x0020815F lo=0x8000033C
      c = vu1gen::vmax(c, cx.vfR[16][3]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[16]);
        const __m128 bv = _mm_set1_ps(vu1gen::nrm(st.i));
        const __m128 rv = _mm_min_ps(vsv, bv);
        urv = rv;
      }
      bvReg = -1;
      vu1gen::storeLanes(st.vf[5], urv, 0x1u);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[5] = rt;
        cx.vfR[5][3] = rt;
      }
      c += 1u;
    }
    L09F8:;
    { // pair 319 pc=0x9F8 up=0x000002FF lo=0x01F03002
      c = vu1gen::vmax(c, cx.viR[6]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[6] + 2) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[16][0], vm + addr + 0u, 16);
        }
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[16] = rt;
        _mm_store_si128((__m128i *)cx.vfR[16], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L0A00:;
    { // pair 320 pc=0xA00 up=0x01E3717C lo=0x01EE3001
      c = vu1gen::vmax(c, cx.vfRAny[14]);
      c = vu1gen::vmax(c, cx.viR[6]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      float ur0 = 0.0f;
      float ur1 = 0.0f;
      float ur2 = 0.0f;
      float ur3 = 0.0f;
      {
        { const int32_t iv = vu1gen::ftoi(vu1gen::nrm(st.vf[14][0]), 1.0f);
          std::memcpy(&ur0, &iv, 4); }
        { const int32_t iv = vu1gen::ftoi(vu1gen::nrm(st.vf[14][1]), 1.0f);
          std::memcpy(&ur1, &iv, 4); }
        { const int32_t iv = vu1gen::ftoi(vu1gen::nrm(st.vf[14][2]), 1.0f);
          std::memcpy(&ur2, &iv, 4); }
        { const int32_t iv = vu1gen::ftoi(vu1gen::nrm(st.vf[14][3]), 1.0f);
          std::memcpy(&ur3, &iv, 4); }
      }
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[6] + 1) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[14][0], vm + addr + 0u, 16);
        }
      }
      bvReg = -1;
      st.vf[3][0] = ur0;
      st.vf[3][1] = ur1;
      st.vf[3][2] = ur2;
      st.vf[3][3] = ur3;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[3] = rt;
        _mm_store_si128((__m128i *)cx.vfR[3], _mm_set1_epi32((int)rt));
      }
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[14] = rt;
        _mm_store_si128((__m128i *)cx.vfR[14], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L0A08:;
    { // pair 321 pc=0xA08 up=0x01C0295C lo=0x01CD37FE
      c = vu1gen::vmax(c, cx.vfR[5][0]);
      c = vu1gen::vmax(c, cx.vfR[5][1]);
      c = vu1gen::vmax(c, cx.vfR[5][2]);
      c = vu1gen::vmax(c, cx.viR[6]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      cx.commitQ(c);
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[5]);
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
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[6] + -2) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[13][0], vm + addr + 0u, 12);
        }
      }
      bvReg = -1;
      vu1gen::storeLanes(st.vf[5], urv, 0xEu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[5] = rt;
        cx.vfR[5][0] = rt;
        cx.vfR[5][1] = rt;
        cx.vfR[5][2] = rt;
      }
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[13] = rt;
        cx.vfR[13][0] = rt;
        cx.vfR[13][1] = rt;
        cx.vfR[13][2] = rt;
      }
      c += 1u;
    }
    L0A10:;
    { // pair 322 pc=0xA10 up=0x00202950 lo=0x01EC37FF
      c = vu1gen::vmax(c, cx.vfR[5][3]);
      c = vu1gen::vmax(c, cx.viR[6]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[5]);
        const __m128 bv = _mm_set1_ps(0.0f);
        const __m128 rv = _mm_max_ps(vsv, bv);
        urv = rv;
      }
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[6] + -1) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[12][0], vm + addr + 0u, 16);
        }
      }
      bvReg = -1;
      vu1gen::storeLanes(st.vf[5], urv, 0x1u);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[5] = rt;
        cx.vfR[5][3] = rt;
      }
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[12] = rt;
        _mm_store_si128((__m128i *)cx.vfR[12], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L0A18:;
    { // pair 323 pc=0xA18 up=0x01F0E1BC lo=0x01CF37FB
      c = vu1gen::vmax(c, cx.vfRAny[28]);
      c = vu1gen::vmax(c, cx.vfR[16][0]);
      c = vu1gen::vmax(c, cx.viR[6]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[28]);
        const __m128 bv = vu1gen::nrmbc(st.vf[16], 0);
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
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[6] + -5) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[15][0], vm + addr + 0u, 12);
        }
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[15] = rt;
        cx.vfR[15][0] = rt;
        cx.vfR[15][1] = rt;
        cx.vfR[15][2] = rt;
      }
      c += 1u;
    }
    L0A20:;
    { // pair 324 pc=0xA20 up=0x01F0E8BD lo=0x10063005
      c = vu1gen::vmax(c, cx.vfRAny[29]);
      c = vu1gen::vmax(c, cx.vfR[16][1]);
      c = vu1gen::vmax(c, cx.viR[6]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[29]);
        const __m128 bv = vu1gen::nrmbc(st.vf[16], 1);
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
        { const int32_t nv = (int32_t)(int16_t)(st.vi[6] + 5); bvOld = st.vi[6]; bvReg = 6; st.vi[6] = nv; }
      }
      cx.viR[6] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L0A28:;
    { // pair 325 pc=0xA28 up=0x01F0F0BE lo=0x12042001
      c = vu1gen::vmax(c, cx.vfRAny[30]);
      c = vu1gen::vmax(c, cx.vfR[16][2]);
      c = vu1gen::vmax(c, cx.viR[4]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[30]);
        const __m128 bv = vu1gen::nrmbc(st.vf[16], 2);
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
        { const int32_t nv = (int32_t)(int16_t)(st.vi[4] - 1); bvOld = st.vi[4]; bvReg = 4; st.vi[4] = nv; }
      }
      cx.viR[4] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L0A30:;
    { // pair 326 pc=0xA30 up=0x01F0FC0B lo=0x100C6003
      c = vu1gen::vmax(c, cx.vfRAny[31]);
      c = vu1gen::vmax(c, cx.vfR[16][3]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[31]);
        const __m128 bv = vu1gen::nrmbc(st.vf[16], 3);
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
        { const int32_t nv = (int32_t)(int16_t)(st.vi[12] + 3); bvOld = st.vi[12]; bvReg = 12; st.vi[12] = nv; }
      }
      vu1gen::storeLanes(st.vf[16], urv, 0xFu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[16] = rt;
        _mm_store_si128((__m128i *)cx.vfR[16], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L0A38:;
    { // pair 327 pc=0xA38 up=0x01C07BDC lo=0x10094801
      c = vu1gen::vmax(c, cx.vfR[15][0]);
      c = vu1gen::vmax(c, cx.vfR[15][1]);
      c = vu1gen::vmax(c, cx.vfR[15][2]);
      c = vu1gen::vmax(c, cx.viR[9]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      cx.commitQ(c);
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[15]);
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
        { const int32_t nv = (int32_t)(int16_t)(st.vi[9] + 1); bvOld = st.vi[9]; bvReg = 9; st.vi[9] = nv; }
      }
      vu1gen::storeLanes(st.vf[15], urv, 0xEu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[15] = rt;
        cx.vfR[15][0] = rt;
        cx.vfR[15][1] = rt;
        cx.vfR[15][2] = rt;
      }
      cx.viR[9] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L0A40:;
    { // pair 328 pc=0xA40 up=0x01E4297D lo=0x03C9688D
      c = vu1gen::vmax(c, cx.vfRAny[5]);
      c = vu1gen::vmax(c, cx.vfR[13][0]);
      c = vu1gen::vmax(c, cx.vfR[13][1]);
      c = vu1gen::vmax(c, cx.vfR[13][2]);
      c = vu1gen::vmax(c, cx.viR[9]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      float ur0 = 0.0f;
      float ur1 = 0.0f;
      float ur2 = 0.0f;
      float ur3 = 0.0f;
      {
        { const int32_t iv = vu1gen::ftoi(vu1gen::nrm(st.vf[5][0]), 16.0f);
          std::memcpy(&ur0, &iv, 4); }
        { const int32_t iv = vu1gen::ftoi(vu1gen::nrm(st.vf[5][1]), 16.0f);
          std::memcpy(&ur1, &iv, 4); }
        { const int32_t iv = vu1gen::ftoi(vu1gen::nrm(st.vf[5][2]), 16.0f);
          std::memcpy(&ur2, &iv, 4); }
        { const int32_t iv = vu1gen::ftoi(vu1gen::nrm(st.vf[5][3]), 16.0f);
          std::memcpy(&ur3, &iv, 4); }
      }
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[9] + 141) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[13][0], 12);
        }
      }
      bvReg = -1;
      st.vf[4][0] = ur0;
      st.vf[4][1] = ur1;
      st.vf[4][2] = ur2;
      st.vf[4][3] = ur3;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[4] = rt;
        _mm_store_si128((__m128i *)cx.vfR[4], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L0A48:;
    { // pair 329 pc=0xA48 up=0x003B01BE lo=0x03E960C7
      c = vu1gen::vmax(c, cx.vfR[27][2]);
      c = vu1gen::vmax(c, cx.vfRAny[12]);
      c = vu1gen::vmax(c, cx.viR[9]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        const __m128 vsv = _mm_setr_ps(0.0f, 0.0f, 0.0f, 1.0f);
        const __m128 bv = vu1gen::nrmbc(st.vf[27], 2);
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
        vu1gen::storeLanes(st.acc, rvn, 0x1u);
      }
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[9] + 199) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[12][0], 16);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L0A50:;
    { // pair 330 pc=0xA50 up=0x0030DC29 lo=0x81F003BC
      c = vu1gen::vmax(c, cx.vfR[27][3]);
      c = vu1gen::vmax(c, cx.vfR[16][3]);
      c = vu1gen::vmax(c, cx.vfR[16][3]);
      if (cx.qValid) c = vu1gen::vmax(c, cx.qReady);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[27]);
        const __m128 bv = vu1gen::nrm4(st.vf[16]);
        const __m128 av = vu1gen::nrm4(st.acc);
        const __m128 product = _mm_mul_ps(vsv, bv);
        const __m128 rv = _mm_add_ps(av, product);
        uint32_t mac = 0u, stf = 0u, stk = 0u;
        __m128 rvn = rv;
        { uint32_t sgn; uint32_t plain = vu1gen::classify4(rv, sgn);
          const __m128i pm = _mm_and_si128(_mm_castps_si128(product), _mm_set1_epi32(0x7FFFFFFF));
          plain &= ~uint32_t(_mm_movemask_ps(_mm_castsi128_ps(_mm_cmpgt_epi32(pm, _mm_set1_epi32(0x7F7FFFFE)))));
          if ((plain & 0x8u) == 0x8u) {
            mac = vu1gen::kMacSign.word[sgn & 0x8u];
            stf = (sgn & 0x8u) != 0u ? 0x2u : 0u;
          } else {
            float rr[4]; _mm_storeu_ps(rr, rv);
            { uint8_t lf;
              if (plain & 8u) lf = ((sgn >> 3) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[3], (double)_mm_cvtss_f32(_mm_shuffle_ps(av, av, _MM_SHUFFLE(3, 3, 3, 3))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(3, 3, 3, 3))) * (double)_mm_cvtss_f32(_mm_shuffle_ps(bv, bv, _MM_SHUFFLE(3, 3, 3, 3))));
              } else {
                uint32_t nf; rr[3] = vu1gen::normResult(rr[3], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[3][lf & 0xFu]; stf |= lf & 0xFu; }
            rvn = _mm_loadu_ps(rr);
          } }
        if (cx.sticky) stk = vu1gen::sticky4(vsv, bv, product, 0x8u);
        cx.pushFmac(c, mac, stf, stk);
        urv = rvn;
      }
      {
        cx.commitQ(c);
        { const float num = vu1gen::nrm(st.vf[0][3]);
          const float den = vu1gen::nrm(st.vf[16][3]);
          uint32_t di = 0u; float r;
          if (den == 0.0f) { di = (num == 0.0f) ? 0x10u : 0x20u;
            r = (std::signbit(num) != std::signbit(den)) ? -std::numeric_limits<float>::max() : std::numeric_limits<float>::max(); }
          else r = num / den;
          uint32_t ig; r = vu1gen::normResult(r, ig);
          cx.qValid = true; cx.qReady = c + 7u; cx.qVal = r; cx.qDi = di; }
      }
      bvReg = -1;
      vu1gen::storeLanes(st.vf[16], urv, 0x1u);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[16] = rt;
        cx.vfR[16][3] = rt;
      }
      c += 1u;
    }
    L0A58:;
    { // pair 331 pc=0xA58 up=0x000002FF lo=0x03CC7FFD
      c = vu1gen::vmax(c, cx.vfR[15][0]);
      c = vu1gen::vmax(c, cx.vfR[15][1]);
      c = vu1gen::vmax(c, cx.vfR[15][2]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[12] + -3) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[15][0], 12);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L0A60:;
    { // pair 332 pc=0xA60 up=0x000002FF lo=0x03EC1FFE
      c = vu1gen::vmax(c, cx.vfRAny[3]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[12] + -2) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[3][0], 16);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L0A68:;
    { const bool bt = (int16_t)(bvReg == 4 ? bvOld : st.vi[4]) > 0;
    { // pair 333 pc=0xA68 up=0x01C08140 lo=0x5A0027F1
      c = vu1gen::vmax(c, cx.vfR[16][0]);
      c = vu1gen::vmax(c, cx.vfR[16][1]);
      c = vu1gen::vmax(c, cx.vfR[16][2]);
      c = vu1gen::vmax(c, cx.viR[4]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[16]);
        const __m128 bv = _mm_set1_ps(0.0f);
        const __m128 rv = _mm_add_ps(vsv, bv);
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
            rvn = _mm_loadu_ps(rr);
          } }
        cx.pushFmac(c, mac, stf, stk);
        urv = rvn;
      }
      bvReg = -1;
      vu1gen::storeLanes(st.vf[5], urv, 0xEu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[5] = rt;
        cx.vfR[5][0] = rt;
        cx.vfR[5][1] = rt;
        cx.vfR[5][2] = rt;
      }
      c += 1u;
    }
    { // pair 334 pc=0xA70 up=0x0020815F lo=0x03EC27FF
      c = vu1gen::vmax(c, cx.vfR[16][3]);
      c = vu1gen::vmax(c, cx.vfRAny[4]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[16]);
        const __m128 bv = _mm_set1_ps(vu1gen::nrm(st.i));
        const __m128 rv = _mm_min_ps(vsv, bv);
        urv = rv;
      }
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[12] + -1) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[4][0], 16);
        }
      }
      bvReg = -1;
      vu1gen::storeLanes(st.vf[5], urv, 0x1u);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[5] = rt;
        cx.vfR[5][3] = rt;
      }
      c += 1u;
    }
    if (bt) {
      st.branchTarget = 0x9F8u;
      if (c >= (uint64_t)a.maxCycles) { st.pc = 0x9F8u; goto BUDGET_OUT; }
      goto L09F8;
    } }
    goto LC0A78;
    L0A70:;
    { // pair 334 pc=0xA70 up=0x0020815F lo=0x03EC27FF
      c = vu1gen::vmax(c, cx.vfR[16][3]);
      c = vu1gen::vmax(c, cx.vfRAny[4]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[16]);
        const __m128 bv = _mm_set1_ps(vu1gen::nrm(st.i));
        const __m128 rv = _mm_min_ps(vsv, bv);
        urv = rv;
      }
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[12] + -1) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[4][0], 16);
        }
      }
      bvReg = -1;
      vu1gen::storeLanes(st.vf[5], urv, 0x1u);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[5] = rt;
        cx.vfR[5][3] = rt;
      }
      c += 1u;
    }
    LC0A78:;
    L0A78:;
    st.branchTarget = 0x6F0u;
    { // pair 335 pc=0xA78 up=0x000002FF lo=0x4000078E
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    { // pair 336 pc=0xA80 up=0x000002FF lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    if (c >= (uint64_t)a.maxCycles) { st.pc = 0x6F0u; goto BUDGET_OUT; }
    goto L06F0;
    L0A80:;
    { // pair 336 pc=0xA80 up=0x000002FF lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    L0A88:;
    { // pair 337 pc=0xA88 up=0x000002FF lo=0x01F03002
      c = vu1gen::vmax(c, cx.viR[6]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[6] + 2) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[16][0], vm + addr + 0u, 16);
        }
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[16] = rt;
        _mm_store_si128((__m128i *)cx.vfR[16], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L0A90:;
    { // pair 338 pc=0xA90 up=0x000002FF lo=0x01F50802
      c = vu1gen::vmax(c, cx.viR[1]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[1] + 2) * 16u) & 0x3FFFu;
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
    L0A98:;
    { // pair 339 pc=0xA98 up=0x000002FF lo=0x01F60803
      c = vu1gen::vmax(c, cx.viR[1]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[1] + 3) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[22][0], vm + addr + 0u, 16);
        }
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[22] = rt;
        _mm_store_si128((__m128i *)cx.vfR[22], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L0AA0:;
    { // pair 340 pc=0xAA0 up=0x000002FF lo=0x0A4703D1
      c = vu1gen::vmax(c, cx.viR[7]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 977) * 16u) & 0x3FFFu;
          const uint32_t v = (uint32_t)(uint16_t)(st.vi[7] & 0xFFFF);
          cx.markStore(addr);
          std::memcpy(vm + addr + 8u, &v, 4);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L0AA8:;
    { // pair 341 pc=0xAA8 up=0x01F099BC lo=0x0A2603D1
      c = vu1gen::vmax(c, cx.vfRAny[19]);
      c = vu1gen::vmax(c, cx.vfR[16][0]);
      c = vu1gen::vmax(c, cx.viR[6]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[19]);
        const __m128 bv = vu1gen::nrmbc(st.vf[16], 0);
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
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 977) * 16u) & 0x3FFFu;
          const uint32_t v = (uint32_t)(uint16_t)(st.vi[6] & 0xFFFF);
          cx.markStore(addr);
          std::memcpy(vm + addr + 12u, &v, 4);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L0AB0:;
    { // pair 342 pc=0xAB0 up=0x01F0A0BD lo=0x088503D2
      c = vu1gen::vmax(c, cx.vfRAny[20]);
      c = vu1gen::vmax(c, cx.vfR[16][1]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[20]);
        const __m128 bv = vu1gen::nrmbc(st.vf[16], 1);
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
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 978) * 16u) & 0x3FFFu;
          uint32_t v = 0u; std::memcpy(&v, vm + addr + 4u, 4);
          st.vi[5] = (int32_t)(int16_t)(v & 0xFFFFu);
        }
      }
      bvReg = -1;
      cx.viR[5] = (uint32_t)(c + 4u);
      c += 1u;
    }
    L0AB8:;
    { // pair 343 pc=0xAB8 up=0x01F0A8BE lo=0x10063005
      c = vu1gen::vmax(c, cx.vfRAny[21]);
      c = vu1gen::vmax(c, cx.vfR[16][2]);
      c = vu1gen::vmax(c, cx.viR[6]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[21]);
        const __m128 bv = vu1gen::nrmbc(st.vf[16], 2);
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
        { const int32_t nv = (int32_t)(int16_t)(st.vi[6] + 5); bvOld = st.vi[6]; bvReg = 6; st.vi[6] = nv; }
      }
      cx.viR[6] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L0AC0:;
    { // pair 344 pc=0xAC0 up=0x01F0B14B lo=0x01F03002
      c = vu1gen::vmax(c, cx.vfRAny[22]);
      c = vu1gen::vmax(c, cx.vfR[16][3]);
      c = vu1gen::vmax(c, cx.viR[6]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[22]);
        const __m128 bv = vu1gen::nrmbc(st.vf[16], 3);
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
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[6] + 2) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[16][0], vm + addr + 0u, 16);
        }
      }
      bvReg = -1;
      vu1gen::storeLanes(st.vf[5], urv, 0xFu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[5] = rt;
        _mm_store_si128((__m128i *)cx.vfR[5], _mm_set1_epi32((int)rt));
      }
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[16] = rt;
        _mm_store_si128((__m128i *)cx.vfR[16], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L0AC8:;
    { // pair 345 pc=0xAC8 up=0x000002FF lo=0x10063005
      c = vu1gen::vmax(c, cx.viR[6]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[6] + 5); bvOld = st.vi[6]; bvReg = 6; st.vi[6] = nv; }
      }
      cx.viR[6] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L0AD0:;
    { // pair 346 pc=0xAD0 up=0x000002FF lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    L0AD8:;
    { // pair 347 pc=0xAD8 up=0x000002FF lo=0x12042001
      c = vu1gen::vmax(c, cx.viR[4]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[4] - 1); bvOld = st.vi[4]; bvReg = 4; st.vi[4] = nv; }
      }
      cx.viR[4] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L0AE0:;
    { // pair 348 pc=0xAE0 up=0x01F099BC lo=0x8000033C
      c = vu1gen::vmax(c, cx.vfRAny[19]);
      c = vu1gen::vmax(c, cx.vfR[16][0]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[19]);
        const __m128 bv = vu1gen::nrmbc(st.vf[16], 0);
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
    L0AE8:;
    { const bool bt = (int16_t)(bvReg == 4 ? bvOld : st.vi[4]) > 0;
    { // pair 349 pc=0xAE8 up=0x01F0A0BD lo=0x5A0027FA
      c = vu1gen::vmax(c, cx.vfRAny[20]);
      c = vu1gen::vmax(c, cx.vfR[16][1]);
      c = vu1gen::vmax(c, cx.viR[4]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[20]);
        const __m128 bv = vu1gen::nrmbc(st.vf[16], 1);
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
    { // pair 350 pc=0xAF0 up=0x01F0A8BE lo=0x81E52B7D
      c = vu1gen::vmax(c, cx.vfRAny[21]);
      c = vu1gen::vmax(c, cx.vfR[16][2]);
      c = vu1gen::vmax(c, cx.vfRAny[5]);
      c = vu1gen::vmax(c, cx.viR[5]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[21]);
        const __m128 bv = vu1gen::nrmbc(st.vf[16], 2);
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
        { const uint32_t addr = ((uint32_t)(uint16_t)st.vi[5] * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[5][0], 16);
        }
        { const int32_t nv = (int32_t)(int16_t)(st.vi[5] + 1); bvOld = st.vi[5]; bvReg = 5; st.vi[5] = nv; }
      }
      cx.viR[5] = (uint32_t)(c + 1u);
      c += 1u;
    }
    if (bt) {
      st.branchTarget = 0xAC0u;
      if (c >= (uint64_t)a.maxCycles) { st.pc = 0xAC0u; goto BUDGET_OUT; }
      goto L0AC0;
    } }
    goto LC0AF8;
    L0AF0:;
    { // pair 350 pc=0xAF0 up=0x01F0A8BE lo=0x81E52B7D
      c = vu1gen::vmax(c, cx.vfRAny[21]);
      c = vu1gen::vmax(c, cx.vfR[16][2]);
      c = vu1gen::vmax(c, cx.vfRAny[5]);
      c = vu1gen::vmax(c, cx.viR[5]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[21]);
        const __m128 bv = vu1gen::nrmbc(st.vf[16], 2);
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
        { const uint32_t addr = ((uint32_t)(uint16_t)st.vi[5] * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[5][0], 16);
        }
        { const int32_t nv = (int32_t)(int16_t)(st.vi[5] + 1); bvOld = st.vi[5]; bvReg = 5; st.vi[5] = nv; }
      }
      cx.viR[5] = (uint32_t)(c + 1u);
      c += 1u;
    }
    LC0AF8:;
    L0AF8:;
    { // pair 351 pc=0xAF8 up=0x000002FF lo=0x088503D2
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 978) * 16u) & 0x3FFFu;
          uint32_t v = 0u; std::memcpy(&v, vm + addr + 4u, 4);
          st.vi[5] = (int32_t)(int16_t)(v & 0xFFFFu);
        }
      }
      bvReg = -1;
      cx.viR[5] = (uint32_t)(c + 4u);
      c += 1u;
    }
    L0B00:;
    { // pair 352 pc=0xB00 up=0x000002FF lo=0x090403D2
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 978) * 16u) & 0x3FFFu;
          uint32_t v = 0u; std::memcpy(&v, vm + addr + 0u, 4);
          st.vi[4] = (int32_t)(int16_t)(v & 0xFFFFu);
        }
      }
      bvReg = -1;
      cx.viR[4] = (uint32_t)(c + 4u);
      c += 1u;
    }
    L0B08:;
    { // pair 353 pc=0xB08 up=0x000002FF lo=0x082603D1
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 977) * 16u) & 0x3FFFu;
          uint32_t v = 0u; std::memcpy(&v, vm + addr + 12u, 4);
          st.vi[6] = (int32_t)(int16_t)(v & 0xFFFFu);
        }
      }
      bvReg = -1;
      cx.viR[6] = (uint32_t)(c + 4u);
      c += 1u;
    }
    L0B10:;
    { // pair 354 pc=0xB10 up=0x000002FF lo=0x084703D1
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 977) * 16u) & 0x3FFFu;
          uint32_t v = 0u; std::memcpy(&v, vm + addr + 8u, 4);
          st.vi[7] = (int32_t)(int16_t)(v & 0xFFFFu);
        }
      }
      bvReg = -1;
      cx.viR[7] = (uint32_t)(c + 4u);
      c += 1u;
    }
    L0B18:;
    { // pair 355 pc=0xB18 up=0x000002FF lo=0x81D12B7C
      c = vu1gen::vmax(c, cx.viR[5]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(uint16_t)st.vi[5] * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[17][0], vm + addr + 0u, 12);
        }
        { const int32_t nv = (int32_t)(int16_t)(st.vi[5] + 1); bvOld = st.vi[5]; bvReg = 5; st.vi[5] = nv; }
      }
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[17] = rt;
        cx.vfR[17][0] = rt;
        cx.vfR[17][1] = rt;
        cx.vfR[17][2] = rt;
      }
      cx.viR[5] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L0B20:;
    { // pair 356 pc=0xB20 up=0x000002FF lo=0x01F03002
      c = vu1gen::vmax(c, cx.viR[6]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[6] + 2) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[16][0], vm + addr + 0u, 16);
        }
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[16] = rt;
        _mm_store_si128((__m128i *)cx.vfR[16], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L0B28:;
    { // pair 357 pc=0xB28 up=0x000002FF lo=0x01CF3000
      c = vu1gen::vmax(c, cx.viR[6]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[6] + 0) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[15][0], vm + addr + 0u, 12);
        }
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[15] = rt;
        cx.vfR[15][0] = rt;
        cx.vfR[15][1] = rt;
        cx.vfR[15][2] = rt;
      }
      c += 1u;
    }
    L0B30:;
    { // pair 358 pc=0xB30 up=0x000002FF lo=0x01EE3001
      c = vu1gen::vmax(c, cx.viR[6]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[6] + 1) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[14][0], vm + addr + 0u, 16);
        }
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[14] = rt;
        _mm_store_si128((__m128i *)cx.vfR[14], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L0B38:;
    { // pair 359 pc=0xB38 up=0x01D189FF lo=0x01CD3003
      c = vu1gen::vmax(c, cx.vfR[17][0]);
      c = vu1gen::vmax(c, cx.vfR[17][1]);
      c = vu1gen::vmax(c, cx.vfR[17][2]);
      c = vu1gen::vmax(c, cx.vfR[17][3]);
      c = vu1gen::vmax(c, cx.viR[6]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { uint32_t wb = 0u; std::memcpy(&wb, &st.vf[17][3], 4);
          const int32_t limit = (wb & 0x7F800000u) != 0u ? (int32_t)(wb & 0x7FFFFFFFu) : 0x007FFFFF;
          uint32_t fl = 0u;
          { uint32_t vb = 0u; std::memcpy(&vb, &st.vf[17][0], 4);
            int32_t ob; uint32_t t = vb; std::memcpy(&ob, &t, 4); if (ob > limit) fl |= 0x01u;
            t = vb ^ 0x80000000u; std::memcpy(&ob, &t, 4); if (ob > limit) fl |= 0x02u; }
          { uint32_t vb = 0u; std::memcpy(&vb, &st.vf[17][1], 4);
            int32_t ob; uint32_t t = vb; std::memcpy(&ob, &t, 4); if (ob > limit) fl |= 0x04u;
            t = vb ^ 0x80000000u; std::memcpy(&ob, &t, 4); if (ob > limit) fl |= 0x08u; }
          { uint32_t vb = 0u; std::memcpy(&vb, &st.vf[17][2], 4);
            int32_t ob; uint32_t t = vb; std::memcpy(&ob, &t, 4); if (ob > limit) fl |= 0x10u;
            t = vb ^ 0x80000000u; std::memcpy(&ob, &t, 4); if (ob > limit) fl |= 0x20u; }
          cx.workingClip = ((cx.workingClip << 6) | (fl & 0x3Fu)) & 0xFFFFFFu;
          cx.pushClip(c, cx.workingClip); }
      }
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[6] + 3) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[13][0], vm + addr + 0u, 12);
        }
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[13] = rt;
        cx.vfR[13][0] = rt;
        cx.vfR[13][1] = rt;
        cx.vfR[13][2] = rt;
      }
      c += 1u;
    }
    L0B40:;
    { // pair 360 pc=0xB40 up=0x000002FF lo=0x01EC3004
      c = vu1gen::vmax(c, cx.viR[6]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[6] + 4) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[12][0], vm + addr + 0u, 16);
        }
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[12] = rt;
        _mm_store_si128((__m128i *)cx.vfR[12], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L0B48:;
    { // pair 361 pc=0xB48 up=0x000002FF lo=0x800000B0
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[0] + st.vi[0]); bvOld = st.vi[2]; bvReg = 2; st.vi[2] = nv; }
      }
      cx.viR[2] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L0B50:;
    { // pair 362 pc=0xB50 up=0x000002FF lo=0x12042001
      c = vu1gen::vmax(c, cx.viR[4]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[4] - 1); bvOld = st.vi[4]; bvReg = 4; st.vi[4] = nv; }
      }
      cx.viR[4] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L0B58:;
    { // pair 363 pc=0xB58 up=0x000002FF lo=0x10063005
      c = vu1gen::vmax(c, cx.viR[6]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[6] + 5); bvOld = st.vi[6]; bvReg = 6; st.vi[6] = nv; }
      }
      cx.viR[6] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L0B60:;
    { // pair 364 pc=0xB60 up=0x000002FF lo=0x81CB2B7C
      c = vu1gen::vmax(c, cx.viR[5]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(uint16_t)st.vi[5] * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[11][0], vm + addr + 0u, 12);
        }
        { const int32_t nv = (int32_t)(int16_t)(st.vi[5] + 1); bvOld = st.vi[5]; bvReg = 5; st.vi[5] = nv; }
      }
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[11] = rt;
        cx.vfR[11][0] = rt;
        cx.vfR[11][1] = rt;
        cx.vfR[11][2] = rt;
      }
      cx.viR[5] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L0B68:;
    { // pair 365 pc=0xB68 up=0x000002FF lo=0x01EA3002
      c = vu1gen::vmax(c, cx.viR[6]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[6] + 2) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[10][0], vm + addr + 0u, 16);
        }
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[10] = rt;
        _mm_store_si128((__m128i *)cx.vfR[10], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L0B70:;
    { // pair 366 pc=0xB70 up=0x000002FF lo=0x01C93000
      c = vu1gen::vmax(c, cx.viR[6]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[6] + 0) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[9][0], vm + addr + 0u, 12);
        }
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[9] = rt;
        cx.vfR[9][0] = rt;
        cx.vfR[9][1] = rt;
        cx.vfR[9][2] = rt;
      }
      c += 1u;
    }
    L0B78:;
    { // pair 367 pc=0xB78 up=0x000002FF lo=0x01E83001
      c = vu1gen::vmax(c, cx.viR[6]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[6] + 1) * 16u) & 0x3FFFu;
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
    L0B80:;
    { // pair 368 pc=0xB80 up=0x01CB59FF lo=0x01C73003
      c = vu1gen::vmax(c, cx.vfR[11][0]);
      c = vu1gen::vmax(c, cx.vfR[11][1]);
      c = vu1gen::vmax(c, cx.vfR[11][2]);
      c = vu1gen::vmax(c, cx.vfR[11][3]);
      c = vu1gen::vmax(c, cx.viR[6]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { uint32_t wb = 0u; std::memcpy(&wb, &st.vf[11][3], 4);
          const int32_t limit = (wb & 0x7F800000u) != 0u ? (int32_t)(wb & 0x7FFFFFFFu) : 0x007FFFFF;
          uint32_t fl = 0u;
          { uint32_t vb = 0u; std::memcpy(&vb, &st.vf[11][0], 4);
            int32_t ob; uint32_t t = vb; std::memcpy(&ob, &t, 4); if (ob > limit) fl |= 0x01u;
            t = vb ^ 0x80000000u; std::memcpy(&ob, &t, 4); if (ob > limit) fl |= 0x02u; }
          { uint32_t vb = 0u; std::memcpy(&vb, &st.vf[11][1], 4);
            int32_t ob; uint32_t t = vb; std::memcpy(&ob, &t, 4); if (ob > limit) fl |= 0x04u;
            t = vb ^ 0x80000000u; std::memcpy(&ob, &t, 4); if (ob > limit) fl |= 0x08u; }
          { uint32_t vb = 0u; std::memcpy(&vb, &st.vf[11][2], 4);
            int32_t ob; uint32_t t = vb; std::memcpy(&ob, &t, 4); if (ob > limit) fl |= 0x10u;
            t = vb ^ 0x80000000u; std::memcpy(&ob, &t, 4); if (ob > limit) fl |= 0x20u; }
          cx.workingClip = ((cx.workingClip << 6) | (fl & 0x3Fu)) & 0xFFFFFFu;
          cx.pushClip(c, cx.workingClip); }
      }
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[6] + 3) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[7][0], vm + addr + 0u, 12);
        }
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[7] = rt;
        cx.vfR[7][0] = rt;
        cx.vfR[7][1] = rt;
        cx.vfR[7][2] = rt;
      }
      c += 1u;
    }
    L0B88:;
    { // pair 369 pc=0xB88 up=0x000002FF lo=0x01E63004
      c = vu1gen::vmax(c, cx.viR[6]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[6] + 4) * 16u) & 0x3FFFu;
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
    L0B90:;
    { // pair 370 pc=0xB90 up=0x000002FF lo=0x12042001
      c = vu1gen::vmax(c, cx.viR[4]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[4] - 1); bvOld = st.vi[4]; bvReg = 4; st.vi[4] = nv; }
      }
      cx.viR[4] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L0B98:;
    { // pair 371 pc=0xB98 up=0x000002FF lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    L0BA0:;
    { // pair 372 pc=0xBA0 up=0x000002FF lo=0x26FFFBEF
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        cx.commitQ(c); cx.drainFlags(c);
        st.vi[1] = ((st.clip | 0xFFFBEFu) == 0xFFFFFFu) ? 1 : 0;
      }
      bvReg = -1;
      cx.viR[1] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L0BA8:;
    { const bool bt = (int16_t)0 != (int16_t)(bvReg == 1 ? bvOld : st.vi[1]);
    { // pair 373 pc=0xBA8 up=0x000002FF lo=0x5201003D
      c = vu1gen::vmax(c, cx.viR[1]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    { // pair 374 pc=0xBB0 up=0x000002FF lo=0x24000410
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        cx.commitQ(c); cx.drainFlags(c);
        st.vi[1] = ((st.clip & 0x410u) != 0u) ? 1 : 0;
      }
      bvReg = -1;
      cx.viR[1] = (uint32_t)(c + 1u);
      c += 1u;
    }
    if (bt) {
      st.branchTarget = 0xD98u;
      goto L0D98;
    } }
    goto LC0BB8;
    L0BB0:;
    { // pair 374 pc=0xBB0 up=0x000002FF lo=0x24000410
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        cx.commitQ(c); cx.drainFlags(c);
        st.vi[1] = ((st.clip & 0x410u) != 0u) ? 1 : 0;
      }
      bvReg = -1;
      cx.viR[1] = (uint32_t)(c + 1u);
      c += 1u;
    }
    LC0BB8:;
    L0BB8:;
    { const bool bt = (int16_t)0 == (int16_t)(bvReg == 1 ? bvOld : st.vi[1]);
    { // pair 375 pc=0xBB8 up=0x000002FF lo=0x50010042
      c = vu1gen::vmax(c, cx.viR[1]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    { // pair 376 pc=0xBC0 up=0x000002FF lo=0x24000400
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        cx.commitQ(c); cx.drainFlags(c);
        st.vi[1] = ((st.clip & 0x400u) != 0u) ? 1 : 0;
      }
      bvReg = -1;
      cx.viR[1] = (uint32_t)(c + 1u);
      c += 1u;
    }
    if (bt) {
      st.branchTarget = 0xDD0u;
      goto L0DD0;
    } }
    goto LC0BC8;
    L0BC0:;
    { // pair 376 pc=0xBC0 up=0x000002FF lo=0x24000400
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        cx.commitQ(c); cx.drainFlags(c);
        st.vi[1] = ((st.clip & 0x400u) != 0u) ? 1 : 0;
      }
      bvReg = -1;
      cx.viR[1] = (uint32_t)(c + 1u);
      c += 1u;
    }
    LC0BC8:;
    L0BC8:;
    { const bool bt = (int16_t)0 == (int16_t)(bvReg == 1 ? bvOld : st.vi[1]);
    { // pair 377 pc=0xBC8 up=0x000002FF lo=0x5001001D
      c = vu1gen::vmax(c, cx.viR[1]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    { // pair 378 pc=0xBD0 up=0x000002FF lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    if (bt) {
      st.branchTarget = 0xCB8u;
      goto L0CB8;
    } }
    goto LC0BD8;
    L0BD0:;
    { // pair 378 pc=0xBD0 up=0x000002FF lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    LC0BD8:;
    L0BD8:;
    { // pair 379 pc=0xBD8 up=0x004B886C lo=0x8025033C
      c = vu1gen::vmax(c, cx.vfR[17][2]);
      c = vu1gen::vmax(c, cx.vfR[11][2]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[17]);
        const __m128 bv = vu1gen::nrm4(st.vf[11]);
        const __m128 rv = _mm_sub_ps(vsv, bv);
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
                lf = vu1gen::normExactLane(rr[2], (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(2, 2, 2, 2))) - (double)_mm_cvtss_f32(_mm_shuffle_ps(bv, bv, _MM_SHUFFLE(2, 2, 2, 2))));
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
        const float mv3 = st.vf[0][3];
        st.vf[5][3] = mv3;
      }
      bvReg = -1;
      vu1gen::storeLanes(st.vf[1], urv, 0x2u);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[1] = rt;
        cx.vfR[1][2] = rt;
      }
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[5] = rt;
        cx.vfR[5][3] = rt;
      }
      c += 1u;
    }
    L0BE0:;
    { // pair 380 pc=0xBE0 up=0x01D0516C lo=0x00440390
      c = vu1gen::vmax(c, cx.vfR[10][0]);
      c = vu1gen::vmax(c, cx.vfR[10][1]);
      c = vu1gen::vmax(c, cx.vfR[10][2]);
      c = vu1gen::vmax(c, cx.vfR[16][0]);
      c = vu1gen::vmax(c, cx.vfR[16][1]);
      c = vu1gen::vmax(c, cx.vfR[16][2]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[10]);
        const __m128 bv = vu1gen::nrm4(st.vf[16]);
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
        urv = rvn;
      }
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 912) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[4][2], vm + addr + 8u, 4);
        }
      }
      bvReg = -1;
      vu1gen::storeLanes(st.vf[5], urv, 0xEu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[5] = rt;
        cx.vfR[5][0] = rt;
        cx.vfR[5][1] = rt;
        cx.vfR[5][2] = rt;
      }
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[4] = rt;
        cx.vfR[4][2] = rt;
      }
      c += 1u;
    }
    L0BE8:;
    { // pair 381 pc=0xBE8 up=0x018F492C lo=0x00420390
      c = vu1gen::vmax(c, cx.vfR[9][0]);
      c = vu1gen::vmax(c, cx.vfR[9][1]);
      c = vu1gen::vmax(c, cx.vfR[15][0]);
      c = vu1gen::vmax(c, cx.vfR[15][1]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[9]);
        const __m128 bv = vu1gen::nrm4(st.vf[15]);
        const __m128 rv = _mm_sub_ps(vsv, bv);
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
            rvn = _mm_loadu_ps(rr);
          } }
        cx.pushFmac(c, mac, stf, stk);
        urv = rvn;
      }
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 912) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[2][2], vm + addr + 8u, 4);
        }
      }
      bvReg = -1;
      vu1gen::storeLanes(st.vf[4], urv, 0xCu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[4] = rt;
        cx.vfR[4][0] = rt;
        cx.vfR[4][1] = rt;
      }
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[2] = rt;
        cx.vfR[2][2] = rt;
      }
      c += 1u;
    }
    L0BF0:;
    { // pair 382 pc=0xBF0 up=0x01EE40EC lo=0x10021001
      c = vu1gen::vmax(c, cx.vfRAny[8]);
      c = vu1gen::vmax(c, cx.vfRAny[14]);
      c = vu1gen::vmax(c, cx.viR[2]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[8]);
        const __m128 bv = vu1gen::nrm4(st.vf[14]);
        const __m128 rv = _mm_sub_ps(vsv, bv);
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
            { uint8_t lf;
              if (plain & 8u) lf = ((sgn >> 3) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[3], (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(3, 3, 3, 3))) - (double)_mm_cvtss_f32(_mm_shuffle_ps(bv, bv, _MM_SHUFFLE(3, 3, 3, 3))));
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
        { const int32_t nv = (int32_t)(int16_t)(st.vi[2] + 1); bvOld = st.vi[2]; bvReg = 2; st.vi[2] = nv; }
      }
      vu1gen::storeLanes(st.vf[3], urv, 0xFu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[3] = rt;
        _mm_store_si128((__m128i *)cx.vfR[3], _mm_set1_epi32((int)rt));
      }
      cx.viR[2] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L0BF8:;
    { // pair 383 pc=0xBF8 up=0x018D38AC lo=0x81418BBC
      c = vu1gen::vmax(c, cx.vfR[7][0]);
      c = vu1gen::vmax(c, cx.vfR[7][1]);
      c = vu1gen::vmax(c, cx.vfR[13][0]);
      c = vu1gen::vmax(c, cx.vfR[13][1]);
      c = vu1gen::vmax(c, cx.vfR[17][2]);
      c = vu1gen::vmax(c, cx.vfR[1][2]);
      if (cx.qValid) c = vu1gen::vmax(c, cx.qReady);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[7]);
        const __m128 bv = vu1gen::nrm4(st.vf[13]);
        const __m128 rv = _mm_sub_ps(vsv, bv);
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
            rvn = _mm_loadu_ps(rr);
          } }
        cx.pushFmac(c, mac, stf, stk);
        urv = rvn;
      }
      {
        cx.commitQ(c);
        { const float num = vu1gen::nrm(st.vf[17][2]);
          const float den = vu1gen::nrm(st.vf[1][2]);
          uint32_t di = 0u; float r;
          if (den == 0.0f) { di = (num == 0.0f) ? 0x10u : 0x20u;
            r = (std::signbit(num) != std::signbit(den)) ? -std::numeric_limits<float>::max() : std::numeric_limits<float>::max(); }
          else r = num / den;
          uint32_t ig; r = vu1gen::normResult(r, ig);
          cx.qValid = true; cx.qReady = c + 7u; cx.qVal = r; cx.qDi = di; }
      }
      bvReg = -1;
      vu1gen::storeLanes(st.vf[2], urv, 0xCu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[2] = rt;
        cx.vfR[2][0] = rt;
        cx.vfR[2][1] = rt;
      }
      c += 1u;
    }
    L0C00:;
    { // pair 384 pc=0xC00 up=0x01EC306C lo=0x10073805
      c = vu1gen::vmax(c, cx.vfRAny[6]);
      c = vu1gen::vmax(c, cx.vfRAny[12]);
      c = vu1gen::vmax(c, cx.viR[7]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[6]);
        const __m128 bv = vu1gen::nrm4(st.vf[12]);
        const __m128 rv = _mm_sub_ps(vsv, bv);
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
            { uint8_t lf;
              if (plain & 8u) lf = ((sgn >> 3) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[3], (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(3, 3, 3, 3))) - (double)_mm_cvtss_f32(_mm_shuffle_ps(bv, bv, _MM_SHUFFLE(3, 3, 3, 3))));
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
        { const int32_t nv = (int32_t)(int16_t)(st.vi[7] + 5); bvOld = st.vi[7]; bvReg = 7; st.vi[7] = nv; }
      }
      vu1gen::storeLanes(st.vf[1], urv, 0xFu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[1] = rt;
        _mm_store_si128((__m128i *)cx.vfR[1], _mm_set1_epi32((int)rt));
      }
      cx.viR[7] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L0C08:;
    { // pair 385 pc=0xC08 up=0x000002FF lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    L0C10:;
    { // pair 386 pc=0xC10 up=0x000002FF lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    L0C18:;
    { // pair 387 pc=0xC18 up=0x000002FF lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    L0C20:;
    { // pair 388 pc=0xC20 up=0x000002FF lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    L0C28:;
    { // pair 389 pc=0xC28 up=0x01C0803C lo=0x8000033C
      c = vu1gen::vmax(c, cx.vfR[16][0]);
      c = vu1gen::vmax(c, cx.vfR[16][1]);
      c = vu1gen::vmax(c, cx.vfR[16][2]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[16]);
        const __m128 bv = _mm_set1_ps(0.0f);
        const __m128 rv = _mm_add_ps(vsv, bv);
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
            rvn = _mm_loadu_ps(rr);
          } }
        cx.pushFmac(c, mac, stf, stk);
        vu1gen::storeLanes(st.acc, rvn, 0xEu);
      }
      bvReg = -1;
      c += 1u;
    }
    L0C30:;
    { // pair 390 pc=0xC30 up=0x01C02961 lo=0x8000033C
      c = vu1gen::vmax(c, cx.vfR[5][0]);
      c = vu1gen::vmax(c, cx.vfR[5][1]);
      c = vu1gen::vmax(c, cx.vfR[5][2]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      cx.commitQ(c);
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[5]);
        const __m128 bv = _mm_set1_ps(vu1gen::nrm(st.q));
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
      vu1gen::storeLanes(st.vf[5], urv, 0xEu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[5] = rt;
        cx.vfR[5][0] = rt;
        cx.vfR[5][1] = rt;
        cx.vfR[5][2] = rt;
      }
      c += 1u;
    }
    L0C38:;
    { // pair 391 pc=0xC38 up=0x0180783C lo=0x8000033C
      c = vu1gen::vmax(c, cx.vfR[15][0]);
      c = vu1gen::vmax(c, cx.vfR[15][1]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[15]);
        const __m128 bv = _mm_set1_ps(0.0f);
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
        vu1gen::storeLanes(st.acc, rvn, 0xCu);
      }
      bvReg = -1;
      c += 1u;
    }
    L0C40:;
    { // pair 392 pc=0xC40 up=0x01802121 lo=0x8000033C
      c = vu1gen::vmax(c, cx.vfR[4][0]);
      c = vu1gen::vmax(c, cx.vfR[4][1]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      cx.commitQ(c);
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[4]);
        const __m128 bv = _mm_set1_ps(vu1gen::nrm(st.q));
        const __m128 av = vu1gen::nrm4(st.acc);
        const __m128 product = _mm_mul_ps(vsv, bv);
        const __m128 rv = _mm_add_ps(av, product);
        uint32_t mac = 0u, stf = 0u, stk = 0u;
        __m128 rvn = rv;
        { uint32_t sgn; uint32_t plain = vu1gen::classify4(rv, sgn);
          const __m128i pm = _mm_and_si128(_mm_castps_si128(product), _mm_set1_epi32(0x7FFFFFFF));
          plain &= ~uint32_t(_mm_movemask_ps(_mm_castsi128_ps(_mm_cmpgt_epi32(pm, _mm_set1_epi32(0x7F7FFFFE)))));
          if ((plain & 0x3u) == 0x3u) {
            mac = vu1gen::kMacSign.word[sgn & 0x3u];
            stf = (sgn & 0x3u) != 0u ? 0x2u : 0u;
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
            rvn = _mm_loadu_ps(rr);
          } }
        if (cx.sticky) stk = vu1gen::sticky4(vsv, bv, product, 0x3u);
        cx.pushFmac(c, mac, stf, stk);
        urv = rvn;
      }
      bvReg = -1;
      vu1gen::storeLanes(st.vf[4], urv, 0xCu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[4] = rt;
        cx.vfR[4][0] = rt;
        cx.vfR[4][1] = rt;
      }
      c += 1u;
    }
    L0C48:;
    { // pair 393 pc=0xC48 up=0x01E0703C lo=0x8000033C
      c = vu1gen::vmax(c, cx.vfRAny[14]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[14]);
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
        vu1gen::storeLanes(st.acc, rvn, 0xFu);
      }
      bvReg = -1;
      c += 1u;
    }
    L0C50:;
    { // pair 394 pc=0xC50 up=0x01E018E1 lo=0x03E72FFD
      c = vu1gen::vmax(c, cx.vfRAny[3]);
      c = vu1gen::vmax(c, cx.vfRAny[5]);
      c = vu1gen::vmax(c, cx.viR[7]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      cx.commitQ(c);
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[3]);
        const __m128 bv = _mm_set1_ps(vu1gen::nrm(st.q));
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
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[7] + -3) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[5][0], 16);
        }
      }
      bvReg = -1;
      vu1gen::storeLanes(st.vf[3], urv, 0xFu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[3] = rt;
        _mm_store_si128((__m128i *)cx.vfR[3], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L0C58:;
    { // pair 395 pc=0xC58 up=0x0180683C lo=0x81ED3B3C
      c = vu1gen::vmax(c, cx.vfR[13][0]);
      c = vu1gen::vmax(c, cx.vfR[13][1]);
      c = vu1gen::vmax(c, cx.vfRAny[7]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[13]);
        const __m128 bv = _mm_set1_ps(0.0f);
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
        vu1gen::storeLanes(st.acc, rvn, 0xCu);
      }
      {
        const float mv0 = st.vf[7][0];
        const float mv1 = st.vf[7][1];
        const float mv2 = st.vf[7][2];
        const float mv3 = st.vf[7][3];
        st.vf[13][0] = mv0;
        st.vf[13][1] = mv1;
        st.vf[13][2] = mv2;
        st.vf[13][3] = mv3;
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[13] = rt;
        _mm_store_si128((__m128i *)cx.vfR[13], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L0C60:;
    { // pair 396 pc=0xC60 up=0x018010A1 lo=0x03C727FB
      c = vu1gen::vmax(c, cx.vfR[2][0]);
      c = vu1gen::vmax(c, cx.vfR[2][1]);
      c = vu1gen::vmax(c, cx.vfR[4][0]);
      c = vu1gen::vmax(c, cx.vfR[4][1]);
      c = vu1gen::vmax(c, cx.vfR[4][2]);
      c = vu1gen::vmax(c, cx.viR[7]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      cx.commitQ(c);
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[2]);
        const __m128 bv = _mm_set1_ps(vu1gen::nrm(st.q));
        const __m128 av = vu1gen::nrm4(st.acc);
        const __m128 product = _mm_mul_ps(vsv, bv);
        const __m128 rv = _mm_add_ps(av, product);
        uint32_t mac = 0u, stf = 0u, stk = 0u;
        __m128 rvn = rv;
        { uint32_t sgn; uint32_t plain = vu1gen::classify4(rv, sgn);
          const __m128i pm = _mm_and_si128(_mm_castps_si128(product), _mm_set1_epi32(0x7FFFFFFF));
          plain &= ~uint32_t(_mm_movemask_ps(_mm_castsi128_ps(_mm_cmpgt_epi32(pm, _mm_set1_epi32(0x7F7FFFFE)))));
          if ((plain & 0x3u) == 0x3u) {
            mac = vu1gen::kMacSign.word[sgn & 0x3u];
            stf = (sgn & 0x3u) != 0u ? 0x2u : 0u;
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
            rvn = _mm_loadu_ps(rr);
          } }
        if (cx.sticky) stk = vu1gen::sticky4(vsv, bv, product, 0x3u);
        cx.pushFmac(c, mac, stf, stk);
        urv = rvn;
      }
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[7] + -5) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[4][0], 12);
        }
      }
      bvReg = -1;
      vu1gen::storeLanes(st.vf[2], urv, 0xCu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[2] = rt;
        cx.vfR[2][0] = rt;
        cx.vfR[2][1] = rt;
      }
      c += 1u;
    }
    L0C68:;
    { // pair 397 pc=0xC68 up=0x01E0603C lo=0x81EC333C
      c = vu1gen::vmax(c, cx.vfRAny[12]);
      c = vu1gen::vmax(c, cx.vfRAny[6]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[12]);
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
        vu1gen::storeLanes(st.acc, rvn, 0xFu);
      }
      {
        const float mv0 = st.vf[6][0];
        const float mv1 = st.vf[6][1];
        const float mv2 = st.vf[6][2];
        const float mv3 = st.vf[6][3];
        st.vf[12][0] = mv0;
        st.vf[12][1] = mv1;
        st.vf[12][2] = mv2;
        st.vf[12][3] = mv3;
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[12] = rt;
        _mm_store_si128((__m128i *)cx.vfR[12], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L0C70:;
    { // pair 398 pc=0xC70 up=0x01E00861 lo=0x03E71FFC
      c = vu1gen::vmax(c, cx.vfRAny[1]);
      c = vu1gen::vmax(c, cx.vfRAny[3]);
      c = vu1gen::vmax(c, cx.viR[7]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      cx.commitQ(c);
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[1]);
        const __m128 bv = _mm_set1_ps(vu1gen::nrm(st.q));
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
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[7] + -4) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[3][0], 16);
        }
      }
      bvReg = -1;
      vu1gen::storeLanes(st.vf[1], urv, 0xFu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[1] = rt;
        _mm_store_si128((__m128i *)cx.vfR[1], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L0C78:;
    { // pair 399 pc=0xC78 up=0x01C05C40 lo=0x10063005
      c = vu1gen::vmax(c, cx.vfR[11][0]);
      c = vu1gen::vmax(c, cx.vfR[11][1]);
      c = vu1gen::vmax(c, cx.vfR[11][2]);
      c = vu1gen::vmax(c, cx.viR[6]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[11]);
        const __m128 bv = _mm_set1_ps(0.0f);
        const __m128 rv = _mm_add_ps(vsv, bv);
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
            rvn = _mm_loadu_ps(rr);
          } }
        cx.pushFmac(c, mac, stf, stk);
        urv = rvn;
      }
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[6] + 5); bvOld = st.vi[6]; bvReg = 6; st.vi[6] = nv; }
      }
      vu1gen::storeLanes(st.vf[17], urv, 0xEu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[17] = rt;
        cx.vfR[17][0] = rt;
        cx.vfR[17][1] = rt;
        cx.vfR[17][2] = rt;
      }
      cx.viR[6] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L0C80:;
    { // pair 400 pc=0xC80 up=0x01E05400 lo=0x03C717FE
      c = vu1gen::vmax(c, cx.vfRAny[10]);
      c = vu1gen::vmax(c, cx.vfR[2][0]);
      c = vu1gen::vmax(c, cx.vfR[2][1]);
      c = vu1gen::vmax(c, cx.vfR[2][2]);
      c = vu1gen::vmax(c, cx.viR[7]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[10]);
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
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[7] + -2) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[2][0], 12);
        }
      }
      bvReg = -1;
      vu1gen::storeLanes(st.vf[16], urv, 0xFu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[16] = rt;
        _mm_store_si128((__m128i *)cx.vfR[16], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L0C88:;
    { const bool bt = (int16_t)(bvReg == 4 ? bvOld : st.vi[4]) > 0;
    { // pair 401 pc=0xC88 up=0x01E04BC0 lo=0x5A0027DA
      c = vu1gen::vmax(c, cx.vfRAny[9]);
      c = vu1gen::vmax(c, cx.viR[4]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[9]);
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
      bvReg = -1;
      vu1gen::storeLanes(st.vf[15], urv, 0xFu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[15] = rt;
        _mm_store_si128((__m128i *)cx.vfR[15], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    { // pair 402 pc=0xC90 up=0x01E04380 lo=0x03E70FFF
      c = vu1gen::vmax(c, cx.vfRAny[8]);
      c = vu1gen::vmax(c, cx.vfRAny[1]);
      c = vu1gen::vmax(c, cx.viR[7]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[8]);
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
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[7] + -1) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[1][0], 16);
        }
      }
      bvReg = -1;
      vu1gen::storeLanes(st.vf[14], urv, 0xFu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[14] = rt;
        _mm_store_si128((__m128i *)cx.vfR[14], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    if (bt) {
      st.branchTarget = 0xB60u;
      if (c >= (uint64_t)a.maxCycles) { st.pc = 0xB60u; goto BUDGET_OUT; }
      goto L0B60;
    } }
    goto LC0C98;
    L0C90:;
    { // pair 402 pc=0xC90 up=0x01E04380 lo=0x03E70FFF
      c = vu1gen::vmax(c, cx.vfRAny[8]);
      c = vu1gen::vmax(c, cx.vfRAny[1]);
      c = vu1gen::vmax(c, cx.viR[7]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[8]);
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
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[7] + -1) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[1][0], 16);
        }
      }
      bvReg = -1;
      vu1gen::storeLanes(st.vf[14], urv, 0xFu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[14] = rt;
        _mm_store_si128((__m128i *)cx.vfR[14], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    LC0C98:;
    L0C98:;
    { const bool bt = (int16_t)(bvReg == 4 ? bvOld : st.vi[4]) < 0;
    { // pair 403 pc=0xC98 up=0x000002FF lo=0x5800202E
      c = vu1gen::vmax(c, cx.viR[4]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    { // pair 404 pc=0xCA0 up=0x000002FF lo=0x088503D2
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 978) * 16u) & 0x3FFFu;
          uint32_t v = 0u; std::memcpy(&v, vm + addr + 4u, 4);
          st.vi[5] = (int32_t)(int16_t)(v & 0xFFFFu);
        }
      }
      bvReg = -1;
      cx.viR[5] = (uint32_t)(c + 4u);
      c += 1u;
    }
    if (bt) {
      st.branchTarget = 0xE10u;
      goto L0E10;
    } }
    goto LC0CA8;
    L0CA0:;
    { // pair 404 pc=0xCA0 up=0x000002FF lo=0x088503D2
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 978) * 16u) & 0x3FFFu;
          uint32_t v = 0u; std::memcpy(&v, vm + addr + 4u, 4);
          st.vi[5] = (int32_t)(int16_t)(v & 0xFFFFu);
        }
      }
      bvReg = -1;
      cx.viR[5] = (uint32_t)(c + 4u);
      c += 1u;
    }
    LC0CA8:;
    L0CA8:;
    st.branchTarget = 0xB60u;
    { // pair 405 pc=0xCA8 up=0x000002FF lo=0x400007D6
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    { // pair 406 pc=0xCB0 up=0x000002FF lo=0x082603D1
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 977) * 16u) & 0x3FFFu;
          uint32_t v = 0u; std::memcpy(&v, vm + addr + 12u, 4);
          st.vi[6] = (int32_t)(int16_t)(v & 0xFFFFu);
        }
      }
      bvReg = -1;
      cx.viR[6] = (uint32_t)(c + 4u);
      c += 1u;
    }
    if (c >= (uint64_t)a.maxCycles) { st.pc = 0xB60u; goto BUDGET_OUT; }
    goto L0B60;
    L0CB0:;
    { // pair 406 pc=0xCB0 up=0x000002FF lo=0x082603D1
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 977) * 16u) & 0x3FFFu;
          uint32_t v = 0u; std::memcpy(&v, vm + addr + 12u, 4);
          st.vi[6] = (int32_t)(int16_t)(v & 0xFFFFu);
        }
      }
      bvReg = -1;
      cx.viR[6] = (uint32_t)(c + 4u);
      c += 1u;
    }
    L0CB8:;
    { // pair 407 pc=0xCB8 up=0x0051586C lo=0x8025033C
      c = vu1gen::vmax(c, cx.vfR[11][2]);
      c = vu1gen::vmax(c, cx.vfR[17][2]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[11]);
        const __m128 bv = vu1gen::nrm4(st.vf[17]);
        const __m128 rv = _mm_sub_ps(vsv, bv);
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
                lf = vu1gen::normExactLane(rr[2], (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(2, 2, 2, 2))) - (double)_mm_cvtss_f32(_mm_shuffle_ps(bv, bv, _MM_SHUFFLE(2, 2, 2, 2))));
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
        const float mv3 = st.vf[0][3];
        st.vf[5][3] = mv3;
      }
      bvReg = -1;
      vu1gen::storeLanes(st.vf[1], urv, 0x2u);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[1] = rt;
        cx.vfR[1][2] = rt;
      }
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[5] = rt;
        cx.vfR[5][3] = rt;
      }
      c += 1u;
    }
    L0CC0:;
    { // pair 408 pc=0xCC0 up=0x01CA816C lo=0x00440390
      c = vu1gen::vmax(c, cx.vfR[16][0]);
      c = vu1gen::vmax(c, cx.vfR[16][1]);
      c = vu1gen::vmax(c, cx.vfR[16][2]);
      c = vu1gen::vmax(c, cx.vfR[10][0]);
      c = vu1gen::vmax(c, cx.vfR[10][1]);
      c = vu1gen::vmax(c, cx.vfR[10][2]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[16]);
        const __m128 bv = vu1gen::nrm4(st.vf[10]);
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
        urv = rvn;
      }
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 912) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[4][2], vm + addr + 8u, 4);
        }
      }
      bvReg = -1;
      vu1gen::storeLanes(st.vf[5], urv, 0xEu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[5] = rt;
        cx.vfR[5][0] = rt;
        cx.vfR[5][1] = rt;
        cx.vfR[5][2] = rt;
      }
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[4] = rt;
        cx.vfR[4][2] = rt;
      }
      c += 1u;
    }
    L0CC8:;
    { // pair 409 pc=0xCC8 up=0x0189792C lo=0x00420390
      c = vu1gen::vmax(c, cx.vfR[15][0]);
      c = vu1gen::vmax(c, cx.vfR[15][1]);
      c = vu1gen::vmax(c, cx.vfR[9][0]);
      c = vu1gen::vmax(c, cx.vfR[9][1]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[15]);
        const __m128 bv = vu1gen::nrm4(st.vf[9]);
        const __m128 rv = _mm_sub_ps(vsv, bv);
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
            rvn = _mm_loadu_ps(rr);
          } }
        cx.pushFmac(c, mac, stf, stk);
        urv = rvn;
      }
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 912) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[2][2], vm + addr + 8u, 4);
        }
      }
      bvReg = -1;
      vu1gen::storeLanes(st.vf[4], urv, 0xCu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[4] = rt;
        cx.vfR[4][0] = rt;
        cx.vfR[4][1] = rt;
      }
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[2] = rt;
        cx.vfR[2][2] = rt;
      }
      c += 1u;
    }
    L0CD0:;
    { // pair 410 pc=0xCD0 up=0x01E870EC lo=0x10021002
      c = vu1gen::vmax(c, cx.vfRAny[14]);
      c = vu1gen::vmax(c, cx.vfRAny[8]);
      c = vu1gen::vmax(c, cx.viR[2]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[14]);
        const __m128 bv = vu1gen::nrm4(st.vf[8]);
        const __m128 rv = _mm_sub_ps(vsv, bv);
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
            { uint8_t lf;
              if (plain & 8u) lf = ((sgn >> 3) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[3], (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(3, 3, 3, 3))) - (double)_mm_cvtss_f32(_mm_shuffle_ps(bv, bv, _MM_SHUFFLE(3, 3, 3, 3))));
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
        { const int32_t nv = (int32_t)(int16_t)(st.vi[2] + 2); bvOld = st.vi[2]; bvReg = 2; st.vi[2] = nv; }
      }
      vu1gen::storeLanes(st.vf[3], urv, 0xFu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[3] = rt;
        _mm_store_si128((__m128i *)cx.vfR[3], _mm_set1_epi32((int)rt));
      }
      cx.viR[2] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L0CD8:;
    { // pair 411 pc=0xCD8 up=0x018768AC lo=0x81415BBC
      c = vu1gen::vmax(c, cx.vfR[13][0]);
      c = vu1gen::vmax(c, cx.vfR[13][1]);
      c = vu1gen::vmax(c, cx.vfR[7][0]);
      c = vu1gen::vmax(c, cx.vfR[7][1]);
      c = vu1gen::vmax(c, cx.vfR[11][2]);
      c = vu1gen::vmax(c, cx.vfR[1][2]);
      if (cx.qValid) c = vu1gen::vmax(c, cx.qReady);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[13]);
        const __m128 bv = vu1gen::nrm4(st.vf[7]);
        const __m128 rv = _mm_sub_ps(vsv, bv);
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
            rvn = _mm_loadu_ps(rr);
          } }
        cx.pushFmac(c, mac, stf, stk);
        urv = rvn;
      }
      {
        cx.commitQ(c);
        { const float num = vu1gen::nrm(st.vf[11][2]);
          const float den = vu1gen::nrm(st.vf[1][2]);
          uint32_t di = 0u; float r;
          if (den == 0.0f) { di = (num == 0.0f) ? 0x10u : 0x20u;
            r = (std::signbit(num) != std::signbit(den)) ? -std::numeric_limits<float>::max() : std::numeric_limits<float>::max(); }
          else r = num / den;
          uint32_t ig; r = vu1gen::normResult(r, ig);
          cx.qValid = true; cx.qReady = c + 7u; cx.qVal = r; cx.qDi = di; }
      }
      bvReg = -1;
      vu1gen::storeLanes(st.vf[2], urv, 0xCu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[2] = rt;
        cx.vfR[2][0] = rt;
        cx.vfR[2][1] = rt;
      }
      c += 1u;
    }
    L0CE0:;
    { // pair 412 pc=0xCE0 up=0x01E6606C lo=0x1007380A
      c = vu1gen::vmax(c, cx.vfRAny[12]);
      c = vu1gen::vmax(c, cx.vfRAny[6]);
      c = vu1gen::vmax(c, cx.viR[7]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[12]);
        const __m128 bv = vu1gen::nrm4(st.vf[6]);
        const __m128 rv = _mm_sub_ps(vsv, bv);
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
            { uint8_t lf;
              if (plain & 8u) lf = ((sgn >> 3) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[3], (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(3, 3, 3, 3))) - (double)_mm_cvtss_f32(_mm_shuffle_ps(bv, bv, _MM_SHUFFLE(3, 3, 3, 3))));
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
        { const int32_t nv = (int32_t)(int16_t)(st.vi[7] + 10); bvOld = st.vi[7]; bvReg = 7; st.vi[7] = nv; }
      }
      vu1gen::storeLanes(st.vf[1], urv, 0xFu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[1] = rt;
        _mm_store_si128((__m128i *)cx.vfR[1], _mm_set1_epi32((int)rt));
      }
      cx.viR[7] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L0CE8:;
    { // pair 413 pc=0xCE8 up=0x000002FF lo=0x03E757FD
      c = vu1gen::vmax(c, cx.vfRAny[10]);
      c = vu1gen::vmax(c, cx.viR[7]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[7] + -3) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[10][0], 16);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L0CF0:;
    { // pair 414 pc=0xCF0 up=0x000002FF lo=0x03C74FFB
      c = vu1gen::vmax(c, cx.vfR[9][0]);
      c = vu1gen::vmax(c, cx.vfR[9][1]);
      c = vu1gen::vmax(c, cx.vfR[9][2]);
      c = vu1gen::vmax(c, cx.viR[7]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[7] + -5) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[9][0], 12);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L0CF8:;
    { // pair 415 pc=0xCF8 up=0x000002FF lo=0x03E747FC
      c = vu1gen::vmax(c, cx.vfRAny[8]);
      c = vu1gen::vmax(c, cx.viR[7]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[7] + -4) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[8][0], 16);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L0D00:;
    { // pair 416 pc=0xD00 up=0x000002FF lo=0x03C73FFE
      c = vu1gen::vmax(c, cx.vfR[7][0]);
      c = vu1gen::vmax(c, cx.vfR[7][1]);
      c = vu1gen::vmax(c, cx.vfR[7][2]);
      c = vu1gen::vmax(c, cx.viR[7]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[7] + -2) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[7][0], 12);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L0D08:;
    { // pair 417 pc=0xD08 up=0x01C0503C lo=0x03E737FF
      c = vu1gen::vmax(c, cx.vfR[10][0]);
      c = vu1gen::vmax(c, cx.vfR[10][1]);
      c = vu1gen::vmax(c, cx.vfR[10][2]);
      c = vu1gen::vmax(c, cx.vfRAny[6]);
      c = vu1gen::vmax(c, cx.viR[7]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[10]);
        const __m128 bv = _mm_set1_ps(0.0f);
        const __m128 rv = _mm_add_ps(vsv, bv);
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
            rvn = _mm_loadu_ps(rr);
          } }
        cx.pushFmac(c, mac, stf, stk);
        vu1gen::storeLanes(st.acc, rvn, 0xEu);
      }
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[7] + -1) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[6][0], 16);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L0D10:;
    { // pair 418 pc=0xD10 up=0x01C02961 lo=0x8000033C
      c = vu1gen::vmax(c, cx.vfR[5][0]);
      c = vu1gen::vmax(c, cx.vfR[5][1]);
      c = vu1gen::vmax(c, cx.vfR[5][2]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      cx.commitQ(c);
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[5]);
        const __m128 bv = _mm_set1_ps(vu1gen::nrm(st.q));
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
      vu1gen::storeLanes(st.vf[5], urv, 0xEu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[5] = rt;
        cx.vfR[5][0] = rt;
        cx.vfR[5][1] = rt;
        cx.vfR[5][2] = rt;
      }
      c += 1u;
    }
    L0D18:;
    { // pair 419 pc=0xD18 up=0x0180483C lo=0x8000033C
      c = vu1gen::vmax(c, cx.vfR[9][0]);
      c = vu1gen::vmax(c, cx.vfR[9][1]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[9]);
        const __m128 bv = _mm_set1_ps(0.0f);
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
        vu1gen::storeLanes(st.acc, rvn, 0xCu);
      }
      bvReg = -1;
      c += 1u;
    }
    L0D20:;
    { // pair 420 pc=0xD20 up=0x01802121 lo=0x8000033C
      c = vu1gen::vmax(c, cx.vfR[4][0]);
      c = vu1gen::vmax(c, cx.vfR[4][1]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      cx.commitQ(c);
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[4]);
        const __m128 bv = _mm_set1_ps(vu1gen::nrm(st.q));
        const __m128 av = vu1gen::nrm4(st.acc);
        const __m128 product = _mm_mul_ps(vsv, bv);
        const __m128 rv = _mm_add_ps(av, product);
        uint32_t mac = 0u, stf = 0u, stk = 0u;
        __m128 rvn = rv;
        { uint32_t sgn; uint32_t plain = vu1gen::classify4(rv, sgn);
          const __m128i pm = _mm_and_si128(_mm_castps_si128(product), _mm_set1_epi32(0x7FFFFFFF));
          plain &= ~uint32_t(_mm_movemask_ps(_mm_castsi128_ps(_mm_cmpgt_epi32(pm, _mm_set1_epi32(0x7F7FFFFE)))));
          if ((plain & 0x3u) == 0x3u) {
            mac = vu1gen::kMacSign.word[sgn & 0x3u];
            stf = (sgn & 0x3u) != 0u ? 0x2u : 0u;
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
            rvn = _mm_loadu_ps(rr);
          } }
        if (cx.sticky) stk = vu1gen::sticky4(vsv, bv, product, 0x3u);
        cx.pushFmac(c, mac, stf, stk);
        urv = rvn;
      }
      bvReg = -1;
      vu1gen::storeLanes(st.vf[4], urv, 0xCu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[4] = rt;
        cx.vfR[4][0] = rt;
        cx.vfR[4][1] = rt;
      }
      c += 1u;
    }
    L0D28:;
    { // pair 421 pc=0xD28 up=0x01E0403C lo=0x8000033C
      c = vu1gen::vmax(c, cx.vfRAny[8]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[8]);
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
        vu1gen::storeLanes(st.acc, rvn, 0xFu);
      }
      bvReg = -1;
      c += 1u;
    }
    L0D30:;
    { // pair 422 pc=0xD30 up=0x01E018E1 lo=0x03E72FF8
      c = vu1gen::vmax(c, cx.vfRAny[3]);
      c = vu1gen::vmax(c, cx.vfRAny[5]);
      c = vu1gen::vmax(c, cx.viR[7]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      cx.commitQ(c);
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[3]);
        const __m128 bv = _mm_set1_ps(vu1gen::nrm(st.q));
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
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[7] + -8) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[5][0], 16);
        }
      }
      bvReg = -1;
      vu1gen::storeLanes(st.vf[3], urv, 0xFu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[3] = rt;
        _mm_store_si128((__m128i *)cx.vfR[3], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L0D38:;
    { // pair 423 pc=0xD38 up=0x0180383C lo=0x81ED3B3C
      c = vu1gen::vmax(c, cx.vfR[7][0]);
      c = vu1gen::vmax(c, cx.vfR[7][1]);
      c = vu1gen::vmax(c, cx.vfRAny[7]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[7]);
        const __m128 bv = _mm_set1_ps(0.0f);
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
        vu1gen::storeLanes(st.acc, rvn, 0xCu);
      }
      {
        const float mv0 = st.vf[7][0];
        const float mv1 = st.vf[7][1];
        const float mv2 = st.vf[7][2];
        const float mv3 = st.vf[7][3];
        st.vf[13][0] = mv0;
        st.vf[13][1] = mv1;
        st.vf[13][2] = mv2;
        st.vf[13][3] = mv3;
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[13] = rt;
        _mm_store_si128((__m128i *)cx.vfR[13], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L0D40:;
    { // pair 424 pc=0xD40 up=0x018010A1 lo=0x03C727F6
      c = vu1gen::vmax(c, cx.vfR[2][0]);
      c = vu1gen::vmax(c, cx.vfR[2][1]);
      c = vu1gen::vmax(c, cx.vfR[4][0]);
      c = vu1gen::vmax(c, cx.vfR[4][1]);
      c = vu1gen::vmax(c, cx.vfR[4][2]);
      c = vu1gen::vmax(c, cx.viR[7]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      cx.commitQ(c);
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[2]);
        const __m128 bv = _mm_set1_ps(vu1gen::nrm(st.q));
        const __m128 av = vu1gen::nrm4(st.acc);
        const __m128 product = _mm_mul_ps(vsv, bv);
        const __m128 rv = _mm_add_ps(av, product);
        uint32_t mac = 0u, stf = 0u, stk = 0u;
        __m128 rvn = rv;
        { uint32_t sgn; uint32_t plain = vu1gen::classify4(rv, sgn);
          const __m128i pm = _mm_and_si128(_mm_castps_si128(product), _mm_set1_epi32(0x7FFFFFFF));
          plain &= ~uint32_t(_mm_movemask_ps(_mm_castsi128_ps(_mm_cmpgt_epi32(pm, _mm_set1_epi32(0x7F7FFFFE)))));
          if ((plain & 0x3u) == 0x3u) {
            mac = vu1gen::kMacSign.word[sgn & 0x3u];
            stf = (sgn & 0x3u) != 0u ? 0x2u : 0u;
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
            rvn = _mm_loadu_ps(rr);
          } }
        if (cx.sticky) stk = vu1gen::sticky4(vsv, bv, product, 0x3u);
        cx.pushFmac(c, mac, stf, stk);
        urv = rvn;
      }
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[7] + -10) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[4][0], 12);
        }
      }
      bvReg = -1;
      vu1gen::storeLanes(st.vf[2], urv, 0xCu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[2] = rt;
        cx.vfR[2][0] = rt;
        cx.vfR[2][1] = rt;
      }
      c += 1u;
    }
    L0D48:;
    { // pair 425 pc=0xD48 up=0x01E0303C lo=0x81EC333C
      c = vu1gen::vmax(c, cx.vfRAny[6]);
      c = vu1gen::vmax(c, cx.vfRAny[6]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[6]);
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
        vu1gen::storeLanes(st.acc, rvn, 0xFu);
      }
      {
        const float mv0 = st.vf[6][0];
        const float mv1 = st.vf[6][1];
        const float mv2 = st.vf[6][2];
        const float mv3 = st.vf[6][3];
        st.vf[12][0] = mv0;
        st.vf[12][1] = mv1;
        st.vf[12][2] = mv2;
        st.vf[12][3] = mv3;
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[12] = rt;
        _mm_store_si128((__m128i *)cx.vfR[12], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L0D50:;
    { // pair 426 pc=0xD50 up=0x01E00861 lo=0x03E71FF7
      c = vu1gen::vmax(c, cx.vfRAny[1]);
      c = vu1gen::vmax(c, cx.vfRAny[3]);
      c = vu1gen::vmax(c, cx.viR[7]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      cx.commitQ(c);
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[1]);
        const __m128 bv = _mm_set1_ps(vu1gen::nrm(st.q));
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
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[7] + -9) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[3][0], 16);
        }
      }
      bvReg = -1;
      vu1gen::storeLanes(st.vf[1], urv, 0xFu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[1] = rt;
        _mm_store_si128((__m128i *)cx.vfR[1], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L0D58:;
    { // pair 427 pc=0xD58 up=0x01C05C40 lo=0x10063005
      c = vu1gen::vmax(c, cx.vfR[11][0]);
      c = vu1gen::vmax(c, cx.vfR[11][1]);
      c = vu1gen::vmax(c, cx.vfR[11][2]);
      c = vu1gen::vmax(c, cx.viR[6]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[11]);
        const __m128 bv = _mm_set1_ps(0.0f);
        const __m128 rv = _mm_add_ps(vsv, bv);
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
            rvn = _mm_loadu_ps(rr);
          } }
        cx.pushFmac(c, mac, stf, stk);
        urv = rvn;
      }
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[6] + 5); bvOld = st.vi[6]; bvReg = 6; st.vi[6] = nv; }
      }
      vu1gen::storeLanes(st.vf[17], urv, 0xEu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[17] = rt;
        cx.vfR[17][0] = rt;
        cx.vfR[17][1] = rt;
        cx.vfR[17][2] = rt;
      }
      cx.viR[6] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L0D60:;
    { // pair 428 pc=0xD60 up=0x01E05400 lo=0x03C717F9
      c = vu1gen::vmax(c, cx.vfRAny[10]);
      c = vu1gen::vmax(c, cx.vfR[2][0]);
      c = vu1gen::vmax(c, cx.vfR[2][1]);
      c = vu1gen::vmax(c, cx.vfR[2][2]);
      c = vu1gen::vmax(c, cx.viR[7]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[10]);
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
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[7] + -7) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[2][0], 12);
        }
      }
      bvReg = -1;
      vu1gen::storeLanes(st.vf[16], urv, 0xFu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[16] = rt;
        _mm_store_si128((__m128i *)cx.vfR[16], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L0D68:;
    { const bool bt = (int16_t)(bvReg == 4 ? bvOld : st.vi[4]) > 0;
    { // pair 429 pc=0xD68 up=0x01E04BC0 lo=0x5A0027BE
      c = vu1gen::vmax(c, cx.vfRAny[9]);
      c = vu1gen::vmax(c, cx.viR[4]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[9]);
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
      bvReg = -1;
      vu1gen::storeLanes(st.vf[15], urv, 0xFu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[15] = rt;
        _mm_store_si128((__m128i *)cx.vfR[15], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    { // pair 430 pc=0xD70 up=0x01E04380 lo=0x03E70FFA
      c = vu1gen::vmax(c, cx.vfRAny[8]);
      c = vu1gen::vmax(c, cx.vfRAny[1]);
      c = vu1gen::vmax(c, cx.viR[7]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[8]);
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
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[7] + -6) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[1][0], 16);
        }
      }
      bvReg = -1;
      vu1gen::storeLanes(st.vf[14], urv, 0xFu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[14] = rt;
        _mm_store_si128((__m128i *)cx.vfR[14], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    if (bt) {
      st.branchTarget = 0xB60u;
      if (c >= (uint64_t)a.maxCycles) { st.pc = 0xB60u; goto BUDGET_OUT; }
      goto L0B60;
    } }
    goto LC0D78;
    L0D70:;
    { // pair 430 pc=0xD70 up=0x01E04380 lo=0x03E70FFA
      c = vu1gen::vmax(c, cx.vfRAny[8]);
      c = vu1gen::vmax(c, cx.vfRAny[1]);
      c = vu1gen::vmax(c, cx.viR[7]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[8]);
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
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[7] + -6) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[1][0], 16);
        }
      }
      bvReg = -1;
      vu1gen::storeLanes(st.vf[14], urv, 0xFu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[14] = rt;
        _mm_store_si128((__m128i *)cx.vfR[14], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    LC0D78:;
    L0D78:;
    { const bool bt = (int16_t)(bvReg == 4 ? bvOld : st.vi[4]) < 0;
    { // pair 431 pc=0xD78 up=0x000002FF lo=0x58002012
      c = vu1gen::vmax(c, cx.viR[4]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    { // pair 432 pc=0xD80 up=0x000002FF lo=0x088503D2
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 978) * 16u) & 0x3FFFu;
          uint32_t v = 0u; std::memcpy(&v, vm + addr + 4u, 4);
          st.vi[5] = (int32_t)(int16_t)(v & 0xFFFFu);
        }
      }
      bvReg = -1;
      cx.viR[5] = (uint32_t)(c + 4u);
      c += 1u;
    }
    if (bt) {
      st.branchTarget = 0xE10u;
      goto L0E10;
    } }
    goto LC0D88;
    L0D80:;
    { // pair 432 pc=0xD80 up=0x000002FF lo=0x088503D2
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 978) * 16u) & 0x3FFFu;
          uint32_t v = 0u; std::memcpy(&v, vm + addr + 4u, 4);
          st.vi[5] = (int32_t)(int16_t)(v & 0xFFFFu);
        }
      }
      bvReg = -1;
      cx.viR[5] = (uint32_t)(c + 4u);
      c += 1u;
    }
    LC0D88:;
    L0D88:;
    st.branchTarget = 0xB60u;
    { // pair 433 pc=0xD88 up=0x000002FF lo=0x400007BA
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    { // pair 434 pc=0xD90 up=0x000002FF lo=0x082603D1
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 977) * 16u) & 0x3FFFu;
          uint32_t v = 0u; std::memcpy(&v, vm + addr + 12u, 4);
          st.vi[6] = (int32_t)(int16_t)(v & 0xFFFFu);
        }
      }
      bvReg = -1;
      cx.viR[6] = (uint32_t)(c + 4u);
      c += 1u;
    }
    if (c >= (uint64_t)a.maxCycles) { st.pc = 0xB60u; goto BUDGET_OUT; }
    goto L0B60;
    L0D90:;
    { // pair 434 pc=0xD90 up=0x000002FF lo=0x082603D1
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 977) * 16u) & 0x3FFFu;
          uint32_t v = 0u; std::memcpy(&v, vm + addr + 12u, 4);
          st.vi[6] = (int32_t)(int16_t)(v & 0xFFFFu);
        }
      }
      bvReg = -1;
      cx.viR[6] = (uint32_t)(c + 4u);
      c += 1u;
    }
    L0D98:;
    { // pair 435 pc=0xD98 up=0x000002FF lo=0x03E75002
      c = vu1gen::vmax(c, cx.vfRAny[10]);
      c = vu1gen::vmax(c, cx.viR[7]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[7] + 2) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[10][0], 16);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L0DA0:;
    { // pair 436 pc=0xDA0 up=0x000002FF lo=0x03C74800
      c = vu1gen::vmax(c, cx.vfR[9][0]);
      c = vu1gen::vmax(c, cx.vfR[9][1]);
      c = vu1gen::vmax(c, cx.vfR[9][2]);
      c = vu1gen::vmax(c, cx.viR[7]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[7] + 0) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[9][0], 12);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L0DA8:;
    { // pair 437 pc=0xDA8 up=0x000002FF lo=0x03E74001
      c = vu1gen::vmax(c, cx.vfRAny[8]);
      c = vu1gen::vmax(c, cx.viR[7]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[7] + 1) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[8][0], 16);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L0DB0:;
    { // pair 438 pc=0xDB0 up=0x000002FF lo=0x03C73803
      c = vu1gen::vmax(c, cx.vfR[7][0]);
      c = vu1gen::vmax(c, cx.vfR[7][1]);
      c = vu1gen::vmax(c, cx.vfR[7][2]);
      c = vu1gen::vmax(c, cx.viR[7]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[7] + 3) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[7][0], 12);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L0DB8:;
    { // pair 439 pc=0xDB8 up=0x000002FF lo=0x03E73004
      c = vu1gen::vmax(c, cx.vfRAny[6]);
      c = vu1gen::vmax(c, cx.viR[7]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[7] + 4) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[6][0], 16);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L0DC0:;
    { // pair 440 pc=0xDC0 up=0x000002FF lo=0x10021001
      c = vu1gen::vmax(c, cx.viR[2]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[2] + 1); bvOld = st.vi[2]; bvReg = 2; st.vi[2] = nv; }
      }
      cx.viR[2] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L0DC8:;
    { // pair 441 pc=0xDC8 up=0x000002FF lo=0x10073805
      c = vu1gen::vmax(c, cx.viR[7]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[7] + 5); bvOld = st.vi[7]; bvReg = 7; st.vi[7] = nv; }
      }
      cx.viR[7] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L0DD0:;
    { // pair 442 pc=0xDD0 up=0x01C05C40 lo=0x81ED3B3C
      c = vu1gen::vmax(c, cx.vfR[11][0]);
      c = vu1gen::vmax(c, cx.vfR[11][1]);
      c = vu1gen::vmax(c, cx.vfR[11][2]);
      c = vu1gen::vmax(c, cx.vfRAny[7]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[11]);
        const __m128 bv = _mm_set1_ps(0.0f);
        const __m128 rv = _mm_add_ps(vsv, bv);
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
            rvn = _mm_loadu_ps(rr);
          } }
        cx.pushFmac(c, mac, stf, stk);
        urv = rvn;
      }
      {
        const float mv0 = st.vf[7][0];
        const float mv1 = st.vf[7][1];
        const float mv2 = st.vf[7][2];
        const float mv3 = st.vf[7][3];
        st.vf[13][0] = mv0;
        st.vf[13][1] = mv1;
        st.vf[13][2] = mv2;
        st.vf[13][3] = mv3;
      }
      bvReg = -1;
      vu1gen::storeLanes(st.vf[17], urv, 0xEu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[17] = rt;
        cx.vfR[17][0] = rt;
        cx.vfR[17][1] = rt;
        cx.vfR[17][2] = rt;
      }
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[13] = rt;
        _mm_store_si128((__m128i *)cx.vfR[13], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L0DD8:;
    { // pair 443 pc=0xDD8 up=0x01E05400 lo=0x81EC333C
      c = vu1gen::vmax(c, cx.vfRAny[10]);
      c = vu1gen::vmax(c, cx.vfRAny[6]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[10]);
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
        const float mv0 = st.vf[6][0];
        const float mv1 = st.vf[6][1];
        const float mv2 = st.vf[6][2];
        const float mv3 = st.vf[6][3];
        st.vf[12][0] = mv0;
        st.vf[12][1] = mv1;
        st.vf[12][2] = mv2;
        st.vf[12][3] = mv3;
      }
      bvReg = -1;
      vu1gen::storeLanes(st.vf[16], urv, 0xFu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[16] = rt;
        _mm_store_si128((__m128i *)cx.vfR[16], _mm_set1_epi32((int)rt));
      }
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[12] = rt;
        _mm_store_si128((__m128i *)cx.vfR[12], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L0DE0:;
    { const bool bt = (int16_t)(bvReg == 4 ? bvOld : st.vi[4]) > 0;
    { // pair 444 pc=0xDE0 up=0x01E04BC0 lo=0x5A0027AF
      c = vu1gen::vmax(c, cx.vfRAny[9]);
      c = vu1gen::vmax(c, cx.viR[4]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[9]);
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
      bvReg = -1;
      vu1gen::storeLanes(st.vf[15], urv, 0xFu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[15] = rt;
        _mm_store_si128((__m128i *)cx.vfR[15], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    { // pair 445 pc=0xDE8 up=0x01E04380 lo=0x10063005
      c = vu1gen::vmax(c, cx.vfRAny[8]);
      c = vu1gen::vmax(c, cx.viR[6]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[8]);
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
        { const int32_t nv = (int32_t)(int16_t)(st.vi[6] + 5); bvOld = st.vi[6]; bvReg = 6; st.vi[6] = nv; }
      }
      vu1gen::storeLanes(st.vf[14], urv, 0xFu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[14] = rt;
        _mm_store_si128((__m128i *)cx.vfR[14], _mm_set1_epi32((int)rt));
      }
      cx.viR[6] = (uint32_t)(c + 1u);
      c += 1u;
    }
    if (bt) {
      st.branchTarget = 0xB60u;
      if (c >= (uint64_t)a.maxCycles) { st.pc = 0xB60u; goto BUDGET_OUT; }
      goto L0B60;
    } }
    goto LC0DF0;
    L0DE8:;
    { // pair 445 pc=0xDE8 up=0x01E04380 lo=0x10063005
      c = vu1gen::vmax(c, cx.vfRAny[8]);
      c = vu1gen::vmax(c, cx.viR[6]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[8]);
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
        { const int32_t nv = (int32_t)(int16_t)(st.vi[6] + 5); bvOld = st.vi[6]; bvReg = 6; st.vi[6] = nv; }
      }
      vu1gen::storeLanes(st.vf[14], urv, 0xFu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[14] = rt;
        _mm_store_si128((__m128i *)cx.vfR[14], _mm_set1_epi32((int)rt));
      }
      cx.viR[6] = (uint32_t)(c + 1u);
      c += 1u;
    }
    LC0DF0:;
    L0DF0:;
    { const bool bt = (int16_t)(bvReg == 4 ? bvOld : st.vi[4]) < 0;
    { // pair 446 pc=0xDF0 up=0x000002FF lo=0x58002003
      c = vu1gen::vmax(c, cx.viR[4]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    { // pair 447 pc=0xDF8 up=0x000002FF lo=0x088503D2
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 978) * 16u) & 0x3FFFu;
          uint32_t v = 0u; std::memcpy(&v, vm + addr + 4u, 4);
          st.vi[5] = (int32_t)(int16_t)(v & 0xFFFFu);
        }
      }
      bvReg = -1;
      cx.viR[5] = (uint32_t)(c + 4u);
      c += 1u;
    }
    if (bt) {
      st.branchTarget = 0xE10u;
      goto L0E10;
    } }
    goto LC0E00;
    L0DF8:;
    { // pair 447 pc=0xDF8 up=0x000002FF lo=0x088503D2
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 978) * 16u) & 0x3FFFu;
          uint32_t v = 0u; std::memcpy(&v, vm + addr + 4u, 4);
          st.vi[5] = (int32_t)(int16_t)(v & 0xFFFFu);
        }
      }
      bvReg = -1;
      cx.viR[5] = (uint32_t)(c + 4u);
      c += 1u;
    }
    LC0E00:;
    L0E00:;
    st.branchTarget = 0xB60u;
    { // pair 448 pc=0xE00 up=0x000002FF lo=0x400007AB
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    { // pair 449 pc=0xE08 up=0x000002FF lo=0x082603D1
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 977) * 16u) & 0x3FFFu;
          uint32_t v = 0u; std::memcpy(&v, vm + addr + 12u, 4);
          st.vi[6] = (int32_t)(int16_t)(v & 0xFFFFu);
        }
      }
      bvReg = -1;
      cx.viR[6] = (uint32_t)(c + 4u);
      c += 1u;
    }
    if (c >= (uint64_t)a.maxCycles) { st.pc = 0xB60u; goto BUDGET_OUT; }
    goto L0B60;
    L0E08:;
    { // pair 449 pc=0xE08 up=0x000002FF lo=0x082603D1
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 977) * 16u) & 0x3FFFu;
          uint32_t v = 0u; std::memcpy(&v, vm + addr + 12u, 4);
          st.vi[6] = (int32_t)(int16_t)(v & 0xFFFFu);
        }
      }
      bvReg = -1;
      cx.viR[6] = (uint32_t)(c + 4u);
      c += 1u;
    }
    L0E10:;
    { // pair 450 pc=0xE10 up=0x000002FF lo=0x80001130
      c = vu1gen::vmax(c, cx.viR[2]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[2] + st.vi[0]); bvOld = st.vi[4]; bvReg = 4; st.vi[4] = nv; }
      }
      cx.viR[4] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L0E18:;
    { // pair 451 pc=0xE18 up=0x000002FF lo=0x48007800
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        jt = ((uint32_t)(uint16_t)(bvReg == 15 ? bvOld : st.vi[15]) * 8u) & 0x3FFFu;
      }
      bvReg = -1;
      c += 1u;
    }
    { // pair 452 pc=0xE20 up=0x000002FF lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    st.branchTarget = jt; goto DISPATCH;
    L0E20:;
    { // pair 452 pc=0xE20 up=0x000002FF lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    L0E28:;
    { // pair 453 pc=0xE28 up=0x00000000 lo=0x00000000
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    L0E30:;
    { // pair 454 pc=0xE30 up=0x00000000 lo=0x00000000
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    L0E38:;
    { // pair 455 pc=0xE38 up=0x00000000 lo=0x00000000
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    L0E40:;
    { // pair 456 pc=0xE40 up=0x00000000 lo=0x00000000
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    L0E48:;
    { // pair 457 pc=0xE48 up=0x00000000 lo=0x00000000
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    L0E50:;
    { // pair 458 pc=0xE50 up=0x00000000 lo=0x00000000
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    L0E58:;
    { // pair 459 pc=0xE58 up=0x00000000 lo=0x00000000
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    L0E60:;
    { // pair 460 pc=0xE60 up=0x00000000 lo=0x00000000
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    L0E68:;
    { // pair 461 pc=0xE68 up=0x00000000 lo=0x00000000
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    L0E70:;
    { // pair 462 pc=0xE70 up=0x00000000 lo=0x00000000
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    L0E78:;
    { // pair 463 pc=0xE78 up=0x00000000 lo=0x00000000
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    L0E80:;
    { // pair 464 pc=0xE80 up=0x00000000 lo=0x00000000
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    L0E88:;
    { // pair 465 pc=0xE88 up=0x00000000 lo=0x00000000
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    L0E90:;
    { // pair 466 pc=0xE90 up=0x00000000 lo=0x00000000
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    L0E98:;
    { // pair 467 pc=0xE98 up=0x00000000 lo=0x00000000
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    L0EA0:;
    { // pair 468 pc=0xEA0 up=0x00000000 lo=0x00000000
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    L0EA8:;
    { // pair 469 pc=0xEA8 up=0x00000000 lo=0x00000000
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    L0EB0:;
    { // pair 470 pc=0xEB0 up=0x00000000 lo=0x00000000
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    L0EB8:;
    { // pair 471 pc=0xEB8 up=0x00000000 lo=0x00000000
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    L0EC0:;
    { // pair 472 pc=0xEC0 up=0x00000000 lo=0x00000000
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    L0EC8:;
    { // pair 473 pc=0xEC8 up=0x00000000 lo=0x00000000
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    L0ED0:;
    { // pair 474 pc=0xED0 up=0x00000000 lo=0x00000000
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    L0ED8:;
    { // pair 475 pc=0xED8 up=0x00000000 lo=0x00000000
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    L0EE0:;
    { // pair 476 pc=0xEE0 up=0x00000000 lo=0x00000000
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    L0EE8:;
    { // pair 477 pc=0xEE8 up=0x00000000 lo=0x00000000
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    L0EF0:;
    { // pair 478 pc=0xEF0 up=0x00000000 lo=0x00000000
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    L0EF8:;
    { // pair 479 pc=0xEF8 up=0x00000000 lo=0x00000000
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    L0F00:;
    { // pair 480 pc=0xF00 up=0x00000000 lo=0x00000000
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    L0F08:;
    { // pair 481 pc=0xF08 up=0x00000000 lo=0x00000000
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    L0F10:;
    { // pair 482 pc=0xF10 up=0x00000000 lo=0x00000000
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    L0F18:;
    { // pair 483 pc=0xF18 up=0x00000000 lo=0x00000000
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    L0F20:;
    { // pair 484 pc=0xF20 up=0x00000000 lo=0x00000000
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    L0F28:;
    { // pair 485 pc=0xF28 up=0x00000000 lo=0x00000000
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    L0F30:;
    { // pair 486 pc=0xF30 up=0x00000000 lo=0x00000000
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    L0F38:;
    { // pair 487 pc=0xF38 up=0x00000000 lo=0x00000000
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    L0F40:;
    { // pair 488 pc=0xF40 up=0x00000000 lo=0x00000000
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    L0F48:;
    { // pair 489 pc=0xF48 up=0x00000000 lo=0x00000000
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    L0F50:;
    { // pair 490 pc=0xF50 up=0x00000000 lo=0x00000000
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    L0F58:;
    { // pair 491 pc=0xF58 up=0x00000000 lo=0x00000000
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    L0F60:;
    { // pair 492 pc=0xF60 up=0x00000000 lo=0x00000000
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    L0F68:;
    { // pair 493 pc=0xF68 up=0x00000000 lo=0x00000000
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    L0F70:;
    { // pair 494 pc=0xF70 up=0x00000000 lo=0x00000000
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    L0F78:;
    { // pair 495 pc=0xF78 up=0x00000000 lo=0x00000000
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    L0F80:;
    { // pair 496 pc=0xF80 up=0x00000000 lo=0x00000000
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    L0F88:;
    { // pair 497 pc=0xF88 up=0x00000000 lo=0x00000000
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    L0F90:;
    { // pair 498 pc=0xF90 up=0x00000000 lo=0x00000000
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    L0F98:;
    { // pair 499 pc=0xF98 up=0x00000000 lo=0x00000000
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    L0FA0:;
    { // pair 500 pc=0xFA0 up=0x00000000 lo=0x00000000
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    L0FA8:;
    { // pair 501 pc=0xFA8 up=0x00000000 lo=0x00000000
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    L0FB0:;
    { // pair 502 pc=0xFB0 up=0x00000000 lo=0x00000000
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    L0FB8:;
    { // pair 503 pc=0xFB8 up=0x00000000 lo=0x00000000
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    L0FC0:;
    { // pair 504 pc=0xFC0 up=0x00000000 lo=0x00000000
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    L0FC8:;
    { // pair 505 pc=0xFC8 up=0x00000000 lo=0x00000000
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    L0FD0:;
    { // pair 506 pc=0xFD0 up=0x00000000 lo=0x00000000
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    L0FD8:;
    { // pair 507 pc=0xFD8 up=0x00000000 lo=0x00000000
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    L0FE0:;
    { // pair 508 pc=0xFE0 up=0x00000000 lo=0x00000000
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    L0FE8:;
    { // pair 509 pc=0xFE8 up=0x00000000 lo=0x00000000
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    L0FF0:;
    { // pair 510 pc=0xFF0 up=0x00000000 lo=0x00000000
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    L0FF8:;
    { // pair 511 pc=0xFF8 up=0x00000000 lo=0x00000000
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    L1000:;
    { // pair 512 pc=0x1000 up=0x000002FF lo=0x800106BC
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        st.vi[1] = (int32_t)(st.top & 0x3FFu);
      }
      bvReg = -1;
      cx.viR[1] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L1008:;
    { // pair 513 pc=0x1008 up=0x000002FF lo=0x800102F0
      c = vu1gen::vmax(c, cx.viR[1]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[0] + st.vi[1]); bvOld = st.vi[11]; bvReg = 11; st.vi[11] = nv; }
      }
      c += 1u;
    }
    L1010:;
    { // pair 514 pc=0x1010 up=0x000002FF lo=0x0A8B03D1
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 977) * 16u) & 0x3FFFu;
          const uint32_t v = (uint32_t)(uint16_t)(st.vi[11] & 0xFFFF);
          cx.markStore(addr);
          std::memcpy(vm + addr + 4u, &v, 4);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L1018:;
    { // pair 515 pc=0x1018 up=0x000002FF lo=0x800100B0
      c = vu1gen::vmax(c, cx.viR[1]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[0] + st.vi[1]); bvOld = st.vi[2]; bvReg = 2; st.vi[2] = nv; }
      }
      cx.viR[2] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L1020:;
    { // pair 516 pc=0x1020 up=0x000002FF lo=0x08231000
      c = vu1gen::vmax(c, cx.viR[2]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[2] + 0) * 16u) & 0x3FFFu;
          uint32_t v = 0u; std::memcpy(&v, vm + addr + 12u, 4);
          st.vi[3] = (int32_t)(int16_t)(v & 0xFFFFu);
        }
      }
      bvReg = -1;
      cx.viR[3] = (uint32_t)(c + 4u);
      c += 1u;
    }
    L1028:;
    { // pair 517 pc=0x1028 up=0x000002FF lo=0x01E11001
      c = vu1gen::vmax(c, cx.viR[2]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[2] + 1) * 16u) & 0x3FFFu;
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
    L1030:;
    { // pair 518 pc=0x1030 up=0x000002FF lo=0x01C2038B
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 907) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[2][0], vm + addr + 0u, 12);
        }
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[2] = rt;
        cx.vfR[2][0] = rt;
        cx.vfR[2][1] = rt;
        cx.vfR[2][2] = rt;
      }
      c += 1u;
    }
    L1038:;
    { // pair 519 pc=0x1038 up=0x000002FF lo=0x10440000
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[0] + 4096); bvOld = st.vi[4]; bvReg = 4; st.vi[4] = nv; }
      }
      cx.viR[4] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L1040:;
    { // pair 520 pc=0x1040 up=0x000002FF lo=0x01D05802
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[11] + 2) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[16][0], vm + addr + 0u, 12);
        }
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[16] = rt;
        cx.vfR[16][0] = rt;
        cx.vfR[16][1] = rt;
        cx.vfR[16][2] = rt;
      }
      c += 1u;
    }
    L1048:;
    { // pair 521 pc=0x1048 up=0x000002FF lo=0x80041934
      c = vu1gen::vmax(c, cx.viR[3]);
      c = vu1gen::vmax(c, cx.viR[4]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[3] & st.vi[4]); bvOld = st.vi[4]; bvReg = 4; st.vi[4] = nv; }
      }
      cx.viR[4] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L1050:;
    { // pair 522 pc=0x1050 up=0x01C208AA lo=0x10050384
      c = vu1gen::vmax(c, cx.vfR[1][0]);
      c = vu1gen::vmax(c, cx.vfR[1][1]);
      c = vu1gen::vmax(c, cx.vfR[1][2]);
      c = vu1gen::vmax(c, cx.vfR[2][0]);
      c = vu1gen::vmax(c, cx.vfR[2][1]);
      c = vu1gen::vmax(c, cx.vfR[2][2]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[1]);
        const __m128 bv = vu1gen::nrm4(st.vf[2]);
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
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[0] + 900); bvOld = st.vi[5]; bvReg = 5; st.vi[5] = nv; }
      }
      vu1gen::storeLanes(st.vf[2], urv, 0xEu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[2] = rt;
        cx.vfR[2][0] = rt;
        cx.vfR[2][1] = rt;
        cx.vfR[2][2] = rt;
      }
      cx.viR[5] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L1058:;
    { const bool bt = (int16_t)0 != (int16_t)(bvReg == 4 ? bvOld : st.vi[4]);
    { // pair 523 pc=0x1058 up=0x000002FF lo=0x52040010
      c = vu1gen::vmax(c, cx.viR[4]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    { // pair 524 pc=0x1060 up=0x01D0813D lo=0x01E82800
      c = vu1gen::vmax(c, cx.vfR[16][0]);
      c = vu1gen::vmax(c, cx.vfR[16][1]);
      c = vu1gen::vmax(c, cx.vfR[16][2]);
      c = vu1gen::vmax(c, cx.viR[5]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      float ur0 = 0.0f;
      float ur1 = 0.0f;
      float ur2 = 0.0f;
      {
        { int32_t iv; std::memcpy(&iv, &st.vf[16][0], 4);
          ur0 = static_cast<float>(iv) / 16.0f; }
        { int32_t iv; std::memcpy(&iv, &st.vf[16][1], 4);
          ur1 = static_cast<float>(iv) / 16.0f; }
        { int32_t iv; std::memcpy(&iv, &st.vf[16][2], 4);
          ur2 = static_cast<float>(iv) / 16.0f; }
      }
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[5] + 0) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[8][0], vm + addr + 0u, 16);
        }
      }
      bvReg = -1;
      st.vf[16][0] = ur0;
      st.vf[16][1] = ur1;
      st.vf[16][2] = ur2;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[16] = rt;
        cx.vfR[16][0] = rt;
        cx.vfR[16][1] = rt;
        cx.vfR[16][2] = rt;
      }
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[8] = rt;
        _mm_store_si128((__m128i *)cx.vfR[8], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    if (bt) {
      st.branchTarget = 0x10E0u;
      goto L10E0;
    } }
    goto LC1068;
    L1060:;
    { // pair 524 pc=0x1060 up=0x01D0813D lo=0x01E82800
      c = vu1gen::vmax(c, cx.vfR[16][0]);
      c = vu1gen::vmax(c, cx.vfR[16][1]);
      c = vu1gen::vmax(c, cx.vfR[16][2]);
      c = vu1gen::vmax(c, cx.viR[5]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      float ur0 = 0.0f;
      float ur1 = 0.0f;
      float ur2 = 0.0f;
      {
        { int32_t iv; std::memcpy(&iv, &st.vf[16][0], 4);
          ur0 = static_cast<float>(iv) / 16.0f; }
        { int32_t iv; std::memcpy(&iv, &st.vf[16][1], 4);
          ur1 = static_cast<float>(iv) / 16.0f; }
        { int32_t iv; std::memcpy(&iv, &st.vf[16][2], 4);
          ur2 = static_cast<float>(iv) / 16.0f; }
      }
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[5] + 0) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[8][0], vm + addr + 0u, 16);
        }
      }
      bvReg = -1;
      st.vf[16][0] = ur0;
      st.vf[16][1] = ur1;
      st.vf[16][2] = ur2;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[16] = rt;
        cx.vfR[16][0] = rt;
        cx.vfR[16][1] = rt;
        cx.vfR[16][2] = rt;
      }
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[8] = rt;
        _mm_store_si128((__m128i *)cx.vfR[8], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    LC1068:;
    L1068:;
    { // pair 525 pc=0x1068 up=0x0020083C lo=0x01E92801
      c = vu1gen::vmax(c, cx.vfR[1][3]);
      c = vu1gen::vmax(c, cx.viR[5]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[1]);
        const __m128 bv = _mm_set1_ps(0.0f);
        const __m128 rv = _mm_add_ps(vsv, bv);
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
                lf = vu1gen::normExactLane(rr[3], (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(3, 3, 3, 3))) + (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[3] = vu1gen::normResult(rr[3], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[3][lf & 0xFu]; stf |= lf & 0xFu; }
            rvn = _mm_loadu_ps(rr);
          } }
        cx.pushFmac(c, mac, stf, stk);
        vu1gen::storeLanes(st.acc, rvn, 0x1u);
      }
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[5] + 1) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[9][0], vm + addr + 0u, 16);
        }
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[9] = rt;
        _mm_store_si128((__m128i *)cx.vfR[9], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L1070:;
    { // pair 526 pc=0x1070 up=0x002200BE lo=0x01EA2802
      c = vu1gen::vmax(c, cx.vfR[2][2]);
      c = vu1gen::vmax(c, cx.viR[5]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        const __m128 vsv = _mm_setr_ps(0.0f, 0.0f, 0.0f, 1.0f);
        const __m128 bv = vu1gen::nrmbc(st.vf[2], 2);
        const __m128 av = vu1gen::nrm4(st.acc);
        const __m128 product = _mm_mul_ps(vsv, bv);
        const __m128 rv = _mm_add_ps(av, product);
        uint32_t mac = 0u, stf = 0u, stk = 0u;
        __m128 rvn = rv;
        { uint32_t sgn; uint32_t plain = vu1gen::classify4(rv, sgn);
          const __m128i pm = _mm_and_si128(_mm_castps_si128(product), _mm_set1_epi32(0x7FFFFFFF));
          plain &= ~uint32_t(_mm_movemask_ps(_mm_castsi128_ps(_mm_cmpgt_epi32(pm, _mm_set1_epi32(0x7F7FFFFE)))));
          if ((plain & 0x8u) == 0x8u) {
            mac = vu1gen::kMacSign.word[sgn & 0x8u];
            stf = (sgn & 0x8u) != 0u ? 0x2u : 0u;
          } else {
            float rr[4]; _mm_storeu_ps(rr, rv);
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
        if (cx.sticky) stk = vu1gen::sticky4(vsv, bv, product, 0x8u);
        cx.pushFmac(c, mac, stf, stk);
        vu1gen::storeLanes(st.acc, rvn, 0x1u);
      }
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[5] + 2) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[10][0], vm + addr + 0u, 16);
        }
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[10] = rt;
        _mm_store_si128((__m128i *)cx.vfR[10], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L1078:;
    { // pair 527 pc=0x1078 up=0x002200BD lo=0x09060398
      c = vu1gen::vmax(c, cx.vfR[2][1]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        const __m128 vsv = _mm_setr_ps(0.0f, 0.0f, 0.0f, 1.0f);
        const __m128 bv = vu1gen::nrmbc(st.vf[2], 1);
        const __m128 av = vu1gen::nrm4(st.acc);
        const __m128 product = _mm_mul_ps(vsv, bv);
        const __m128 rv = _mm_add_ps(av, product);
        uint32_t mac = 0u, stf = 0u, stk = 0u;
        __m128 rvn = rv;
        { uint32_t sgn; uint32_t plain = vu1gen::classify4(rv, sgn);
          const __m128i pm = _mm_and_si128(_mm_castps_si128(product), _mm_set1_epi32(0x7FFFFFFF));
          plain &= ~uint32_t(_mm_movemask_ps(_mm_castsi128_ps(_mm_cmpgt_epi32(pm, _mm_set1_epi32(0x7F7FFFFE)))));
          if ((plain & 0x8u) == 0x8u) {
            mac = vu1gen::kMacSign.word[sgn & 0x8u];
            stf = (sgn & 0x8u) != 0u ? 0x2u : 0u;
          } else {
            float rr[4]; _mm_storeu_ps(rr, rv);
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
        if (cx.sticky) stk = vu1gen::sticky4(vsv, bv, product, 0x8u);
        cx.pushFmac(c, mac, stf, stk);
        vu1gen::storeLanes(st.acc, rvn, 0x1u);
      }
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 920) * 16u) & 0x3FFFu;
          uint32_t v = 0u; std::memcpy(&v, vm + addr + 0u, 4);
          st.vi[6] = (int32_t)(int16_t)(v & 0xFFFFu);
        }
      }
      bvReg = -1;
      cx.viR[6] = (uint32_t)(c + 4u);
      c += 1u;
    }
    L1080:;
    { // pair 528 pc=0x1080 up=0x01DA842A lo=0x01E30396
      c = vu1gen::vmax(c, cx.vfR[16][0]);
      c = vu1gen::vmax(c, cx.vfR[16][1]);
      c = vu1gen::vmax(c, cx.vfR[16][2]);
      c = vu1gen::vmax(c, cx.vfR[26][0]);
      c = vu1gen::vmax(c, cx.vfR[26][1]);
      c = vu1gen::vmax(c, cx.vfR[26][2]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[16]);
        const __m128 bv = vu1gen::nrm4(st.vf[26]);
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
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 918) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[3][0], vm + addr + 0u, 16);
        }
      }
      bvReg = -1;
      vu1gen::storeLanes(st.vf[16], urv, 0xEu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[16] = rt;
        cx.vfR[16][0] = rt;
        cx.vfR[16][1] = rt;
        cx.vfR[16][2] = rt;
      }
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[3] = rt;
        _mm_store_si128((__m128i *)cx.vfR[3], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L1088:;
    { // pair 529 pc=0x1088 up=0x00220088 lo=0x01E43399
      c = vu1gen::vmax(c, cx.vfR[2][0]);
      c = vu1gen::vmax(c, cx.viR[6]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = _mm_setr_ps(0.0f, 0.0f, 0.0f, 1.0f);
        const __m128 bv = vu1gen::nrmbc(st.vf[2], 0);
        const __m128 av = vu1gen::nrm4(st.acc);
        const __m128 product = _mm_mul_ps(vsv, bv);
        const __m128 rv = _mm_add_ps(av, product);
        uint32_t mac = 0u, stf = 0u, stk = 0u;
        __m128 rvn = rv;
        { uint32_t sgn; uint32_t plain = vu1gen::classify4(rv, sgn);
          const __m128i pm = _mm_and_si128(_mm_castps_si128(product), _mm_set1_epi32(0x7FFFFFFF));
          plain &= ~uint32_t(_mm_movemask_ps(_mm_castsi128_ps(_mm_cmpgt_epi32(pm, _mm_set1_epi32(0x7F7FFFFE)))));
          if ((plain & 0x8u) == 0x8u) {
            mac = vu1gen::kMacSign.word[sgn & 0x8u];
            stf = (sgn & 0x8u) != 0u ? 0x2u : 0u;
          } else {
            float rr[4]; _mm_storeu_ps(rr, rv);
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
        if (cx.sticky) stk = vu1gen::sticky4(vsv, bv, product, 0x8u);
        cx.pushFmac(c, mac, stf, stk);
        urv = rvn;
      }
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[6] + 921) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[4][0], vm + addr + 0u, 16);
        }
      }
      bvReg = -1;
      vu1gen::storeLanes(st.vf[2], urv, 0x1u);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[2] = rt;
        cx.vfR[2][3] = rt;
      }
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[4] = rt;
        _mm_store_si128((__m128i *)cx.vfR[4], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L1090:;
    { // pair 530 pc=0x1090 up=0x000002FF lo=0x01E503A5
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 933) * 16u) & 0x3FFFu;
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
    L1098:;
    { // pair 531 pc=0x1098 up=0x000002FF lo=0x01E603A9
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 937) * 16u) & 0x3FFFu;
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
    L10A0:;
    { // pair 532 pc=0x10A0 up=0x01D78328 lo=0x10040010
      c = vu1gen::vmax(c, cx.vfR[16][0]);
      c = vu1gen::vmax(c, cx.vfR[16][1]);
      c = vu1gen::vmax(c, cx.vfR[16][2]);
      c = vu1gen::vmax(c, cx.vfR[23][0]);
      c = vu1gen::vmax(c, cx.vfR[23][1]);
      c = vu1gen::vmax(c, cx.vfR[23][2]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[16]);
        const __m128 bv = vu1gen::nrm4(st.vf[23]);
        const __m128 rv = _mm_add_ps(vsv, bv);
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
                lf = vu1gen::normExactLane(rr[0], (double)_mm_cvtss_f32(vsv) + (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[0] = vu1gen::normResult(rr[0], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[0][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 2u) lf = ((sgn >> 1) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[1], (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(1, 1, 1, 1))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(bv, bv, _MM_SHUFFLE(1, 1, 1, 1))));
              } else {
                uint32_t nf; rr[1] = vu1gen::normResult(rr[1], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[1][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 4u) lf = ((sgn >> 2) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[2], (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(2, 2, 2, 2))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(bv, bv, _MM_SHUFFLE(2, 2, 2, 2))));
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
        { const int32_t nv = (int32_t)(int16_t)(st.vi[0] + 16); bvOld = st.vi[4]; bvReg = 4; st.vi[4] = nv; }
      }
      vu1gen::storeLanes(st.vf[12], urv, 0xEu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[12] = rt;
        cx.vfR[12][0] = rt;
        cx.vfR[12][1] = rt;
        cx.vfR[12][2] = rt;
      }
      cx.viR[4] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L10A8:;
    { // pair 533 pc=0x10A8 up=0x00200300 lo=0x34042000
      c = vu1gen::vmax(c, cx.viR[4]);
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
          if ((plain & 0x8u) == 0x8u) {
            mac = vu1gen::kMacSign.word[sgn & 0x8u];
            stf = (sgn & 0x8u) != 0u ? 0x2u : 0u;
          } else {
            float rr[4]; _mm_storeu_ps(rr, rv);
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
        cx.commitQ(c); cx.drainFlags(c);
        st.vi[4] = (int32_t)(st.mac & (uint32_t)(uint16_t)st.vi[4]);
      }
      bvReg = -1;
      vu1gen::storeLanes(st.vf[12], urv, 0x1u);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[12] = rt;
        cx.vfR[12][3] = rt;
      }
      cx.viR[4] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L10B0:;
    { const bool bt = (int16_t)0 == (int16_t)(bvReg == 4 ? bvOld : st.vi[4]);
    { // pair 534 pc=0x10B0 up=0x000002FF lo=0x50040010
      c = vu1gen::vmax(c, cx.viR[4]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    { // pair 535 pc=0x10B8 up=0x000002FF lo=0x100C0902
      c = vu1gen::vmax(c, cx.viR[1]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[1] + 258); bvOld = st.vi[12]; bvReg = 12; st.vi[12] = nv; }
      }
      c += 1u;
    }
    if (bt) {
      st.branchTarget = 0x1138u;
      goto L1138;
    } }
    goto LC10C0;
    L10B8:;
    { // pair 535 pc=0x10B8 up=0x000002FF lo=0x100C0902
      c = vu1gen::vmax(c, cx.viR[1]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[1] + 258); bvOld = st.vi[12]; bvReg = 12; st.vi[12] = nv; }
      }
      c += 1u;
    }
    LC10C0:;
    L10C0:;
    { // pair 536 pc=0x10C0 up=0x000002FF lo=0x10840000
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[0] + 8192); bvOld = st.vi[4]; bvReg = 4; st.vi[4] = nv; }
      }
      cx.viR[4] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L10C8:;
    { // pair 537 pc=0x10C8 up=0x000002FF lo=0x800418F5
      c = vu1gen::vmax(c, cx.viR[3]);
      c = vu1gen::vmax(c, cx.viR[4]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[3] | st.vi[4]); bvOld = st.vi[3]; bvReg = 3; st.vi[3] = nv; }
      }
      cx.viR[3] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L10D0:;
    { // pair 538 pc=0x10D0 up=0x400002FF lo=0x0A231000
      c = vu1gen::vmax(c, cx.viR[2]);
      c = vu1gen::vmax(c, cx.viR[3]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[2] + 0) * 16u) & 0x3FFFu;
          const uint32_t v = (uint32_t)(uint16_t)(st.vi[3] & 0xFFFF);
          cx.markStore(addr);
          std::memcpy(vm + addr + 12u, &v, 4);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    { // pair 539 pc=0x10D8 up=0x000002FF lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    st.pc = 0x10E0u; goto END_OUT;
    L10D8:;
    { // pair 539 pc=0x10D8 up=0x000002FF lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    L10E0:;
    { // pair 540 pc=0x10E0 up=0x000002FF lo=0x01E92801
      c = vu1gen::vmax(c, cx.viR[5]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[5] + 1) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[9][0], vm + addr + 0u, 16);
        }
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[9] = rt;
        _mm_store_si128((__m128i *)cx.vfR[9], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L10E8:;
    { // pair 541 pc=0x10E8 up=0x000002FF lo=0x01EA2802
      c = vu1gen::vmax(c, cx.viR[5]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[5] + 2) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[10][0], vm + addr + 0u, 16);
        }
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[10] = rt;
        _mm_store_si128((__m128i *)cx.vfR[10], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L10F0:;
    { // pair 542 pc=0x10F0 up=0x000002FF lo=0x09060398
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 920) * 16u) & 0x3FFFu;
          uint32_t v = 0u; std::memcpy(&v, vm + addr + 0u, 4);
          st.vi[6] = (int32_t)(int16_t)(v & 0xFFFFu);
        }
      }
      bvReg = -1;
      cx.viR[6] = (uint32_t)(c + 4u);
      c += 1u;
    }
    L10F8:;
    { // pair 543 pc=0x10F8 up=0x01DA842A lo=0x01E30396
      c = vu1gen::vmax(c, cx.vfR[16][0]);
      c = vu1gen::vmax(c, cx.vfR[16][1]);
      c = vu1gen::vmax(c, cx.vfR[16][2]);
      c = vu1gen::vmax(c, cx.vfR[26][0]);
      c = vu1gen::vmax(c, cx.vfR[26][1]);
      c = vu1gen::vmax(c, cx.vfR[26][2]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[16]);
        const __m128 bv = vu1gen::nrm4(st.vf[26]);
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
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 918) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[3][0], vm + addr + 0u, 16);
        }
      }
      bvReg = -1;
      vu1gen::storeLanes(st.vf[16], urv, 0xEu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[16] = rt;
        cx.vfR[16][0] = rt;
        cx.vfR[16][1] = rt;
        cx.vfR[16][2] = rt;
      }
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[3] = rt;
        _mm_store_si128((__m128i *)cx.vfR[3], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L1100:;
    { // pair 544 pc=0x1100 up=0x000002FF lo=0x01E43399
      c = vu1gen::vmax(c, cx.viR[6]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[6] + 921) * 16u) & 0x3FFFu;
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
    L1108:;
    { // pair 545 pc=0x1108 up=0x000002FF lo=0x01E503A5
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 933) * 16u) & 0x3FFFu;
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
    L1110:;
    { // pair 546 pc=0x1110 up=0x000002FF lo=0x01E603A9
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 937) * 16u) & 0x3FFFu;
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
    L1118:;
    { // pair 547 pc=0x1118 up=0x01D78328 lo=0x8000033C
      c = vu1gen::vmax(c, cx.vfR[16][0]);
      c = vu1gen::vmax(c, cx.vfR[16][1]);
      c = vu1gen::vmax(c, cx.vfR[16][2]);
      c = vu1gen::vmax(c, cx.vfR[23][0]);
      c = vu1gen::vmax(c, cx.vfR[23][1]);
      c = vu1gen::vmax(c, cx.vfR[23][2]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[16]);
        const __m128 bv = vu1gen::nrm4(st.vf[23]);
        const __m128 rv = _mm_add_ps(vsv, bv);
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
                lf = vu1gen::normExactLane(rr[0], (double)_mm_cvtss_f32(vsv) + (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[0] = vu1gen::normResult(rr[0], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[0][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 2u) lf = ((sgn >> 1) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[1], (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(1, 1, 1, 1))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(bv, bv, _MM_SHUFFLE(1, 1, 1, 1))));
              } else {
                uint32_t nf; rr[1] = vu1gen::normResult(rr[1], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[1][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 4u) lf = ((sgn >> 2) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[2], (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(2, 2, 2, 2))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(bv, bv, _MM_SHUFFLE(2, 2, 2, 2))));
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
      vu1gen::storeLanes(st.vf[12], urv, 0xEu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[12] = rt;
        cx.vfR[12][0] = rt;
        cx.vfR[12][1] = rt;
        cx.vfR[12][2] = rt;
      }
      c += 1u;
    }
    L1120:;
    { // pair 548 pc=0x1120 up=0x00200300 lo=0x8000033C
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
          if ((plain & 0x8u) == 0x8u) {
            mac = vu1gen::kMacSign.word[sgn & 0x8u];
            stf = (sgn & 0x8u) != 0u ? 0x2u : 0u;
          } else {
            float rr[4]; _mm_storeu_ps(rr, rv);
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
      bvReg = -1;
      vu1gen::storeLanes(st.vf[12], urv, 0x1u);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[12] = rt;
        cx.vfR[12][3] = rt;
      }
      c += 1u;
    }
    L1128:;
    { // pair 549 pc=0x1128 up=0x000002FF lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    L1130:;
    { // pair 550 pc=0x1130 up=0x000002FF lo=0x100C0902
      c = vu1gen::vmax(c, cx.viR[1]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[1] + 258); bvOld = st.vi[12]; bvReg = 12; st.vi[12] = nv; }
      }
      c += 1u;
    }
    L1138:;
    { // pair 551 pc=0x1138 up=0x01ECE1BC lo=0x0B0C03D1
      c = vu1gen::vmax(c, cx.vfRAny[28]);
      c = vu1gen::vmax(c, cx.vfR[12][0]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[28]);
        const __m128 bv = vu1gen::nrmbc(st.vf[12], 0);
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
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 977) * 16u) & 0x3FFFu;
          const uint32_t v = (uint32_t)(uint16_t)(st.vi[12] & 0xFFFF);
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &v, 4);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L1140:;
    { // pair 552 pc=0x1140 up=0x01ECE8BD lo=0x090A1000
      c = vu1gen::vmax(c, cx.vfRAny[29]);
      c = vu1gen::vmax(c, cx.vfR[12][1]);
      c = vu1gen::vmax(c, cx.viR[2]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[29]);
        const __m128 bv = vu1gen::nrmbc(st.vf[12], 1);
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
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[2] + 0) * 16u) & 0x3FFFu;
          uint32_t v = 0u; std::memcpy(&v, vm + addr + 0u, 4);
          st.vi[10] = (int32_t)(int16_t)(v & 0xFFFFu);
        }
      }
      bvReg = -1;
      cx.viR[10] = (uint32_t)(c + 4u);
      c += 1u;
    }
    L1148:;
    { // pair 553 pc=0x1148 up=0x01ECF0BE lo=0x01E11000
      c = vu1gen::vmax(c, cx.vfRAny[30]);
      c = vu1gen::vmax(c, cx.vfR[12][2]);
      c = vu1gen::vmax(c, cx.viR[2]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[30]);
        const __m128 bv = vu1gen::nrmbc(st.vf[12], 2);
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
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[2] + 0) * 16u) & 0x3FFFu;
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
    L1150:;
    { // pair 554 pc=0x1150 up=0x01ECFD8B lo=0x03EC1800
      c = vu1gen::vmax(c, cx.vfRAny[31]);
      c = vu1gen::vmax(c, cx.vfR[12][3]);
      c = vu1gen::vmax(c, cx.vfRAny[3]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[31]);
        const __m128 bv = vu1gen::nrmbc(st.vf[12], 3);
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
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[12] + 0) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[3][0], 16);
        }
      }
      bvReg = -1;
      vu1gen::storeLanes(st.vf[22], urv, 0xFu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[22] = rt;
        _mm_store_si128((__m128i *)cx.vfR[22], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L1158:;
    { // pair 555 pc=0x1158 up=0x000002FF lo=0x10010080
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[0] + 128); bvOld = st.vi[1]; bvReg = 1; st.vi[1] = nv; }
      }
      cx.viR[1] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L1160:;
    { // pair 556 pc=0x1160 up=0x000002FF lo=0x01955814
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[11] + 20) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[21][0], vm + addr + 0u, 8);
        }
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[21] = rt;
        cx.vfR[21][0] = rt;
        cx.vfR[21][1] = rt;
      }
      c += 1u;
    }
    L1168:;
    { // pair 557 pc=0x1168 up=0x000002FF lo=0x00550390
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 912) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[21][2], vm + addr + 8u, 4);
        }
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[21] = rt;
        cx.vfR[21][2] = rt;
      }
      c += 1u;
    }
    L1170:;
    { // pair 558 pc=0x1170 up=0x01160003 lo=0x81F603BC
      c = vu1gen::vmax(c, cx.vfR[22][3]);
      c = vu1gen::vmax(c, cx.vfR[22][3]);
      if (cx.qValid) c = vu1gen::vmax(c, cx.qReady);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        const __m128 vsv = _mm_setr_ps(0.0f, 0.0f, 0.0f, 1.0f);
        const __m128 bv = vu1gen::nrmbc(st.vf[22], 3);
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
      }
      {
        cx.commitQ(c);
        { const float num = vu1gen::nrm(st.vf[0][3]);
          const float den = vu1gen::nrm(st.vf[22][3]);
          uint32_t di = 0u; float r;
          if (den == 0.0f) { di = (num == 0.0f) ? 0x10u : 0x20u;
            r = (std::signbit(num) != std::signbit(den)) ? -std::numeric_limits<float>::max() : std::numeric_limits<float>::max(); }
          else r = num / den;
          uint32_t ig; r = vu1gen::normResult(r, ig);
          cx.qValid = true; cx.qReady = c + 7u; cx.qVal = r; cx.qDi = di; }
      }
      bvReg = -1;
      c += 1u;
    }
    L1178:;
    { // pair 559 pc=0x1178 up=0x000002FF lo=0x01D4581D
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[11] + 29) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[20][0], vm + addr + 0u, 12);
        }
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[20] = rt;
        cx.vfR[20][0] = rt;
        cx.vfR[20][1] = rt;
        cx.vfR[20][2] = rt;
      }
      c += 1u;
    }
    L1180:;
    { // pair 560 pc=0x1180 up=0x000002FF lo=0x0034038D
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 909) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[20][3], vm + addr + 12u, 4);
        }
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[20] = rt;
        cx.vfR[20][3] = rt;
      }
      c += 1u;
    }
    L1188:;
    { // pair 561 pc=0x1188 up=0x0180B640 lo=0x01820391
      c = vu1gen::vmax(c, cx.vfR[22][0]);
      c = vu1gen::vmax(c, cx.vfR[22][1]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[22]);
        const __m128 bv = _mm_set1_ps(0.0f);
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
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 913) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[2][0], vm + addr + 0u, 8);
        }
      }
      bvReg = -1;
      vu1gen::storeLanes(st.vf[25], urv, 0xCu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[25] = rt;
        cx.vfR[25][0] = rt;
        cx.vfR[25][1] = rt;
      }
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[2] = rt;
        cx.vfR[2][0] = rt;
        cx.vfR[2][1] = rt;
      }
      c += 1u;
    }
    L1190:;
    { // pair 562 pc=0x1190 up=0x000002FF lo=0x34010800
      c = vu1gen::vmax(c, cx.viR[1]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        cx.commitQ(c); cx.drainFlags(c);
        st.vi[1] = (int32_t)(st.mac & (uint32_t)(uint16_t)st.vi[1]);
      }
      bvReg = -1;
      cx.viR[1] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L1198:;
    { // pair 563 pc=0x1198 up=0x0195A93E lo=0x03EC2001
      c = vu1gen::vmax(c, cx.vfR[21][0]);
      c = vu1gen::vmax(c, cx.vfR[21][1]);
      c = vu1gen::vmax(c, cx.vfRAny[4]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      float ur0 = 0.0f;
      float ur1 = 0.0f;
      {
        { int32_t iv; std::memcpy(&iv, &st.vf[21][0], 4);
          ur0 = static_cast<float>(iv) / 4096.0f; }
        { int32_t iv; std::memcpy(&iv, &st.vf[21][1], 4);
          ur1 = static_cast<float>(iv) / 4096.0f; }
      }
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[12] + 1) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[4][0], 16);
        }
      }
      bvReg = -1;
      st.vf[21][0] = ur0;
      st.vf[21][1] = ur1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[21] = rt;
        cx.vfR[21][0] = rt;
        cx.vfR[21][1] = rt;
      }
      c += 1u;
    }
    L11A0:;
    { // pair 564 pc=0x11A0 up=0x01D4A13C lo=0x03EC2802
      c = vu1gen::vmax(c, cx.vfR[20][0]);
      c = vu1gen::vmax(c, cx.vfR[20][1]);
      c = vu1gen::vmax(c, cx.vfR[20][2]);
      c = vu1gen::vmax(c, cx.vfRAny[5]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      float ur0 = 0.0f;
      float ur1 = 0.0f;
      float ur2 = 0.0f;
      {
        { int32_t iv; std::memcpy(&iv, &st.vf[20][0], 4);
          ur0 = static_cast<float>(iv); }
        { int32_t iv; std::memcpy(&iv, &st.vf[20][1], 4);
          ur1 = static_cast<float>(iv); }
        { int32_t iv; std::memcpy(&iv, &st.vf[20][2], 4);
          ur2 = static_cast<float>(iv); }
      }
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[12] + 2) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[5][0], 16);
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
    L11A8:;
    { // pair 565 pc=0x11A8 up=0x0180CE5C lo=0x100B5801
      c = vu1gen::vmax(c, cx.vfR[25][0]);
      c = vu1gen::vmax(c, cx.vfR[25][1]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      cx.commitQ(c);
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[25]);
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
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[11] + 1); bvOld = st.vi[11]; bvReg = 11; st.vi[11] = nv; }
      }
      vu1gen::storeLanes(st.vf[25], urv, 0xCu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[25] = rt;
        cx.vfR[25][0] = rt;
        cx.vfR[25][1] = rt;
      }
      c += 1u;
    }
    L11B0:;
    { // pair 566 pc=0x11B0 up=0x01C0B59C lo=0x03EC3003
      c = vu1gen::vmax(c, cx.vfR[22][0]);
      c = vu1gen::vmax(c, cx.vfR[22][1]);
      c = vu1gen::vmax(c, cx.vfR[22][2]);
      c = vu1gen::vmax(c, cx.vfRAny[6]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      cx.commitQ(c);
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[22]);
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
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[12] + 3) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[6][0], 16);
        }
      }
      bvReg = -1;
      vu1gen::storeLanes(st.vf[22], urv, 0xEu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[22] = rt;
        cx.vfR[22][0] = rt;
        cx.vfR[22][1] = rt;
        cx.vfR[22][2] = rt;
      }
      c += 1u;
    }
    L11B8:;
    { const bool bt = (int16_t)0 == (int16_t)(bvReg == 1 ? bvOld : st.vi[1]);
    { // pair 567 pc=0x11B8 up=0x01C0AB9C lo=0x50010002
      c = vu1gen::vmax(c, cx.vfR[21][0]);
      c = vu1gen::vmax(c, cx.vfR[21][1]);
      c = vu1gen::vmax(c, cx.vfR[21][2]);
      c = vu1gen::vmax(c, cx.viR[1]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      cx.commitQ(c);
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[21]);
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
      bvReg = -1;
      vu1gen::storeLanes(st.vf[14], urv, 0xEu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[14] = rt;
        cx.vfR[14][0] = rt;
        cx.vfR[14][1] = rt;
        cx.vfR[14][2] = rt;
      }
      c += 1u;
    }
    { // pair 568 pc=0x11C0 up=0x000002FF lo=0x11E207FF
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[0] + 32767); bvOld = st.vi[2]; bvReg = 2; st.vi[2] = nv; }
      }
      cx.viR[2] = (uint32_t)(c + 1u);
      c += 1u;
    }
    if (bt) {
      st.branchTarget = 0x11D0u;
      goto L11D0;
    } }
    goto LC11C8;
    L11C0:;
    { // pair 568 pc=0x11C0 up=0x000002FF lo=0x11E207FF
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[0] + 32767); bvOld = st.vi[2]; bvReg = 2; st.vi[2] = nv; }
      }
      cx.viR[2] = (uint32_t)(c + 1u);
      c += 1u;
    }
    LC11C8:;
    L11C8:;
    { // pair 569 pc=0x11C8 up=0x0199166C lo=0x10010001
      c = vu1gen::vmax(c, cx.vfR[2][0]);
      c = vu1gen::vmax(c, cx.vfR[2][1]);
      c = vu1gen::vmax(c, cx.vfR[25][0]);
      c = vu1gen::vmax(c, cx.vfR[25][1]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[2]);
        const __m128 bv = vu1gen::nrm4(st.vf[25]);
        const __m128 rv = _mm_sub_ps(vsv, bv);
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
            rvn = _mm_loadu_ps(rr);
          } }
        cx.pushFmac(c, mac, stf, stk);
        urv = rvn;
      }
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[0] + 1); bvOld = st.vi[1]; bvReg = 1; st.vi[1] = nv; }
      }
      vu1gen::storeLanes(st.vf[25], urv, 0xCu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[25] = rt;
        cx.vfR[25][0] = rt;
        cx.vfR[25][1] = rt;
      }
      cx.viR[1] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L11D0:;
    { // pair 570 pc=0x11D0 up=0x003B01BE lo=0x800252B4
      c = vu1gen::vmax(c, cx.vfR[27][2]);
      c = vu1gen::vmax(c, cx.viR[2]);
      c = vu1gen::vmax(c, cx.viR[10]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        const __m128 vsv = _mm_setr_ps(0.0f, 0.0f, 0.0f, 1.0f);
        const __m128 bv = vu1gen::nrmbc(st.vf[27], 2);
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
        vu1gen::storeLanes(st.acc, rvn, 0x1u);
      }
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[10] & st.vi[2]); bvOld = st.vi[10]; bvReg = 10; st.vi[10] = nv; }
      }
      cx.viR[10] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L11D8:;
    { // pair 571 pc=0x11D8 up=0x8036DDA9 lo=0x437F0000
      c = vu1gen::vmax(c, cx.vfR[27][3]);
      c = vu1gen::vmax(c, cx.vfR[22][3]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[27]);
        const __m128 bv = vu1gen::nrm4(st.vf[22]);
        const __m128 av = vu1gen::nrm4(st.acc);
        const __m128 product = _mm_mul_ps(vsv, bv);
        const __m128 rv = _mm_add_ps(av, product);
        uint32_t mac = 0u, stf = 0u, stk = 0u;
        __m128 rvn = rv;
        { uint32_t sgn; uint32_t plain = vu1gen::classify4(rv, sgn);
          const __m128i pm = _mm_and_si128(_mm_castps_si128(product), _mm_set1_epi32(0x7FFFFFFF));
          plain &= ~uint32_t(_mm_movemask_ps(_mm_castsi128_ps(_mm_cmpgt_epi32(pm, _mm_set1_epi32(0x7F7FFFFE)))));
          if ((plain & 0x8u) == 0x8u) {
            mac = vu1gen::kMacSign.word[sgn & 0x8u];
            stf = (sgn & 0x8u) != 0u ? 0x2u : 0u;
          } else {
            float rr[4]; _mm_storeu_ps(rr, rv);
            { uint8_t lf;
              if (plain & 8u) lf = ((sgn >> 3) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[3], (double)_mm_cvtss_f32(_mm_shuffle_ps(av, av, _MM_SHUFFLE(3, 3, 3, 3))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(3, 3, 3, 3))) * (double)_mm_cvtss_f32(_mm_shuffle_ps(bv, bv, _MM_SHUFFLE(3, 3, 3, 3))));
              } else {
                uint32_t nf; rr[3] = vu1gen::normResult(rr[3], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[3][lf & 0xFu]; stf |= lf & 0xFu; }
            rvn = _mm_loadu_ps(rr);
          } }
        if (cx.sticky) stk = vu1gen::sticky4(vsv, bv, product, 0x8u);
        cx.pushFmac(c, mac, stf, stk);
        urv = rvn;
      }
      { const uint32_t ib = 0x437F0000u; std::memcpy(&st.i, &ib, 4); }
      bvReg = -1;
      vu1gen::storeLanes(st.vf[22], urv, 0x1u);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[22] = rt;
        cx.vfR[22][3] = rt;
      }
      c += 1u;
    }
    L11E0:;
    { // pair 572 pc=0x11E0 up=0x01EDA17C lo=0x03EC0804
      c = vu1gen::vmax(c, cx.vfRAny[20]);
      c = vu1gen::vmax(c, cx.vfRAny[1]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      float ur0 = 0.0f;
      float ur1 = 0.0f;
      float ur2 = 0.0f;
      float ur3 = 0.0f;
      {
        { const int32_t iv = vu1gen::ftoi(vu1gen::nrm(st.vf[20][0]), 1.0f);
          std::memcpy(&ur0, &iv, 4); }
        { const int32_t iv = vu1gen::ftoi(vu1gen::nrm(st.vf[20][1]), 1.0f);
          std::memcpy(&ur1, &iv, 4); }
        { const int32_t iv = vu1gen::ftoi(vu1gen::nrm(st.vf[20][2]), 1.0f);
          std::memcpy(&ur2, &iv, 4); }
        { const int32_t iv = vu1gen::ftoi(vu1gen::nrm(st.vf[20][3]), 1.0f);
          std::memcpy(&ur3, &iv, 4); }
      }
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[12] + 4) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[1][0], 16);
        }
      }
      bvReg = -1;
      st.vf[13][0] = ur0;
      st.vf[13][1] = ur1;
      st.vf[13][2] = ur2;
      st.vf[13][3] = ur3;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[13] = rt;
        _mm_store_si128((__m128i *)cx.vfR[13], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    L11E8:;
    { // pair 573 pc=0x11E8 up=0x019BCE45 lo=0x100C6005
      c = vu1gen::vmax(c, cx.vfR[25][0]);
      c = vu1gen::vmax(c, cx.vfR[25][1]);
      c = vu1gen::vmax(c, cx.vfR[27][1]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[25]);
        const __m128 bv = vu1gen::nrmbc(st.vf[27], 1);
        const __m128 rv = _mm_sub_ps(vsv, bv);
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
                lf = vu1gen::normExactLane(rr[0], (double)_mm_cvtss_f32(vsv) - (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[0] = vu1gen::normResult(rr[0], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[0][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 2u) lf = ((sgn >> 1) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[1], (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(1, 1, 1, 1))) - (double)_mm_cvtss_f32(bv));
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
        { const int32_t nv = (int32_t)(int16_t)(st.vi[12] + 5); bvOld = st.vi[12]; bvReg = 12; st.vi[12] = nv; }
      }
      vu1gen::storeLanes(st.vf[25], urv, 0xCu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[25] = rt;
        cx.vfR[25][0] = rt;
        cx.vfR[25][1] = rt;
      }
      c += 1u;
    }
    L11F0:;
    { // pair 574 pc=0x11F0 up=0x000002FF lo=0x01D05802
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[11] + 2) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[16][0], vm + addr + 0u, 12);
        }
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[16] = rt;
        cx.vfR[16][0] = rt;
        cx.vfR[16][1] = rt;
        cx.vfR[16][2] = rt;
      }
      c += 1u;
    }
    L11F8:;
    { // pair 575 pc=0x11F8 up=0x0020B59F lo=0x03EB6001
      c = vu1gen::vmax(c, cx.vfR[22][3]);
      c = vu1gen::vmax(c, cx.vfRAny[12]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[22]);
        const __m128 bv = _mm_set1_ps(vu1gen::nrm(st.i));
        const __m128 rv = _mm_min_ps(vsv, bv);
        urv = rv;
      }
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[11] + 1) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[12][0], 16);
        }
      }
      bvReg = -1;
      vu1gen::storeLanes(st.vf[22], urv, 0x1u);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[22] = rt;
        cx.vfR[22][3] = rt;
      }
      c += 1u;
    }
    L1200:;
    { // pair 576 pc=0x1200 up=0x000002FF lo=0x03CBA813
      c = vu1gen::vmax(c, cx.vfR[21][0]);
      c = vu1gen::vmax(c, cx.vfR[21][1]);
      c = vu1gen::vmax(c, cx.vfR[21][2]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[11] + 19) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[21][0], 12);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L1208:;
    { // pair 577 pc=0x1208 up=0x01DAC9FF lo=0x03EBA01C
      c = vu1gen::vmax(c, cx.vfR[25][0]);
      c = vu1gen::vmax(c, cx.vfR[25][1]);
      c = vu1gen::vmax(c, cx.vfR[25][2]);
      c = vu1gen::vmax(c, cx.vfR[26][3]);
      c = vu1gen::vmax(c, cx.vfRAny[20]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { uint32_t wb = 0u; std::memcpy(&wb, &st.vf[26][3], 4);
          const int32_t limit = (wb & 0x7F800000u) != 0u ? (int32_t)(wb & 0x7FFFFFFFu) : 0x007FFFFF;
          uint32_t fl = 0u;
          { uint32_t vb = 0u; std::memcpy(&vb, &st.vf[25][0], 4);
            int32_t ob; uint32_t t = vb; std::memcpy(&ob, &t, 4); if (ob > limit) fl |= 0x01u;
            t = vb ^ 0x80000000u; std::memcpy(&ob, &t, 4); if (ob > limit) fl |= 0x02u; }
          { uint32_t vb = 0u; std::memcpy(&vb, &st.vf[25][1], 4);
            int32_t ob; uint32_t t = vb; std::memcpy(&ob, &t, 4); if (ob > limit) fl |= 0x04u;
            t = vb ^ 0x80000000u; std::memcpy(&ob, &t, 4); if (ob > limit) fl |= 0x08u; }
          { uint32_t vb = 0u; std::memcpy(&vb, &st.vf[25][2], 4);
            int32_t ob; uint32_t t = vb; std::memcpy(&ob, &t, 4); if (ob > limit) fl |= 0x10u;
            t = vb ^ 0x80000000u; std::memcpy(&ob, &t, 4); if (ob > limit) fl |= 0x20u; }
          cx.workingClip = ((cx.workingClip << 6) | (fl & 0x3Fu)) & 0xFFFFFFu;
          cx.pushClip(c, cx.workingClip); }
      }
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[11] + 28) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[20][0], 16);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L1210:;
    { // pair 578 pc=0x1210 up=0x01D0813D lo=0x03CC7000
      c = vu1gen::vmax(c, cx.vfR[16][0]);
      c = vu1gen::vmax(c, cx.vfR[16][1]);
      c = vu1gen::vmax(c, cx.vfR[16][2]);
      c = vu1gen::vmax(c, cx.vfR[14][0]);
      c = vu1gen::vmax(c, cx.vfR[14][1]);
      c = vu1gen::vmax(c, cx.vfR[14][2]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      float ur0 = 0.0f;
      float ur1 = 0.0f;
      float ur2 = 0.0f;
      {
        { int32_t iv; std::memcpy(&iv, &st.vf[16][0], 4);
          ur0 = static_cast<float>(iv) / 16.0f; }
        { int32_t iv; std::memcpy(&iv, &st.vf[16][1], 4);
          ur1 = static_cast<float>(iv) / 16.0f; }
        { int32_t iv; std::memcpy(&iv, &st.vf[16][2], 4);
          ur2 = static_cast<float>(iv) / 16.0f; }
      }
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[12] + 0) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[14][0], 12);
        }
      }
      bvReg = -1;
      st.vf[16][0] = ur0;
      st.vf[16][1] = ur1;
      st.vf[16][2] = ur2;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[16] = rt;
        cx.vfR[16][0] = rt;
        cx.vfR[16][1] = rt;
        cx.vfR[16][2] = rt;
      }
      c += 1u;
    }
    L1218:;
    { // pair 579 pc=0x1218 up=0x01D9C9FF lo=0x03EC6801
      c = vu1gen::vmax(c, cx.vfR[25][0]);
      c = vu1gen::vmax(c, cx.vfR[25][1]);
      c = vu1gen::vmax(c, cx.vfR[25][2]);
      c = vu1gen::vmax(c, cx.vfR[25][3]);
      c = vu1gen::vmax(c, cx.vfRAny[13]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { uint32_t wb = 0u; std::memcpy(&wb, &st.vf[25][3], 4);
          const int32_t limit = (wb & 0x7F800000u) != 0u ? (int32_t)(wb & 0x7FFFFFFFu) : 0x007FFFFF;
          uint32_t fl = 0u;
          { uint32_t vb = 0u; std::memcpy(&vb, &st.vf[25][0], 4);
            int32_t ob; uint32_t t = vb; std::memcpy(&ob, &t, 4); if (ob > limit) fl |= 0x01u;
            t = vb ^ 0x80000000u; std::memcpy(&ob, &t, 4); if (ob > limit) fl |= 0x02u; }
          { uint32_t vb = 0u; std::memcpy(&vb, &st.vf[25][1], 4);
            int32_t ob; uint32_t t = vb; std::memcpy(&ob, &t, 4); if (ob > limit) fl |= 0x04u;
            t = vb ^ 0x80000000u; std::memcpy(&ob, &t, 4); if (ob > limit) fl |= 0x08u; }
          { uint32_t vb = 0u; std::memcpy(&vb, &st.vf[25][2], 4);
            int32_t ob; uint32_t t = vb; std::memcpy(&ob, &t, 4); if (ob > limit) fl |= 0x10u;
            t = vb ^ 0x80000000u; std::memcpy(&ob, &t, 4); if (ob > limit) fl |= 0x20u; }
          cx.workingClip = ((cx.workingClip << 6) | (fl & 0x3Fu)) & 0xFFFFFFu;
          cx.pushClip(c, cx.workingClip); }
      }
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[12] + 1) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[13][0], 16);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L1220:;
    { // pair 580 pc=0x1220 up=0x0020B590 lo=0x800701B0
      c = vu1gen::vmax(c, cx.vfR[22][3]);
      c = vu1gen::vmax(c, cx.viR[7]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[22]);
        const __m128 bv = _mm_set1_ps(0.0f);
        const __m128 rv = _mm_max_ps(vsv, bv);
        urv = rv;
      }
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[0] + st.vi[7]); bvOld = st.vi[6]; bvReg = 6; st.vi[6] = nv; }
      }
      vu1gen::storeLanes(st.vf[22], urv, 0x1u);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[22] = rt;
        cx.vfR[22][3] = rt;
      }
      cx.viR[6] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L1228:;
    { // pair 581 pc=0x1228 up=0x000002FF lo=0x800801F0
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[0] + st.vi[8]); bvOld = st.vi[7]; bvReg = 7; st.vi[7] = nv; }
      }
      cx.viR[7] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L1230:;
    { // pair 582 pc=0x1230 up=0x01DA842A lo=0x80073135
      c = vu1gen::vmax(c, cx.vfR[16][0]);
      c = vu1gen::vmax(c, cx.vfR[16][1]);
      c = vu1gen::vmax(c, cx.vfR[16][2]);
      c = vu1gen::vmax(c, cx.vfR[26][0]);
      c = vu1gen::vmax(c, cx.vfR[26][1]);
      c = vu1gen::vmax(c, cx.vfR[26][2]);
      c = vu1gen::vmax(c, cx.viR[6]);
      c = vu1gen::vmax(c, cx.viR[7]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[16]);
        const __m128 bv = vu1gen::nrm4(st.vf[26]);
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
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[6] | st.vi[7]); bvOld = st.vi[4]; bvReg = 4; st.vi[4] = nv; }
      }
      vu1gen::storeLanes(st.vf[16], urv, 0xEu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[16] = rt;
        cx.vfR[16][0] = rt;
        cx.vfR[16][1] = rt;
        cx.vfR[16][2] = rt;
      }
      cx.viR[4] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L1238:;
    { // pair 583 pc=0x1238 up=0x000002FF lo=0x80073174
      c = vu1gen::vmax(c, cx.viR[6]);
      c = vu1gen::vmax(c, cx.viR[7]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[6] & st.vi[7]); bvOld = st.vi[5]; bvReg = 5; st.vi[5] = nv; }
      }
      cx.viR[5] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L1240:;
    { // pair 584 pc=0x1240 up=0x01EFB17D lo=0x100200CC
      c = vu1gen::vmax(c, cx.vfRAny[22]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      float ur0 = 0.0f;
      float ur1 = 0.0f;
      float ur2 = 0.0f;
      float ur3 = 0.0f;
      {
        { const int32_t iv = vu1gen::ftoi(vu1gen::nrm(st.vf[22][0]), 16.0f);
          std::memcpy(&ur0, &iv, 4); }
        { const int32_t iv = vu1gen::ftoi(vu1gen::nrm(st.vf[22][1]), 16.0f);
          std::memcpy(&ur1, &iv, 4); }
        { const int32_t iv = vu1gen::ftoi(vu1gen::nrm(st.vf[22][2]), 16.0f);
          std::memcpy(&ur2, &iv, 4); }
        { const int32_t iv = vu1gen::ftoi(vu1gen::nrm(st.vf[22][3]), 16.0f);
          std::memcpy(&ur3, &iv, 4); }
      }
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[0] + 204); bvOld = st.vi[2]; bvReg = 2; st.vi[2] = nv; }
      }
      st.vf[15][0] = ur0;
      st.vf[15][1] = ur1;
      st.vf[15][2] = ur2;
      st.vf[15][3] = ur3;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[15] = rt;
        _mm_store_si128((__m128i *)cx.vfR[15], _mm_set1_epi32((int)rt));
      }
      cx.viR[2] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L1248:;
    { // pair 585 pc=0x1248 up=0x000002FF lo=0x38080000
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        cx.commitQ(c); cx.drainFlags(c);
        st.vi[8] = (int32_t)(st.clip & 0x0FFFu);
      }
      bvReg = -1;
      c += 1u;
    }
    L1250:;
    { // pair 586 pc=0x1250 up=0x01D78328 lo=0x80024234
      c = vu1gen::vmax(c, cx.vfR[16][0]);
      c = vu1gen::vmax(c, cx.vfR[16][1]);
      c = vu1gen::vmax(c, cx.vfR[16][2]);
      c = vu1gen::vmax(c, cx.vfR[23][0]);
      c = vu1gen::vmax(c, cx.vfR[23][1]);
      c = vu1gen::vmax(c, cx.vfR[23][2]);
      c = vu1gen::vmax(c, cx.viR[2]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[16]);
        const __m128 bv = vu1gen::nrm4(st.vf[23]);
        const __m128 rv = _mm_add_ps(vsv, bv);
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
                lf = vu1gen::normExactLane(rr[0], (double)_mm_cvtss_f32(vsv) + (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[0] = vu1gen::normResult(rr[0], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[0][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 2u) lf = ((sgn >> 1) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[1], (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(1, 1, 1, 1))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(bv, bv, _MM_SHUFFLE(1, 1, 1, 1))));
              } else {
                uint32_t nf; rr[1] = vu1gen::normResult(rr[1], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[1][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 4u) lf = ((sgn >> 2) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[2], (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(2, 2, 2, 2))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(bv, bv, _MM_SHUFFLE(2, 2, 2, 2))));
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
        { const int32_t nv = (int32_t)(int16_t)(st.vi[8] & st.vi[2]); bvOld = st.vi[8]; bvReg = 8; st.vi[8] = nv; }
      }
      vu1gen::storeLanes(st.vf[12], urv, 0xEu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[12] = rt;
        cx.vfR[12][0] = rt;
        cx.vfR[12][1] = rt;
        cx.vfR[12][2] = rt;
      }
      c += 1u;
    }
    L1258:;
    { // pair 587 pc=0x1258 up=0x00200300 lo=0x80014235
      c = vu1gen::vmax(c, cx.viR[1]);
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
          if ((plain & 0x8u) == 0x8u) {
            mac = vu1gen::kMacSign.word[sgn & 0x8u];
            stf = (sgn & 0x8u) != 0u ? 0x2u : 0u;
          } else {
            float rr[4]; _mm_storeu_ps(rr, rv);
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
        { const int32_t nv = (int32_t)(int16_t)(st.vi[8] | st.vi[1]); bvOld = st.vi[8]; bvReg = 8; st.vi[8] = nv; }
      }
      vu1gen::storeLanes(st.vf[12], urv, 0x1u);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[12] = rt;
        cx.vfR[12][3] = rt;
      }
      c += 1u;
    }
    L1260:;
    { // pair 588 pc=0x1260 up=0x000002FF lo=0x80082135
      c = vu1gen::vmax(c, cx.viR[4]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[4] | st.vi[8]); bvOld = st.vi[4]; bvReg = 4; st.vi[4] = nv; }
      }
      cx.viR[4] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L1268:;
    { // pair 589 pc=0x1268 up=0x000002FF lo=0x80082974
      c = vu1gen::vmax(c, cx.viR[5]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[5] & st.vi[8]); bvOld = st.vi[5]; bvReg = 5; st.vi[5] = nv; }
      }
      cx.viR[5] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L1270:;
    { const bool bt = (int16_t)0 == (int16_t)(bvReg == 4 ? bvOld : st.vi[4]);
    { // pair 590 pc=0x1270 up=0x01ECE1BC lo=0x50040002
      c = vu1gen::vmax(c, cx.vfRAny[28]);
      c = vu1gen::vmax(c, cx.vfR[12][0]);
      c = vu1gen::vmax(c, cx.viR[4]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[28]);
        const __m128 bv = vu1gen::nrmbc(st.vf[12], 0);
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
    { // pair 591 pc=0x1278 up=0x01ECE8BD lo=0x800000F0
      c = vu1gen::vmax(c, cx.vfRAny[29]);
      c = vu1gen::vmax(c, cx.vfR[12][1]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[29]);
        const __m128 bv = vu1gen::nrmbc(st.vf[12], 1);
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
        { const int32_t nv = (int32_t)(int16_t)(st.vi[0] + st.vi[0]); bvOld = st.vi[3]; bvReg = 3; st.vi[3] = nv; }
      }
      cx.viR[3] = (uint32_t)(c + 1u);
      c += 1u;
    }
    if (bt) {
      st.branchTarget = 0x1288u;
      goto L1288;
    } }
    goto LC1280;
    L1278:;
    { // pair 591 pc=0x1278 up=0x01ECE8BD lo=0x800000F0
      c = vu1gen::vmax(c, cx.vfRAny[29]);
      c = vu1gen::vmax(c, cx.vfR[12][1]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[29]);
        const __m128 bv = vu1gen::nrmbc(st.vf[12], 1);
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
        { const int32_t nv = (int32_t)(int16_t)(st.vi[0] + st.vi[0]); bvOld = st.vi[3]; bvReg = 3; st.vi[3] = nv; }
      }
      cx.viR[3] = (uint32_t)(c + 1u);
      c += 1u;
    }
    LC1280:;
    L1280:;
    { // pair 592 pc=0x1280 up=0x000002FF lo=0x800D00F0
      c = vu1gen::vmax(c, cx.viR[13]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[0] + st.vi[13]); bvOld = st.vi[3]; bvReg = 3; st.vi[3] = nv; }
      }
      cx.viR[3] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L1288:;
    { const bool bt = (int16_t)0 == (int16_t)(bvReg == 5 ? bvOld : st.vi[5]);
    { // pair 593 pc=0x1288 up=0x01ECF0BE lo=0x50050003
      c = vu1gen::vmax(c, cx.vfRAny[30]);
      c = vu1gen::vmax(c, cx.vfR[12][2]);
      c = vu1gen::vmax(c, cx.viR[5]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[30]);
        const __m128 bv = vu1gen::nrmbc(st.vf[12], 2);
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
    { // pair 594 pc=0x1290 up=0x01ECFD8B lo=0x0A245813
      c = vu1gen::vmax(c, cx.vfRAny[31]);
      c = vu1gen::vmax(c, cx.vfR[12][3]);
      c = vu1gen::vmax(c, cx.viR[4]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[31]);
        const __m128 bv = vu1gen::nrmbc(st.vf[12], 3);
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
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[11] + 19) * 16u) & 0x3FFFu;
          const uint32_t v = (uint32_t)(uint16_t)(st.vi[4] & 0xFFFF);
          cx.markStore(addr);
          std::memcpy(vm + addr + 12u, &v, 4);
        }
      }
      bvReg = -1;
      vu1gen::storeLanes(st.vf[22], urv, 0xFu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[22] = rt;
        _mm_store_si128((__m128i *)cx.vfR[22], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    if (bt) {
      st.branchTarget = 0x12A8u;
      goto L12A8;
    } }
    goto LC1298;
    L1290:;
    { // pair 594 pc=0x1290 up=0x01ECFD8B lo=0x0A245813
      c = vu1gen::vmax(c, cx.vfRAny[31]);
      c = vu1gen::vmax(c, cx.vfR[12][3]);
      c = vu1gen::vmax(c, cx.viR[4]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[31]);
        const __m128 bv = vu1gen::nrmbc(st.vf[12], 3);
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
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[11] + 19) * 16u) & 0x3FFFu;
          const uint32_t v = (uint32_t)(uint16_t)(st.vi[4] & 0xFFFF);
          cx.markStore(addr);
          std::memcpy(vm + addr + 12u, &v, 4);
        }
      }
      bvReg = -1;
      vu1gen::storeLanes(st.vf[22], urv, 0xFu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[22] = rt;
        _mm_store_si128((__m128i *)cx.vfR[22], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    LC1298:;
    L1298:;
    { // pair 595 pc=0x1298 up=0x000002FF lo=0x12020001
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[0] - 1); bvOld = st.vi[2]; bvReg = 2; st.vi[2] = nv; }
      }
      cx.viR[2] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L12A0:;
    { // pair 596 pc=0x12A0 up=0x000002FF lo=0x0A225813
      c = vu1gen::vmax(c, cx.viR[2]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[11] + 19) * 16u) & 0x3FFFu;
          const uint32_t v = (uint32_t)(uint16_t)(st.vi[2] & 0xFFFF);
          cx.markStore(addr);
          std::memcpy(vm + addr + 12u, &v, 4);
        }
      }
      bvReg = -1;
      c += 1u;
    }
    L12A8:;
    { // pair 597 pc=0x12A8 up=0x000002FF lo=0x10010080
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[0] + 128); bvOld = st.vi[1]; bvReg = 1; st.vi[1] = nv; }
      }
      cx.viR[1] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L12B0:;
    { // pair 598 pc=0x12B0 up=0x000002FF lo=0x01955814
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[11] + 20) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[21][0], vm + addr + 0u, 8);
        }
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[21] = rt;
        cx.vfR[21][0] = rt;
        cx.vfR[21][1] = rt;
      }
      c += 1u;
    }
    L12B8:;
    { // pair 599 pc=0x12B8 up=0x000002FF lo=0x00550390
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 912) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[21][2], vm + addr + 8u, 4);
        }
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[21] = rt;
        cx.vfR[21][2] = rt;
      }
      c += 1u;
    }
    L12C0:;
    { // pair 600 pc=0x12C0 up=0x01160003 lo=0x81F603BC
      c = vu1gen::vmax(c, cx.vfR[22][3]);
      c = vu1gen::vmax(c, cx.vfR[22][3]);
      if (cx.qValid) c = vu1gen::vmax(c, cx.qReady);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        const __m128 vsv = _mm_setr_ps(0.0f, 0.0f, 0.0f, 1.0f);
        const __m128 bv = vu1gen::nrmbc(st.vf[22], 3);
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
      }
      {
        cx.commitQ(c);
        { const float num = vu1gen::nrm(st.vf[0][3]);
          const float den = vu1gen::nrm(st.vf[22][3]);
          uint32_t di = 0u; float r;
          if (den == 0.0f) { di = (num == 0.0f) ? 0x10u : 0x20u;
            r = (std::signbit(num) != std::signbit(den)) ? -std::numeric_limits<float>::max() : std::numeric_limits<float>::max(); }
          else r = num / den;
          uint32_t ig; r = vu1gen::normResult(r, ig);
          cx.qValid = true; cx.qReady = c + 7u; cx.qVal = r; cx.qDi = di; }
      }
      bvReg = -1;
      c += 1u;
    }
    L12C8:;
    { // pair 601 pc=0x12C8 up=0x000002FF lo=0x01D4581D
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[11] + 29) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[20][0], vm + addr + 0u, 12);
        }
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[20] = rt;
        cx.vfR[20][0] = rt;
        cx.vfR[20][1] = rt;
        cx.vfR[20][2] = rt;
      }
      c += 1u;
    }
    L12D0:;
    { // pair 602 pc=0x12D0 up=0x000002FF lo=0x0034038D
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 909) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[20][3], vm + addr + 12u, 4);
        }
      }
      bvReg = -1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[20] = rt;
        cx.vfR[20][3] = rt;
      }
      c += 1u;
    }
    L12D8:;
    { // pair 603 pc=0x12D8 up=0x0180B640 lo=0x01820391
      c = vu1gen::vmax(c, cx.vfR[22][0]);
      c = vu1gen::vmax(c, cx.vfR[22][1]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[22]);
        const __m128 bv = _mm_set1_ps(0.0f);
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
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[0] + 913) * 16u) & 0x3FFFu;
          std::memcpy(&st.vf[2][0], vm + addr + 0u, 8);
        }
      }
      bvReg = -1;
      vu1gen::storeLanes(st.vf[25], urv, 0xCu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[25] = rt;
        cx.vfR[25][0] = rt;
        cx.vfR[25][1] = rt;
      }
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[2] = rt;
        cx.vfR[2][0] = rt;
        cx.vfR[2][1] = rt;
      }
      c += 1u;
    }
    L12E0:;
    { // pair 604 pc=0x12E0 up=0x000002FF lo=0x34010800
      c = vu1gen::vmax(c, cx.viR[1]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        cx.commitQ(c); cx.drainFlags(c);
        st.vi[1] = (int32_t)(st.mac & (uint32_t)(uint16_t)st.vi[1]);
      }
      bvReg = -1;
      cx.viR[1] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L12E8:;
    { // pair 605 pc=0x12E8 up=0x0195A93E lo=0x80627BFC
      c = vu1gen::vmax(c, cx.vfR[21][0]);
      c = vu1gen::vmax(c, cx.vfR[21][1]);
      c = vu1gen::vmax(c, cx.vfR[15][3]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      float ur0 = 0.0f;
      float ur1 = 0.0f;
      {
        { int32_t iv; std::memcpy(&iv, &st.vf[21][0], 4);
          ur0 = static_cast<float>(iv) / 4096.0f; }
        { int32_t iv; std::memcpy(&iv, &st.vf[21][1], 4);
          ur1 = static_cast<float>(iv) / 4096.0f; }
      }
      {
        { uint32_t fv = 0u; std::memcpy(&fv, &st.vf[15][3], 4);
          bvOld = st.vi[2]; bvReg = 2;
          st.vi[2] = (int32_t)(int16_t)(fv & 0xFFFFu);
        }
      }
      st.vf[21][0] = ur0;
      st.vf[21][1] = ur1;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[21] = rt;
        cx.vfR[21][0] = rt;
        cx.vfR[21][1] = rt;
      }
      cx.viR[2] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L12F0:;
    { // pair 606 pc=0x12F0 up=0x01D4A13C lo=0x03CC7802
      c = vu1gen::vmax(c, cx.vfR[20][0]);
      c = vu1gen::vmax(c, cx.vfR[20][1]);
      c = vu1gen::vmax(c, cx.vfR[20][2]);
      c = vu1gen::vmax(c, cx.vfR[15][0]);
      c = vu1gen::vmax(c, cx.vfR[15][1]);
      c = vu1gen::vmax(c, cx.vfR[15][2]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      float ur0 = 0.0f;
      float ur1 = 0.0f;
      float ur2 = 0.0f;
      {
        { int32_t iv; std::memcpy(&iv, &st.vf[20][0], 4);
          ur0 = static_cast<float>(iv); }
        { int32_t iv; std::memcpy(&iv, &st.vf[20][1], 4);
          ur1 = static_cast<float>(iv); }
        { int32_t iv; std::memcpy(&iv, &st.vf[20][2], 4);
          ur2 = static_cast<float>(iv); }
      }
      {
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[12] + 2) * 16u) & 0x3FFFu;
          cx.markStore(addr);
          std::memcpy(vm + addr + 0u, &st.vf[15][0], 12);
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
    L12F8:;
    { // pair 607 pc=0x12F8 up=0x0180CE5C lo=0x100B5801
      c = vu1gen::vmax(c, cx.vfR[25][0]);
      c = vu1gen::vmax(c, cx.vfR[25][1]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      cx.commitQ(c);
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[25]);
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
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[11] + 1); bvOld = st.vi[11]; bvReg = 11; st.vi[11] = nv; }
      }
      vu1gen::storeLanes(st.vf[25], urv, 0xCu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[25] = rt;
        cx.vfR[25][0] = rt;
        cx.vfR[25][1] = rt;
      }
      c += 1u;
    }
    L1300:;
    { // pair 608 pc=0x1300 up=0x01C0B59C lo=0x100C6003
      c = vu1gen::vmax(c, cx.vfR[22][0]);
      c = vu1gen::vmax(c, cx.vfR[22][1]);
      c = vu1gen::vmax(c, cx.vfR[22][2]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      cx.commitQ(c);
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[22]);
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
        { const int32_t nv = (int32_t)(int16_t)(st.vi[12] + 3); bvOld = st.vi[12]; bvReg = 12; st.vi[12] = nv; }
      }
      vu1gen::storeLanes(st.vf[22], urv, 0xEu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[22] = rt;
        cx.vfR[22][0] = rt;
        cx.vfR[22][1] = rt;
        cx.vfR[22][2] = rt;
      }
      c += 1u;
    }
    L1308:;
    { const bool bt = (int16_t)0 == (int16_t)(bvReg == 1 ? bvOld : st.vi[1]);
    { // pair 609 pc=0x1308 up=0x01C0AB9C lo=0x50010002
      c = vu1gen::vmax(c, cx.vfR[21][0]);
      c = vu1gen::vmax(c, cx.vfR[21][1]);
      c = vu1gen::vmax(c, cx.vfR[21][2]);
      c = vu1gen::vmax(c, cx.viR[1]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      cx.commitQ(c);
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[21]);
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
      bvReg = -1;
      vu1gen::storeLanes(st.vf[14], urv, 0xEu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[14] = rt;
        cx.vfR[14][0] = rt;
        cx.vfR[14][1] = rt;
        cx.vfR[14][2] = rt;
      }
      c += 1u;
    }
    { // pair 610 pc=0x1310 up=0x000002FF lo=0x100400C9
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[0] + 201); bvOld = st.vi[4]; bvReg = 4; st.vi[4] = nv; }
      }
      cx.viR[4] = (uint32_t)(c + 1u);
      c += 1u;
    }
    if (bt) {
      st.branchTarget = 0x1320u;
      goto L1320;
    } }
    goto LC1318;
    L1310:;
    { // pair 610 pc=0x1310 up=0x000002FF lo=0x100400C9
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[0] + 201); bvOld = st.vi[4]; bvReg = 4; st.vi[4] = nv; }
      }
      cx.viR[4] = (uint32_t)(c + 1u);
      c += 1u;
    }
    LC1318:;
    L1318:;
    { // pair 611 pc=0x1318 up=0x0199166C lo=0x10010001
      c = vu1gen::vmax(c, cx.vfR[2][0]);
      c = vu1gen::vmax(c, cx.vfR[2][1]);
      c = vu1gen::vmax(c, cx.vfR[25][0]);
      c = vu1gen::vmax(c, cx.vfR[25][1]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[2]);
        const __m128 bv = vu1gen::nrm4(st.vf[25]);
        const __m128 rv = _mm_sub_ps(vsv, bv);
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
            rvn = _mm_loadu_ps(rr);
          } }
        cx.pushFmac(c, mac, stf, stk);
        urv = rvn;
      }
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[0] + 1); bvOld = st.vi[1]; bvReg = 1; st.vi[1] = nv; }
      }
      vu1gen::storeLanes(st.vf[25], urv, 0xCu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[25] = rt;
        cx.vfR[25][0] = rt;
        cx.vfR[25][1] = rt;
      }
      cx.viR[1] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L1320:;
    { // pair 612 pc=0x1320 up=0x003B01BE lo=0x120A5001
      c = vu1gen::vmax(c, cx.vfR[27][2]);
      c = vu1gen::vmax(c, cx.viR[10]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        const __m128 vsv = _mm_setr_ps(0.0f, 0.0f, 0.0f, 1.0f);
        const __m128 bv = vu1gen::nrmbc(st.vf[27], 2);
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
        vu1gen::storeLanes(st.acc, rvn, 0x1u);
      }
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[10] - 1); bvOld = st.vi[10]; bvReg = 10; st.vi[10] = nv; }
      }
      cx.viR[10] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L1328:;
    { // pair 613 pc=0x1328 up=0x0036DDA9 lo=0x800310F5
      c = vu1gen::vmax(c, cx.vfR[27][3]);
      c = vu1gen::vmax(c, cx.vfR[22][3]);
      c = vu1gen::vmax(c, cx.viR[2]);
      c = vu1gen::vmax(c, cx.viR[3]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[27]);
        const __m128 bv = vu1gen::nrm4(st.vf[22]);
        const __m128 av = vu1gen::nrm4(st.acc);
        const __m128 product = _mm_mul_ps(vsv, bv);
        const __m128 rv = _mm_add_ps(av, product);
        uint32_t mac = 0u, stf = 0u, stk = 0u;
        __m128 rvn = rv;
        { uint32_t sgn; uint32_t plain = vu1gen::classify4(rv, sgn);
          const __m128i pm = _mm_and_si128(_mm_castps_si128(product), _mm_set1_epi32(0x7FFFFFFF));
          plain &= ~uint32_t(_mm_movemask_ps(_mm_castsi128_ps(_mm_cmpgt_epi32(pm, _mm_set1_epi32(0x7F7FFFFE)))));
          if ((plain & 0x8u) == 0x8u) {
            mac = vu1gen::kMacSign.word[sgn & 0x8u];
            stf = (sgn & 0x8u) != 0u ? 0x2u : 0u;
          } else {
            float rr[4]; _mm_storeu_ps(rr, rv);
            { uint8_t lf;
              if (plain & 8u) lf = ((sgn >> 3) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[3], (double)_mm_cvtss_f32(_mm_shuffle_ps(av, av, _MM_SHUFFLE(3, 3, 3, 3))) + (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(3, 3, 3, 3))) * (double)_mm_cvtss_f32(_mm_shuffle_ps(bv, bv, _MM_SHUFFLE(3, 3, 3, 3))));
              } else {
                uint32_t nf; rr[3] = vu1gen::normResult(rr[3], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[3][lf & 0xFu]; stf |= lf & 0xFu; }
            rvn = _mm_loadu_ps(rr);
          } }
        if (cx.sticky) stk = vu1gen::sticky4(vsv, bv, product, 0x8u);
        cx.pushFmac(c, mac, stf, stk);
        urv = rvn;
      }
      {
        { const int32_t nv = (int32_t)(int16_t)(st.vi[2] | st.vi[3]); bvOld = st.vi[3]; bvReg = 3; st.vi[3] = nv; }
      }
      vu1gen::storeLanes(st.vf[22], urv, 0x1u);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[22] = rt;
        cx.vfR[22][3] = rt;
      }
      cx.viR[3] = (uint32_t)(c + 1u);
      c += 1u;
    }
    L1330:;
    { const bool bt = (int16_t)(bvReg == 10 ? bvOld : st.vi[10]) > 0;
    { // pair 614 pc=0x1330 up=0x01EDA17C lo=0x5A0057D7
      c = vu1gen::vmax(c, cx.vfRAny[20]);
      c = vu1gen::vmax(c, cx.viR[10]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      float ur0 = 0.0f;
      float ur1 = 0.0f;
      float ur2 = 0.0f;
      float ur3 = 0.0f;
      {
        { const int32_t iv = vu1gen::ftoi(vu1gen::nrm(st.vf[20][0]), 1.0f);
          std::memcpy(&ur0, &iv, 4); }
        { const int32_t iv = vu1gen::ftoi(vu1gen::nrm(st.vf[20][1]), 1.0f);
          std::memcpy(&ur1, &iv, 4); }
        { const int32_t iv = vu1gen::ftoi(vu1gen::nrm(st.vf[20][2]), 1.0f);
          std::memcpy(&ur2, &iv, 4); }
        { const int32_t iv = vu1gen::ftoi(vu1gen::nrm(st.vf[20][3]), 1.0f);
          std::memcpy(&ur3, &iv, 4); }
      }
      bvReg = -1;
      st.vf[13][0] = ur0;
      st.vf[13][1] = ur1;
      st.vf[13][2] = ur2;
      st.vf[13][3] = ur3;
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[13] = rt;
        _mm_store_si128((__m128i *)cx.vfR[13], _mm_set1_epi32((int)rt));
      }
      c += 1u;
    }
    { // pair 615 pc=0x1338 up=0x019BCE45 lo=0x0A2367FF
      c = vu1gen::vmax(c, cx.vfR[25][0]);
      c = vu1gen::vmax(c, cx.vfR[25][1]);
      c = vu1gen::vmax(c, cx.vfR[27][1]);
      c = vu1gen::vmax(c, cx.viR[3]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[25]);
        const __m128 bv = vu1gen::nrmbc(st.vf[27], 1);
        const __m128 rv = _mm_sub_ps(vsv, bv);
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
                lf = vu1gen::normExactLane(rr[0], (double)_mm_cvtss_f32(vsv) - (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[0] = vu1gen::normResult(rr[0], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[0][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 2u) lf = ((sgn >> 1) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[1], (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(1, 1, 1, 1))) - (double)_mm_cvtss_f32(bv));
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
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[12] + -1) * 16u) & 0x3FFFu;
          const uint32_t v = (uint32_t)(uint16_t)(st.vi[3] & 0xFFFF);
          cx.markStore(addr);
          std::memcpy(vm + addr + 12u, &v, 4);
        }
      }
      bvReg = -1;
      vu1gen::storeLanes(st.vf[25], urv, 0xCu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[25] = rt;
        cx.vfR[25][0] = rt;
        cx.vfR[25][1] = rt;
      }
      c += 1u;
    }
    if (bt) {
      st.branchTarget = 0x11F0u;
      if (c >= (uint64_t)a.maxCycles) { st.pc = 0x11F0u; goto BUDGET_OUT; }
      goto L11F0;
    } }
    goto LC1340;
    L1338:;
    { // pair 615 pc=0x1338 up=0x019BCE45 lo=0x0A2367FF
      c = vu1gen::vmax(c, cx.vfR[25][0]);
      c = vu1gen::vmax(c, cx.vfR[25][1]);
      c = vu1gen::vmax(c, cx.vfR[27][1]);
      c = vu1gen::vmax(c, cx.viR[3]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      __m128 urv = _mm_setzero_ps();
      {
        const __m128 vsv = vu1gen::nrm4(st.vf[25]);
        const __m128 bv = vu1gen::nrmbc(st.vf[27], 1);
        const __m128 rv = _mm_sub_ps(vsv, bv);
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
                lf = vu1gen::normExactLane(rr[0], (double)_mm_cvtss_f32(vsv) - (double)_mm_cvtss_f32(bv));
              } else {
                uint32_t nf; rr[0] = vu1gen::normResult(rr[0], nf); lf = (uint8_t)nf;
              }
              mac |= vu1gen::kMacScatter.lane[0][lf & 0xFu]; stf |= lf & 0xFu; }
            { uint8_t lf;
              if (plain & 2u) lf = ((sgn >> 1) & 1u) ? 0x2u : 0u;
              else if (cx.exact) {
                lf = vu1gen::normExactLane(rr[1], (double)_mm_cvtss_f32(_mm_shuffle_ps(vsv, vsv, _MM_SHUFFLE(1, 1, 1, 1))) - (double)_mm_cvtss_f32(bv));
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
        { const uint32_t addr = ((uint32_t)(int32_t)(st.vi[12] + -1) * 16u) & 0x3FFFu;
          const uint32_t v = (uint32_t)(uint16_t)(st.vi[3] & 0xFFFF);
          cx.markStore(addr);
          std::memcpy(vm + addr + 12u, &v, 4);
        }
      }
      bvReg = -1;
      vu1gen::storeLanes(st.vf[25], urv, 0xCu);
      { const uint32_t rt = (uint32_t)(c + 4u);
        cx.vfRAny[25] = rt;
        cx.vfR[25][0] = rt;
        cx.vfR[25][1] = rt;
      }
      c += 1u;
    }
    LC1340:;
    L1340:;
    { // pair 616 pc=0x1340 up=0x000002FF lo=0x48002000
      c = vu1gen::vmax(c, cx.viR[4]);
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      {
        jt = ((uint32_t)(uint16_t)(bvReg == 4 ? bvOld : st.vi[4]) * 8u) & 0x3FFFu;
      }
      bvReg = -1;
      c += 1u;
    }
    { // pair 617 pc=0x1348 up=0x000002FF lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    st.branchTarget = jt; goto DISPATCH;
    L1348:;
    { // pair 617 pc=0x1348 up=0x000002FF lo=0x8000033C
      cx.advance(c);
      if (cx.kickInvalid || c >= (uint64_t)a.maxCycles) goto HAND_OUT;
      bvReg = -1;
      c += 1u;
    }
    st.pc = 0x1350u; goto HAND_OUT;

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
    case 0x440u: goto L0440;
    case 0x448u: goto L0448;
    case 0x450u: goto L0450;
    case 0x458u: goto L0458;
    case 0x460u: goto L0460;
    case 0x468u: goto L0468;
    case 0x470u: goto L0470;
    case 0x478u: goto L0478;
    case 0x480u: goto L0480;
    case 0x488u: goto L0488;
    case 0x490u: goto L0490;
    case 0x498u: goto L0498;
    case 0x4A0u: goto L04A0;
    case 0x4A8u: goto L04A8;
    case 0x4B0u: goto L04B0;
    case 0x4B8u: goto L04B8;
    case 0x4C0u: goto L04C0;
    case 0x4C8u: goto L04C8;
    case 0x4D0u: goto L04D0;
    case 0x4D8u: goto L04D8;
    case 0x4E0u: goto L04E0;
    case 0x4E8u: goto L04E8;
    case 0x4F0u: goto L04F0;
    case 0x4F8u: goto L04F8;
    case 0x500u: goto L0500;
    case 0x508u: goto L0508;
    case 0x510u: goto L0510;
    case 0x518u: goto L0518;
    case 0x520u: goto L0520;
    case 0x528u: goto L0528;
    case 0x530u: goto L0530;
    case 0x538u: goto L0538;
    case 0x540u: goto L0540;
    case 0x548u: goto L0548;
    case 0x550u: goto L0550;
    case 0x558u: goto L0558;
    case 0x560u: goto L0560;
    case 0x568u: goto L0568;
    case 0x570u: goto L0570;
    case 0x578u: goto L0578;
    case 0x580u: goto L0580;
    case 0x588u: goto L0588;
    case 0x590u: goto L0590;
    case 0x598u: goto L0598;
    case 0x5A0u: goto L05A0;
    case 0x5A8u: goto L05A8;
    case 0x5B0u: goto L05B0;
    case 0x5B8u: goto L05B8;
    case 0x5C0u: goto L05C0;
    case 0x5C8u: goto L05C8;
    case 0x5D0u: goto L05D0;
    case 0x5D8u: goto L05D8;
    case 0x5E0u: goto L05E0;
    case 0x5E8u: goto L05E8;
    case 0x5F0u: goto L05F0;
    case 0x5F8u: goto L05F8;
    case 0x600u: goto L0600;
    case 0x608u: goto L0608;
    case 0x610u: goto L0610;
    case 0x618u: goto L0618;
    case 0x620u: goto L0620;
    case 0x628u: goto L0628;
    case 0x630u: goto L0630;
    case 0x638u: goto L0638;
    case 0x640u: goto L0640;
    case 0x648u: goto L0648;
    case 0x650u: goto L0650;
    case 0x658u: goto L0658;
    case 0x660u: goto L0660;
    case 0x668u: goto L0668;
    case 0x670u: goto L0670;
    case 0x678u: goto L0678;
    case 0x680u: goto L0680;
    case 0x688u: goto L0688;
    case 0x690u: goto L0690;
    case 0x698u: goto L0698;
    case 0x6A0u: goto L06A0;
    case 0x6A8u: goto L06A8;
    case 0x6B0u: goto L06B0;
    case 0x6B8u: goto L06B8;
    case 0x6C0u: goto L06C0;
    case 0x6C8u: goto L06C8;
    case 0x6D0u: goto L06D0;
    case 0x6D8u: goto L06D8;
    case 0x6E0u: goto L06E0;
    case 0x6E8u: goto L06E8;
    case 0x6F0u: goto L06F0;
    case 0x6F8u: goto L06F8;
    case 0x700u: goto L0700;
    case 0x708u: goto L0708;
    case 0x710u: goto L0710;
    case 0x718u: goto L0718;
    case 0x720u: goto L0720;
    case 0x728u: goto L0728;
    case 0x730u: goto L0730;
    case 0x738u: goto L0738;
    case 0x740u: goto L0740;
    case 0x748u: goto L0748;
    case 0x750u: goto L0750;
    case 0x758u: goto L0758;
    case 0x760u: goto L0760;
    case 0x768u: goto L0768;
    case 0x770u: goto L0770;
    case 0x778u: goto L0778;
    case 0x780u: goto L0780;
    case 0x788u: goto L0788;
    case 0x790u: goto L0790;
    case 0x798u: goto L0798;
    case 0x7A0u: goto L07A0;
    case 0x7A8u: goto L07A8;
    case 0x7B0u: goto L07B0;
    case 0x7B8u: goto L07B8;
    case 0x7C0u: goto L07C0;
    case 0x7C8u: goto L07C8;
    case 0x7D0u: goto L07D0;
    case 0x7D8u: goto L07D8;
    case 0x7E0u: goto L07E0;
    case 0x7E8u: goto L07E8;
    case 0x7F0u: goto L07F0;
    case 0x7F8u: goto L07F8;
    case 0x800u: goto L0800;
    case 0x808u: goto L0808;
    case 0x810u: goto L0810;
    case 0x818u: goto L0818;
    case 0x820u: goto L0820;
    case 0x828u: goto L0828;
    case 0x830u: goto L0830;
    case 0x838u: goto L0838;
    case 0x840u: goto L0840;
    case 0x848u: goto L0848;
    case 0x850u: goto L0850;
    case 0x858u: goto L0858;
    case 0x860u: goto L0860;
    case 0x868u: goto L0868;
    case 0x870u: goto L0870;
    case 0x878u: goto L0878;
    case 0x880u: goto L0880;
    case 0x888u: goto L0888;
    case 0x890u: goto L0890;
    case 0x898u: goto L0898;
    case 0x8A0u: goto L08A0;
    case 0x8A8u: goto L08A8;
    case 0x8B0u: goto L08B0;
    case 0x8B8u: goto L08B8;
    case 0x8C0u: goto L08C0;
    case 0x8C8u: goto L08C8;
    case 0x8D0u: goto L08D0;
    case 0x8D8u: goto L08D8;
    case 0x8E0u: goto L08E0;
    case 0x8E8u: goto L08E8;
    case 0x8F0u: goto L08F0;
    case 0x8F8u: goto L08F8;
    case 0x900u: goto L0900;
    case 0x908u: goto L0908;
    case 0x910u: goto L0910;
    case 0x918u: goto L0918;
    case 0x920u: goto L0920;
    case 0x928u: goto L0928;
    case 0x930u: goto L0930;
    case 0x938u: goto L0938;
    case 0x940u: goto L0940;
    case 0x948u: goto L0948;
    case 0x950u: goto L0950;
    case 0x958u: goto L0958;
    case 0x960u: goto L0960;
    case 0x968u: goto L0968;
    case 0x970u: goto L0970;
    case 0x978u: goto L0978;
    case 0x980u: goto L0980;
    case 0x988u: goto L0988;
    case 0x990u: goto L0990;
    case 0x998u: goto L0998;
    case 0x9A0u: goto L09A0;
    case 0x9A8u: goto L09A8;
    case 0x9B0u: goto L09B0;
    case 0x9B8u: goto L09B8;
    case 0x9C0u: goto L09C0;
    case 0x9C8u: goto L09C8;
    case 0x9D0u: goto L09D0;
    case 0x9D8u: goto L09D8;
    case 0x9E0u: goto L09E0;
    case 0x9E8u: goto L09E8;
    case 0x9F0u: goto L09F0;
    case 0x9F8u: goto L09F8;
    case 0xA00u: goto L0A00;
    case 0xA08u: goto L0A08;
    case 0xA10u: goto L0A10;
    case 0xA18u: goto L0A18;
    case 0xA20u: goto L0A20;
    case 0xA28u: goto L0A28;
    case 0xA30u: goto L0A30;
    case 0xA38u: goto L0A38;
    case 0xA40u: goto L0A40;
    case 0xA48u: goto L0A48;
    case 0xA50u: goto L0A50;
    case 0xA58u: goto L0A58;
    case 0xA60u: goto L0A60;
    case 0xA68u: goto L0A68;
    case 0xA70u: goto L0A70;
    case 0xA78u: goto L0A78;
    case 0xA80u: goto L0A80;
    case 0xA88u: goto L0A88;
    case 0xA90u: goto L0A90;
    case 0xA98u: goto L0A98;
    case 0xAA0u: goto L0AA0;
    case 0xAA8u: goto L0AA8;
    case 0xAB0u: goto L0AB0;
    case 0xAB8u: goto L0AB8;
    case 0xAC0u: goto L0AC0;
    case 0xAC8u: goto L0AC8;
    case 0xAD0u: goto L0AD0;
    case 0xAD8u: goto L0AD8;
    case 0xAE0u: goto L0AE0;
    case 0xAE8u: goto L0AE8;
    case 0xAF0u: goto L0AF0;
    case 0xAF8u: goto L0AF8;
    case 0xB00u: goto L0B00;
    case 0xB08u: goto L0B08;
    case 0xB10u: goto L0B10;
    case 0xB18u: goto L0B18;
    case 0xB20u: goto L0B20;
    case 0xB28u: goto L0B28;
    case 0xB30u: goto L0B30;
    case 0xB38u: goto L0B38;
    case 0xB40u: goto L0B40;
    case 0xB48u: goto L0B48;
    case 0xB50u: goto L0B50;
    case 0xB58u: goto L0B58;
    case 0xB60u: goto L0B60;
    case 0xB68u: goto L0B68;
    case 0xB70u: goto L0B70;
    case 0xB78u: goto L0B78;
    case 0xB80u: goto L0B80;
    case 0xB88u: goto L0B88;
    case 0xB90u: goto L0B90;
    case 0xB98u: goto L0B98;
    case 0xBA0u: goto L0BA0;
    case 0xBA8u: goto L0BA8;
    case 0xBB0u: goto L0BB0;
    case 0xBB8u: goto L0BB8;
    case 0xBC0u: goto L0BC0;
    case 0xBC8u: goto L0BC8;
    case 0xBD0u: goto L0BD0;
    case 0xBD8u: goto L0BD8;
    case 0xBE0u: goto L0BE0;
    case 0xBE8u: goto L0BE8;
    case 0xBF0u: goto L0BF0;
    case 0xBF8u: goto L0BF8;
    case 0xC00u: goto L0C00;
    case 0xC08u: goto L0C08;
    case 0xC10u: goto L0C10;
    case 0xC18u: goto L0C18;
    case 0xC20u: goto L0C20;
    case 0xC28u: goto L0C28;
    case 0xC30u: goto L0C30;
    case 0xC38u: goto L0C38;
    case 0xC40u: goto L0C40;
    case 0xC48u: goto L0C48;
    case 0xC50u: goto L0C50;
    case 0xC58u: goto L0C58;
    case 0xC60u: goto L0C60;
    case 0xC68u: goto L0C68;
    case 0xC70u: goto L0C70;
    case 0xC78u: goto L0C78;
    case 0xC80u: goto L0C80;
    case 0xC88u: goto L0C88;
    case 0xC90u: goto L0C90;
    case 0xC98u: goto L0C98;
    case 0xCA0u: goto L0CA0;
    case 0xCA8u: goto L0CA8;
    case 0xCB0u: goto L0CB0;
    case 0xCB8u: goto L0CB8;
    case 0xCC0u: goto L0CC0;
    case 0xCC8u: goto L0CC8;
    case 0xCD0u: goto L0CD0;
    case 0xCD8u: goto L0CD8;
    case 0xCE0u: goto L0CE0;
    case 0xCE8u: goto L0CE8;
    case 0xCF0u: goto L0CF0;
    case 0xCF8u: goto L0CF8;
    case 0xD00u: goto L0D00;
    case 0xD08u: goto L0D08;
    case 0xD10u: goto L0D10;
    case 0xD18u: goto L0D18;
    case 0xD20u: goto L0D20;
    case 0xD28u: goto L0D28;
    case 0xD30u: goto L0D30;
    case 0xD38u: goto L0D38;
    case 0xD40u: goto L0D40;
    case 0xD48u: goto L0D48;
    case 0xD50u: goto L0D50;
    case 0xD58u: goto L0D58;
    case 0xD60u: goto L0D60;
    case 0xD68u: goto L0D68;
    case 0xD70u: goto L0D70;
    case 0xD78u: goto L0D78;
    case 0xD80u: goto L0D80;
    case 0xD88u: goto L0D88;
    case 0xD90u: goto L0D90;
    case 0xD98u: goto L0D98;
    case 0xDA0u: goto L0DA0;
    case 0xDA8u: goto L0DA8;
    case 0xDB0u: goto L0DB0;
    case 0xDB8u: goto L0DB8;
    case 0xDC0u: goto L0DC0;
    case 0xDC8u: goto L0DC8;
    case 0xDD0u: goto L0DD0;
    case 0xDD8u: goto L0DD8;
    case 0xDE0u: goto L0DE0;
    case 0xDE8u: goto L0DE8;
    case 0xDF0u: goto L0DF0;
    case 0xDF8u: goto L0DF8;
    case 0xE00u: goto L0E00;
    case 0xE08u: goto L0E08;
    case 0xE10u: goto L0E10;
    case 0xE18u: goto L0E18;
    case 0xE20u: goto L0E20;
    case 0xE28u: goto L0E28;
    case 0xE30u: goto L0E30;
    case 0xE38u: goto L0E38;
    case 0xE40u: goto L0E40;
    case 0xE48u: goto L0E48;
    case 0xE50u: goto L0E50;
    case 0xE58u: goto L0E58;
    case 0xE60u: goto L0E60;
    case 0xE68u: goto L0E68;
    case 0xE70u: goto L0E70;
    case 0xE78u: goto L0E78;
    case 0xE80u: goto L0E80;
    case 0xE88u: goto L0E88;
    case 0xE90u: goto L0E90;
    case 0xE98u: goto L0E98;
    case 0xEA0u: goto L0EA0;
    case 0xEA8u: goto L0EA8;
    case 0xEB0u: goto L0EB0;
    case 0xEB8u: goto L0EB8;
    case 0xEC0u: goto L0EC0;
    case 0xEC8u: goto L0EC8;
    case 0xED0u: goto L0ED0;
    case 0xED8u: goto L0ED8;
    case 0xEE0u: goto L0EE0;
    case 0xEE8u: goto L0EE8;
    case 0xEF0u: goto L0EF0;
    case 0xEF8u: goto L0EF8;
    case 0xF00u: goto L0F00;
    case 0xF08u: goto L0F08;
    case 0xF10u: goto L0F10;
    case 0xF18u: goto L0F18;
    case 0xF20u: goto L0F20;
    case 0xF28u: goto L0F28;
    case 0xF30u: goto L0F30;
    case 0xF38u: goto L0F38;
    case 0xF40u: goto L0F40;
    case 0xF48u: goto L0F48;
    case 0xF50u: goto L0F50;
    case 0xF58u: goto L0F58;
    case 0xF60u: goto L0F60;
    case 0xF68u: goto L0F68;
    case 0xF70u: goto L0F70;
    case 0xF78u: goto L0F78;
    case 0xF80u: goto L0F80;
    case 0xF88u: goto L0F88;
    case 0xF90u: goto L0F90;
    case 0xF98u: goto L0F98;
    case 0xFA0u: goto L0FA0;
    case 0xFA8u: goto L0FA8;
    case 0xFB0u: goto L0FB0;
    case 0xFB8u: goto L0FB8;
    case 0xFC0u: goto L0FC0;
    case 0xFC8u: goto L0FC8;
    case 0xFD0u: goto L0FD0;
    case 0xFD8u: goto L0FD8;
    case 0xFE0u: goto L0FE0;
    case 0xFE8u: goto L0FE8;
    case 0xFF0u: goto L0FF0;
    case 0xFF8u: goto L0FF8;
    case 0x1000u: goto L1000;
    case 0x1008u: goto L1008;
    case 0x1010u: goto L1010;
    case 0x1018u: goto L1018;
    case 0x1020u: goto L1020;
    case 0x1028u: goto L1028;
    case 0x1030u: goto L1030;
    case 0x1038u: goto L1038;
    case 0x1040u: goto L1040;
    case 0x1048u: goto L1048;
    case 0x1050u: goto L1050;
    case 0x1058u: goto L1058;
    case 0x1060u: goto L1060;
    case 0x1068u: goto L1068;
    case 0x1070u: goto L1070;
    case 0x1078u: goto L1078;
    case 0x1080u: goto L1080;
    case 0x1088u: goto L1088;
    case 0x1090u: goto L1090;
    case 0x1098u: goto L1098;
    case 0x10A0u: goto L10A0;
    case 0x10A8u: goto L10A8;
    case 0x10B0u: goto L10B0;
    case 0x10B8u: goto L10B8;
    case 0x10C0u: goto L10C0;
    case 0x10C8u: goto L10C8;
    case 0x10D0u: goto L10D0;
    case 0x10D8u: goto L10D8;
    case 0x10E0u: goto L10E0;
    case 0x10E8u: goto L10E8;
    case 0x10F0u: goto L10F0;
    case 0x10F8u: goto L10F8;
    case 0x1100u: goto L1100;
    case 0x1108u: goto L1108;
    case 0x1110u: goto L1110;
    case 0x1118u: goto L1118;
    case 0x1120u: goto L1120;
    case 0x1128u: goto L1128;
    case 0x1130u: goto L1130;
    case 0x1138u: goto L1138;
    case 0x1140u: goto L1140;
    case 0x1148u: goto L1148;
    case 0x1150u: goto L1150;
    case 0x1158u: goto L1158;
    case 0x1160u: goto L1160;
    case 0x1168u: goto L1168;
    case 0x1170u: goto L1170;
    case 0x1178u: goto L1178;
    case 0x1180u: goto L1180;
    case 0x1188u: goto L1188;
    case 0x1190u: goto L1190;
    case 0x1198u: goto L1198;
    case 0x11A0u: goto L11A0;
    case 0x11A8u: goto L11A8;
    case 0x11B0u: goto L11B0;
    case 0x11B8u: goto L11B8;
    case 0x11C0u: goto L11C0;
    case 0x11C8u: goto L11C8;
    case 0x11D0u: goto L11D0;
    case 0x11D8u: goto L11D8;
    case 0x11E0u: goto L11E0;
    case 0x11E8u: goto L11E8;
    case 0x11F0u: goto L11F0;
    case 0x11F8u: goto L11F8;
    case 0x1200u: goto L1200;
    case 0x1208u: goto L1208;
    case 0x1210u: goto L1210;
    case 0x1218u: goto L1218;
    case 0x1220u: goto L1220;
    case 0x1228u: goto L1228;
    case 0x1230u: goto L1230;
    case 0x1238u: goto L1238;
    case 0x1240u: goto L1240;
    case 0x1248u: goto L1248;
    case 0x1250u: goto L1250;
    case 0x1258u: goto L1258;
    case 0x1260u: goto L1260;
    case 0x1268u: goto L1268;
    case 0x1270u: goto L1270;
    case 0x1278u: goto L1278;
    case 0x1280u: goto L1280;
    case 0x1288u: goto L1288;
    case 0x1290u: goto L1290;
    case 0x1298u: goto L1298;
    case 0x12A0u: goto L12A0;
    case 0x12A8u: goto L12A8;
    case 0x12B0u: goto L12B0;
    case 0x12B8u: goto L12B8;
    case 0x12C0u: goto L12C0;
    case 0x12C8u: goto L12C8;
    case 0x12D0u: goto L12D0;
    case 0x12D8u: goto L12D8;
    case 0x12E0u: goto L12E0;
    case 0x12E8u: goto L12E8;
    case 0x12F0u: goto L12F0;
    case 0x12F8u: goto L12F8;
    case 0x1300u: goto L1300;
    case 0x1308u: goto L1308;
    case 0x1310u: goto L1310;
    case 0x1318u: goto L1318;
    case 0x1320u: goto L1320;
    case 0x1328u: goto L1328;
    case 0x1330u: goto L1330;
    case 0x1338u: goto L1338;
    case 0x1340u: goto L1340;
    case 0x1348u: goto L1348;
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
