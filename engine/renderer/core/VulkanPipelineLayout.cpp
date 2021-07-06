//
// Created by jbili on 28.06.2021.
//

#include "VulkanPipelineLayout.h"

VulkanPipelineLayout::VulkanPipelineLayout(std::shared_ptr<VulkanLogicalDevice> logicalDevice)
{
    LogicalDevice = std::move(logicalDevice);

    // TODO: Provide proper implementation here
    VkPipelineLayoutCreateInfo pipelineLayoutCreateInfo{};
    pipelineLayoutCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    pipelineLayoutCreateInfo.setLayoutCount = 0; // Optional
    pipelineLayoutCreateInfo.pSetLayouts = nullptr; // Optional
    pipelineLayoutCreateInfo.pushConstantRangeCount = 0; // Optional
    pipelineLayoutCreateInfo.pPushConstantRanges = nullptr; // Optional

    const auto result = vkCreatePipelineLayout(LogicalDevice->GetRaw(),
                                               &pipelineLayoutCreateInfo,
                                               nullptr,
                                               &InternalPipelineLayout);
    if (result != VK_SUCCESS)
        throw std::runtime_error("Creating pipeline layout failed!");
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
