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
    if (Enabled)
        UpdateSystem(deltaTime);
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
