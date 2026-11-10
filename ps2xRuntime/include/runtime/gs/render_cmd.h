
#pragma once
#include "runtime/render/rdraw.h"
#if !defined(DK_RENDER_DLL) // (dk_render.dll sees no GS type: docs/gs-removal-plan.md rule 6)
#include "runtime/gs/gs_types.h"
#include "runtime/gs/render_data.h"
#endif
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#ifndef PS2X_GS_EMULATION
#error "PS2X_GS_EMULATION must be defined (ps2_runtime compile definitions)"
#endif
#if !defined(DK_RENDER_DLL) && defined(_WIN32) && !PS2X_GS_EMULATION
#define PS2X_RENDER_CLIENT 1

#else
#define PS2X_RENDER_CLIENT 0
#endif


struct GSNativeTarget;           // the backend's drawing interface (gs/hw/gs_native_target.h)
class GSNativeShadowFrame;       // real-time shadows (gs/hw/gs_native_shadow.h)
struct GSNativeShadowCastContext;

struct RenderFrame;

#if PS2X_RENDER_CLIENT
struct DkCmd; // a command of dk_render.dll (src/lib/render/dk_render_abi.h)
struct DkRes ;
struct GSNativeFontBatch; // runtime/gs/gs_native_font.h

class RenderCmd
{
public:
    RenderCmd(DkCmd *handle, std::shared_ptr<const Native2D> native2d) : m_handle(handle), m_native2d(std::move(native2d)) {}
    ~RenderCmd(); // the DLL frees its command on the GS thread

    RenderCmd(const RenderCmd &) = delete;
    RenderCmd &operator=(const RenderCmd &) = delete;
    DkCmd *handle() const { return m_handle; } // (null: one of the exe's commands)
    const char *typeName() const; // the command's kind (logs, the stream hash)

    // A native port's 2D draw: the list it was made from.
    const Native2D *native2d() const { return m_native2d.get(); }
    const NativeDraws *nativeDraws() const { return m_draws.get(); }
    void setNativeDraws(std::shared_ptr<const NativeDraws> draws) { m_draws = std::move(draws); }
    // A movie picture (makeMoviePicture): the picture the next uploads stand for.
    struct Movie
    {
        std::shared_ptr<const std::vector<uint8_t>> rgba;
        uint32_t width = 0, height = 0;
    };
    const Movie *movie() const { return m_movie.get(); }
    void setMovie(Movie movie) { m_movie = std::make_shared<const Movie>(std::move(movie)); }
    // A display dump (makeDisplayDump): its request and file.
    struct Dump
    {
        GSPresentationRequest request;
        std::string path;
    };
    const Dump *dump() const { return m_dump.get(); }
    void setDump(Dump dump) { m_dump = std::make_shared<const Dump>(std::move(dump)); }
    // An owner mark (RenderExec::makeOwnerMark): its owner and flags.
    bool ownerMark(uint32_t &owner, uint32_t &flags) const
    {
        if (!m_mark)
            return false;   
        owner = m_owner;
        flags = m_flags;
        return true;

    }
    void setMark(uint32_t owner, uint32_t flags)
    {
        m_mark = true;
        m_owner = owner;
        m_flags = flags;
    }

    // Phase 3 stage 4: state fields the command draws with from its own data.
    const NativeDraws::State *ownState() const { return m_own.get(); }
    void setOwnState(std::shared_ptr<const NativeDraws::State> state) { m_own = std::move(state); }

    const std::vector<uint64_t> &textures() const { return m_textures; }
    void setTextures( std::vector<uint64_t> tex0) { m_textures = std::move(tex0); }
    const GSNativeFontBatch *font() const { return m_font.get(); }
    DkRes *fontRes() const { return m_fontRes; }
    void setFont(std::shared_ptr<const GSNativeFontBatch> batch, DkRes *res)
    {

        m_font = std::move(batch);
        m_fontRes = res ;
    }

private:
    DkCmd *m_handle;
    std::vector<uint64_t> m_textures;

    std::shared_ptr<const GSNativeFontBatch> m_font;
    DkRes *m_fontRes = nullptr;
    std::shared_ptr<const Native2D> m_native2d;
    std::shared_ptr<const NativeDraws::State> m_own;
    std::shared_ptr<const NativeDraws> m_draws;
    std::shared_ptr<const Movie> m_movie;
    std::shared_ptr<const Dump> m_dump;

    bool m_mark = false;
    uint32_t m_owner = 0, m_flags = 0;
};
#else
class RenderCmd
{
public:
    virtual ~RenderCmd() = default;
    // Render thread; `env`: the drawing contexts where the command is.
    virtual void draw(GSNativeTarget &target, const rdraw::NativeEnv &env) = 0;
    virtual void shadowCollect(GSNativeShadowFrame &, const rdraw::NativeEnv &) {}
    // Draws the depth of the command into one shadow map cascade.
    virtual void shadowCast(GSNativeShadowCastContext &, const rdraw::NativeEnv &) {}
    virtual bool inFramePass() const { return true; }
#if !defined(DK_RENDER_DLL)
    // A native port's 2D draw (the GS frontend applies it, no draw() call).
    virtual const Native2D *native2d() const { return nullptr; }
    virtual const NativeDraws *nativeDraws() const { return nullptr; }
    // An owner mark (RenderExec::makeOwnerMark): its owner and flags.
    virtual bool ownerMark(uint32_t &, uint32_t &) const { return false; }
#endif

