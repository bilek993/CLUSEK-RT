//
// Created by jbili on 07.04.2021.
//

#ifndef CLUSEK_RT_VULKANPHYSICALDEVICE_H
#define CLUSEK_RT_VULKANPHYSICALDEVICE_H

#include <vulkan/vulkan.h>
#include <memory>

#include "VulkanInstance.h"

#define CHECK_FEATURE(TYPE) if (requiredFeatures.TYPE && !deviceFeatures.TYPE) continue

class VulkanPhysicalDevice final
{
public:
    VulkanPhysicalDevice(std::shared_ptr<VulkanInstance> vulkanInstance,
                         bool requireDiscretePhysicalDevice,
                         const VkPhysicalDeviceFeatures& requiredFeatures);
    ~VulkanPhysicalDevice() = default;
    VulkanPhysicalDevice(const VulkanPhysicalDevice& other) = delete;
    VulkanPhysicalDevice(VulkanPhysicalDevice&& other) noexcept = delete;
    VulkanPhysicalDevice& operator=(const VulkanPhysicalDevice& other) = delete;
    VulkanPhysicalDevice& operator=(VulkanPhysicalDevice&& other) noexcept = delete;

    [[nodiscard]] VkPhysicalDeviceProperties GetProperties() const;
    [[nodiscard]] VkPhysicalDeviceFeatures GetFeatures() const;
    [[nodiscard]] VkPhysicalDeviceMemoryProperties GetMemoryProperties() const;

    [[nodiscard]] VkPhysicalDevice GetRaw() const;

private:
    VkPhysicalDevice InternalPhysicalDevice = VK_NULL_HANDLE;
    VkPhysicalDeviceProperties InternalPhysicalDeviceProperties{};
    VkPhysicalDeviceFeatures InternalPhysicalDeviceFeatures{};
    VkPhysicalDeviceMemoryProperties InternalPhysicalDeviceMemoryProperties{};

    void PickDevice(const std::vector<VkPhysicalDevice>& devices,
                    bool requireDiscretePhysicalDevice,
                    const VkPhysicalDeviceFeatures& requiredFeatures);
};


#endif //CLUSEK_RT_VULKANPHYSICALDEVICE_H
