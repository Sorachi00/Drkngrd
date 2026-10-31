// Based on Blackline Interactive implementation
#include "runtime/ps2_memory.h"
#include <cstring>

enum VIFCmd : uint8_t
{
    VIF_NOP = 0x00,
    VIF_STCYCL = 0x01,
    VIF_OFFSET = 0x02,
    VIF_BASE = 0x03,
    VIF_ITOP = 0x04,
    VIF_STMOD = 0x05,
    VIF_MSKPATH3 = 0x06,
    VIF_MARK = 0x07,
    VIF_FLUSHE = 0x10,
    VIF_FLUSH = 0x11,
    VIF_FLUSHA = 0x13,
    VIF_MSCAL = 0x14,
    VIF_MSCALF = 0x15,
    VIF_MSCNT = 0x17,
    VIF_STMASK = 0x20,
    VIF_STROW = 0x30,
    VIF_STCOL = 0x31,
    VIF_MPG = 0x4A,
    VIF_DIRECT = 0x50,
    VIF_DIRECTHL = 0x51,
};

namespace
{
    constexpr uint8_t kGifFmtImage = 2u;

    // Qwords the last GIFtag's IMAGE packet still needs after these qw qwords (0 if none).
    uint32_t gifImageRunOver(const uint8_t *data, uint32_t qw)
    {
        uint32_t at = 0u;
        while (at < qw)
        {
            uint64_t tagLo = 0u;
            std::memcpy(&tagLo, data + at * 16u, sizeof(tagLo));
            ++at;
            const uint32_t nloop = static_cast<uint32_t>(tagLo & 0x7FFFu);
            const uint32_t flg = static_cast<uint32_t>((tagLo >> 58) & 0x3u);
            uint32_t nreg = static_cast<uint32_t>((tagLo >> 60) & 0xFu);
            if (nreg == 0u)
                nreg = 16u;
            const uint32_t size = flg == 0u ? nloop * nreg : flg == 1u ? (nloop * nreg + 1u) / 2u : nloop;
            if (at + size > qw)
                return flg >= kGifFmtImage ? at + size - qw : 0u;
            at += size;
        }
        return 0u;
    }
}

void PS2Memory::processVIF0Data(uint32_t srcPhys, uint32_t sizeBytes)
{
    if (sizeBytes == 0u || srcPhys >= PS2_RAM_SIZE)
        return;

    const uint64_t requestedEnd = static_cast<uint64_t>(srcPhys) + static_cast<uint64_t>(sizeBytes);
    if (requestedEnd > static_cast<uint64_t>(PS2_RAM_SIZE))
        sizeBytes = PS2_RAM_SIZE - srcPhys;

    processVIF0Data(m_rdram + srcPhys, sizeBytes);
}

void PS2Memory::processVIF0Data(const uint8_t *data, uint32_t sizeBytes)
{
    if (sizeBytes)
        m_vif0Stream.insert(m_vif0Stream.end(), data, data + sizeBytes);
    if (m_vif0Stream.empty() || m_vifStalled[0])
        return;
    const uint32_t consumed = parseVIF0Stream(m_vif0Stream.data(), static_cast<uint32_t>(m_vif0Stream.size()));
    m_vif0Stream.erase(m_vif0Stream.begin(), m_vif0Stream.begin() + consumed);
}

// I bit: INTC 4/5 after the code; all but MARK then stall until FBRST.STC (real PS2: dma/vif/intstall).
bool PS2Memory::vifInterrupt(int unit, uint8_t opcode)
{
    VIFRegisters &regs = unit ? vif1_regs : vif0_regs;
    regs.stat |= (1u << 11); // INT
    queueCompletedDmacCause(0x100u | (unit ? 5u : 4u));
    if (opcode == VIF_MARK)
        return false;
    regs.stat |= (1u << 10); // VIS
    m_vifStalled[unit] = true;
    return true;
}

