//
// Created by jbili on 16.04.2021.
//

#include "VulkanQueues.h"

#include <algorithm>

VulkanQueues::VulkanQueues(const std::shared_ptr<VulkanPhysicalDevice> physicalDevice,
                           const unsigned int graphicsQueuesCount,
                           const unsigned int computeQueuesCount,
                           const unsigned int transferQueues)
{
    auto graphicsQueuesToBeAllocated = graphicsQueuesCount;
    auto computeQueuesToBeAllocated = computeQueuesCount;
    auto transferQueuesToBeAllocated = transferQueues;

    const auto queueFamilies = GetAllQueueFamilyProperties(physicalDevice);

    for (auto i = 0; i < queueFamilies.size(); i++)
    {
        const auto& queueFamily = queueFamilies[i];
        auto currentFamilyLeftQueues = queueFamily.queueCount;

        if (graphicsQueuesToBeAllocated > 0 && queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
        {
            const auto allocatedQueues = std::min(graphicsQueuesToBeAllocated, currentFamilyLeftQueues);
            currentFamilyLeftQueues -= allocatedQueues;

            for (auto j = 0; j < allocatedQueues; j++)
            {
                VulkanQueue graphicQueue{};
                graphicQueue.FamilyIndex = i;
                GraphicsQueues.emplace_back(graphicQueue);
            }
        }

        if (computeQueuesToBeAllocated > 0 && queueFamily.queueFlags & VK_QUEUE_COMPUTE_BIT)
        {
            const auto allocatedQueues = std::min(computeQueuesToBeAllocated, currentFamilyLeftQueues);
            currentFamilyLeftQueues -= allocatedQueues;

            for (auto j = 0; j < allocatedQueues; j++)
            {
                VulkanQueue computeQueue{};
                computeQueue.FamilyIndex = i;
                ComputeQueues.emplace_back(computeQueue);
            }
        }

        if (transferQueuesToBeAllocated > 0 && queueFamily.queueFlags & VK_QUEUE_TRANSFER_BIT)
        {
            const auto allocatedQueues = std::min(transferQueuesToBeAllocated, currentFamilyLeftQueues);
            currentFamilyLeftQueues -= allocatedQueues;

            for (auto j = 0; j < allocatedQueues; j++)
            {
                VulkanQueue transferQueue{};
                transferQueue.FamilyIndex = i;
                TransferQueues.emplace_back(transferQueue);
            }
        }
    }
}

std::vector<VkQueueFamilyProperties>
VulkanQueues::GetAllQueueFamilyProperties(const std::shared_ptr<VulkanPhysicalDevice> physicalDevice)
{
    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice->GetRaw(), &queueFamilyCount, nullptr);

    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice->GetRaw(), &queueFamilyCount, queueFamilies.data());

    return queueFamilies;
}
