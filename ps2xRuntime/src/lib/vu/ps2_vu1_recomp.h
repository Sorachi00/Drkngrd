#ifndef PS2_VU1_RECOMP_H
#define PS2_VU1_RECOMP_H

#include "runtime/ps2_vu1.h"

#include <cmath>
#include <cstdint>
#include <cstring>
#include <emmintrin.h>
#include <limits>
#include <smmintrin.h>

class GS;
class PS2Memory;

struct Vu1ProgArgs {
  VU1State *state = nullptr;
  uint8_t *vuData = nullptr;
  uint32_t dataSize = 0;
  GS *gs = nullptr;
  PS2Memory *memory = nullptr;
  uint32_t startPC = 0;
  uint32_t top = 0;
  uint32_t itop = 0;
  uint32_t maxCycles = 65536;
  int32_t branchReg = -1, branchOld = 0;
  uint8_t *undo = nullptr;
};

enum : int {
  kVu1ProgNoEntry = 0,
  kVu1ProgRan = 1,
  kVu1ProgHandOff = 2,
};

using Vu1ProgFn = int (*)(Vu1ProgArgs &);

void ps2Vu1EmitKick(GS *gs, PS2Memory *memory, const uint8_t *packet,
                    uint32_t totalBytes);
uint64_t *ps2Vu1DataDirtyWords();

