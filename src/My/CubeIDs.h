
#pragma once

#include "ManagerEnvironmentConfiguration.h"
#include "ManagerTex.h"
#include "Tex.h"

#include "StdIncludes.h"

//Get Local Multimedia Path ( module/mm/{input} )
string LMM(string const& input);

//Get Shared Multimedia Path ( usr/shared/mm/{input} )
string SMM(string const& input);

template<typename T>
using six = std::array<T,6>;

//types of blocks present in game
enum class CubeID: size_t {
    AIR,
    TEST,
    GRASS,
    DIRT
};

//map containing the textures for each respective cube ID
inline std::unordered_map<CubeID, six<Aftr::Tex>> CubeID_TXTs;

//loads the values of CubeID_TXTs (must be done after GLView starts?)
void load_CubeID_TXTs();

