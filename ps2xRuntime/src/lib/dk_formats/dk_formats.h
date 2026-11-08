 #pragma once

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

namespace dk_formats
{
    struct WzimImage
    {
        uint32_t width = 0;
        uint32_t height = 0;
        std::vector<uint8_t> rgba;
    };
    bool wzimDecode(const uint8_t *data, size_t size, std::vector<WzimImage> &images, std::string &error);
    bool wzimEncode(std::vector<uint8_t> &data, const std::vector<WzimImage> &images, std::string &error);

    bool kpsDecode(const uint8_t *data, size_t size, std::string &utf8, std::string &error);
    bool kpsEncode(const std::string &utf8, std::vector<uint8_t> &out, std::string &error); 

    struct CadsAudio

    {
        uint32_t sampleRate = 0;
        uint32_t channels = 0;
         std::vector<int16_t> pcm;
    };
    bool cadsDecode(const uint8_t *data, size_t size, CadsAudio &audio, std::string &error);
    bool cadsEncode(std::vector<uint8_t> &data, const CadsAudio &audio, std::string &error);
}
