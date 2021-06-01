//
// Created by jbili on 31.05.2021.
//

#ifndef CLUSEK_RT_VULKANFENCE_H
#define CLUSEK_RT_VULKANFENCE_H

#include <memory>
#include <vulkan/vulkan.h>

#include "VulkanLogicalDevice.h"

class VulkanFence final
{
public:
    VulkanFence(std::shared_ptr<VulkanLogicalDevice> logicalDevice, bool createInSignaledState);
    ~VulkanFence();
    VulkanFence(const VulkanFence& other) = delete;
    VulkanFence(VulkanFence&& other) noexcept = delete;
    VulkanFence& operator=(const VulkanFence& other) = delete;
    VulkanFence& operator=(VulkanFence&& other) noexcept = delete;

    [[nodiscard]] VkFence GetRaw() const;

private:
    VkFence InternalFence = VK_NULL_HANDLE;
    std::shared_ptr<VulkanLogicalDevice> LogicalDevice;
};


#endif //CLUSEK_RT_VULKANFENCE_H
