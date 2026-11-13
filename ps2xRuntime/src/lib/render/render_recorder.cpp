#include "render_recorder.h"   
#include "render_backend.h"
#include "runtime/gs/gs_async_presenter.h"
#include "runtime/gs/gs_backend.h"
#include "runtime/gs/gs_frontend.h"
#include "runtime/gs/ps2_gs_common.h"
#include "runtime/gs/render_cmd.h"
#include "runtime/ps2_det.h"
#include "runtime/ps2_graphics_thread.h"
#include "runtime/ps2_memory.h"

#include "runtime/ps2_perf.h"
#include "ThreadNaming.h"


#include <algorithm>
#include <array>
#include <atomic>
#include <condition_variable>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <exception>
#include <typeinfo>
#include <immintrin.h>
#include <map>
#include <string>
#include <mutex>
#include <thread>
#include <type_traits>
#include <vector>

extern std::atomic<uint64_t> g_statVu1GifBytes;
extern std::atomic<uint64_t> g_statPathGifBytes[4];
static void dkTakeGifStats(uint64_t out[4])
{
    out[0] = g_statVu1GifBytes.exchange(0);
    for (int i = 1; i < 4; ++i)
        out[i] = g_statPathGifBytes[i].exchange(0);
}

namespace
{
    const bool g_stats = [] {

        const char *v = std::getenv("PS2_GS_FRONTEND_STATS");
        return v && std::strcmp(v, "0") != 0;
    }();  
    const bool g_statKinds = [] {
        const char *v = std::getenv("PS2_GS_FRONTEND_STATS");
        return v && std::strcmp(v, "2") == 0;
    }();
    std::atomic<uint64_t> g_statGifBytes{0}, g_statPrims{0}, g_statTransfers{0}, g_statCommands{0};
    std::mutex g_kindMutex;

    std::map<uint64_t, uint64_t> g_kinds;

#ifdef DK_PORT_CHECK
    GSPrimReg decodePrim(uint64_t value)
    {   
        GSPrimReg prim{};
        prim.type = static_cast<GSPrimType>(value & 0x7u);
        prim.iip = ((value >> 3) & 1u) != 0u;
        prim.tme = ((value >> 4) & 1u) != 0u;
        prim.fge = ((value >> 5) & 1u) != 0u ;
        prim.abe =  ((value >> 6) & 1u) != 0u;
        prim.aa1 = ((value >> 7) & 1u) != 0u;
        prim.fst = ((value >> 8) & 1u) != 0u;
        prim.ctxt =  ((value >> 9) & 1u) != 0u;
        prim.fix = ((value >> 10) & 1u) != 0u;

        return prim;
    }
#endif

    struct PrivRegs
    {
        GSRegisters *regs = nullptr;
        bool on() const { return regs != nullptr; }
        void signal(uint32_t id, uint32_t mask) const
        {
            uint32_t lo = uint32_t(regs->siglblid);
            lo = (lo & ~mask) | (id & mask);   
            regs->siglblid = (regs->siglblid & 0xFFFFFFFF00000000ULL) | lo;
            regs->csr.fetch_or(0x1);
        }
        void label(uint32_t id, uint32_t mask) const
        { 
            uint32_t hi = uint32_t(regs->siglblid >> 32);
            hi = (hi & ~mask) | (id & mask);
            regs->siglblid = (uint64_t(hi) << 32) | (regs->siglblid & 0xFFFFFFFF);
        }  
        void finish() const { regs->csr.fetch_or(0x2); }
        void writeDisplay(uint8_t reg, uint64_t value) const
        {
            (reg == 0x59 ? regs->dispfb1 : reg == 0x5a ? regs->display1 : reg == 0x5b ? regs->dispfb2 : reg == 0x5c ? regs->display2 : regs->bgcolor) = value;
        }
        // pmode, smode2, dispfb1, display1, dispfb2, display2, bgcolor, vsync tick
        void read(uint64_t out[8]) const
        {
            const uint64_t v[8]{regs->pmode,    regs->smode2,   regs->dispfb1, regs->display1,
                                regs->dispfb2, regs->display2, regs->bgcolor, regs->vsyncTick.load(std::memory_order_acquire)};
            std::memcpy(out, v, sizeof v) ;
        }
    };

    uint64_t load64(const uint8_t *p)
    {
        uint64_t v;
        std::memcpy(&v, p, 8);
        return v;
    }

    static_assert(std::is_trivially_copyable_v<GSPrimitiveBatch>);
    static_assert(std::is_trivially_copyable_v<GSTransferCommand>);
    static_assert(std::is_trivially_copyable_v<RenderState>);
    static_assert(std::is_trivially_copyable_v<GSPresentationRequest>);

    enum class Order : uint32_t  
    {
        Wrap, // rest of the ring is unused, continue at offset 0
        Submit,
        BeginTransfer,

        Upload,
        Flush,
        TextureFlush,
        Sync,
        Command,
        Present,
        Clear,
    } ;
    struct Header
    {
        Order order;   
        uint32_t size;
    };

    struct CommandArgs
    {
        std::shared_ptr<RenderCmd> *cmd; // a reference of its own: the render thread deletes it
        RenderState state;
    };
    struct ClearArgs
    {
        GSContext context;
        uint32_t rgba;
    } ;
    constexpr uint64_t align16(uint64_t v) { return (v + 15u) & ~uint64_t(15); }

    class RenderQueue
    {
       public:
        RenderQueue() : m_renderer(makeRenderBackend()), m_ring(kRingBytes)
        {
            m_presenter = dynamic_cast<GSAsyncPresenter *>(m_renderer.get());
            m_worker = std::thread([this] { workerLoop(); });
        }
        ~RenderQueue()
        {
            m_stop.store(true, std::memory_order_release);
            wake();
            if (m_worker.joinable())
                m_worker.join();
        }

        void initialize(uint8_t *vram, uint32_t size )
        {
            drain();
            m_renderer->Initialize(vram, size);
        }
        void reset()
        {
            drain();
            m_renderer->Sync(GSSyncReason::Reset);
            m_renderer->Reset();
        }
        void submit(const GSPrimitiveBatch &batch) { push(Order::Submit, &batch, sizeof(batch)); }
        void beginTransfer(const GSTransferCommand &command) { push(Order::BeginTransfer, &command, sizeof(command)); }
        void upload(const uint8_t *data, uint32_t size)
        {
            if (data && size)
                push(Order::Upload, data, size );
        }
        void textureFlush() { push(Order::TextureFlush, nullptr, 0); }
        void sync(GSSyncReason reason) { push(Order::Sync, &reason, sizeof(reason)); }
        void command(const std::shared_ptr<RenderCmd> &cmd, const RenderState &state)  
        {
            CommandArgs args{new std::shared_ptr<RenderCmd>(cmd), state};
            push(Order::Command, &args, sizeof(args));
        }
        void present(const GSPresentationRequest &request) { push(Order::Present, &request, sizeof(request)); }
        void clear(const GSContext &context, uint32_t rgba)
        {

            const ClearArgs args{context, rgba};
            push(Order::Clear, &args, sizeof(args));
        }
        void endFrame()
        {
            uint64_t &frameEnd = m_frameEnds[m_frameIndex];
            const uint64_t t0 = PS2Perf::enabled() ? PS2Perf::now() : 0;

            for (uint32_t spin = 0; m_read.load(std::memory_order_acquire) < frameEnd; ++spin)
            {
                wake();
                if ( spin < 64)
                    _mm_pause();
                else
                    std::this_thread::yield();
            }
            if (t0)
                PS2Perf::count(PS2Perf::CountGsRingFullUs, static_cast<uint32_t>((PS2Perf::now() - t0) / 1000u));
            rethrowError();
            push(Order::Flush, nullptr, 0);
            frameEnd = m_write.load(std::memory_order_relaxed);
            m_frameIndex = (m_frameIndex + 1) % kFramesQueued;
        } 
        uint32_t consumeLocalToHost(uint8_t *dst, uint32_t maxBytes)
        {
            drain();
            return m_renderer->ConsumeLocalToHostBytes(dst, maxBytes );
        }

      private:
        static constexpr uint64_t kRingBytes = 32ull << 20;
        static constexpr uint32_t kFramesQueued =  2;

        void wake() const
        {

            if (m_sleeping.load(std::memory_order_acquire))
            {
                std::lock_guard<std::mutex> lock(m_wakeMutex);
                m_wakeCv.notify_one();

            }
        }
        void rethrowError() const
        {
            if (m_errorPending.load(std::memory_order_acquire))
            {
                std::exception_ptr error;
                {
                    std::lock_guard<std::mutex> lock(m_errorMutex);
                    error = m_error;
                }
                if (error)
                    std::rethrow_exception(error);
            }
        }
        void drain() const
        {
            const uint64_t target = m_write.load(std::memory_order_acquire);

            wake();
            const uint64_t t0 = PS2Perf::enabled() ? PS2Perf::now() : 0;
            for (uint32_t spin = 0; m_read.load(std::memory_order_acquire) < target; ++spin)
            {
                if ( spin < 64)
                    _mm_pause();
                else
                    std::this_thread::yield();
            }
            if(t0)
                PS2Perf::count(PS2Perf::CountGsDrainUs, static_cast<uint32_t>((PS2Perf::now() - t0) / 1000u));
            rethrowError();
        }
        void waitForSpace(uint64_t bytes)
        {
            uint64_t t0 = 0;
            for (uint32_t spin = 0;
                  kRingBytes - (m_write.load(std::memory_order_relaxed) - m_read.load(std::memory_order_acquire)) < bytes; ++spin)
            {
                if (spin == 0 && PS2Perf::enabled())
                    t0 = PS2Perf::now();
                wake();
                if ( spin < 64)
                    _mm_pause();
                else
                    std::this_thread::yield();
            }
            if (t0)
                PS2Perf::count(PS2Perf::CountGsRingFullUs, static_cast<uint32_t>((PS2Perf::now() - t0) / 1000u));
        }
        void push(Order order, const void *payload, uint32_t size)
        {
            rethrowError();
            const uint64_t need = align16(sizeof(Header) + size);
            if (need > kRingBytes / 2)
            {
                // Larger than the ring can hold: run it here once the queue is empty.
                drain();
                run(order, static_cast<const uint8_t *>(payload), size);
                return;
            }
            uint64_t w = m_write.load(std::memory_order_relaxed);
            uint64_t offset = w % kRingBytes;
            const uint64_t tail = kRingBytes - offset;
            if (tail < need)
            {
                waitForSpace(tail + need);
                const Header wrap{Order::Wrap, 0};
                std::memcpy(m_ring.data() + offset, &wrap, sizeof(wrap));
                w += tail;
                offset = 0;
            }
            else

                waitForSpace(need);
            const Header header{order, size}; 
            std::memcpy(m_ring.data() + offset, &header, sizeof(header));
            if (size)
                std::memcpy(m_ring.data() + offset + sizeof(header), payload, size);
            m_write.store(w + need, std::memory_order_release);
            wake();
        }
        void run(Order order, const uint8_t *payload, uint32_t size)
        {
            GSRasterBackend &r = *m_renderer;
            switch (order)
            {

            case Order::Submit:
            {
                GSPrimitiveBatch batch;
                std::memcpy(&batch, payload, sizeof(batch));
                r.Submit(batch);
                break;
            }
            case Order::BeginTransfer:
            {
                GSTransferCommand command;
                std::memcpy(&command, payload, sizeof(command));

                r.BeginTransfer(command);
                break;
            }
            case Order::Upload:
                r.UploadImage(payload, size);
                break;
            case Order::Flush:
                r.Flush();

                break;
            case Order::TextureFlush:
                r.TextureFlush();
                break;
            case Order::Sync:
            {
                GSSyncReason reason;
                std::memcpy(&reason, payload, sizeof(reason));
                r.Sync(reason);
                break;
            }
            case Order::Command:
            {
                CommandArgs a;
                std::memcpy(&a, payload, sizeof(a));
                std::unique_ptr<std::shared_ptr<RenderCmd>> cmd(a.cmd);
                if (*cmd)
                    renderRunCommand(*m_renderer, **cmd, a.state);
                break;
            }
            case Order::Present:
            {
                GSPresentationRequest request;
                std::memcpy(&request, payload, sizeof(request) );
                PS2_PERF_ZONE(ZonePresent);
                if (m_presenter)
                    m_presenter->PresentBegin(request);
                else

                    r.Present(request);
                break;
            }
            case Order::Clear:
            {
                ClearArgs a;
                std::memcpy(&a, payload, sizeof(a));
                r.ClearFramebuffer( a.context, a.rgba);
                break;
            }
            case Order::Wrap:

                break;
            }
        }
        void workerLoop()
        {
            ThreadNaming::SetCurrentThreadName("RenderThread");
            uint64_t read = m_read.load(std::memory_order_relaxed);
            for (;;)
            {
                const uint64_t write = m_write.load(std::memory_order_acquire);
                if (read == write)
                {
                    if (m_stop.load(std::memory_order_acquire))
                        break;
                    bool more = false;
                    for (int spin = 0; spin < 2000 && !more; ++spin)
                    {

                        _mm_pause();
                        more = m_write.load(std::memory_order_acquire) != read || m_stop.load(std::memory_order_acquire);
                    }
                    if (!more)
                    {
                        std::unique_lock<std::mutex> lock(m_wakeMutex);
                        m_sleeping.store(true, std::memory_order_release);
                        m_wakeCv.wait_for(lock, std::chrono::milliseconds(2), [&] {
                            return m_write.load(std::memory_order_acquire) != read || m_stop.load(std::memory_order_acquire);
                        });
                        m_sleeping.store(false, std::memory_order_release);
                    }
                    continue;
                }
                PS2_PERF_ZONE(ZoneGs);
                while (read != write)
                {
                    const uint64_t offset =  read % kRingBytes;
                    Header header;
                    std::memcpy(&header, m_ring.data() + offset, sizeof(header));
                    if (header.order == Order::Wrap)
                        read += kRingBytes - offset;
                    else
                    {
                        try
                        {
                            run(header.order, m_ring.data() + offset + sizeof(Header), header.size);
                        }
                        catch (...)
                        {  
                            std::lock_guard<std::mutex> lock(m_errorMutex);
                            if (!m_error) 
                                m_error = std::current_exception();
                            m_errorPending.store(true, std::memory_order_release);
                        }
                        read += align16(sizeof(Header) + header.size);
                    }
                    m_read.store(read, std::memory_order_release);

                }
            }
        }

