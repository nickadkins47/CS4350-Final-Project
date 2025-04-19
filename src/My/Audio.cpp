
#include "Audio.h"

MyAudioManager::MyAudioManager() {
    engine = createIrrKlangDevice();
}

void MyAudioManager::add2D(
    string const& name,
    string const& filePath, 
    bool const& playLooped,
    bool const& startPaused, 
    E_STREAM_MODE const& streamMode,
    bool const& enableSFX
) {
    soundMap[name] = engine->play2D(
        filePath.c_str(), playLooped, 
        startPaused, true, streamMode, enableSFX
    );
    if (startPaused) {
        soundMap[name]->setIsPaused(false);
        soundMap[name]->setIsPaused(true);
    }
}

void MyAudioManager::add3D(
    string const& name,
    string const& filePath, 
    Aftr::Vector const& initPos,
    bool const& playLooped, 
    bool const& startPaused,
    E_STREAM_MODE const& streamMode,
    bool const& enableSFX
) {
    soundMap[name] = engine->play3D(
        filePath.c_str(), VecAtoI(initPos), playLooped, 
        startPaused, true, streamMode, enableSFX
    );
    if (startPaused) {
        soundMap[name]->setIsPaused(false);
        soundMap[name]->setIsPaused(true);
    }
}

ISound*& MyAudioManager::operator[](string const& name) {
    return soundMap[name];
}

void MyAudioManager::play(string const& name) {
    soundMap.at(name)->setPlayPosition(0);
    soundMap.at(name)->setIsPaused(false);
}

void MyAudioManager::resume(string const& name) {
    soundMap.at(name)->setIsPaused(false);
}

void MyAudioManager::pause(string const& name) {
    soundMap.at(name)->setIsPaused(true);
}

void MyAudioManager::stop(string const& name) {
    soundMap.at(name)->setIsPaused(true);
    soundMap.at(name)->setPlayPosition(0);
}

//set listener position to the camera's position
void MyAudioManager::updateListenerPos() {
    engine->setListenerPosition(
        VecAtoI((*mycamPtr)->getPosition()),
        VecAtoI((*mycamPtr)->getLookDirection()),
        VecAtoI((*mycamPtr).getVelocity()),
        vec3df(0,0,-1) //this one seems to work
    );
}

ISoundEngine* MyAudioManager::operator->() {
    return engine;
}