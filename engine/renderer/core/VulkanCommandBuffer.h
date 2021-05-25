//
// Created by jbili on 24.05.2021.
//

#ifndef CLUSEK_RT_VULKANCOMMANDBUFFER_H
#define CLUSEK_RT_VULKANCOMMANDBUFFER_H

#include <vulkan/vulkan.h>

#include "VulkanLogicalDevice.h"
#include "VulkanCommandPool.h"

class VulkanCommandBuffer final
{
public:
    VulkanCommandBuffer(std::shared_ptr<VulkanLogicalDevice> logicalDevice,
                        std::shared_ptr<VulkanCommandPool> commandPool,
                        VkCommandBufferLevel level);
    ~VulkanCommandBuffer();
    VulkanCommandBuffer(const VulkanCommandBuffer& other) = delete;
    VulkanCommandBuffer(VulkanCommandBuffer&& other) noexcept = delete;
    VulkanCommandBuffer& operator=(const VulkanCommandBuffer& other) = delete;
    VulkanCommandBuffer& operator=(VulkanCommandBuffer&& other) noexcept = delete;

    [[nodiscard]] VkCommandBuffer GetRaw() const;

private:
    VkCommandBuffer InternalCommandBuffer = VK_NULL_HANDLE;

    std::shared_ptr<VulkanLogicalDevice> LogicalDevice;
    std::shared_ptr<VulkanCommandPool> CommandPool;
};


#endif //CLUSEK_RT_VULKANCOMMANDBUFFER_H
