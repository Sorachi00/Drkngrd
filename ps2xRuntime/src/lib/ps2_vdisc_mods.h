#pragma once

// Data mods (D7) use the mod loader when the mods feature is built in.
#if __has_include("ps2_mods.h")
#include "ps2_mods.h"

#else
#include <filesystem>

#include <string>
#include <vector>

// Without the mods feature: no mod folders, log to stderr (ps2_vdisc_mods.cpp).
namespace ps2_mods
{
    std::vector<std::filesystem::path> modDirectories();
    void log(const std::string &line);
}
#endif
