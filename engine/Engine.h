//
// Created by jbili on 19.03.2021.
//

#ifndef CLUSEK_RT_ENGINE_H
#define CLUSEK_RT_ENGINE_H

#include <vector>
#include <memory>

#include "ecs/systems/BaseSystem.h"
#include "common/Timer.h"
#include "common/ConfigData.h"
#include "window/Window.h"

class Engine final
{
public:
    Engine() = default;
    ~Engine() = default;
    Engine(const Engine& other) = delete;
    Engine(Engine&& other) noexcept = delete;
    Engine& operator=(const Engine& other) = delete;
    Engine& operator=(Engine&& other) noexcept = delete;

    void Initialize(std::shared_ptr<ConfigData> configData);

    [[nodiscard]] bool ShouldUpdate() const;
    void Update();

    void Finalize();

private:
    void CreateSystems();
    void StartSystems();

    void UpdateSystems(float deltaTime);

    void PrepareTimer();

    Timer DeltaTimer{};

    std::shared_ptr<ConfigData> ConfigurationData;
    std::shared_ptr<Window> MainWindow;
    std::shared_ptr<std::vector<std::shared_ptr<BaseSystem>>> Systems{};
};


#endif //CLUSEK_RT_ENGINE_H