        std::unique_ptr<GSRasterBackend> m_renderer;
        GSAsyncPresenter *m_presenter = nullptr ;
        std::vector<uint8_t> m_ring;
        uint64_t m_frameEnds[kFramesQueued]{};
        uint32_t m_frameIndex = 0;
        alignas(64) std::atomic<uint64_t> m_write{0};
        alignas(64) std::atomic<uint64_t> m_read{0};
        alignas(64) std::atomic<bool> m_stop{false};
        mutable std::atomic<bool> m_sleeping{false};
        mutable std::mutex m_wakeMutex;
        mutable std::condition_variable m_wakeCv;
        mutable std::mutex m_errorMutex;
        std::exception_ptr m_error;
        std::atomic<bool> m_errorPending{false};
        std::thread m_worker;
    };

    struct GsSink
    {
        virtual void submit(const GSPrimitiveBatch &batch) = 0;
        virtual void beginTransfer(const GSTransferCommand &command) =  0;
        virtual void upload(const uint8_t *data, uint32_t size) = 0;
        virtual void textureFlush() = 0;
        virtual void privileged(uint8_t reg, uint64_t value) = 0; // SIGNAL, FINISH, LABEL, display
        virtual void registerWritten(uint8_t, uint64_t) {}

      protected:   
        ~GsSink() = default;
    };

    struct GsState
    {
        void resetState()

        {
            std::memset(m_ctx, 0, sizeof(m_ctx));
            m_prim = {};
            m_primRegister = {};
            m_prmodeRegister = {};
            m_curR =  m_curG = m_curB = m_curA = 0x80;
            m_curQ = 1.0f;

            m_curS = m_curT = 0.0f;
            m_curU = m_curV = 0;
            m_curFog = 0;
            m_fogR = m_fogG = m_fogB = 0;
            m_prmodecont = true;
            m_pabe = false;
            m_scanmsk = m_dimx = m_dthe = m_colclamp = 0;
            m_texa = {0u, false, 0u};
            m_texclut = {0u, 0u, 0u};
            m_bitbltbuf = {};
            m_trxpos = {};
            m_trxreg = {};
            m_trxdir = 3;
            m_preferredSource = {};
            m_preferredDestFbp = 0 ;
            m_hasPreferred = false;
            for(int i =  0; i < 2; ++i)
            {
                m_ctx[i].frame.fbw = 10;
                m_ctx[i].scissor = {0, 639, 0, 447};
                m_ctx[i].xyoffset = {0, 0};
            }
        }

        void setTransferRegister(uint8_t regAddr, uint64_t value)
        {
            switch (regAddr)
            {
            case GS_REG_BITBLTBUF:
                m_bitbltbuf.sbp = uint32_t( value & 0x3FFF);
                m_bitbltbuf.sbw = uint8_t((value >> 16) & 0x3F);
                m_bitbltbuf.spsm = uint8_t((value >> 24) & 0x3F);   
                m_bitbltbuf.dbp = uint32_t( (value >> 32) & 0x3FFF);
                m_bitbltbuf.dbw = uint8_t( (value >> 48) & 0x3F);
                m_bitbltbuf.dpsm =  uint8_t( (value >> 56) & 0x3F);
                break ;
            case GS_REG_TRXPOS:
                m_trxpos.ssax = uint16_t(value & 0x7FF);
                m_trxpos.ssay = uint16_t((value >> 16) & 0x7FF );   
                m_trxpos.dsax = uint16_t((value >> 32) & 0x7FF);
                m_trxpos.dsay = uint16_t((value >> 48) & 0x7FF);
                m_trxpos.dir = uint8_t((value >> 59) & 0x3);
                break; 
            case GS_REG_TRXREG:
                m_trxreg.rrw = uint16_t(value & 0xFFF);
                m_trxreg.rrh = uint16_t((value >> 32) & 0xFFF);
                break;
            default:
                break;
            }
        }
        GSTransferCommand transferCommand(uint64_t trxdir)

        {
            m_trxdir = uint32_t(trxdir & 0x3);
            GSTransferCommand command{};
            command.bitbltbuf = m_bitbltbuf;
            command.trxpos = m_trxpos;
            command.trxreg = m_trxreg;
            command.direction = m_trxdir;
            return command;
        }

        void preferredSource(const GSPrimitiveBatch &batch)
        {
            const GSDrawState &state = batch.state;
            const GSContext &ctx = state.context;
            if (m_hasPreferred && ctx.frame.fbp == m_preferredDestFbp)
                m_hasPreferred = false;   
            if (state.prim.type != GS_PRIM_SPRITE || batch.vertexCount < 2u)
                return;
            const GSVertex &v0 = batch.vertices[0], &v1 = batch.vertices[1];
            int x0 =  int(v0.x) - (ctx.xyoffset.ofx >> 4), y0 = int(v0.y) - (ctx.xyoffset.ofy >> 4);
            int x1 = int(v1.x) - (ctx.xyoffset.ofx >> 4), y1 = int(v1.y) - (ctx.xyoffset.ofy >> 4);
            if (x0 > x1)
                std::swap(x0, x1);
            if (y0 > y1)
                std::swap(y0, y1);
            const int xEnd = x0 + std::max(1, x1 - x0) - 1, yEnd = y0 + std::max(1, y1 - y0) - 1;
            if (state.prim.tme && state.prim.abe && state.prim.fst && state.prim.ctxt && ctx.frame.fbp != ctx.tex0.tbp0 && GSGameHeuristics::isDisplayCopyBlend(ctx.alpha) && x0 <= 0 && y0 <= 0 && xEnd >= GSGameHeuristics::kDisplayCopyWidth - 1 && yEnd >= GSGameHeuristics::kDisplayCopyHeight - 1)
            {
                m_preferredSource = {ctx.tex0.tbp0, ctx.tex0.tbw, ctx.tex0.psm, 0u};
                m_preferredDestFbp = ctx.frame.fbp;
                m_hasPreferred = true;
            }
        }

        GSContext m_ctx[2];
        GSPrimReg m_prim{}, m_primRegister{}, m_prmodeRegister{};
        uint8_t m_curR = 0x80, m_curG = 0x80, m_curB = 0x80, m_curA = 0x80;
        float m_curQ = 1.0f, m_curS = 0.0f, m_curT = 0.0f;
        uint16_t m_curU = 0, m_curV = 0; 
        uint8_t m_curFog = 0, m_fogR = 0, m_fogG = 0, m_fogB = 0;
        bool m_prmodecont = true, m_pabe = false;
        uint64_t m_scanmsk = 0, m_dimx = 0, m_dthe = 0, m_colclamp = 0;  
        GSTexaReg m_texa{0u, false, 0u};
        GSTexClutReg m_texclut{0u, 0u, 0u};
        GSBitBltBuf m_bitbltbuf{};
        GSTrxPos m_trxpos{};
        GSTrxReg m_trxreg{};
        uint32_t m_trxdir = 3 ;
        GSFrameReg m_preferredSource{};
        uint32_t m_preferredDestFbp = 0;
        bool m_hasPreferred = false;
    };

#ifdef DK_PORT_CHECK
    class GsDecoder : public GsState
    {
      public:
        GsSink *m_sink = nullptr;
        bool m_counting = true;
        bool m_tellWrites = false;

        void resetState()
        {
            GsState::resetState();
            m_vtxCount = 0;
        }

        void decode(const uint8_t *data, uint32_t sizeBytes)
        {
            uint32_t offset = 0;
            while (offset + 16 <= sizeBytes)
            {
                const uint64_t tagLo = load64( data + offset), tagHi = load64(data + offset + 8);
                offset += 16;
                m_curQ = 1.0f;
                const uint32_t nloop = uint32_t(tagLo & 0x7FFF);
                const uint8_t flg =  uint8_t((tagLo >> 58) & 0x3);
                uint32_t nreg = uint32_t((tagLo >> 60) & 0xF);
                if (nreg == 0)
                    nreg = 16;
                if (((tagLo >> 46) & 1) && nloop != 0)  
                    writeRegisterUnlocked(GS_REG_PRIM, (tagLo >> 47) & 0x7FF);
                uint8_t regs[16];
                for (uint32_t i = 0; i < nreg; ++i)
                    regs[i] = uint8_t((tagHi >> (i * 4)) & 0xF);
                if (flg == GIF_FMT_PACKED)
                {   
                    for (uint32_t loop = 0; loop < nloop; ++loop)
                        for (uint32_t r = 0; r < nreg; ++r)
                        {
                            if (offset + 16 > sizeBytes)
                                return;
                            writePacked(regs[r], load64(data + offset), load64(data + offset + 8) );
                            offset += 16;
                        }
                }
                else if ( flg == GIF_FMT_REGLIST)
                {
                    for (uint32_t loop = 0; loop < nloop; ++loop)
                        for (uint32_t r = 0; r < nreg; ++r)
                        {
                            if (offset + 8 > sizeBytes)
                                return;
                            writeRegisterUnlocked(regs[r], load64(data + offset));
                            offset += 8;
                        }
                    if ((nloop * nreg) & 1)
                        offset += 8;
                }
                else if (flg == GIF_FMT_IMAGE)
                {
                    uint32_t imageBytes = nloop * 16;
                    if (offset + imageBytes > sizeBytes)
                        imageBytes = sizeBytes - offset;
                    m_sink->upload(data + offset, imageBytes);
                    offset += imageBytes;
                }
            }
        }

        void setVertex(float x, float y, double z, uint8_t fog)
        {
            GSVertex &vtx = m_vtxQueue[m_vtxCount % kMaxVerts];
            vtx.x = x;
            vtx.y = y;
            vtx.z = z;
            vtx.r = m_curR;
            vtx.g = m_curG;

            vtx.b = m_curB;
            vtx.a = m_curA;
            vtx.q = m_curQ;
            vtx.s = m_curS;
            vtx.t = m_curT;
            vtx.u = m_curU;
            vtx.v = m_curV;
            vtx.fog = fog;
        }

        void writePacked(uint8_t regDesc, uint64_t lo, uint64_t hi)

        {
            switch (regDesc)  
            {
            case 0x00: 
                writeRegisterUnlocked(GS_REG_PRIM, lo & 0x7FF);
                break;

            case 0x01:

                m_curR = uint8_t(lo & 0xFF);
                m_curG = uint8_t((lo >> 32) & 0xFF );
                m_curB = uint8_t(hi & 0xFF);

                m_curA = uint8_t((hi >> 32) & 0xFF);
                break;
            case 0x02:
            {
                const uint32_t sBits = uint32_t(lo), tBits = uint32_t(lo >> 32), qBits = uint32_t(hi);
                std::memcpy(&m_curS, &sBits, 4) ;
                std::memcpy(&m_curT, &tBits, 4);
                std::memcpy(&m_curQ, &qBits, 4);
                if ( m_curQ == 0.0f)
                    m_curQ = 1.0f;
                break;
            }
            case 0x03:
                m_curU = uint16_t(lo & 0x3FFFu);
                m_curV = uint16_t((lo >> 32) & 0x3FFFu);
                break;
            case 0x04: // XYZF2 (ADC: no kick)
                setVertex(float(lo & 0xFFFF) / 16.0f, float((lo >> 32) & 0xFFFF) / 16.0f, float((hi >> 4) & 0xFFFFFF), uint8_t((hi >> 36) & 0xFF));
                vertexKick(((hi >> 47) & 1) == 0) ;
                break;
            case 0x05: // XYZ2
                setVertex(float(lo & 0xFFFF) / 16.0f, float((lo >> 32) & 0xFFFF) / 16.0f, float(hi & 0xFFFFFFFF), m_curFog);
                vertexKick(((hi >> 47) & 1) == 0);
                break;
            case 0x0A:
                m_curFog = uint8_t((hi >> 36) & 0xFF);
                break ;
            case 0x0C: // XYZF3

                setVertex(float(lo & 0xFFFF) / 16.0f, float((lo >> 32) & 0xFFFF) / 16.0f, float((hi >> 4) & 0xFFFFFF), uint8_t((hi >> 36) & 0xFF));
                vertexKick(false);
                break;
            case 0x0D: // XYZ3
                setVertex(float(lo & 0xFFFF) / 16.0f, float((lo >> 32) & 0xFFFF) / 16.0f, float(hi & 0xFFFFFFFF), m_curFog);
                vertexKick(false);
                break;  
            case 0x0E: // A+D

                writeRegisterUnlocked(uint8_t(hi & 0xFF), lo);
                break;
            case 0x0F: // NOP
                break;
            default:
                writeRegisterUnlocked(regDesc, lo);
                break;
            }
        }

