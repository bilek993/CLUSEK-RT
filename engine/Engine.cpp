//
// Created by jbili on 19.03.2021.
//

#include "Engine.h"

#include "ecs/systems/RenderSystem.h"
#include "common/debug/Logger.h"

void Engine::Initialize()
{
    LOG_DEBUG("Staring engine initialization process...");

    CreateSystems();
    StartSystems();

    LOG_DEBUG("Engine initialization finished!");
}

bool Engine::ShouldUpdate()
{
    return true; // TODO: Add proper logic here
}

void Engine::Update()
{
    for (auto& system : Systems)
        system.first->Update(0.0F); // TODO: Add delta time passing
}

void Engine::CreateSystems()
{
    Systems = {
            std::make_pair(std::make_unique<RenderSystem>(), "RenderSystem"),
    };
}

void Engine::StartSystems()
{
    for (auto& system : Systems)
        system.first->Start();
}