uint32_t PS2Memory::parseVIF0Stream(const uint8_t *data, uint32_t sizeBytes)
{
    uint32_t pos = 0;
    bool irqArmed = false;
    uint8_t irqOpcode = 0u;
    while (pos + 4 <= sizeBytes)
    {
        if (irqArmed)
        {
            irqArmed = false;
            if (vifInterrupt(0, irqOpcode))
                return pos;
        }
        const uint32_t cmdStart = pos;
        uint32_t cmd = 0u;
        std::memcpy(&cmd, data + pos, sizeof(cmd));
        pos += 4u;

        const uint8_t opcode = static_cast<uint8_t>((cmd >> 24) & 0x7Fu);
        const uint16_t imm = static_cast<uint16_t>(cmd & 0xFFFFu);
        const uint8_t num = static_cast<uint8_t>((cmd >> 16) & 0xFFu);
        const bool irq = (cmd & 0x80000000u) != 0u;

        vif0_regs.code = cmd;
        vif0_regs.num = 0u;
        // ERR.MII masks the I bit (PCSX2 Vif_Transfer.cpp vifTransferLoop).
        irqArmed = irq && !(vif0_regs.err & 1u);
        irqOpcode = opcode;

        if (opcode == VIF_NOP)
        {
            continue;
        }
        else if (opcode == VIF_STCYCL)
        {
            vif0_regs.cycle = imm;
            continue;
        }
        else if (opcode == VIF_ITOP)
        {
            vif0_regs.itops = imm & 0x3FFu;
            continue;
        }
        else if (opcode == VIF_STMOD)
        {
            vif0_regs.mode = imm & 3u;
            continue;
        }
        else if (opcode == VIF_MARK)
        {
            vif0_regs.mark = imm;
            vif0_regs.stat |= (1u << 6);
            continue;
        }
        else if (opcode == VIF_FLUSHE || opcode == VIF_FLUSH || opcode == VIF_FLUSHA)
        {
            continue;
        }
        else if (opcode == VIF_MSCAL || opcode == VIF_MSCALF || opcode == VIF_MSCNT)
        {
            if (m_vu0MscalCallback)
                m_vu0MscalCallback((imm & 0x1FFu) * 8u, opcode == VIF_MSCNT);
            continue;
        }
        else if (opcode == VIF_STMASK)
        {
            if (pos + 4u > sizeBytes)
                return cmdStart;
            std::memcpy(&vif0_regs.mask, data + pos, sizeof(vif0_regs.mask));
            pos += 4u;
            continue;
        }
        else if (opcode == VIF_STROW)
        {
            if (pos + 16u > sizeBytes)
                return cmdStart;
            std::memcpy(vif0_regs.row, data + pos, 16u);
            pos += 16u;
            continue;
        }
        else if (opcode == VIF_OFFSET || opcode == VIF_BASE || opcode == VIF_MSKPATH3)
        {
            continue; // VIF1-only codes; no effect on VIF0 (ps2tek "VIF Commands")
        }
        else if (opcode == VIF_STCOL)
        {
            if (pos + 16u > sizeBytes)
                return cmdStart;
            std::memcpy(vif0_regs.col, data + pos, 16u);
            pos += 16u;
            continue;
        }
        else if (opcode == VIF_MPG)
        {
            const uint32_t destAddr = static_cast<uint32_t>(imm & 0x1FFu) * 8u;
            const uint32_t instructionCount = (num == 0u) ? 256u : static_cast<uint32_t>(num);
            const uint32_t mpgBytes = instructionCount * 8u;
            if (pos + mpgBytes > sizeBytes)
            {
                vif0_regs.num = num;
                return cmdStart;
            }
            // Wrap at the end of the 4 KB code memory (PCSX2 Vif_Codes.cpp:338-351).
            if (m_vu0Code && mpgBytes > 0u)
            {
                const uint32_t first = std::min(mpgBytes, PS2_VU0_CODE_SIZE - destAddr);
                std::memcpy(m_vu0Code + destAddr, data + pos, first);
                if (mpgBytes > first)
                    std::memcpy(m_vu0Code, data + pos + first, std::min(mpgBytes - first, PS2_VU0_CODE_SIZE));
                markVU0CodeModified();
            }

            pos += mpgBytes;
            if (pos > sizeBytes)
                break;
            continue;
        }
        else if ((opcode & 0x60u) == 0x60u)
        {
            const uint8_t vn = static_cast<uint8_t>((opcode >> 2) & 0x3u);
            const uint8_t vl = static_cast<uint8_t>(opcode & 0x3u);
            const int components = static_cast<int>(vn) + 1;
            int bitsPerComponent = 32;
            switch (vl)
            {
            case 0:
                bitsPerComponent = 32;
                break;
            case 1:
                bitsPerComponent = 16;
                break;
            case 2:
                bitsPerComponent = 8;
                break;
            case 3:
                bitsPerComponent = (vn == 3u) ? 4 : 16;
                break;
            default:
                break;
            }
            const int bitsPerVector = (vl == 3u && vn == 3u) ? 16 : (components * bitsPerComponent);
            uint32_t bytesPerVector = static_cast<uint32_t>((bitsPerVector + 7) / 8);
            const uint32_t writeVectorCount = (num == 0u) ? 256u : static_cast<uint32_t>(num);
            uint32_t cl = vif0_regs.cycle & 0xFFu;
            uint32_t wl = (vif0_regs.cycle >> 8) & 0xFFu;
            if (wl == 0u)
                wl = 256u; // WL=0 means 256; CL=0 is a fill-only cycle (PCSX2 Vif_Unpack.cpp:221)
            uint32_t sourceVectorCount = writeVectorCount;
            if (cl < wl)
            {
                const uint32_t fullBlocks = writeVectorCount / wl;
                uint32_t remainder = writeVectorCount % wl;
                if (remainder > cl)
                    remainder = cl;
                sourceVectorCount = fullBlocks * cl + remainder;
            }
            uint32_t totalBytes = sourceVectorCount * bytesPerVector;
            totalBytes = (totalBytes + 3u) & ~3u;

            if (pos + totalBytes > sizeBytes)
            {
                // Waits for data; 8-bit VIF0 NUM reads 256 as 0 (real PS2: dma/vif/unpack).
                vif0_regs.num = num;
                return cmdStart;
            }
            if (m_vu0Data && (vl <= 2u || vn == 3u))
            {
                // VU0 data is 256 quadwords (PCSX2 Vif_Unpack.cpp:235 addr & 0xff0).
                uint32_t vuAddr = static_cast<uint32_t>(imm & 0xFFu);
                if ((imm & 0x8000u) != 0u)
                    vuAddr = (vuAddr + (vif0_regs.tops & 0x3FFu)) & 0xFFu;
                const bool zeroExtend = (imm & 0x4000u) != 0u;
                const bool maskEnable = (opcode & 0x10u) != 0u;
                const uint8_t *srcBase = data + pos;
                uint32_t srcIndex = 0u;
                for (uint32_t writeIndex = 0; writeIndex < writeVectorCount; ++writeIndex)
                {
                    const uint32_t cyclePos = writeIndex % wl;
                    const bool sourceAvailable = (cl >= wl) || (cyclePos < cl);
                    uint32_t destVec = (cl >= wl) ? ((vuAddr + (writeIndex / wl) * cl + cyclePos) & 0xFFu)
                                                  : ((vuAddr + writeIndex) & 0xFFu);
                    const uint32_t destOff = destVec * 16u;
                    if (destOff + 16u > PS2_VU0_DATA_SIZE)
                    {
                        if (sourceAvailable && srcIndex < sourceVectorCount)
                            ++srcIndex;
                        continue;
                    }
                    // Fill writes read no data; data lanes take ROW (real PS2: dma/vif/stcycl).
                    const bool hasSource = sourceAvailable && srcIndex < sourceVectorCount;
                    const uint8_t *srcVec = hasSource ? srcBase + srcIndex * bytesPerVector : nullptr;
                    if (hasSource)
                        ++srcIndex;
                    uint32_t lanes[4] = {0u, 0u, 0u, 0u};
                    std::memcpy(lanes, m_vu0Data + destOff, sizeof(lanes));
                    const uint32_t limit = (components > 4) ? 4u : static_cast<uint32_t>(components);
                    uint32_t decoded[4] = {};
                    if (hasSource && vl == 3u)
                    {
                        // V4-5: RGBA 5-5-5-1, each field scaled to 8 bits (PCSX2 Vif_Unpack.cpp:103-106).
                        uint16_t packed;
                        std::memcpy(&packed, srcVec, sizeof(packed));
                        decoded[0] = (packed & 0x1Fu) << 3;
                        decoded[1] = ((packed >> 5) & 0x1Fu) << 3;
                        decoded[2] = ((packed >> 10) & 0x1Fu) << 3;
                        decoded[3] = ((packed >> 15) & 1u) << 7;
                    }
                    for (uint32_t c = 0; hasSource && vl != 3u && c < limit; ++c)
                    {
                        if (vl == 0u)
                            std::memcpy(&decoded[c], srcVec + c * 4u, 4u);
                        else if (vl == 1u)
                        {
                            uint16_t raw;
                            std::memcpy(&raw, srcVec + c * 2u, 2u);
                            decoded[c] = zeroExtend ? raw : static_cast<uint32_t>(static_cast<int16_t>(raw));
                        }
                        else
                            decoded[c] = zeroExtend ? srcVec[c] : static_cast<uint32_t>(static_cast<int8_t>(srcVec[c]));
                    }
                    uint32_t writeLimit = limit;
                    if (hasSource && vl != 3u && (vn == 1u || vn == 2u))
                    {
                        // V2 writes X,Y,X,Y; V3 writes W from the next component (real PS2: dma/vif/unpack).
                        if (vn == 1u)
                        {
                            decoded[2] = decoded[0];
                            decoded[3] = decoded[1];
                        }
                        else
                        {
                            const uint32_t size = 4u >> vl;
                            const uint8_t *w = srcVec + 3u * size;
                            decoded[3] = 0u;
                            if (w + size <= data + sizeBytes)
                            {
                                if (vl == 0u)
                                    std::memcpy(&decoded[3], w, 4u);
                                else if (vl == 1u)
                                {
                                    uint16_t raw;
                                    std::memcpy(&raw, w, 2u);
                                    decoded[3] = zeroExtend ? raw : static_cast<uint32_t>(static_cast<int16_t>(raw));
                                }
                                else
                                    decoded[3] = zeroExtend ? *w : static_cast<uint32_t>(static_cast<int8_t>(*w));
                            }
                        }
                        writeLimit = 4u;
                    }
                    const uint32_t cycle = std::min(cyclePos, 3u);
                    for (uint32_t c = 0; c < 4u; ++c)
                    {
                        uint32_t mask = maskEnable ? (vif0_regs.mask >> ((cycle * 4u + c) * 2u)) & 3u : 0u;
                        if (!hasSource && mask == 0u)
                            mask = 1u;
                        if (mask == 1u)
                            lanes[c] = vif0_regs.row[c];
                        else if (mask == 2u)
                            lanes[c] = vif0_regs.col[cycle];
                        else if (mask == 0u && (c < writeLimit || limit == 1u))
                        {
                            lanes[c] = decoded[limit == 1u ? 0u : c];
                            if (vl != 3u && (vif0_regs.mode == 1u || vif0_regs.mode == 2u))
                            {
                                lanes[c] += vif0_regs.row[c];
                                if (vif0_regs.mode == 2u)
                                    vif0_regs.row[c] = lanes[c];
                            }
                            else if (vl != 3u && vif0_regs.mode == 3u)
                            {
                                vif0_regs.row[c] = lanes[c];
                            }
                        }
                    }
                    _mm_storeu_si128(reinterpret_cast<__m128i *>(m_vu0Data + destOff), _mm_loadu_si128(reinterpret_cast<const __m128i *>(lanes)));
                }
            }
            pos += totalBytes;
            if (pos > sizeBytes)
                break;
            continue;
        }
        else
        {
            break;
        }
    }
    if (irqArmed)
        vifInterrupt(0, irqOpcode);
    return pos;
}