        void writeRegisterUnlocked(uint8_t regAddr, uint64_t value) 
        {
            if (m_tellWrites)
                m_sink->registerWritten(regAddr, value);
            switch (regAddr)

            {
            case GS_REG_PRIM:
                m_primRegister = decodePrim(value);
                if (m_prmodecont)
                    m_prim = m_primRegister;

                else
                    m_prim.type = m_primRegister.type; // AC=0: the rest from PRMODE
                m_vtxCount = 0;
                break;
            case GS_REG_RGBAQ:
            {

                m_curR = uint8_t(value & 0xFF);
                m_curG = uint8_t((value >> 8) & 0xFF);
                m_curB = uint8_t((value >> 16) & 0xFF);
                m_curA = uint8_t((value >> 24) & 0xFF);
                const uint32_t qBits = uint32_t(value >> 32);
                std::memcpy(&m_curQ, &qBits, 4);
                if ( m_curQ == 0.0f)
                    m_curQ = 1.0f;
                break;
            }
            case GS_REG_ST:
            {
                const uint32_t sBits = uint32_t(value), tBits = uint32_t(value >> 32);
                std::memcpy(&m_curS, &sBits, 4);
                std::memcpy(&m_curT, &tBits, 4);
                break;   
            }

            case GS_REG_UV:
                m_curU = uint16_t(value & 0x3FFFu);
                m_curV = uint16_t((value >> 16) & 0x3FFFu);
                break;
            case GS_REG_XYZF2:
            case GS_REG_XYZF3:

                setVertex(float(value & 0xFFFF) / 16.0f, float((value >> 16) & 0xFFFF) / 16.0f, double((value >> 32) & 0xFFFFFF), uint8_t((value >> 56) & 0xFF));
                vertexKick(regAddr == GS_REG_XYZF2);
                break;
            case GS_REG_XYZ2:
            case GS_REG_XYZ3:
                setVertex(float(value & 0xFFFF) / 16.0f, float((value >> 16) & 0xFFFF) / 16.0f, double((value >> 32) & 0xFFFFFFFF), m_curFog);
                vertexKick(regAddr == GS_REG_XYZ2);
                break;
            case GS_REG_TEX0_1:
            case GS_REG_TEX0_2:
            {
                auto &t =  m_ctx[regAddr == GS_REG_TEX0_2 ? 1 : 0].tex0;
                t.tbp0 = uint32_t(value & 0x3FFF);
                t.tbw = uint8_t((value >> 14) & 0x3F);
                t.psm = uint8_t((value >> 20) & 0x3F);
                t.tw = uint8_t((value >> 26) & 0xF);
                t.th = uint8_t((value >> 30) & 0xF);
                t.tcc = uint8_t((value >> 34) & 0x1);
                t.tfx = uint8_t((value >> 35) & 0x3);
                t.cbp = uint32_t((value >> 37) & 0x3FFF);
                t.cpsm = uint8_t((value >> 51) & 0xF);
                t.csm = uint8_t((value >> 55) & 0x1);
                t.csa = uint8_t((value >> 56) & 0x1F);
                t.cld = uint8_t((value >> 61) & 0x7);
                break;
            }
            case GS_REG_CLAMP_1:
            case GS_REG_CLAMP_2:
                m_ctx[regAddr == GS_REG_CLAMP_2 ? 1 : 0].clamp = value;
                break;
            case GS_REG_FOG:
                m_curFog = uint8_t( (value >> 56) & 0xFF);
                break;
            case GS_REG_TEX1_1:
            case GS_REG_TEX1_2:

                m_ctx[regAddr == GS_REG_TEX1_2 ? 1 : 0].tex1 = value;
                break;
            case GS_REG_TEX2_1:
            case GS_REG_TEX2_2:
            { 
                auto &t = m_ctx[regAddr == GS_REG_TEX2_2 ? 1 : 0].tex0;
                t.psm = uint8_t((value >> 20) & 0x3F);
                t.cbp = uint32_t((value >> 37) & 0x3FFF);

                t.cpsm = uint8_t((value >> 51) & 0xF);

                t.csm = uint8_t((value >> 55) & 0x1);

                t.csa = uint8_t((value >> 56) & 0x1F);
                t.cld = uint8_t((value >> 61) & 0x7) ;
                break;
            }
            case GS_REG_XYOFFSET_1:
            case GS_REG_XYOFFSET_2:

            {
                const int ci = regAddr == GS_REG_XYOFFSET_2 ? 1 : 0;   
                m_ctx[ci].xyoffset.ofx = uint16_t(value & 0xFFFF);
                m_ctx[ci].xyoffset.ofy = uint16_t((value >> 32) & 0xFFFF);
                break;

            }
            case GS_REG_PRMODECONT:
            {
                m_prmodecont = (value & 1) != 0;
                const GSPrimType type = m_primRegister.type;
                m_prim = m_prmodecont ? m_primRegister : m_prmodeRegister;
                m_prim.type = type;
                break;   
            }
            case GS_REG_PRMODE:
                m_prmodeRegister = decodePrim(value);
                if (!m_prmodecont)
                {
                    const GSPrimType type = m_primRegister.type;
                    m_prim = m_prmodeRegister;
                    m_prim.type = type;
                }
                break;
            case GS_REG_TEXCLUT:
                m_texclut.cbw = uint8_t(value & 0x3Fu);
                m_texclut.cou = uint8_t((value >> 6) & 0x3Fu);
                m_texclut.cov = uint16_t((value >> 12) & 0x3FFu);
                break;
            case GS_REG_SCISSOR_1:
            case GS_REG_SCISSOR_2:
            {  
                auto &sc = m_ctx[regAddr == GS_REG_SCISSOR_2 ? 1 : 0].scissor;

                sc.x0 = uint16_t(value & 0x7FF);
                sc.x1 = uint16_t((value >> 16) & 0x7FF);
                sc.y0 = uint16_t((value >> 32) & 0x7FF) ;
                sc.y1 = uint16_t((value >> 48) & 0x7FF);
                break;
            }  
            case GS_REG_ALPHA_1:
            case GS_REG_ALPHA_2:
                m_ctx[regAddr == GS_REG_ALPHA_2 ? 1 : 0].alpha = value;
                break;
            case GS_REG_TEST_1:
            case GS_REG_TEST_2:
                m_ctx[regAddr == GS_REG_TEST_2 ? 1 : 0].test = value;
                break;
            case GS_REG_FRAME_1:
            case GS_REG_FRAME_2:
            {
                auto &f = m_ctx[regAddr == GS_REG_FRAME_2 ? 1 : 0].frame;
                f.fbp = uint32_t(value & 0x1FF) ;
                f.fbw = uint32_t((value >> 16) & 0x3F);
                f.psm = uint8_t((value >> 24) & 0x3F);
                f.fbmsk = uint32_t((value >> 32) & 0xFFFFFFFF);
                break;
            }
            case GS_REG_ZBUF_1:

            case GS_REG_ZBUF_2:
            {
                auto &z = m_ctx[regAddr == GS_REG_ZBUF_2 ? 1 : 0].zbuf;
                z.zbp = value & 0x1FF;
                z.psm = ((value >> 24) & 0xF) | 0x30;
                z.zmask = (value >> 32) & 1;
                break;
            }
            case GS_REG_FBA_1:
            case GS_REG_FBA_2:   
                m_ctx[regAddr == GS_REG_FBA_2 ? 1 : 0].fba = value;
                break;
            case GS_REG_BITBLTBUF:
            case GS_REG_TRXPOS:
            case GS_REG_TRXREG:
                setTransferRegister(regAddr, value);
                break; 
            case GS_REG_TRXDIR:
            {
                m_sink->beginTransfer(transferCommand(value));
                if (g_stats && m_counting)
                    g_statTransfers.fetch_add(1, std::memory_order_relaxed);
                break;
            }
            case GS_REG_HWREG:
            {

                uint8_t buf[8];
                std::memcpy(buf, &value, 8);
                m_sink->upload(buf, 8);
                break;
            }
            case GS_REG_PABE:
                m_pabe = (value & 1u) != 0u;

                break;
            case GS_REG_FOGCOL:
                m_fogR = uint8_t(value & 0xFFu );
                m_fogG = uint8_t((value >> 8) & 0xFFu );
                m_fogB = uint8_t((value >> 16) & 0xFFu);
                break;
            case GS_REG_TEXFLUSH:
                m_sink->textureFlush();
                break;
            case GS_REG_SCANMSK:
                m_scanmsk = value;
                break;
            case GS_REG_DIMX:  
                m_dimx = value;
                break;
            case GS_REG_DTHE: 
                m_dthe = value;
                break;
            case GS_REG_COLCLAMP:
                m_colclamp = value;
                break;
            case GS_REG_MIPTBP1_1:
            case GS_REG_MIPTBP1_2:
                m_ctx[regAddr == GS_REG_MIPTBP1_2 ? 1 : 0].miptbp1 = value;

                break;
            case GS_REG_MIPTBP2_1:
            case GS_REG_MIPTBP2_2:
                m_ctx[regAddr == GS_REG_MIPTBP2_2 ? 1 : 0].miptbp2 = value;
                break ;
            case GS_REG_TEXA:
                m_texa.ta0 = uint8_t(value & 0xFFu) ;
                m_texa.aem = ((value >> 15) & 0x1u) != 0u; 
                m_texa.ta1 = uint8_t((value >> 32) & 0xFFu);
                break;
            case GS_REG_SIGNAL:
            case GS_REG_FINISH:
            case GS_REG_LABEL:
            case 0x59:
            case 0x5a:
            case 0x5b:  
            case 0x5c:
            case 0x5f:
                m_sink->privileged(regAddr, value);
                break ;
            default:
                break;
            }
        }

        void vertexKick(bool drawing)
        {
            ++m_vtxCount;
            int needed = 0;
            switch (m_prim.type)
            {
            case GS_PRIM_POINT:
                needed = 1;
                break;
            case GS_PRIM_LINE:
            case GS_PRIM_LINESTRIP:

            case GS_PRIM_SPRITE:

                needed = 2;
                break;
            case GS_PRIM_TRIANGLE:
            case GS_PRIM_TRISTRIP:
            case GS_PRIM_TRIFAN:   
                needed = 3;
                break;
            default:
                return;
            }
            if (m_vtxCount < needed)
                return;

            if ( drawing)
            {
                const GSPrimitiveBatch batch = drawBatch(needed);
                preferredSource(batch);
                m_sink->submit(batch);
                if (g_stats && m_counting)
                {
                    g_statPrims.fetch_add(1, std::memory_order_relaxed);
                    if (g_statKinds)
                    {
                        const GSContext &kc = batch.state.context;
                        const uint64_t key = uint64_t(batch.state.prim.type) | uint64_t(batch.state.prim.tme) << 3 |
                                            uint64_t(batch.state.prim.abe) << 4 | uint64_t(batch.state.prim.ctxt) << 5 |
                                            uint64_t(kc.frame.fbp & 0x1FF) << 8 | uint64_t(kc.tex0.tbp0 & 0x3FFF) << 20 |
                                            uint64_t(kc.alpha & 0xFF) << 40 | uint64_t((kc.alpha >> 32) & 0xFF) << 48;
                        std::lock_guard<std::mutex> lock(g_kindMutex);   

                        ++g_kinds[key];
                    }
                }
            }
            switch (m_prim.type)
            {
            case GS_PRIM_LINESTRIP:
                m_vtxQueue[0] = m_vtxQueue[1];
                m_vtxCount = 1;
                break;
            case GS_PRIM_TRISTRIP:
                m_vtxQueue[0] = m_vtxQueue[1] ;
                m_vtxQueue[1] = m_vtxQueue[2];
                m_vtxCount = 2 ;
                break;
            case GS_PRIM_TRIFAN:
                m_vtxQueue[1] = m_vtxQueue[2];
                m_vtxCount = 2;
                break;
            default:
                m_vtxCount = 0;
                break;
            }
        }


        GSPrimitiveBatch drawBatch(int vertexCount) const   
        {
            GSPrimitiveBatch batch{};
            batch.vertexCount = uint8_t(std::min(vertexCount, 3));
            for(int i = 0; i < batch.vertexCount; ++i)
                batch.vertices[size_t(i)] = m_vtxQueue[i];
            batch.state.context = m_ctx[m_prim.ctxt ? 1 : 0]; 
            batch.state.prim = m_prim;
            batch.state.texa = m_texa;
            batch.state.texclut = m_texclut;
            batch.state.pabe = m_pabe;
            batch.state.scanmsk = m_scanmsk; 
            batch.state.dimx = m_dimx;
            batch.state.dthe = m_dthe ;
            batch.state.colclamp = m_colclamp;
            batch.state.fogR = m_fogR;

            batch.state.fogG = m_fogG;
            batch.state.fogB = m_fogB;
            batch.state.textureWidth = uint16_t(1u << std::min<uint32_t>(batch.state.context.tex0.tw, 10u));
            batch.state.textureHeight = uint16_t(1u << std::min<uint32_t>(batch.state.context.tex0.th, 10u));
            const uint64_t tex1 = batch.state.context.tex1;
            const uint8_t mmag = uint8_t((tex1 >> 5u) & 0x1u), mmin = uint8_t((tex1 >> 6u) & 0x7u);
            batch.state.linearFilter = mmag != 0u || mmin == 1u || (mmin & 0x4u) != 0u;
            return batch;
        }

