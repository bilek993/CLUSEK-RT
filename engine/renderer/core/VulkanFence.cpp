//
// Created by jbili on 31.05.2021.
//

#include "VulkanFence.h"

VulkanFence::VulkanFence(std::shared_ptr<VulkanLogicalDevice> logicalDevice, const bool createInSignaledState)
{
    LogicalDevice = std::move(logicalDevice);

    VkFenceCreateInfo fenceCreateInfo{};
    fenceCreateInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    fenceCreateInfo.flags = createInSignaledState ? VK_FENCE_CREATE_SIGNALED_BIT : 0;

    const auto result = vkCreateFence(LogicalDevice->GetRaw(), &fenceCreateInfo, nullptr, &InternalFence);
}

VulkanFence::~VulkanFence()
{
    if (InternalFence != VK_NULL_HANDLE)
        vkDestroyFence(LogicalDevice->GetRaw(), InternalFence, nullptr);
}

bool VulkanFence::Wait(uint64_t timeout)
{
    const auto result = vkWaitForFences(LogicalDevice->GetRaw(), 1, &InternalFence, VK_TRUE, timeout);

    if (result == VK_TIMEOUT)
        return false;
    else if (result != VK_SUCCESS)
        throw std::runtime_error("Resetting fence failed!");

    return true;
}

void VulkanFence::Reset()
{
    const auto result = vkResetFences(LogicalDevice->GetRaw(), 1, &InternalFence);
    if (result != VK_SUCCESS)
        throw std::runtime_error("Resetting fence failed!");
}

VkFence VulkanFence::GetRaw() const
{
    return InternalFence;
}
