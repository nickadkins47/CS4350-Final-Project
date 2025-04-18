
#pragma once

#include "Camera.h"
#include "Model.h"
#include "MyKeyboard.h"

class MyCam {
public:

    //Update camera movements based on currently pressed keys (via updateWorld)
    void update();

    //Pointer to Keyboard for Movement inputs
    MyKeyboard* kbdPtr = nullptr;

    //Pointer to main camera (Aftr::Camera*)
    Aftr::Camera** camPtr = nullptr;

    //arrow operator just returns the "cam" this MyCam points to
    Aftr::Camera* operator->();

    //Get Previous Position of Camera
    Aftr::Vector getPrevPosition() const;

    //Get Velocity of Camera
    Aftr::Vector getVelocity() const;
    
protected:
    Aftr::Vector prevPos {0,0,0};

};
