//
// Created by jbili on 07.04.2021.
//

#ifndef CLUSEK_RT_VULKANLOGICALDEVICE_H
#define CLUSEK_RT_VULKANLOGICALDEVICE_H

#include <vulkan/vulkan.h>

class VulkanLogicalDevice final
{
public:
    VulkanLogicalDevice();
    ~VulkanLogicalDevice();
    VulkanLogicalDevice(const VulkanLogicalDevice& other) = delete;
    VulkanLogicalDevice(VulkanLogicalDevice&& other) noexcept = delete;
    VulkanLogicalDevice& operator=(const VulkanLogicalDevice& other) = delete;
    VulkanLogicalDevice& operator=(VulkanLogicalDevice&& other) noexcept = delete;

    [[nodiscard]] VkDevice GetRaw() const;
private:
    VkDevice InternalLogicalDevice{};
};


#endif //CLUSEK_RT_VULKANLOGICALDEVICE_H
