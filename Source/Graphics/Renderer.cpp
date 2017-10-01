//
// Created by genkinger on 9/28/17.
//

#include "Renderer.h"
#include "../Common.h"
#include "../Utils/ScopeTimer.h"

Renderer::Renderer(EngineWindow *window)
: mWindow(window)
{

}

void Renderer::Begin(RenderMode mode) {
    mRenderMode = mode;
    mInBlock = true;
    mPoints.clear();
    mColors.clear();
}

void Renderer::Clear(float r, float g, float b) {
    for (int i = 0; i < mWindow->GetWidth() * mWindow->GetHeight(); ++i) {
        ((int*)mWindow->GetBackBuffer())[i] = rgb_float(r,g,b);
    }
}

void Renderer::End() {
    if(mRenderMode == RenderMode::POINTS) {
        Points();
    }
    else if(mRenderMode == RenderMode::LINES) {
       // Lines();
        Vec2f start = Vec2f{mPoints[0][0],mPoints[0][1]};
        int startCol = mColors[0];
        for(int i = 1; i < mPoints.size();i++){
            Vec2f end = Vec2f{mPoints[i][0],mPoints[i][1]};
            Line(start,end,startCol,mColors[i]);
            start = end;
            startCol = mColors[i];
        }
    }
    else if(mRenderMode == RenderMode::TRIANGLES){
        if(mPoints.size() % 3 != 0) return;
        for(int i = 0; i < mPoints.size()/3;i++){
            Vec3f _a,_b,_c;
            Vec2f a,b,c;
            _a = mPoints[i * 3];
            _b = mPoints[i * 3 + 1];
            _c = mPoints[i * 3 + 2];

            a = Vec2f{_a[0],_a[1]};
            b = Vec2f{_b[0],_b[1]};
            c = Vec2f{_c[0],_c[1]};

            Line(a,b,mColors[i*3],mColors[i*3+1]);
            Line(b,c,mColors[i*3+1],mColors[i*3+2]);
            Line(c,a,mColors[i*3+2],mColors[i*3]);
        }
    }

    mInBlock = false;
}

void Renderer::Vertex2(float x, float y) {
    if(!mInBlock) return;

    mPoints.push_back(Vec3f{x,y,0});
    mColors.push_back(mCurrentColor);
}

void Renderer::Vertex3(float x, float y, float z) {
    if(!mInBlock) return;

    mPoints.push_back(Vec3f{x,y,z});
    mColors.push_back(mCurrentColor);
}

void Renderer::Color3(float r, float g, float b) {
    if(!mInBlock) return;
    mCurrentColor = rgb_float(r,g,b);
}

void Renderer::Lines() {

    Vec2f a = Vec2f{floorf(Map(mPoints[0][0],-1,1,0,mWindow->GetWidth())),floorf(Map(mPoints[0][0],1,-1,0,mWindow->GetHeight()))};
    Vec4f aCol = unpack_color(mColors[0]);

    for (int i = 1; i < mPoints.size(); ++i) {
        Vec2f b =  Vec2f {floorf(Map(mPoints[i][0], -1, 1, 0, mWindow->GetWidth())),
                         floorf(Map(mPoints[i][1], 1, -1, 0, mWindow->GetHeight()))};

        Vec2f dir = b - a;
        Vec2f dir_n = dir.Normalize_Copy();

        Vec4f bCol = unpack_color(mColors[i]);
        Vec4f dirCol = bCol-aCol;

        Vec2f currentPoint = a;
        Vec4f currentColor = aCol;


        std::vector<Vec2f> pos;
        while(!FloatEquals(currentPoint[0], b[0]) || !FloatEquals(currentPoint[1],b[1])) {
            pos.push_back(currentPoint);
            currentPoint = currentPoint + dir_n;
        }

        float step = dirCol.Length()/pos.size();
        Vec4f factor = dirCol/pos.size();

        for(int j = 0; j < pos.size(); j++){
            auto x = static_cast<int>(pos[j][0]);
            auto y = static_cast<int>(pos[j][1]);

            reinterpret_cast<uint*>(mWindow->GetBackBuffer())[x + y * mWindow->GetWidth()] = rgb_float(currentColor[0],currentColor[1],currentColor[2]);
            currentColor = currentColor + factor;
        }

        a = b;
        aCol = bCol;
    }

}

