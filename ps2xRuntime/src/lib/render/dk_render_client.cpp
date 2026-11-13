#if defined(_WIN32)

#include "dk_render_abi.h"
#include "render_core.h"
#include "render_translate.h" 
#include "../object_pool.h"
#include "../gs/hw/gs_hw_quality_internal.h"
#include "runtime/gs/gs_frontend.h"
#include "runtime/gs/gs_native_blob.h"
#include "runtime/gs/gs_native_font.h"
#include "runtime/gs/gs_native_map.h"
#include "runtime/gs/gs_native_model.h"
#include "runtime/gs/gs_native_post.h"
#include "runtime/gs/render_cmd.h"
#include "runtime/ps2_memory.h"
#include "runtime/gs/gs_hw_scale.h"
#include "runtime/gs/gs_widescreen.h"
#include "runtime/gs/gs_window_present.h"
#include "runtime/ps2_det.h"
#include "runtime/ps2_graphics_thread.h"
#include "runtime/ps2_perf.h"   


#include <atomic>
#include <cstdint>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#ifndef NOMINMAX
#define NOMINMAX
#endif
#ifndef WIN32_LEAN_AND_MEAN  
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>

void renderWorldDrawn( uint32_t frame);
void renderModelsDrawn(uint32_t frame);


namespace 
{
    std::string toUtf8( const std::wstring &text) 
    {   
        if (text.empty())
            return std::string();
        const int n = WideCharToMultiByte(CP_UTF8, 0, text.data(), int(text.size()), nullptr, 0, nullptr, nullptr);
        if (n <= 0)
            return std::string();

        std::string out(size_t(n), '\0');
        WideCharToMultiByte(CP_UTF8, 0, text.data(), int(text.size()), out.data(), n, nullptr, nullptr);
        return out;
    }

    [[noreturn]] void fail(const std::wstring &text)
    {
        std::fprintf(stderr, "[render] %s\n", toUtf8(text).c_str());
        std::fflush(stderr );
        if(!PS2Det::enabled())
            MessageBoxW(nullptr, text.c_str(), L"Drakengard", MB_OK | MB_ICONERROR);
        std::_Exit(1);
    }

    std::wstring dllPath()
    {
        std::wstring buffer(MAX_PATH, L'\0');
        for (;;)

        {
            const DWORD n = GetModuleFileNameW(nullptr, buffer.data(), DWORD(buffer.size()));
            if (n == 0)
            {
                buffer.clear() ;
                break;
            }
            if (n < buffer.size())
            {
                buffer.resize(n);
                break;
            }
            buffer.resize(buffer.size() * 2) ;
        } 
        const size_t slash = buffer.find_last_of(L"\\/");
        return (slash == std::wstring::npos ? std::wstring() : buffer.substr(0, slash + 1)) + L"dk_render.dll";

    }

    const DkRenderApi &loadApi()
    {  
        static DkRenderApi api{};
        api.size = sizeof(DkRenderApi);


        const std::wstring path = dllPath();
        const HMODULE module = LoadLibraryW(path.c_str());
        if (!module)
        {
            const DWORD error = GetLastError();
            fail(L"Cannot load the renderer (dk_render.dll).\nTried: " + path + L"\nWindows error " + std::to_wstring(unsigned(error)) + L".\nPut dk_render.dll in the same folder as the game.");
        }
        const auto init = reinterpret_cast<DkRenderInitFn>(GetProcAddress(module, "dk_render_init"));
        if (!init)
            fail(L"The renderer (" + path + L") has no dk_render_init. It is not a dk_render.dll of this game.");

        // The DLL keeps a pointer to it: static, not on this stack.
        static DkHostApi host{};
        host.size = sizeof( DkHostApi);
        host.detVsyncTick = [] { return PS2Det::vsyncTick(); };
        host.perfNow = [] { return PS2Perf::now(); };
        host.perfCount = []( uint32_t counter, uint32_t n) { PS2Perf::count(PS2Perf::Counter(counter), n); };  
        host.perfEnter =  [](uint32_t zone) { PS2Perf::enter(PS2Perf::Zone(zone)); };
        host.perfLeave = [] { PS2Perf::leave(); };
        host.wsWorldDrawn = &renderWorldDrawn;
        host.wsModelsDrawn = &renderModelsDrawn;
        if (!init(&host, &api, kDkRenderVersion))
            fail(L"The renderer (" + path + L") does not match this game (version " + std::to_wstring(unsigned(kDkRenderVersion)) + L").\nUse the dk_render.dll that was built together with the game.");
        if (api.size != sizeof(DkRenderApi) || !api.coreDraw)
            fail(L"The renderer (" + path + L") gave an incomplete function table.\n" + L"Use the dk_render.dll that was built together with the game.");

        if (api.perfSetEnabled)

        {
            api.perfSetEnabled(PS2Perf::g_enabled);
        }
        std::fprintf(stderr, "[render] dk_render.dll loaded (%s)\n", toUtf8(path).c_str());
        return api;
    }
}

