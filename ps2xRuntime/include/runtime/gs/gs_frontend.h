#ifndef PS2_GS_FRONTEND_H
#define PS2_GS_FRONTEND_H

#include <array>
#include <atomic>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <mutex>
#include <vector>

#include "runtime/gs/gs_backend.h"

struct GSDebugSnapshot
{
    GSContext ctx[2]{};
    GSPrimReg prim{};
    GSTexaReg texa{};
    GSTexClutReg texclut{};
    uint64_t scanmsk = 0;
    uint64_t dimx = 0;
    uint64_t dthe = 0;
    uint64_t colclamp = 0;
    GSBitBltBuf bitbltbuf{};
    GSTrxPos trxpos{};
    GSTrxReg trxreg{};
    uint32_t trxdir = 0;
    uint32_t transferX = 0;
    uint32_t transferY = 0;
    uint32_t transferTotalPixels = 0;
    uint32_t transferCopiedPixels = 0;
    uint32_t lastDisplayBaseBytes = 0;
    GSFrameReg preferredDisplaySourceFrame{};
    uint32_t preferredDisplayDestFbp = 0;
    bool hasPreferredDisplaySource = false;
    uint32_t hostPresentationWidth = 0;
    uint32_t hostPresentationHeight = 0;
    uint32_t hostPresentationDisplayFbp = 0;
    uint32_t hostPresentationSourceFbp = 0;
    bool hostPresentationUsedPreferred = false;
    bool hasHostPresentationFrame = false;
    size_t localToHostPendingBytes = 0;
};

enum class GSDebugEventKind : uint8_t
{
    GifTag = 0,
    Register = 1,
    Draw = 2,
    Transfer = 3,
    Present = 4,
};

struct GSDebugHistoryEntry
{
    uint64_t seq = 0;
    uint64_t vsyncTick = 0;
    uint32_t frameIndex = 0;
    GSDebugEventKind kind = GSDebugEventKind::Register;

    uint8_t reg = 0;
    uint64_t regValue = 0;

    uint32_t gifSizeBytes = 0;
    uint32_t gifNloop = 0;
    uint8_t gifFlg = 0;
    uint8_t gifNreg = 0;

    GSPrimReg prim{};
    GSFrameReg frame{};
    GSZbufReg zbuf{};
    GSTex0Reg tex0{};
    GSScissorReg scissor{};
    uint64_t test = 0;
    uint64_t alpha = 0;

    uint32_t vertexCount = 0;
    float xMin = 0.0f;
    float xMax = 0.0f;
    float yMin = 0.0f;
    float yMax = 0.0f;
    double zMin = 0.0;
    double zMax = 0.0;
    uint8_t aMin = 0;
    uint8_t aMax = 0;

    GSBitBltBuf bitbltbuf{};
    GSTrxPos trxpos{};
    GSTrxReg trxreg{};
    uint32_t trxdir = 0;
    uint32_t transferPixels = 0;

    uint32_t displayFbp = 0;
    uint32_t sourceFbp = 0;
    uint32_t width = 0;
    uint32_t height = 0;
    bool usedPreferred = false;
};

class GS
{
public:
    virtual ~GS() = default;


    virtual void init(uint8_t *vram, uint32_t vramSize, struct GSRegisters *privRegs = nullptr) = 0;
    virtual void reset() = 0;

    virtual void processGIFPacket(const uint8_t *data, uint32_t sizeBytes) = 0;

    virtual bool processNativePackedGIFPacket(const uint8_t *data, uint32_t sizeBytes) = 0;
    virtual void uploadImageNative(uint64_t bitbltbuf, uint64_t trxpos, uint64_t trxreg, uint64_t trxdir, const uint8_t *data, uint32_t sizeBytes) = 0;
    virtual void writeRegister(uint8_t regAddr, uint64_t value) = 0;

    // Vsync: show the frame drawn so far.
    virtual void latchHostPresentationFrame() = 0;
    // Platforms without a window presenter: the picture for the CPU.
    virtual bool copyLatchedHostPresentationFrame(std::vector<uint8_t> &outPixels, uint32_t &outWidth, uint32_t &outHeight, uint32_t *outDisplayFbp = nullptr, uint32_t *outSourceFbp = nullptr, bool *outUsedPreferred = nullptr) const
    {
        return false;
    }
    virtual bool clearFramebufferContext( uint32_t contextIndex, uint32_t rgba) = 0;
    virtual uint32_t consumeLocalToHostBytes(uint8_t *dst, uint32_t maxBytes) = 0;
    virtual GSFrameReg getContextFrame(int index) const = 0;
    virtual bool getPreferredDisplaySource(GSFrameReg &outSource, uint32_t &outDestFbp) const = 0;
    virtual bool directGif() const { return false; }

    // Debug UI (ps2_debug_panel.cpp).
    virtual GSDebugSnapshot getDebugSnapshot() const { return {}; }
    virtual std::vector<GSDebugHistoryEntry> getDebugHistory() const { return {}; }
    virtual void clearDebugHistory() {}

    virtual bool isDebugHistoryPaused() const { return true; }
    virtual void setDebugHistoryPaused( bool) {}
};

using GSFrontendFactory = std::unique_ptr<GS> (*)();
void gsSetFrontendFactory(GSFrontendFactory factory);
std::unique_ptr<GS> gsCreate();


// Display registers latched at vsync (EeScheduler), read by the presentation.
void gsLatchDisplayRegisters(const struct GSRegisters &regs);
bool gsLatchedDisplayRegisters(uint64_t out[7]); // pmode, smode2, dispfb1, display1, dispfb2, display2, bgcolor

#endif
