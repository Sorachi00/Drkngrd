#include "runtime/ps2_display_clock.h"

#include <algorithm>
#include <atomic>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <mutex>

#if defined(_WIN32)
#define NOMINMAX

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <dxgi1_2.h>
#include <wrl/client.h>
#include <thread>
#pragma comment(lib, "dxgi.lib")
#endif

namespace PS2DisplayClock
{
namespace
{
    std::atomic<bool> s_locked{false};
    // Game vblank = monitor vblank + phase (ns). The window thread moves it.
    std::atomic<int64_t> s_phaseNs{0};
    // Window thread: the vblank at which the last new frame is shown.
    Clock::time_point s_lastShown{};
    constexpr double kReadyPhase = -0.45;

    bool lockAllowed()
    {
        static const bool allowed = [] {
            const char *v = std::getenv("PS2_DISPLAY_LOCK");
            return !v || std::strcmp(v, "0") != 0;
        }();
        return allowed;
    }

    struct Shared
    {
        std::mutex mutex;
        Grid grid;
        bool valid = false;

    } s_grid;

    double simHz()
    {
        static const double hz = [] {
            const char *v = std::getenv("PS2_DISPLAY_SIM");
            return v ? std::clamp(std::atof(v), 0.0, 400.0) : 0.0;
        }() ;   
        return hz;
    }

#if defined(_WIN32)
    std::atomic<HWND> s_window{nullptr};
    std::thread s_vblank;
    std::atomic<bool> s_vblankStop{false}; // shutdown()

    void vblankThread()
    {
        SetThreadPriority( GetCurrentThread(), THREAD_PRIORITY_TIME_CRITICAL);  
        using Microsoft::WRL::ComPtr;
        ComPtr<IDXGIFactory1> factory;
        if (FAILED(CreateDXGIFactory1(IID_PPV_ARGS(&factory))))
            return;  
        ComPtr<IDXGIOutput> output;
        HMONITOR monitor = nullptr;
        double nominal = 0;                // period from the display mode (s)
        double base = 0, period = 0;       // smoothed grid (s, steady_clock)

        double last = 0;
        int good = 0, bad = 0;
        auto nextCheck = Clock::now();
        auto seconds = [](Clock::time_point t) { return std::chrono::duration<double>(t.time_since_epoch()).count(); };
        auto publish = [&](bool valid) {
            std::lock_guard lock(s_grid.mutex);
            s_grid.valid = valid;
            if (valid)
            {
                s_grid.grid.vblank = Clock::time_point(std::chrono::duration_cast<Clock::duration>(std::chrono::duration<double>(base)));
                s_grid.grid.period = std::chrono::duration_cast<Clock::duration>(std::chrono::duration<double>(period));
                s_grid.grid.hz = 1.0 / period;
            }
        };
        while (!s_vblankStop.load(std::memory_order_acquire))
        {
            const auto now = Clock::now() ;
            if (now >= nextCheck)
            {
                // The window's monitor (it can move to another one).
                nextCheck = now + std::chrono::seconds(1);
                const HWND window = s_window.load(std::memory_order_relaxed);
                const HMONITOR m = window ? MonitorFromWindow(window, MONITOR_DEFAULTTONEAREST) : nullptr;
                if (m != monitor || !output)
                {
                    monitor = m;
                    output.Reset();
                    good = bad = 0;
                    publish(false);
                    ComPtr<IDXGIAdapter1> adapter;
                    for (UINT i = 0; !output && m && factory->EnumAdapters1(i, &adapter) == S_OK; ++i)
                    {
                        ComPtr<IDXGIOutput> o;
                        for (UINT j = 0; adapter->EnumOutputs(j, &o) == S_OK; ++j)
                        {
                            DXGI_OUTPUT_DESC d{};
                            if (SUCCEEDED(o->GetDesc(&d)) && d.Monitor == m)   
                            {
                                output = o;
                                MONITORINFOEXW info{};
                                info.cbSize = sizeof(info);
                                DEVMODEW mode{} ;
                                mode.dmSize = sizeof(mode);
                                nominal = GetMonitorInfoW(m, &info) && EnumDisplaySettingsW(info.szDevice, ENUM_CURRENT_SETTINGS, &mode) &&
                                                  mode.dmDisplayFrequency > 1
                                              ? 1.0 / double(mode.dmDisplayFrequency)
                                               : 0.0;
                                break;
                            }
                            o.Reset();
                        }
                        adapter.Reset();   
                    }
                }
            }
            if (!output || nominal <= 0 )
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                continue;
            }
            if (FAILED(output->WaitForVBlank()))
            {
                output.Reset();
                continue;
            }
            const double t = seconds(Clock::now());
            const double interval = t - last;
            last = t;
            // No real vblank: the wait returned at once.
            if (interval < nominal * 0.5)
            {
                if (++bad >= 4)
                {
                    good = 0;

                    publish(false);
                    std::this_thread::sleep_for(std::chrono::milliseconds(100));
                }
                continue;
            }
            bad = 0;  
            if (good == 0)
            {
                base = t;
                period = nominal;
                good = 1;
                continue;
            }
            const double k = std::max(1.0, std::round((t - base) / period));
            const double predicted = base + k * period;
            const double error = t - predicted;
            if (std::fabs(error) > period * 0.25 || k > 4)
            {
                good = 0; // irregular: start again
                publish(false);
                continue; 
            }
            // Phase-locked loop: small corrections of phase and period.
            base = predicted + error * 0.05;
            period += error * 0.002 / k;
            if (++good >= 80 && std::fabs(period - nominal) < nominal * 0.02)
                publish(true);
        }
    }
#endif   
}