const DkRenderApi &dkRender()
{  
    static const DkRenderApi &api = loadApi();
    return api;
}


namespace rdraw  
{
    Core::Core() = default; 
    Core::~Core() = default;
    void Core::create() { dkRender().coreCreate(); }
    bool Core::ready() const { return dkRender().coreReady(); }
    uint32_t Core::scale() const { return dkRender().coreScale(); }
    bool Core::setScale(uint32_t scale) { return dkRender().coreSetScale(scale); }
    TargetId Core::createTarget(uint32_t width, bool depth, uint32_t scale) { return dkRender().coreCreateTarget(width, depth, scale); }   
    void Core::releaseTarget(TargetId target) { dkRender().coreReleaseTarget(target); }
    uint32_t Core::targetScaleX(TargetId target ) const
    {
        uint32_t sx = 1, sy = 1;
        dkRender().coreTargetScale(target, &sx, &sy);
        return sx;
    }
    uint32_t Core::targetScaleY(TargetId target) const
    {
        uint32_t sx = 1, sy = 1;
        dkRender().coreTargetScale(target, &sx, &sy);
        return sy;
    }
    void Core::copyTexels(TargetId dst, TargetId src, uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1 )
    {
        dkRender().coreCopyTexels(dst, src, x0, y0, x1, y1);
    }
    void Core::writePixels(TargetId target, const Rect &r, const uint32_t *pixels, bool movie)
    {
        dkRender().coreWritePixels(target, &r, pixels, movie ? 1u : 0u);
    }
    void Core::writePixelsMasked( TargetId target, const Rect &r, const uint32_t *pixels, const uint8_t *mask)
    {
        dkRender().coreWritePixelsMasked(target, &r, pixels, mask);
    } 
    void Core::clearPixels(TargetId target, const Rect &r, uint32_t rgba) { dkRender().coreClearPixels(target, &r, rgba); }
    TextureId Core::createTexture(uint32_t width, uint32_t height) { return dkRender().coreCreateTexture(width, height); }
    void Core::releaseTexture(TextureId texture) { dkRender().coreReleaseTexture(texture); }
    void Core::updateTexture(TextureId texture, const Rect &r, const uint32_t *pixels) { dkRender().coreUpdateTexture(texture, &r, pixels); }
    void Core::gather(TextureId out, const Rect &area, const Gather &g) { dkRender().coreGather(out, &area, &g); }
    void Core::draw(const Batch &batch) { dkRender().coreDraw(&batch); }
    bool Core::bindNative(TargetId color, TargetId depth, const Rect &scissor) { return dkRender().coreBindNative(color, depth, &scissor); }
    void Core::unbind() { dkRender().coreUnbind(); }
    void Core::restoreState() { dkRender().coreRestoreState(); }
    void Core::present(const Present &p) { dkRender().corePresent(&p); }
    void Core::flush() { dkRender().coreFlush(); }
    Stats Core::stats(bool reset)
    {
        Stats s;
        dkRender().coreStats(&s, reset);  
        return s;
    }
}

