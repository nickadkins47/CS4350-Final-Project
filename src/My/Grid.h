
#pragma once

#include "CubeIDs.h"
#include "Chunk.h"

class MyGrid {
public:
    MyGrid();
    ~MyGrid();
    
    MyGrid( const MyGrid& toCopy ) = delete;
    MyGrid( MyGrid&& toMove ) = delete;
    MyGrid& operator=( const MyGrid& toCopyAssign ) = delete;
    MyGrid& operator=( MyGrid&& toCopyMove ) = delete;

    MyChunk& chunk(int const& cx, int const& cy); //return chunk based on (cx,cy) coordinates
    CubeID& at(int const& x, int const& y, int const& z); //return Cube ID at (x,y,z)

    void load(int const& cx, int const& cy); //load/render chunk; also generates Cube IDs for neighboring chunks

    inline static const size_t sz_x = 32; // 32x32 chunks in the world
    inline static const size_t sz_y = 32; // 32x32 chunks in the world

private:

    bool isOpen(int const& x, int const& y, int const& z); //true if block at (x,y,z) is air/empty/invalid

    std::array<std::array<MyChunk, sz_x>, sz_y> _grid; //Grid of Chunks, each of which is a 16x16x32 grid

};