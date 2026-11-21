#include "drakengard_loads.h"
#include "game_overrides.h"
#include "ps2_runtime.h"
#include "ps2_runtime_macros.h"
#include "runtime/ps2_vdisc.h"

#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <unordered_map>
#include <vector>

void FUN_00130168_0x130168(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime);

namespace
{
    constexpr uint32_t kImageDesc = 0x48FF38u; // IMAGE.BIN descriptor (file server slot 0)
    constexpr uint32_t kRamMask = PS2_RAM_MASK;

    enum class Mode
    {
        Off,
        On,
        Check
    };


    Mode mode()
    {   
        static const Mode m = []
        {
            const char *v = std::getenv("PS2_NATIVE_LOAD");
            if (v && std::strcmp(v, "0") == 0)
                return Mode::Off;
            if (v && std::strcmp(v, "check") == 0)
                return Mode::Check;
            return Mode::On;
        }();
        return m;
    }

    uint32_t rd32(const uint8_t *rdram, uint32_t address)
    {
        uint32_t v;
        std::memcpy(&v, rdram + (address & PS2_RAM_MASK & ~3u), 4);
        return v ;
    }

    void wr32(uint8_t *rdram, uint32_t address, uint32_t value)
    {
        std::memcpy(rdram + (address & PS2_RAM_MASK & ~3u), &value, 4);
    }

    bool hostEntry(const uint8_t *rdram, uint32_t index, std::vector<uint8_t> &out)  
    {
        const uint32_t table = rd32(rdram, kImageDesc + 0xE0u);
        if (table == 0u || index >= rd32(rdram, kImageDesc + 0xE4u))
            return false;
        const uint32_t pos = rd32(rdram, table + index * 16u);
        const uint32_t stored = rd32(rdram, table + index * 16u + 8u);
        const uint32_t unpacked = rd32(rdram, table + index * 16u + 12u) ;

        if (stored == 0u)
            return false;
        PS2VDisc::FilePtr file = unpacked != 0u ? PS2VDisc::findUnpacked("IMAGE.BIN", index)
                                                : PS2VDisc::find("IMAGE.BIN");   
        const uint64_t offset = unpacked != 0u ? 0u : pos;
        const uint32_t size = unpacked != 0u ? unpacked : stored;
        if (!file || (unpacked != 0u && file->size() != unpacked))
            return false;
        out.resize(size );
        return file->read(offset, out.data(), size) == size;

    }

    uint32_t entryBytes(const uint8_t *rdram, uint32_t index)
    {
        const uint32_t table = rd32(rdram, kImageDesc + 0xE0u);
        if (table == 0u || index >= rd32(rdram, kImageDesc + 0xE4u))
            return 0u;
        return std::max(rd32(rdram, table + index * 16u + 8u), rd32(rdram, table + index * 16u + 12u));
    }

    std::vector<dk_loads::Range> g_loads;
    std::unordered_map<uint32_t, uint32_t> g_noted; // C -> buffer of the load already in g_loads

    void noteLoad(const uint8_t *rdram, uint32_t c)
    {
        const uint32_t buf = rd32(rdram, c + 0x0Cu) & 0x1FFFFFFFu;
        const auto it = g_noted.find(c); 

        if (it != g_noted.end() && it->second == buf)
            return;
        g_noted[c] = buf;

        if (const uint32_t bytes = entryBytes(rdram, rd32(rdram, c + 0x2Cu)))
            g_loads.push_back({buf, buf + bytes});
    }

    struct CheckStats
    {
        uint32_t equal = 0;
        uint32_t differ = 0;
    };

    void dkNativeLoad(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime)

    {
        const uint32_t c = GPR_U32(ctx, 4);
        const uint32_t state = rd32(rdram, c + 0x08u);
        if (state == 1u)
            g_noted.erase(c);
        else if (state == 5u)
            noteLoad(rdram, c); // finished (the call returns 2)
        if (mode() == Mode::On && state == 1u && PS2VDisc::mounted())
        {
            static std::vector<uint8_t> data;
            const uint32_t index = rd32(rdram, c + 0x2Cu);
            const uint32_t buf = rd32(rdram, c + 0x0Cu);
            if (hostEntry(rdram, index, data) && (buf & kRamMask) + data.size() <= PS2_RAM_SIZE)

            {
                // The buffer holds align2048(size + 0x810) bytes (FUN_001300c8).
                std::memcpy(rdram + (buf & kRamMask), data.data(), data.size());
                std::cerr << "[native-load] entry " << index << " (" << data.size() << " bytes) from the data folder"
                          << std::endl;
                wr32(rdram, c + 0x30u, 3u); // status: done (file server)
                wr32(rdram, c + 0x08u, 5u); // state 5: finished
                noteLoad(rdram, c);
                SET_GPR_U64(ctx, 2, 2u);    // return 2: done (0x130298)
                ctx->pc = GPR_U32(ctx, 31);
                return;
            }
        }

        if (mode() != Mode::Check || !PS2VDisc::mounted())  
        {
            FUN_00130168_0x130168(rdram, ctx, runtime);
            return;
        }   

        static std::unordered_map<uint32_t, uint32_t> s_loading;
        static CheckStats s_stats;
        if (state == 1u)
            s_loading[c] = rd32(rdram, c + 0x2Cu);
        const uint64_t unwinds = ps2_game_overrides::guestUnwindCount();
        FUN_00130168_0x130168(rdram, ctx, runtime);
        if (ps2_game_overrides::guestUnwindCount() != unwinds || GPR_U32(ctx, 2) != 2u )
            return;
        const auto it = s_loading.find(c);
        if (it == s_loading.end())
            return;
        const uint32_t index = it->second;
        s_loading.erase(it) ;
        std::vector<uint8_t> data;
        const uint32_t buf = rd32(rdram, c + 0x0Cu);
        const bool equal = hostEntry(rdram, index, data) && (buf & kRamMask) + data.size() <= PS2_RAM_SIZE &&
                           std::memcmp(rdram + (buf & kRamMask), data.data(), data.size()) == 0;
        ++(equal ? s_stats.equal : s_stats.differ);
        std::cerr << "[native-load] check entry " << index << " (" << data.size() << " bytes): "
                  << (equal ? "equal" : "DIFFERENT") << " (equal " << s_stats.equal << ", different "
                  << s_stats.differ << ")" << std::endl;
    }
}

namespace dk_loads
{
    const std::vector<Range> &ranges() { return g_loads; }
}

void applyDrakengardNativeLoad(PS2Runtime &runtime)
{
    runtime.replaceFunction(0x130168u, &dkNativeLoad);

}
