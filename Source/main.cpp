//
// Created by genkinger on 9/24/17.
//


#include <iostream>
#include "Graphics/Color.h"
#include "Graphics/EngineWindow.h"
#include "Graphics/Renderer.h"
#include "Common.h"
#include "Utils/ScopeTimer.h"
#include <GL/glew.h>


#define WIDTH 640
#define HEIGHT 480


void apply_div(Matrix<4,float> matrix, float* buffer, float* out, int cpe, int ecount){

    for(int i = 0; i < ecount; i++){
        Vec4f v = {buffer[i*cpe],
                   buffer[i*cpe + 1],
                   buffer[i * cpe + 2],
                   1
        };

        Vec4f res = matrix * v;
        out[i*cpe] = res[0] /res[3];
        out[i*cpe+1] = res[1] / res[3];
        out[i*cpe+2] = res[2] / res[3];
    }

}


#if 1
int main(){

    EngineWindow w("Win",WIDTH,HEIGHT,4,false);
    Renderer r(&w);
    bool running = true;

    float buffer[] = {
            -1.0f,-1.0f,-1.0f, // triangle 1 : begin
            -1.0f,-1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f, // triangle 1 : end
            1.0f, 1.0f,-1.0f, // triangle 2 : begin
            -1.0f,-1.0f,-1.0f,
            -1.0f, 1.0f,-1.0f, // triangle 2 : end
            1.0f,-1.0f, 1.0f,
            -1.0f,-1.0f,-1.0f,
            1.0f,-1.0f,-1.0f,
            1.0f, 1.0f,-1.0f,
            1.0f,-1.0f,-1.0f,
            -1.0f,-1.0f,-1.0f,
            -1.0f,-1.0f,-1.0f,
            -1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f,-1.0f,
            1.0f,-1.0f, 1.0f,
            -1.0f,-1.0f, 1.0f,
            -1.0f,-1.0f,-1.0f,
            -1.0f, 1.0f, 1.0f,
            -1.0f,-1.0f, 1.0f,
            1.0f,-1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f,-1.0f,-1.0f,
            1.0f, 1.0f,-1.0f,
            1.0f,-1.0f,-1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f,-1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f,-1.0f,
            -1.0f, 1.0f,-1.0f,
            1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f,-1.0f,
            -1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f,
            1.0f,-1.0f, 1.0f
    };

    float colors[] = {
            1,0,0,
            0,1,0,
            0,0,1
    };

    float out_buffer[3 * 36];
    float out_buffer_b[3 * 36];
    float out_buffer_c[3 * 36];
    float out_buffer_bb[3 * 36];
    float out_buffer_cc[3 * 36];
    float out_buffer_ccc[3 * 36];

    float angle = 0;
    float fac = -1;
    float pos = 2;
    float k = -0.01;

    while(running) {
        SDL_Event ev;
        while (SDL_PollEvent(&ev)) {
            if (ev.type == SDL_QUIT || (ev.type == SDL_KEYDOWN && ev.key.keysym.sym == SDLK_ESCAPE)) {
                running = false;
            }if(ev.type == SDL_KEYDOWN && ev.key.keysym.sym == SDLK_UP){
                fac -=0.1;
            }if(ev.type == SDL_KEYDOWN && ev.key.keysym.sym == SDLK_DOWN){
                fac += 0.1;
            }
        }
        pos = Constrain(pos,-2,2);
        if(pos >= 2 || pos <= -2) k *= -1;

        Mat4f model = Mat4f::Rotation(angle,{0,1,0}) * Mat4f::Translation({0,0,fac}) * Mat4f::Scaling({0.5,0.5,0.5});
        Mat4f modelb = Mat4f::Rotation(-angle,{0,1,0}) * Mat4f::Translation({0,0,-fac}) * Mat4f::Scaling({0.5,0.5,0.5});
        Mat4f lookAt = Mat4f::LookAt({sinf(angle) * 5,2,cosf(angle * 0.23) * 5},{0,0,0},{0,1,0});
        Mat4f projection = Mat4f::Perspective(DEG_TO_RAD(60),4/3.0,1,100);

        apply_div(model,buffer,out_buffer,3,36);
        apply_div(lookAt,out_buffer,out_buffer_b,3,36);
        apply_div(projection,out_buffer_b,out_buffer_c,3,36);

        apply_div(modelb,buffer,out_buffer_bb,3,36);
        apply_div(lookAt,out_buffer_bb,out_buffer_cc,3,36);
        apply_div(projection,out_buffer_cc,out_buffer_ccc,3,36);

        {
            ScopeTimer t("Frame",TimerResolution::MILLI);

            r.Begin(RenderMode::TRIANGLES);

            r.Clear(0, 0, 0);

            r.DrawBuffer(out_buffer_c,NULL,3,36);
            r.DrawBuffer(out_buffer_ccc,NULL,3,36);

            r.End();
            w.Swap();
        }
        angle += 0.01;
        pos -= k;

    }
    SDL_Quit();
    return EXIT_SUCCESS;
}
#endif



