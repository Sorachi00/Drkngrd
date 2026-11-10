#include "runtime/gs/gs_frontend.h"
#include "runtime/ps2_memory.h"

#include <atomic>

#include <cstdlib>
#include <cstring>
#include <mutex>   
#include <stdexcept>

#if PS2X_GS_EMULATION
#include "gs_emulation.h"
#endif

std::atomic<uint64_t> g_statVu1GifBytes{0};    // VU1 XGKICK bytes (ps2_vu1_core.cpp, ps2_vu1_recomp.cpp)
std::atomic<uint64_t> g_statPathGifBytes[4]{}; // GIF bytes per path id (ps2_memory.cpp submitGifPacket)

namespace
{
    GSFrontendFactory g_factory = nullptr;

    std::mutex g_displayLatchMutex ;
    bool g_displayLatched = false;
    uint64_t g_displayLatch[7]{};
}

void gsSetFrontendFactory(GSFrontendFactory factory)
{
    g_factory = factory;
}


std::unique_ptr<GS> gsCreate()
{
#if PS2X_GS_EMULATION
    const char *which = std::getenv("PS2_RENDERER");
    if (!g_factory || (which && std::strcmp(which, "gs") == 0))
        return makeGsEmulation();
#endif
    if (!g_factory)
        throw std::runtime_error("no GS: this game registers no renderer and PS2X_GS_EMULATION is off");
    return g_factory() ;
}

void gsLatchDisplayRegisters(const GSRegisters &regs)
{
    const uint64_t values[7]{regs.pmode, regs.smode2, regs.dispfb1, regs.display1, regs.dispfb2, regs.display2, regs.bgcolor};
    std::lock_guard<std::mutex> lock(g_displayLatchMutex);
    std::memcpy(g_displayLatch, values, sizeof(values));
    g_displayLatched = true;
}

bool gsLatchedDisplayRegisters(uint64_t out[7])
{
    std::lock_guard<std::mutex> lock(g_displayLatchMutex);
    if (g_displayLatched)
        std::memcpy(out, g_displayLatch, sizeof(g_displayLatch));
    return g_displayLatched;
}
