//
// Created by jbili on 15.06.2021.
//

#ifndef CLUSEK_RT_VULKANRASTERIZATIONPIPELINE_H
#define CLUSEK_RT_VULKANRASTERIZATIONPIPELINE_H

#include <vulkan/vulkan.h>

#include "VulkanLogicalDevice.h"

class VulkanRasterizationPipeline final
{
public:
    VulkanRasterizationPipeline(std::shared_ptr<VulkanLogicalDevice> logicalDevice,
                                const VkPipelineCache& pipelineCache,
                                const std::vector<VkPipelineShaderStageCreateInfo>& shaderStages,
                                const VkPipelineVertexInputStateCreateInfo& vertexInputState,
                                const VkPipelineInputAssemblyStateCreateInfo& inputAssemblyState,
                                const VkPipelineViewportStateCreateInfo& constantViewportState,
                                bool tesselationEnabled,
                                const VkPipelineTessellationStateCreateInfo& tessellationState,
                                const VkPipelineRasterizationStateCreateInfo& rasterizationState,
                                const VkPipelineMultisampleStateCreateInfo& multisampleState,
                                const VkPipelineDepthStencilStateCreateInfo& depthStencilState,
                                const VkPipelineColorBlendStateCreateInfo& colorBlendState,
                                const VkPipelineDynamicStateCreateInfo& dynamicState,
                                const VkPipelineLayout& pipelineLayout,
                                const VkRenderPass& renderPass,
                                uint32_t subpassIndex);
    ~VulkanRasterizationPipeline();
    VulkanRasterizationPipeline(const VulkanRasterizationPipeline& other) = delete;
    VulkanRasterizationPipeline(VulkanRasterizationPipeline&& other) noexcept = delete;
    VulkanRasterizationPipeline& operator=(const VulkanRasterizationPipeline& other) = delete;
    VulkanRasterizationPipeline& operator=(VulkanRasterizationPipeline&& other) noexcept = delete;

    [[nodiscard]] VkPipeline GetRaw() const;

private:
    VkPipeline InternalPipeline = VK_NULL_HANDLE;

    std::shared_ptr<VulkanLogicalDevice> LogicalDevice;
};


#endif //CLUSEK_RT_VULKANRASTERIZATIONPIPELINE_H
