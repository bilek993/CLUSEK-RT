//
// Created by jbili on 24.05.2021.
//

#include "VulkanCommandBuffer.h"

VulkanCommandBuffer::VulkanCommandBuffer(std::shared_ptr<VulkanLogicalDevice> logicalDevice,
                                         std::shared_ptr<VulkanCommandPool> commandPool,
                                         VkCommandBufferLevel level)
{
    LogicalDevice = std::move(logicalDevice);
    CommandPool = std::move(commandPool);

    VkCommandBufferAllocateInfo commandBufferAllocateInfo{};
    commandBufferAllocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    commandBufferAllocateInfo.commandPool = CommandPool->GetRaw();
    commandBufferAllocateInfo.level = level;
    commandBufferAllocateInfo.commandBufferCount = 1;

    const auto result = vkAllocateCommandBuffers(LogicalDevice->GetRaw(),
                                                 &commandBufferAllocateInfo,
                                                 &InternalCommandBuffer);
    if (result != VK_SUCCESS)
        throw std::runtime_error("Command buffer cannot be created!");
}

VulkanCommandBuffer::~VulkanCommandBuffer()
{
    if (InternalCommandBuffer != VK_NULL_HANDLE)
        vkFreeCommandBuffers(LogicalDevice->GetRaw(), CommandPool->GetRaw(), 1, &InternalCommandBuffer);
}

VkCommandBuffer VulkanCommandBuffer::GetRaw() const
{
    return InternalCommandBuffer;
}
