#include "runtime/ps2_graphics_thread.h"
#include "runtime/ps2_perf.h"
#include "ThreadNaming.h"

#include <atomic>
#include <condition_variable>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <exception>
#include <immintrin.h>   
#include <mutex>
#include <thread>
#include <intrin.h>
extern "C" __declspec(dllimport) void *__stdcall GetModuleHandleA(const char *name);
#include <algorithm>
#include <chrono>
#include <cstdio>  
#include <map>
#include <vector>

namespace GraphicsThread
{
namespace
{
struct Job
{
    std::function<void()> run;
    uint32_t vuControl = 0;
};

std::mutex s_mutex;
std::condition_variable s_wake;
std::deque<Job> s_queue;

std::atomic<uint64_t> s_submitted{0}, s_done{0};
std::atomic<bool> s_started{false};
std::thread::id s_threadId;
std::thread s_thread;
// shutdown(): the graphics and GIF threads end after their current job.
std::atomic<bool> s_stop{false};
std::exception_ptr s_error;
std::function<void()> s_afterSync;
std::function<uint32_t()> s_vuControlSource;
std::function<uint32_t()> s_pcSource;
std::atomic<uint32_t> s_csrNoSyncPcs[4]{};
thread_local uint32_t t_vuControl = 0;
std::atomic<uint32_t> s_vuStopBits{0};
std::atomic<bool> s_vuStopValid{false};

// GIF stage: packets of a job go to the GIF thread in one batch.
struct GifBatch

{
    std::vector<uint8_t> bytes;
    std::vector<uint32_t> sizes;
    // Deferred EE writes, run before the packet with this index.
    std::vector<std::pair<size_t, std::function<void()>>> calls;
};
std::mutex s_gifMutex;
std::condition_variable s_gifWake;
std::deque<GifBatch> s_gifQueue;
std::vector<GifBatch> s_gifFree;
GifBatch s_gifCurrent; // graphics thread only
std::atomic<uint64_t> s_gifSubmitted{0}, s_gifDone{0};

std::atomic<bool> s_gifStarted{false};
std::thread::id s_gifThreadId;
std::thread s_gifThread; // made by the graphics thread
std::function<void(const uint8_t *, uint32_t)> s_gifSink;

std::atomic<bool> s_gifDisabled{false}; // disableGifStage

bool gifEnabled()
{
#if !PS2X_GS_EMULATION
    return false; // the game's own GS decodes on the graphics thread (GS::directGif)
#endif

    static const bool on = [] {
        const char *v = std::getenv("PS2_GIF_THREAD");
        return !v || std::strcmp(v, "0") != 0;
    }();
    return on && !s_gifDisabled.load(std::memory_order_relaxed);
}

#if PS2X_GS_EMULATION
void gifLoop()
{
    ThreadNaming::SetCurrentThreadName("GifThread");
    for (;;)
    {
        GifBatch batch;
        {
            std::unique_lock lock(s_gifMutex);

            s_gifWake.wait(lock, [] { return !s_gifQueue.empty() || s_stop.load(std::memory_order_acquire); });
            if (s_stop.load(std::memory_order_acquire))

                return;
            batch = std::move(s_gifQueue.front());
            s_gifQueue.pop_front();
        }
        try
        {
            size_t offset = 0, call = 0;
            for (size_t i = 0; i < batch.sizes.size(); ++i)
            {
                for (; call < batch.calls.size() && batch.calls[call].first == i; ++call)

                    batch.calls[call].second();
                s_gifSink(batch.bytes.data() + offset, batch.sizes[i]);  
                offset += batch.sizes[i];
            }
            for (; call < batch.calls.size(); ++call)
                batch.calls[call].second();
        }
        catch (...)
        {

            std::lock_guard lock(s_mutex);
            if (!s_error)
                s_error = std::current_exception();
        }
        batch.bytes.clear();
        batch.sizes.clear();
        batch.calls.clear(); 
        {
            std::lock_guard lock(s_gifMutex);
            if (s_gifFree.size() < 64)
                s_gifFree.push_back(std::move(batch));
        }
        s_gifDone.fetch_add(1, std::memory_order_release);
        s_gifDone.notify_all();
    }
}

#endif


// Graphics thread, at the end of each job.
void flushGifBatch()
{
#if PS2X_GS_EMULATION
    if (s_gifCurrent.sizes.empty() && s_gifCurrent.calls.empty())
        return;
    if (!s_gifStarted.load(std::memory_order_relaxed))
    {
        s_gifThread = std::thread(gifLoop);
        s_gifThreadId = s_gifThread.get_id();
        s_gifStarted.store(true, std::memory_order_release);
    }
    s_gifSubmitted.fetch_add(1, std::memory_order_relaxed);
    {
        std::lock_guard lock(s_gifMutex);
        s_gifQueue.push_back( std::move(s_gifCurrent));
        s_gifCurrent = {};

        if (!s_gifFree.empty())

        {
            s_gifCurrent = std::move(s_gifFree.back());
            s_gifFree.pop_back();
        }
    }
    s_gifWake.notify_one();
#endif
}

void waitCounter(std::atomic<uint64_t> &done, uint64_t target)
{
    uint64_t value = done.load(std::memory_order_acquire);
    for (int spin = 0; spin < 4000 && value < target; ++spin)
    {
        _mm_pause();
        value =  done.load(std::memory_order_acquire);
    }   
    while (value < target)
    {
        done.wait(value, std::memory_order_acquire);
        value = done.load(std::memory_order_acquire);
    }
}

void loop()
{
    ThreadNaming::SetCurrentThreadName("GraphicsThread");
    for (;;)
    { 
        Job job;
        {
            std::unique_lock lock(s_mutex);
            s_wake.wait(lock, [] { return !s_queue.empty() || s_stop.load(std::memory_order_acquire); });
            if (s_stop.load(std::memory_order_acquire))
                return;   
            job = std::move(s_queue.front());
            s_queue.pop_front();
        }
        t_vuControl = job.vuControl;
        try
        {
            job.run();
        }
        catch (...)
        { 
            std::lock_guard lock(s_mutex);
            if (!s_error)
                s_error = std::current_exception();

        }
        flushGifBatch();
        s_done.fetch_add(1, std::memory_order_release);
        s_done.notify_all() ;
    }
}

void start()
{
    std::lock_guard lock(s_mutex);
    if (s_started.load(std::memory_order_relaxed))
        return;
    // Joined by shutdown().
    s_thread = std::thread(loop);
    s_threadId = s_thread.get_id();
    s_started.store(true, std::memory_order_release);
}
} // namespace   

bool active()
{
    static std::atomic<int> s_on{-1};
    int on = s_on.load(std::memory_order_relaxed);
    if (on < 0)
    {
        const char *v = std::getenv("PS2_GRAPHICS_THREAD");
        on = (!v || std::strcmp(v, "0") != 0) ? 1 : 0;
        s_on.store(on, std::memory_order_relaxed);
    }
    return on != 0;
}

bool onThread()
{
    return s_started.load(std::memory_order_acquire) && std::this_thread::get_id() == s_threadId;
}

void submit(std::function<void()> job)
{
    const uint32_t vuControl = s_vuControlSource ? s_vuControlSource() : 0u;
    if (!s_started.load(std::memory_order_acquire))
        start();
    s_submitted.fetch_add(1, std::memory_order_relaxed);
    {
        std::lock_guard lock(s_mutex);
        s_queue.push_back(Job{std::move(job), vuControl});
    }
    s_wake.notify_one();
}

void syncImpl();


__declspec(noinline) void sync()
{   
    static const bool trace = std::getenv("PS2_TRACE_SYNC") != nullptr;
    if (!trace)
    {
        syncImpl();
        return;
    } 
    void *caller = _ReturnAddress();

    const auto t0 = std::chrono::steady_clock::now();
    syncImpl();
    const double us = std::chrono::duration<double, std::micro>(std::chrono::steady_clock::now() - t0).count();
    if (us < 1.0)
        return;
    static std::mutex m; 
    static std::map<void *, std::pair<uint64_t, double>> stats;
    static auto next = std::chrono::steady_clock::now() + std::chrono::seconds(10);
    std::lock_guard lock(m);
    auto &e = stats[caller];
    ++e.first;
    e.second += us;
    if (std::chrono::steady_clock::now() >= next)
    {
        next += std::chrono::seconds(10);
        const uintptr_t base = reinterpret_cast<uintptr_t>(GetModuleHandleA(nullptr));
        std::vector<std::pair<double, void *>> top;
        for (auto &[k, v] : stats)
            top.push_back({v.second, k});
        std::sort(top.rbegin(), top.rend());
        for (size_t i = 0; i < top.size() && i < 6; ++i)
            std::fprintf(stderr, "[sync-caller] m+%llx waits %llu total %.0f us\n", static_cast<unsigned long long>(reinterpret_cast<uintptr_t>(top[i].second) - base), static_cast<unsigned long long>(stats[top[i].second].first), top[i].first);
        stats.clear();
    }

}

void syncImpl()
{ 
    if (!s_started.load(std::memory_order_acquire) || std::this_thread::get_id() == s_threadId || (s_gifStarted.load(std::memory_order_acquire) && std::this_thread::get_id() == s_gifThreadId))
        return;
    const uint64_t target = s_submitted.load( std::memory_order_relaxed);
    if (s_done.load(std::memory_order_acquire) >= target && s_gifDone.load(std::memory_order_acquire) >= s_gifSubmitted.load(std::memory_order_acquire))
        return;
    {
        PS2_PERF_ZONE(ZoneVu1);
        waitCounter(s_done, target);
        waitCounter(s_gifDone, s_gifSubmitted.load(std::memory_order_acquire));
    }
    {
        std::lock_guard lock(s_mutex);
        if (s_error)
        {
            std::exception_ptr error = s_error;
            s_error = nullptr;
            std::rethrow_exception(error); 

        }
    }
    if (s_afterSync )
        s_afterSync();
}

bool isGraphicsAddress(uint32_t address)
{
    // KSEG0/1 aliases; scratchpad (0x70000000) and RAM mirrors stay below.
    if (address >= 0x80000000u && address < 0xC0000000u)
        address &= 0x1FFFFFFFu;
    return (address >= 0x10003000u && address < 0x10003100u) || // GIF registers
           (address >= 0x10003C00u && address < 0x10004000u) || // VIF1 registers
           (address >= 0x10005000u && address < 0x10007000u) || // VIF1 and GIF FIFOs
            (address >= 0x11008000u && address < 0x11010000u) || // VU1 code and data
           (address >= 0x12000000u && address < 0x12002000u);   // GS privileged registers
}

uint32_t jobVuControl()
{
    return t_vuControl ;
}


void setVuStopBits( uint32_t bits)
{
    s_vuStopBits.store(bits, std::memory_order_relaxed);
    s_vuStopValid.store(true, std::memory_order_release);
}

bool takeVuStopBits(uint32_t &bits)
{
    if (!s_vuStopValid.exchange(false, std::memory_order_acquire))
        return false;
    bits = s_vuStopBits.load(std::memory_order_relaxed);
    return true;
}

void setVuControlSource(std::function<uint32_t()> fn)
{
    s_vuControlSource = std::move(fn);
}

bool syncFor(uint32_t address, bool write)
{
    const uint32_t physical = address >= 0x80000000u && address < 0xC0000000u ? address & 0x1FFFFFFFu : address;
    if (!write && (physical & ~7u) == 0x12001000u && s_pcSource && s_csrNoSyncPcs[0].load(std::memory_order_relaxed))
    {
        const uint32_t pc = s_pcSource();
        for (auto &noSync : s_csrNoSyncPcs)
            if (noSync.load(std::memory_order_relaxed) == pc)
                return false;
    }
    static const bool trace = std::getenv("PS2_TRACE_SYNC") != nullptr;   
    if (!trace)
    {
        sync();
        return true;
    }
    const auto t0 = std::chrono::steady_clock::now();
    sync();
    const double us = std::chrono::duration<double, std::micro>(std::chrono::steady_clock::now() - t0).count();
    static std::map<std::pair<uint32_t, bool>, std::pair<uint64_t, double>> stats;
    if ( us >= 100.0 && s_pcSource)
    {
        static std::map<std::pair<uint32_t, uint32_t>, uint64_t> slowPcs;

        static uint64_t slowCount = 0;
        if(++slowPcs[{address, s_pcSource()}] == 1 || (++slowCount % 600) == 0)
            for (auto &[k, n] : slowPcs)
                std::fprintf(stderr, "[sync-pc] 0x%08X pc 0x%08X slow waits %llu\n", k.first, k.second, static_cast<unsigned long long>(n));
    }
    static auto next = std::chrono::steady_clock::now() + std::chrono::seconds(10);
    auto &e = stats[{address, write}];
    ++e.first;
    e.second += us;
    if (std::chrono::steady_clock::now() >= next)
    {
        next += std::chrono::seconds(10);
        std::vector<std::pair<double, std::pair<uint32_t, bool>>> top;
        for(auto &[k, v] : stats)
            top.push_back({v.second, k});
        std::sort(top.rbegin(), top.rend());
        for (size_t i = 0; i < top.size() && i < 8; ++i) 
            std::fprintf(stderr, "[sync] %s 0x%08X calls %llu wait %.0f us\n", top[i].second.second ? "write" : "read", top[i].second.first, static_cast<unsigned long long>(stats[top[i].second].first), top[i].first);
        stats.clear();
    }
    return true;
}

bool deferPrivWrite(std::function<void()> write)
{
    if (!active() || onThread() || (s_gifStarted.load(std::memory_order_acquire) && std::this_thread::get_id() == s_gifThreadId))
        return false;
    submit([write = std::move(write)]() mutable {
        if (gifStage())
            s_gifCurrent.calls.emplace_back(s_gifCurrent.sizes.size(), std::move(write));
        else
            write();
    });
    return true;
}

void frameBoundary()
{
    if (!s_started.load(std::memory_order_acquire))
        return;
    static uint64_t s_jobMark = 0, s_gifMark = 0;
    if (s_done.load(std::memory_order_acquire) < s_jobMark || s_gifDone.load(std::memory_order_acquire) < s_gifMark)
    {
        PS2_PERF_ZONE(ZoneVu1);
        waitCounter(s_done, s_jobMark);

        waitCounter(s_gifDone, s_gifMark);
    }
    s_jobMark = s_submitted.load(std::memory_order_relaxed) ;
    s_gifMark = s_gifSubmitted.load(std::memory_order_acquire);
}


void setCsrNoSyncReadPc(uint32_t pc)   
{
    for (auto &slot : s_csrNoSyncPcs)  
    {
        uint32_t expected = 0;
        if (slot.load() == pc || slot.compare_exchange_strong(expected, pc))
            return;
    }
}

void setPcSource(std::function<uint32_t()> fn)
{
    s_pcSource = std::move(fn);
}

bool gifStage()
{

    return active() && gifEnabled();
}

void disableGifStage()
{
    s_gifDisabled.store( true, std::memory_order_relaxed);
}


void submitGif(const uint8_t *data, uint32_t size)
{
    auto &bytes = s_gifCurrent.bytes;

    if (bytes.capacity() < bytes.size() + size)
        bytes.reserve(std::max<size_t>(bytes.capacity() * 2, std::max<size_t>(bytes.size() + size, 512 * 1024)));
    const size_t old = bytes.size();
    bytes.resize(old + size) ;  
    std::memcpy(bytes.data() + old, data, size);
    s_gifCurrent.sizes.push_back(size);
}

void gifCall(std::function<void()> call)
{
    if (gifStage() && onThread())
        s_gifCurrent.calls.emplace_back(s_gifCurrent.sizes.size(), std::move(call));
    else
        call();
}

void setGifSink(std::function<void(const uint8_t *, uint32_t)> fn)
{

    s_gifSink = std::move( fn);
}

void setAfterSync(std::function<void()> fn)
{
    s_afterSync = std::move(fn);
}

void shutdown() 
{
    {

        std::lock_guard lock(s_mutex);
        s_stop.store(true, std::memory_order_release);
    }
    s_wake.notify_all();
    // (Called on one of the two threads, e.g. an exit from a job: no self-join.)
    auto join = [](std::thread &thread) {
        if (thread.joinable())
            thread.get_id() == std::this_thread::get_id() ? thread.detach() : thread.join();
    };
    join(s_thread);
    // The graphics thread made the GIF thread: joined after it.
    {
        std::lock_guard lock(s_gifMutex);
    }
    s_gifWake.notify_all();
    join(s_gifThread);

}

namespace
{
struct Joiner
{
    ~Joiner() { shutdown(); }
} s_joiner;
} // namespace
} // namespace GraphicsThread
