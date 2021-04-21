//
// Created by jbili on 16.04.2021.
//

#ifndef CLUSEK_RT_VULKANQUEUES_H
#define CLUSEK_RT_VULKANQUEUES_H

#include <set>
#include <vulkan/vulkan.h>
#include <vector>
#include <unordered_map>

#include "VulkanQueue.h"
#include "VulkanPhysicalDevice.h"

class VulkanQueues final
{
public:
    VulkanQueues(std::shared_ptr<VulkanPhysicalDevice> physicalDevice,
                 unsigned int graphicsQueuesCount,
                 const std::vector<float>& graphicsQueuesPriorities,
                 unsigned int computeQueuesCount,
                 const std::vector<float>& computeQueuesPriorities,
                 unsigned int transferQueuesCount,
                 const std::vector<float>& transferQueuesPriorities);
    ~VulkanQueues() = default;
    VulkanQueues(const VulkanQueues& other) = delete;
    VulkanQueues(VulkanQueues&& other) noexcept = delete;
    VulkanQueues& operator=(const VulkanQueues& other) = delete;
    VulkanQueues& operator=(VulkanQueues&& other) noexcept = delete;

    [[nodiscard]] std::shared_ptr<std::vector<VulkanQueue>> GetGraphicsQueues() const;
    [[nodiscard]] std::shared_ptr<std::vector<VulkanQueue>> GetComputeQueues() const;
    [[nodiscard]] std::shared_ptr<std::vector<VulkanQueue>> GetTransferQueues() const;

    [[nodiscard]] VulkanQueue* GetQueuePointerInFamily(uint32_t familyIndex, uint32_t queueIndex) const;

    [[nodiscard]] std::set<uint32_t> GetUsedQueueFamilies() const;
    [[nodiscard]] std::unordered_map<uint32_t, std::vector<float>> GetQueuePriorities() const;
    [[nodiscard]] uint32_t CountQueuesInFamily(uint32_t familyIndex) const;
private:
    static std::vector<VkQueueFamilyProperties>
    GetAllQueueFamilyProperties(std::shared_ptr<VulkanPhysicalDevice> physicalDevice);

    std::shared_ptr<std::vector<VulkanQueue>> GraphicsQueues{};
    std::shared_ptr<std::vector<VulkanQueue>> ComputeQueues{};
    std::shared_ptr<std::vector<VulkanQueue>> TransferQueues{};

    std::vector<float> GraphicsQueuesPriorities;
    std::vector<float> ComputeQueuesPriorities;
    std::vector<float> TransferQueuesPriorities;
};


#endif //CLUSEK_RT_VULKANQUEUES_H