        static constexpr int kMaxVerts = 6;
        GSVertex m_vtxQueue[kMaxVerts];
        int m_vtxCount = 0;
    };

    struct DrawBuilder final : GsSink
    {
        NativeDraws out;
        GsDecoder dec;
        uint32_t set[3] = {}; // context 1, context 2, global (NativeDraws bits)
        bool ok = true, rgba = false, st = false, uv = false, fog = false, prim = false;
        uint32_t trx = 0; // BITBLTBUF | TRXPOS << 1 | TRXREG << 2
        const char *why = nullptr;
        void fail(const char *reason)
        {
            if (ok)
                why = reason;
            ok = false;
        }
        void registerWritten(uint8_t r, uint64_t) override
        {
            auto ctxBit = [&](uint8_t base, uint32_t bit ) {
                if (r == base || r == base + 1)
                    set[r - base] |= bit;
            };
            ctxBit(GS_REG_TEX0_1, NativeDraws::kTex0);
            ctxBit(GS_REG_CLAMP_1, NativeDraws::kClamp);
            ctxBit(GS_REG_TEX1_1, NativeDraws::kTex1);
            ctxBit(GS_REG_XYOFFSET_1, NativeDraws::kXyoffset); 
            ctxBit(GS_REG_SCISSOR_1, NativeDraws::kScissor) ;
            ctxBit(GS_REG_ALPHA_1, NativeDraws::kAlpha);
            ctxBit(GS_REG_TEST_1, NativeDraws::kTest);
            ctxBit(GS_REG_FBA_1, NativeDraws::kFba);
            ctxBit(GS_REG_FRAME_1, NativeDraws::kFrame );
            ctxBit(GS_REG_ZBUF_1, NativeDraws::kZbuf);
            ctxBit(GS_REG_MIPTBP1_1, NativeDraws::kMiptbp);
            ctxBit(GS_REG_MIPTBP2_1, NativeDraws::kMiptbp);  
            if ((r == GS_REG_TEX2_1 || r == GS_REG_TEX2_2) && !(set[r - GS_REG_TEX2_1] & NativeDraws::kTex0))
                fail("TEX2 without TEX0");
            switch (r)   
            {
            case GS_REG_TEXA: set[2] |= NativeDraws::kTexa; break;
            case GS_REG_TEXCLUT: set[2] |= NativeDraws::kTexclut; break;
            case GS_REG_FOGCOL: set[2] |= NativeDraws::kFogcol; break; 
            case GS_REG_DTHE: set[2] |= NativeDraws::kDthe; break;
            case GS_REG_COLCLAMP: set[2] |= NativeDraws::kColclamp; break;
            case GS_REG_PABE: set[2] |= NativeDraws::kPabe; break;
            case GS_REG_SCANMSK: set[2] |= NativeDraws::kScanmsk; break;
            case GS_REG_DIMX: set[2] |= NativeDraws::kDimx; break;
            case GS_REG_PRIM: prim = true; set[2] |= NativeDraws::kPrim; break;
            case GS_REG_PRMODE: case GS_REG_PRMODECONT: set[2] |= NativeDraws::kPrmode; break;
            case GS_REG_RGBAQ: rgba = true; set[2] |= NativeDraws::kRgbaq; break;
            case GS_REG_ST: st = true; set[2] |= NativeDraws::kSt; break;
            case GS_REG_UV: uv = true; set[2] |= NativeDraws::kUv; break;
            case GS_REG_FOG: case GS_REG_XYZF2: case GS_REG_XYZF3: fog = true; set[2] |= NativeDraws::kFog; break;
            case GS_REG_BITBLTBUF: trx |= 1; set[2] |= NativeDraws::kTransfer; break;
            case GS_REG_TRXPOS: trx |= 2; set[2] |= NativeDraws::kTransfer; break;
            case GS_REG_TRXREG: trx |= 4; set[2] |= NativeDraws::kTransfer; break;  
            default: break;
            }  
        }
        void submit(const GSPrimitiveBatch &b) override
        {
            const GSPrimReg &pr = b.state.prim;
            if (!prim)
                fail("PRIM not set");
            else if (!rgba)
                fail("RGBAQ not set");
            else if (pr.tme && (pr.fst ? !uv : !st))
                fail("UV / ST not set");

            else if (pr.fge && !fog)
                fail("FOG not set");
            const uint32_t c = pr.ctxt ? 1u : 0u;
            out.items.push_back({NativeDraws::Kind::Prim, uint32_t(out.prims.size())});
            out.prims.push_back({b, (~set[c] & NativeDraws::kContextFields) | (~set[2] & NativeDraws::kGlobalFields)});
        }
        void beginTransfer(const GSTransferCommand &command) override
        {
            if (trx != 7)
                fail("transfer registers not set");
            out.items.push_back({NativeDraws::Kind::Transfer, uint32_t(out.transfers.size())});
            out.transfers.push_back(command);
            out.images.emplace_back();
        }

        void upload(const uint8_t *data, uint32_t size) override
        {

            if (out.images.empty())
            {

                fail("image without a transfer");
                return;
            }
            out.images.back().insert(out.images.back().end(), data, data + size);
        }  
        void textureFlush() override { out.items.push_back({NativeDraws::Kind::TexFlush, 0}); }
        void privileged(uint8_t reg, uint64_t value) override
        {
            out.items.push_back({NativeDraws::Kind::Privileged, uint32_t(out.privileged.size())});
            out.privileged.push_back({reg, value});
        }
    };

#endif

    bool isTypedNative(const Native2D &draw)   
    {
        for (const Native2D::Write &w : draw.writes )
            if (w.reg == Native2D::kPrim || w.reg == Native2D::kState || w.reg == Native2D::kTransfer || w.reg == Native2D::kTexFlush || w.reg == Native2D::kPrivileged || w.reg == Native2D::kSet)
                return true;
        return false;
    }   
    bool typedListBad(const Native2D &draw, const char *why)
    {
        static std::atomic<uint32_t> count{0};
        if (count.fetch_add(1, std::memory_order_relaxed) < 20)
            std::fprintf(stderr, "[native-draws] %06X: %s: not drawn\n", draw.function, why);
        return false ;
    }
    bool typedNativeDraws(const Native2D &draw, NativeDraws &d, Native2D *own = nullptr)
    {
        if (own)
        {
            uint64_t next = 0;
            for (const Native2D::Write &w : draw.writes )
                if (w.reg == Native2D::kPrim && w.value != next++)
                {
                    own =  nullptr;
                    break;
                }
            if (own && next != draw.prims.size())
                own = nullptr;
        }
        if (own)
            d.prims = std::move(own->prims);
        else
            d.prims.reserve( draw.prims.size());
        d.items.reserve(draw.writes.size());
        uint32_t set[3] = {};
        const NativeDraws::State *last = nullptr;
        for (const Native2D::Write &w : draw.writes )
            switch(w.reg)
            {
            case Native2D::kPrim:
            {
                if (!own)
                    d.prims.push_back(draw.prims[size_t(w.value)]);
                const uint32_t index = own ? uint32_t(w.value) : uint32_t(d.prims.size() - 1) ;
                d.items.push_back({NativeDraws::Kind::Prim, index});
                NativeDraws::Prim &p = d.prims[index];
                p.inherit = (~set[p.batch.state.prim.ctxt ? 1 : 0] & NativeDraws::kContextFields) | (~set[2] & NativeDraws::kGlobalFields);
                break;
            }
            case Native2D::kTransfer:
                d.items.push_back({NativeDraws::Kind::Transfer, uint32_t(d.transfers.size())});
                d.transfers.push_back(draw.transfers[size_t(w.value)]);
                d.images.emplace_back();
                break;
            case Native2D::kImage:
            {
                if(d.images.empty())
                    return typedListBad(draw, "image data without a transfer");

                if (own && d.images.back().empty())
                    d.images.back() = std::move(own->images[size_t(w.value)]);
                else
                {
                    const auto &image = draw.images[size_t(w.value)];
                    d.images.back().insert(d.images.back().end(), image.begin(), image.end());
                }   

                break;
            }
            case Native2D::kTexFlush:
                d.items.push_back({NativeDraws::Kind::TexFlush, 0});
                break;
            case Native2D::kPrivileged:
                d.items.push_back({NativeDraws::Kind::Privileged, uint32_t(d.privileged.size())});
                d.privileged.push_back(draw.privileged[size_t(w.value)]);
                break;

            case Native2D::kSet:
                Native2D::unpackSet( w.value, set) ;
                break;
            case Native2D::kState:
            {
                const NativeDraws::State &st = draw.states[size_t(w.value)];
                last = &st;
                for (int i = 0; i < 3; ++i) 
                    set[i] |= st.set[i];
                break;
            }
            default:
                if (w.reg < 0xF0)  
                    return typedListBad(draw, "GS register writes in a typed list");
                break;
            }  
        if (last)
            d.end = last->values;
        for (int i = 0; i < 3; ++i)
            d.endSet[i] = set[i];
        d.function =  draw.function;
        return true;
    }

    std::atomic<uint64_t> g_drawsMade{0}, g_drawsKept{0}, g_drawsDecoded{0};
    std::mutex g_drawsWhyMutex;
    std::map<std::string, uint64_t> g_drawsWhy;