namespace vu1gen {

struct MacScatter {
  uint16_t lane[4][16];
  constexpr MacScatter() : lane{} {
    for (uint32_t c = 0; c < 4u; ++c)
      for (uint32_t f = 0; f < 16u; ++f) {
        uint16_t word = 0u;
        for (uint32_t k = 0; k < 4u; ++k)
          if ((f >> k) & 1u)
            word |= static_cast<uint16_t>(1u << (k * 4u + (3u - c)));
        lane[c][f] = word;
      }
  }
};
inline constexpr MacScatter kMacScatter{};

struct MacSignScatter {
  uint16_t word[16];
  constexpr MacSignScatter() : word{} {
    for (uint32_t m = 0; m < 16u; ++m) {
      uint16_t v = 0u;
      for (uint32_t c = 0; c < 4u; ++c)
        if ((m >> c) & 1u)
          v |= static_cast<uint16_t>(1u << (4u + (3u - c)));
      word[m] = v;
    }
  }
};
inline constexpr MacSignScatter kMacSign{};

inline __m128 nrm4(const float *src) {
  const __m128i bits = _mm_loadu_si128(reinterpret_cast<const __m128i *>(src));
  const __m128i sign =
      _mm_and_si128(bits, _mm_set1_epi32(static_cast<int>(0x80000000u)));
  __m128i magnitude = _mm_and_si128(bits, _mm_set1_epi32(0x7FFFFFFF));
  magnitude = _mm_min_epi32(magnitude, _mm_set1_epi32(0x7F7FFFFF));
  const __m128i normal = _mm_cmpgt_epi32(magnitude, _mm_set1_epi32(0x007FFFFF));
  return _mm_castsi128_ps(_mm_or_si128(sign, _mm_and_si128(magnitude, normal)));
}

inline __m128 nrmbc(const float *src, int lane) {
  const __m128 v = nrm4(src);
  switch (lane) {
  case 0:
    return _mm_shuffle_ps(v, v, _MM_SHUFFLE(0, 0, 0, 0));
  case 1:
    return _mm_shuffle_ps(v, v, _MM_SHUFFLE(1, 1, 1, 1));
  case 2:
    return _mm_shuffle_ps(v, v, _MM_SHUFFLE(2, 2, 2, 2));
  default:
    return _mm_shuffle_ps(v, v, _MM_SHUFFLE(3, 3, 3, 3));
  }
}

inline uint32_t classify4(__m128 r, uint32_t &signBits) {
  const __m128i bits = _mm_castps_si128(r);
  const __m128i magnitude = _mm_and_si128(bits, _mm_set1_epi32(0x7FFFFFFF));
  const __m128i low = _mm_cmplt_epi32(magnitude, _mm_set1_epi32(0x00800000));
  const __m128i high = _mm_cmpgt_epi32(magnitude, _mm_set1_epi32(0x7F7FFFFE));
  const __m128i special = _mm_or_si128(low, high);
  signBits = static_cast<uint32_t>(_mm_movemask_ps(r));
  return static_cast<uint32_t>(_mm_movemask_ps(_mm_castsi128_ps(special))) ^
         0xFu;
}

inline float nrm(float value) {
  uint32_t bits = 0;
  std::memcpy(&bits, &value, sizeof(bits));
  const uint32_t sign = bits & 0x80000000u;
  const uint32_t magnitude = bits & 0x7FFFFFFFu;
  const uint32_t capped = magnitude > 0x7F7FFFFFu ? 0x7F7FFFFFu : magnitude;
  bits = sign | (magnitude < 0x00800000u ? 0u : capped);
  std::memcpy(&value, &bits, sizeof(value));
  return value;
}

#if defined(_MSC_VER)
__forceinline
#else
inline
#endif
void storeLanes(float *dst, __m128 v, uint32_t mask) {
  if (mask == 0xFu) {
    _mm_storeu_ps(dst, v);
    return;
  }
  if (mask & 0xCu) {
    if ((mask & 0xCu) == 0xCu)
      _mm_store_sd(reinterpret_cast<double *>(dst), _mm_castps_pd(v));
    else if (mask & 0x8u)
      _mm_store_ss(dst, v);
    else
      _mm_store_ss(dst + 1, _mm_shuffle_ps(v, v, _MM_SHUFFLE(1, 1, 1, 1)));
  }
  if (mask & 0x3u) {
    if ((mask & 0x3u) == 0x3u)
      _mm_storeh_pd(reinterpret_cast<double *>(dst + 2), _mm_castps_pd(v));
    else if (mask & 0x2u)
      _mm_store_ss(dst + 2, _mm_movehl_ps(v, v));
    else
      _mm_store_ss(dst + 3, _mm_shuffle_ps(v, v, _MM_SHUFFLE(3, 3, 3, 3)));
  }
}

inline float normResult(float value, uint32_t &laneFlags) {
  uint32_t bits = 0;
  std::memcpy(&bits, &value, sizeof(bits));
  const uint32_t sign = bits & 0x80000000u;
  const uint32_t magnitude = bits & 0x7FFFFFFFu;
  const uint32_t exponent = (bits >> 23) & 0xFFu;
  laneFlags = sign != 0u ? 0x2u : 0u;
  if (magnitude == 0u)
    laneFlags |= 0x1u;
  else if (exponent == 0u) {
    laneFlags |= 0x5u;
    bits = sign;
  } else if (exponent == 0xFFu) {
    laneFlags |= 0x8u;
    bits = sign | 0x7F7FFFFFu;
  }
  std::memcpy(&value, &bits, sizeof(value));
  return value;
}

inline uint8_t normExactLane(float &value, double exact) {
  const bool negative = std::signbit(exact);
  const double magnitude = std::fabs(exact);
  const double maximum = static_cast<double>(std::numeric_limits<float>::max());
  const double minimum = static_cast<double>(std::numeric_limits<float>::min());
  uint8_t flags = negative ? 0x2u : 0u;
  uint32_t bits = negative ? 0x80000000u : 0u;
  if (magnitude == 0.0) {
    flags |= 0x1u;
    std::memcpy(&value, &bits, sizeof(value));
  } else if (magnitude > maximum) {
    flags |= 0x8u;
    bits |= 0x7F7FFFFFu;
    std::memcpy(&value, &bits, sizeof(value));
  } else if (magnitude < minimum) {
    flags |= 0x5u;
    std::memcpy(&value, &bits, sizeof(value));
  }
  return flags;
}

inline bool lanePlain(float value, uint8_t &flags) {
  uint32_t bits = 0;
  std::memcpy(&bits, &value, sizeof(bits));
  const uint32_t exponent = (bits >> 23) & 0xFFu;
  const uint32_t magnitude = bits & 0x7FFFFFFFu;
  if (exponent != 0u && exponent != 0xFFu && magnitude != 0x7F7FFFFFu) {
    flags = (bits >> 31) != 0u ? 0x2u : 0u;
    return true;
  }
  return false;
}

inline uint8_t stickyLane(float leftLane, float rightLane) {
  float product = leftLane * rightLane;
  uint8_t flags = 0u;
  if (lanePlain(product, flags))
    return flags & 0x2u;
  return normExactLane(product, static_cast<double>(leftLane) *
                                    static_cast<double>(rightLane)) &
         0xFu;
}

// Inputs have already passed VU normalization. Reuse their SIMD product.
inline uint32_t sticky4(__m128 left, __m128 right, __m128 product,
                        uint32_t lanes) {
  const __m128i absMask = _mm_set1_epi32(0x7FFFFFFF);
  const __m128i magnitude = _mm_and_si128(_mm_castps_si128(product), absMask);
  uint32_t flags = (uint32_t(_mm_movemask_ps(product)) & lanes) ? 2u : 0u;
  const uint32_t small = uint32_t(_mm_movemask_ps(_mm_castsi128_ps(
      _mm_cmplt_epi32(magnitude, _mm_set1_epi32(0x00800000))))) & lanes;
  if (small) {
    const __m128i zero = _mm_setzero_si128();
    const __m128i zeroInput = _mm_or_si128(
        _mm_cmpeq_epi32(_mm_and_si128(_mm_castps_si128(left), absMask), zero),
        _mm_cmpeq_epi32(_mm_and_si128(_mm_castps_si128(right), absMask), zero));
    flags |= 1u;
    if (small & ~uint32_t(_mm_movemask_ps(_mm_castsi128_ps(zeroInput))))
      flags |= 4u;
  }
  uint32_t saturated = uint32_t(_mm_movemask_ps(_mm_castsi128_ps(
      _mm_cmpgt_epi32(magnitude, _mm_set1_epi32(0x7F7FFFFE))))) & lanes;
  if (saturated) {
    float lhs[4], rhs[4];
    _mm_storeu_ps(lhs, left);
    _mm_storeu_ps(rhs, right);
    for (unsigned lane = 0; lane < 4; ++lane)
      if (saturated & (1u << lane))
        flags |= stickyLane(lhs[lane], rhs[lane]);
  }
  return flags;
}

inline int32_t ftoi(float value, float scale) {
  if (std::isnan(value)) {
    return 0;
  }
  const double scaled = static_cast<double>(value) * static_cast<double>(scale);
  if (scaled >= static_cast<double>(std::numeric_limits<int32_t>::max())) {
    return std::numeric_limits<int32_t>::max();
  }
  if (scaled <= static_cast<double>(std::numeric_limits<int32_t>::min())) {
    return std::numeric_limits<int32_t>::min();
  }
  return static_cast<int32_t>(scaled);
}

struct FlagEntry {
  uint64_t ready;
  uint32_t mac;
  uint32_t status;
  uint32_t sticky;
  uint32_t clip;
  uint8_t kind;
};

struct RunCtx {
  alignas(16) uint32_t vfR[32][4];
  uint32_t vfRAny[32];
  uint32_t viR[16];
  FlagEntry ring[64];
  uint32_t head;
  uint32_t count;
  bool qValid;
  uint64_t qReady;
  float qVal;
  uint32_t qDi;
  uint8_t *vm = nullptr, *kickBuffer = nullptr, *undo = nullptr;
  GS *gs = nullptr;
  PS2Memory *memory = nullptr;
  uint64_t kickNext = 0;
  uint32_t kickSource = 0, kickCopied = 0, kickTagEnd = 0;
  bool kickActive = false, kickEop = false, kickInvalid = false;
  uint32_t workingClip;
  bool exact;
  bool sticky;
  uint64_t *dirty;
  VU1State *st;