void Renderer::Points() {
    int x, y;
    for (int i = 0; i < mPoints.size(); i++) {
        x = static_cast<int>(Map(mPoints[i][0], -1, 1, 0, mWindow->GetWidth()));
        y = static_cast<int>(Map(mPoints[i][1], 1, -1, 0, mWindow->GetHeight()));
        reinterpret_cast<uint*>(mWindow->GetBackBuffer())[y * mWindow->GetWidth() + x] = mColors[i];
    }
}

bool Renderer::FloatEquals(float a, float b) {
     return !(abs(a-b) > 0.5);
}

void Renderer::Line(Vec2f a_norm, Vec2f b_norm, int aCol, int bCol) {
   //TODO: simple clipping done wrong
    a_norm[0] = Constrain(a_norm[0],-1,1);
    a_norm[1] = Constrain(a_norm[1],-1,1);

    b_norm[0] = Constrain(b_norm[0],-1,1);
    b_norm[1] = Constrain(b_norm[1],-1,1);
    //END

    Vec2f a = Vec2f{floorf(Map(a_norm[0],-1,1,0,mWindow->GetWidth())),
                    floorf(Map(a_norm[1],1,-1,0,mWindow->GetHeight()))};

    Vec4f aCol_unpacked = unpack_color(aCol);

    Vec2f b = Vec2f{floorf(Map(b_norm[0],-1,1,0,mWindow->GetWidth())),
                    floorf(Map(b_norm[1],1,-1,0,mWindow->GetHeight()))};
    Vec2f dir = b - a;
    Vec2f dir_n = dir.Normalize_Copy();

    Vec4f bCol_unpacked = unpack_color(bCol);
    Vec4f dirCol = bCol_unpacked - aCol_unpacked;

    Vec2f currentPoint = a;
    Vec4f currentColor = aCol_unpacked;


    std::vector<Vec2f> pos;
    while(!FloatEquals(currentPoint[0], b[0]) || !FloatEquals(currentPoint[1],b[1])){

        pos.push_back(currentPoint);
        currentPoint = currentPoint + dir_n;

    }

    float step = dirCol.Length()/pos.size();
    Vec4f factor = dirCol/pos.size();

    for(int j= 0; j < pos.size(); j++){
        auto x = static_cast<int>(pos[j][0]);
        auto y = static_cast<int>(pos[j][1]);

        reinterpret_cast<uint*>(mWindow->GetBackBuffer())[x + y * mWindow->GetWidth()] = rgb_float(currentColor[0],currentColor[1],currentColor[2]);
        currentColor = currentColor + factor;
    }

}

void Renderer::DrawBuffer(float *buffer,float *colorBuffer,int cpe, int ecount) {
    if(!mInBlock) return;

    if(cpe == 3) {
        for (int i = 0; i < ecount; i++) {
            Vec3f p = Vec3f{buffer[i*cpe],buffer[i*cpe+1],buffer[i*cpe+2]};
            mPoints.push_back(p);
        }
        for(int i = 0; i < ecount; i++){
            if(colorBuffer != NULL){
                mColors.push_back(rgb_float(colorBuffer[i*3],colorBuffer[i*3+1],colorBuffer[i*3+2]));
            }else{
                mColors.push_back(mCurrentColor);
            }
        }
    }else if(cpe == 2){
        for (int i = 0; i < ecount; i++ ) {
            Vec3f p = Vec3f{buffer[i*cpe],buffer[i*cpe+1],0};
            mPoints.push_back(p);
        }
        for(int i = 0; i < ecount; i++){
            if(colorBuffer != NULL){
                mColors.push_back(rgb_float(colorBuffer[i*3],colorBuffer[i*3+1],colorBuffer[i*3+2]));

            }else{
                mColors.push_back(mCurrentColor);
            }
        }
    }else return;
}

void Renderer::ClipLine(Vec2f a_norm, Vec2f b_norm, Vec2f* a_out, Vec2f* b_out) {

    if(InRange(a_norm[0],-1,1) && InRange(a_norm[1],-1,1)){
        *a_out = a_norm;
    }
    if(InRange(b_norm[0],-1,1) && InRange(b_norm[1],-1,1)){
        *b_out = b_norm;
    }
    //TODO: implement clipping


}