    bool portCheck()
    {
        static const bool on = [] {
            const char *v = std::getenv("PS2_DK_NATIVE2D");
            const bool asked = v && std::strcmp(v, "check") == 0;
#ifndef DK_PORT_CHECK
            if (asked)
                std::fprintf(stderr, "[render] PS2_DK_NATIVE2D=check needs an exe built with -DPS2X_DK_PORT_CHECK=ON\n");
            return false;
#else
            return asked;
#endif
        }();
        return on;
    }

#ifdef DK_PORT_CHECK
    class RenderRecorder final : private GsSink, private GsDecoder
#else
    class RenderRecorder final : private GsSink, private GsState
#endif
    {
      public:
        explicit RenderRecorder(const PrivRegs &regs) : m_privRegs(regs)   
        {
#ifdef DK_PORT_CHECK
            m_sink = this;
#endif
            resetState();
        }

        void init(uint8_t *vram, uint32_t vramSize)
        {
            (void)portCheck();
            m_queue.initialize(vram, vramSize);
            RenderExec::setDirectMovies(true);
            reset();
            RenderSink::setConsumer(
                [](void *user, const std::shared_ptr<RenderCmd> &cmd, const uint8_t *writes, uint32_t size) {
                    static_cast<RenderRecorder *>(user)->nativeCommand(cmd, writes, size);
                },
                this);
        }
        void reset()  
        {
            std::lock_guard<std::recursive_mutex> lock(m_mutex );
            resetState() ;
            m_queue.reset();
        }

        void processGIFPacket(const uint8_t *data, uint32_t sizeBytes)  
        {
            if (g_stats )
                g_statGifBytes.fetch_add(sizeBytes, std::memory_order_relaxed);
            GraphicsThread::sync(); // EE callers (HLE); no-op on the graphics thread

            PS2_PERF_ZONE(ZoneGif);
            std::lock_guard<std::recursive_mutex> lock(m_mutex );
            if (!data || sizeBytes < 16)
                return;
            PS2Det::hashGif(data, sizeBytes);
#ifdef DK_PORT_CHECK
            if (portCheck())
            {
                decode(data, sizeBytes);
                return;
            }
#endif
            gameGifSkip(data, sizeBytes);
        }
        bool processNativePackedGIFPacket(const uint8_t *data, uint32_t sizeBytes)
        {
            // Only whole PACKED packets (the caller's DMA shortcut, ps2_memory.cpp).
            for (uint32_t offset = 0; offset + 16 <= sizeBytes;)
            {
                const uint64_t lo = load64(data + offset);
                uint32_t nreg = uint32_t((lo >> 60) & 0xF);
                if (((lo >> 58) & 3) != GIF_FMT_PACKED)
                    return false;
                if (!nreg)
                    nreg = 16;
                offset += 16 + uint32_t(lo & 0x7FFF) * nreg * 16;
                if(offset > sizeBytes)
                    return false;
            }
            processGIFPacket(data, sizeBytes);
            return true;
        }
        void uploadImageNative(uint64_t bitbltbuf, uint64_t trxpos, uint64_t trxreg, uint64_t trxdir, const uint8_t *data, uint32_t sizeBytes)
        {
            GraphicsThread::sync();
            std::lock_guard<std::recursive_mutex> lock(m_mutex );
            if (!data || !sizeBytes)
                return;
            setTransferRegister(GS_REG_BITBLTBUF, bitbltbuf); 
            setTransferRegister(GS_REG_TRXPOS, trxpos);
            setTransferRegister(GS_REG_TRXREG, trxreg);
            beginTransfer(transferCommand(trxdir));
            m_queue.upload(data, sizeBytes);
        }
        void writeRegister(uint8_t regAddr, uint64_t value) 
        {
            GraphicsThread::sync();
            std::lock_guard<std::recursive_mutex> lock(m_mutex );
#ifdef DK_PORT_CHECK
            writeRegisterUnlocked(regAddr, value);
#else
            static std::atomic<uint32_t> count{0};
            if (count.fetch_add(1, std::memory_order_relaxed) < 8)
                std::fprintf(stderr, "[render] GS register %02X write from the runtime ignored\n", unsigned(regAddr));
            (void)value;
#endif
        }


        void present(GSPresentationRequest request)
        {
            if (g_stats )
                printStats();
            std::lock_guard<std::recursive_mutex> lock(m_mutex );
#ifdef DK_PORT_CHECK
            checkEnd();
            printCheckStats(); 
#endif
            gameGifStats();
            request.contextFrames[0] = m_ctx[0].frame;
            request.contextFrames[1] = m_ctx[1].frame;
            request.preferredSource = m_preferredSource;
            request.preferredDestFbp = m_preferredDestFbp;
            request.hasPreferredSource = m_hasPreferred;

            m_queue.present(request);
        }
        bool clearFramebufferContext(uint32_t contextIndex, uint32_t rgba)
        {
            GraphicsThread::sync();
            std::lock_guard<std::recursive_mutex> lock(m_mutex );
            m_queue.clear(m_ctx[contextIndex != 0 ? 1 : 0], rgba);
            return true;
        }
        uint32_t consumeLocalToHostBytes(uint8_t *dst, uint32_t maxBytes)
        {
            GraphicsThread::sync();
            std::lock_guard<std::recursive_mutex> lock(m_mutex );
            return m_queue.consumeLocalToHost(dst, maxBytes);
        }
        GSFrameReg getContextFrame(int index) const { return m_ctx[index != 0 ? 1 : 0].frame; }
        bool getPreferredDisplaySource(GSFrameReg &outSource, uint32_t &outDestFbp) const
        {
            std::lock_guard<std::recursive_mutex> lock(m_mutex );
            if (!m_hasPreferred)

                return false;
            outSource = m_preferredSource;
            outDestFbp = m_preferredDestFbp;
            return true;
        }

      private:
        uint32_t m_logOwner = 0, m_logFlags = 0;
        FILE *m_streamFile = [] {
            const char *v = std::getenv("PS2_DK_STREAMHASH");
            return v ? std::fopen(v, "w") : nullptr;
        }();
        uint64_t m_streamHash = 1469598103934665603ull, m_streamSeg = 0, m_streamItems = 0;
        void streamMix(const void *data, size_t size)
        {
            const uint8_t *p = static_cast<const uint8_t *>(data);
            for (size_t i = 0; i < size; ++i)
                m_streamHash = (m_streamHash ^ p[i]) * 1099511628211ull;
        }
        template <class T> void streamMixValue(T v) { streamMix(&v, sizeof v); }
        const bool m_streamUsed = [] {  
            const char *v = std::getenv("PS2_DK_STREAMHASH_USED");
            return v && *v && *v != '0';
        }();
        void streamPrim(const GSPrimitiveBatch &b)
        {
            if (m_streamUsed)
            {
                streamPrimUsed(b);
                return;
            }
            const GSDrawState &x = b.state;
            const GSContext &c = x.context;
            streamMixValue(uint32_t(x.prim.type) | x.prim.iip << 3 | x.prim.tme << 4 | x.prim.fge << 5 | x.prim.abe << 6 | x.prim.aa1 << 7 | x.prim.fst << 8 | x.prim.ctxt << 9 | x.prim.fix << 10);
            streamMixValue(c.frame.fbp), streamMixValue(c.frame.fbw), streamMixValue(c.frame.psm), streamMixValue(c.frame.fbmsk);  
            streamMixValue(c.zbuf.zbp), streamMixValue(c.zbuf.psm), streamMixValue(c.zbuf.zmask);
            streamMixValue(c.tex0.tbp0), streamMixValue(c.tex0.tbw), streamMixValue(c.tex0.psm), streamMixValue(c.tex0.tw);
            streamMixValue(c.tex0.th), streamMixValue(c.tex0.tcc), streamMixValue(c.tex0.tfx), streamMixValue(c.tex0.cbp) ;
            streamMixValue(c.tex0.cpsm), streamMixValue(c.tex0.csm), streamMixValue(c.tex0.csa);
            streamMixValue(c.tex1), streamMixValue(c.clamp), streamMixValue(c.alpha), streamMixValue(c.test), streamMixValue(c.fba);
            streamMixValue(c.scissor.x0), streamMixValue(c.scissor.x1), streamMixValue(c.scissor.y0), streamMixValue(c.scissor.y1);
            streamMixValue(c.xyoffset.ofx), streamMixValue(c.xyoffset.ofy);
            streamMixValue(b.vertexCount);
            for (int i = 0; i < b.vertexCount; ++i)  
            {
                const GSVertex &v = b.vertices[size_t(i)];
                streamMixValue(v.x), streamMixValue(v.y), streamMixValue(v.z), streamMixValue(v.r), streamMixValue(v.g);
                streamMixValue(v.b), streamMixValue(v.a), streamMixValue(v.q), streamMixValue(v.s), streamMixValue(v.t);
                streamMixValue(v.u), streamMixValue(v.v), streamMixValue(v.fog);
            }
            ++m_streamItems;
        }
        void streamPrimUsed(const GSPrimitiveBatch &b)
        {
            const GSDrawState &x = b.state;
            const GSContext &c = x.context;
            streamMixValue( uint32_t(x.prim.type) | x.prim.iip << 3 | x.prim.tme << 4 | x.prim.fge << 5 | x.prim.abe << 6 | x.prim.aa1 << 7 | x.prim.fst << 8 | x.prim.fix << 10);
            streamMixValue(c.frame.fbp), streamMixValue(c.frame.fbw), streamMixValue(c.frame.psm), streamMixValue(c.frame.fbmsk) ;
            streamMixValue(c.zbuf.zbp), streamMixValue(c.zbuf.psm), streamMixValue(c.zbuf.zmask);
            if (x.prim.tme)  
            {
                streamMixValue(c.tex0.tbp0), streamMixValue(c.tex0.tbw), streamMixValue(c.tex0.psm), streamMixValue(c.tex0.tw);
                streamMixValue(c.tex0.th), streamMixValue(c.tex0.tcc), streamMixValue(c.tex0.tfx), streamMixValue(c.tex0.cbp);
                streamMixValue(c.tex0.cpsm), streamMixValue(c.tex0.csm), streamMixValue(c.tex0.csa);
                streamMixValue(c.tex1), streamMixValue(c.clamp);

            }
            if (x.prim.abe)
                streamMixValue(c.alpha);
            streamMixValue(c.test), streamMixValue(c.fba);
            streamMixValue(c.scissor.x0), streamMixValue(c.scissor.x1), streamMixValue(c.scissor.y0), streamMixValue(c.scissor.y1);
            streamMixValue(c.xyoffset.ofx), streamMixValue(c.xyoffset.ofy);
            streamMixValue(b.vertexCount);

            for (int i = 0; i < b.vertexCount; ++i)

            {
                const GSVertex &v = b.vertices[size_t(i)];
                streamMixValue(v.x), streamMixValue(v.y), streamMixValue(v.z), streamMixValue(v.r), streamMixValue(v.g);
                streamMixValue(v.b), streamMixValue(v.a);
                if (x.prim.tme && x.prim.fst) // (UV for UV textures, STQ for ST ones; the other pair is not read)
                    streamMixValue(v.u), streamMixValue(v.v);
                else if (x.prim.tme)
                    streamMixValue(v.q), streamMixValue(v.s), streamMixValue(v.t);
                if (x.prim.fge)
                    streamMixValue(v.fog);
            }
            ++m_streamItems;

        }
        void streamEnd() 
        {  
            if ( !m_streamFile)
                return;
            std::fprintf(m_streamFile, "t%llu %llu %llu %016llX\n", (unsigned long long)PS2Det::vsyncTick(), (unsigned long long)m_streamSeg++, (unsigned long long)m_streamItems, (unsigned long long)m_streamHash);
            m_streamHash = 1469598103934665603ull;
            m_streamItems = 0;
            if ((m_streamSeg & 255) == 0)
                std::fflush(m_streamFile);
        }
        bool drawLogOn()
        {
            static const std::pair<uint64_t, uint64_t> range =  [] {
                const char *v = std::getenv("PS2_DK_DRAWLOG");
                if (!v)
                    return std::pair<uint64_t, uint64_t>{1, 0};
                char *e;
                const uint64_t a = std::strtoull( v, &e, 10);
                const uint64_t b = *e == '-' ? std::strtoull(e + 1, nullptr, 10) : a;  
                return std::pair<uint64_t, uint64_t>{a, b};
            }();   
            if ( range.first > range.second)
                return false;
            const uint64_t t = PS2Det::vsyncTick();
            return t >= range.first && t <= range.second;
        }
        void submit(const GSPrimitiveBatch &batch) override
        {
            if (drawLogOn())
            {
                const GSDrawState &x = batch.state;
                const GSContext &c = x.context;
                std::fprintf(stderr, "[drawlog] t%llu o%06X/%u%s P%u%s%s F%X/%u Z%X T%X/%u/%u n%d v0 %.1f,%.1f,%.0f c%02X%02X%02X%02X\n", (unsigned long long)PS2Det::vsyncTick(), m_logOwner, m_logFlags, (m_ownerNative && !m_applying) ? " dropped" : "", unsigned(x.prim.type), x.prim.tme ? " tme" : "", x.prim.abe ? " abe" : "", c.frame.fbp, c.frame.psm, c.zbuf.zbp, c.tex0.tbp0, c.tex0.psm, c.tex0.cbp, batch.vertexCount, batch.vertexCount ? batch.vertices[0].x : 0.0f, batch.vertexCount ? batch.vertices[0].y : 0.0f, batch.vertexCount ? batch.vertices[0].z : 0.0f, batch.vertexCount ? batch.vertices[0].r : 0, batch.vertexCount ? batch.vertices[0].g : 0, batch.vertexCount ? batch.vertices[0].b : 0, batch.vertexCount ? batch.vertices[0].a : 0);
                static const bool full = [] {
                    const char *v = std::getenv("PS2_DK_DRAWLOG_FULL");
                    return v && *v == '1';
                }();   

                if (full)
                {   
                    std::fprintf(stderr, "[drawlog]   tex1 %llX clamp %llX alpha %llX test %llX fba %llX sc %u-%u,%u-%u off %X,%X texa %X/%d/%X clut %X dthe %llX colclamp %llX pabe %d fog %02X%02X%02X fst %d iip %d fge %d\n", (unsigned long long)c.tex1, (unsigned long long)c.clamp, (unsigned long long)c.alpha, (unsigned long long)c.test, (unsigned long long)c.fba, c.scissor.x0, c.scissor.x1, c.scissor.y0, c.scissor.y1, c.xyoffset.ofx, c.xyoffset.ofy, x.texa.ta0, int(x.texa.aem), x.texa.ta1, x.texclut.cbw, (unsigned long long)x.dthe, (unsigned long long)x.colclamp, int(x.pabe), x.fogR, x.fogG, x.fogB, int(x.prim.fst), int(x.prim.iip), int(x.prim.fge));
                    for (int i =  0; i < batch.vertexCount; ++i)
                    {   
                        const GSVertex &v = batch.vertices[size_t(i)];
                        std::fprintf(stderr, "[drawlog]   v%d %.4f,%.4f,%.0f c%02X%02X%02X%02X q%g st %g,%g uv %u,%u fog %u\n", i, v.x, v.y, v.z, v.r, v.g, v.b, v.a, v.q, v.s, v.t, v.u, v.v, v.fog);
                    }
                }
            }
#ifdef DK_PORT_CHECK
            if (m_check.active && !m_applying)
                m_check.gotPrims.push_back(batch);
#endif
            if (m_streamFile && (!m_ownerNative || m_applying))
                streamPrim(batch);
            if (!m_ownerNative || m_applying)
                m_queue.submit(batch);
        }
        void beginTransfer(const GSTransferCommand &command) override
        {
            if (drawLogOn())
                std::fprintf(stderr, "[drawlog] t%llu o%06X/%u%s transfer\n", (unsigned long long)PS2Det::vsyncTick(), m_logOwner, m_logFlags, (m_ownerNative && !m_applying) ? " dropped" : "");
#ifdef DK_PORT_CHECK
            if (m_check.active && !m_applying)
                m_check.gotTransfers.push_back(command);
#endif
            if (!m_ownerNative || m_applying)
                m_queue.beginTransfer(command);
        }
        void upload(const uint8_t *data, uint32_t size) override
        {
            if (drawLogOn())
            {

                uint64_t h = 1469598103934665603ull;
                for (uint32_t i = 0; i < size; ++i)
                    h = (h ^ data[i]) * 1099511628211ull;
                std::fprintf(stderr, "[drawlog] t%llu o%06X/%u%s upload %u %016llX%s", (unsigned long long)PS2Det::vsyncTick(), m_logOwner, m_logFlags, (m_ownerNative && !m_applying) ? " dropped" : "", size, (unsigned long long)h, "\n");
            }
#ifdef DK_PORT_CHECK
            if (m_check.active && !m_applying)
            {
                m_check.gotBytes += size;
                for (uint32_t i = 0; i < size; ++i)
                    m_check.gotHash = (m_check.gotHash ^ data[i]) * 1099511628211ull;
            }
#endif
            if (m_streamFile && (!m_ownerNative || m_applying))
            {
                streamMix(data, size);
                ++m_streamItems;
            }
            if (!m_ownerNative || m_applying)
                m_queue.upload(data, size);
        }
        void textureFlush() override { m_queue.textureFlush(); }
        void privileged(uint8_t regAddr, uint64_t value) override
        {
            switch (regAddr)
            {
            case GS_REG_SIGNAL:
                if (m_privRegs.on())
                    m_privRegs.signal(uint32_t(value), uint32_t(value >> 32));
                break;
            case GS_REG_FINISH:
            {
                PS2_PERF_ZONE(ZoneGs);
                streamEnd();
                m_queue.endFrame(); 
                m_queue.sync(GSSyncReason::Finish);
                if (m_privRegs.on())
                    m_privRegs.finish();  
                break;
            }
            case GS_REG_LABEL:
                if (m_privRegs.on())
                    m_privRegs.label(uint32_t(value), uint32_t(value >> 32));
                break;
            case 0x59:
            case 0x5a:
            case 0x5b:
            case 0x5c:
            case 0x5f:
                if (m_privRegs.on())
                    m_privRegs.writeDisplay(regAddr, value);
                break;
            default:
                break; 
            }
        }

        void nativeCommand(const std::shared_ptr<RenderCmd> &cmd, const uint8_t *writes, uint32_t size )
        {
            std::lock_guard<std::recursive_mutex> lock(m_mutex );
            if (cmd && m_streamFile)
                if (uint32_t o, f; !cmd->ownerMark(o, f) && !cmd->native2d())
                {
                    const char *name = cmd->typeName();
                    streamMix(name, std::strlen(name));
                    ++m_streamItems;

                }
            if (cmd && drawLogOn())
            {
                uint32_t o, f ;
                const bool mark = cmd->ownerMark(o, f);
                std::fprintf(stderr, "[drawlog] t%llu cmd %s%s %06X\n", (unsigned long long)PS2Det::vsyncTick(), mark ? "ownerMark" : (cmd->native2d() ? "native2d" : cmd->typeName()), (mark && (f & 1u)) ? " drop" : "", mark ? o : (cmd->native2d() ? cmd->native2d()->function : 0u));
            }
            if (const NativeDraws *draws = cmd ? cmd->nativeDraws() : nullptr)
                applyDraws(*draws) ;
            else if(const Native2D *draw = cmd ? cmd->native2d() : nullptr)
            {
#ifdef DK_PORT_CHECK
                if (draw->check)
                    checkBegin(*draw);
                else

#endif
                    applyNative(*draw);
            } 
            else if (cmd)
            {
                if (uint32_t owner, flags; cmd->ownerMark(owner, flags))
                {
                    m_logOwner = owner, m_logFlags = flags;
                    m_ownerNative = (flags & RenderExec::kOwnerNative) != 0;
#ifdef DK_PORT_CHECK

                    checkOwner(owner);
#endif
                }
                RenderState state{};
                state.ctx[0] = m_ctx[0];
                state.ctx[1] = m_ctx[1]; 
                state.fogcol = uint32_t(m_fogR) | uint32_t(m_fogG) << 8 | uint32_t(m_fogB) << 16;

                state.texa = m_texa;
                state.texclut = m_texclut;
                state.prim = m_prim ;
                state.primRegister = m_primRegister;
                state.prmodeRegister = m_prmodeRegister;
                state.prmodecont = m_prmodecont;
                state.rgba[0] = m_curR;
                state.rgba[1] = m_curG;
                state.rgba[2] = m_curB ;
                state.rgba[3] = m_curA;
                state.q = m_curQ;
                state.s = m_curS;
                state.t = m_curT;
                state.u = m_curU;
                state.v = m_curV;
                state.fog =  m_curFog;
                state.pabe = m_pabe;
                state.scanmsk = m_scanmsk;
                state.dimx = m_dimx;
                state.dthe = m_dthe;   
                state.colclamp = m_colclamp;
                state.bitbltbuf = m_bitbltbuf;
                state.trxpos = m_trxpos;
                state.trxreg = m_trxreg;
                if(drawLogOn())  
                    std::fprintf(stderr, "[drawlog]   state: FRAME_1 %X FRAME_2 %X ZBUF_2 %X SCISSOR_2 %u,%u fog %06X own %d\n", state.ctx[0].frame.fbp, state.ctx[1].frame.fbp, state.ctx[1].zbuf.zbp, state.ctx[1].scissor.x1, state.ctx[1].scissor.y1, state.fogcol, cmd->ownState() ? 1 : 0);
                if(const NativeDraws::State *own = cmd->ownState())
                    ownState(*own, state);
                if (uint32_t o2, f2; m_streamFile && m_streamUsed && !cmd->ownerMark(o2, f2))
                {
                    for ( const GSContext &c : state.ctx)   
                    {
                        streamMixValue(c.frame.fbp), streamMixValue(c.frame.fbw), streamMixValue(c.frame.psm), streamMixValue(c.frame.fbmsk);
                        streamMixValue(c.zbuf.zbp), streamMixValue(c.zbuf.psm), streamMixValue(c.zbuf.zmask);
                        streamMixValue(c.scissor.x0), streamMixValue(c.scissor.x1), streamMixValue(c.scissor.y0), streamMixValue(c.scissor.y1);
                        streamMixValue(c.xyoffset.ofx), streamMixValue(c.xyoffset.ofy);
                        streamMixValue(c.test), streamMixValue(c.clamp), streamMixValue(c.tex1), streamMixValue(c.fba);

                    }
                    streamMixValue(state.texa.ta0), streamMixValue(state.texa.aem), streamMixValue(state.texa.ta1);
                    streamMixValue(state.texclut.cbw), streamMixValue(state.texclut.cou), streamMixValue(state.texclut.cov);
                    streamMixValue(state.fogcol);
                }
                m_queue.command(cmd, state);
                if (g_stats )
                    g_statCommands.fetch_add(1, std::memory_order_relaxed);
            }
            if (writes && size >= 16)
                processGIFPacket(writes, size);
        }

        static void ownState(const NativeDraws::State &own, RenderState &state)
        {
            for (int i = 0; i < 2; ++i)
            {
                const uint32_t set = own.set[i];
                if (!set)
                    continue;
                GSContext &c = state.ctx[i];
                const GSContext &o = own.values.ctx[i];
                if (set & NativeDraws::kFrame)
                    c.frame = o.frame;
                if (set & NativeDraws::kZbuf)
                    c.zbuf = o.zbuf;
                if (set & NativeDraws::kScissor)
                    c.scissor = o.scissor;
                if (set & NativeDraws::kXyoffset)
                    c.xyoffset = o.xyoffset;
                if (set & NativeDraws::kTest)
                    c.test = o.test;   
                if (set & NativeDraws::kClamp)
                    c.clamp = o.clamp;
                if (set & NativeDraws::kTex1)
                    c.tex1 = o.tex1;
                if (set & NativeDraws::kFba)
                    c.fba = o.fba;
                if (set & NativeDraws::kAlpha)
                    c.alpha = o.alpha;

            }
            if (const uint32_t set = own.set[2])
            {
                if(set & NativeDraws::kFogcol)
                    state.fogcol = own.values.fogcol & 0xFFFFFF;
                if (set & NativeDraws::kTexa)
                    state.texa = own.values.texa;
            }
        }

        void applyDraws(const NativeDraws &d)
        {
            m_applying = true;
            for (const NativeDraws::Item &item : d.items)
                switch (item.kind)
                {
                case NativeDraws::Kind::Prim:
                {
                    const NativeDraws::Prim &p = d.prims[item.index];
                    GSPrimitiveBatch b = p.batch;
                    if (const uint32_t in = p.inherit)

                    {
                        GSContext &c = b.state.context;
                        const GSContext &h = m_ctx[b.state.prim.ctxt ? 1 : 0] ;
                        if ( in & NativeDraws::kFrame) c.frame = h.frame;
                        if (in & NativeDraws::kZbuf) c.zbuf = h.zbuf;
                        if (in & NativeDraws::kScissor) c.scissor = h.scissor;
                        if (in & NativeDraws::kXyoffset) c.xyoffset = h.xyoffset;
                        if (in & NativeDraws::kTex0 ) c.tex0 = h.tex0;
                        if (in & NativeDraws::kTex1) c.tex1 = h.tex1;
                        if (in & NativeDraws::kClamp) c.clamp = h.clamp;

                        if (in & NativeDraws::kAlpha) c.alpha = h.alpha;
                        if (in & NativeDraws::kTest) c.test = h.test;
                        if (in & NativeDraws::kFba) c.fba = h.fba;
                        if (in & NativeDraws::kMiptbp) c.miptbp1 = h.miptbp1, c.miptbp2 = h.miptbp2;
                        GSDrawState &s = b.state;
                        if (in & NativeDraws::kTexa) s.texa = m_texa;
                        if (in & NativeDraws::kTexclut) s.texclut = m_texclut;
                        if (in & NativeDraws::kFogcol) s.fogR = m_fogR, s.fogG = m_fogG, s.fogB = m_fogB;
                        if (in & NativeDraws::kDthe ) s.dthe = m_dthe;
                        if (in & NativeDraws::kColclamp) s.colclamp = m_colclamp;
                        if (in & NativeDraws::kPabe) s.pabe = m_pabe;
                        if (in & NativeDraws::kScanmsk) s.scanmsk =  m_scanmsk;
                        if (in & NativeDraws::kDimx) s.dimx = m_dimx;
                        if(in & (NativeDraws::kTex0 | NativeDraws::kTex1))
                        {
                            s.textureWidth = uint16_t(1u << std::min<uint32_t>(c.tex0.tw, 10u));
                            s.textureHeight = uint16_t(1u << std::min<uint32_t>(c.tex0.th, 10u));
                            const uint8_t mmag = uint8_t((c.tex1 >> 5u) & 0x1u), mmin = uint8_t((c.tex1 >> 6u) & 0x7u);

                            s.linearFilter = mmag != 0u || mmin == 1u || (mmin & 0x4u) != 0u;
                        }   
                    }
                    preferredSource(b );
                    submit(b);
                    break ;
                }
                case NativeDraws::Kind::Transfer:
                {
                    beginTransfer(d.transfers[item.index]);
                    const auto &image = d.images[item.index];
                    if (!image.empty())
                        upload(image.data(), uint32_t(image.size()));
                    break;
                }
                case NativeDraws::Kind::TexFlush:
                    textureFlush();
                    break;
                case NativeDraws::Kind::Privileged:
                    privileged(d.privileged[item.index].reg, d.privileged[item.index].value);
                    break;
                }
            const RenderState &e = d.end;
            for (int i = 0; i < 2; ++i)
                if (const uint32_t set = d.endSet[i])
                {
                    GSContext &c = m_ctx[i];
                    const GSContext &v = e.ctx[i] ;
                    if (set & NativeDraws::kFrame) c.frame = v.frame;
                    if (set & NativeDraws::kZbuf) c.zbuf = v.zbuf;
                    if (set & NativeDraws::kScissor) c.scissor = v.scissor;
                    if (set & NativeDraws::kXyoffset) c.xyoffset = v.xyoffset;
                    if (set & NativeDraws::kTex0 ) c.tex0 = v.tex0;
                    if (set & NativeDraws::kTex1) c.tex1 = v.tex1;
                    if (set & NativeDraws::kClamp) c.clamp = v.clamp;
                    if (set & NativeDraws::kAlpha) c.alpha = v.alpha;
                    if (set & NativeDraws::kTest) c.test = v.test;
                    if (set & NativeDraws::kFba) c.fba = v.fba;
                    if (set & NativeDraws::kMiptbp) c.miptbp1 = v.miptbp1, c.miptbp2 = v.miptbp2;
                }
            if (const uint32_t set = d.endSet[2])
            {   
                if (set & NativeDraws::kTexa) m_texa = e.texa;
                if (set & NativeDraws::kTexclut) m_texclut = e.texclut;
                if (set & NativeDraws::kFogcol) m_fogR = uint8_t(e.fogcol), m_fogG = uint8_t(e.fogcol >> 8), m_fogB = uint8_t(e.fogcol >> 16) ;
                if (set & NativeDraws::kDthe) m_dthe = e.dthe;
                if (set & NativeDraws::kColclamp ) m_colclamp = e.colclamp;   
                if (set & NativeDraws::kPabe) m_pabe = e.pabe;
                if (set & NativeDraws::kScanmsk) m_scanmsk = e.scanmsk;
                if (set & NativeDraws::kDimx) m_dimx = e.dimx;
                if (set & NativeDraws::kPrim) m_primRegister = e.primRegister;
                if (set & (NativeDraws::kPrim | NativeDraws::kPrmode)) m_prim = e.prim, m_prmodeRegister = e.prmodeRegister, m_prmodecont = e.prmodecont;
                if ( set & NativeDraws::kRgbaq) m_curR = e.rgba[0], m_curG = e.rgba[1], m_curB = e.rgba[2], m_curA = e.rgba[3], m_curQ = e.q;
                if (set & NativeDraws::kSt) m_curS = e.s, m_curT = e.t;
                if (set & NativeDraws::kUv) m_curU = e.u, m_curV = e.v;
                if (set & NativeDraws::kFog) m_curFog = e.fog;   
                if (set & NativeDraws::kTransfer) m_bitbltbuf = e.bitbltbuf, m_trxpos = e.trxpos, m_trxreg = e.trxreg;
            }
#ifdef DK_PORT_CHECK
            m_vtxCount = 0 ;
#endif
            m_applying = false;
        }

        void applyNative(const Native2D &draw)
        {
            if (isTypedNative(draw))
            {
                NativeDraws d;
                if (typedNativeDraws(draw, d))
                    applyDraws(d);
                return;
            }  
#ifndef DK_PORT_CHECK
            typedListBad(draw, "a GS register list (only the test build decodes them)"); 
#else
            m_applying = true;
            for (const Native2D::Write &w : draw.writes )
            {
                if (w.reg == Native2D::kImage)
                {
                    const auto &image = draw.images[size_t(w.value)];
                    if (!image.empty())
                        m_sink->upload(image.data(), uint32_t(image.size()));

                }
                else if (w.reg < 0xF0)
                    writeRegisterUnlocked(w.reg, w.value);
            }
            m_applying = false;
#endif
        }

#ifdef DK_PORT_CHECK
        struct Collect final : GsSink
        {
            std::vector<GSPrimitiveBatch> prims;
            std::vector<GSTransferCommand> transfers;
            uint64_t bytes = 0;
            void submit(const GSPrimitiveBatch &b) override { prims.push_back(b); } 
            void beginTransfer(const GSTransferCommand &c) override { transfers.push_back(c); }
            void upload(const uint8_t *, uint32_t size) override { bytes += size; }
            void textureFlush() override {}
            void privileged(uint8_t, uint64_t) override {}
        };
        struct EndState
        {
            GSContext ctx[2];
            GSTexaReg texa;
            uint64_t dimx = 0, dthe = 0, colclamp = 0, scanmsk = 0;
            uint8_t fogR = 0, fogG = 0, fogB = 0;
            bool pabe = false, prmodecont = true;
        };
        static EndState endState(const GsDecoder &d)
        {
            EndState e;
            e.ctx[0] = d.m_ctx[0];
            e.ctx[1] = d.m_ctx[1];
            e.texa = d.m_texa;
            e.dimx = d.m_dimx, e.dthe = d.m_dthe, e.colclamp = d.m_colclamp, e.scanmsk = d.m_scanmsk;
            e.fogR = d.m_fogR, e.fogG = d.m_fogG, e.fogB = d.m_fogB;
            e.pabe = d.m_pabe, e.prmodecont = d.m_prmodecont;
            return e;
        }
        static std::string endStateDiff(const EndState &a, const EndState &b)
        {
            char t[160];
            for (int i = 0; i < 2; ++i)
            {
                const GSContext &c = a.ctx[i], &d = b.ctx[i];
                const char *what = nullptr;
                if (c.frame.fbp != d.frame.fbp || c.frame.fbw != d.frame.fbw || c.frame.psm != d.frame.psm || c.frame.fbmsk != d.frame.fbmsk)
                    what = "FRAME";

                else if (c.zbuf.zbp != d.zbuf.zbp || c.zbuf.psm != d.zbuf.psm || c.zbuf.zmask != d.zbuf.zmask)
                    what = "ZBUF";   
                else if (c.tex0.tbp0 != d.tex0.tbp0 || c.tex0.tbw != d.tex0.tbw || c.tex0.psm != d.tex0.psm || c.tex0.tw != d.tex0.tw || c.tex0.th != d.tex0.th || c.tex0.tcc != d.tex0.tcc || c.tex0.tfx != d.tex0.tfx || c.tex0.cbp != d.tex0.cbp || c.tex0.cpsm != d.tex0.cpsm || c.tex0.csm != d.tex0.csm || c.tex0.csa != d.tex0.csa)
                    what = "TEX0";
                else if (c.tex1 != d.tex1 || c.clamp != d.clamp)
                    what = "TEX1/CLAMP";
                else if (c.alpha != d.alpha)
                    what = "ALPHA";
                else if (c.test != d.test)

                    what = "TEST";
                else if (c.scissor.x0 != d.scissor.x0 || c.scissor.x1 != d.scissor.x1 || c.scissor.y0 != d.scissor.y0 || c.scissor.y1 != d.scissor.y1)
                    what = "SCISSOR";
                else if (c.xyoffset.ofx != d.xyoffset.ofx || c.xyoffset.ofy != d.xyoffset.ofy)
                    what = "XYOFFSET";
                else if (c.fba != d.fba)
                    what = "FBA";
                if (what)
                    return std::snprintf(t, sizeof t, "end state %s_%d", what, i + 1), t;
            }
            if (a.texa.ta0 != b.texa.ta0 || a.texa.aem != b.texa.aem || a.texa.ta1 != b.texa.ta1)
                return "end state TEXA";
            if (a.dimx != b.dimx || a.dthe != b.dthe || a.colclamp != b.colclamp || a.scanmsk != b.scanmsk)
                return "end state DIMX/DTHE/COLCLAMP/SCANMSK";
            if (a.fogR != b.fogR || a.fogG != b.fogG || a.fogB != b.fogB)
                return "end state FOGCOL";
            if (a.pabe != b.pabe || a.prmodecont != b.prmodecont)
                return "end state PABE/PRMODECONT";
            return {};
        }
        struct CheckRun
        {
            bool active = false, ownerSeen = false;

            uint32_t function = 0, owner = 0;
            EndState portEnd;
            Collect expected;
            std::vector<GSPrimitiveBatch> gotPrims;
            std::vector<GSTransferCommand> gotTransfers;   
            uint64_t gotBytes = 0, gotHash = 1469598103934665603ull, expectedHash = 1469598103934665603ull;
        } m_check;
        struct CheckStats
        {
            uint64_t calls = 0, equal = 0;
            uint32_t reported = 0;

        };
        std::map<uint32_t, CheckStats> m_checkStats;
        void checkBegin(const Native2D &draw)
        {
            checkEnd();
            m_check = {}; 
            m_check.active = true;
            m_check.function = draw.function;
            GsDecoder shadow = static_cast<const GsDecoder &>(*this);
            shadow.m_sink = &m_check.expected;
            shadow.m_counting = false;
            for (const Native2D::Write &w : draw.writes )
            {
                if (w.reg == Native2D::kImage)
                {
                    const auto &image = draw.images[size_t(w.value)];
                    m_check.expected.bytes += image.size();
                    for (const uint8_t b : image)
                        m_check.expectedHash = (m_check.expectedHash ^ b) * 1099511628211ull;
                }

                else if (w.reg < 0xF0)
                    shadow.writeRegisterUnlocked(w.reg, w.value);
            }
            m_check.portEnd = endState(shadow);
        }
        void checkOwner(uint32_t owner)
        {
            if (!m_check.active)
                return;
            if (!m_check.ownerSeen)
            {
                m_check.ownerSeen = true;
                m_check.owner = owner;
            }
            else if (owner != m_check.owner)
                checkEnd();
        }

        static std::string primDiff(const GSPrimitiveBatch &a, const GSPrimitiveBatch &b)
        {
            char t[256];
            if (a.vertexCount != b.vertexCount)
                return "vertex count";
            const GSDrawState &x = a.state, &y = b.state;
            const GSContext &c = x.context, &d = y.context;
            auto pr = [](const GSPrimReg &p) {

                return uint32_t(p.type) | p.iip << 3 | p.tme << 4 | p.fge << 5 | p.abe << 6 | p.aa1 << 7 | p.fst << 8 | p.ctxt << 9 | p.fix << 10;
            };
            if (pr(x.prim) != pr(y.prim))
                return std::snprintf(t, sizeof t, "PRIM %x vs %x", pr(x.prim), pr(y.prim)), t;
            if (c.frame.fbp != d.frame.fbp || c.frame.fbw != d.frame.fbw || c.frame.psm != d.frame.psm || c.frame.fbmsk != d.frame.fbmsk)
                return "FRAME";
            if (c.zbuf.zbp != d.zbuf.zbp || c.zbuf.psm != d.zbuf.psm || c.zbuf.zmask != d.zbuf.zmask)
                return "ZBUF";   
            const GSTex0Reg &e = c.tex0, &f = d.tex0;
            if (x.prim.tme && (e.tbp0 != f.tbp0 || e.tbw != f.tbw || e.psm != f.psm || e.tw != f.tw || e.th != f.th || e.tcc != f.tcc || e.tfx != f.tfx || e.cbp != f.cbp || e.cpsm != f.cpsm || e.csm != f.csm || e.csa != f.csa))
                return std::snprintf(t, sizeof t, "TEX0 tbp %x/%x psm %u/%u cbp %x/%x", e.tbp0, f.tbp0, e.psm, f.psm, e.cbp, f.cbp), t;
            if (x.prim.tme && (c.clamp != d.clamp || c.tex1 != d.tex1))
                return "CLAMP/TEX1";
            if (c.alpha != d.alpha && (x.prim.abe || pr(x.prim) != pr(y.prim)))
                return std::snprintf(t, sizeof t, "ALPHA %llx vs %llx", (unsigned long long)c.alpha, (unsigned long long)d.alpha), t;   
            if (c.test != d.test)
                return std::snprintf(t, sizeof t, "TEST %llx vs %llx", (unsigned long long)c.test, (unsigned long long)d.test), t;
            if (c.scissor.x0 != d.scissor.x0 || c.scissor.x1 != d.scissor.x1 || c.scissor.y0 != d.scissor.y0 || c.scissor.y1 != d.scissor.y1 )

                return "SCISSOR";
            if (c.xyoffset.ofx != d.xyoffset.ofx || c.xyoffset.ofy != d.xyoffset.ofy)
                return "XYOFFSET";
            if (c.fba != d.fba || x.pabe != y.pabe || x.colclamp != y.colclamp || x.dthe != y.dthe || x.texa.ta0 != y.texa.ta0 || x.texa.aem != y.texa.aem || x.texa.ta1 != y.texa.ta1)
                return "FBA/PABE/COLCLAMP/DTHE/TEXA";
            if (x.prim.fge && (x.fogR != y.fogR || x.fogG != y.fogG || x.fogB != y.fogB))
                return "FOGCOL";
            for ( int i =  0; i < a.vertexCount; ++i)
            {
                const GSVertex &v = a.vertices[size_t(i)], &w = b.vertices[size_t(i)];
                if (v.x != w.x || v.y != w.y || v.z != w.z)
                    return std::snprintf(t, sizeof t, "v%d XYZ %.4f,%.4f,%.0f vs %.4f,%.4f,%.0f", i, v.x, v.y, v.z, w.x, w.y, w.z), t;
                if (v.r != w.r || v.g != w.g || v.b != w.b || v.a != w.a)
                    return std::snprintf(t, sizeof t, "v%d RGBA %02x%02x%02x%02x vs %02x%02x%02x%02x", i, v.r, v.g, v.b, v.a, w.r, w.g, w.b, w.a), t;
                if (x.prim.tme && (x.prim.fst ? (v.u != w.u || v.v != w.v) : (v.s != w.s || v.t != w.t || v.q != w.q)))
                    return std::snprintf(t, sizeof t, "v%d UV/STQ %u,%u %.5f,%.5f,%.5f vs %u,%u %.5f,%.5f,%.5f", i, v.u, v.v, v.s, v.t, v.q, w.u, w.v, w.s, w.t, w.q), t;
                if (x.prim.fge && v.fog != w.fog)
                    return "FOG";
            }

            return {};
        }  
        void checkEnd()
        {
            if (!m_check.active)

                return;
            m_check.active = false;
            CheckStats &st = m_checkStats[m_check.function];
            ++st.calls;
            std::string why;
            const auto &e = m_check.expected;
            if (e.prims.size() != m_check.gotPrims.size() )   
                why = "primitives " + std::to_string(e.prims.size()) + " vs game " + std::to_string(m_check.gotPrims.size());
            for (size_t i = 0; why.empty() && i < e.prims.size(); ++i)
                if (std::string d = primDiff(e.prims[i], m_check.gotPrims[i]); !d.empty())
                    why = "primitive " + std::to_string(i) + ": " + d;
            if (why.empty() && e.bytes == m_check.gotBytes && m_check.expectedHash != m_check.gotHash)
                why = "upload data differs (" + std::to_string(e.bytes) + " bytes)";
            if (why.empty() && (e.transfers.size() != m_check.gotTransfers.size() || e.bytes != m_check.gotBytes))
                why = "transfers " + std::to_string(e.transfers.size()) + "/" + std::to_string(e.bytes) + " bytes vs game " +
                       std::to_string(m_check.gotTransfers.size()) + "/" + std::to_string(m_check.gotBytes);
            if (why.empty())
                why = endStateDiff(m_check.portEnd, endState(*this));

            if (why.empty())
                ++st.equal;
            else if (st.reported < 8)
            {
                ++st.reported;
                std::fprintf(stderr, "[native2d] %06X call %llu differs: %s\n", m_check.function, (unsigned long long)st.calls, why.c_str());
            }
        }
        void printCheckStats()
        {
            static uint32_t vsyncs = 0;
            if (m_checkStats.empty() || ++vsyncs < 600)
                return;
            vsyncs = 0;
            std::string line = "[native2d] equal/calls:";
            char item[64];
            for (const auto &[f, st] : m_checkStats)
            {
                std::snprintf(item, sizeof item, " %06X %llu/%llu", f, (unsigned long long)st.equal, (unsigned long long)st.calls);

                line += item;
            }
            std::fprintf(stderr, "%s\n", line.c_str());
        }
#endif

        static void printStats()
        {
            static uint32_t vsyncs = 0;   
            if (++vsyncs < 600)
                return;
            vsyncs = 0;
            uint64_t gif[4];
            dkTakeGifStats(gif);
            std::fprintf(stderr,
                        "[gs-frontend] per vsync: GIF %.0f bytes (path1 %.0f path2 %.0f path3 %.0f; VU1 XGKICK %.0f), %.1f "
                        "primitives, %.1f transfers, %.1f render commands\n",
                        g_statGifBytes.exchange(0) / 600.0, gif[1] / 600.0, gif[2] / 600.0, gif[3] / 600.0, gif[0] / 600.0,
                        g_statPrims.exchange(0) / 600.0,
                        g_statTransfers.exchange(0) / 600.0, g_statCommands.exchange(0) / 600.0);
            if (!g_statKinds)
                return;
            std::vector<std::pair<uint64_t, uint64_t>> top;
            {
                std::lock_guard<std::mutex> lock(g_kindMutex);
                top.assign(g_kinds.begin(), g_kinds.end());
                g_kinds.clear();
            }
            std::sort(top.begin(), top.end(), [](auto &a, auto &b) { return a.second > b.second; });
            for (size_t i = 0; i < top.size() && i < 10; ++i)
            {
                const uint64_t k = top[i].first;
                std::fprintf(stderr, "[gs-frontend]   %6.1f/vsync prim %llu tme %llu abe %llu ctxt %llu fbp %03llX tbp %04llX alpha %02llX fix %02llX\n", top[i].second / 600.0, (unsigned long long)(k & 7), (unsigned long long)((k >> 3) & 1), (unsigned long long)((k >> 4) & 1), (unsigned long long)((k >> 5) & 1), (unsigned long long)((k >> 8) & 0x1FF), (unsigned long long)((k >> 20) & 0x3FFF), (unsigned long long)((k >> 40) & 0xFF), (unsigned long long)((k >> 48) & 0xFF));
            }

        }

        mutable std::recursive_mutex m_mutex;

        const PrivRegs &m_privRegs;
        RenderQueue m_queue;
        bool m_ownerNative = false;

        bool m_applying = false;

        const bool m_gameGifLog = [] {
            const char *v = std::getenv("PS2_DK_GAME_GIF_LOG");
            return v && *v == '1';
        }();
        uint64_t m_gameGifBytes = 0, m_gameGifPackets = 0, m_gameGifPriv = 0, m_gameGifReadback = 0, m_gameGifPresents = 0;
        void gameGifSkip(const uint8_t *data, uint32_t sizeBytes)
        {
            uint32_t priv = 0;
            bool readback = false;

            std::pair<uint8_t, uint64_t> pending[8];

            uint32_t pendingCount = 0;
            for (uint32_t offset = 0; offset + 16 <= sizeBytes;)
            {  
                const uint64_t tagLo = load64( data + offset), tagHi = load64(data + offset + 8);
                offset += 16;
                const uint32_t nloop = uint32_t(tagLo & 0x7FFF);
                const uint8_t flg = uint8_t((tagLo >> 58) & 0x3);
                uint32_t nreg = uint32_t((tagLo >> 60) & 0xF);
                if (nreg == 0)
                    nreg = 16 ;

                if (flg == GIF_FMT_PACKED)  
                {
                    for (uint32_t loop = 0; loop < nloop; ++loop)
                        for (uint32_t r = 0; r < nreg && offset + 16 <= sizeBytes; ++r, offset += 16)

                            if (((tagHi >> (r * 4)) & 0xF) == 0xE) // A+D

                            {

                                const uint8_t reg = uint8_t(load64(data + offset + 8) & 0xFF);
                                const uint64_t value = load64(data + offset);
                                if (reg == GS_REG_BITBLTBUF || reg == GS_REG_TRXPOS || reg == GS_REG_TRXREG)
                                {  
                                    if (readback)
                                        setTransferRegister(reg, value);
                                    else if (pendingCount < 8)
                                        pending[pendingCount++] = {reg, value};

                                }
                                else if (reg == GS_REG_TRXDIR && (value & 3) == 1)
                                {

                                    for (uint32_t i = 0; i < pendingCount; ++i)
                                        setTransferRegister(pending[i].first, pending[i].second);
                                    pendingCount = 0;
                                    beginTransfer( transferCommand(value));
                                    readback = true;
                                }
                                else if (reg == GS_REG_SIGNAL || reg == GS_REG_FINISH || reg == GS_REG_LABEL)
                                    privileged(reg, value), ++priv;
                            }
                }
                else if ( flg == GIF_FMT_REGLIST)
                    offset += (nloop * nreg + 1) / 2 * 16;

                else if(flg == GIF_FMT_IMAGE)
                    offset += nloop * 16;
            }
            m_gameGifBytes += sizeBytes;
            m_gameGifPriv += priv;
            m_gameGifReadback += readback ? 1 : 0;
            if (m_gameGifLog && (m_gameGifPackets < 16 || readback))
                std::fprintf(stderr, "[game-gif] t%llu %u bytes owner %06X%s priv %u%s tag %016llX %016llX\n", (unsigned long long)PS2Det::vsyncTick(),

                            sizeBytes, m_logOwner, m_ownerNative ? " (native)" : "", priv, readback ? " readback" : "",
                            (unsigned long long)load64(data), (unsigned long long)load64(data + 8));
            ++m_gameGifPackets;
        }
        void gameGifStats()
        {
            if (m_gameGifLog && ++m_gameGifPresents % 600 == 0)
                std::fprintf(stderr, "[game-gif] t%llu skipped %llu packets %llu bytes, privileged writes %llu, readbacks %llu\n", (unsigned long long)PS2Det::vsyncTick(), (unsigned long long)m_gameGifPackets, (unsigned long long)m_gameGifBytes, (unsigned long long)m_gameGifPriv, (unsigned long long)m_gameGifReadback);
        }
    } ;