  void init(VU1State &state, bool exactMode, bool stickyMode) {
    std::memset(vfR, 0, sizeof(vfR));
    std::memset(vfRAny, 0, sizeof(vfRAny));
    std::memset(viR, 0, sizeof(viR));
    head = 0;
    count = 0;
    qValid = false;
    qReady = 0;
    qVal = 0.0f;
    qDi = 0;
    kickActive = kickInvalid = false;
    workingClip = state.clip;
    exact = exactMode;
    sticky = stickyMode;
    dirty = ps2Vu1DataDirtyWords();
    st = &state;
  }

  void drainFlags(uint64_t c) {
    while (count != 0u) {
      FlagEntry &e = ring[head];
      if (e.ready > c)
        break;
      head = (head + 1u) & 63u;
      --count;
      if (e.kind == 1u) {
        st->mac = e.mac;
        const uint32_t current = e.status & 0xFu;
        st->status =
            (st->status & 0xFF0u) | current | ((current | e.sticky) << 6);
      } else if (e.kind == 2u) {
        st->clip = e.clip;
      } else {
        st->status = (st->status & 0x03Fu) | (e.status & 0xFC0u);
      }
    }
  }

  void pushFmac(uint64_t c, uint32_t mac, uint32_t status,
                uint32_t stickyBits) {
    if (count >= 64u)
      drainFlags(c);
    if (count >= 64u)
      return;
    FlagEntry &e = ring[(head + count) & 63u];
    ++count;
    e.ready = c + 4u;
    e.mac = mac;
    e.status = status;
    e.sticky = stickyBits;
    e.kind = 1u;
  }

