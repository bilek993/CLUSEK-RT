//
// Created by jbili on 02.07.2021.
//

#ifndef CLUSEK_RT_RASTERIZATIONPIPELINEBUILDER_H
#define CLUSEK_RT_RASTERIZATIONPIPELINEBUILDER_H

#include <memory>
#include <vector>
#include <array>
#include <vulkan/vulkan.h>

#include "../core/VulkanRasterizationPipeline.h"
#include "../core/VulkanPipelineLayout.h"
#include "../core/VulkanRenderPass.h"
#include "../core/VulkanShaderModule.h"

class RasterizationPipelineBuilder final
{
public:
    RasterizationPipelineBuilder();

    RasterizationPipelineBuilder& SetLogicalDevice(std::shared_ptr<VulkanLogicalDevice> logicalDevice);

    RasterizationPipelineBuilder& AddShaderStage(const VulkanShaderModule& shaderModule);
    RasterizationPipelineBuilder& AddShaderStage(const VkPipelineShaderStageCreateInfo& shaderStage);
    RasterizationPipelineBuilder& AddShaderStage(const std::vector<VkPipelineShaderStageCreateInfo>& shaderStages);

    RasterizationPipelineBuilder& AddVertexInput(const VkVertexInputBindingDescription& inputBindingDescription,
                                                 const VkVertexInputAttributeDescription& inputAttributeDescription);

    RasterizationPipelineBuilder& SetInputTopology(VkPrimitiveTopology topology);
    RasterizationPipelineBuilder& EnableInputPrimitiveRestart();

    RasterizationPipelineBuilder& EnableConstantViewport();
    RasterizationPipelineBuilder& EnableDynamicViewport();
    RasterizationPipelineBuilder& AddConstantViewportAndScissor(const VkViewport& viewport, const VkRect2D& scissor);
    RasterizationPipelineBuilder& AddDynamicViewportAndScissor();

    RasterizationPipelineBuilder& EnableTesselation();
    RasterizationPipelineBuilder& SetTesselationPatchControlPoints(uint32_t count);

    RasterizationPipelineBuilder& EnableDepthClamping();
    RasterizationPipelineBuilder& EnableDiscardingAllResultByRasterizer();
    RasterizationPipelineBuilder& SetPolygonMode(VkPolygonMode mode);
    RasterizationPipelineBuilder& SetLineWidth(float width);
    RasterizationPipelineBuilder& SetCullMode(VkCullModeFlags flags);
    RasterizationPipelineBuilder& SetFrontFace(VkFrontFace frontFace);
    RasterizationPipelineBuilder& EnableDepthBias();
    RasterizationPipelineBuilder& SetDepthBiasConstantFactor(float constantFactor);
    RasterizationPipelineBuilder& SetDepthBiasClamp(float clamp);
    RasterizationPipelineBuilder& SetDepthBiasSlopeFactor(float slopeFactor);

    RasterizationPipelineBuilder& EnableSampleShading();
    RasterizationPipelineBuilder& SetRasterizationSamples(VkSampleCountFlagBits samples);
    RasterizationPipelineBuilder& SetMinimalSampleShading(float minSampleShading);
    RasterizationPipelineBuilder& SetSampleMask(const VkSampleMask& mask);
    RasterizationPipelineBuilder& EnableAlphaToCoverage();
    RasterizationPipelineBuilder& EnableAlphaToOne();

    RasterizationPipelineBuilder& EnableDepthTesting();
    RasterizationPipelineBuilder& EnableDepthWriting();
    RasterizationPipelineBuilder& SetDepthCompareOperator(VkCompareOp compareOperator);
    RasterizationPipelineBuilder& EnableDepthBoundTesting();
    RasterizationPipelineBuilder& SetDepthBounds(float minBound, float maxBound);
    RasterizationPipelineBuilder& EnableStencilTesting();
    RasterizationPipelineBuilder& SetDepthFrontParameters(VkStencilOpState front);
    RasterizationPipelineBuilder& SetDepthBackParameters(VkStencilOpState back);

    RasterizationPipelineBuilder& AddBlendAttachmentWithDisabledBlending(VkColorComponentFlags colorWriteMask);
    RasterizationPipelineBuilder& AddBlendAttachmentWithEnabledBlending(VkColorComponentFlags colorWriteMask,
                                                                        VkBlendFactor srcColorBlendFactor,
                                                                        VkBlendFactor dstColorBlendFactor,
                                                                        VkBlendOp colorBlendOp,
                                                                        VkBlendFactor srcAlphaBlendFactor,
                                                                        VkBlendFactor dstAlphaBlendFactor,
                                                                        VkBlendOp alphaBlendOp);
    RasterizationPipelineBuilder& EnableSecondBlending();
    RasterizationPipelineBuilder& SetSecondBlendingLogicOperator(VkLogicOp logicOperator);
    RasterizationPipelineBuilder& SetSecondBlendingConstants(std::array<float, 4> constantValues);

    RasterizationPipelineBuilder& SetPipelineLayout(const VulkanPipelineLayout& pipelineLayout);

    RasterizationPipelineBuilder& SetRenderPass(const VulkanRenderPass& renderPass);

    RasterizationPipelineBuilder& SetSubpassIndex(uint32_t index);

    [[nodiscard]] VulkanRasterizationPipeline Build() const;

private:
    std::shared_ptr<VulkanLogicalDevice> LogicalDevice = nullptr;
    std::vector<VkPipelineShaderStageCreateInfo> ShaderStages{};
    std::vector<VkVertexInputBindingDescription> VertexInputBindingDescriptions{};
    std::vector<VkVertexInputAttributeDescription> VertexInputAttributeDescriptions{};
    VkPipelineInputAssemblyStateCreateInfo InputAssemblyState{};
    bool ConstantViewportsEnabled;
    bool DynamicViewportEnabled;
    std::vector<VkViewport> Viewports{};
    std::vector<VkRect2D> ViewportScissors{};
    bool TesselationEnabled;
    VkPipelineTessellationStateCreateInfo TessellationState{};
    VkPipelineRasterizationStateCreateInfo RasterizationState{};
    VkPipelineMultisampleStateCreateInfo MultisampleState{};
    VkPipelineDepthStencilStateCreateInfo DepthStencilState{};
    std::vector<VkPipelineColorBlendAttachmentState> BlendAttachmentStates{};
    VkPipelineColorBlendStateCreateInfo ColorBlendState{};
    VkPipelineLayout PipelineLayout{};
    std::vector<VkDynamicState> DynamicStates{};
    VkRenderPass RenderPass{};
    uint32_t SubpassIndex = 0;
};


#endif //CLUSEK_RT_RASTERIZATIONPIPELINEBUILDER_H
