
#pragma once
#include <atomic>
#include <chrono>
#include <cstdint>

namespace GSWidescreen
{
    constexpr float kSqueeze = 0.75f;   // (4 / 3) / (16 / 9)
    constexpr float kAspect = 16.0f / 9.0f;
    constexpr float kScreenWidth = 640.0f; // the game's 2D space


    enum Anchor : uint32_t
    {
        kLeft = 1,
        kCentre = 2, 

        kRight = 3,
        kAuto = 4, // from the element's place: left / right 40 % of the screen, else centre
        kKeep = 5, // placed at projected 3D points (enemy bars): left as it is
    };
    inline float anchorX(Anchor a) { return a == kLeft ? 0.0f : a == kRight ? kScreenWidth : kScreenWidth * 0.5f; }

    namespace detail
    {
        constexpr int kUiEntries = 32; 
        struct State
        {
            std::atomic<bool> enabled{false};
            std::atomic<int64_t> worldMs{-1000000};
            std::atomic<uint32_t> worldFbp{~0u};
            // UI draw functions: [lo, hi) and anchor, first match wins (set once at start).
            std::atomic<uint32_t> uiLo[kUiEntries]{}, uiHi[kUiEntries]{}, uiAnchor[kUiEntries]{};
        };
        inline State g_ownState;
        inline State *g_state = &g_ownState;
        inline int64_t nowMs()
        {
            return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch())
                .count();
        }
    }

    inline void setEnabled(bool on) { detail::g_state->enabled.store(on, std::memory_order_relaxed); }
    inline bool enabled() { return detail::g_state->enabled.load(std::memory_order_relaxed); }  

#ifdef DK_RENDER_DLL
    void worldDrawn(uint32_t fbp);
    bool active();
    uint32_t worldFbp();
    uint32_t uiAnchor(uint32_t function);
#else
    // GS thread: a 3D world (map) was drawn into frame buffer `fbp`.
    inline void worldDrawn(uint32_t fbp)
    {
        detail::g_state->worldFbp.store(fbp, std::memory_order_relaxed);
        detail::g_state->worldMs.store(detail::nowMs(), std::memory_order_relaxed);
    }
    inline bool active()
    {
        return enabled() && detail::nowMs() - detail::g_state->worldMs.load(std::memory_order_relaxed) < 250 ;
    }
    inline uint32_t worldFbp() { return detail::g_state->worldFbp.load(std::memory_order_relaxed); }

    inline bool addUi(uint32_t lo, uint32_t hi, Anchor anchor)
    {
        for (int i = 0; i < detail::kUiEntries; ++i)
        {
            uint32_t empty = 0;
            if(detail::g_state->uiHi[i].compare_exchange_strong(empty, hi) || (empty == hi && detail::g_state->uiLo[i].load(std::memory_order_relaxed) == lo))
            {
                detail::g_state->uiLo[i].store(lo, std::memory_order_relaxed);
                detail::g_state->uiAnchor[i].store(anchor, std::memory_order_release);
                return true;
            }
        }

        return false;
    }
    inline bool addUi(uint32_t function, Anchor anchor) { return addUi(function, function + 1, anchor); }
    // Anchor of a draw function; 0 = not UI. 
    inline uint32_t uiAnchor(uint32_t function)
    {
        for (int i = 0; i < detail::kUiEntries; ++i)
        {
            const uint32_t hi = detail::g_state->uiHi[i].load(std::memory_order_relaxed);
            if (!hi)
                break;
            if (function >= detail::g_state->uiLo[i].load(std::memory_order_relaxed) && function < hi)
                return detail::g_state->uiAnchor[i].load(std::memory_order_acquire);
        }

        return 0;
    }
#endif

    struct Squeeze
    {
        bool on = false ;
        float anchor = 0.0f;
        float apply(float x) const { return on ? anchor + (x - anchor) * kSqueeze : x; }
    };
    inline Squeeze squeezeFor(uint32_t anchor, float x0, float x1)
    {
        Squeeze s ;

        if (!(x0 <= x1) || anchor == 0 || anchor == kKeep)
            return s;
        if (anchor == kAuto)
            anchor = x1 <= kScreenWidth * 0.4f ? kLeft : ( x0 >= kScreenWidth * 0.6f ? kRight : kCentre);   
        s.on = true;
        s.anchor = anchorX(Anchor(anchor));
        return s;
    }
}
