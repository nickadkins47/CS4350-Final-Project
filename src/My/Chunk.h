
#pragma once

#include "IndexedGeometryQuad.h"
#include "Model.h"
#include "WOQuad.h"
#include "WorldContainer.h"

#include "../ThirdParty/PerlinNoise.h"

#include "CubeIDs.h"

class MyGrid;

class MyChunk {
public:
    MyChunk();
    ~MyChunk();

    //returns reference to the block ID at (x,y,z)
    CubeID& at(int const& x, int const& y, int const& z);

    //generate this chunk's data
    void generate(int const& cx, int const& cy);

    void renderCube(
        int const& x, int const& y, int const& z,
        six<Aftr::Tex> const& textures, six<bool> const& isBlank
    );

    bool isGenerated = false;

    inline static Aftr::WorldContainer** worldLst;
    inline static siv::PerlinNoise::seed_type seed = 0;

    inline static const size_t x_dim = 16;
    inline static const size_t y_dim = 16;
    inline static const size_t z_dim = 32;

private:
    
    void renderQuad(
        size_t const& face, Aftr::Vector const& position,
        Aftr::QuadOrientation const& orientation, Aftr::Tex const& tex
    );

    static double perlin2d(double x, double y, double scale, int32_t octaves, double persistence = 0.5);

    std::array<std::array<std::array<CubeID, z_dim>, y_dim>, x_dim> _chunk {};
    //svector<Aftr::WOQuad*> quads;

    inline static const float quadSize = 10.0f;

};