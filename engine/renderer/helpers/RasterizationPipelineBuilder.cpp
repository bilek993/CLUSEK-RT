//
// Created by jbili on 02.07.2021.
//

#include "RasterizationPipelineBuilder.h"

#include "../../common/debug/Logger.h"

RasterizationPipelineBuilder::RasterizationPipelineBuilder()
{
    InputAssemblyState.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    InputAssemblyState.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    InputAssemblyState.primitiveRestartEnable = VK_FALSE;

    ConstantViewportsEnabled = false;
    DynamicViewportEnabled = false;

    TesselationEnabled = false;

    TessellationState.sType = VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_STATE_CREATE_INFO;
    TessellationState.patchControlPoints = 4;

    RasterizationState.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    RasterizationState.depthClampEnable = VK_FALSE;
    RasterizationState.rasterizerDiscardEnable = VK_FALSE;
    RasterizationState.polygonMode = VK_POLYGON_MODE_FILL;
    RasterizationState.lineWidth = 1.0F;
    RasterizationState.cullMode = VK_CULL_MODE_NONE;
    RasterizationState.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
    RasterizationState.depthBiasEnable = VK_FALSE;
    RasterizationState.depthBiasConstantFactor = 0.0f;
    RasterizationState.depthBiasClamp = 0.0f;
    RasterizationState.depthBiasSlopeFactor = 0.0f;

    MultisampleState.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    MultisampleState.sampleShadingEnable = VK_FALSE;
    MultisampleState.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
    MultisampleState.minSampleShading = 0.2f;
    MultisampleState.pSampleMask = nullptr;
    MultisampleState.alphaToCoverageEnable = VK_FALSE;
    MultisampleState.alphaToOneEnable = VK_FALSE;

    DepthStencilState.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
    DepthStencilState.depthTestEnable = VK_FALSE;
    DepthStencilState.depthWriteEnable = VK_FALSE;
    DepthStencilState.depthCompareOp = VK_COMPARE_OP_LESS;
    DepthStencilState.depthBoundsTestEnable = VK_FALSE;
    DepthStencilState.minDepthBounds = 0.0f;
    DepthStencilState.maxDepthBounds = 1.0f;
    DepthStencilState.stencilTestEnable = VK_FALSE;
    DepthStencilState.front = {};
    DepthStencilState.back = {};

    ColorBlendState.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    ColorBlendState.logicOpEnable = VK_FALSE;
    ColorBlendState.logicOp = VK_LOGIC_OP_COPY;
    ColorBlendState.blendConstants[0] = 0.0f;
    ColorBlendState.blendConstants[1] = 0.0f;
    ColorBlendState.blendConstants[2] = 0.0f;
    ColorBlendState.blendConstants[3] = 0.0f;
}

RasterizationPipelineBuilder&
RasterizationPipelineBuilder::SetLogicalDevice(std::shared_ptr<VulkanLogicalDevice> logicalDevice)
{
    LogicalDevice = std::move(logicalDevice);
    return *this;
}

RasterizationPipelineBuilder& RasterizationPipelineBuilder::AddShaderStage(const VulkanShaderModule& shaderModule)
{
    ShaderStages.emplace_back(shaderModule.GenerateShaderStageCreateInfo());
    return *this;
}

RasterizationPipelineBuilder&
RasterizationPipelineBuilder::AddShaderStage(const VkPipelineShaderStageCreateInfo& shaderStage)
{
    ShaderStages.emplace_back(shaderStage);
    return *this;
}

RasterizationPipelineBuilder&
RasterizationPipelineBuilder::AddShaderStage(const std::vector<VkPipelineShaderStageCreateInfo>& shaderStages)
{
    ShaderStages.insert(ShaderStages.end(), shaderStages.begin(), shaderStages.end());
    return *this;
}

RasterizationPipelineBuilder&
RasterizationPipelineBuilder::AddVertexInput(const VkVertexInputBindingDescription& inputBindingDescription,
                                             const std::vector<VkVertexInputAttributeDescription>& inputAttributeDescription)
{
    VertexInputBindingDescriptions.emplace_back(inputBindingDescription);
    VertexInputAttributeDescriptions.insert(VertexInputAttributeDescriptions.end(),
                                            inputAttributeDescription.begin(),
                                            inputAttributeDescription.end());
    return *this;
}