void setWindow(void *window )
{
#if defined(_WIN32)  
    s_window.store(static_cast<HWND>(window), std::memory_order_relaxed);
    static const bool started = [] {
        if(simHz() <= 0)
            s_vblank = std::thread(vblankThread); // joined by shutdown()
        return true;
    }();

    (void)started;
#else
    (void)window;
#endif
}

bool grid(Grid &out) 
{
    if (const double hz = simHz(); hz > 0)
    {
        static const Clock::time_point epoch = Clock::now();
        out.period = std::chrono::duration_cast<Clock::duration>(std::chrono::duration<double>(1.0 / hz));
        out.vblank = epoch + out.period * ((Clock::now() - epoch) / out.period);
        out.hz = hz;   
        return true;
    }
    std::lock_guard lock(s_grid.mutex);
    out = s_grid.grid;
    return s_grid.valid;
}

Clock::time_point lockVBlank(Clock::time_point target, uint32_t gameHz)
{
    Grid g;
    const bool lock = lockAllowed() && gameHz && grid(g) && std::fabs(double(gameHz) - g.hz) <= g.hz * 0.02 ;
    if (s_locked.exchange(lock, std::memory_order_relaxed) != lock)
        std::fprintf(stderr, "[display] vblank lock %s (game %u Hz, monitor %.3f Hz)\n", lock ? "on" : "off", gameHz, g.hz);
    if (!lock)
        return target;
    const auto base = g.vblank + std::chrono::nanoseconds(s_phaseNs.load(std::memory_order_relaxed)) ;  
    const double k = std::round(std::chrono::duration<double>(target - base).count() / std::chrono::duration<double>(g.period).count());
    return base + std::chrono::duration_cast<Clock::duration>(g.period * k);
}

void frameShown( Clock::time_point t, Clock::time_point published, uint64_t)
{
    Clock::time_point &lastShown = s_lastShown;
    static double meanX = 0, meanY = 0; 
    Grid g;
    if (!grid(g))
    {
        lastShown = {};
        return;
    }
    const double period = std::chrono::duration<double>(g.period).count();
    const double cycles = std::chrono::duration<double>(t - g.vblank).count() / period;
    // DWM shows the swap at the next refresh.
    const auto shown = g.vblank + std::chrono::duration_cast<Clock::duration>(g.period * std::ceil(cycles));
    const uint32_t refreshes =
        lastShown == Clock::time_point{}
            ? 1u
            : uint32_t(std::max(0.0, std::round(std::chrono::duration<double>(shown - lastShown).count() / period)));
    lastShown = shown;   

    if (!s_locked.load(std::memory_order_relaxed))
    {
        meanX = meanY = 0;
        return;
    }
    constexpr double kTwoPi =  6.283185307179586;
    const double ready = std::chrono::duration<double>(published - g.vblank).count() / period;
    const double where = ready - std::floor(ready);
    meanX = meanX * 0.95 + std::cos(kTwoPi * where) * 0.05;
    meanY = meanY * 0.95 + std::sin(kTwoPi * where) * 0.05;
    if (meanX * meanX + meanY * meanY < 0.01)
        return; // ready times spread over the whole interval: no clear phase
    double error = std::atan2(meanY, meanX) / kTwoPi - kReadyPhase; // 0 = at kReadyPhase
    error -= std::floor(error + 0.5);                                // -0.5..0.5
    const double stepNs = std::clamp(-error * 0.1 * period * 1e9, -20000.0, 20000.0);
    const int64_t periodNs = int64_t( period * 1e9);
    int64_t phase = s_phaseNs.load(std::memory_order_relaxed) + int64_t(stepNs);
    phase %= periodNs;
    if (phase < 0)
        phase += periodNs;
    s_phaseNs.store(phase, std::memory_order_relaxed);
}


void shutdown()
{
#if defined(_WIN32)
    s_vblankStop.store(true, std::memory_order_release);  
    if (s_vblank.joinable()) 
        s_vblank.join();
#endif
}

namespace
{
    struct Joiner
    {
        ~Joiner() { shutdown(); }
    } s_joiner;

}
}
