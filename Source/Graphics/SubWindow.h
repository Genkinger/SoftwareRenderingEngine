//
// Created by genkinger on 10/5/17.
//

#ifndef ENGINE_WINDOW_H
#define ENGINE_WINDOW_H

#include "../Common.h"

using namespace M3D;

class SubWindow {
public:

    SubWindow(float x, float y, float w, float h);
    SubWindow(Vec2f position, Vec2f dimension);

    Vec2f GetPosition() const;
    void SetPosition(const Vec2f &mPosition);

    Vec2f GetDimension() const;
    void SetDimension(const Vec2f &mDimension);


private:
    Vec2f mPosition;
    Vec2f mDimension;
};


#endif //ENGINE_WINDOW_H
