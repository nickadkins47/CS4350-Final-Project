
#include "Cube.h"

MyCube::MyCube(std::array<Aftr::Tex, 6> const& textures) {
    this->textures = textures;
}

void MyCube::create(Aftr::Vector const& position) {
    const float sh = size / 2; //"shift" quad by size/2 units
    const float x = position.x + sh;
    const float y = position.y + sh;
    const float z = position.z + sh;

    static const auto makeQuad = [&](
        Aftr::QuadOrientation const& orientation, Aftr::Tex const& tex,
        Aftr::Vector const& position, Aftr::Vector const& rotation
    ) {
        Aftr::WOQuad* quad = Aftr::WOQuad::New(orientation, tex, size, size);
        if (rotation.x != 0) quad->rotateAboutRelX(std::numbers::pi * rotation.x);
        if (rotation.y != 0) quad->rotateAboutRelY(std::numbers::pi * rotation.y);
        if (rotation.z != 0) quad->rotateAboutRelZ(std::numbers::pi * rotation.z);
        quad->setPosition(position);
        (*worldLst)->push_back(quad);
    };

    makeQuad(Aftr::QuadOrientation::qoYZ, textures[0], {x-5, y, z}, {0,0,1}   ); // -x
    makeQuad(Aftr::QuadOrientation::qoYZ, textures[1], {x+5, y, z}, {0,0,0}   ); // +x
    makeQuad(Aftr::QuadOrientation::qoXZ, textures[2], {x, y-5, z}, {0,0,0}   ); // -y
    makeQuad(Aftr::QuadOrientation::qoXZ, textures[3], {x, y+5, z}, {0,0,1}   ); // +y
    makeQuad(Aftr::QuadOrientation::qoXY, textures[4], {x, y, z-5}, {1,0,0.5} ); // -z
    makeQuad(Aftr::QuadOrientation::qoXY, textures[5], {x, y, z+5}, {0,0,-0.5}); // +z

}