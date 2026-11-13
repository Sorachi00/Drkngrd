#pragma once

#include <cstdint>
#include <functional>
#include <memory>
#include <vector>

namespace ps2_runtime_hooks
{
    using ChainKickFn = void ( *)(uint8_t *rdram, uint32_t tadr);
    using DmaNormalKickFn = uint32_t (*)(uint8_t *rdram, uint32_t channel, uint32_t madr, uint32_t qwc);
    using ChainTagDataFn = const std::vector<uint8_t> *(*)(uint32_t channel, uint32_t index, uint32_t tagAddr, bool tte);
    using EeThreadRunFn = void (*)(int threadId );

    void setVif1ChainKick(ChainKickFn fn);
    void setGifChainKick(ChainKickFn fn);
    void setDmaNormalKick(DmaNormalKickFn fn);
    void setChainTagData(ChainTagDataFn fn);
    void setEeThreadRun(EeThreadRunFn fn);

    ChainKickFn gifChainKick();
    ChainTagDataFn chainTagData(); 

    void dmaInsert(std::function<void()> atGif);

    // A native movie picture for the renderer (null rgba ends it): false = write it to guest RAM.
    using MoviePictureFn = bool (*)(std::shared_ptr<const std::vector<uint8_t>> rgba, uint32_t width, uint32_t height);
    void setMoviePicture(MoviePictureFn fn);
    MoviePictureFn moviePicture();
}
