#pragma once 

#include <cstdint>
#include <functional>

#include "ps2_runtime.h"

namespace dk_return
{
    using After = std::function<void(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime )> ;

    bool enabled(uint32_t user);

    // Before the original function: from here its return runs `after`.
    void arm(PS2Runtime *runtime, R5900Context *ctx, After after);

    bool finish(uint8_t *rdram, R5900Context *ctx, PS2Runtime *runtime);


    void cancel(R5900Context *ctx);

    // The trampoline's address (an armed call's $ra).
    uint32_t trampolineAddress();
}