    class GsShim final : public GS
    {
      public:
        GsShim() : m_recorder( m_regs) {}
        void init(uint8_t *vram, uint32_t vramSize, GSRegisters *privRegs) override
        {
            m_regs.regs = privRegs;
            m_recorder.init(vram, vramSize);
        }
        void reset() override { m_recorder.reset(); }
        void processGIFPacket(const uint8_t *data, uint32_t sizeBytes) override { m_recorder.processGIFPacket(data, sizeBytes); }
        bool processNativePackedGIFPacket(const uint8_t *data, uint32_t sizeBytes) override
        {
            return m_recorder.processNativePackedGIFPacket(data, sizeBytes);
        }
        void uploadImageNative(uint64_t bitbltbuf, uint64_t trxpos, uint64_t trxreg, uint64_t trxdir, const uint8_t *data, uint32_t sizeBytes) override
        {

            m_recorder.uploadImageNative(bitbltbuf, trxpos, trxreg, trxdir, data, sizeBytes);
        }
        void writeRegister(uint8_t regAddr, uint64_t value) override { m_recorder.writeRegister(regAddr, value); }

        void latchHostPresentationFrame() override
        {
            GSPresentationRequest request{};
            if (m_regs.on())
            {
                uint64_t display[8];
                m_regs.read(display );

                gsLatchedDisplayRegisters(display);
                request.pmode = display[0];
                request.smode2 = display[1];
                request.dispfb1 = display[2];
                request.display1 = display[3];
                request.dispfb2 = display[4];
                request.display2 = display[5];
                request.bgcolor = display[6];
                request.vsyncTick = display[7];
            }
            m_recorder.present(request);
        }
        bool clearFramebufferContext(uint32_t contextIndex, uint32_t rgba) override
        {
            return m_recorder.clearFramebufferContext(contextIndex, rgba);
        }
        uint32_t consumeLocalToHostBytes(uint8_t *dst, uint32_t maxBytes) override
        {
            return m_recorder.consumeLocalToHostBytes(dst, maxBytes);
        }
        GSFrameReg getContextFrame(int index) const override { return m_recorder.getContextFrame(index); }
        bool getPreferredDisplaySource(GSFrameReg &outSource, uint32_t &outDestFbp) const override