namespace GSHwQualityFrame
{
    void latch(uint64_t vsyncTick) { dkRender().qualityLatch(vsyncTick); }
    bool deflicker() { return dkRender().qualityDeflicker(); }

}


namespace
{
    template <class T, class Make> DkRes *resOf(const T &obj, Make make)
    {
        if ( !obj.gpu)
            if (DkRes *r = make(obj))
                obj.gpu = std::shared_ptr<void>(r, [](void *p) { dkRender().resRelease(static_cast<DkRes *>(p)); });
        return static_cast<DkRes *>(obj.gpu.get());
    }

    DkRes *texRes(const std::shared_ptr<const GSNativeTexture> &t)
    {
        if (!t)
            return nullptr;
        return resOf( *t, [](const GSNativeTexture &t) {
            const DkTextureView v{t.width, t.height, t.rgba.data(), uint32_t(t.rgba.size())};
            return dkRender().resTexture(&v); 
        });
    }

    DkRes *meshRes(const std::shared_ptr<const GSNativeMesh> &m)
    {
        if (!m)
            return nullptr;
        return resOf(*m, [](const GSNativeMesh &m ) {
            std::vector<DkMeshGroupView> groups(m.groups.size());
            for (size_t i = 0; i < groups.size(); ++i)
            {

                const GSNativeMeshGroup &g = m.groups[i];
                groups[i] = {g.firstIndex, g.indexCount, g.type, g.tfx, g.passes, g.tcc, g.envMesh, texRes(g.texture), texRes(g.envTexture )};
            }
            const DkMeshView v{m.vertices.data(), uint32_t(m.vertices.size()), m.indices.data(), uint32_t(m.indices.size()),
                               groups.data(), uint32_t(groups.size())};
            return dkRender().resMesh(&v);
        });
    }

    DkRes *mapMeshRes(const std::shared_ptr<const GSNativeMapMesh> &m)
    {
        if (!m)
            return nullptr;
        return resOf(*m, [](const GSNativeMapMesh &m) {
            const DkMapMeshView v{m.vertices.data(), uint32_t(m.vertices.size()), m.indices.data(), uint32_t(m.indices.size()),
                                  m.groups.data(), uint32_t(m.groups.size())};
            return dkRender().resMapMesh(&v);
        });
    }

    DkRes *skyMeshRes(const std::shared_ptr<const GSNativeSkyMesh> &m)
    {
        if (!m)
            return nullptr;
        return resOf(*m, [](const GSNativeSkyMesh &m) {
            const DkSkyMeshView v{m.vertices.data(), uint32_t(m.vertices.size()), m.indices.data(), uint32_t(m.indices.size())};
            return dkRender().resSkyMesh(&v);
        });
    }

    DkRes *fontRes(const std::shared_ptr<const GSNativeFontData> &f)
    {
        if(!f)
            return nullptr;
        return resOf(*f, [](const GSNativeFontData &f) {
            const DkFontView v{f.cell, f.cellBytes, f.cells, {f.bitmap.data(), uint32_t(f.bitmap.size())}};  
            return dkRender().resFont( &v);
        });
    }

    using Bones = std::vector<std::array<float, 16>>;
    struct BonesRes  
    {
        std::weak_ptr<const Bones> owner;
        std::shared_ptr<DkRes> res;
    };
    std::unordered_map<const Bones *, BonesRes> g_bonesRes;
    size_t g_bonesSweepAt = 1024;


    DkRes *bonesRes(const std::shared_ptr<const Bones> &b)
    {
        if (!b)
            return nullptr;
        BonesRes &e = g_bonesRes[b.get()];
        if (!e.res || e.owner.lock() != b)
        {
            e.owner = b;
            e.res = std::shared_ptr<DkRes>(dkRender().resBones(reinterpret_cast<const float(*)[16]>(b->data()), uint32_t(b->size())), [](DkRes *r) { dkRender().resRelease(r); });
        }
        DkRes *r = e.res.get();
        if (g_bonesRes.size() >= g_bonesSweepAt)
        {

            for (auto it = g_bonesRes.begin(); it != g_bonesRes.end();)
                it = it->second.owner.expired() ? g_bonesRes.erase(it) : std::next(it);
            g_bonesSweepAt = std::max<size_t>(1024, g_bonesRes.size() * 2);
        }
        return r;
    }

