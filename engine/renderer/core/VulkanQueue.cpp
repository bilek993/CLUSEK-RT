//
// Created by jbili on 13.05.2021.
//

#include "VulkanQueue.h"

VulkanQueue::VulkanQueue()
{
}

VulkanQueue::VulkanQueue(uint32_t familyIndex, bool supportPresentation)
{
    FamilyIndex = familyIndex;
    SupportPresentation = supportPresentation;
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
