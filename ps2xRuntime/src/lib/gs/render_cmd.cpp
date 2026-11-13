#include "runtime/gs/render_cmd.h"
#include "runtime/ps2_det.h"
#include "runtime/ps2_graphics_thread.h"
#include "../ps2_runtime_hooks.h"

#include <atomic>
#include <cstdio>
#include <deque>
#include <functional>
#include <unordered_map>
#include <vector>

namespace
{
    // A game frame (the game's draw pass, or one vsync tick without those hooks).

    struct Frame
    {
        uint64_t id = 0 ;
        uint64_t tick = 0;
        bool byTick = false; // no draw pass hooks: one vsync tick, never waited for
        bool ended = false;
    };
}

namespace 
{
    struct Entry
    {
        std::shared_ptr<RenderCmd> cmd;
        RenderStateWrites writes;
        uint64_t tick;
        uint64_t frame = 0;
        uint32_t pinned = 0;
        bool reached = false; 
        bool repeat = false;
        uint32_t tagWord = 0; // (repeat: the anchor tag's first word; another there is the game's tag over a stale anchor)
    };
    std::deque<Entry> g_entries;
    uint64_t g_firstId = 1;
    uint64_t g_nextId = 1;
    constexpr uint64_t kKeepTicks = 8, kKeepFrames = 4;
    constexpr size_t kMaxEntries = 1u << 15;
    Frame g_frame;
    bool g_haveFrame = false;
    bool g_framesKnown = false;
    uint64_t g_frameIds = 0;

    Frame newFrame(bool byTick, uint64_t tick)
    {
        Frame f;

        f.id = ++g_frameIds;
        f.tick = tick;
        f.byTick =  byTick;
        f.ended = byTick;
        return f;
    }

    void deliver(const std::shared_ptr<RenderCmd> &cmd, const RenderStateWrites &writes)
    {

        RenderSink::consume(cmd, writes ? writes->data() : nullptr, writes ? uint32_t(writes->size()) : 0u);
    }
}

namespace
{
    std::atomic<bool> g_directMovies{false};
}
bool RenderExec::directMovies()   
{
    return g_directMovies.load(std::memory_order_relaxed);
}
void RenderExec::setDirectMovies(bool on)
{
    g_directMovies.store(on, std::memory_order_relaxed);
}


void FrameRecorder::beginFrame()
{
    if (g_haveFrame && !g_frame.ended)
    {
        g_frame.ended =  true;
        RenderSink::frameEnd(g_frame.id);
    }
    g_framesKnown = true;
    g_frame = newFrame(false, PS2Det::vsyncTick());
    g_haveFrame = true;
}

void FrameRecorder::endFrame()
{
    if (g_haveFrame)
    {  
        g_frame.ended = true;
        RenderSink::frameEnd(g_frame.id);
    }
}

uint64_t FrameRecorder::record( std::shared_ptr<RenderCmd> cmd, RenderStateWrites writes)
{
    const uint64_t tick = PS2Det::vsyncTick();
    const uint64_t frame = g_haveFrame ? g_frame.id : 0;  
    while (!g_entries.empty() && ((g_entries.front().tick + kKeepTicks < tick && g_entries.front().frame + kKeepFrames < frame) || g_entries.size() >= kMaxEntries))
    {
        if (g_entries.front().cmd)
            RenderSink::drop(std::move(g_entries.front().cmd));
        g_entries.pop_front();
        ++g_firstId;
    }
    if (g_entries.empty())
        g_firstId = g_nextId;
    if (!g_framesKnown && (!g_haveFrame || g_frame.tick != tick))
    {
        g_frame = newFrame(true, tick);
        g_haveFrame = true;
    }
    if ( cmd)

        RenderSink::frame(cmd, g_frame.id, g_frame.ended); 
    g_entries.push_back(Entry{std::move(cmd), std::move(writes), tick, g_haveFrame ? g_frame.id : 0});
    return g_nextId++;
}

bool FrameRecorder::reachAnchor(uint32_t word0, uint32_t word1)
{
    if (!isAnchor(word0))
        return false;
    if (g_nextId == g_firstId)
        return true;
    const uint64_t low = word0 & 0xFFFF; 
    uint64_t id;
    if ((word1 >> 24) == 0) // a NOP: the high id bits
        id = uint64_t(word1 & 0xFFFFFF) << 16 | low;
    else // the game's VIF code: the newest kept id with these low bits
        id = (g_nextId - 1) - (((g_nextId - 1) - low) & 0xFFFF);
    if (id < g_firstId || id >= g_nextId)
    {
        static uint64_t late = 0;
        if ((++late & (late - 1)) == 0)
            std::fprintf(stderr, "[render] anchor %llu reached after its command expired: not drawn (%llu so far, t%llu, kept %llu..%llu, word0 %08X word1 %08X)\n", (unsigned long long)id, (unsigned long long)late, (unsigned long long)PS2Det::vsyncTick(), (unsigned long long)g_firstId, (unsigned long long)g_nextId, word0, word1);
        return true;
    }
    const Entry &e = g_entries[size_t(id - g_firstId)];
    if (g_haveFrame && e.frame != g_frame.id) // (recorded in an older draw pass: a persistent chain or stale heap data)
    {
        static uint64_t old = 0;
        if ((++old & (old - 1)) == 0)
            std::fprintf(stderr, "[render] anchor %llu of draw pass %llu reached in pass %llu (t%llu, recorded t%llu, %llu so far)\n", (unsigned long long)id, (unsigned long long)e.frame, (unsigned long long)g_frame.id, (unsigned long long)PS2Det::vsyncTick(), (unsigned long long)e.tick, (unsigned long long)old);
    }
    insertAtDma(e.cmd, e.writes);
    return true;
}

