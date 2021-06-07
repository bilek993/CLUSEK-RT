//
// Created by jbili on 14.04.2021.
//

#include "DeviceRequiredFeatures.h"

VkPhysicalDeviceFeatures DeviceRequiredFeatures::FromConfig(const ConfigData& configurationData)
{
    VkPhysicalDeviceFeatures requiredFeatures{};
    requiredFeatures.robustBufferAccess = configurationData.VulkanPhysicalDeviceRequireRobustBufferAccess;
    requiredFeatures.robustBufferAccess = configurationData.VulkanPhysicalDeviceRequireFullDrawIndexUint32;
    requiredFeatures.imageCubeArray = configurationData.VulkanPhysicalDeviceRequireImageCubeArray;
    requiredFeatures.independentBlend = configurationData.VulkanPhysicalDeviceRequireIndependentBlend;
    requiredFeatures.geometryShader = configurationData.VulkanPhysicalDeviceRequireGeometryShader;
    requiredFeatures.tessellationShader = configurationData.VulkanPhysicalDeviceRequireTessellationShader;
    requiredFeatures.sampleRateShading = configurationData.VulkanPhysicalDeviceRequireSampleRateShading;
    requiredFeatures.dualSrcBlend = configurationData.VulkanPhysicalDeviceRequireDualSrcBlend;
    requiredFeatures.logicOp = configurationData.VulkanPhysicalDeviceRequireLogicOp;
    requiredFeatures.multiDrawIndirect = configurationData.VulkanPhysicalDeviceRequireMultiDrawIndirect;
    requiredFeatures.drawIndirectFirstInstance = configurationData.VulkanPhysicalDeviceRequireDrawIndirectFirstInstance;
    requiredFeatures.depthClamp = configurationData.VulkanPhysicalDeviceRequireDepthClamp;
    requiredFeatures.depthBiasClamp = configurationData.VulkanPhysicalDeviceRequireDepthBiasClamp;
    requiredFeatures.fillModeNonSolid = configurationData.VulkanPhysicalDeviceRequireFillModeNonSolid;
    requiredFeatures.depthBounds = configurationData.VulkanPhysicalDeviceRequireDepthBounds;
    requiredFeatures.wideLines = configurationData.VulkanPhysicalDeviceRequireWideLines;
    requiredFeatures.largePoints = configurationData.VulkanPhysicalDeviceRequireLargePoints;
    requiredFeatures.alphaToOne = configurationData.VulkanPhysicalDeviceRequireAlphaToOne;
    requiredFeatures.multiViewport = configurationData.VulkanPhysicalDeviceRequireMultiViewport;
    requiredFeatures.samplerAnisotropy = configurationData.VulkanPhysicalDeviceRequireSamplerAnisotropy;
    requiredFeatures.textureCompressionETC2 = configurationData.VulkanPhysicalDeviceRequireTextureCompressionETC2;
    requiredFeatures.textureCompressionASTC_LDR = configurationData.VulkanPhysicalDeviceRequireTextureCompressionASTC_LDR;
    requiredFeatures.textureCompressionBC = configurationData.VulkanPhysicalDeviceRequireTextureCompressionBC;
    requiredFeatures.occlusionQueryPrecise = configurationData.VulkanPhysicalDeviceRequireOcclusionQueryPrecise;
    requiredFeatures.pipelineStatisticsQuery = configurationData.VulkanPhysicalDeviceRequirePipelineStatisticsQuery;
    requiredFeatures.vertexPipelineStoresAndAtomics = configurationData.VulkanPhysicalDeviceRequireVertexPipelineStoresAndAtomics;
    requiredFeatures.fragmentStoresAndAtomics = configurationData.VulkanPhysicalDeviceRequireFragmentStoresAndAtomics;
    requiredFeatures.shaderTessellationAndGeometryPointSize = configurationData.VulkanPhysicalDeviceRequireShaderTessellationAndGeometryPointSize;
    requiredFeatures.shaderImageGatherExtended = configurationData.VulkanPhysicalDeviceRequireShaderImageGatherExtended;
    requiredFeatures.shaderStorageImageExtendedFormats = configurationData.VulkanPhysicalDeviceRequireShaderStorageImageExtendedFormats;
    requiredFeatures.shaderStorageImageMultisample = configurationData.VulkanPhysicalDeviceRequireShaderStorageImageMultisample;
    requiredFeatures.shaderStorageImageReadWithoutFormat = configurationData.VulkanPhysicalDeviceRequireShaderStorageImageReadWithoutFormat;
    requiredFeatures.shaderStorageImageWriteWithoutFormat = configurationData.VulkanPhysicalDeviceRequireShaderStorageImageWriteWithoutFormat;
    requiredFeatures.shaderUniformBufferArrayDynamicIndexing = configurationData.VulkanPhysicalDeviceRequireShaderUniformBufferArrayDynamicIndexing;
    requiredFeatures.shaderSampledImageArrayDynamicIndexing = configurationData.VulkanPhysicalDeviceRequireShaderSampledImageArrayDynamicIndexing;
    requiredFeatures.shaderStorageBufferArrayDynamicIndexing = configurationData.VulkanPhysicalDeviceRequireShaderStorageBufferArrayDynamicIndexing;
    requiredFeatures.shaderStorageImageArrayDynamicIndexing = configurationData.VulkanPhysicalDeviceRequireShaderStorageImageArrayDynamicIndexing;
    requiredFeatures.shaderClipDistance = configurationData.VulkanPhysicalDeviceRequireShaderClipDistance;
    requiredFeatures.shaderCullDistance = configurationData.VulkanPhysicalDeviceRequireShaderCullDistance;
    requiredFeatures.shaderFloat64 = configurationData.VulkanPhysicalDeviceRequireShaderFloat64;
    requiredFeatures.shaderInt64 = configurationData.VulkanPhysicalDeviceRequireShaderInt64;
    requiredFeatures.shaderInt16 = configurationData.VulkanPhysicalDeviceRequireShaderInt16;
    requiredFeatures.shaderResourceResidency = configurationData.VulkanPhysicalDeviceRequireShaderResourceResidency;
    requiredFeatures.shaderResourceMinLod = configurationData.VulkanPhysicalDeviceRequireShaderResourceMinLod;
    requiredFeatures.sparseBinding = configurationData.VulkanPhysicalDeviceRequireSparseBinding;
    requiredFeatures.sparseResidencyBuffer = configurationData.VulkanPhysicalDeviceRequireSparseResidencyBuffer;
    requiredFeatures.sparseResidencyImage2D = configurationData.VulkanPhysicalDeviceRequireSparseResidencyImage2D;
    requiredFeatures.sparseResidencyImage3D = configurationData.VulkanPhysicalDeviceRequireSparseResidencyImage3D;
    requiredFeatures.sparseResidency2Samples = configurationData.VulkanPhysicalDeviceRequireSparseResidency2Samples;
    requiredFeatures.sparseResidency4Samples = configurationData.VulkanPhysicalDeviceRequireSparseResidency4Samples;
    requiredFeatures.sparseResidency8Samples = configurationData.VulkanPhysicalDeviceRequireSparseResidency8Samples;
    requiredFeatures.sparseResidency16Samples = configurationData.VulkanPhysicalDeviceRequireSparseResidency16Samples;
    requiredFeatures.sparseResidencyAliased = configurationData.VulkanPhysicalDeviceRequireSparseResidencyAliased;
    requiredFeatures.variableMultisampleRate = configurationData.VulkanPhysicalDeviceRequireVariableMultisampleRate;
    requiredFeatures.inheritedQueries = configurationData.VulkanPhysicalDeviceRequireInheritedQueries;

    return requiredFeatures;
}
