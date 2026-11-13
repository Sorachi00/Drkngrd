#pragma once

#include <cstdint>

namespace GSHwScale
{
    void request(uint32_t scale);  
    uint32_t requested();
    void setDynamic(float minFraction);
    float dynamicMin();
}
