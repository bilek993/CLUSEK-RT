//
// Created by jbili on 16.04.2021.
//

#ifndef CLUSEK_RT_VULKANQUEUES_H
#define CLUSEK_RT_VULKANQUEUES_H

#include <vulkan/vulkan.h>
#include <vector>

#include "VulkanQueue.h"
#include "VulkanPhysicalDevice.h"

class VulkanQueues final
{
public:
    VulkanQueues(std::shared_ptr<VulkanPhysicalDevice> physicalDevice,
                 unsigned int graphicsQueuesCount,
                 unsigned int computeQueuesCount,
                 unsigned int transferQueuesCount);
    ~VulkanQueues() = default;
    VulkanQueues(const VulkanQueues& other) = delete;
    VulkanQueues(VulkanQueues&& other) noexcept = delete;
    VulkanQueues& operator=(const VulkanQueues& other) = delete;
    VulkanQueues& operator=(VulkanQueues&& other) noexcept = delete;
private:
    static std::vector<VkQueueFamilyProperties>
    GetAllQueueFamilyProperties(std::shared_ptr<VulkanPhysicalDevice> physicalDevice);

    std::vector<VulkanQueue> GraphicsQueues{};
    std::vector<VulkanQueue> ComputeQueues{};
    std::vector<VulkanQueue> TransferQueues{};
};


#endif //CLUSEK_RT_VULKANQUEUES_H
