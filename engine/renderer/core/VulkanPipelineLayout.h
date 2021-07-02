//
// Created by jbili on 28.06.2021.
//

#ifndef CLUSEK_RT_VULKANPIPELINELAYOUT_H
#define CLUSEK_RT_VULKANPIPELINELAYOUT_H

#include <memory>
#include <vulkan/vulkan.h>

#include "VulkanLogicalDevice.h"

class VulkanPipelineLayout final
{
public:
    VulkanPipelineLayout(std::shared_ptr<VulkanLogicalDevice> logicalDevice);
    ~VulkanPipelineLayout();
    VulkanPipelineLayout(const VulkanPipelineLayout& other) = delete;
    VulkanPipelineLayout(VulkanPipelineLayout&& other) noexcept = delete;
    VulkanPipelineLayout& operator=(const VulkanPipelineLayout& other) = delete;
    VulkanPipelineLayout& operator=(VulkanPipelineLayout&& other) noexcept = delete;

private:
    VkPipelineLayout InternalPipelineLayout = VK_NULL_HANDLE;
    std::shared_ptr<VulkanLogicalDevice> LogicalDevice;
};


#endif //CLUSEK_RT_VULKANPIPELINELAYOUT_H