    // The frame that recorded the command (RenderExec::frameRecord).
    const std::shared_ptr<RenderFrame> &frame() const { return m_frame; }

private:
    friend struct RenderExecAccess;
    std::shared_ptr<RenderFrame> m_frame;
};
#endif

#if !defined(DK_RENDER_DLL)
using RenderStateWrites = std::shared_ptr<const std::vector<uint8_t>>;

namespace FrameRecorder
{
    void beginFrame();
    void endFrame();

    uint64_t record( std::shared_ptr<RenderCmd> cmd, RenderStateWrites writes = nullptr);

    constexpr uint32_t kAnchorMark = 0xA5u; // in the NOP's NUM field
    inline uint32_t anchorWord0(uint64_t id) { return kAnchorMark << 16 | uint32_t(id & 0xFFFF); }
    inline uint32_t anchorWord1(uint64_t id) { return uint32_t(id >> 16) & 0xFFFFFFu; }
    inline bool isAnchor(uint32_t word0) { return (word0 >> 16) == kAnchorMark; }

    bool reachAnchor(uint32_t word0, uint32_t word1);
    void insertAtDma(std::shared_ptr<RenderCmd> cmd, RenderStateWrites writes = nullptr);
    // EE thread, outside a DMA kick: after all queued GS work.
    void insertNow(std::shared_ptr<RenderCmd> cmd);
}

namespace RenderSink
{
    void frame(const std::shared_ptr<RenderCmd> &cmd, uint64_t frameId, bool ended);
    void frameEnd(uint64_t frameId) ;
    void consume(const std::shared_ptr<RenderCmd> &cmd, const uint8_t *writes, uint32_t size);
    // A command FrameRecorder no longer keeps: freed on the GS thread.
    void drop(std::shared_ptr<RenderCmd> cmd);

#if PS2X_RENDER_CLIENT 
    // The GS side takes the commands (render_recorder.cpp; set once).
    using Consumer = void (*)(void *user, const std::shared_ptr<RenderCmd> &cmd, const uint8_t *writes, uint32_t size);
    void setConsumer(Consumer consumer, void *user);
#endif
}
#endif

#if !PS2X_RENDER_CLIENT
// The renderer's side (render_exec.cpp; also inside dk_render.dll).

namespace RenderExec
{
    // EE thread: `cmd` belongs to frame `frameId` (RenderSink::frame).   
    void frameRecord(const std::shared_ptr<RenderCmd> &cmd, uint64_t frameId, bool ended);
    void frameEnd(uint64_t frameId);
    // A command nothing else keeps: freed on the GS thread (next execute).
    void dropLater(std::shared_ptr<RenderCmd> cmd );

    // The GS frontend takes the commands (RenderSink::consume); set once.
    using Consumer = void (*)(void *user, const std::shared_ptr<RenderCmd> &cmd, const uint8_t *writes, uint32_t size);
    void setConsumer(Consumer consumer, void *user);
    void consume(const std::shared_ptr<RenderCmd> &cmd, const uint8_t *writes, uint32_t size);

    void execute(RenderCmd &cmd, const rdraw::NativeEnv &env);

    // The renderer runs the commands.
    using Executor = void (*)(void *user, RenderCmd &cmd, const rdraw::NativeEnv &env);
    void setExecutor(Executor executor, void *user);

    struct FrameItem
    {
        std::shared_ptr<RenderCmd> cmd;
        rdraw::NativeEnv env;
    };

    using FrameExecutor = void (*)(void *user, const FrameItem *items, size_t count);  
    using FrameWanted = bool (*)(void *user);
    void setFrameExecutor(FrameExecutor executor, FrameWanted wanted, void *user);
}
#endif   

#if !defined(DK_RENDER_DLL)
// The make functions (both sides; exe with dk_render.dll: dk_render_client.cpp).
namespace RenderExec
{
    // Saves the display image (as presented for `request`) to `path` (PPM).
    std::shared_ptr<RenderCmd> makeDisplayDump(const GSPresentationRequest &request, const char *path);

    constexpr uint32_t kOwnerDrop = 1;   // flags: its packets are not drawn
    constexpr uint32_t kOwnerNative = 2; // flags: drawn by its native port, the packets' draws and transfers are not
    std::shared_ptr<RenderCmd> makeNative2D(std::shared_ptr<const Native2D> draw);
    std::shared_ptr<RenderCmd> makeOwnerMark(uint32_t owner, uint32_t flags);   

    bool directMovies();
    void setDirectMovies(bool on);
    std::shared_ptr<RenderCmd> makeMoviePicture(std::shared_ptr<const std::vector<uint8_t>> rgba, uint32_t width, uint32_t height);
}
#endif
