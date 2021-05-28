//
// Created by jbili on 24.05.2021.
//

#include "VulkanCommandBuffer.h"

#include "../../common/debug/Logger.h"

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

void VulkanCommandBuffer::BeginRecording(const bool oneTimeSubmit,
                                         const bool renderPassContinue,
                                         const bool useSimultaneous)
{
    BeginRecording(oneTimeSubmit, renderPassContinue, useSimultaneous, VK_NULL_HANDLE);
}

void VulkanCommandBuffer::BeginRecording(const bool oneTimeSubmit,
                                         const bool renderPassContinue,
                                         const bool useSimultaneous,
                                         const VkCommandBufferInheritanceInfo* inheritanceInfo)
{
    if (RecordingInProgress)
        LOG_WARNING("Requested begin of the recording without ending previous recording!");

    VkCommandBufferBeginInfo commandBufferBeginInfo{};
    commandBufferBeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    commandBufferBeginInfo.flags = 0;
    commandBufferBeginInfo.pInheritanceInfo = inheritanceInfo;

    if (oneTimeSubmit)
        commandBufferBeginInfo.flags |= VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
    if (renderPassContinue)
        commandBufferBeginInfo.flags |= VK_COMMAND_BUFFER_USAGE_RENDER_PASS_CONTINUE_BIT;
    if (useSimultaneous)
        commandBufferBeginInfo.flags |= VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;

    const auto result = vkBeginCommandBuffer(InternalCommandBuffer, &commandBufferBeginInfo);
    if (result != VK_SUCCESS)
        throw std::runtime_error("Failed to begin recording!");
    else
        RecordingInProgress = true;
}

void VulkanCommandBuffer::EndRecording()
{
    if (!RecordingInProgress)
        LOG_WARNING("Requested record ending on not started command buffer!");

    const auto result = vkEndCommandBuffer(InternalCommandBuffer);
    if (result != VK_SUCCESS)
        throw std::runtime_error("Failed to end recording!");
    else
        RecordingInProgress = false;
}

bool VulkanCommandBuffer::IsRecording() const
{
    return RecordingInProgress;
}

VkCommandBuffer VulkanCommandBuffer::GetRaw() const
{
    return InternalCommandBuffer;
}
