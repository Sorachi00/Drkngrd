#pragma once

#include <cstdint>
#include <filesystem>
#include <functional>
#include <memory>
#include <string>
#include <string_view>
#include <vector> 

namespace PS2VDisc
{
    class File
    {
    public: 
        virtual ~File() = default;
        virtual uint64_t size() const = 0;
        virtual size_t read(uint64_t offset, void *dst, size_t n) const = 0;
        virtual const std::filesystem::path &hostPath() const =  0;
        virtual const std::string &discName() const = 0;
    };
    using FilePtr = std::shared_ptr<const File>;

    FilePtr openHostFile(const std::filesystem::path &path);

    std::filesystem::path resolveDataDir(const std::filesystem::path &fallback);

    bool installed(const std::filesystem::path &dataDir);
    bool mount(const std::filesystem::path &dataDir, std::string &error);
    void unmount();
    bool mounted();
    const std::filesystem::path &dataDir();  
    FilePtr find(std::string_view discPath);
    bool readDiscSectors(uint32_t lbn, uint32_t count, void *dst, size_t byteCount);
    uint64_t discSectors();

    using Progress = std::function<void(const std::string &step, uint64_t done, uint64_t total)>;
    bool checkImage(const std::filesystem::path &image, std::string &error);
    bool extractFile(const std::filesystem::path &image, const std::string &discPath,const std::filesystem::path &out, std::string &error);
    bool install(const std::filesystem::path &image, const std::filesystem::path &dataDir,const Progress &progress, std::string &error);

    uint32_t crc32(uint32_t crc, const void *data, size_t n);

    bool decodeV3a(const uint8_t *data, size_t size, std::vector<uint8_t> &out, std::string &error);
    FilePtr findUnpacked(std::string_view discPath, uint32_t index) ;

    bool exportPcFiles(const std::filesystem::path &dataDir, const Progress &progress, std::string &error);
    uint32_t importPcFiles(const std::filesystem::path &dataDir);
    uint32_t buildModPcFiles(const std::filesystem::path &dataDir);

    bool prepareBoot(int argc, char *argv[], std::filesystem::path &elfOut, int &exitCode);
}
