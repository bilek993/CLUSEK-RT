//
// Created by jbili on 16.04.2021.
//

#include "VulkanQueues.h"

#include <algorithm>

VulkanQueues::VulkanQueues(const std::shared_ptr<VulkanPhysicalDevice> physicalDevice,
                           const unsigned int graphicsQueuesCount,
                           const std::vector<float>& graphicsQueuesPriorities,
                           const unsigned int computeQueuesCount,
                           const std::vector<float>& computeQueuesPriorities,
                           const unsigned int transferQueuesCount,
                           const std::vector<float>& transferQueuesPriorities)
{
    GraphicsQueues = std::make_shared<std::vector<VulkanQueue>>();
    ComputeQueues = std::make_shared<std::vector<VulkanQueue>>();
    TransferQueues = std::make_shared<std::vector<VulkanQueue>>();

    GraphicsQueuesPriorities = graphicsQueuesPriorities;
    ComputeQueuesPriorities = computeQueuesPriorities;
    TransferQueuesPriorities = transferQueuesPriorities;

    auto graphicsQueuesToBeAllocated = graphicsQueuesCount;
    auto computeQueuesToBeAllocated = computeQueuesCount;
    auto transferQueuesToBeAllocated = transferQueuesCount;

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

VulkanQueue* VulkanQueues::GetQueuePointerInFamily(const uint32_t familyIndex, const uint32_t queueIndex) const
{
    auto counter = 0;

    for (auto& queue : *GraphicsQueues)
        if (queue.FamilyIndex == familyIndex)
            if (queueIndex == counter++)
                return &queue;

    for (auto& queue : *ComputeQueues)
        if (queue.FamilyIndex == familyIndex)
            if (queueIndex == counter++)
                return &queue;

    for (auto& queue : *TransferQueues)
        if (queue.FamilyIndex == familyIndex)
            if (queueIndex == counter++)
                return &queue;

    return nullptr;
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

std::unordered_map<uint32_t, std::vector<float>> VulkanQueues::GetQueuePriorities() const
{
    const auto usedQueueFamilies = GetUsedQueueFamilies();
    std::unordered_map<uint32_t, std::vector<float>> queuePriorities{};

    auto graphicCounter = 0;
    auto computeCounter = 0;
    auto transferCounter = 0;

    for (const auto familyIndex : usedQueueFamilies)
    {
        for (const auto& queue : *GraphicsQueues)
            if (queue.FamilyIndex == familyIndex)
                queuePriorities[familyIndex].emplace_back(GraphicsQueuesPriorities[graphicCounter++]);

        for (const auto& queue : *ComputeQueues)
            if (queue.FamilyIndex == familyIndex)
                queuePriorities[familyIndex].emplace_back(ComputeQueuesPriorities[computeCounter++]);

        for (const auto& queue : *TransferQueues)
            if (queue.FamilyIndex == familyIndex)
                queuePriorities[familyIndex].emplace_back(TransferQueuesPriorities[transferCounter++]);
    }

    return queuePriorities;
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
