
#include "Cube.h"

MyCube::MyCube(std::array<Aftr::Tex, 6> const& textures) {
    this->textures = textures;
}

void MyCube::create(Aftr::Vector const& position) {
    const float sh = size / 2; //"shift" quad by size/2 units
    const float x = position.x + 5;
    const float y = position.y + 5;
    const float z = position.z + 5;

    { // -x
        Aftr::WOQuad* quad = Aftr::WOQuad::New(Aftr::QuadOrientation::qoYZ, textures[0], size, size);
        quad->setPosition({x-5, y, z});
        (*worldLst)->push_back(quad);
    }
    { // +x
        Aftr::WOQuad* quad = Aftr::WOQuad::New(Aftr::QuadOrientation::qoYZ, textures[1], size, size);
        quad->setPosition({x+5, y, z});
        (*worldLst)->push_back(quad);
    }
    { // -y
        Aftr::WOQuad* quad = Aftr::WOQuad::New(Aftr::QuadOrientation::qoXZ, textures[2], size, size);
        quad->setPosition({x, y-5, z});
        (*worldLst)->push_back(quad);
    }
    { // +y
        Aftr::WOQuad* quad = Aftr::WOQuad::New(Aftr::QuadOrientation::qoXZ, textures[3], size, size);
        quad->setPosition({x, y+5, z});
        (*worldLst)->push_back(quad);
    }
    { // -z
        Aftr::WOQuad* quad = Aftr::WOQuad::New(Aftr::QuadOrientation::qoXY, textures[4], size, size);
        quad->setPosition({x, y, z-5});
        (*worldLst)->push_back(quad);
    }
    { // +z
        Aftr::WOQuad* quad = Aftr::WOQuad::New(Aftr::QuadOrientation::qoXY, textures[5], size, size);
        quad->setPosition({x, y, z+5});
        (*worldLst)->push_back(quad);
    }
}