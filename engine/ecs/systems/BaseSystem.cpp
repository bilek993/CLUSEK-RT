//
// Created by jbili on 30.03.2021.
//

#include "BaseSystem.h"

#include <fmt/format.h>
#include <fmt/compile.h>

#include <utility>

#include "../../common/debug/Logger.h"

void BaseSystem::Start(std::shared_ptr<ConfigData> configurationData,
                       std::shared_ptr<Window> mainWindow,
                       std::shared_ptr<std::vector<std::shared_ptr<BaseSystem>>> systems)
{
    LOG_DEBUG(fmt::format(FMT_COMPILE("Starting '{}'..."), GetName()));

    ConfigurationData = std::move(configurationData);
    MainWindow = std::move(mainWindow);
    Systems = std::move(systems);

    OnStart();

    LOG_DEBUG(fmt::format(FMT_COMPILE("Successfully started '{}'..."), GetName()));
}

void BaseSystem::Update(float deltaTime)
{
    UpdateTimer.Restart();

    if (Enabled)
        OnUpdate(deltaTime);

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
