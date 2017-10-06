//
// Created by genkinger on 10/5/17.
//

#include "Timer.h"

Timer::Timer() {
    mLast = std::chrono::system_clock::now();
}

void Timer::Tick() {
    auto time = std::chrono::system_clock::now();
    mDeltaTime = std::chrono::duration_cast<std::chrono::seconds>(time - mLast).count();
    mLast = time;
}

float Timer::GetElapsedSeconds() {
    return mDeltaTime;
}
