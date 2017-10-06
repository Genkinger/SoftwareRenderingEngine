//
// Created by genkinger on 10/2/17.
//

#include "Game.h"
#include "../Utils/ScopeTimer.h"

Game::Game(int width, int height)
        : mWindow(EngineWindow("Game",width,height,4,false)),
          mRenderer(SoftwareRenderer(&mWindow)),
          mFull(0,0,mWindow.GetWidth(),mWindow.GetHeight()),

          mTopLeft(0,0,mWindow.GetWidth()/2,mWindow.GetHeight()/2),
          mTopRight(mWindow.GetWidth()/2,0,mWindow.GetWidth()/2,mWindow.GetHeight()/2),
          mBotLeft(0,mWindow.GetHeight()/2,mWindow.GetWidth()/2,mWindow.GetHeight()/2),
          mBotRight(mWindow.GetWidth()/2,mWindow.GetHeight()/2,mWindow.GetWidth()/2,mWindow.GetHeight()/2)
{

}

void Game::Start() {
    mRunning = true;
    Run();
}

void Game::Run() {
    while(mRunning){
        Update();
        Tick();
        Render();
    }
}

void Game::Stop() {
    mRunning = false;
}



void Game::Tick() {

}

void Game::Render() {
    ScopeTimer t("Render",TimerResolution::MILLI);

    a+=0.1f;


    mRenderer.Clear(mFull,{0,0,0});

    mRenderer.SetProjection(Mat4f::Identity(1));
    mRenderer.SetModelView(Mat4f::Identity(1));
    mRenderer.DrawLine(mFull,{-1,0,0},{1,0,0},{1,1,1},{1,1,1});
    mRenderer.DrawLine(mFull,{0,1,0},{0,-1,0},{1,1,1},{1,1,1});



    mRenderer.SetModelView(Mat4f::Rotation(DEG_TO_RAD(a),{0,1,0}) * Mat4f::LookAt({2,2,2},{0,0,0},{0,1,0}));
    mRenderer.SetProjection(Mat4f::Perspective(DEG_TO_RAD(60),4.0f/3,1,100));
    mRenderer.DrawTriangle(mTopRight,{-1,-1,0},{0,1,0},{1,-1,0},{1,0,0},{0,1,0},{0,0,1});
    mRenderer.DrawTriangle(mTopLeft,{-1,-1,0},{0,1,0},{1,-1,0},{1,0,0},{0,1,0},{0,0,1});
    mRenderer.DrawTriangle(mBotRight,{-1,-1,0},{0,1,0},{1,-1,0},{1,0,0},{0,1,0},{0,0,1});
    mRenderer.DrawTriangle(mBotLeft,{-1,-1,0},{0,1,0},{1,-1,0},{1,0,0},{0,1,0},{0,0,1});

    //mRenderer.DrawTriangleFilled(mFull,{-0.5,-0.5,0},{0,0.5,0},{0.5,-0.5,0});

    mWindow.Swap();
}

void Game::Update() {
    mHandler.Update([](SDL_Event& ev){});

    mRunning = !mHandler.ShouldQuit();
}

Game::~Game() {

    SDL_Quit();
}

void Game::Apply(Matrix<4,float> matrix, float* buffer, float* out, int cpe, int ecount){

    for(int i = 0; i < ecount; i++){
        Vec4f v = {buffer[i*cpe], buffer[i*cpe + 1], buffer[i * cpe + 2], 1};

        Vec4f res = matrix * v;
        out[i*cpe] = res[0] /res[3];
        out[i*cpe+1] = res[1] / res[3];
        out[i*cpe+2] = res[2] / res[3];
    }

}



