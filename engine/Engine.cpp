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
    UpdateSystems(UpdateTimer.GetDeltaTimeAndRestart());
}

void Engine::CreateSystems()
{
    RegisterNewSystem<RenderSystem>("Render System");
}

void Engine::StartSystems()
{
    for (auto& system : Systems)
        system.first->Start();
}

void Engine::UpdateSystems(float deltaTime)
{
    for (auto& system : Systems)
        system.first->Update(deltaTime);
}

template<class T>
void Engine::RegisterNewSystem(const std::string& name)
{
    std::pair<std::shared_ptr<BaseSystem>, std::string> system = std::make_pair(std::make_unique<T>(), name);
    Systems.emplace_back(system);
}

void Engine::PrepareTimer()
{
    LOG_DEBUG("Preparing timer for updating systems...");
    UpdateTimer.Restart();
}

