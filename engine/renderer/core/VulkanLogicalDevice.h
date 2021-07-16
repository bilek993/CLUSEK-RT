//
// Created by jbili on 07.04.2021.
//

#ifndef CLUSEK_RT_VULKANLOGICALDEVICE_H
#define CLUSEK_RT_VULKANLOGICALDEVICE_H

#include <vulkan/vulkan.h>
#include <vector>

#include "VulkanQueues.h"
#include "VulkanPhysicalDevice.h"
#include "VulkanFence.h"

class VulkanLogicalDevice final
{
public:
    VulkanLogicalDevice(bool enableValidationLayers,
                        const VulkanPhysicalDevice& physicalDevice,
                        const VulkanQueues& queues,
                        const VkPhysicalDeviceFeatures& requiredFeatures,
                        std::vector<const char*> requiredExtensions);
    ~VulkanLogicalDevice();
    VulkanLogicalDevice(const VulkanLogicalDevice& other) = delete;
    VulkanLogicalDevice(VulkanLogicalDevice&& other) noexcept = delete;
    VulkanLogicalDevice& operator=(const VulkanLogicalDevice& other) = delete;
    VulkanLogicalDevice& operator=(VulkanLogicalDevice&& other) noexcept = delete;

    void WaitIdle();
    void WaitFences(const std::vector<VulkanFence*>& fences, bool waitForAll, uint64_t timeout = UINT64_MAX);

    [[nodiscard]] VkDevice GetRaw() const;
private:
    VkDevice InternalLogicalDevice{};
};


#endif //CLUSEK_RT_VULKANLOGICALDEVICE_H
