#pragma once  
#include <cstddef>
#include <cstdint>
#include <iterator>
#include <vector>

namespace dk_loads
{
    struct Range
    {
        uint32_t begin, end; // physical guest addresses, end exclusive
    };
    const std::vector<Range> &ranges();

    template <class Map, class AddressOf>
    void dropLoaded(Map &cache, size_t &seen, AddressOf addressOf)
    {
        const std::vector<Range> &loads = ranges();
        for (; seen < loads.size(); ++seen)
            for (auto it =  cache.begin(); it != cache.end(); )
            {
                const uint32_t a = addressOf(*it) & 0x1FFFFFFFu;
                it = a >= loads[seen].begin && a < loads[seen].end ? cache.erase(it) : std::next(it);
            }
    }
}
