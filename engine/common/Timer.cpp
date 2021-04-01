//
// Created by jbili on 30.03.2021.
//

#include "Timer.h"

Timer::Timer()
{
    Restart();
}

void Timer::Restart()
{
    PreviousTimePoint = std::chrono::steady_clock::now();
}

float Timer::GetDeltaTime() const
{
    const auto elapsed = std::chrono::duration<float, std::milli>(
            std::chrono::steady_clock::now() - PreviousTimePoint);
    return elapsed.count();
}

float Timer::GetDeltaTimeAndRestart()
{
    const auto deltaTime = GetDeltaTime();
    Restart();
    return deltaTime;
}
