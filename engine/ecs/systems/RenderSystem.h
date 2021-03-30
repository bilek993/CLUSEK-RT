//
// Created by jbili on 30.03.2021.
//

#ifndef CLUSEK_RT_RENDERSYSTEM_H
#define CLUSEK_RT_RENDERSYSTEM_H

#include "BaseSystem.h"

class RenderSystem : public BaseSystem
{
public:
    std::string GetName() override;

protected:
    void StartSystem() override;
    void UpdateSystem(float deltaTime) override;
};


#endif //CLUSEK_RT_RENDERSYSTEM_H