RasterizationPipelineBuilder& RasterizationPipelineBuilder::SetInputTopology(const VkPrimitiveTopology topology)
{
    InputAssemblyState.topology = topology;
    return *this;
}

RasterizationPipelineBuilder& RasterizationPipelineBuilder::EnableInputPrimitiveRestart()
{
    InputAssemblyState.primitiveRestartEnable = true;
    return *this;
}

RasterizationPipelineBuilder& RasterizationPipelineBuilder::EnableConstantViewport()
{
    if (DynamicViewportEnabled)
        LOG_ERROR("Dynamic and constant viewport may lead to problems!");

    ConstantViewportsEnabled = true;
    return *this;
}

RasterizationPipelineBuilder& RasterizationPipelineBuilder::EnableDynamicViewport()
{
    if (ConstantViewportsEnabled)
        LOG_ERROR("Dynamic and constant viewport may lead to problems!");

    DynamicStates.emplace_back(VK_DYNAMIC_STATE_VIEWPORT);
    DynamicStates.emplace_back(VK_DYNAMIC_STATE_SCISSOR);

    DynamicViewportEnabled = true;
    return *this;
}

RasterizationPipelineBuilder& RasterizationPipelineBuilder::AddConstantViewportAndScissor(const VkViewport& viewport,
                                                                                          const VkRect2D& scissor)
{
    if (!ConstantViewportsEnabled)
        LOG_ERROR("Constant viewports are not enabled");

    Viewports.emplace_back(viewport);
    ViewportScissors.emplace_back(scissor);
    return *this;
}

RasterizationPipelineBuilder& RasterizationPipelineBuilder::AddDynamicViewportAndScissor()
{
    if (!ConstantViewportsEnabled)
        LOG_ERROR("Dynamic viewports are not enabled");

    Viewports.emplace_back(VkViewport{});
    ViewportScissors.emplace_back(VkRect2D{});
    return *this;
}

RasterizationPipelineBuilder& RasterizationPipelineBuilder::EnableTesselation()
{
    TesselationEnabled = true;
    return *this;
}

RasterizationPipelineBuilder& RasterizationPipelineBuilder::SetTesselationPatchControlPoints(const uint32_t count)
{
    TessellationState.patchControlPoints = count;
    return *this;
}

RasterizationPipelineBuilder& RasterizationPipelineBuilder::EnableDepthClamping()
{
    RasterizationState.depthClampEnable = true;
    return *this;
}

RasterizationPipelineBuilder& RasterizationPipelineBuilder::EnableDiscardingAllResultByRasterizer()
{
    RasterizationState.rasterizerDiscardEnable = true;
    return *this;
}

RasterizationPipelineBuilder& RasterizationPipelineBuilder::SetPolygonMode(const VkPolygonMode mode)
{
    RasterizationState.polygonMode = mode;
    return *this;
}

RasterizationPipelineBuilder& RasterizationPipelineBuilder::SetLineWidth(const float width)
{
    RasterizationState.lineWidth = width;
    return *this;
}

RasterizationPipelineBuilder& RasterizationPipelineBuilder::SetCullMode(const VkCullModeFlags flags)
{
    RasterizationState.cullMode = flags;
    return *this;
}

RasterizationPipelineBuilder& RasterizationPipelineBuilder::SetFrontFace(const VkFrontFace frontFace)
{
    RasterizationState.frontFace = frontFace;
    return *this;
}

RasterizationPipelineBuilder& RasterizationPipelineBuilder::EnableDepthBias()
{
    RasterizationState.depthBiasEnable = true;
    return *this;
}

RasterizationPipelineBuilder& RasterizationPipelineBuilder::SetDepthBiasConstantFactor(const float constantFactor)
{
    RasterizationState.depthBiasConstantFactor = constantFactor;
    return *this;
}

RasterizationPipelineBuilder& RasterizationPipelineBuilder::SetDepthBiasClamp(const float clamp)
{
    RasterizationState.depthBiasClamp = clamp;
    return *this;
}

