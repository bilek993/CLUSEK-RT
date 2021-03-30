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

class Engine final
{
public:
    void Initialize(const ConfigData& configData);
    bool ShouldUpdate();
    void Update();

private:
    void CreateSystems();
    void StartSystems();

    void UpdateSystems(float deltaTime);

    template<class T>
    void RegisterNewSystem(const std::string& name);

    void PrepareTimer();

    Timer UpdateTimer{};

    ConfigData ConfigurationData;

    std::vector<std::pair<std::shared_ptr<BaseSystem>, std::string>> Systems{};
};


#endif //CLUSEK_RT_ENGINE_H
