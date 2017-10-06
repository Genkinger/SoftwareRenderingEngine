//
// Created by genkinger on 10/5/17.
//

#ifndef ENGINE_INPUTHANDLER_H
#define ENGINE_INPUTHANDLER_H


#include <map>
#include "../Common.h"

using namespace M3D;
class InputHandler {

public:
    InputHandler();
    Vec2i GetCursorPos();
    bool IsKeyDown(int key);
    bool IsButtonDown(int key);
    void Update(void (*func)(SDL_Event&));
    bool ShouldQuit();

private:
    std::map<SDL_Keycode, bool> mKeys;
    std::map<int, bool> mButtons;
    bool mShouldQuit = false;

};


#endif //ENGINE_INPUTHANDLER_H
