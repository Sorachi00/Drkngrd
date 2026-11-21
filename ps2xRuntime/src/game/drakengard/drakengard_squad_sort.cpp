#include "game_overrides.h"
#include "ps2_runtime.h"
#include "ps2_runtime_macros.h"
#include "dk_port_macros.h"
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

namespace dk_squad_sort
{
    float readFloat(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime, uint32_t a)
    {
        const uint32_t bits = READ32(a);
        float f;
        std::memcpy(&f, &bits, 4);
        return f;
    }
}

namespace dk_squad_sort

{
    PS2Runtime::RecompiledFunction g_squadSort = nullptr;
    constexpr uint32_t kCaimPos = 0x3B0670u, kSortStart = 0x56F54Cu;

    int sortMode()
    {
        static const int mode = [] {  
            const char *v = std::getenv("PS2_DK_NATIVE_SORT");
            if (!v)
                return 1;
            return std::strcmp(v, "check") == 0 ? 2 : std::strcmp(v, "0") == 0 ? 0 : 1;
        }();
        return mode;

    }
    float bitsFloat(uint32_t bits)
    {
        float f;
        std::memcpy(&f, &bits, 4);
        return f;
    }
    uint32_t floatBits(float f )
    {
        uint32_t bits;
        std::memcpy(&bits, &f, 4);
        return bits;
    }

    struct SortEntry
    {
        float key;
        uint32_t value; // index << 16 | members counted
    };
    struct SortOut
    {
        uint32_t squad, minBits, rank, sum;
    };  

    // The results (per squad: +0x9C4, +0x9C8, +0x9CA) without writing them.
    void squadOrder(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime, uint32_t array, int32_t count, std::vector<SortOut> &out)
    {
        out.clear();
        if (count <= 0)
            return;
        thread_local std::vector<SortEntry> e;
        e.clear();
        const float caim[3] = {readFloat(rdram, ctx, runtime, kCaimPos), readFloat(rdram, ctx, runtime, kCaimPos + 4u),

                               readFloat(rdram, ctx, runtime, kCaimPos + 8u)};
        const float start = bitsFloat(READ32(kSortStart));
        for (int32_t k = 0; k < count; ++k)
        {
            const uint32_t squad = READ32(array + 4u * uint32_t(k));
            float best = start;
            const int32_t n = int32_t(READ32(squad + 0xA18u));
            uint32_t members = 0;
            for (int32_t m = 0; m < n; ++m )
            {
                const uint32_t slot = squad + 0x3A0u + uint32_t(m) * 0xA0u;
                if (READ32(slot + 0x70u) < 2u)
                    continue;
                // FUN_00283bc4(caim, slot + 0x50)
                const float dz = FPU_SUB_S(ctx, caim[2], readFloat(rdram, ctx, runtime, slot + 0x58u));
                const float dx = FPU_SUB_S(ctx, caim[0], readFloat(rdram, ctx, runtime, slot + 0x50u));
                const float dy = FPU_SUB_S(ctx, caim[1], readFloat(rdram, ctx, runtime, slot + 0x54u));
                float acc = FPU_MUL_S(ctx, dx, dx);
                acc = FPU_MADD_S(ctx, acc, dy, dy);
                const float d = FPU_SQRT_S(ctx, FPU_MADD_S(ctx, acc, dz, dz));
                if (FPU_C_OLT_S(d, best))
                    best = d;
                ++members;
            }
            out.push_back({squad, floatBits(best), 0, 0});
            e.push_back({best, uint32_t(k) << 16 | (members & 0xFFFFu)} );
        }  
        // FUN_0016d348 (comb sort, in place).
        if (count >= 2)
        {
            int32_t gap =  count;
            for (;;)
            {  
                gap = int32_t((int64_t(gap) * 0xC4EC) >> 16);
                if (gap == 0)
                    gap = 1;
                else if (uint32_t(gap - 9) < 2u)
                    gap = 11;
                bool swapped = false;   
                for (int32_t i = 0; i + gap < count; ++i)
                    if (FPU_C_OLT_S(e[size_t(i + gap)].key, e[size_t(i)].key))
                    {
                        std::swap(e[size_t(i)], e[size_t(i + gap)]);
                        swapped = true;
                    }
                if (!swapped && gap < 2)
                    break;
            }
        }
        uint32_t sum = 0;  
        for (int32_t i = 0; i < count; ++i)
        {
            const uint32_t v = e[size_t(i)].value;
            sum += v & 0xFFFFu;
            SortOut &o = out[v >> 16];
            o.rank = uint32_t(i) & 0xFFFFu;
            o.sum = sum & 0xFFFFu;
        }
    }

    void squadSort(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime )
    {
        const int mode = sortMode();
        if (ctx->pc != 0x16CD34u || mode == 0)
        {
            g_squadSort(rdram, ctx, runtime);
            return;

        }
        thread_local std::vector<SortOut> out;
        squadOrder(rdram, ctx, runtime, GPR_U32(ctx, 4), int32_t(GPR_U32(ctx, 5)), out);
        if (mode == 2)
        {
            const uint64_t unwinds = ps2_game_overrides::guestUnwindCount() ;
            g_squadSort(rdram, ctx, runtime);
            static uint64_t calls = 0, bad = 0, paused = 0;
            if (ps2_game_overrides::guestUnwindCount() != unwinds)
            {
                ++paused; // the original continues later: nothing to compare yet
                return;
            }
            ++calls;
            for (const SortOut &o : out)
                if (READ32(o.squad + 0x9C4u) != o.minBits || READ16(o.squad + 0x9C8u) != o.rank || READ16(o.squad + 0x9CAu) != o.sum)
                {
                    if ( ++bad <= 20)
                        std::fprintf(stderr, "[sort] mismatch squad %08X: min %08X/%08X rank %u/%u sum %u/%u\n", o.squad, READ32(o.squad + 0x9C4u), o.minBits, READ16(o.squad + 0x9C8u), o.rank, READ16(o.squad + 0x9CAu), o.sum);
                }
            if (calls % 600 == 0)
                std::fprintf(stderr, "[sort] calls %llu mismatches %llu paused %llu (squads %zu)\n", (unsigned long long)calls, (unsigned long long)bad, (unsigned long long)paused, out.size());
            return;
        }
        for (const SortOut &o : out)
        {  
            WRITE32(o.squad + 0x9C4u, o.minBits);
            WRITE16(o.squad + 0x9C8u, o.rank);
            WRITE16(o.squad + 0x9CAu, o.sum);
        }
        ctx->pc = GPR_U32(ctx, 31);
    }
}

void applyDrakengardSquadSort(PS2Runtime &runtime)
{
    using namespace dk_squad_sort;
    if (runtime.hasFunction(0x16CD34u))
    {
        g_squadSort = runtime.lookupFunction(0x16CD34u);
        runtime.replaceFunction( 0x16CD34u, &squadSort);
    }
}
