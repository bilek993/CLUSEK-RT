//
// Created by jbili on 19.03.2021.
//

#ifndef CLUSEK_RT_CONFIGDATA_H
#define CLUSEK_RT_CONFIGDATA_H

#include <string>

#include "generators/SerializationMacros.h"

SERIALIZE_OBJECT(ConfigData)
struct ConfigData final
{
    SERIALIZE_FIELD(LoggerPath, std::string)
    std::string LoggerPath{};

    SERIALIZE_FIELD(LoggerLevel, int)
    int LoggerLevel = 0;

    SERIALIZE_FIELD(EnableLoggingToConsole, bool)
    bool EnableLoggingToConsole = false;

    SERIALIZE_FIELD(EnableLoggingToFile, bool)
    bool EnableLoggingToFile = false;

    SERIALIZE_FIELD(ShowMessageBoxOnError, bool)
    bool ShowMessageBoxOnError = true;

    SERIALIZE_FIELD(TextEnglishPath, std::string)
    std::string TextEnglishPath{};

    SERIALIZE_FIELD(TextPolishPath, std::string)
    std::string TextPolishPath{};

    SERIALIZE_FIELD(TextDefaultLanguageId, std::string)
    std::string TextDefaultLanguageId = "E";

    SERIALIZE_FIELD(ApplicationName, std::string)
    std::string ApplicationName = "Unnamed Project";

    SERIALIZE_FIELD(ApplicationVersion, std::string)
    std::string ApplicationVersion = "1.0.0";

    SERIALIZE_FIELD(WindowResizable, bool)
    bool WindowResizable = false;

    SERIALIZE_FIELD(WindowClosableWithX, bool)
    bool WindowClosableWithX = true;

    SERIALIZE_FIELD(WindowedMode, bool)
    bool WindowedMode = true;

    SERIALIZE_FIELD(WindowWidth, int)
    int WindowWidth = 800;

    SERIALIZE_FIELD(WindowHeight, int)
    int WindowHeight = 600;

    SERIALIZE_FIELD(EnableVulkanValidationLayers, bool)
    bool EnableVulkanValidationLayers = true;

    SERIALIZE_FIELD(CheckVulkanBufferMemoryBeforeMapping, bool)
    bool CheckVulkanBufferMemoryBeforeMapping = false;

    SERIALIZE_FIELD(VulkanRequireDiscreteDevice, bool)
    bool VulkanRequireDiscreteDevice = true;

    SERIALIZE_FIELD(VulkanPhysicalDeviceRequireRobustBufferAccess, bool)
    bool VulkanPhysicalDeviceRequireRobustBufferAccess = false;

    SERIALIZE_FIELD(VulkanPhysicalDeviceRequireFullDrawIndexUint32, bool)
    bool VulkanPhysicalDeviceRequireFullDrawIndexUint32 = false;

    SERIALIZE_FIELD(VulkanPhysicalDeviceRequireImageCubeArray, bool)
    bool VulkanPhysicalDeviceRequireImageCubeArray = false;

    SERIALIZE_FIELD(VulkanPhysicalDeviceRequireIndependentBlend, bool)
    bool VulkanPhysicalDeviceRequireIndependentBlend = false;

    SERIALIZE_FIELD(VulkanPhysicalDeviceRequireGeometryShader, bool)
    bool VulkanPhysicalDeviceRequireGeometryShader = false;

    SERIALIZE_FIELD(VulkanPhysicalDeviceRequireTessellationShader, bool)
    bool VulkanPhysicalDeviceRequireTessellationShader = false;

    SERIALIZE_FIELD(VulkanPhysicalDeviceRequireSampleRateShading, bool)
    bool VulkanPhysicalDeviceRequireSampleRateShading = false;

    SERIALIZE_FIELD(VulkanPhysicalDeviceRequireDualSrcBlend, bool)
    bool VulkanPhysicalDeviceRequireDualSrcBlend = false;

    SERIALIZE_FIELD(VulkanPhysicalDeviceRequireLogicOp, bool)
    bool VulkanPhysicalDeviceRequireLogicOp = false;

    SERIALIZE_FIELD(VulkanPhysicalDeviceRequireMultiDrawIndirect, bool)
    bool VulkanPhysicalDeviceRequireMultiDrawIndirect = false;

    SERIALIZE_FIELD(VulkanPhysicalDeviceRequireDrawIndirectFirstInstance, bool)
    bool VulkanPhysicalDeviceRequireDrawIndirectFirstInstance = false;

