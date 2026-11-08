#include "ps2_vdisc_mods.h"

#if !__has_include("ps2_mods.h")
#include <iostream>

namespace ps2_mods
{
    std::vector<std::filesystem::path> modDirectories() { return {}; }


    void log(const std::string &line) { std::cerr << line << std::endl; }
}
#endif
