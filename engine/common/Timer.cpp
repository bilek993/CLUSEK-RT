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
    PreviousTimePoint = std::chrono::high_resolution_clock::now();
}

float Timer::GetDeltaTime() const
{
    const auto elapsed = std::chrono::duration<float, std::milli>(
            std::chrono::high_resolution_clock::now() - PreviousTimePoint);
    return elapsed.count();
}

float Timer::GetDeltaTimeAndRestart()
{
    const auto deltaTime = GetDeltaTime();
    Restart();
    return deltaTime;
}
