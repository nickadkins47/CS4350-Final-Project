
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

    MyChunk( const MyChunk& toCopy ) = delete;
    MyChunk( MyChunk&& toMove ) = delete;
    MyChunk& operator=( const MyChunk& toCopyAssign ) = delete;
    MyChunk& operator=( MyChunk&& toCopyMove ) = delete;

    //returns reference to the block ID at (x,y,z)
    CubeID& at(int const& x, int const& y, int const& z);

    //generate this chunk's block IDs
    void generate(int const& cx, int const& cy);

    //sends quad data for a given cube to this->quadData
    void registerCube(
        int const& x, int const& y, int const& z,
        six<Aftr::Tex> const& textures, six<bool> const& openSides
    );

    //turns this->quadData into a WORawQuads, adds to worldLst
    void render(int const& cx, int const& cy);

    bool isGenerated = false;
    bool isRendered = false;

    inline static Aftr::WorldContainer** worldLst;
    inline static siv::PerlinNoise::seed_type seed = 0;

    inline static const size_t x_dim = 16;
    inline static const size_t y_dim = 16;
    inline static const size_t z_dim = 32;

private:

    //concatenate 4 Aftr::Vector's into a single array of 12 floats
    static std::array<float, 12> fourAftrVecsAsFloats(
        Aftr::Vector const& v1, Aftr::Vector const& v2, Aftr::Vector const& v3, Aftr::Vector const& v4
    );

    //Perlin noise function, given an x & y coordinate, # of octaves, persistence value, and a scalar + vertical shift value
    static double perlin2d(double x, double y, double scale, double shift, int32_t octaves, double persistence = 0.5);

    std::array<std::array<std::array<CubeID, z_dim>, y_dim>, x_dim> _chunk {}; //3d array of

    Aftr::WORawQuads* rquads = nullptr; //Result of turning this chunk into a VBO
    svector<float> quadData; //used for WORawQuads
    size_t numQuads = 0; //# of quads stored in quadData

    inline static const float qs = 10.0f; //qs / quadSize: physical size of a quad / side of a cube

};