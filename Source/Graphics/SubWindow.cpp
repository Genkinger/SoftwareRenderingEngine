//
// Created by genkinger on 10/5/17.
//

#include "SubWindow.h"

Vec2f SubWindow::GetPosition() const {
    return mPosition;
}

void SubWindow::SetPosition(const Vec2f &mPosition) {
    SubWindow::mPosition = mPosition;
}

Vec2f SubWindow::GetDimension() const {
    return mDimension;
}

void SubWindow::SetDimension(const Vec2f &mDimension) {
    SubWindow::mDimension = mDimension;
}

SubWindow::SubWindow(float x, float y, float w, float h) : mPosition{x,y}, mDimension{w,h}{}

SubWindow::SubWindow(Vec2f position, Vec2f dimension) : mPosition(position), mDimension(dimension){}
