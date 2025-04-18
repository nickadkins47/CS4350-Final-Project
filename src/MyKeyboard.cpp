
#include "MyKeyboard.h"

MyKeyboard::MyKey const& MyKeyboard::at(SDL_Keycode const& keycode) {
    return keys[keycode];
}

MyKeyboard::MyKey& MyKeyboard::operator[](SDL_Keycode const& keycode) {
    return keys[keycode];
}

void MyKeyboard::onKeyDown(SDL_Keycode const& keycode) {
    MyKey& thisKey = keys[keycode];
    thisKey.onKeyDown();
    thisKey.isKeyDown = true;
}

void MyKeyboard::onKeyUp(SDL_Keycode const& keycode) {
    MyKey& thisKey = keys[keycode];
    thisKey.onKeyUp();
    thisKey.isKeyDown = false;
}

bool MyKeyboard::isKeyDown(SDL_Keycode const& keycode) {
    return keys[keycode].isKeyDown;
}

bool MyKeyboard::isKeyUp(SDL_Keycode const& keycode) {
    return !keys[keycode].isKeyDown;
}