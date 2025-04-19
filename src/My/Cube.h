
#pragma once

#include "../ModuleIncludes.h"

class MyCube {
public:
    MyCube() = delete;

    //textures: in order of {-x +x -y +y -z +z}
    //NOTE: cube is of size 10x10x10
    MyCube(std::array<Aftr::Tex, 6> const& textures);

    void create(Aftr::Vector const& position);

    inline static Aftr::WorldContainer** worldLst;

private:
    
    std::array<Aftr::Tex, 6> textures;

    const float size = 10;

};