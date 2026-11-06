#pragma once

#include <cstdint>
#include <functional>
#include <memory>

namespace ps2x::iop
{
    namespace sd
    {
        constexpr uint32_t voiceEntry(uint32_t core, uint32_t voice)
        {
            return (core & 1u) | (voice << 1); 
        }

        constexpr uint32_t VP_VOLL = 0x0000u;
         constexpr uint32_t VP_VOLR = 0x0100u;
        constexpr uint32_t VP_PITCH = 0x0200u;
         constexpr uint32_t VP_ADSR1 = 0x0300u;
        constexpr uint32_t VP_ADSR2 = 0x0400u;
         constexpr uint32_t VP_ENVX = 0x0500u;
        constexpr uint32_t VP_VOLXL = 0x0600u;   

        constexpr uint32_t VP_VOLXR = 0x0700u;
        constexpr uint32_t P_MMIX = 0x0880u;
        constexpr uint32_t P_MVOLL = 0x0980u;
        constexpr uint32_t P_MVOLR = 0x0A80u;
         constexpr uint32_t P_EVOLL = 0x0B80u;
        constexpr uint32_t P_EVOLR = 0x0C80u;
        constexpr uint32_t P_AVOLL = 0x0D80u;
        constexpr uint32_t P_AVOLR = 0x0E80u;

        constexpr uint32_t P_BVOLL = 0x0F80u;
        constexpr uint32_t P_BVOLR = 0x1080u;
        constexpr uint32_t P_MVOLXL = 0x1180u;
        constexpr uint32_t P_MVOLXR = 0x1280u; 
        constexpr uint32_t S_PMON = 0x1300u;
        constexpr uint32_t S_NON = 0x1400u;  
        constexpr uint32_t S_KON = 0x1500u;
        constexpr uint32_t S_KOFF = 0x1600u;
        constexpr uint32_t S_ENDX = 0x1700u;
        constexpr uint32_t S_VMIXL = 0x1800u;
        constexpr uint32_t S_VMIXEL = 0x1900u ;
        constexpr uint32_t S_VMIXR = 0x1A00u;
        constexpr uint32_t S_VMIXER = 0x1B00u;
        constexpr uint32_t A_ESA =  0x1C00u;
        constexpr uint32_t A_EEA = 0x1D00u;
        constexpr uint32_t A_TSA = 0x1E00u;
        constexpr uint32_t A_IRQA = 0x1F00u;
        constexpr uint32_t VA_SSA = 0x2040u;
        constexpr uint32_t VA_LSAX = 0x2140u ;
        constexpr uint32_t VA_NAX = 0x2240u;

        constexpr uint32_t CORE_ATTR_EFFECT_ENABLE = 0x02u;
        constexpr uint32_t CORE_ATTR_IRQ_ENABLE = 0x04u;
         constexpr uint32_t CORE_ATTR_MUTE = 0x06u;
        constexpr uint32_t CORE_ATTR_NOISE_CLOCK = 0x08u;
        constexpr uint32_t CORE_ATTR_SPDIF_MODE = 0x0Au;

        constexpr uint32_t MMIX_SINER = 1u << 0;
        constexpr uint32_t MMIX_SINEL = 1u << 1;
        constexpr uint32_t MMIX_SINR =  1u << 2;
        constexpr uint32_t MMIX_SINL = 1u << 3;
        constexpr uint32_t MMIX_MINER = 1u << 4;
        constexpr uint32_t MMIX_MINEL = 1u << 5;
        constexpr uint32_t MMIX_MINR = 1u << 6;
        constexpr uint32_t MMIX_MINL = 1u << 7;
        constexpr uint32_t MMIX_MSNDER = 1u << 8;
        constexpr uint32_t MMIX_MSNDEL = 1u << 9;
        constexpr uint32_t MMIX_MSNDR = 1u << 10;
        constexpr uint32_t MMIX_MSNDL = 1u << 11;

        constexpr uint32_t TRANS_WRITE = 0u;
        constexpr uint32_t TRANS_READ = 1u;
        constexpr uint32_t TRANS_STOP = 2u;
        constexpr uint32_t TRANS_WRITE_FROM = 3u;
        constexpr uint32_t TRANS_DIRECTION_MASK = 3u;
        constexpr uint32_t TRANS_MODE_IO = 8u;
         constexpr uint32_t TRANS_LOOP = 0x10u;

