
#pragma once

#include <map>
#include <functional>
#include "GLView.h"

//Keeps track of keyboard events like onKeyUp, onKeyDown, as
//well as handling whether or not a key is currently pressed
class MyKeyboard {
public:

    //stores things to do upon pressing a given key
    struct MyKey {
    public:
        std::function<void(void)> onKeyDown = [](){return;};
        std::function<void(void)> onKeyUp   = [](){return;};
        bool isKeyDown = false;
    };

    MyKey const& at(SDL_Keycode const& keycode); //return const& to key 
    MyKey& operator[](SDL_Keycode const& keycode); //return reference to key

    void onKeyDown(SDL_Keycode const& keycode); //triggers when key is pressed
    void onKeyUp(SDL_Keycode const& keycode); //triggers when key is released

    bool isKeyDown(SDL_Keycode const& keycode);
    bool isKeyUp(SDL_Keycode const& keycode);

protected:
    std::unordered_map<SDL_Keycode, MyKey> keys;

};