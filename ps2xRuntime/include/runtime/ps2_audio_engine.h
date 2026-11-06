#pragma once

#include "runtime/ps2_spu2.h"

#include <cstdint>
#include <memory>

class PS2AudioEngine  
{
public:
    static PS2AudioEngine &instance();

    // Opens the output stream when the host audio device is ready.
    void start(PS2Spu2::GuestResolver resolver, bool audioDeviceReady);
    void stop();
    void reset();

    PS2Spu2 &spu2() { return m_spu2; }

    uint32_t sdrCommand(uint32_t function, const uint32_t *args, uint32_t argCount);
    // The same commands over SIF RPC (sid 0x80000701).
    void onSoundCommand(uint32_t sid, uint32_t function, const uint8_t *sendBuf, uint32_t sendSize,
                        uint8_t *recvBuf, uint32_t recvSize);


     // Audio thread: `frames` interleaved stereo frames at PS2Spu2::kSampleRate.
    void render(int16_t *pcm, uint32_t frames);

    void setMasterVolume(float volume);
    float masterVolume() const ;
    void setMuted(bool muted);
    bool muted() const;

private:
    PS2AudioEngine();   
    ~PS2AudioEngine() ;

    struct Impl;
    std::unique_ptr<Impl> m_impl;
     PS2Spu2 m_spu2;
};