  void pushClip(uint64_t c, uint32_t clipValue) {
    if (count >= 64u)
      drainFlags(c);
    if (count >= 64u)
      return;
    FlagEntry &e = ring[(head + count) & 63u];
    ++count;
    e.ready = c + 4u;
    e.clip = clipValue;
    e.kind = 2u;
  }

  void commitQ(uint64_t c) {
    if (qValid && qReady <= c) {
      st->q = qVal;
      const uint32_t di = qDi & 0x30u;
      st->status = (st->status & 0xFCFu) | di | (di << 6);
      qValid = false;
    }
  }

  void advanceKick(uint64_t c) {
    while (kickActive && kickNext <= c) {
      if (kickCopied > 65536u - 16u) {
        kickActive = false;
        kickInvalid = true;
        return;
      }
      const uint32_t offset = kickCopied;
      std::memcpy(kickBuffer + offset, vm + ((kickSource + offset) & 16383u),
                  16u);
      kickCopied += 16u;
      kickNext += 2u;
      if (!kickTagEnd) {
        uint64_t tag;
        std::memcpy(&tag, kickBuffer + offset, 8);
        const uint32_t loops = tag & 32767u, format = (tag >> 58) & 3u;
        uint32_t regs = (tag >> 60) & 15u;
        if (!regs)
          regs = 16;
        uint64_t bytes = 16;
        if (format == 0)
          bytes += uint64_t(loops) * regs * 16;
        else if (format == 1)
          bytes += ((uint64_t(loops) * regs + 1) & ~1ull) * 8;
        else if (format == 2)
          bytes += uint64_t(loops) * 16;
        else {
          kickActive = false;
          kickInvalid = true;
          return;
        }
        if (bytes > 65536u - offset) {
          kickActive = false;
          kickInvalid = true;
          return;
        }
        kickTagEnd = offset + uint32_t(bytes);
        kickEop = ((tag >> 15) & 1) != 0;
      }
      if (kickCopied >= kickTagEnd) {
        if (kickEop) {
          ps2Vu1EmitKick(gs, memory, kickBuffer, kickCopied);
          kickActive = false;
        } else
          kickTagEnd = 0;
      }
    }
  }
  void advance(uint64_t c) {
    for (;;) {
      uint64_t next = count ? ring[head].ready : UINT64_MAX;
      if (qValid && qReady < next)
        next = qReady;
      if (next > c || next == UINT64_MAX)
        break;
      drainFlags(next);
      commitQ(next);
    }
    advanceKick(c);
  }
  void waitKick(uint64_t &c) {
    while (kickActive) {
      if (kickNext > c)
        c = kickNext;
      advance(c);
    }
  }
  void startKick(uint64_t c, uint32_t qword) {
    kickSource = (qword * 16u) & 16383u;
    kickCopied = kickTagEnd = 0;
    kickEop = false;
    kickActive = true;
    kickNext = c + 1;
  }
  void flush(uint64_t &c) {
    for (unsigned r = 0; r < 32; ++r)
      for (unsigned k = 0; k < 4; ++k)
        if (vfR[r][k] > c)
          c = vfR[r][k];
    for (unsigned r = 0; r < 16; ++r)
      if (viR[r] > c)
        c = viR[r];
    if (qValid && qReady > c)
      c = qReady;
    if (count && ring[(head + count - 1) & 63].ready > c)
      c = ring[(head + count - 1) & 63].ready;
    advance(c);
    waitKick(c);
  }

  void markStore(uint32_t addr) {
    const uint32_t qword = addr >> 4;
    const uint64_t mask = 1ull << (qword & 63u);
    auto &word = dirty[qword >> 6];
    if (undo && !(word & mask))
      std::memcpy(undo + addr, vm + addr, 16);
    word |= mask;
  }
};

inline uint64_t vmax(uint64_t a, uint64_t b) { return a > b ? a : b; }

} // namespace vu1gen

#endif
