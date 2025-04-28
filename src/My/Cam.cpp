
#include <stdexcept>
#include "Cam.h"

void MyCam::update() {
    if (camPtr == nullptr) throw std::runtime_error("myCam's camPtr == nullptr");
    if (kbdPtr == nullptr) throw std::runtime_error("myCam's kbdPtr == nullptr");

    const bool forward = kbdPtr->isKeyDown(SDLK_w);
    const bool back    = kbdPtr->isKeyDown(SDLK_s);
    const bool left    = kbdPtr->isKeyDown(SDLK_a);
    const bool right   = kbdPtr->isKeyDown(SDLK_d);
    const bool up      = kbdPtr->isKeyDown(SDLK_e);
    const bool down    = kbdPtr->isKeyDown(SDLK_q);

    const bool fast    = kbdPtr->isKeyDown(SDLK_LSHIFT) || kbdPtr->isKeyDown(SDLK_RSHIFT);

    const Aftr::Model* const camModel = (*camPtr)->getModel();

    prevPos = (*camPtr)->getPosition();

    (*camPtr)->setPosition( 
        ( camModel->getRelXDir() * (forward - back ) * (fast? 4:1) ) +
        ( camModel->getRelYDir() * (   left - right) * (fast? 4:1) ) +
        ( camModel->getRelZDir() * (     up - down ) * (fast? 4:1) ) +
        prevPos
    );
}

Aftr::Camera* MyCam::operator->() {
    return *camPtr;
}

Aftr::Vector MyCam::getPrevPosition() const {
    return prevPos;
}

Aftr::Vector MyCam::getVelocity() const {
    return (*camPtr)->getPosition() - prevPos;
}