    SERIALIZE_FIELD(VulkanPhysicalDeviceRequireDepthClamp, bool)
    bool VulkanPhysicalDeviceRequireDepthClamp = false;

    SERIALIZE_FIELD(VulkanPhysicalDeviceRequireDepthBiasClamp, bool)
    bool VulkanPhysicalDeviceRequireDepthBiasClamp = false;

    SERIALIZE_FIELD(VulkanPhysicalDeviceRequireFillModeNonSolid, bool)
    bool VulkanPhysicalDeviceRequireFillModeNonSolid = false;

    SERIALIZE_FIELD(VulkanPhysicalDeviceRequireDepthBounds, bool)
    bool VulkanPhysicalDeviceRequireDepthBounds = false;

    SERIALIZE_FIELD(VulkanPhysicalDeviceRequireWideLines, bool)
    bool VulkanPhysicalDeviceRequireWideLines = false;

    SERIALIZE_FIELD(VulkanPhysicalDeviceRequireLargePoints, bool)
    bool VulkanPhysicalDeviceRequireLargePoints = false;

    SERIALIZE_FIELD(VulkanPhysicalDeviceRequireAlphaToOne, bool)
    bool VulkanPhysicalDeviceRequireAlphaToOne = false;

    SERIALIZE_FIELD(VulkanPhysicalDeviceRequireMultiViewport, bool)
    bool VulkanPhysicalDeviceRequireMultiViewport = false;

    SERIALIZE_FIELD(VulkanPhysicalDeviceRequireSamplerAnisotropy, bool)
    bool VulkanPhysicalDeviceRequireSamplerAnisotropy = false;

    SERIALIZE_FIELD(VulkanPhysicalDeviceRequireTextureCompressionETC2, bool)
    bool VulkanPhysicalDeviceRequireTextureCompressionETC2 = false;

    SERIALIZE_FIELD(VulkanPhysicalDeviceRequireTextureCompressionASTC_LDR, bool)
    bool VulkanPhysicalDeviceRequireTextureCompressionASTC_LDR = false;

    SERIALIZE_FIELD(VulkanPhysicalDeviceRequireTextureCompressionBC, bool)
    bool VulkanPhysicalDeviceRequireTextureCompressionBC = false;

    SERIALIZE_FIELD(VulkanPhysicalDeviceRequireOcclusionQueryPrecise, bool)
    bool VulkanPhysicalDeviceRequireOcclusionQueryPrecise = false;

    SERIALIZE_FIELD(VulkanPhysicalDeviceRequirePipelineStatisticsQuery, bool)
    bool VulkanPhysicalDeviceRequirePipelineStatisticsQuery = false;

    SERIALIZE_FIELD(VulkanPhysicalDeviceRequireVertexPipelineStoresAndAtomics, bool)
    bool VulkanPhysicalDeviceRequireVertexPipelineStoresAndAtomics = false;

    SERIALIZE_FIELD(VulkanPhysicalDeviceRequireFragmentStoresAndAtomics, bool)
    bool VulkanPhysicalDeviceRequireFragmentStoresAndAtomics = false;

    SERIALIZE_FIELD(VulkanPhysicalDeviceRequireShaderTessellationAndGeometryPointSize, bool)
    bool VulkanPhysicalDeviceRequireShaderTessellationAndGeometryPointSize = false;

    SERIALIZE_FIELD(VulkanPhysicalDeviceRequireShaderImageGatherExtended, bool)
    bool VulkanPhysicalDeviceRequireShaderImageGatherExtended = false;

    SERIALIZE_FIELD(VulkanPhysicalDeviceRequireShaderStorageImageExtendedFormats, bool)
    bool VulkanPhysicalDeviceRequireShaderStorageImageExtendedFormats = false;

    SERIALIZE_FIELD(VulkanPhysicalDeviceRequireShaderStorageImageMultisample, bool)
    bool VulkanPhysicalDeviceRequireShaderStorageImageMultisample = false;

    SERIALIZE_FIELD(VulkanPhysicalDeviceRequireShaderStorageImageReadWithoutFormat, bool)
    bool VulkanPhysicalDeviceRequireShaderStorageImageReadWithoutFormat = false;

    SERIALIZE_FIELD(VulkanPhysicalDeviceRequireShaderStorageImageWriteWithoutFormat, bool)
    bool VulkanPhysicalDeviceRequireShaderStorageImageWriteWithoutFormat = false;

