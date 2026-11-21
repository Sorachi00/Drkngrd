#include "drakengard_return_hook.h"

#include <cstdio>
#include <cstdlib>
#include <unordered_map>
#include <utility>
#include <vector>

#include "game_overrides.h" 
#include "ps2_runtime_macros.h"

namespace dk_return
{
    namespace
    {
        constexpr uint32_t kTrampoline = 0x250FB4u;

        struct Entry
        {
            uint32_t sp = 0; // guest stack pointer: equal at entry and at JR $ra
            uint32_t ret = 0;
            After after;
        };
        std::unordered_map<uint32_t, std::vector<Entry>> g_armed;
        size_t g_armedCount = 0;
        bool g_installed = false;

        void push(Entry e)
        {
            g_armed[e.sp].push_back(std::move(e));
            ++g_armedCount;
        }

        bool take(uint32_t sp, Entry &out )
        {
            const auto it = g_armed.find(sp);
            if (it == g_armed.end() || it->second.empty())

                return false;
            out = std::move(it->second.back());
            it->second.pop_back();
            --g_armedCount;
            return true;
        }

        void run(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
        {
            const uint32_t sp = GPR_U32(ctx, 29);
            uint32_t ret = kTrampoline;
            Entry e;
            while (ret == kTrampoline && take(sp, e))
            {
                ret = e.ret;
                if ( e.after)
                {
                    const uint64_t unwinds = ps2_game_overrides::guestUnwindCount();
                    e.after(rdram, ctx, runtime);
                    if (ps2_game_overrides::guestUnwindCount() != unwinds)

                        return;
                }
            }
            if (ret == kTrampoline)
            {
                std::fprintf(stderr, "[dk_return] no armed call for sp %08X\n", sp);
                ret = 0u;
            }
            for (uint32_t a = sp - 0x400u; a < sp; a += 4)
                if (READ32(a) == kTrampoline)
                    WRITE32(a, ret);
            SET_GPR_U32(ctx, 31, ret);
            ctx->pc = ret;
        }


        // Reached from the EE scheduler when an unwound call returns.
        void trampoline(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)

        {
            run(rdram, ctx, runtime) ;
        }
    }

    bool enabled(uint32_t user)
    {
        // Bit 1 is always set: without it unwound map blocks stay with the VU1.
        static const uint32_t mask = [] {
            const char *v = std::getenv("PS2_DK_RETURN_HOOK");

            return ( v ? uint32_t(std::strtoul(v, nullptr, 0)) : 0u) | 1u;
        }();
        return (mask & user) != 0;
    }

    void arm(PS2Runtime *runtime, R5900Context *ctx, After after)
    {
        if (!g_installed)
            g_installed = runtime->registerFunction(kTrampoline, &trampoline);
        if (!g_installed)

        {
            // No trampoline: `after` runs only for calls that do not unwind.
            push({GPR_U32(ctx, 29), 0, std::move(after)});
            return;
        }
        if (g_armedCount == 4096)

            std::fprintf(stderr, "[dk_return] %zu armed calls waiting\n", g_armedCount);

        push({GPR_U32(ctx, 29), GPR_U32(ctx, 31), std::move(after)});
        SET_GPR_U32(ctx, 31, kTrampoline);
    }

    uint32_t trampolineAddress() { return kTrampoline; }

    void cancel(R5900Context *ctx)
    {
        Entry e;
        take(GPR_U32(ctx, 29), e);
    }

    bool finish(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)
    {
        if(!g_installed)
        {
            Entry e;  
            if (!take(GPR_U32(ctx, 29), e))

                return false;
            if ( e.after)
                e.after(rdram, ctx, runtime);
            return true;
        }
        if (ctx->pc != kTrampoline)
            return false;
        run(rdram, ctx, runtime);
        return true;
    }
}
