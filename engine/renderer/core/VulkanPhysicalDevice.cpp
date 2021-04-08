//
// Created by jbili on 07.04.2021.
//

#include "VulkanPhysicalDevice.h"

VulkanPhysicalDevice::VulkanPhysicalDevice(const std::shared_ptr<VulkanInstance> vulkanInstance)
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

    // TODO: Add logic here

    if (InternalPhysicalDevice == VK_NULL_HANDLE)
        throw std::runtime_error("Didn't found compatible physical device!");
}

VkPhysicalDevice VulkanPhysicalDevice::GetRaw() const
{
    return InternalPhysicalDevice;
}
