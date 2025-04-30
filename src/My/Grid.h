
#pragma once

#include "CubeIDs.h"
#include "Chunk.h"

class MyGrid {
public:
    MyGrid();
    ~MyGrid();

    MyChunk& chunk(int const& cx, int const& cy);
    CubeID& at(int const& x, int const& y, int const& z);

    void load(int const& cx, int const& cy);

    inline static const size_t sz_x = 8;
    inline static const size_t sz_y = 8;

private:

    void render(int const& cx, int const& cy);

    std::array<std::array<MyChunk, sz_x>, sz_y> _grid; //Grid of Chunks, each of which is a 16x16x32 grid

};