        {
            return m_recorder.getPreferredDisplaySource(outSource, outDestFbp);
        }
        bool directGif() const override { return true; }

      private:
        PrivRegs m_regs;
        RenderRecorder m_recorder;
    } ;

}  

bool renderMakeNativeDraws(const std::shared_ptr<const Native2D> &draw, NativeDraws &out)
{

    if (!draw || draw->check)
        return false;

    auto counted = [](bool made, bool decoded) {
        const uint64_t n = g_drawsMade.load(std::memory_order_relaxed) + g_drawsKept.load(std::memory_order_relaxed) + 1;
        (made ? g_drawsMade : g_drawsKept).fetch_add(1, std::memory_order_relaxed );
        if (decoded)
            g_drawsDecoded.fetch_add(1, std::memory_order_relaxed);
        if (n % 20000 == 0 )
        {
            std::lock_guard<std::mutex> lock(g_drawsWhyMutex);
            std::string kept;
            for (const auto &[k, c] : g_drawsWhy)
                kept += " | " + k + ": " + std::to_string(c);
            std::fprintf(stderr, "[native-draws] %llu made (decoded from GS registers %llu), %llu kept as register lists%s\n", (unsigned long long)g_drawsMade.load(), (unsigned long long)g_drawsDecoded.load(), (unsigned long long)g_drawsKept.load(), kept.c_str());
        }
    };
    if (isTypedNative(*draw))
    {
        if (!typedNativeDraws(*draw, out, draw.use_count() == 1 ? const_cast<Native2D *>(draw.get()) : nullptr))
            return false;
        counted(true, false);
        return true;
    }
#ifndef DK_PORT_CHECK
    counted(false, false);
    return false;
#else
    DrawBuilder b;
    b.dec.m_sink = &b;
    b.dec.m_counting = false;  
    b.dec.m_tellWrites =  true;
    b.dec.resetState();
    {
        size_t vertices = 0;

        for (const Native2D::Write &w : draw->writes)
            vertices += w.reg == GS_REG_XYZ2 || w.reg == GS_REG_XYZF2 || w.reg == GS_REG_XYZ3 || w.reg == GS_REG_XYZF3;
        b.out.prims.reserve(vertices);
        b.out.items.reserve( vertices + 8);
    }
    for (const Native2D::Write &w : draw->writes)
    {
        if (w.reg == Native2D::kImage)
        {

            const auto &image = draw->images[size_t(w.value)];
            if (!image.empty())
                b.upload(image.data(), uint32_t(image.size()) );
        }
        else if (w.reg < 0xF0)
            b.dec.writeRegisterUnlocked(w.reg, w.value);
        if(!b.ok)   
            break;
    }
    if (!b.ok)
    {
        std::lock_guard<std::mutex> lock(g_drawsWhyMutex);
        char key[64];
        std::snprintf(key, sizeof key, "%06X %s", draw->function, b.why ? b.why : "?");
        ++g_drawsWhy[key];
    }
    counted(b.ok, b.ok);
    if (!b.ok)

        return false;
    NativeDraws &d = b.out;
    d.function = draw->function;
    const GsDecoder &s = b.dec;
    d.endSet[0] = b.set[0];
    d.endSet[1] = b.set[1];
    d.endSet[2] = b.set[2];
    d.end.ctx[0] = s.m_ctx[0];
    d.end.ctx[1] = s.m_ctx[1];
    d.end.texa = s.m_texa;
    d.end.texclut =  s.m_texclut;
    d.end.fogcol = uint32_t(s.m_fogR) | uint32_t(s.m_fogG) << 8 | uint32_t(s.m_fogB) << 16;
    d.end.dthe = s.m_dthe;
    d.end.colclamp = s.m_colclamp;
    d.end.pabe = s.m_pabe;
    d.end.scanmsk = s.m_scanmsk;
    d.end.dimx = s.m_dimx;
    d.end.prim =  s.m_prim;
    d.end.primRegister = s.m_primRegister;
    d.end.prmodeRegister = s.m_prmodeRegister;
    d.end.prmodecont = s.m_prmodecont;
    d.end.rgba[0] = s.m_curR, d.end.rgba[1] = s.m_curG, d.end.rgba[2] = s.m_curB, d.end.rgba[3] = s.m_curA;
    d.end.q = s.m_curQ, d.end.s = s.m_curS, d.end.t = s.m_curT, d.end.u = s.m_curU, d.end.v = s.m_curV, d.end.fog = s.m_curFog;
    d.end.bitbltbuf = s.m_bitbltbuf, d.end.trxpos = s.m_trxpos, d.end.trxreg = s.m_trxreg;
    out = std::move(d);   
    return true;
#endif
}

std::unique_ptr<GS> makeRenderRecorder()
{
    return std::make_unique<GsShim>();
}
