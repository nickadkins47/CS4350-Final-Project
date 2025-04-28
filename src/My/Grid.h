
#pragma once

#include "IndexedGeometryQuad.h"
#include "Model.h"
#include "WOQuad.h"
#include "WorldContainer.h"

#include "CubeIDs.h"

class MyGrid {
public:
    MyGrid();
    ~MyGrid();

    //returns reference to the block ID at (x,y,z)
    CubeID& at(int const& x, int const& y, int const& z);

    //render this grid
    void render();

    inline static Aftr::WorldContainer** worldLst;

private:
    inline static const size_t x_dim = 100;
    inline static const size_t y_dim = 100;
    inline static const size_t z_dim = 20;

    inline static const float quadSize = 10.0f;

    std::array<std::array<std::array<CubeID, z_dim>, y_dim>, x_dim> grid {};
    //svector<Aftr::WOQuad*> quads;
    
    void renderCube(int const& x, int const& y, int const& z, six<Aftr::Tex> const& textures);
    
    void renderQuad(
        size_t const& face, Aftr::Vector const& position,
        Aftr::QuadOrientation const& orientation, Aftr::Tex const& tex
    );

    bool isBlank(int const& x, int const& y, int const& z);

};