//
// Created by jbili on 15.06.2021.
//

#include "VulkanRasterizationPipeline.h"

VulkanRasterizationPipeline::VulkanRasterizationPipeline(std::shared_ptr<VulkanLogicalDevice> logicalDevice)
{
    LogicalDevice = std::move(logicalDevice);

    const auto result = vkCreateGraphicsPipelines(LogicalDevice->GetRaw(),
                                                  VK_NULL_HANDLE,
                                                  1,
                                                  nullptr, // TODO: Change this
                                                  nullptr,
                                                  &InternalPipeline);
    if (result != VK_SUCCESS)
        throw std::runtime_error("Vulkan rasterization pipeline creation failed!");
}

VulkanRasterizationPipeline::~VulkanRasterizationPipeline()
{
    if (InternalPipeline != VK_NULL_HANDLE)
        vkDestroyPipeline(LogicalDevice->GetRaw(), InternalPipeline, nullptr);
}

VkPipeline VulkanRasterizationPipeline::GetRaw() const
{
    return InternalPipeline;
}
