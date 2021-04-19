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
    GraphicsQueues = std::make_shared<std::vector<VulkanQueue>>();
    ComputeQueues = std::make_shared<std::vector<VulkanQueue>>();
    TransferQueues = std::make_shared<std::vector<VulkanQueue>>();

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
            graphicsQueuesToBeAllocated -= allocatedQueues;

            for (auto j = 0; j < allocatedQueues; j++)
            {
                VulkanQueue graphicQueue{};
                graphicQueue.FamilyIndex = i;
                GraphicsQueues->emplace_back(graphicQueue);
            }
        }

        if (computeQueuesToBeAllocated > 0 && queueFamily.queueFlags & VK_QUEUE_COMPUTE_BIT)
        {
            const auto allocatedQueues = std::min(computeQueuesToBeAllocated, currentFamilyLeftQueues);
            currentFamilyLeftQueues -= allocatedQueues;
            computeQueuesToBeAllocated -= allocatedQueues;

            for (auto j = 0; j < allocatedQueues; j++)
            {
                VulkanQueue computeQueue{};
                computeQueue.FamilyIndex = i;
                ComputeQueues->emplace_back(computeQueue);
            }
        }

        if (transferQueuesToBeAllocated > 0 && queueFamily.queueFlags & VK_QUEUE_TRANSFER_BIT)
        {
            const auto allocatedQueues = std::min(transferQueuesToBeAllocated, currentFamilyLeftQueues);
            currentFamilyLeftQueues -= allocatedQueues;
            transferQueuesToBeAllocated -= allocatedQueues;

            for (auto j = 0; j < allocatedQueues; j++)
            {
                VulkanQueue transferQueue{};
                transferQueue.FamilyIndex = i;
                TransferQueues->emplace_back(transferQueue);
            }
        }
    }

    if (graphicsQueuesToBeAllocated > 0)
        throw std::runtime_error("Not all graphic queues have been assigned!");

    if (computeQueuesToBeAllocated > 0)
        throw std::runtime_error("Not all compute queues have been assigned!");

    if (transferQueuesToBeAllocated > 0)
        throw std::runtime_error("Not all transfer queues have been assigned!");
}

std::shared_ptr<std::vector<VulkanQueue>> VulkanQueues::GetGraphicsQueues() const
{
    return GraphicsQueues;
}

std::shared_ptr<std::vector<VulkanQueue>> VulkanQueues::GetComputeQueues() const
{
    return ComputeQueues;
}

std::shared_ptr<std::vector<VulkanQueue>> VulkanQueues::GetTransferQueues() const
{
    return TransferQueues;
}


std::set<uint32_t> VulkanQueues::GetUsedQueueFamilies() const
{
    std::set<uint32_t> usedFamilies{};

    for (const auto& queue : *GraphicsQueues)
        usedFamilies.insert(queue.FamilyIndex);

    for (const auto& queue : *ComputeQueues)
        usedFamilies.insert(queue.FamilyIndex);

    for (const auto& queue : *TransferQueues)
        usedFamilies.insert(queue.FamilyIndex);

    return usedFamilies;
}

uint32_t VulkanQueues::CountQueuesInFamily(const uint32_t familyIndex) const
{
    auto counter = 0;

    for (const auto& queue : *GraphicsQueues)
        if (queue.FamilyIndex == familyIndex)
            counter++;

    for (const auto& queue : *ComputeQueues)
        if (queue.FamilyIndex == familyIndex)
            counter++;

    for (const auto& queue : *TransferQueues)
        if (queue.FamilyIndex == familyIndex)
            counter++;

    return counter;
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