    std::unique_ptr<RenderCmd> own(DkCmd *h)
    {
        return h ? std::make_unique<RenderCmd>(h, nullptr) : nullptr;
    } 
}


RenderCmd::~RenderCmd()
{
    if (m_handle)   
        dkRender().cmdRelease(m_handle);
}   

const char *RenderCmd::typeName() const
{
    if (m_handle)
        return dkRender().cmdTypeName(m_handle);
    if (m_movie)

        return "class `anonymous namespace'::MoviePicture";
    if (m_dump)
        return "class `anonymous namespace'::DisplayDump";
    if (m_mark)  

        return "class `anonymous namespace'::OwnerMark";

    if (m_font)
        return "class gs_native_font::FontDraw";
    return m_draws ? "class `anonymous namespace'::NativeDrawsCmd" : "class `anonymous namespace'::Native2DCmd";  

}

namespace
{
    RenderSink::Consumer g_consumer = nullptr;
    void *g_consumerUser = nullptr;
}

namespace RenderSink
{
    void frame(const std::shared_ptr<RenderCmd> &cmd, uint64_t frameId, bool ended) 
    {
        dkRender().frameRecord(cmd ? cmd->handle() : nullptr, frameId, ended);
    }  
    void frameEnd(uint64_t frameId)
    {
        dkRender().frameEnd(frameId);
    }
    void setConsumer( Consumer consumer, void *user)
    {
        g_consumer = consumer;
        g_consumerUser = user;
    }   
    void consume(const std::shared_ptr<RenderCmd> &cmd, const uint8_t *writes, uint32_t size)
    {
        if (g_consumer)
            g_consumer(g_consumerUser, cmd, writes, size);
    }

    void drop(std::shared_ptr<RenderCmd> cmd)
    {
        cmd.reset(); // (the DLL frees its command on the GS thread)
    }
}

