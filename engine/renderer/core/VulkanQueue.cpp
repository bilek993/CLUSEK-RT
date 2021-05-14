//
// Created by jbili on 13.05.2021.
//

#include "VulkanQueue.h"

#include <stdexcept>

VulkanQueue::VulkanQueue()
{
}

VulkanQueue::VulkanQueue(uint32_t familyIndex, bool supportPresentation)
{
    FamilyIndex = familyIndex;
    SupportPresentation = supportPresentation;
}

void VulkanQueue::WaitIdle()
{
    const auto result = vkQueueWaitIdle(InternalQueue);
    if (result != VK_SUCCESS)
        throw std::runtime_error("Waiting for queue failed!");
}

uint32_t VulkanQueue::GetFamilyIndex() const
{
    return FamilyIndex;
}

bool VulkanQueue::IsSupportingPresentation() const
{
    return SupportPresentation;
}

VkQueue VulkanQueue::GetRaw() const
{
    return InternalQueue;
}

VkQueue* VulkanQueue::GetPointerToRaw()
{
    return &InternalQueue;
}