RasterizationPipelineBuilder& RasterizationPipelineBuilder::SetDepthBiasSlopeFactor(const float slopeFactor)
{
    RasterizationState.depthBiasSlopeFactor = slopeFactor;
    return *this;
}

RasterizationPipelineBuilder& RasterizationPipelineBuilder::EnableSampleShading()
{
    MultisampleState.sampleShadingEnable = true;
    return *this;
}

RasterizationPipelineBuilder& RasterizationPipelineBuilder::SetRasterizationSamples(const VkSampleCountFlagBits samples)
{
    MultisampleState.rasterizationSamples = samples;
    return *this;
}

RasterizationPipelineBuilder& RasterizationPipelineBuilder::SetMinimalSampleShading(const float minSampleShading)
{
    MultisampleState.minSampleShading = minSampleShading;
    return *this;
}

RasterizationPipelineBuilder& RasterizationPipelineBuilder::SetSampleMask(const VkSampleMask& mask)
{
    MultisampleState.pSampleMask = &mask;
    return *this;
}

RasterizationPipelineBuilder& RasterizationPipelineBuilder::EnableAlphaToCoverage()
{
    MultisampleState.alphaToCoverageEnable = true;
    return *this;
}

RasterizationPipelineBuilder& RasterizationPipelineBuilder::EnableAlphaToOne()
{
    MultisampleState.alphaToOneEnable = true;
    return *this;
}

RasterizationPipelineBuilder& RasterizationPipelineBuilder::EnableDepthTesting()
{
    DepthStencilState.depthTestEnable = true;
    return *this;
}

RasterizationPipelineBuilder& RasterizationPipelineBuilder::EnableDepthWriting()
{
    DepthStencilState.depthWriteEnable = true;
    return *this;
}

RasterizationPipelineBuilder& RasterizationPipelineBuilder::SetDepthCompareOperator(const VkCompareOp compareOperator)
{
    DepthStencilState.depthCompareOp = compareOperator;
    return *this;
}

RasterizationPipelineBuilder& RasterizationPipelineBuilder::EnableDepthBoundTesting()
{
    DepthStencilState.depthBoundsTestEnable = true;
    return *this;
}

RasterizationPipelineBuilder& RasterizationPipelineBuilder::SetDepthBounds(const float minBound, const float maxBound)
{
    DepthStencilState.minDepthBounds = minBound;
    DepthStencilState.maxDepthBounds = maxBound;
    return *this;
}

RasterizationPipelineBuilder& RasterizationPipelineBuilder::EnableStencilTesting()
{
    DepthStencilState.stencilTestEnable = true;
    return *this;
}

RasterizationPipelineBuilder& RasterizationPipelineBuilder::SetDepthFrontParameters(const VkStencilOpState front)
{
    DepthStencilState.front = front;
    return *this;
}

RasterizationPipelineBuilder& RasterizationPipelineBuilder::SetDepthBackParameters(const VkStencilOpState back)
{
    DepthStencilState.back = back;
    return *this;
}

RasterizationPipelineBuilder&
RasterizationPipelineBuilder::AddBlendAttachmentWithDisabledBlending(VkColorComponentFlags colorWriteMask)
{

    VkPipelineColorBlendAttachmentState colorBlendAttachment{};
    colorBlendAttachment.colorWriteMask = colorWriteMask;
    colorBlendAttachment.blendEnable = VK_FALSE;

    BlendAttachmentStates.emplace_back(colorBlendAttachment);
    return *this;
}

RasterizationPipelineBuilder&
RasterizationPipelineBuilder::AddBlendAttachmentWithEnabledBlending(VkColorComponentFlags colorWriteMask,
                                                                    VkBlendFactor srcColorBlendFactor,
                                                                    VkBlendFactor dstColorBlendFactor,
                                                                    VkBlendOp colorBlendOp,
                                                                    VkBlendFactor srcAlphaBlendFactor,
                                                                    VkBlendFactor dstAlphaBlendFactor,
                                                                    VkBlendOp alphaBlendOp)
{
    VkPipelineColorBlendAttachmentState colorBlendAttachment{};
    colorBlendAttachment.colorWriteMask = colorWriteMask;
    colorBlendAttachment.blendEnable = VK_TRUE;
    colorBlendAttachment.srcColorBlendFactor = srcColorBlendFactor;
    colorBlendAttachment.dstColorBlendFactor = dstColorBlendFactor;
    colorBlendAttachment.colorBlendOp = colorBlendOp;
    colorBlendAttachment.srcAlphaBlendFactor = srcAlphaBlendFactor;
    colorBlendAttachment.dstAlphaBlendFactor = dstAlphaBlendFactor;
    colorBlendAttachment.alphaBlendOp = alphaBlendOp;

    BlendAttachmentStates.emplace_back(colorBlendAttachment);
    return *this;
}

