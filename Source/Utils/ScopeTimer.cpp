//
// Created by genkinger on 9/29/17.
//

#include <iostream>
#include "ScopeTimer.h"

ScopeTimer::ScopeTimer(const std::string& name,TimerResolution res) : mName(name),mRes(res){
    mStart = mClock.now();
}

ScopeTimer::~ScopeTimer() {
    if(mRes == TimerResolution::MILLI) {
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(mClock.now() - mStart);
        std::cout << "[" << mName << "]: " << duration.count() << "ms" << std::endl;
    }else if(mRes == TimerResolution::NANO){
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(mClock.now() - mStart);
        std::cout << "[" << mName << "]: " << duration.count() << "ns" << std::endl;
    }else if(mRes == TimerResolution::MICRO){
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(mClock.now() - mStart);
        std::cout << "[" << mName << "]: " << duration.count() << "micros" << std::endl;
    }
}
