//
// Created by jbili on 28.05.2021.
//

#ifndef CLUSEK_RT_VULKANSEMAPHORE_H
#define CLUSEK_RT_VULKANSEMAPHORE_H

#include <memory>
#include <vulkan/vulkan.h>

#include "VulkanLogicalDevice.h"

class VulkanSemaphore final
{
public:
    VulkanSemaphore(std::shared_ptr<VulkanLogicalDevice> logicalDevice);
    ~VulkanSemaphore();
    VulkanSemaphore(const VulkanSemaphore& other) = delete;
    VulkanSemaphore(VulkanSemaphore&& other) noexcept = delete;
    VulkanSemaphore& operator=(const VulkanSemaphore& other) = delete;
    VulkanSemaphore& operator=(VulkanSemaphore&& other) noexcept = delete;

    [[nodiscard]] VkSemaphore GetRaw() const;

private:
    VkSemaphore InternalSemaphore = VK_NULL_HANDLE;
    std::shared_ptr<VulkanLogicalDevice> LogicalDevice;
};


#endif //CLUSEK_RT_VULKANSEMAPHORE_H
