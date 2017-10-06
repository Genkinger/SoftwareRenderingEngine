//
// Created by genkinger on 10/6/17.
//

#include <vector>
#include <iostream>
#include "SoftwareRenderer.h"
#include "Color.h"

SoftwareRenderer::SoftwareRenderer(EngineWindow *window) : mWindow(window){}

void SoftwareRenderer::DrawLine(const SubWindow &win, Vec3f a, Vec3f b, Vec3f cola, Vec3f colb) {

    Vec4f a_screen = NormalizedToScreen(ApplyMatricesToVertex(a),win.GetDimension()) + Vec4f(win.GetPosition()[0],win.GetPosition()[1],0,0);
    Vec4f b_screen = NormalizedToScreen(ApplyMatricesToVertex(b),win.GetDimension()) + Vec4f(win.GetPosition()[0],win.GetPosition()[1],0,0);

    Vec4f direction = b_screen - a_screen;
    Vec4f directionStep = direction / direction.Length();

    std::vector<Vec2i> pts;
    Vec4f currentPoint = a_screen;
    while (fabs(currentPoint[1] - b_screen[1]) > 0.5 || fabs(currentPoint[0] - b_screen[0]) > 0.5) {
        int x = (int) floorf(currentPoint[0]);
        int y = (int) floorf(currentPoint[1]);
        pts.push_back(Vec2i(x, y));
        currentPoint = currentPoint + directionStep;
    }

    uint* pixels = reinterpret_cast<uint*>(mWindow->GetBackBuffer());
    int width = mWindow->GetWidth();


    Vec3f colorDirection = colb - cola;
    Vec3f colorStep = colorDirection / pts.size();
    Vec3f currentColor = cola;
    for(auto v : pts){
        pixels[v[0] + v[1] * width] = rgb_float(currentColor[0],currentColor[1],currentColor[2]);
        currentColor  = currentColor + colorStep;
    }


}

void SoftwareRenderer::DrawPoint(const SubWindow &win, Vec3f p, Vec3f c) {

    Vec4f p_screen = NormalizedToScreen(ApplyMatricesToVertex(p),win.GetDimension()) + Vec4f(win.GetPosition()[0],win.GetPosition()[1],0,0);
    int x = (int)floorf(p_screen[0]);
    int y = (int)floorf(p_screen[1]);

    reinterpret_cast<uint*>(mWindow->GetBackBuffer())[x + y * mWindow->GetWidth()] = rgb_float(c[0],c[1],c[2]);
}

void SoftwareRenderer::DrawTriangle(const SubWindow &win, Vec3f a, Vec3f b, Vec3f c, Vec3f cola, Vec3f colb, Vec3f colc) {
    DrawLine(win,a,b,cola,colb);
    DrawLine(win,b,c,colb,colc);
    DrawLine(win,c,a,colc,cola);
}

void SoftwareRenderer::DrawTriangleFilled(const SubWindow &win, Vec3f a, Vec3f b, Vec3f c) {

}

void SoftwareRenderer::DrawBuffer(float *vertices, int *indices, int components, int elements) {

}

Vec4f SoftwareRenderer::NormalizedToScreen(const Vec4f &normalized, const Vec2f &dimension) {
    return {Map(normalized[0],-1,1,0,dimension[0]-1),Map(-normalized[1],-1,1,0,dimension[1]-1),normalized[2],normalized[3]};
}

void SoftwareRenderer::Clear(const SubWindow &win, Vec3f col){
    int cnt = mWindow->GetHeight() * mWindow->GetWidth();
    uint* pixels = reinterpret_cast<uint*>(mWindow->GetBackBuffer());
    uint c = rgb_float(col[0],col[1],col[2]);


    int xmin = (int)floorf(win.GetPosition()[0]);
    int xmax = (int)floorf(win.GetPosition()[0] + win.GetDimension()[0]);

    int ymin = (int)floorf(win.GetPosition()[1]);
    int ymax = (int)floorf(win.GetPosition()[1] + win.GetDimension()[1]);

    int width = mWindow->GetWidth();

    for(int j = ymin; j < ymax; j++){
        for (int i = xmin; i < xmax; ++i) {
            pixels[j * width + i] = c;
        }
    }

}

void SoftwareRenderer::SetModelView(const Mat4f &matrix) {
    mModelView = matrix;
}

void SoftwareRenderer::SetProjection(const Mat4f &matrix) {
    mProjection = matrix;
}

Vec4f SoftwareRenderer::ApplyMatricesToVertex(const Vec4f &vertex) {
    Vec4f result = mProjection * mModelView * vertex;
    result[0] = result[0]/result[3];
    result[1] = result[1]/result[3];
    result[2] = result[2]/result[3];
    result[3] = result[3]/result[3];
    return result;
}

Vec4f SoftwareRenderer::ApplyMatricesToVertex(const Vec3f &vertex) {
    Vec4f result =  mModelView * mProjection * Vec4f(vertex[0],vertex[1],vertex[2],1);
    if(result[3] != 0) {
        result[0] = result[0] / result[3];
        result[1] = result[1] / result[3];
        result[2] = result[2] / result[3];
        result[3] = result[3] / result[3];
    }
    return result;
}

Vec4f SoftwareRenderer::ApplyMatricesToVertices(Vec4f *vertices, int count) {
    return M3D::Vec4f();
}