void PS2Memory::processVIF1Data(uint32_t srcPhys, uint32_t sizeBytes)
{
    if (sizeBytes == 0u || srcPhys >= PS2_RAM_SIZE)
        return;

    const uint64_t requestedEnd = static_cast<uint64_t>(srcPhys) + static_cast<uint64_t>(sizeBytes);
    if (requestedEnd > static_cast<uint64_t>(PS2_RAM_SIZE))
        sizeBytes = PS2_RAM_SIZE - srcPhys;

    processVIF1Data(m_rdram + srcPhys, sizeBytes);
}

// A command split over two transfers waits for the rest of its data (real PS2: dma/vif/stcycl, basic).
void PS2Memory::processVIF1Data(const uint8_t *data, uint32_t sizeBytes)
{
    if (m_vif1Stream.empty() && !m_vifStalled[1])
    {
        if (sizeBytes == 0u)
            return;
        const uint32_t used = parseVIF1Stream(data, sizeBytes);
        if (used < sizeBytes)
            m_vif1Stream.assign(data + used, data + sizeBytes);
        return;
    }
    if (sizeBytes)
        m_vif1Stream.insert(m_vif1Stream.end(), data, data + sizeBytes);
    if (m_vifStalled[1] || m_vif1Stream.empty())
        return;
    std::vector<uint8_t> pending;
    pending.swap(m_vif1Stream);
    const uint32_t used = parseVIF1Stream(pending.data(), static_cast<uint32_t>(pending.size()));
    if (used < pending.size())
        m_vif1Stream.assign(pending.begin() + used, pending.end());
}

