//
// Created by genkinger on 10/6/17.
//

#ifndef ENGINE_SOFTWARERENDERER_H
#define ENGINE_SOFTWARERENDERER_H


#include "EngineWindow.h"
#include "../Common.h"
#include "SubWindow.h"

using namespace M3D;
class SoftwareRenderer {

public:
    SoftwareRenderer(EngineWindow* window);

    void DrawLine(const SubWindow& win, Vec3f a, Vec3f b, Vec3f cola, Vec3f colb);
    void DrawPoint(const SubWindow& win, Vec3f p, Vec3f c);
    void DrawTriangle(const SubWindow& win, Vec3f a, Vec3f b, Vec3f c,Vec3f cola, Vec3f colb, Vec3f colc);
    void DrawTriangleFilled(const SubWindow& win, Vec3f a, Vec3f b, Vec3f c);
    void DrawBuffer(float* vertices, int* indices, int components, int elements);
    void Clear(const SubWindow& win, Vec3f c);

    void SetModelView(const Mat4f& matrix);
    void SetProjection(const Mat4f& matrix);

    Vec4f NormalizedToScreen(const Vec4f& normalized, const Vec2f& dimension);
private:
    Vec4f ApplyMatricesToVertex(const Vec4f& vertex);
    Vec4f ApplyMatricesToVertex(const Vec3f& vertex);
    Vec4f ApplyMatricesToVertices(Vec4f* vertices, int count);


    Mat4f mModelView = Mat4f::Identity(1);
    Mat4f mProjection = Mat4f::Identity(1);
    EngineWindow *mWindow;
};


#endif //ENGINE_SOFTWARERENDERER_H
