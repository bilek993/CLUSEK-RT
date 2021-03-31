//
// Created by jbili on 19.03.2021.
//

#include "Engine.h"

#include "ecs/systems/RenderSystem.h"
#include "common/debug/Logger.h"

void Engine::Initialize(const ConfigData& configData)
{
    LOG_DEBUG("Staring engine initialization process...");

    ConfigurationData = configData;

    CreateSystems();
    StartSystems();

    PrepareTimer();

    LOG_DEBUG("Engine initialization finished!");
}

bool Engine::ShouldUpdate()
{
    return true; // TODO: Add proper logic here
}

void Engine::Update()
{
    UpdateSystems(DeltaTimer.GetDeltaTimeAndRestart());
}

void Engine::CreateSystems()
{
    LOG_DEBUG("Creating systems...");

    Systems = {
            std::make_shared<RenderSystem>(),
    };
}

void Engine::StartSystems()
{
    LOG_DEBUG("Starting systems...");

    for (auto& system : Systems)
        system->Start();
}

void Engine::UpdateSystems(float deltaTime)
{
    for (auto& system : Systems)
        system->Update(deltaTime);
}

void Engine::PrepareTimer()
{
    LOG_DEBUG("Preparing delta timer to be used in systems...");
    DeltaTimer.Restart();
}

