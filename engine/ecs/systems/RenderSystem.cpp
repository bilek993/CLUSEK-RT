//
// Created by jbili on 30.03.2021.
//

#include "RenderSystem.h"

#include "../../common/debug/Logger.h"

std::string RenderSystem::GetName()
{
    return "Render System";
}

void RenderSystem::OnStart()
{
    LOG_DEBUG("Preparing to create Vulkan Instance...");
    const auto vulkanInstanceRequiredExtensions = MainWindow->GetRequiredExtensions();
    Instance = std::make_shared<VulkanInstance>(ConfigurationData->EnableVulkanValidationLayers,
                                                ConfigurationData->ApplicationName,
                                                ConfigurationData->ApplicationVersion,
                                                vulkanInstanceRequiredExtensions);

    LOG_DEBUG("Preparing to create Vulkan Physical Device...");
    VkPhysicalDeviceFeatures physicalDeviceRequiredFeatures = GeneratePhysicalDeviceRequiredFeatures();
    PhysicalDevice = std::make_shared<VulkanPhysicalDevice>(Instance,
                                                            ConfigurationData->VulkanRequireDiscreteDevice,
                                                            physicalDeviceRequiredFeatures);
}

void RenderSystem::OnUpdate(float deltaTime)
{

}

VkPhysicalDeviceFeatures RenderSystem::GeneratePhysicalDeviceRequiredFeatures() const
{
    VkPhysicalDeviceFeatures requiredFeatures{};
    requiredFeatures.robustBufferAccess = ConfigurationData->VulkanPhysicalDeviceRequireRobustBufferAccess;
    requiredFeatures.robustBufferAccess = ConfigurationData->VulkanPhysicalDeviceRequireFullDrawIndexUint32;
    requiredFeatures.imageCubeArray = ConfigurationData->VulkanPhysicalDeviceRequireImageCubeArray;
    requiredFeatures.independentBlend = ConfigurationData->VulkanPhysicalDeviceRequireIndependentBlend;
    requiredFeatures.geometryShader = ConfigurationData->VulkanPhysicalDeviceRequireGeometryShader;
    requiredFeatures.tessellationShader = ConfigurationData->VulkanPhysicalDeviceRequireTessellationShader;
    requiredFeatures.sampleRateShading = ConfigurationData->VulkanPhysicalDeviceRequireSampleRateShading;
    requiredFeatures.dualSrcBlend = ConfigurationData->VulkanPhysicalDeviceRequireDualSrcBlend;
    requiredFeatures.logicOp = ConfigurationData->VulkanPhysicalDeviceRequireLogicOp;
    requiredFeatures.multiDrawIndirect = ConfigurationData->VulkanPhysicalDeviceRequireMultiDrawIndirect;
    requiredFeatures.drawIndirectFirstInstance = ConfigurationData->VulkanPhysicalDeviceRequireDrawIndirectFirstInstance;
    requiredFeatures.depthClamp = ConfigurationData->VulkanPhysicalDeviceRequireDepthClamp;
    requiredFeatures.depthBiasClamp = ConfigurationData->VulkanPhysicalDeviceRequireDepthBiasClamp;
    requiredFeatures.fillModeNonSolid = ConfigurationData->VulkanPhysicalDeviceRequireFillModeNonSolid;
    requiredFeatures.depthBounds = ConfigurationData->VulkanPhysicalDeviceRequireDepthBounds;
    requiredFeatures.wideLines = ConfigurationData->VulkanPhysicalDeviceRequireWideLines;
    requiredFeatures.largePoints = ConfigurationData->VulkanPhysicalDeviceRequireLargePoints;
    requiredFeatures.alphaToOne = ConfigurationData->VulkanPhysicalDeviceRequireAlphaToOne;
    requiredFeatures.multiViewport = ConfigurationData->VulkanPhysicalDeviceRequireMultiViewport;
    requiredFeatures.samplerAnisotropy = ConfigurationData->VulkanPhysicalDeviceRequireSamplerAnisotropy;
    requiredFeatures.textureCompressionETC2 = ConfigurationData->VulkanPhysicalDeviceRequireTextureCompressionETC2;
    requiredFeatures.textureCompressionASTC_LDR = ConfigurationData->VulkanPhysicalDeviceRequireTextureCompressionASTC_LDR;
    requiredFeatures.textureCompressionBC = ConfigurationData->VulkanPhysicalDeviceRequireTextureCompressionBC;
    requiredFeatures.occlusionQueryPrecise = ConfigurationData->VulkanPhysicalDeviceRequireOcclusionQueryPrecise;
    requiredFeatures.pipelineStatisticsQuery = ConfigurationData->VulkanPhysicalDeviceRequirePipelineStatisticsQuery;
    requiredFeatures.vertexPipelineStoresAndAtomics = ConfigurationData->VulkanPhysicalDeviceRequireVertexPipelineStoresAndAtomics;
    requiredFeatures.fragmentStoresAndAtomics = ConfigurationData->VulkanPhysicalDeviceRequireFragmentStoresAndAtomics;
    requiredFeatures.shaderTessellationAndGeometryPointSize = ConfigurationData->VulkanPhysicalDeviceRequireShaderTessellationAndGeometryPointSize;
    requiredFeatures.shaderImageGatherExtended = ConfigurationData->VulkanPhysicalDeviceRequireShaderImageGatherExtended;
    requiredFeatures.shaderStorageImageExtendedFormats = ConfigurationData->VulkanPhysicalDeviceRequireShaderStorageImageExtendedFormats;
    requiredFeatures.shaderStorageImageMultisample = ConfigurationData->VulkanPhysicalDeviceRequireShaderStorageImageMultisample;
    requiredFeatures.shaderStorageImageReadWithoutFormat = ConfigurationData->VulkanPhysicalDeviceRequireShaderStorageImageReadWithoutFormat;
    requiredFeatures.shaderStorageImageWriteWithoutFormat = ConfigurationData->VulkanPhysicalDeviceRequireShaderStorageImageWriteWithoutFormat;
    requiredFeatures.shaderUniformBufferArrayDynamicIndexing = ConfigurationData->VulkanPhysicalDeviceRequireShaderUniformBufferArrayDynamicIndexing;
    requiredFeatures.shaderSampledImageArrayDynamicIndexing = ConfigurationData->VulkanPhysicalDeviceRequireShaderSampledImageArrayDynamicIndexing;
    requiredFeatures.shaderStorageBufferArrayDynamicIndexing = ConfigurationData->VulkanPhysicalDeviceRequireShaderStorageBufferArrayDynamicIndexing;
    requiredFeatures.shaderStorageImageArrayDynamicIndexing = ConfigurationData->VulkanPhysicalDeviceRequireShaderStorageImageArrayDynamicIndexing;
    requiredFeatures.shaderClipDistance = ConfigurationData->VulkanPhysicalDeviceRequireShaderClipDistance;
    requiredFeatures.shaderCullDistance = ConfigurationData->VulkanPhysicalDeviceRequireShaderCullDistance;
    requiredFeatures.shaderFloat64 = ConfigurationData->VulkanPhysicalDeviceRequireShaderFloat64;
    requiredFeatures.shaderInt64 = ConfigurationData->VulkanPhysicalDeviceRequireShaderInt64;
    requiredFeatures.shaderInt16 = ConfigurationData->VulkanPhysicalDeviceRequireShaderInt16;
    requiredFeatures.shaderResourceResidency = ConfigurationData->VulkanPhysicalDeviceRequireShaderResourceResidency;
    requiredFeatures.shaderResourceMinLod = ConfigurationData->VulkanPhysicalDeviceRequireShaderResourceMinLod;
    requiredFeatures.sparseBinding = ConfigurationData->VulkanPhysicalDeviceRequireSparseBinding;
    requiredFeatures.sparseResidencyBuffer = ConfigurationData->VulkanPhysicalDeviceRequireSparseResidencyBuffer;
    requiredFeatures.sparseResidencyImage2D = ConfigurationData->VulkanPhysicalDeviceRequireSparseResidencyImage2D;
    requiredFeatures.sparseResidencyImage3D = ConfigurationData->VulkanPhysicalDeviceRequireSparseResidencyImage3D;
    requiredFeatures.sparseResidency2Samples = ConfigurationData->VulkanPhysicalDeviceRequireSparseResidency2Samples;
    requiredFeatures.sparseResidency4Samples = ConfigurationData->VulkanPhysicalDeviceRequireSparseResidency4Samples;
    requiredFeatures.sparseResidency8Samples = ConfigurationData->VulkanPhysicalDeviceRequireSparseResidency8Samples;
    requiredFeatures.sparseResidency16Samples = ConfigurationData->VulkanPhysicalDeviceRequireSparseResidency16Samples;
    requiredFeatures.sparseResidencyAliased = ConfigurationData->VulkanPhysicalDeviceRequireSparseResidencyAliased;
    requiredFeatures.variableMultisampleRate = ConfigurationData->VulkanPhysicalDeviceRequireVariableMultisampleRate;
    requiredFeatures.inheritedQueries = ConfigurationData->VulkanPhysicalDeviceRequireInheritedQueries;

    return requiredFeatures;
}