uint32_t PS2Memory::parseVIF1Stream(const uint8_t *data, uint32_t sizeBytes)
{
    uint32_t pos = 0;
    bool irqArmed = false;
    uint8_t irqOpcode = 0u;

    // An IMAGE packet stays open in the GIF over the next DIRECTs; its continued data gets its own tag.
    auto feedPath2 = [&](const uint8_t *p, uint32_t qw, bool directHl)
    {
        uint32_t imageLeft = m_vif1PendingPath2ImageQwc;
        while (qw != 0u)
        {
            if (imageLeft == 0u)
            {
                submitGifPacket(GifPathId::Path2, p, qw * 16u, true, directHl);
                imageLeft = gifImageRunOver(p, qw);
                break;
            }
            const uint32_t chunkQw = std::min<uint32_t>(imageLeft, qw);
            std::vector<uint8_t> imagePacket(16u + static_cast<size_t>(chunkQw) * 16u, 0u);
            const uint64_t imageTag =
                static_cast<uint64_t>(chunkQw & 0x7FFFu) |
                ((imageLeft == chunkQw) ? (1ull << 15) : 0ull) |
                (static_cast<uint64_t>(kGifFmtImage) << 58);
            std::memcpy(imagePacket.data(), &imageTag, sizeof(imageTag));
            std::memcpy(imagePacket.data() + 16u, p, static_cast<size_t>(chunkQw) * 16u);
            submitGifPacket(GifPathId::Path2, imagePacket.data(), static_cast<uint32_t>(imagePacket.size()), true, directHl);
            imageLeft -= chunkQw;
            p += chunkQw * 16u;
            qw -= chunkQw;
        }
        m_vif1PendingPath2ImageQwc = imageLeft;
    };

    while (pos + 4 <= sizeBytes)
    {
        if (irqArmed)
        {
            irqArmed = false;
            if (vifInterrupt(1, irqOpcode))
                return pos;
        }
        // DIRECT/DIRECTHL payload cut off by the end of the last transfer.
        if (const uint32_t directLeft = m_vif1PendingDirectQwc; directLeft != 0u)
        {
            const uint32_t availableQw = (sizeBytes - pos) / 16u;
            if (availableQw == 0u)
            {
                break;
            }
            const uint32_t chunkQw = std::min<uint32_t>(directLeft, availableQw);
            feedPath2(data + pos, chunkQw, m_vif1PendingPath2DirectHl);
            pos += chunkQw * 16u;
            m_vif1PendingDirectQwc = directLeft - chunkQw;
            continue;
        }

        const uint32_t cmdStart = pos;
        uint32_t cmd;
        memcpy(&cmd, data + pos, 4);
        pos += 4;

        uint8_t opcode = (cmd >> 24) & 0x7F;
        uint16_t imm = cmd & 0xFFFF;
        uint8_t num = (cmd >> 16) & 0xFF;
        const bool irq = (cmd & 0x80000000u) != 0u;

        // Track most-recent command for VIFn_CODE emulation.
        vif1_regs.code = cmd;
        vif1_regs.num = 0u;
        // ERR.MII masks the I bit (PCSX2 Vif_Transfer.cpp vifTransferLoop).
        irqArmed = irq && !(vif1_regs.err & 1u);
        irqOpcode = opcode;

        if (opcode == VIF_NOP)
        {
            continue;
        }
        else if (opcode == VIF_STCYCL)
        {
            vif1_regs.cycle = imm;
            continue;
        }
        else if (opcode == VIF_OFFSET)
        {
            // VIF double-buffer setup. OFFSET clears DBF and resets TOPS to BASE.
            // Do not rewrite BASE from the previous TOPS value.
            vif1_regs.ofst = imm & 0x3FFu;
            vif1_regs.tops = vif1_regs.base & 0x3FFu;
            vif1_regs.stat &= ~(1u << 7); // clear DBF
            continue;
        }
        else if (opcode == VIF_BASE)
        {
            // BASE only updates the base register. TOPS changes on OFFSET/MSCAL.
            vif1_regs.base = imm & 0x3FFu;
            continue;
        }
        else if (opcode == VIF_ITOP)
        {
            // ITOP VIFcode writes pending ITOPS; VU XITOP observes it after MSCAL/MSCNT.
            vif1_regs.itops = imm & 0x3FFu;
            continue;
        }
        else if (opcode == VIF_STMOD)
        {
            vif1_regs.mode = imm & 3u;
            continue;
        }
        else if (opcode == VIF_MSKPATH3)
        {
            // VIF command docs: MSKPATH3 uses IMMEDIATE bit 15.
            const bool wasMasked = m_path3Masked;
            m_path3Masked = (imm & 0x8000u) != 0u;
            if (wasMasked && !m_path3Masked)
                flushMaskedPath3Packets();
            continue;
        }
        else if (opcode == VIF_MARK)
        {
            vif1_regs.mark = imm;
            vif1_regs.stat |= (1u << 6); // MRK
            continue;
        }
        else if (opcode == VIF_FLUSHE || opcode == VIF_FLUSH || opcode == VIF_FLUSHA)
        {
            continue;
        }
        else if (opcode == VIF_MSCAL || opcode == VIF_MSCALF)
        {
            uint32_t startPC = (uint32_t)imm * 8u;

            // Values visible to the VU program for this MSCAL.
            // DobieStation semantics: ITOP = ITOPS; TOP = current TOPS;
            // then TOPS/DBF are prepared for the next buffer.
            const uint32_t runTop = vif1_regs.tops & 0x3FFu;
            const uint32_t runItop = vif1_regs.itops & 0x3FFu;
            vif1_regs.top = runTop;
            vif1_regs.itop = runItop;

            const bool dbf = (vif1_regs.stat & (1u << 7)) != 0u;
            if (dbf)
                vif1_regs.tops = vif1_regs.base & 0x3FFu;
            else
                vif1_regs.tops = (vif1_regs.base + vif1_regs.ofst) & 0x3FFu;
            vif1_regs.stat ^= (1u << 7); // toggle DBF

            if (m_vu1MscalCallback)
                m_vu1MscalCallback(startPC, runTop, runItop);
            continue;
        }
        else if (opcode == VIF_MSCNT)
        {
            const uint32_t runTop = vif1_regs.tops & 0x3FFu;
            const uint32_t runItop = vif1_regs.itops & 0x3FFu;
            vif1_regs.top = runTop;
            vif1_regs.itop = runItop;

            const bool dbf = (vif1_regs.stat & (1u << 7)) != 0u;
            if (dbf)
                vif1_regs.tops = vif1_regs.base & 0x3FFu;
            else
                vif1_regs.tops = (vif1_regs.base + vif1_regs.ofst) & 0x3FFu;
            vif1_regs.stat ^= (1u << 7); // toggle DBF

            if (m_vu1MscntCallback)
                m_vu1MscntCallback(runTop, runItop);
            continue;
        }
        else if (opcode == VIF_STMASK)
        {
            if (pos + 4 > sizeBytes)
                return cmdStart;
            uint32_t maskValue = 0;
            std::memcpy(&maskValue, data + pos, sizeof(maskValue));
            vif1_regs.mask = maskValue;
            pos += 4;
            continue;
        }
        else if (opcode == VIF_STROW)
        {
            if (pos + 16 > sizeBytes)
                return cmdStart;
            std::memcpy(vif1_regs.row, data + pos, 16);
            pos += 16;
            continue;
        }
        else if (opcode == VIF_STCOL)
        {
            if (pos + 16 > sizeBytes)
                return cmdStart;
            std::memcpy(vif1_regs.col, data + pos, 16);
            pos += 16;
            continue;
        }
        else if (opcode == VIF_MPG)
        {
            uint32_t destAddr = ((uint32_t)imm * 8u) & (PS2_VU1_CODE_SIZE - 1u); // PCSX2 Vif_Codes.cpp:375
            // VIF MPG semantics: NUM==0 means 256 instructions (2048 bytes).
            // MPG payload is instruction-packed and should not be QW-aligned.
            const uint32_t instructionCount = (num == 0u) ? 256u : static_cast<uint32_t>(num);
            const uint32_t mpgBytes = instructionCount * 8u;
            if (pos + mpgBytes > sizeBytes)
            {
                vif1_regs.num = instructionCount;
                return cmdStart;
            }
            if (m_vu1Code && mpgBytes > 0 && pos + mpgBytes <= sizeBytes)
            {
                // Wrap at the end of the 16 KB code memory (PCSX2 Vif_Codes.cpp:338-351).
                const uint32_t first = std::min(mpgBytes, PS2_VU1_CODE_SIZE - destAddr);
                std::memcpy(m_vu1Code + destAddr, data + pos, first);
                if (mpgBytes > first)
                    std::memcpy(m_vu1Code, data + pos + first, std::min(mpgBytes - first, PS2_VU1_CODE_SIZE));
                markVU1CodeModified();
            }
            pos += mpgBytes;
            if (pos > sizeBytes)
                break;
            continue;
        }
        else if (opcode == VIF_DIRECT || opcode == VIF_DIRECTHL)
        {
            const uint32_t qwCount = imm != 0u ? imm : 65536u;
            const uint32_t availableQw = (sizeBytes - pos) / 16u;
            if (availableQw == 0u)
            {
                return cmdStart; // waits for its data
            }
            const bool directHl = (opcode == VIF_DIRECTHL);
            const uint32_t chunkQw = std::min(qwCount, availableQw);
            feedPath2(data + pos, chunkQw, directHl);
            pos += chunkQw * 16u;
            if (chunkQw < qwCount)
            {
                // The rest of the payload comes with the next transfer.
                m_vif1PendingDirectQwc = qwCount - chunkQw;
                m_vif1PendingPath2DirectHl = directHl;
                pos = sizeBytes;
                break;
            }
            continue;
        }
        else if ((opcode & 0x60) == 0x60)
        {
            uint8_t vn = (opcode >> 2) & 0x3;
            uint8_t vl = opcode & 0x3;
            const bool maskEnable = (opcode & 0x10u) != 0u;
            int components = vn + 1;
            int bitsPerComponent = 32;
            switch (vl)
            {
            case 0:
                bitsPerComponent = 32;
                break;
            case 1:
                bitsPerComponent = 16;
                break;
            case 2:
                bitsPerComponent = 8;
                break;
            case 3:
                bitsPerComponent = (vn == 3) ? 4 : 16;
                break;
            default:
                break;
            }
            int bitsPerVector = (vl == 3 && vn == 3) ? 16 : (components * bitsPerComponent);
            uint32_t bytesPerVector = (bitsPerVector + 7) / 8;
            // UNPACK semantics: NUM is 8-bit and NUM==0 means 256 vectors (writes).
            const uint32_t writeVectorCount = (num == 0u) ? 256u : static_cast<uint32_t>(num);

            // STCYCL controls write cycles for UNPACK.
            uint32_t cl = vif1_regs.cycle & 0xFFu;
            uint32_t wl = (vif1_regs.cycle >> 8) & 0xFFu;
            if (wl == 0u)
                wl = 256u; // WL=0 means 256; CL=0 is a fill-only cycle (PCSX2 Vif_Unpack.cpp:221)

            uint32_t sourceVectorCount = writeVectorCount;
            if (cl < wl)
            {
                const uint32_t fullBlocks = writeVectorCount / wl;
                uint32_t remainder = writeVectorCount % wl;
                if (remainder > cl)
                    remainder = cl;
                sourceVectorCount = fullBlocks * cl + remainder;
            }

            uint32_t totalBytes = sourceVectorCount * bytesPerVector;
            totalBytes = (totalBytes + 3) & ~3u;

            uint32_t vuAddr = (uint32_t)imm & 0x3FFu;
            if ((imm & 0x8000u) != 0u)
                vuAddr = (vuAddr + (vif1_regs.tops & 0x3FFu)) & 0x3FFu;

            const bool zeroExtend = (imm & 0x4000u) != 0u;

            if (pos + totalBytes > sizeBytes)
            {
                // Waits for data; NUM = vectors left (real PS2: dma/vif/unpack).
                vif1_regs.num = writeVectorCount;
                return cmdStart;
            }

            // CL = 0 reads no data but still writes every vector (real PS2: dma/vif/stcycl).
            if (m_vu1Data)
            {
                const uint8_t *srcBase = data + pos;
                uint32_t srcIndex = 0u;
                for (uint32_t writeIndex = 0; writeIndex < writeVectorCount; ++writeIndex)
                {
                    const uint32_t cyclePos = writeIndex % wl;
                    const bool sourceAvailable = (cl >= wl) || (cyclePos < cl);

                    uint32_t destVec = 0;
                    if (cl >= wl)
                    {
                        destVec = (vuAddr + (writeIndex / wl) * cl + cyclePos) & 0x3FFu;
                    }
                    else
                    {
                        destVec = (vuAddr + writeIndex) & 0x3FFu;
                    }

                    uint32_t destOff = destVec * 16u;
                    if (destOff + 16u > PS2_VU1_DATA_SIZE)
                    {
                        if (sourceAvailable && srcIndex < sourceVectorCount)
                            ++srcIndex;
                        continue;
                    }

                    uint32_t lanes[4] = {0u, 0u, 0u, 0u};
                    std::memcpy(lanes, m_vu1Data + destOff, sizeof(lanes));
                    uint32_t decompressed[4] = {lanes[0], lanes[1], lanes[2], lanes[3]};
                    bool decoded = false;

                    const uint8_t *srcVec = nullptr;
                    if (sourceAvailable && srcIndex < sourceVectorCount)
                    {
                        srcVec = srcBase + srcIndex * bytesPerVector;
                        ++srcIndex;
                        decoded = true;
                    }

                    auto extend16 = [&](uint16_t raw) -> uint32_t
                    {
                        if (zeroExtend)
                            return static_cast<uint32_t>(raw);
                        return static_cast<uint32_t>(static_cast<int32_t>(static_cast<int16_t>(raw)));
                    };

                    auto extend8 = [&](uint8_t raw) -> uint32_t
                    {
                        if (zeroExtend)
                            return static_cast<uint32_t>(raw);
                        return static_cast<uint32_t>(static_cast<int32_t>(static_cast<int8_t>(raw)));
                    };

                    bool handledFormat = true;
                    if (!decoded)
                    {
                        handledFormat = false;
                    }
                    else if (vl == 0u)
                    {
                        if (components == 1)
                        {
                            uint32_t scalar = 0;
                            std::memcpy(&scalar, srcVec, sizeof(scalar));
                            decompressed[0] = scalar;
                            decompressed[1] = scalar;
                            decompressed[2] = scalar;
                            decompressed[3] = scalar;
                        }
                        else
                        {
                            const uint32_t limit = (components > 4) ? 4u : static_cast<uint32_t>(components);
                            for (uint32_t c = 0; c < limit; ++c)
                            {
                                uint32_t scalar = 0;
                                std::memcpy(&scalar, srcVec + c * 4u, sizeof(scalar));
                                decompressed[c] = scalar;
                            }
                        }
                    }
                    else if (vl == 1u)
                    {
                        if (components == 1)
                        {
                            uint16_t raw = 0;
                            std::memcpy(&raw, srcVec, sizeof(raw));
                            const uint32_t scalar = extend16(raw);
                            decompressed[0] = scalar;
                            decompressed[1] = scalar;
                            decompressed[2] = scalar;
                            decompressed[3] = scalar;
                        }
                        else
                        {
                            const uint32_t limit = (components > 4) ? 4u : static_cast<uint32_t>(components);
                            for (uint32_t c = 0; c < limit; ++c)
                            {
                                uint16_t raw = 0;
                                std::memcpy(&raw, srcVec + c * 2u, sizeof(raw));
                                decompressed[c] = extend16(raw);
                            }
                        }
                    }
                    else if (vl == 2u)
                    {
                        if (components == 1)
                        {
                            const uint32_t scalar = extend8(srcVec[0]);
                            decompressed[0] = scalar;
                            decompressed[1] = scalar;
                            decompressed[2] = scalar;
                            decompressed[3] = scalar;
                        }
                        else
                        {
                            const uint32_t limit = (components > 4) ? 4u : static_cast<uint32_t>(components);
                            for (uint32_t c = 0; c < limit; ++c)
                            {
                                decompressed[c] = extend8(srcVec[c]);
                            }
                        }
                    }
                    else if (vl == 3u && vn == 3u)
                    {
                        // V4-5: packed color-like format in a single 16-bit value.
                        uint16_t packed = 0;
                        std::memcpy(&packed, srcVec, sizeof(packed));
                        // Each field scaled to 8 bits (PCSX2 Vif_Unpack.cpp:103-106).
                        decompressed[0] = (packed & 0x1Fu) << 3;
                        decompressed[1] = ((packed >> 5) & 0x1Fu) << 3;
                        decompressed[2] = ((packed >> 10) & 0x1Fu) << 3;
                        decompressed[3] = ((packed >> 15) & 0x01u) << 7;
                    }
                    else
                    {
                        handledFormat = false;
                    }
                    if (handledFormat && vn == 1u && vl != 3u)
                    {
                        // V2 writes X,Y,X,Y (PCSX2 Vif_Unpack.cpp:74-75).
                        decompressed[2] = decompressed[0];
                        decompressed[3] = decompressed[1];
                    }
                    if (handledFormat && vn == 2u && vl != 3u)
                    {
                        // V3 writes W from the next component, 0 past the buffer (real PS2: dma/vif/unpack).
                        const uint32_t size = 4u >> vl;
                        const uint8_t *w = srcVec + 3u * size;
                        uint32_t value = 0u;
                        if (w + size <= data + sizeBytes)
                        {
                            if (vl == 0u)
                                std::memcpy(&value, w, 4u);
                            else if (vl == 1u)
                            {
                                uint16_t raw;
                                std::memcpy(&raw, w, 2u);
                                value = extend16(raw);
                            }
                            else
                                value = extend8(*w);
                        }
                        decompressed[3] = value;
                    }

                    // Unknown compressed format fallback: preserve legacy raw-copy behavior.
                    if (!handledFormat && decoded && !maskEnable && (vif1_regs.mode == 0u || vif1_regs.mode == 3u))
                    {
                        uint32_t copyBytes = (bytesPerVector < 16u) ? bytesPerVector : 16u;
                        std::memcpy(m_vu1Data + destOff, srcVec, copyBytes);
                        continue;
                    }

                    const bool canAdd = (vl != 3u || vn != 3u);
                    const uint32_t mode = vif1_regs.mode & 3u;
                    if (handledFormat && !maskEnable && (!canAdd || mode == 0u))
                    {
                        std::memcpy(m_vu1Data + destOff, decompressed, sizeof(decompressed));
                        continue;
                    }
                    const uint32_t colIdx = (cyclePos > 3u) ? 3u : cyclePos;
                    const uint32_t maskCycle = (cyclePos > 3u) ? 3u : cyclePos;

                    for (uint32_t field = 0u; field < 4u; ++field)
                    {
                        uint32_t maskSpec = 0u;
                        if (maskEnable)
                        {
                            const uint32_t shift = ((maskCycle * 4u) + field) * 2u;
                            maskSpec = (vif1_regs.mask >> shift) & 0x3u;
                        }

                        // In fill-write cycles with suspended source reads, treat raw-data selections as row-fill.
                        if (!decoded && maskSpec == 0u)
                            maskSpec = 1u;

                        uint32_t writeVal = lanes[field];
                        if (maskSpec == 0u)
                        {
                            if (handledFormat)
                            {
                                writeVal = decompressed[field];
                                if (canAdd && (mode == 1u || mode == 2u))
                                {
                                    writeVal = writeVal + vif1_regs.row[field];
                                    if (mode == 2u)
                                        vif1_regs.row[field] = writeVal;
                                }
                                else if (canAdd && mode == 3u)
                                {
                                    vif1_regs.row[field] = writeVal;
                                }
                            }
                        }
                        else if (maskSpec == 1u)
                        {
                            writeVal = vif1_regs.row[field];
                        }
                        else if (maskSpec == 2u)
                        {
                            writeVal = vif1_regs.col[colIdx];
                        }
                        else
                        {
                            continue; // write-protect
                        }

                        lanes[field] = writeVal;
                    }

                    std::memcpy(m_vu1Data + destOff, lanes, sizeof(lanes));
                }
            }
            pos += totalBytes;

            if (pos > sizeBytes)
                break;
            continue;
        }
        else
        {
            continue;
        }
    }
    if (irqArmed)
        vifInterrupt(1, irqOpcode);
    return pos;
}
