//
// Created by jbili on 07.04.2021.
//

#include "VulkanPhysicalDevice.h"

VulkanPhysicalDevice::VulkanPhysicalDevice(const std::shared_ptr<VulkanInstance> vulkanInstance,
                                           bool requireDiscretePhysicalDevice,
                                           const VkPhysicalDeviceFeatures& requiredFeatures)
{
    uint32_t deviceCount = 0;
    auto result = vkEnumeratePhysicalDevices(vulkanInstance->GetRaw(), &deviceCount, nullptr);
    if (result != VK_SUCCESS)
        throw std::runtime_error("Error enumerating physical devices!");

    if (deviceCount == 0)
        throw std::runtime_error("Zero physical devices found!");

    std::vector<VkPhysicalDevice> devices(deviceCount);
    result = vkEnumeratePhysicalDevices(vulkanInstance->GetRaw(), &deviceCount, devices.data());
    if (result != VK_SUCCESS)
        throw std::runtime_error("Error enumerating physical devices!");

    PickDevice(devices, requireDiscretePhysicalDevice, requiredFeatures);

    if (InternalPhysicalDevice == VK_NULL_HANDLE)
        throw std::runtime_error("Didn't found compatible physical device!");
}


VkPhysicalDevice VulkanPhysicalDevice::GetRaw() const
{
    return InternalPhysicalDevice;
}

std::pair<VkPhysicalDeviceProperties, VkPhysicalDeviceFeatures> VulkanPhysicalDevice::GetDeviceInfo()
{
    return std::make_pair(InternalPhysicalDeviceProperties, InternalVkPhysicalDeviceFeatures);
}

void VulkanPhysicalDevice::PickDevice(const std::vector<VkPhysicalDevice>& devices,
                                      bool requireDiscretePhysicalDevice,
                                      const VkPhysicalDeviceFeatures& requiredFeatures)
{
    int bestVRamSize = 0;
    VkPhysicalDevice bestPhysicalDevice = VK_NULL_HANDLE;
    VkPhysicalDeviceProperties bestProperties{};
    VkPhysicalDeviceFeatures bestFeatures{};

    for (const auto& device : devices)
    {
        VkPhysicalDeviceProperties deviceProperties{};
        VkPhysicalDeviceFeatures deviceFeatures{};
        vkGetPhysicalDeviceProperties(device, &deviceProperties);
        vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

        if (requireDiscretePhysicalDevice && deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
            continue;

        CHECK_FEATURE(robustBufferAccess);
        CHECK_FEATURE(fullDrawIndexUint32);
        CHECK_FEATURE(imageCubeArray);
        CHECK_FEATURE(independentBlend);
        CHECK_FEATURE(geometryShader);
        CHECK_FEATURE(tessellationShader);
        CHECK_FEATURE(sampleRateShading);
        CHECK_FEATURE(dualSrcBlend);
        CHECK_FEATURE(logicOp);
        CHECK_FEATURE(multiDrawIndirect);
        CHECK_FEATURE(drawIndirectFirstInstance);
        CHECK_FEATURE(depthClamp);
        CHECK_FEATURE(depthBiasClamp);
        CHECK_FEATURE(fillModeNonSolid);
        CHECK_FEATURE(depthBounds);
        CHECK_FEATURE(wideLines);
        CHECK_FEATURE(largePoints);
        CHECK_FEATURE(alphaToOne);
        CHECK_FEATURE(multiViewport);
        CHECK_FEATURE(samplerAnisotropy);
        CHECK_FEATURE(textureCompressionETC2);
        CHECK_FEATURE(textureCompressionASTC_LDR);
        CHECK_FEATURE(textureCompressionBC);
        CHECK_FEATURE(occlusionQueryPrecise);
        CHECK_FEATURE(pipelineStatisticsQuery);
        CHECK_FEATURE(vertexPipelineStoresAndAtomics);
        CHECK_FEATURE(fragmentStoresAndAtomics);
        CHECK_FEATURE(shaderTessellationAndGeometryPointSize);
        CHECK_FEATURE(shaderImageGatherExtended);
        CHECK_FEATURE(shaderStorageImageExtendedFormats);
        CHECK_FEATURE(shaderStorageImageMultisample);
        CHECK_FEATURE(shaderStorageImageReadWithoutFormat);
        CHECK_FEATURE(shaderStorageImageWriteWithoutFormat);
        CHECK_FEATURE(shaderUniformBufferArrayDynamicIndexing);
        CHECK_FEATURE(shaderSampledImageArrayDynamicIndexing);
        CHECK_FEATURE(shaderStorageBufferArrayDynamicIndexing);
        CHECK_FEATURE(shaderStorageImageArrayDynamicIndexing);
        CHECK_FEATURE(shaderClipDistance);
        CHECK_FEATURE(shaderCullDistance);
        CHECK_FEATURE(shaderFloat64);
        CHECK_FEATURE(shaderInt64);
        CHECK_FEATURE(shaderInt16);
        CHECK_FEATURE(shaderResourceResidency);
        CHECK_FEATURE(shaderResourceMinLod);
        CHECK_FEATURE(sparseBinding);
        CHECK_FEATURE(sparseResidencyBuffer);
        CHECK_FEATURE(sparseResidencyImage2D);
        CHECK_FEATURE(sparseResidencyImage3D);
        CHECK_FEATURE(sparseResidency2Samples);
        CHECK_FEATURE(sparseResidency4Samples);
        CHECK_FEATURE(sparseResidency8Samples);
        CHECK_FEATURE(sparseResidency16Samples);
        CHECK_FEATURE(sparseResidencyAliased);
        CHECK_FEATURE(variableMultisampleRate);
        CHECK_FEATURE(inheritedQueries);

        bestProperties = deviceProperties;
        bestFeatures = deviceFeatures;
    }

    InternalPhysicalDevice = bestPhysicalDevice;
    InternalPhysicalDeviceProperties = bestProperties;
    InternalVkPhysicalDeviceFeatures = bestFeatures;
}

