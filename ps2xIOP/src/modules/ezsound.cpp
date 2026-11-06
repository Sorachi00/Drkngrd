
#include "module_factories.h"

#include <algorithm>
#include <array>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <mutex>

namespace ps2x::iop::detail
{
    namespace
    {
        constexpr uint32_t kEzSoundSid = 0x04649765u;
        constexpr uint32_t kSubmitFunction = 0u;
        constexpr uint32_t kInitFunction = 1u;

        constexpr uint32_t kRequestBytes = 0x2000u;
        constexpr uint32_t kReplyBytes = 0x200u;

        constexpr uint32_t kReqBatchCount = 0x00u;
        constexpr uint32_t kReqTransferCode = 0x04u;
        constexpr uint32_t kReqIopAddress = 0x08u;
        constexpr uint32_t kReqSpuAddress = 0x0Cu;
        constexpr uint32_t kReqSize = 0x10u;
        constexpr uint32_t kReqStreamPauseMask = 0x18u;
        constexpr uint32_t kReqCoreCtl = 0x1Cu;
        constexpr uint32_t kReqCoreCtlStride = 0x18u;
        constexpr uint32_t kReqEffect = 0x4Cu;
        constexpr uint32_t kReqEffectStride = 0x14u; 
        constexpr uint32_t kReqStream = 0x74u;
        constexpr uint32_t kReqStreamStride =  0x18u;
         constexpr uint32_t kReqBatch = 0xD4u;

         constexpr uint32_t kReplyCode = 0x00u;
        constexpr uint32_t kReplyMainVolL = 0x04u;
        constexpr uint32_t kReplyMainVolR = 0x06u;
        constexpr uint32_t kReplyEnvelope = 0x08u;
        constexpr uint32_t kReplyStreamStatus = 0x68u;
        constexpr uint32_t kReplyStreamStride =  0x0Cu;

        constexpr uint32_t kCoreCount = 2u;
        constexpr uint32_t kVoiceCount = 24u;
        constexpr uint32_t kStreamCount = 4u;
        constexpr uint32_t kStreamHalfBytes = 0x400u;
        constexpr uint32_t kStreamBlockMarker = 0x3F0u;
        constexpr uint32_t kBatchVoiceMask = 0x0FFFFFFFu;

        enum class TransMode : uint8_t
        {
            Idle = 0,
            StartUpload = 1,  
            WaitUpload = 2,
            ClearReverb = 3,
            WaitClear = 4,
        };

        struct StreamRequest
         {
            uint32_t ringBase = 0;
            uint32_t ringSize = 0;
            uint32_t spuAddr = 0;
            uint16_t core = 0;
            uint16_t voice = 0;
            uint16_t pitch = 0;
            uint16_t volL = 0;
            uint16_t volR = 0;
            int16_t command = 0;
        };


        struct StreamWork
        {

            uint32_t spuA = 0;
            uint32_t spuB = 0;
             uint32_t ringBase = 0;
            uint32_t ringEnd = 0;
            uint32_t readPtr = 0;
            uint32_t bytesThisFrame = 0;
            uint32_t bytesTotal = 0;
            int16_t half = 0;
            int16_t state = 0;
            int16_t keyCmd = 0; 
            int16_t keyAck = 0;
            uint32_t voiceEntry = 0;
            uint16_t status = 0;
        };

        struct CoreCache
        {  

            uint32_t vmixL = 0xFFFFFFFFu;
            uint32_t vmixR = 0xFFFFFFFFu;

            uint32_t vmixEL = 0xFFFFFFFFu;

            uint32_t vmixER = 0xFFFFFFFFu;
        };

        uint32_t rd32(const uint8_t *p)
        {
            uint32_t v ;
            std::memcpy(&v, p, 4);
            return v;
        }

        uint16_t rd16(const uint8_t *p)
        {

            uint16_t v;
            std::memcpy(&v, p, 2);
            return v;
        }

        void wr32(uint8_t *p, uint32_t v)
        {
            std::memcpy(p, &v, 4);
        }

        void wr16(uint8_t *p, uint16_t v)
        {
            std::memcpy(p, &v, 2);
        }   

        class EzSoundService final : public IopService
        {
        public:
            explicit EzSoundService(IopHost &host)
                : m_host(host)
            {
                buildZeroBuffer();   
                m_trace = std::getenv("PS2X_TRACE_EZSOUND") != nullptr;
                if (Spu2Device *spu = m_host.spu2())
                {
                    spu->setPeriodicTick([this]   
                                         { streamTick(); },
                                         sd::SAMPLE_RATE / 60u);
                }
            }

