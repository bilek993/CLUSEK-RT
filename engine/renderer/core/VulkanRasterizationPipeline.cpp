//
// Created by jbili on 15.06.2021.
//

#include "VulkanRasterizationPipeline.h"

VulkanRasterizationPipeline::VulkanRasterizationPipeline(std::shared_ptr<VulkanLogicalDevice> logicalDevice,
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
                                                         uint32_t subpassIndex)
{
    LogicalDevice = std::move(logicalDevice);

    VkGraphicsPipelineCreateInfo pipelineCreateInfo{};
    pipelineCreateInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    pipelineCreateInfo.stageCount = shaderStages.size();
    pipelineCreateInfo.pStages = shaderStages.data();
    pipelineCreateInfo.pVertexInputState = &vertexInputState;
    pipelineCreateInfo.pInputAssemblyState = &inputAssemblyState;
    pipelineCreateInfo.pTessellationState = tesselationEnabled ? &tessellationState : nullptr;
    pipelineCreateInfo.pViewportState = &constantViewportState;
    pipelineCreateInfo.pRasterizationState = &rasterizationState;
    pipelineCreateInfo.pMultisampleState = &multisampleState;
    pipelineCreateInfo.pDepthStencilState = &depthStencilState;
    pipelineCreateInfo.pColorBlendState = &colorBlendState;
    pipelineCreateInfo.pDynamicState = nullptr;
    pipelineCreateInfo.layout = pipelineLayout;
    pipelineCreateInfo.renderPass = renderPass;
    pipelineCreateInfo.subpass = subpassIndex;

    const auto result = vkCreateGraphicsPipelines(LogicalDevice->GetRaw(),
                                                  pipelineCache,
                                                  1,
                                                  &pipelineCreateInfo,
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
