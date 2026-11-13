#pragma once

#include "runtime/gs/gs_backend.h"

#include <cstdint>
#include <memory>

enum class GSRecordCmd : uint32_t
{
    End = 0,
    Vram,
    Submit,
    BeginTransfer,
    Upload,
    Flush,
    TextureFlush,
    Sync,
    Present,
    ClearFramebuffer,
    WriteVram,
    Reset,

};

inline constexpr char kGSRecordMagic[8] = {'G', 'S', 'R', 'E', 'C', '0', '0', '1'};

std::unique_ptr<GSRasterBackend> makeRecordingGsBackend(std::unique_ptr<GSRasterBackend> inner);

void requestGsRecording();