            ~EzSoundService() override 
            {
                if (Spu2Device *spu = m_host.spu2())
                {
                    spu->setPeriodicTick(nullptr, 0u);
                }
            }

            [[nodiscard]] std::string_view name() const override
            {
                return "ezsound";
            }

            [[nodiscard]] std::span<const uint32_t> sids() const override
            {
                return kSids;
            }

            void reset() override
            {
                std::lock_guard<std::mutex> lock(m_mutex);
                resetLocked();
            }

            void resetLocked()
            {  
                m_initialised = false;
                m_submissions = 0u;
                m_transMode = TransMode::Idle;
                m_backupCode = 0u;
                m_pauseMask = 0u;
                m_reply.fill(0u);
                m_request.fill(0u);
                m_work = {};
                m_cache = {};
                m_attrMode.fill(0u);
                m_reverbVolL = 0u;
                m_reverbVolR = 0u;
                m_targetReverbCore = 0u;
                m_keyCommand.fill(0);
            }

             [[nodiscard]] RpcResult handleRpc(const RpcRequest &request) override
            {
                if (request.sid != kEzSoundSid)
                {
                    return {};
                }

                RpcResult result;
                result.handled = true;
                result.resultAddress = request.receive.address;

                std::lock_guard<std::mutex> lock(m_mutex);
                Spu2Device *spu = m_host.spu2();
                if (request.function == kInitFunction)
                {
                    initialise(spu);
                }
                else if (request.function == kSubmitFunction)
                {
                    ++m_submissions;

                    if (request.send.address != 0u && spu)
                    {
                        submit(*spu, request.send);
                    }
                }
                else
                {
                    m_host.log(LogLevel::Warning,
                               "ezsound: unknown command " + std::to_string(request.function));
                 }

                if (request.receive.address != 0u && request.receive.size != 0u)
                {
                    (void)m_host.writeGuest(request.receive.address, m_reply.data(),
                                            std::min<uint32_t>(request.receive.size, kReplyBytes));
                }
                return result;
            }

            // One iteration of tVagStream2Play, from the audio clock.
            void streamTick()
            {
                std::lock_guard<std::mutex> lock(m_mutex);
                Spu2Device *spu = m_host.spu2();
                if (!spu || !m_initialised)
                {
                    return;
                }
                for (uint32_t i = 0; i < kStreamCount; ++i)
                {
                    StreamWork &w = m_work[i];
                    const StreamRequest s = streamRequest(i);
                    m_streamPause = (m_pauseMask & (1u << i)) != 0u;
                    if (w.state != 0)
                    {
                        streamSync(*spu, w, s);
                    }
                    else if (s.command != 0)
                    {
                        streamStart(*spu, w, s);
                        streamSync(*spu, w, s);
                    } 

                }
            }

             void appendDebugMetrics(std::vector<DebugMetric> &metrics) const override
            {
                metrics.push_back({"submissions", m_submissions, false});
                metrics.push_back({"transfer_code", m_backupCode, true});
                metrics.push_back({"trans_mode", static_cast<uint64_t>(m_transMode), false});
                uint32_t running = 0u;  

                for (const StreamWork &w : m_work)
                {
                    running += w.state == 3 ? 1u : 0u;
                }
                metrics.push_back({"streams_running", running, false});
            }

        private:
            void buildZeroBuffer()
            {
                m_zeroBuffer.fill(0u);
                for (uint32_t off = 0; off < 0x800u; off += 16u)
                {
                    wr32(m_zeroBuffer.data() + off, 0x00000200u);
                }
                m_zeroBuffer[0x001] = 6u;
                m_zeroBuffer[0x011] = 2u;

                m_zeroBuffer[0x7F1] = 3u;
            }

            void initialise(Spu2Device *spu)
            {
                resetLocked() ;
                m_initialised = true;
                if (!spu)
                {
                    return;
                }
                spu->init(0u);
                spu->setCoreAttr(sd::CORE_ATTR_SPDIF_MODE, 0u);
                for (uint32_t core = 0; core < kCoreCount; ++core)
                {

                    spu->setAddr(core | sd::A_EEA, 0x1FFFFFu - (core << 17)) ;
                     // mode 0x100: preset OFF and clear the work area.
                    spu->setEffectAttr(core, 0x100u, 0u, 0u, 0u, 0u);
                    spu->setCoreAttr(core | sd::CORE_ATTR_EFFECT_ENABLE, 1u);  
                    spu->setParam(core | sd::P_EVOLL, 0u);
                     spu->setParam(core | sd::P_EVOLR, 0u);
                    spu->setParam(core | sd::P_MVOLL, 0x3FFFu);
                    spu->setParam(core | sd::P_MVOLR, 0x3FFFu);
                }
            }

