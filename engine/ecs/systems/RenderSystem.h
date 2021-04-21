//
// Created by jbili on 30.03.2021.
//

#ifndef CLUSEK_RT_RENDERSYSTEM_H
#define CLUSEK_RT_RENDERSYSTEM_H

#include <memory>
#include <vector>
#include <vulkan/vulkan.h>

#include "BaseSystem.h"
#include "../../renderer/allocator/VulkanMemoryAllocatorImplementation.h"
#include "../../renderer/core/VulkanInstance.h"
#include "../../renderer/core/VulkanPhysicalDevice.h"
#include "../../renderer/core/VulkanQueues.h"
#include "../../renderer/core/VulkanLogicalDevice.h"

class RenderSystem final : public BaseSystem
{
public:
    std::string GetName() override;

protected:
    void OnStart() override;
    void OnUpdate(float deltaTime) override;

private:
    std::shared_ptr<VulkanInstance> Instance;
    std::shared_ptr<VulkanPhysicalDevice> PhysicalDevice;
    std::shared_ptr<VulkanQueues> Queues;
    std::shared_ptr<VulkanLogicalDevice> LogicalDevice;

    std::vector<const char*> LogicalDeviceRequiredExtensions = {
            VK_KHR_SWAPCHAIN_EXTENSION_NAME
    };
};


#endif //CLUSEK_RT_RENDERSYSTEM_H
