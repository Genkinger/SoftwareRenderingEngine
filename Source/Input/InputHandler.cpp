//
// Created by genkinger on 10/5/17.
//

#include <SDL2/SDL_events.h>
#include "InputHandler.h"

InputHandler::InputHandler(){

}

Vec2i InputHandler::GetCursorPos() {
    Vec2i v;
    SDL_GetRelativeMouseState(&v[0],&v[1]);
    return v;
}

bool InputHandler::IsKeyDown(SDL_Keycode key) {
    return mKeys[key];
}

bool InputHandler::IsButtonDown(int key) {
    return mButtons[key];
}

void InputHandler::Update(void (*func)(SDL_Event&)) {
    SDL_Event ev;
    while(SDL_PollEvent(&ev)){
        func(ev);
        if(ev.type == SDL_QUIT) mShouldQuit = true;
        if(ev.type == SDL_KEYDOWN){
            auto it = mKeys.find(ev.key.keysym.sym);
            if(it != std::end(mKeys)){
                return;
            }else{
                mKeys[ev.key.keysym.sym] = true;
            }
        }
        if(ev.type == SDL_KEYUP){
            auto it = mKeys.find(ev.key.keysym.sym);
            if(it != std::end(mKeys)){
                return;
            }else{
                mKeys[ev.key.keysym.sym] = false;
            }
        }
        if(ev.type == SDL_MOUSEBUTTONDOWN){
            auto it = mButtons.find(ev.button.button);
            if(it != std::end(mButtons)){
                return;
            }else{
                mButtons[ev.button.button] = true;
            }
        }
        if(ev.type == SDL_MOUSEBUTTONUP){
            auto it = mButtons.find(ev.button.button);
            if(it != std::end(mButtons)){
                return;
            }else{
                mButtons[ev.button.button] = false;
            }
        }
    }
}

bool InputHandler::ShouldQuit() {
    return mShouldQuit;
}
