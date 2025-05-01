
#include "Chunk.h"

MyChunk::MyChunk() {}
MyChunk::~MyChunk() {}

CubeID& MyChunk::at(int const& x, int const& y, int const& z) {
    return _chunk[x][y][z];
}

void MyChunk::generate(int const& cx, int const& cy) {
    for (int x = 0; x < x_dim; x++) { //local x
        int const gx = x + (cx * x_dim); //global x
        for (int y = 0; y < y_dim; y++) { //local y
            int const gy = y + (cy * y_dim); //global y
            const int z = int(perlin2d(gx*0.03125, gy*0.03125, 16, 0, 24));
            _chunk[x][y][z] = CubeID::GRASS;
            for (int uz = z - 1; uz >= 0; uz--) {
                _chunk[x][y][uz] = CubeID::DIRT;
            }
        }
    }
}

void MyChunk::registerCube(
    int const& x, int const& y, int const& z,
    six<Aftr::Tex> const& textures, six<bool> const& isBlank
) {
    const float gx = qs * x; //graphical/simulation location x
    const float gy = qs * y; //etc
    const float gz = qs * z; //etc

    std::array<Aftr::Vector, 8> const v {
        Aftr::Vector{   gx,    gy,    gz},
        Aftr::Vector{   gx,    gy, gz+qs},
        Aftr::Vector{   gx, gy+qs,    gz},
        Aftr::Vector{   gx, gy+qs, gz+qs},
        Aftr::Vector{gx+qs,    gy,    gz},
        Aftr::Vector{gx+qs,    gy, gz+qs},
        Aftr::Vector{gx+qs, gy+qs,    gz},
        Aftr::Vector{gx+qs, gy+qs, gz+qs},
    };

    if (isBlank[0]) { quadData.append_range(fourAftrVecsAsFloats(v[0], v[1], v[3], v[2])); numQuads++; }
    if (isBlank[1]) { quadData.append_range(fourAftrVecsAsFloats(v[4], v[5], v[7], v[6])); numQuads++; }
    if (isBlank[2]) { quadData.append_range(fourAftrVecsAsFloats(v[0], v[1], v[5], v[4])); numQuads++; }
    if (isBlank[3]) { quadData.append_range(fourAftrVecsAsFloats(v[2], v[3], v[7], v[6])); numQuads++; }
    if (isBlank[4]) { quadData.append_range(fourAftrVecsAsFloats(v[0], v[2], v[6], v[4])); numQuads++; }
    if (isBlank[5]) { quadData.append_range(fourAftrVecsAsFloats(v[1], v[3], v[7], v[5])); numQuads++; }
}

void MyChunk::render(int const& cx, int const& cy) {
    rquads = Aftr::WORawQuads::New(quadData.data(), numQuads);
    rquads->setLabel(fmt::format("Chunk({},{})", cx, cy));
    (*worldLst)->push_back(rquads);
}

double MyChunk::perlin2d(double x, double y, double scale, double shift, int32_t octaves, double persistence) {
    siv::PerlinNoise static const perlin(seed);
    return scale * perlin.octave2D_01(double(x), double(y), octaves, persistence) + shift;
}

std::array<float, 12> MyChunk::fourAftrVecsAsFloats(
    Aftr::Vector const& v1, Aftr::Vector const& v2, Aftr::Vector const& v3, Aftr::Vector const& v4
) {
    return { v1.x, v1.y, v1.z, v2.x, v2.y, v2.z, v3.x, v3.y, v3.z, v4.x, v4.y, v4.z };
}