void frameRecorderPinAnchor(uint64_t id, uint32_t tagAddr)
{
    if (id >= g_firstId && id < g_nextId)
        g_entries[size_t(id - g_firstId)].pinned = (tagAddr & 0x1FFFFFFFu) | 1u; // (bit 0: set; tags are qword aligned)
} 

void frameRecorderPinAnchorRepeat(uint64_t id, uint32_t tagAddr, uint32_t tagWord)
{
    if (id >= g_firstId && id < g_nextId)
    {
        Entry &e =  g_entries[size_t(id - g_firstId)];
        e.pinned = (tagAddr & 0x1FFFFFFFu) | 1u;
        e.repeat = true;
        e.tagWord = tagWord ;
    }
}

int frameRecorderReachAnchorAt(uint32_t word0, uint32_t word1, uint32_t tagAddr, uint32_t tagWord)
{
    if (!FrameRecorder::isAnchor(word0))
        return -1;
    if (g_nextId == g_firstId)
        return 1;
    const uint64_t low = word0 & 0xFFFF;
    uint64_t id;

    if ((word1 >> 24) == 0)
        id = uint64_t(word1 & 0xFFFFFF) << 16 | low;
    else
        id = (g_nextId - 1) - (((g_nextId - 1) - low) & 0xFFFF) ;
    if (id >= g_firstId && id < g_nextId)
    {
        Entry &e = g_entries[size_t(id - g_firstId)];
        if (e.pinned)
        {
            if ((e.reached && !e.repeat) || (e.pinned & ~1u) != (tagAddr & 0x1FFFFFFFu) || (e.repeat && tagWord != e.tagWord))
                return 0;
            e.reached = true;
        }
    }
    return FrameRecorder::reachAnchor(word0, word1) ? 1 : -1;
}

namespace
{
    struct TagBucket 
    {
        uint64_t frame = 0;
        std::vector<std::shared_ptr<RenderCmd>> cmds;  
    };
    std::unordered_map<uint32_t, TagBucket> g_tagCmds;
}

void frameRecorderRecordAt(std::shared_ptr<RenderCmd> cmd, uint32_t tagAddr)
{
    FrameRecorder::record(cmd);
    const uint64_t frame = g_haveFrame ? g_frame.id : 0;
    if (g_tagCmds.size() > 2048)
        for (auto it = g_tagCmds.begin(); it != g_tagCmds.end();)
            it = it->second.frame + kKeepFrames < frame ? g_tagCmds.erase(it) : std::next(it);
    TagBucket &b = g_tagCmds[tagAddr & 0x1FFFFFFFu];
    if (b.frame != frame) // (left over from an older frame: the game reuses the address)
    {
        if (!b.cmds.empty()) // (never reached by the DMA walk: not drawn)

        {
            static uint32_t lost = 0;
            if ((++lost & (lost - 1)) == 0)
                std::fprintf(stderr, "[render] %zu draws at tag %08X never reached by the DMA walk (t%llu, %u so far)\n", b.cmds.size(), tagAddr, (unsigned long long)PS2Det::vsyncTick(), lost);
        }
        b.cmds.clear();
        b.frame = frame;
    }
    b.cmds.push_back(std::move(cmd));
}

// A DMA kick walks the tag at `tagAddr`: its commands go to the GIF stream here.
bool frameRecorderReachTag(uint32_t tagAddr)
{ 
    if(g_tagCmds.empty())

        return false;
    const auto it = g_tagCmds.find(tagAddr & 0x1FFFFFFFu);
    if (it == g_tagCmds.end() || it->second.cmds.empty())
        return false;
    std::vector<std::shared_ptr<RenderCmd>> cmds = std::move(it->second.cmds);
    g_tagCmds.erase(it); 
    for (auto &c : cmds)
        FrameRecorder::insertAtDma(std::move(c));

    return true;
}

void FrameRecorder::insertAtDma(std::shared_ptr<RenderCmd> cmd, RenderStateWrites writes)
{
    if ( !cmd && !writes)
        return;
    ps2_runtime_hooks::dmaInsert([cmd = std::move(cmd), writes = std::move(writes)] { deliver(cmd, writes); });
}

void FrameRecorder::insertNow(std::shared_ptr<RenderCmd> cmd)
{

    std::function<void()> run = [cmd = std::move(cmd)] { deliver(cmd, nullptr); } ;
    if (!GraphicsThread::deferPrivWrite(run))

        run();
}