            StreamRequest streamRequest(uint32_t index) const
            {
                const uint8_t *p = m_request.data() + kReqStream + index * kReqStreamStride;
                 StreamRequest s;
                s.ringBase = rd32(p + 0x00);
                s.ringSize = rd32(p + 0x04);
                s.spuAddr = rd32(p + 0x08); 
                s.core = rd16(p + 0x0C) & 1u;
                s.voice = rd16(p + 0x0E);
                s.pitch = rd16(p + 0x10);

                s.volL = rd16(p + 0x12);
                s.volR = rd16(p + 0x14); 
                s.command = static_cast<int16_t>(rd16(p + 0x16));
                return s;
            }

            void submit(Spu2Device &spu, const GuestBuffer &send)

            {
                std::array<uint8_t, kRequestBytes> incoming{};
                const uint32_t bytes = std::min<uint32_t>(send.size, kRequestBytes);
                if(!m_host.readGuest(send.address, incoming.data(), bytes))
                {
                    return;
                }
                std::memcpy(m_request.data(), incoming.data(), bytes);
                uint8_t *req = m_request.data();

                for (uint32_t i = 0; i < kStreamCount; ++i)
                {
                    const StreamWork &w = m_work[i];
                    m_keyCommand[i] = (w.keyCmd != w.keyAck) ? w.keyCmd : 0;
                }
                m_pauseMask = ~rd32(req + kReqStreamPauseMask);

                for (uint32_t i = 0; i < kStreamCount; ++i)
                {
                    const StreamRequest s = streamRequest(i);
                    uint8_t *ctl = req + kReqCoreCtl + s.core * kReqCoreCtlStride;
                    if (m_keyCommand[i] == 2)
                    {
                        wr32(ctl + 0x04, rd32(ctl + 0x04) | (1u << (s.voice & 31u)));

                    }
                    else if (m_keyCommand[i] == 1)
                     { 
                        const uint32_t e = sd::voiceEntry(s.core, s.voice);
                        spu.setParam(e | sd::VP_VOLL, s.volL);
                        spu.setParam(e | sd::VP_VOLR, s.volR);
                        spu.setParam(e | sd::VP_PITCH, s.pitch);
                        spu.setParam(e | sd::VP_ADSR1, 0x000Fu);
                        spu.setParam(e | sd::VP_ADSR2, 0x1FC0u);
                        spu.setAddr(e | sd::VA_SSA, s.spuAddr);
                        wr32(ctl + 0x00, rd32(ctl + 0x00) | (1u << (s.voice & 31u)));
                    }
                }

                for (uint32_t core = 0; core < kCoreCount; ++core)
                {
                    const uint32_t keyOff = rd32(req + kReqCoreCtl + core * kReqCoreCtlStride + 0x04);
                    if (keyOff != 0u)
                    {
                        spu.setSwitch(core | sd::S_KOFF, keyOff);
                    }
                }

                const uint32_t batchCount = rd32(req + kReqBatchCount);
                if (batchCount != 0u)
                {

                    const uint32_t maxEntries = (kRequestBytes - kReqBatch) / sizeof(Spu2Batch);
                    const uint32_t count = std::min(batchCount, maxEntries);
                    std::vector<Spu2Batch> batch(count);
                    std::memcpy(batch.data(), req + kReqBatch, count * sizeof(Spu2Batch));
                    (void)spu.procBatch(batch.data(), count, nullptr, kBatchVoiceMask);
                    if (m_trace)
                    {
                        traceBatch(batch);
                    }
                }

                for (uint32_t core = 0; core < kCoreCount; ++core)
                {
                    const uint8_t *ctl = req + kReqCoreCtl + core * kReqCoreCtlStride;
                    CoreCache &c = m_cache[core];
                    const uint32_t vmixL = rd32(ctl + 0x08);
                    const uint32_t vmixR = rd32(ctl + 0x0C);
                    const uint32_t vmixEL = rd32(ctl + 0x10);   
                    const uint32_t vmixER = rd32(ctl + 0x14);
                    if (c.vmixL != vmixL)
                    {
                        c.vmixL = vmixL;
                        spu.setSwitch(core | sd::S_VMIXL, vmixL);
                    }
                    if (c.vmixR != vmixR)
                    {
                        c.vmixR = vmixR;
                        spu.setSwitch(core | sd::S_VMIXR, vmixR);
                    }
                    if (c.vmixEL != vmixEL)
                    {
                        c.vmixEL = vmixEL;
                        spu.setSwitch(core | sd::S_VMIXEL, vmixEL);
                    }
                    if(c.vmixER != vmixER)
                    {
                        c.vmixER = vmixER;
                        spu.setSwitch(core | sd::S_VMIXER, vmixER);
                    }
                     const uint32_t keyOn = rd32(ctl + 0x00);
                    if (keyOn != 0u)
                    {
                        spu.setSwitch(core | sd::S_KON, keyOn);
                    }
                }

                for (uint32_t i = 0; i < kStreamCount; ++i)
                {
                    if (m_keyCommand[i] != 0)
                    {
                        m_work[i].keyAck = m_keyCommand[i];
                    }
                }

                stepTransfer(spu);
                buildReply(spu); 
            }

