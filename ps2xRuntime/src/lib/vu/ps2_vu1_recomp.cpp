#include "ps2_vu1_recomp.h"
#include "runtime/gs/gs_frontend.h"
#include "runtime/gs/ps2_gif_arbiter.h"
#include "runtime/ps2_memory.h"
#include <array>
#include <bit>
#include <cfenv>
#include <vector>
uint64_t *ps2Vu1DataDirtyWords() {
  static thread_local uint64_t dirty[16]{};
  return dirty;
}
namespace {
struct Packets {
  std::vector<uint8_t> bytes;
  std::vector<uint32_t> sizes;
  bool active = false, overflow = false;
};
thread_local Packets packets;
void emit(GS *gs, PS2Memory *mem, const uint8_t *p, uint32_t n) {
  if (mem)
    mem->submitGifPacket(GifPathId::Path1, p, n);
  else if (gs)
    gs->processGIFPacket(p, n);
}
} // namespace
void ps2Vu1EmitKick(GS *gs, PS2Memory *mem, const uint8_t *p, uint32_t n) {
  if (!packets.active) {
    emit(gs, mem, p, n);
    return;
  }
  if (packets.bytes.size() + n > 4u * 1024u * 1024u) {
    packets.overflow = true;
    return;
  }
  packets.bytes.insert(packets.bytes.end(), p, p + n);
  packets.sizes.push_back(n);
}
extern int ps2Vu1Prog_4F9E7E58F7514FFB(Vu1ProgArgs &);
extern int ps2Vu1Prog_082E98435EDBA5AF(Vu1ProgArgs &);
extern int ps2Vu1Prog_A6B7CEEB0D61CE07(Vu1ProgArgs &);
extern int ps2Vu1Prog_F94A7D89E2026153(Vu1ProgArgs &);
extern int ps2Vu1Prog_185EAD24A713EAD1(Vu1ProgArgs &);
extern int ps2Vu1Prog_A0DCD4A134308539(Vu1ProgArgs &);
extern int ps2Vu1Prog_459DB7696A445705(Vu1ProgArgs &);
extern int ps2Vu1Prog_D22B626A059765FF(Vu1ProgArgs &);
extern int ps2Vu0Prog_3C3413D987B6A568(Vu1ProgArgs &);
extern int ps2Vu0Prog_2B80CC53B8E362D4(Vu1ProgArgs &);
extern int ps2Vu0Prog_A8705453F47F3C96(Vu1ProgArgs &);
extern int ps2Vu0Prog_1C26D35874EA765E(Vu1ProgArgs &);
extern int ps2Vu0Prog_E732734F0A4A8CD0(Vu1ProgArgs &);
extern int ps2Vu1Prog_513B4D4A44BE8C92(Vu1ProgArgs &);
extern int ps2Vu1Prog_9E7358D59E4B91BD(Vu1ProgArgs &);
extern int ps2Vu1Prog_8256F19A5156869B(Vu1ProgArgs &);
extern int ps2Vu1Prog_44AE735583C51F39(Vu1ProgArgs &);
extern int ps2Vu1Prog_CFD3D978B248B60E(Vu1ProgArgs &);
extern int ps2Vu1Prog_E9FDDA9470B1C49D(Vu1ProgArgs &);
extern int ps2Vu1Prog_0E76D1215C4890A1(Vu1ProgArgs &);
extern int ps2Vu1Prog_2CDC6FC2E953DA70(Vu1ProgArgs &);
extern int ps2Vu1Prog_F6F59A7CA24D0605(Vu1ProgArgs &);
extern int ps2Vu1Prog_4E770661A2A4C3E4(Vu1ProgArgs &);
extern int ps2Vu1Prog_4851692F3FF97E90(Vu1ProgArgs &);
extern int ps2Vu1Prog_D165F689BA814B6E(Vu1ProgArgs &);
extern int ps2Vu1Prog_771C5887BF6ED35F(Vu1ProgArgs &);
extern int ps2Vu1Prog_5314E660A37CD9A5(Vu1ProgArgs &);
extern int ps2Vu1Prog_31522B545E41B7B3(Vu1ProgArgs &);
extern int ps2Vu1Prog_F291B505E69410EE(Vu1ProgArgs &);
extern int ps2Vu1Prog_1D4E7DA313168DDA(Vu1ProgArgs &);
extern int ps2Vu1Prog_C26A3EBF7398F617(Vu1ProgArgs &);
extern int ps2Vu1Prog_661D54E7686D8699(Vu1ProgArgs &);
extern int ps2Vu1Prog_98DC28D14BC35AD1(Vu1ProgArgs &);
extern int ps2Vu1Prog_D276A08578EDE61C(Vu1ProgArgs &);
int ps2Vu1TryRunCompiled(const uint8_t *code, VU1State &state, uint8_t *data,
                         uint32_t size, GS &gs, PS2Memory *mem, uint32_t start,
                         uint32_t top, uint32_t itop, uint32_t maxCycles,
                         int32_t &branchReg, int32_t &branchOld) {
  if (!code || !data || (size != 16384 && size != 4096) || !maxCycles ||
      state.cycles > UINT64_MAX - maxCycles || packets.active)
    return 0;
  struct P {
    uint64_t hash;
    unsigned size;
    Vu1ProgFn fn;
    unsigned dataSize;
  };
  static constexpr P table[] = {
      {0x3C3413D987B6A568ull, 752u, &ps2Vu0Prog_3C3413D987B6A568, 4096},
      {0x2B80CC53B8E362D4ull, 776u, &ps2Vu0Prog_2B80CC53B8E362D4, 4096},
      {0xA8705453F47F3C96ull, 776u, &ps2Vu0Prog_A8705453F47F3C96, 4096},
      {0x1C26D35874EA765Eull, 776u, &ps2Vu0Prog_1C26D35874EA765E, 4096},
      {0xE732734F0A4A8CD0ull, 736u, &ps2Vu0Prog_E732734F0A4A8CD0, 4096},

      {0xF94A7D89E2026153ull, 4992u, &ps2Vu1Prog_F94A7D89E2026153, 16384},
      {0x185EAD24A713EAD1ull, 4992u, &ps2Vu1Prog_185EAD24A713EAD1, 16384},
      {0xA0DCD4A134308539ull, 4992u, &ps2Vu1Prog_A0DCD4A134308539, 16384},
      {0x459DB7696A445705ull, 4992u, &ps2Vu1Prog_459DB7696A445705, 16384},
      {0xD22B626A059765FFull, 4992u, &ps2Vu1Prog_D22B626A059765FF, 16384},
      {0x8256F19A5156869Bull, 4992u, &ps2Vu1Prog_8256F19A5156869B, 16384},
      {0x44AE735583C51F39ull, 4992u, &ps2Vu1Prog_44AE735583C51F39, 16384},
      {0xCFD3D978B248B60Eull, 4992u, &ps2Vu1Prog_CFD3D978B248B60E, 16384},
      {0xE9FDDA9470B1C49Dull, 4992u, &ps2Vu1Prog_E9FDDA9470B1C49D, 16384},
      {0x0E76D1215C4890A1ull, 4992u, &ps2Vu1Prog_0E76D1215C4890A1, 16384},
      {0x2CDC6FC2E953DA70ull, 4992u, &ps2Vu1Prog_2CDC6FC2E953DA70, 16384},
      {0xF6F59A7CA24D0605ull, 4992u, &ps2Vu1Prog_F6F59A7CA24D0605, 16384},
      {0x4E770661A2A4C3E4ull, 4992u, &ps2Vu1Prog_4E770661A2A4C3E4, 16384},
      {0x4851692F3FF97E90ull, 4992u, &ps2Vu1Prog_4851692F3FF97E90, 16384},
      {0xD165F689BA814B6Eull, 4992u, &ps2Vu1Prog_D165F689BA814B6E, 16384},
      {0x771C5887BF6ED35Full, 4992u, &ps2Vu1Prog_771C5887BF6ED35F, 16384},
      {0x5314E660A37CD9A5ull, 4992u, &ps2Vu1Prog_5314E660A37CD9A5, 16384},
      {0x31522B545E41B7B3ull, 4992u, &ps2Vu1Prog_31522B545E41B7B3, 16384},
      {0xF291B505E69410EEull, 4992u, &ps2Vu1Prog_F291B505E69410EE, 16384},
      {0x1D4E7DA313168DDAull, 4992u, &ps2Vu1Prog_1D4E7DA313168DDA, 16384},
      {0xC26A3EBF7398F617ull, 4992u, &ps2Vu1Prog_C26A3EBF7398F617, 16384},
      {0x661D54E7686D8699ull, 4992u, &ps2Vu1Prog_661D54E7686D8699, 16384},
      {0x98DC28D14BC35AD1ull, 4992u, &ps2Vu1Prog_98DC28D14BC35AD1, 16384},
      {0xD276A08578EDE61Cull, 4992u, &ps2Vu1Prog_D276A08578EDE61C, 16384},
      {0xA6B7CEEB0D61CE07ull, 4944u, &ps2Vu1Prog_A6B7CEEB0D61CE07, 16384},
      {0x082E98435EDBA5AFull, 4856u, &ps2Vu1Prog_082E98435EDBA5AF, 16384},
      {0x9E7358D59E4B91BDull, 4856u, &ps2Vu1Prog_9E7358D59E4B91BD, 16384},
      {0x513B4D4A44BE8C92ull, 1088u, &ps2Vu1Prog_513B4D4A44BE8C92, 16384},
      {0x4F9E7E58F7514FFBull, 704u, &ps2Vu1Prog_4F9E7E58F7514FFB, 16384},
  };
  static constexpr auto codeSizes = [] {
    std::array<unsigned, 2> sizes{};
    for (const auto &p : table) {
      auto &length = sizes[p.dataSize == 16384];
      if (p.size > length) length = p.size;
    }
    return sizes;
  }();
  const unsigned codeSize = codeSizes[size == 16384];
  struct Cache {
    std::array<uint8_t, 16384> previous{};
    const P *selected = nullptr;
    bool valid = false;
  };
  static thread_local Cache caches[2];
  static thread_local std::array<uint8_t, 16384> undo{};
  auto &[previous, selected, valid] = caches[size == 16384];
  if (!valid || std::memcmp(previous.data(), code, codeSize)) {
    std::memcpy(previous.data(), code, codeSize);
    valid = true;
    selected = nullptr;
    uint64_t hash = 0;
    unsigned length = 0;
    for (auto &p : table) {
      if (p.dataSize != size) continue;
      if (p.size != length) {
        length = p.size;
        hash = 0xcbf29ce484222325ull;
        for (unsigned i = 0; i < p.size; ++i)
          hash = (hash ^ code[i]) * 0x100000001b3ull;
      }
      if (hash == p.hash) {
        selected = &p;
        break;
      }
    }
  }
  if (!selected) {
    return 0;
  }
  // Commit only completed programs; the undo journal restores memory on hand-off.
  VU1State working;
  std::memcpy(&working, &state, sizeof(working));
  auto *dirty = ps2Vu1DataDirtyWords();
  std::fill(dirty, dirty + 16, 0);
  packets.bytes.clear();
  packets.sizes.clear();
  packets.overflow = false;
  struct CaptureGuard {
    CaptureGuard() { packets.active = true; }
    ~CaptureGuard() { packets.active = false; }
  } capture;

  struct Transaction {
    uint8_t *data, *undo;
    uint64_t *dirty;
    bool committed = false;
    ~Transaction() {
      if (!committed)
        for (unsigned word = 0; word < 16; ++word)
          for (uint64_t bits = dirty[word]; bits; bits &= bits - 1) {
            unsigned off = (word * 64 + std::countr_zero(bits)) * 16;
            std::memcpy(data + off, undo + off, 16);
          }
    }
  } transaction{data, undo.data(), dirty};
  Vu1ProgArgs args{&working, data, size, &gs, mem, start,
                   top, itop, maxCycles};
  args.undo = undo.data();
  struct Rounding {
    int previous = std::fegetround();
    Rounding() { std::fesetround(FE_TOWARDZERO); }
    ~Rounding() {
      if (previous != -1)
        std::fesetround(previous);
    }
  };
  int rc;
  {
    Rounding rounding;
    rc = selected->fn(args);
  }
  if (rc != kVu1ProgRan || packets.overflow) {
    return 0;
  }
  std::memcpy(&state, &working, sizeof(state));
  transaction.committed = true;
  size_t offset = 0;
  for (uint32_t n : packets.sizes) {
    emit(&gs, mem, packets.bytes.data() + offset, n);
    offset += n;
  }
  branchReg = args.branchReg;
  branchOld = args.branchOld;
  return 1;
}
