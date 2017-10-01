//
// Created by genkinger on 9/29/17.
//

#ifndef ENGINE_SCOPETIMER_H
#define ENGINE_SCOPETIMER_H


#include <chrono>

enum class TimerResolution{
    MILLI,
    NANO,
    MICRO,
};

class ScopeTimer {
public:
    ScopeTimer(const std::string& name,TimerResolution res);
    ~ScopeTimer();
private:
    std::string mName;
    TimerResolution mRes;
    std::chrono::high_resolution_clock mClock;
    std::chrono::time_point<std::chrono::_V2::system_clock, std::chrono::duration<long int, std::ratio<1l, 1000000000l> > > mStart;
};


#endif //ENGINE_SCOPETIMER_H