            void traceBatch(const std::vector<Spu2Batch> &batch)
            {
                static uint32_t printed = 0u;
                if (printed >= 64u)
                { 
                    return;
                }
                ++printed;
                std::cerr << "[ezsound] batch " << batch.size() << " entries:";

                for(size_t i = 0; i < batch.size() && i < 12u; ++i)
                {
                    std::cerr << " {" << std::hex << batch[i].func << "," << batch[i].entry << "," << batch[i].value << std::dec << "}";
                }
                std::cerr << std::endl;
            }


            void stepTransfer(Spu2Device &spu) 
            {
                uint8_t *req = m_request.data();
                switch (m_transMode)

                {
                case TransMode::Idle:
                {
                    const uint32_t code = rd32(req + kReqTransferCode);
                    if (code == rd32(m_reply.data() + kReplyCode))
                    {
                        break;
                    }
                    if (spu.voiceTransStatus(0u, 0u) == 0u)
                    {
                        break;
                    }
                    m_backupCode = code;
                    const uint32_t size = rd32(req + kReqSize);
                    if (size != 0u && size != 1u)
                    {

                        m_transMode = TransMode::StartUpload;
                        startUpload(spu);
                        break;
                    }
                    const uint32_t core = size;
                    uint8_t *fx = req + kReqEffect + core * kReqEffectStride;
                    const uint32_t mode = rd32(fx + 0x04);
                    const uint16_t depthL =  rd16(fx + 0x08);
                    const uint16_t depthR = rd16(fx + 0x0A);
                    if (m_attrMode[core] != mode)
                    {
                        m_attrMode[core] = mode;
                        m_targetReverbCore = core;
                        m_reverbVolL = depthL;
                        m_reverbVolR = depthR;
                        spu.setParam(core | sd::P_EVOLL, 0u);
                        spu.setParam(core | sd::P_EVOLR, 0u);
                        spu.setEffectAttr(core, mode, 0u, 0u, rd32(fx + 0x0C), rd32(fx + 0x10));
                        if (mode == 0u) // AttrMode == 0 at 0x1534: OFF needs no clear

                        {
                            wr32(m_reply.data() + kReplyCode, m_backupCode) ;
                            break;

                        }
                        m_transMode = TransMode::ClearReverb;
                    }   
                    else
                    {
                        spu.setParam(core | sd::P_EVOLL, depthL);
                        spu.setParam(core | sd::P_EVOLR, depthR);
                        wr32(m_reply.data() + kReplyCode, m_backupCode);
                    }
                    break;
                }
                case TransMode::StartUpload:   
                    startUpload(spu) ;

                    break;
                case TransMode::WaitUpload:
                    if (spu.voiceTransStatus(0u, 0u) == 0u)
                    {
                        break;
                    }
                    wr32(m_reply.data() + kReplyCode, m_backupCode); 
                    m_transMode = TransMode::Idle;
                    break;
                case TransMode::ClearReverb:
                    spu.clearEffectWorkArea(m_targetReverbCore, m_attrMode[m_targetReverbCore]);
                    m_transMode = TransMode::WaitClear;
                    break;
                case TransMode::WaitClear:
                    spu.setParam(m_targetReverbCore | sd::P_EVOLL, m_reverbVolL);
                     spu.setParam(m_targetReverbCore | sd::P_EVOLR, m_reverbVolR);
                    wr32(m_reply.data() + kReplyCode, m_backupCode);
                    m_transMode = TransMode::Idle; 
                    break;
                }
            }