        constexpr uint32_t BATCH_SETPARAM = 0x01u;
        constexpr uint32_t BATCH_SETSWITCH = 0x02u;
        constexpr uint32_t BATCH_SETADDR = 0x03u;
         constexpr uint32_t BATCH_SETCOREATTR = 0x04u;
        constexpr uint32_t BATCH_WRITEIOP = 0x05u;
        constexpr uint32_t BATCH_WRITEEE = 0x06u;
        constexpr uint32_t BATCH_EERETURN = 0x07u;
        constexpr uint32_t BATCH_GETPARAM = 0x11u;   
        constexpr uint32_t BATCH_GETSWITCH = 0x12u;
        constexpr uint32_t BATCH_GETADDR = 0x13u;
        constexpr uint32_t BATCH_GETCOREATTR = 0x14u;

        constexpr uint32_t CORE_COUNT = 2u;
        constexpr uint32_t VOICE_COUNT = 24u;
        constexpr uint32_t RAM_SIZE = 2u * 1024u * 1024u ;
        constexpr uint32_t SAMPLE_RATE = 48000u;
        constexpr uint32_t ADMA_BLOCK_BYTES = 1024u;
    }

    struct Spu2Batch
    {
        uint16_t func;
        uint16_t entry;
        uint32_t value ;
    };

    class HostPcmSource
    {
    public:
        virtual ~HostPcmSource() = default; 
        virtual uint32_t pull(int16_t *interleavedStereo, uint32_t frames) = 0;
        virtual bool finished() const = 0;
    };

    class Spu2Device  
    {
    public:
        virtual ~Spu2Device() = default;

        virtual void init(uint32_t flags) = 0;
        virtual void setParam(uint32_t entry, uint32_t value) = 0;   
        virtual uint32_t getParam(uint32_t entry) = 0; 
        virtual void setSwitch(uint32_t entry, uint32_t value) = 0;
         virtual uint32_t getSwitch(uint32_t entry) = 0;

        virtual void setAddr(uint32_t entry, uint32_t value) = 0;
         virtual uint32_t getAddr(uint32_t entry) = 0;
        virtual void setCoreAttr(uint32_t entry, uint32_t value) = 0;
        virtual uint32_t getCoreAttr(uint32_t entry) = 0;
        virtual uint32_t voiceTrans(uint32_t core, uint32_t mode, uint32_t iopAddr, uint32_t spuAddr, uint32_t size) = 0;
        virtual uint32_t blockTrans(uint32_t core, uint32_t mode, uint32_t iopAddr, uint32_t size, uint32_t startAddr) = 0;
         virtual uint32_t voiceTransStatus(uint32_t core, uint32_t flag) = 0; 
        virtual uint32_t blockTransStatus(uint32_t core, uint32_t flag) = 0;

        virtual int32_t procBatch(const Spu2Batch *batch, uint32_t count, uint32_t *returns, uint32_t voiceMask) = 0;

        virtual void setEffectAttr(uint32_t core, uint32_t mode, uint32_t depthL, uint32_t depthR,
                                   uint32_t delay, uint32_t feedback) = 0;
        virtual void clearEffectWorkArea(uint32_t core, uint32_t mode) = 0;

        virtual bool writeRam(uint32_t spuAddr, const void *data, uint32_t size) = 0;
        virtual bool readRam(uint32_t spuAddr, void *out, uint32_t size) const =  0;

        virtual void setPeriodicTick(std::function<void()> tick, uint32_t intervalFrames) = 0;

        virtual uint32_t createHostStream(uint32_t sampleRate, std::shared_ptr<HostPcmSource> source) = 0;
        virtual void destroyHostStream(uint32_t id) = 0;
        virtual void setHostStreamVolume(uint32_t id, float left, float right) = 0;
        virtual void setHostStreamPaused(uint32_t id, bool paused) = 0;
        virtual bool hostStreamActive(uint32_t id) const = 0;
    };
}