namespace NativeDraw
{   
    std::unique_ptr<RenderCmd> makeModelDraw( GSNativeModelParams params)
    {
        DkModelView v{};
        v.mesh = meshRes(params.mesh);
        v.typeMask = params.typeMask;
        std::memcpy(v.screen, params.screen, sizeof v.screen );
        std::memcpy(v.lightDir, params.lightDir, sizeof v.lightDir);
        std::memcpy(v.lightColor, params.lightColor, sizeof v.lightColor);
        std::memcpy(v.clampMax, params.clampMax, sizeof v.clampMax);
        std::memcpy( v.fog, params.fog, sizeof v.fog);
        v.depthBias = params.depthBias;
        v.alpha = params.alpha;
        v.squareLight = params.squareLight;
        v.noShadow = params.noShadow;
        v.placed = params.placed;
        v.envScale = params.envScale;
        std::memcpy(v.colorAdd, params.colorAdd, sizeof v.colorAdd);
        v.context = params.context;
        static_assert(sizeof(params.bones[0]) == 64 && sizeof(params.instances[0]) == 128);
        v.bones = reinterpret_cast<const float(*)[16]>(params.bones.data());
        v.boneCount = uint32_t(params.bones.size());

        v.instances = reinterpret_cast<const float(*)[32]>(params.instances.data());
        v.instanceCount = uint32_t(params.instances.size());
        std::vector<DkPoseView> poses(params.instancePoses.size());
        for (size_t i = 0; i < poses.size(); ++i)
            poses[i] = {params.instancePoses[i].id, bonesRes(params.instancePoses[i].bones)};
        v.poses = poses.data();
        v.poseCount = uint32_t(poses.size());
        return own(dkRender().cmdModel(&v));
    }
    std::unique_ptr<RenderCmd> makeMapDraw(GSNativeMapParams params)
    {
        DkMapView v{};
        v.mesh = mapMeshRes( params.mesh);
        std::vector<rdraw::TexMode> slots(params.tex0.size());
        for (size_t i = 0; i < slots.size(); ++i)
            slots[i] = rtrans::texMode(params.tex0[i]);
        v.slots = slots.data();   
        v.slotCount = uint32_t(slots.size());
        std::vector<DkRes *> textures(params.textures.size());
        for (size_t i = 0; i < textures.size(); ++i)
            textures[i] = texRes(params.textures[i]);
        v.textures = textures.data();
        v.textureCount = uint32_t(textures.size()) ;
        std::memcpy( v.matrix, params.matrix, sizeof v.matrix);
        std::memcpy(v.origin, params.origin, sizeof v.origin);
        std::memcpy(v.camera, params.camera, sizeof v.camera);
        std::memcpy( v.fog, params.fog, sizeof v.fog);
        std::memcpy(v.ramp, params.ramp, sizeof v.ramp) ;
        v.aref = params.aref;
        v.colourOnly = params.colourOnly;
        v.worldMatrix = params.worldMatrix;  

        std::unique_ptr<RenderCmd> cmd = own(dkRender().cmdMap(&v));
        if ( cmd)
            cmd->setTextures(std::move(params.tex0));
        return cmd;
    }
    std::unique_ptr<RenderCmd> makeSkyDraw(GSNativeSkyParams params)
    {
        DkSkyView v{};
        std::vector<DkSkyCellView> cells(params.cells.size());
        for (size_t i = 0; i < cells.size(); ++i)
        {
            const GSNativeSkyCell &c = params.cells[i];
            cells[i] = {skyMeshRes(c.mesh), texRes(c.texture), rtrans::texMode(c.tex0), rtrans::bilinear(c.tex1), {c.row[0], c.row[1]}};
        }
        v.cells = cells.data();
        v.cellCount = uint32_t(cells.size());
        std::memcpy(v.m1, params.m1, sizeof v.m1);
        std::memcpy(v.m2, params.m2, sizeof v.m2);
        std::memcpy(v.scale, params.scale, sizeof v.scale);
        std::memcpy( v.fog, params.fog, sizeof v.fog);
        return own(dkRender().cmdSky(&v));
    }
    std::unique_ptr<RenderCmd> makeFontDraw( std::shared_ptr<const GSNativeFontBatch> batch)
    {
        if (!batch )
            return nullptr;
        DkRes *font = fontRes(batch->font);
        auto cmd = std::make_unique<RenderCmd>(nullptr, nullptr); 
        cmd->setFont(std::move(batch), font);
        return cmd;
    }
    void fontAddGlyph(RenderCmd &, GSNativeFontBatch &batch, const GSNativeFontGlyph &glyph)
    {
        std::lock_guard lock(batch.mutex);
        batch.glyphs.push_back(glyph);
    }
    std::unique_ptr<RenderCmd> makeBlobDraw(GSNativeBlobParams params)

    {
        std::unique_ptr<RenderCmd> cmd = own(dkRender().cmdBlob(params.quads.data(), uint32_t(params.quads.size()))) ;
        if ( cmd)
            cmd->setTextures({params.tex0});
        return cmd;
    }
}

namespace GSNativePost
{
    std::unique_ptr<RenderCmd> makeDraw()
    {
        return own(dkRender().cmdPost());

    }
}

bool renderMakeNativeDraws(const std::shared_ptr<const Native2D> &draw, NativeDraws &out);

