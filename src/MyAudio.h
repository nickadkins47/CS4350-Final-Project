
#pragma once

#include <string>
using std::string;
#include <map>

#include "Vector.h"
#include "VectorFwd.h"

#include "MyCam.h"

//cant get irrklang to work otherwise (included from usr/include)
#include "../../../include/irrklang/include/irrKlang.h"
using namespace irrklang;

// Turn Aftr Vector to IrrKlang Vector
inline irrklang::vec3df VecAtoI( Aftr::Vector const& vec ) {
    return irrklang::vec3df( vec.x, vec.y, vec.z );
}

// Turn IrrKlang Vector to Aftr Vector
inline Aftr::Vector VecItoA( irrklang::vec3df const& vec ) {
    return Aftr::Vector( vec.X, vec.Y, vec.Z );
}

class MyAudioManager {
public:
    MyAudioManager();

    void add2D(
        string const& name,
        string const& filePath, 
        bool const& playLooped = false,
        bool const& startPaused = false, 
        E_STREAM_MODE const& streamMode = ESM_AUTO_DETECT,
        bool const& enableSFX = false
    );

    void add3D(
        string const& name,
        string const& filePath, 
        Aftr::Vector const& initPos = Aftr::Vector(0,0,0),
        bool const& playLooped = false, 
        bool const& startPaused = false,
        E_STREAM_MODE const& streamMode = ESM_AUTO_DETECT,
        bool const& enableSFX = false
    );

    ISound*& operator[](string const& name);

    void play(string const& name);

    void resume(string const& name);

    void pause(string const& name);

    void stop(string const& name);

    //set listener position to the camera's position
    void updateListenerPos();

    ISoundEngine* operator->();

    MyCam* mycamPtr = nullptr;

private:
    ISoundEngine* engine = nullptr;
    std::map<string,ISound*> soundMap;

};
