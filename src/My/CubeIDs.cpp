
#include "CubeIDs.h"

string LMM(string const& input) {
    return Aftr::ManagerEnvironmentConfiguration::getLMM() + input;
}

string SMM(string const& input) {
    return Aftr::ManagerEnvironmentConfiguration::getSMM() + input;
}

void load_CubeID_TXTs() {
    auto static const getTXTs = [](six<string> const& filePaths) -> six<Aftr::Tex> {
        return {
            *Aftr::ManagerTex::loadTexAsync(filePaths[0]),
            *Aftr::ManagerTex::loadTexAsync(filePaths[1]),
            *Aftr::ManagerTex::loadTexAsync(filePaths[2]),
            *Aftr::ManagerTex::loadTexAsync(filePaths[3]),
            *Aftr::ManagerTex::loadTexAsync(filePaths[4]),
            *Aftr::ManagerTex::loadTexAsync(filePaths[5])
        };
    };

    CubeID_TXTs = {
        //0 or Undefined value -> "Air" / Empty
        { CubeID::TEST, getTXTs({ //test block
            LMM("images/test/test1.png"),
            LMM("images/test/test2.png"),
            LMM("images/test/test3.png"),
            LMM("images/test/test4.png"),
            LMM("images/test/test5.png"),
            LMM("images/test/test6.png")
        })},
        { CubeID::GRASS, getTXTs({ //grass
            LMM("images/grass_side.png"),
            LMM("images/grass_side.png"),
            LMM("images/grass_side.png"),
            LMM("images/grass_side.png"),
            LMM("images/grass_bottom.png"),
            LMM("images/grass_top.png")
        })},
        { CubeID::DIRT, getTXTs({ //dirt
            LMM("images/grass_bottom.png"),
            LMM("images/grass_bottom.png"),
            LMM("images/grass_bottom.png"),
            LMM("images/grass_bottom.png"),
            LMM("images/grass_bottom.png"),
            LMM("images/grass_bottom.png")
        })},
    };
}
