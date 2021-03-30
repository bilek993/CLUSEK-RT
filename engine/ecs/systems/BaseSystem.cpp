//
// Created by jbili on 30.03.2021.
//

#include "BaseSystem.h"

void BaseSystem::Start()
{
    StartSystem();
}

void BaseSystem::Update(float deltaTime)
{
    UpdateTimer.Restart();

    if (Enabled)
        UpdateSystem(deltaTime);

    SingleDeltaTime = UpdateTimer.GetDeltaTime();
}

void BaseSystem::Enable()
{
    Enabled = true;
}

void BaseSystem::Disable()
{
    Enabled = false;
}

bool BaseSystem::IsEnabled() const
{
    return Enabled;
}

float BaseSystem::GetSingleDeltaTime() const
{
    return SingleDeltaTime;
}
