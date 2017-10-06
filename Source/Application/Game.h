//
// Created by genkinger on 10/2/17.
//

#ifndef ENGINE_GAME_H
#define ENGINE_GAME_H


#include "Application.h"
#include "../Graphics/EngineWindow.h"
#include "../Graphics/Renderer.h"
#include "../Input/InputHandler.h"
#include "../Graphics/SoftwareRenderer.h"

class Game : public Application {

public:
    Game(int width, int height);
    void Start() override;
    ~Game();
private:
    void Run() override;
    void Stop() override;

    void Tick();   //Physics
    void Render(); //Graphics
    void Update(); //Input
    void Apply(Matrix<4,float> matrix, float* buffer, float* out, int cpe, int ecount);
private:
    EngineWindow mWindow;
    SoftwareRenderer mRenderer;
    InputHandler mHandler;
    SubWindow mFull;
    SubWindow mTopLeft;
    SubWindow mTopRight;
    SubWindow mBotRight;
    SubWindow mBotLeft;
    float a = 0;
    bool mRunning = false;
};


#endif //ENGINE_GAME_H
