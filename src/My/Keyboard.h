
#pragma once

#include <map>
#include <functional>
#include "GLView.h"

//Keeps track of keyboard events like onKeyUp, onKeyDown, as
//well as handling whether or not a key is currently pressed
class MyKeyboard {
public:

    struct MyKey {
    public:
        std::function<void(void)> onKeyDown = [](){return;};
        std::function<void(void)> onKeyUp   = [](){return;};
        bool isKeyDown = false;
    };

    MyKey const& at(SDL_Keycode const& keycode);
    MyKey& operator[](SDL_Keycode const& keycode);

    void onKeyDown(SDL_Keycode const& keycode);
    void onKeyUp(SDL_Keycode const& keycode);

    bool isKeyDown(SDL_Keycode const& keycode);
    bool isKeyUp(SDL_Keycode const& keycode);

protected:
    std::map<SDL_Keycode, MyKey> keys;

};