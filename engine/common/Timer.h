//
// Created by jbili on 30.03.2021.
//

#ifndef CLUSEK_RT_TIMER_H
#define CLUSEK_RT_TIMER_H

#include <chrono>

class Timer
{
public:
    Timer();

    void Restart();
    [[nodiscard]] float GetDeltaTime() const;
    [[nodiscard]] float GetDeltaTimeAndRestart();
private:
    std::chrono::time_point<std::chrono::steady_clock> PreviousTimePoint;
};


#endif //CLUSEK_RT_TIMER_H