    SERIALIZE_FIELD(VulkanPhysicalDeviceRequireShaderUniformBufferArrayDynamicIndexing, bool)
    bool VulkanPhysicalDeviceRequireShaderUniformBufferArrayDynamicIndexing = false;

    SERIALIZE_FIELD(VulkanPhysicalDeviceRequireShaderSampledImageArrayDynamicIndexing, bool)
    bool VulkanPhysicalDeviceRequireShaderSampledImageArrayDynamicIndexing = false;

    SERIALIZE_FIELD(VulkanPhysicalDeviceRequireShaderStorageBufferArrayDynamicIndexing, bool)
    bool VulkanPhysicalDeviceRequireShaderStorageBufferArrayDynamicIndexing = false;

    SERIALIZE_FIELD(VulkanPhysicalDeviceRequireShaderStorageImageArrayDynamicIndexing, bool)
    bool VulkanPhysicalDeviceRequireShaderStorageImageArrayDynamicIndexing = false;

    SERIALIZE_FIELD(VulkanPhysicalDeviceRequireShaderClipDistance, bool)
    bool VulkanPhysicalDeviceRequireShaderClipDistance = false;

    SERIALIZE_FIELD(VulkanPhysicalDeviceRequireShaderCullDistance, bool)
    bool VulkanPhysicalDeviceRequireShaderCullDistance = false;

    SERIALIZE_FIELD(VulkanPhysicalDeviceRequireShaderFloat64, bool)
    bool VulkanPhysicalDeviceRequireShaderFloat64 = false;

    SERIALIZE_FIELD(VulkanPhysicalDeviceRequireShaderInt64, bool)
    bool VulkanPhysicalDeviceRequireShaderInt64 = false;

    SERIALIZE_FIELD(VulkanPhysicalDeviceRequireShaderInt16, bool)
    bool VulkanPhysicalDeviceRequireShaderInt16 = false;

    SERIALIZE_FIELD(VulkanPhysicalDeviceRequireShaderResourceResidency, bool)
    bool VulkanPhysicalDeviceRequireShaderResourceResidency = false;

    SERIALIZE_FIELD(VulkanPhysicalDeviceRequireShaderResourceMinLod, bool)
    bool VulkanPhysicalDeviceRequireShaderResourceMinLod = false;

    SERIALIZE_FIELD(VulkanPhysicalDeviceRequireSparseBinding, bool)
    bool VulkanPhysicalDeviceRequireSparseBinding = false;

    SERIALIZE_FIELD(VulkanPhysicalDeviceRequireSparseResidencyBuffer, bool)
    bool VulkanPhysicalDeviceRequireSparseResidencyBuffer = false;

    SERIALIZE_FIELD(VulkanPhysicalDeviceRequireSparseResidencyImage2D, bool)
    bool VulkanPhysicalDeviceRequireSparseResidencyImage2D = false;

    SERIALIZE_FIELD(VulkanPhysicalDeviceRequireSparseResidencyImage3D, bool)
    bool VulkanPhysicalDeviceRequireSparseResidencyImage3D = false;

    SERIALIZE_FIELD(VulkanPhysicalDeviceRequireSparseResidency2Samples, bool)
    bool VulkanPhysicalDeviceRequireSparseResidency2Samples = false;

    SERIALIZE_FIELD(VulkanPhysicalDeviceRequireSparseResidency4Samples, bool)
    bool VulkanPhysicalDeviceRequireSparseResidency4Samples = false;

    SERIALIZE_FIELD(VulkanPhysicalDeviceRequireSparseResidency8Samples, bool)
    bool VulkanPhysicalDeviceRequireSparseResidency8Samples = false;

    SERIALIZE_FIELD(VulkanPhysicalDeviceRequireSparseResidency16Samples, bool)
    bool VulkanPhysicalDeviceRequireSparseResidency16Samples = false;

    SERIALIZE_FIELD(VulkanPhysicalDeviceRequireSparseResidencyAliased, bool)
    bool VulkanPhysicalDeviceRequireSparseResidencyAliased = false;

    SERIALIZE_FIELD(VulkanPhysicalDeviceRequireVariableMultisampleRate, bool)
    bool VulkanPhysicalDeviceRequireVariableMultisampleRate = false;

    SERIALIZE_FIELD(VulkanPhysicalDeviceRequireInheritedQueries, bool)
    bool VulkanPhysicalDeviceRequireInheritedQueries = false;
};

#endif //CLUSEK_RT_CONFIGDATA_H
