
#include "Grid.h"

MyGrid::MyGrid() {}
MyGrid::~MyGrid() {}

CubeID& MyGrid::at(int const& x, int const& y, int const& z) {
    return grid[x][y][z];
}

void MyGrid::render() {
    for (size_t x = 0; x < x_dim; x++) {
        for (size_t y = 0; y < y_dim; y++) {
            for (size_t z = 0; z < z_dim; z++) {
                //if 0 or undefined, dont draw any quads
                if (isBlank(x,y,z)) continue;
                renderCube(x,y,z, CubeID_TXTs[grid[x][y][z]]);
            }
        }
    }
}

void MyGrid::renderCube(int const& x, int const& y, int const& z, six<Aftr::Tex> const& textures) {

    const float gx = quadSize * (x + 0.5f); //graphical/simulation location x
    const float gy = quadSize * (y + 0.5f); //etc
    const float gz = quadSize * (z + 0.5f); //etc
    const float sh = quadSize / 2; //shift sides of cube by size/2 away from center of cube

    //If any neighboring block is empty, render the side of this cube that is facing towards that block
    if (isBlank(x-1,y,z)) renderQuad(0, {gx-sh, gy, gz}, Aftr::QuadOrientation::qoYZ, textures[0]); // -x
    if (isBlank(x+1,y,z)) renderQuad(1, {gx+sh, gy, gz}, Aftr::QuadOrientation::qoYZ, textures[1]); // +x
    if (isBlank(x,y-1,z)) renderQuad(2, {gx, gy-sh, gz}, Aftr::QuadOrientation::qoXZ, textures[2]); // -y
    if (isBlank(x,y+1,z)) renderQuad(3, {gx, gy+sh, gz}, Aftr::QuadOrientation::qoXZ, textures[3]); // +y
    if (isBlank(x,y,z-1)) renderQuad(4, {gx, gy, gz-sh}, Aftr::QuadOrientation::qoXY, textures[4]); // -z
    if (isBlank(x,y,z+1)) renderQuad(5, {gx, gy, gz+sh}, Aftr::QuadOrientation::qoXY, textures[5]); // +z

}

void MyGrid::renderQuad(
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

bool MyGrid::isBlank(int const& x, int const& y, int const& z) {
    if (x < 0 || x >= x_dim || y < 0 || y >= y_dim || z < 0 || z >= z_dim) return true;
    return !CubeID_TXTs.contains(grid[x][y][z]);
}