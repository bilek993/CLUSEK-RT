//
// Created by jbili on 28.06.2021.
//

#include "VulkanPipelineLayout.h"

VulkanPipelineLayout::VulkanPipelineLayout(std::shared_ptr<VulkanLogicalDevice> logicalDevice)
{
    LogicalDevice = std::move(logicalDevice);

    // TODO: Provide proper implementation here
}

VulkanPipelineLayout::~VulkanPipelineLayout()
{
    if (InternalPipelineLayout != VK_NULL_HANDLE)
        vkDestroyPipelineLayout(LogicalDevice->GetRaw(), InternalPipelineLayout, nullptr);
}

VkPipelineLayout VulkanPipelineLayout::GetRaw() const
{
    return InternalPipelineLayout;
}