            void startUpload(Spu2Device &spu)   
            {
                const uint8_t *req = m_request.data();
                const uint32_t iopAddr = rd32(req + kReqIopAddress);
                const uint32_t spuAddr = rd32(req + kReqSpuAddress);
                const uint32_t size = rd32(req + kReqSize);
                const uint32_t moved = spu.voiceTrans(0u, 0u, iopAddr, spuAddr, size);
                if (m_trace)
                {
                     std::cerr << "[ezsound] upload iop=0x" << std::hex << iopAddr << " spu=0x" << spuAddr 
                              << " size=0x" << size << " moved=0x" << moved << std::dec << std::endl;
                }
                m_transMode = TransMode::WaitUpload;
            }

             void buildReply(Spu2Device &spu)
            {
                uint8_t *rep = m_reply.data();
                wr16(rep + kReplyMainVolL, static_cast<uint16_t>(spu.getParam(sd::P_MVOLXL)));
                wr16(rep + kReplyMainVolR, static_cast<uint16_t>(spu.getParam(sd::P_MVOLXR)));
                for (uint32_t core = 0; core < kCoreCount; ++core)
                {
                     for (uint32_t v = 0; v < kVoiceCount; ++v)
                    {
                        const uint16_t env = static_cast<uint16_t>(spu.getParam(sd::voiceEntry(core, v) | sd::VP_ENVX));
                        wr16(rep + kReplyEnvelope + core * kVoiceCount * 2u + v * 2u, env); 
                    }
                }
                for (uint32_t i = 0; i < kStreamCount; ++i)
                {
                    uint8_t *st = rep + kReplyStreamStatus + i * kReplyStreamStride;
                    StreamWork &w = m_work[i];
                    wr32(st + 0x04, w.bytesThisFrame);
                    wr32(st + 0x08, rd32(st + 0x08) + w.bytesThisFrame);
                    wr16(st + 0x02, w.status);
                    w.bytesThisFrame = 0u ; 
                }   
            }

            void streamStart(Spu2Device &spu, StreamWork &w, const StreamRequest &s)
            {
                if (s.command != 1 && s.command != 2)
                {
                    return;
                }
                w.spuA = s.spuAddr;
                w.spuB = s.spuAddr + kStreamHalfBytes;
                w.ringBase = s.ringBase;

                w.ringEnd = s.ringBase + s.ringSize;
                w.readPtr = s.ringBase; 
                w.bytesThisFrame = 0u;
                w.bytesTotal = 0u;
                w.half = 2;
                w.state = 1;  
                w.voiceEntry = sd::voiceEntry(s.core, s.voice);
                w.keyCmd = 0;
                w.keyAck = 0;
                if (m_trace)   
                {
                    std::cerr << "[ezsound] stream start ring=0x" << std::hex << s.ringBase << "+0x" << s.ringSize
                              << " spu=0x" << s.spuAddr << " core=" << s.core << " voice=" << std::dec << s.voice 
                              << " pitch=0x" << std::hex << s.pitch << " vol=" << s.volL << "/" << s.volR
                              << " cmd=" << std::dec << s.command << std::endl;
                }  
                streamTransfer(spu, w);
             }

            void streamSync(Spu2Device &spu, StreamWork &w, const StreamRequest &s)
            {
                switch (w.state)
                {
                case 1:
                    if (s.command == 2)
                    {
                        w.keyCmd = 1;

                        w.state = 2;
                    }
                    else if (s.command == 3)   
                    {
                        w.state = 0;
                    }
                    break;
                case 2:
                    if (w.keyCmd == w.keyAck)
                    {
                        w.state = 3;
                    }
                    break;
                case 3:
                    if (s.command == 3)
                    {

                        w.keyCmd = 2;
                        w.state = 4;
                        m_streamPause =  true;

                    }

                    streamTransfer(spu, w);
                    break;
                case 4:
                    if (w.keyCmd == w.keyAck)
                    {
                        w.state = 0;
                    }
                    m_streamPause = true;
                    streamTransfer(spu, w);
                    break;
                default:
                    break;
                }
            }

