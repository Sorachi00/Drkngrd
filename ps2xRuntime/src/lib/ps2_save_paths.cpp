#include "runtime/ps2_save_paths.h"
#include "games_database.h" 

#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <string>

#ifdef _WIN32
// Own file: windows.h and raylib define the same names.  
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#include <knownfolders.h>
#include <shlobj.h>
#endif

namespace
{
    // SLES_523.22 -> SLES-52322 (the id the game database uses, as main.cpp).
    std::string gameIdFromElf(const std::filesystem::path &elfPath)
    {
        std::string id = elfPath.filename().string();
        const size_t underscore = id.find('_');

        if (underscore != std::string::npos)
            id[underscore] = '-';
        const size_t dot = id.find('.');

        if (dot != std::string::npos)
            id.erase(dot, 1);
        std::transform(id.begin(), id.end(), id.begin(),
                       [](unsigned char c) { return static_cast<char>(std::toupper(c)); });
        return id;
    }

    // A folder name Windows accepts: no <>:"/\|?* or control characters.
    std::string folderName(const std::filesystem::path &elfPath)
    {
        const std::string id = gameIdFromElf(elfPath);
        const char *name = getGameName(id);
        std::string out = name ? name : id;
        for (char &c : out)
        {
            if (static_cast<unsigned char>(c) < 0x20 || std::strchr("<>:\"/\\|?*", c))
                c = '_';
        }
        while (!out.empty() && (out.back() == '.' || out.back() == ' '))  
            out.pop_back();
        return out.empty() ? std::string("PS2Recomp") : out;
    }
}

std::filesystem::path ps2NativeSaveRoot(const std::filesystem::path &elfPath)
{
    const char *enabled = std::getenv("PS2_NATIVE_SAVES");
    if (enabled && std::strcmp(enabled, "0") == 0)
        return {};
    if (const char *dir = std::getenv("PS2_SAVE_DIR"); dir && *dir)
        return std::filesystem::path(dir);
#ifdef _WIN32
    PWSTR savedGames = nullptr;
    std::filesystem::path root;
    if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_SavedGames, KF_FLAG_CREATE, nullptr, &savedGames)))
        root = std::filesystem::path(savedGames) / folderName(elfPath);
     CoTaskMemFree(savedGames);
    return root;
#else
    (void)elfPath;
    return {} ;
#endif
}
