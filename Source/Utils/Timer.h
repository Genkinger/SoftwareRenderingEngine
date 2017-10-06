//
// Created by genkinger on 10/5/17.
//

#ifndef ENGINE_TIMER_H
#define ENGINE_TIMER_H


#include <chrono>

class Timer {
public:
    Timer();
    void Tick();
    float GetElapsedSeconds();
private:

    std::chrono::time_point<std::chrono::system_clock> mLast;
    float mDeltaTime;

};


#endif //ENGINE_TIMER_H
