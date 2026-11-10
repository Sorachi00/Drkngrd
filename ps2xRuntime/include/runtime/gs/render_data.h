#pragma once

#include "runtime/gs/gs_types.h"
#include <cstdint>
#include <utility>
#include <vector>

// A GS register write: register, value.

struct GSRegWrite

{
    uint8_t reg;
    uint64_t value;
    bool operator==(const GSRegWrite &o) const { return reg == o.reg && value == o.value; }
    bool operator!=(const GSRegWrite &o) const { return !(*this == o); }
}; 

// GS state where the command is in the GIF stream.
struct RenderState
{ 

    GSContext ctx[2]; // drawing contexts 1 and 2

    uint32_t fogcol;  // FOGCOL: R | G << 8 | B << 16
    GSTexaReg texa; 
    GSTexClutReg texclut;

    // The rest of the GS register state.
    GSPrimReg prim, primRegister, prmodeRegister;
    bool prmodecont;
    uint8_t rgba[4]; // RGBAQ R, G, B, A   
    float q, s, t;
    uint16_t u, v; 
    uint8_t fog;
    bool pabe;
    uint64_t scanmsk, dimx, dthe, colclamp;
    GSBitBltBuf bitbltbuf;
    GSTrxPos trxpos;
    GSTrxReg trxreg;
};

struct NativeDraws
{
    enum : uint32_t // state fields: per context (inherit, endSet[0/1]) and global (endSet[2])
    {
        kFrame = 1u << 0, kZbuf = 1u << 1, kScissor = 1u << 2, kXyoffset = 1u << 3, kTex0 = 1u << 4, kTex1 = 1u << 5,
        kClamp = 1u << 6, kAlpha = 1u << 7, kTest = 1u << 8, kFba = 1u << 9, kMiptbp = 1u << 10,

        kTexa = 1u << 16, kTexclut = 1u << 17, kFogcol = 1u << 18, kDthe = 1u << 19, kColclamp = 1u << 20,

        kPabe = 1u << 21, kScanmsk = 1u << 22, kDimx = 1u << 23,
        // endSet[2] only: vertex and transfer state the draw leaves
        kPrim = 1u << 24, kPrmode = 1u << 25, kRgbaq = 1u << 26, kSt = 1u << 27, kUv = 1u << 28, kFog = 1u << 29,
        kTransfer = 1u << 30,
        kContextFields = 0xFFFFu, kGlobalFields = 0xFF0000u
    };
    struct Prim
    {
        GSPrimitiveBatch batch;

        uint32_t inherit; // context fields (of batch.state.prim.ctxt) | global fields
    } ;
    struct State
    {
        RenderState values{} ;
        uint32_t set[3] = {};
    };
    enum class Kind : uint8_t
    {
        Prim,
        Transfer,   // transfers[index], then images[index] (may be empty)
        TexFlush,
        Privileged, // privileged[index]
    } ;
    struct Item
    {
        Kind kind;
        uint32_t index;
    };
    std::vector<Item> items;
    std::vector<Prim> prims;
    std::vector<GSTransferCommand> transfers;
    std::vector<std::vector<uint8_t>> images;
    std::vector<GSRegWrite> privileged ;
    RenderState end{};
    uint32_t endSet[3] =  {};
    uint32_t function = 0; // the game function the port stands for
};

struct Native2D

{
    static constexpr uint8_t kImage = 0xFF; // a write that is image data: images[value]

    static constexpr uint8_t kPrim = 0xFA;  // a ready primitive: prims[value]
    static constexpr uint8_t kState =  0xF9; // state set for the draws after it: states[value]
    static constexpr uint8_t kTransfer = 0xF8;   // a transfer: transfers[value]
    static constexpr uint8_t kTexFlush = 0xF7;   // a texture flush   
    static constexpr uint8_t kPrivileged = 0xF6; // privileged[value] (SIGNAL, FINISH, LABEL)
    static constexpr uint8_t kSet = 0xF5; 
    static uint64_t packSet(const uint32_t (&set)[3])
    {

        return uint64_t(set[0] & 0xFFFFu) | uint64_t(set[1] & 0xFFFFu) << 16 | uint64_t(set[2] >> 16) << 32;
    }
    static void unpackSet(uint64_t v, uint32_t (&set)[3])
    {  
        set[0] |= uint32_t(v & 0xFFFFu);
        set[1] |= uint32_t((v >> 16) & 0xFFFFu);
        set[2] |= uint32_t((v >> 32) & 0x7FFFu) << 16;

    }
    using Write =  GSRegWrite;
    template <typename V> static void room(V &v)
    {
        if (v.size() == v.capacity())
            v.reserve(v.capacity() < 16 ? 16 : v.capacity() * 4);
    }
    std::vector<Write> writes;
    std::vector<std::vector<uint8_t>> images;
    std::vector<NativeDraws::Prim> prims;
    std::vector<NativeDraws::State> states;
    std::vector<GSTransferCommand> transfers;
    std::vector<GSRegWrite> privileged;
    uint32_t function = 0; // the game function the port stands for
    bool check = false;    // compare with the game's packets (drawn), PS2_DK_NATIVE2D=check

    void reg(uint8_t r, uint64_t v)
    {
        room(writes);
        writes.push_back({r, v});   
    }
    void image(std::vector<uint8_t> data)   
    {
        room(writes);
        writes.push_back({kImage, images.size()});
        images.push_back(std::move(data));
    }
    void prim(const NativeDraws::Prim &p )

    {
        room(writes);
        room(prims);
        writes.push_back({kPrim, prims.size()});
        prims.push_back(p) ;
    }
    void state( const NativeDraws::State &st)
    {
        room(writes);

        room(states);
        writes.push_back({kState, states.size()});
        states.push_back(st);

    }
    // Write `w` of `from` (with its image, primitive or state) at the end.
    void copy(const Native2D &from, const Write &w)
    {
        if (w.reg == kImage)
            image(from.images[size_t(w.value)]);
        else if (w.reg == kPrim)
            prim(from.prims[size_t(w.value)]);
        else if (w.reg == kState)
            state(from.states[size_t(w.value)]);
        else if (w.reg == kTransfer)
        {
            writes.push_back({kTransfer, transfers.size()});
            transfers.push_back(from.transfers[size_t(w.value)]);
        }
        else if (w.reg == kPrivileged)
        {
            writes.push_back({kPrivileged, privileged.size()});
            privileged.push_back(from.privileged[size_t(w.value)]);
        }
        else
        {
            room(writes);
            writes.push_back( w);
        }
    }

};
