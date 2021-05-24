//
// Created by jbili on 24.05.2021.
//

#ifndef CLUSEK_RT_VULKANCOMMANDPOOL_H
#define CLUSEK_RT_VULKANCOMMANDPOOL_H

#include <vulkan/vulkan.h>

#include "VulkanQueue.h"
#include "VulkanLogicalDevice.h"

class VulkanCommandPool final
{
public:
    VulkanCommandPool(std::shared_ptr<VulkanLogicalDevice> logicalDevice,
                      const VulkanQueue& queue,
                      bool shortLivedCommandBuffers,
                      bool resetCommandBuffersIndividually);
    ~VulkanCommandPool();
    VulkanCommandPool(const VulkanCommandPool& other) = delete;
    VulkanCommandPool(VulkanCommandPool&& other) noexcept = delete;
    VulkanCommandPool& operator=(const VulkanCommandPool& other) = delete;
    VulkanCommandPool& operator=(VulkanCommandPool&& other) noexcept = delete;

    [[nodiscard]] VkCommandPool GetRaw() const;

private:
    VkCommandPool InternalCommandPool = VK_NULL_HANDLE;

    std::shared_ptr<VulkanLogicalDevice> LogicalDevice;
};


#endif //CLUSEK_RT_VULKANCOMMANDPOOL_H