RasterizationPipelineBuilder& RasterizationPipelineBuilder::EnableSecondBlending()
{
    ColorBlendState.logicOpEnable = true;
    return *this;
}

RasterizationPipelineBuilder& RasterizationPipelineBuilder::SetSecondBlendingLogicOperator(VkLogicOp logicOperator)
{
    ColorBlendState.logicOp = logicOperator;
    return *this;
}

RasterizationPipelineBuilder&
RasterizationPipelineBuilder::SetSecondBlendingConstants(std::array<float, 4> constantValues)
{
    std::move(constantValues.begin(), constantValues.end(), std::begin(ColorBlendState.blendConstants));
    return *this;
}

RasterizationPipelineBuilder&
RasterizationPipelineBuilder::SetPipelineLayout(const VulkanPipelineLayout& pipelineLayout)
{
    PipelineLayout = pipelineLayout.GetRaw();
    return *this;
}

RasterizationPipelineBuilder& RasterizationPipelineBuilder::SetRenderPass(const VulkanRenderPass& renderPass)
{
    RenderPass = renderPass.GetRaw();
    return *this;
}

RasterizationPipelineBuilder& RasterizationPipelineBuilder::SetSubpassIndex(const uint32_t index)
{
    SubpassIndex = index;
    return *this;
}

VulkanRasterizationPipeline RasterizationPipelineBuilder::Build() const
{
    if (LogicalDevice == nullptr)
        LOG_ERROR("Logical device must be passed to the builder!");

    VkPipelineVertexInputStateCreateInfo vertexInputStateCreateInfo{};
    vertexInputStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    vertexInputStateCreateInfo.vertexBindingDescriptionCount = VertexInputBindingDescriptions.size();
    vertexInputStateCreateInfo.vertexAttributeDescriptionCount = VertexInputAttributeDescriptions.size();
    vertexInputStateCreateInfo.pVertexBindingDescriptions = VertexInputBindingDescriptions.data();
    vertexInputStateCreateInfo.pVertexAttributeDescriptions = VertexInputAttributeDescriptions.data();

    VkPipelineViewportStateCreateInfo viewportState{};
    viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    viewportState.viewportCount = (ConstantViewportsEnabled | DynamicViewportEnabled) ? Viewports.size() : 0;
    viewportState.pViewports = ConstantViewportsEnabled ? Viewports.data() : nullptr;
    viewportState.scissorCount = (ConstantViewportsEnabled | DynamicViewportEnabled) ? ViewportScissors.size() : 0;
    viewportState.pScissors = ConstantViewportsEnabled ? ViewportScissors.data() : nullptr;

    VkPipelineDynamicStateCreateInfo dynamicState{};
    dynamicState.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
    dynamicState.dynamicStateCount = DynamicStates.size();
    dynamicState.pDynamicStates = DynamicStates.data();

    VkPipelineColorBlendStateCreateInfo colorBlendStateTmp = ColorBlendState;
    colorBlendStateTmp.attachmentCount = BlendAttachmentStates.size();
    colorBlendStateTmp.pAttachments = BlendAttachmentStates.data();

    return VulkanRasterizationPipeline(LogicalDevice,
                                       VkPipelineCache{},
                                       ShaderStages,
                                       vertexInputStateCreateInfo,
                                       InputAssemblyState,
                                       viewportState,
                                       TesselationEnabled,
                                       TessellationState,
                                       RasterizationState,
                                       MultisampleState,
                                       DepthStencilState,
                                       colorBlendStateTmp,
                                       dynamicState,
                                       PipelineLayout,
                                       RenderPass,
                                       SubpassIndex);
}
