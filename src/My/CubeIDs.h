
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

enum class CubeID: size_t {
    AIR,
    TEST,
    GRASS,
    DIRT
};

void load_CubeID_TXTs();

inline std::unordered_map<CubeID, six<Aftr::Tex>> CubeID_TXTs;

