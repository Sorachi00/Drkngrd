#pragma once

#include <cstdint>
#include <functional>

namespace GraphicsThread
{
    bool active(); // enabled (the thread starts at the first job)
    bool onThread();
    void submit(std::function<void()> job);
    void setVuControlSource(std::function<uint32_t()> fn);
    void sync();   
    bool syncFor(uint32_t address, bool write);
    void setPcSource(std::function<uint32_t()> fn);

    bool deferPrivWrite(std::function<void()> write);  
    void setCsrNoSyncReadPc(uint32_t pc);

    void frameBoundary();
    // VIF1/GIF/GS registers and FIFOs, VU1 memory, GS privileged registers.
    bool isGraphicsAddress(uint32_t address);

    uint32_t jobVuControl() ;
    void setVuStopBits( uint32_t bits);   
    bool takeVuStopBits(uint32_t &bits);
    // Runs on the EE thread at the end of each sync that waited for work.

    void setAfterSync(std::function<void()> fn);   

    bool gifStage();  
    void disableGifStage();
    // Graphics thread: queue one packet (copied) for the GIF stage.
    void submitGif(const uint8_t *data, uint32_t size);
    void gifCall(std::function<void()> call);
    // The GIF stage hands each packet to this function.
    void setGifSink(std::function<void(const uint8_t *, uint32_t)> fn);
    void shutdown();
}
