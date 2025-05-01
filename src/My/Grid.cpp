
#include "Grid.h"

MyGrid::MyGrid() {}
MyGrid::~MyGrid() {}

MyChunk& MyGrid::chunk(int const& cx, int const& cy) {
    return _grid
        [(cx < 0)? (sz_x + cx): cx]
        [(cy < 0)? (sz_y + cy): cy]; 
        //negative values will loop back around
}

CubeID& MyGrid::at(int const& x, int const& y, int const& z) {
    return this->chunk(
        int(std::floor(double(x) / MyChunk::x_dim)), //floor to lowest multiple of x/y_dim
        int(std::floor(double(y) / MyChunk::y_dim))  //
    ).at(
        x % MyChunk::x_dim, y % MyChunk::y_dim, z
    );
}

void MyGrid::load(int const& cx, int const& cy) {
    MyChunk& chk = this->chunk(cx,cy);
    if (chk.isRendered) return;

    for (int const& xs : {-1,0,1}) { //generate all neighboring chunks
        for (int const& ys : {-1,0,1}) {
            MyChunk& neighbor = this->chunk(cx+xs,cy+ys);
            if (!neighbor.isGenerated) neighbor.generate(cx+xs,cy+ys);
        }
    }

    for (size_t lx = 0; lx < chk.x_dim; lx++) { //local x
        int const x = lx + (cx * chk.x_dim); //global x
        for (size_t ly = 0; ly < chk.y_dim; ly++) { //local y
            int const y = ly + (cy * chk.y_dim); //global y
            for (size_t z = 0; z < chk.z_dim; z++) { //local & global z
                //if (x,y,z) is 0 (air) or undefined, dont draw any quads for that block
                if (isOpen(x,y,z)) continue;
                six<bool> const openSides = {
                    isOpen(x-1,y,z), //is block at(x,y,z) air/empty/invalid?
                    isOpen(x+1,y,z),
                    isOpen(x,y-1,z),
                    isOpen(x,y+1,z),
                    isOpen(x,y,z-1),
                    isOpen(x,y,z+1),
                };
                chk.registerCube(x, y, z, CubeID_TXTs[chk.at(lx,ly,z)], openSides);
            }
        }
    }
    chk.render(cx,cy);
}

bool MyGrid::isOpen(int const& x, int const& y, int const& z) {
    if (z < 0 || z >= MyChunk::z_dim) return false;
    return !CubeID_TXTs.contains(at(x,y,z));
}