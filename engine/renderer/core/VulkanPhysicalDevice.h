//
// Created by jbili on 07.04.2021.
//

#ifndef CLUSEK_RT_VULKANPHYSICALDEVICE_H
#define CLUSEK_RT_VULKANPHYSICALDEVICE_H

#include <vulkan/vulkan.h>
#include <memory>

#include "VulkanInstance.h"

class VulkanPhysicalDevice final
{
public:
    VulkanPhysicalDevice(std::shared_ptr<VulkanInstance> vulkanInstance);
    ~VulkanPhysicalDevice() = default;
    VulkanPhysicalDevice(const VulkanPhysicalDevice& other) = delete;
    VulkanPhysicalDevice(VulkanPhysicalDevice&& other) noexcept = delete;
    VulkanPhysicalDevice& operator=(const VulkanPhysicalDevice& other) = delete;
    VulkanPhysicalDevice& operator=(VulkanPhysicalDevice&& other) noexcept = delete;

    [[nodiscard]] VkPhysicalDevice GetRaw() const;

private:
    VkPhysicalDevice InternalPhysicalDevice = VK_NULL_HANDLE;
};


#endif //CLUSEK_RT_VULKANPHYSICALDEVICE_H
