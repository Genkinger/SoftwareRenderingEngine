//
// Created by genkinger on 9/28/17.
//

#ifndef ENGINE_RENDERER_H
#define ENGINE_RENDERER_H

#include <vector>
#include "EngineWindow.h"
#include "Color.h"

using namespace M3D;

enum class RenderMode{
    TRIANGLES,
    LINES,
    POINTS
};

class Renderer {
public:
    Renderer(EngineWindow *window);
    void Begin(RenderMode mode);
    void End();
    void Vertex2(float x, float y);
    void Vertex3(float x, float y, float z);
    void Color3(float r, float g, float b);
    void Clear(float r, float g, float b);
    void DrawBuffer(float* buffer,float* colorBuffer,int cpe, int ecount);
private:
    void Lines();
    void Line(Vec2f a_norm, Vec2f b_norm,int aCol, int bCol);
    void Points();
    void ClipLine(Vec2f a_norm, Vec2f b_norm, Vec2f* a_out, Vec2f* b_out);
    bool FloatEquals(float a, float b);
private:
    uint mCurrentColor = rgb_float(1,1,1);
    bool mInBlock = false;
    std::vector<Vec3f> mPoints;
    std::vector<uint> mColors;
    EngineWindow *mWindow;
    RenderMode mRenderMode;

};


#endif //ENGINE_RENDERER_H