namespace RenderExec
{
    // (from a pool: made for every port call, thousands a frame in the sky missions)
    void resetNativeDraws( NativeDraws &d)
    {
        d.items.clear();
        d.prims.clear();
        d.transfers.clear(); 
        d.images.clear();
        d.privileged.clear();
        d.end =  {};
        d.endSet[0] =  d.endSet[1] = d.endSet[2] = 0;
        d.function = 0;
    }
    std::shared_ptr<RenderCmd> makeNative2D(std::shared_ptr<const Native2D> draw)
    {
        auto d = pooledShared<NativeDraws, resetNativeDraws>();
        const bool made = draw && renderMakeNativeDraws(draw, *d);
        auto cmd = std::make_shared<RenderCmd>(nullptr, std::move(draw));
        if (made)
            cmd->setNativeDraws(std::move(d));
        return cmd;
    }
    std::shared_ptr<RenderCmd> makeOwnerMark(uint32_t owner, uint32_t flags )
    {
        auto cmd =  std::make_shared<RenderCmd>(nullptr, nullptr);
        cmd->setMark(owner, flags);
        return cmd;
    } 
    std::shared_ptr<RenderCmd> makeMoviePicture(std::shared_ptr<const std::vector<uint8_t>> rgba, uint32_t width, uint32_t height)
    {
        auto cmd = std::make_shared<RenderCmd>(nullptr, nullptr);
        cmd->setMovie({std::move(rgba), width, height});
        return cmd ;
    }
    std::shared_ptr<RenderCmd> makeDisplayDump(const GSPresentationRequest &request, const char *path)
    {
        auto cmd = std::make_shared<RenderCmd>(nullptr, nullptr);
        cmd->setDump({request, path ? path : ""});
        return cmd;
    }
}


namespace GSHwQuality
{
    void setAntiAlias(uint32_t mode) { dkRender().setAntiAlias(mode); }
    uint32_t antiAlias() { return dkRender().antiAlias(); }
    void setTextureFilter(uint32_t level) { dkRender().setTextureFilter(level); }
    uint32_t textureFilter() { return dkRender().textureFilter(); }
    void setDeflicker(bool on) { dkRender().setDeflicker(on); }   
    bool deflicker() { return dkRender().deflicker(); }
    void setShadows(uint32_t mode) { dkRender().setShadows(mode); }
    uint32_t shadows() { return dkRender().shadows(); }
    void setCharacters(uint32_t mode) { dkRender().setCharacters(mode); }
    uint32_t characters() { return dkRender().characters(); }
    void setCelParams(const CelParams &params) { dkRender().setCelParams(&params); }
    CelParams celParams()
    {
        CelParams p;
        dkRender().celParams(&p);
        return p;
    }
    void setPostParams( const PostParams &params) { dkRender().setPostParams(&params); }
    PostParams postParams()
    {
        PostParams p;
        dkRender().postParams(&p);

        return p;
    }

    bool postWanted() { return dkRender().postWanted(); }
    void setSaveHandler(void (*save)()) { dkRender().setSaveHandler(save); }
    void save() { dkRender().save(); }
}

namespace GSHwScale
{
    void request(uint32_t scale) { dkRender().scaleRequest(scale); }
    uint32_t requested() { return dkRender().scaleRequested(); }
    void setDynamic(float minFraction) { dkRender().scaleSetDynamic(minFraction); }
}


namespace GSWindowPresent
{
    void setWindow(void *hwnd) { dkRender().setWindow(hwnd); }
    void setClientSize(uint32_t width, uint32_t height) { dkRender().setClientSize(width, height); }
    void setAspect(float aspect) { dkRender().setAspect(aspect); }
    void setVsync( bool on) { dkRender().setVsync(on); }
    bool active() { return dkRender().active(); }
    uint64_t presentedFrames() { return dkRender().presentedFrames(); }
    void setUiRenderer(void (*draw)(void *user), void *user) { dkRender().setUiRenderer(draw, user); }
    void uiLock() { dkRender().uiLock(); }
    void uiUnlock() { dkRender().uiUnlock(); }
    ID3D11Device *device() { return dkRender().device(); }
    ID3D11DeviceContext *uiContext() { return dkRender().uiContext(); }
    void setPresentedCallback(void (*callback)(int64_t presentNs, uint64_t frame))
    {
        dkRender().setPresentedCallback(callback);
    }
}

#endif
