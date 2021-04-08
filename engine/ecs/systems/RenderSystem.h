//
// Created by jbili on 30.03.2021.
//

#ifndef CLUSEK_RT_RENDERSYSTEM_H
#define CLUSEK_RT_RENDERSYSTEM_H

#include <memory>

#include "BaseSystem.h"
#include "../../renderer/allocator/VulkanMemoryAllocatorImplementation.h"
#include "../../renderer/core/VulkanInstance.h"

class RenderSystem : public BaseSystem
{
public:
    std::string GetName() override;

protected:
    void OnStart() override;
    void OnUpdate(float deltaTime) override;

private:
    std::shared_ptr<VulkanInstance> Instance;
};


#endif //CLUSEK_RT_RENDERSYSTEM_H
