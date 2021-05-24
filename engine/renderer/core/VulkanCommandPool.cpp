//
// Created by jbili on 24.05.2021.
//

#include "VulkanCommandPool.h"

VulkanCommandPool::VulkanCommandPool(std::shared_ptr<VulkanLogicalDevice> logicalDevice,
                         const VulkanQueue& queue,
                         const bool shortLivedCommandBuffers,
                         const bool resetCommandBuffersIndividually)
{
    LogicalDevice = std::move(logicalDevice);

    VkCommandPoolCreateInfo commandPoolCreateInfo{};
    commandPoolCreateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    commandPoolCreateInfo.queueFamilyIndex = queue.GetFamilyIndex();
    commandPoolCreateInfo.flags = 0;

    if (shortLivedCommandBuffers)
        commandPoolCreateInfo.flags |= VK_COMMAND_POOL_CREATE_TRANSIENT_BIT;
    if (resetCommandBuffersIndividually)
        commandPoolCreateInfo.flags |= VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;

    const auto result = vkCreateCommandPool(LogicalDevice->GetRaw(),
                                            &commandPoolCreateInfo,
                                            nullptr,
                                            &InternalCommandPool);
    if (result != VK_SUCCESS)
        throw std::runtime_error("Command pool cannot be created!");
}

VulkanCommandPool::~VulkanCommandPool()
{
    vkDestroyCommandPool(LogicalDevice->GetRaw(), InternalCommandPool, nullptr);
}

VkCommandPool VulkanCommandPool::GetRaw() const
{
    return InternalCommandPool;
}