            void streamTransfer(Spu2Device &spu, StreamWork &w)
            {
                const uint32_t nax = spu.getAddr(w.voiceEntry | sd::VA_NAX);
                if (w.half == 0)
                {
                    if (!(w.spuB < nax))
                    {
                        return;
                    }
                }
                else if (w.half == 1)
                {
                    if(w.spuB < nax || nax == w.spuA)
                    {
                        return;
                    }
                 }

                bool haveData = false; 
                if (!m_streamPause)
                {
                    uint32_t marker = 0xFFFFFFFFu;
                    (void)m_host.readGuest(w.readPtr + kStreamBlockMarker, &marker, sizeof(marker));
                    haveData = marker != 0xFFFFFFFFu;
                    w.status = haveData ? 0u : 2u;
                }   
                else
                {
                    w.status = 1u;
                }

                uint32_t len = kStreamHalfBytes;
                if (haveData)
                {
                    std::array<uint8_t, 0x800> data{};
                    const uint32_t want = (w.half == 2) ? 0x800u : kStreamHalfBytes;   
                    if (!m_host.readGuest(w.readPtr, data.data(), want))
                    {
                        haveData = false;
                        w.status = 2u; 
                    }
                    else
                    {
                        switch (w.half)
                        {
                        case 0:
                            data[0x001] = 6u;
                            data[0x011] = 2u;
                            data[0x3F1] = 0u;
                            break;
                        case 1:
                            data[0x001] = 0u ;
                            data[0x011] = 0u;
                            data[0x3F1] = 3u ;
                            break;
                        default:
                            data[0x001] = 6u;
                            data[0x011] = 2u;
                            data[0x3F1] = 0u;
                            data[0x401] = 0u;
                            data[0x411] = 0u;
                             data[0x7F1] = 3u;
                            w.half = 0;
                            break;

                         }
                        len = want;
                        (void)m_host.writeGuest(w.readPtr, data.data(), want);
                        const uint32_t dst = (w.half == 0) ? w.spuA : w.spuB;
                        (void)spu.writeRam(dst, data.data(), len);
                    }
                }
                if (!haveData)
                {
                    const uint8_t *src = m_zeroBuffer.data();
                    switch (w.half)
                    {
                    case 0:
                        len =  kStreamHalfBytes;
                        break;
                    case 1:
                        src += kStreamHalfBytes;
                        len = kStreamHalfBytes;
                        break;
                    default: 
                        len = 0x800u;
                        w.half = 0;
                         break;
                    }
                    const uint32_t dst = (w.half == 0) ? w.spuA : w.spuB;
                    (void)spu.writeRam(dst, src, len);
                }

                if (m_trace && m_streamTraceCount < 400u)
                {
                    ++m_streamTraceCount;
                    std::cerr << "[ezsound] refill voice=0x" << std::hex << w.voiceEntry << " nax=0x" << nax
                              << " half=" << std::dec << w.half << " data=" << (haveData ? 1 : 0)
                              << " len=0x" << std::hex << len << " readPtr=0x" << w.readPtr
                              << " status=" << std::dec << w.status << " state=" << w.state << std::endl;
                }

                if (len < 0x800u)
                {
                    w.half = static_cast<int16_t>((w.half + 1) & 1);
                }

                if (haveData)
                {
                    const uint32_t consumed = 0xFFFFFFFFu ;

                    (void)m_host.writeGuest(w.readPtr + kStreamBlockMarker, &consumed, sizeof(consumed));
                    w.bytesThisFrame += len;
                    w.bytesTotal += len;
                    w.readPtr += len;
                    if (w.readPtr >= w.ringEnd)
                    {
                        w.readPtr = w.ringBase;
                    }
                }
            }

            inline static constexpr std::array<uint32_t, 1> kSids{kEzSoundSid};

            IopHost &m_host;
            std::mutex m_mutex;
            bool m_initialised = false;
            bool m_trace = false;
            uint64_t m_submissions = 0u;
            TransMode m_transMode = TransMode::Idle;
            uint32_t m_backupCode = 0u;

            uint32_t m_pauseMask = 0u;
            bool m_streamPause = false;
            std::array<uint8_t, kRequestBytes> m_request{};
            std::array<uint8_t, kReplyBytes> m_reply{};
            std::array<uint8_t, 0x800> m_zeroBuffer{};
            std::array<StreamWork, kStreamCount> m_work{};
            std::array<int16_t, kStreamCount> m_keyCommand{};
            std::array<CoreCache, kCoreCount> m_cache{};
            std::array<uint32_t, kCoreCount> m_attrMode{};
            uint32_t m_reverbVolL = 0u;
            uint32_t m_reverbVolR = 0u;
            uint32_t m_targetReverbCore = 0u;
            uint32_t m_streamTraceCount = 0u;
        };
    }

    std::unique_ptr<IopService> createEzSoundService(IopHost &host)
    {
        return std::make_unique<EzSoundService>(host);
    }
}
