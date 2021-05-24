//
// Created by jbili on 24.05.2021.
//

#ifndef CLUSEK_RT_COMMANDPOOL_H
#define CLUSEK_RT_COMMANDPOOL_H

#include <vulkan/vulkan.h>

#include "VulkanQueue.h"
#include "VulkanLogicalDevice.h"

class CommandPool final
{
public:
    CommandPool(std::shared_ptr<VulkanLogicalDevice> logicalDevice,
                const VulkanQueue& queue,
                bool shortLivedCommandBuffers,
                bool resetCommandBuffersIndividually);
    ~CommandPool();
    CommandPool(const CommandPool& other) = delete;
    CommandPool(CommandPool&& other) noexcept = delete;
    CommandPool& operator=(const CommandPool& other) = delete;
    CommandPool& operator=(CommandPool&& other) noexcept = delete;

    [[nodiscard]] VkCommandPool GetRaw() const;

private:
    VkCommandPool InternalCommandPool = VK_NULL_HANDLE;

    std::shared_ptr<VulkanLogicalDevice> LogicalDevice;
};


#endif //CLUSEK_RT_COMMANDPOOL_H
