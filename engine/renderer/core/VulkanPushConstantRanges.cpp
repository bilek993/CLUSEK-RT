//
// Created by jbili on 19.07.2021.
//

#include "VulkanPushConstantRanges.h"

uint32_t VulkanPushConstantRanges::GetCount() const
{
    return InternalRanges.size();
}

const VkPushConstantRange* VulkanPushConstantRanges::GetRawPointer() const
{
    return InternalRanges.data();
}
