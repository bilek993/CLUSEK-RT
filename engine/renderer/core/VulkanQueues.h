//
// Created by jbili on 16.04.2021.
//

#ifndef CLUSEK_RT_VULKANQUEUES_H
#define CLUSEK_RT_VULKANQUEUES_H

#include <set>
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

    [[nodiscard]] std::shared_ptr<std::vector<VulkanQueue>> GetGraphicsQueues() const;
    [[nodiscard]] std::shared_ptr<std::vector<VulkanQueue>> GetComputeQueues() const;
    [[nodiscard]] std::shared_ptr<std::vector<VulkanQueue>> GetTransferQueues() const;

    [[nodiscard]] std::set<uint32_t> GetUsedQueueFamilies() const;
    [[nodiscard]] uint32_t CountQueuesInFamily(uint32_t familyIndex) const;
private:
    static std::vector<VkQueueFamilyProperties>
    GetAllQueueFamilyProperties(std::shared_ptr<VulkanPhysicalDevice> physicalDevice);

    std::shared_ptr<std::vector<VulkanQueue>> GraphicsQueues{};
    std::shared_ptr<std::vector<VulkanQueue>> ComputeQueues{};
    std::shared_ptr<std::vector<VulkanQueue>> TransferQueues{};
};


#endif //CLUSEK_RT_VULKANQUEUES_H
