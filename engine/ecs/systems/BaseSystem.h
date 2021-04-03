//
// Created by jbili on 30.03.2021.
//

#ifndef CLUSEK_RT_BASESYSTEM_H
#define CLUSEK_RT_BASESYSTEM_H

#include <string>
#include <memory>
#include <vector>

#include "../../common/Timer.h"
#include "../../common/ConfigData.h"
#include "../../window/Window.h"

class BaseSystem
{
public:
    BaseSystem() = default;
    ~BaseSystem() = default;
    BaseSystem(const BaseSystem& other) = delete;
    BaseSystem(BaseSystem&& other) noexcept = delete;
    BaseSystem& operator=(const BaseSystem& other) = delete;
    BaseSystem& operator=(BaseSystem&& other) noexcept = delete;

    void Start(std::shared_ptr<ConfigData> configurationData,
               std::shared_ptr<Window> mainWindow,
               std::shared_ptr<std::vector<std::shared_ptr<BaseSystem>>> systems);
    void Update(float deltaTime);

    void Enable();
    void Disable();
    [[nodiscard]] bool IsEnabled() const;

    [[nodiscard]] float GetSingleDeltaTime() const;

    virtual std::string GetName() = 0;

protected:
    virtual void OnStart() = 0;
    virtual void OnUpdate(float deltaTime) = 0;

    std::shared_ptr<ConfigData> ConfigurationData;
    std::shared_ptr<Window> MainWindow;
    std::shared_ptr<std::vector<std::shared_ptr<BaseSystem>>> Systems;

private:
    bool Enabled = true;

    Timer UpdateTimer{};
    float SingleDeltaTime{};
};


#endif //CLUSEK_RT_BASESYSTEM_H
