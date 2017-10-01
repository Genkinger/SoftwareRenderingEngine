//
// Created by genkinger on 9/28/17.
//

#ifndef ENGINE_ENGINEWINDOW_H
#define ENGINE_ENGINEWINDOW_H

#include <string>
#include <SDL2/SDL.h>
typedef unsigned char byte;

class EngineWindow {

public:
    EngineWindow(const std::string& title, int width, int height,int bpp,bool fullscreen);
    ~EngineWindow();

    int GetWidth() const;
    int GetHeight() const;
    SDL_Window *GetWindow() const;
    SDL_Surface *GetSurface() const;
    byte *GetBackBuffer() const;
    float *GetZBuffer() const;
    int GetBpp() const;
    void Swap();


private:
    int mWidth;
    int mHeight;
    int mBpp;


    SDL_Window* mWindow;
    SDL_Surface* mSurface;

    byte* mBackBuffer;
    float* mZBuffer;




};


#endif //ENGINE_ENGINEWINDOW_H
