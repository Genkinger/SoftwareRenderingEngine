//
// Created by genkinger on 9/28/17.
//

#include <cassert>
#include "EngineWindow.h"

int EngineWindow::GetWidth() const {
    return mWidth;
}

int EngineWindow::GetHeight() const {
    return mHeight;
}

SDL_Window *EngineWindow::GetWindow() const {
    return mWindow;
}

SDL_Surface *EngineWindow::GetSurface() const {
    return mSurface;
}

byte *EngineWindow::GetBackBuffer() const {
    return mBackBuffer;
}

int EngineWindow::GetBpp() const {
    return mBpp;
}

EngineWindow::EngineWindow(const std::string &title, int width, int height,int bpp,bool fullscreen)
: mWidth(width), mHeight(height), mBpp(bpp)
{
    SDL_Init(SDL_INIT_VIDEO);
    if(!fullscreen)
        mWindow = SDL_CreateWindow(title.c_str(),SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,width,height,SDL_WINDOW_SHOWN);
    else
        mWindow = SDL_CreateWindow(title.c_str(),SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,width,height,SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN);
    assert(mWindow);

    mSurface = SDL_GetWindowSurface(mWindow);
    assert(mSurface);

    mBackBuffer = new byte[mWidth * mHeight * 4];

}


EngineWindow::~EngineWindow() {
    delete[] mBackBuffer;
}

void EngineWindow::Swap() {
    SDL_LockSurface(mSurface);

    byte* tmp = (byte*)mSurface->pixels;
    mSurface->pixels = mBackBuffer;
    mBackBuffer = tmp;

    SDL_UnlockSurface(mSurface);
    SDL_UpdateWindowSurface(mWindow);
}

