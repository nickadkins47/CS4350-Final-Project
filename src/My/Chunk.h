
#pragma once

#include "IndexedGeometryQuad.h"
#include "Model.h"
#include "WOQuad.h"
#include "WORawQuads.h"
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

    void registerCube(
        int const& x, int const& y, int const& z,
        six<Aftr::Tex> const& textures, six<bool> const& openSides
    );

    void render();

    bool isGenerated = false;
    bool isRendered = false;

    inline static Aftr::WorldContainer** worldLst;
    inline static siv::PerlinNoise::seed_type seed = 0;

    inline static const size_t x_dim = 16;
    inline static const size_t y_dim = 16;
    inline static const size_t z_dim = 32;

private:

    static std::array<float, 12> fourAftrVecsAsFloats(
        Aftr::Vector const& v1, Aftr::Vector const& v2, Aftr::Vector const& v3, Aftr::Vector const& v4
    );

    static double perlin2d(double x, double y, double scale, double shift, int32_t octaves, double persistence = 0.5);

    std::array<std::array<std::array<CubeID, z_dim>, y_dim>, x_dim> _chunk {};

    svector<float> vertexValues; //used for WORawQuads
    size_t numQuads = 0;

    Aftr::WORawQuads* rquads = nullptr;

    inline static const float qs = 10.0f; //"quadSize": physical size of a quad / side of a cube

};