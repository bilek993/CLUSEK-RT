//
// Created by jbili on 19.03.2021.
//

#ifndef CLUSEK_RT_ENGINE_H
#define CLUSEK_RT_ENGINE_H

#include <vector>
#include <memory>

#include "ecs/systems/BaseSystem.h"

class Engine final
{
public:
    void Initialize();
    bool ShouldUpdate();
    void Update();

private:
    void CreateSystems();
    void StartSystems();

    std::vector<std::pair<std::shared_ptr<BaseSystem>, std::string>> Systems{};
};


#endif //CLUSEK_RT_ENGINE_H
