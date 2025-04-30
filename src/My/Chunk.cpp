
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
            const int z = int(perlin2d(gx*.0625, gy*.0625, 5, 6));
            _chunk[x][y][z] = CubeID::GRASS;
            for (int uz = z - 1; uz >= 0; uz--) {
                _chunk[x][y][uz] = CubeID::DIRT;
            }
        }
    }
}

void MyChunk::renderCube(
    int const& x, int const& y, int const& z,
    six<Aftr::Tex> const& textures, six<bool> const& isBlank
) {
    const float gx = quadSize * (x + 0.5f); //graphical/simulation location x
    const float gy = quadSize * (y + 0.5f); //etc
    const float gz = quadSize * (z + 0.5f); //etc
    const float sh = quadSize / 2; //shift sides of cube by size/2 away from center of cube

    //If any neighboring block is empty, render the side of this cube that is facing towards that block
    if (isBlank[0]) renderQuad(0, {gx-sh, gy, gz}, Aftr::QuadOrientation::qoYZ, textures[0]); // -x
    if (isBlank[1]) renderQuad(1, {gx+sh, gy, gz}, Aftr::QuadOrientation::qoYZ, textures[1]); // +x
    if (isBlank[2]) renderQuad(2, {gx, gy-sh, gz}, Aftr::QuadOrientation::qoXZ, textures[2]); // -y
    if (isBlank[3]) renderQuad(3, {gx, gy+sh, gz}, Aftr::QuadOrientation::qoXZ, textures[3]); // +y
    if (isBlank[4]) renderQuad(4, {gx, gy, gz-sh}, Aftr::QuadOrientation::qoXY, textures[4]); // -z
    if (isBlank[5]) renderQuad(5, {gx, gy, gz+sh}, Aftr::QuadOrientation::qoXY, textures[5]); // +z
}

void MyChunk::renderQuad(
    size_t const& face, Aftr::Vector const& position,
    Aftr::QuadOrientation const& orientation, Aftr::Tex const& tex
) {
    Aftr::WOQuad* quad = Aftr::WOQuad::New(orientation, tex, quadSize, quadSize);
    quad->upon_async_model_loaded([quad](){
        Aftr::ModelMeshSkin& skin = quad->getModel()->getSkin();
        skin.setAmbient(Aftr::aftrColor4f(.75f, .75f, .75f, 1.f));
        /* skin.setDiffuse(Aftr::aftrColor4f(0.f,0.f,0.f,1.f));
        skin.setMeshShadingType(Aftr::MESH_SHADING_TYPE::mstFLAT);
        skin.setSpecular(Aftr::aftrColor4f(0.f,0.f,0.f,1.f));
        skin.setSpecularCoefficient(1000); */
    });
    quad->useFrustumCulling = true;
    quad->setPosition(position);
    if (face == 0 || face == 3) quad->rotateAboutRelZ(std::numbers::pi);
    if (face == 4) quad->rotateAboutRelX(std::numbers::pi);
    (*worldLst)->push_back(quad);
    //quads.push_back(quad);
}

double MyChunk::perlin2d(double x, double y, double scale, int32_t octaves, double persistence) {
    siv::PerlinNoise static const perlin(seed);
    return scale * perlin.octave2D_01(double(x), double(y), octaves, persistence);
}