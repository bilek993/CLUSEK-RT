//
// Created by jbili on 07.04.2021.
//

#include "VulkanLogicalDevice.h"

#include <algorithm>

#include "../helpers/DebugExtender.h"

VulkanLogicalDevice::VulkanLogicalDevice(bool enableValidationLayers,
                                         const VulkanPhysicalDevice& physicalDevice,
                                         const VulkanQueues& queues,
                                         const VkPhysicalDeviceFeatures& requiredFeatures,
                                         std::vector<const char*> requiredExtensions)
{
    const auto usedQueueFamiliesIndices = queues.GetUsedQueueFamilies();
    const auto queuePriorities = queues.GetQueuePriorities();
    std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;

    for (const auto queueFamilyIndex : usedQueueFamiliesIndices)
    {
        VkDeviceQueueCreateInfo queueCreateInfo{};
        queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueCreateInfo.queueFamilyIndex = queueFamilyIndex;
        queueCreateInfo.queueCount = queues.CountQueuesInFamily(queueFamilyIndex);
        queueCreateInfo.pQueuePriorities = queuePriorities.at(queueFamilyIndex).data();
        queueCreateInfos.push_back(queueCreateInfo);
    }

    const auto validationLayers = DebugExtender::GetValidationLayers();

    VkDeviceCreateInfo deviceCreateInfo{};
    deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    deviceCreateInfo.pQueueCreateInfos = queueCreateInfos.data();
    deviceCreateInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
    deviceCreateInfo.pEnabledFeatures = &requiredFeatures;
    deviceCreateInfo.enabledExtensionCount = static_cast<uint32_t>(requiredExtensions.size());
    deviceCreateInfo.ppEnabledExtensionNames = requiredExtensions.data();

    if (enableValidationLayers)
    {
        deviceCreateInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
        deviceCreateInfo.ppEnabledLayerNames = validationLayers.data();
    }
    else
    {
        deviceCreateInfo.enabledLayerCount = 0;
    }

    const auto result = vkCreateDevice(physicalDevice.GetRaw(), &deviceCreateInfo, nullptr, &InternalLogicalDevice);
    if (result != VK_SUCCESS)
        throw std::runtime_error("Failed to create proper logical device!");

    for (const auto queueFamilyIndex : usedQueueFamiliesIndices)
    {
        const auto numberOfQueues = queues.CountQueuesInFamily(queueFamilyIndex);

        for (auto queueIndex = 0; queueIndex < numberOfQueues; queueIndex++)
        {
            const auto queue = queues.GetQueuePointerInFamily(queueFamilyIndex, queueIndex);
            vkGetDeviceQueue(InternalLogicalDevice, queueFamilyIndex, queueIndex, queue->GetPointerToRaw());
        }
    }
}

VulkanLogicalDevice::~VulkanLogicalDevice()
{
    if (InternalLogicalDevice != VK_NULL_HANDLE)
        vkDestroyDevice(InternalLogicalDevice, nullptr);
}

void VulkanLogicalDevice::WaitIdle()
{
    const auto result = vkDeviceWaitIdle(InternalLogicalDevice);
    if (result != VK_SUCCESS)
        throw std::runtime_error("Waiting for logical device failed!");
}

void VulkanLogicalDevice::WaitFences(const std::vector<VulkanFence*>& fences, bool waitForAll, uint64_t timeout)
{
    std::vector<VkFence> vulkanFences{};
    std::transform(fences.begin(), fences.end(),
                   std::back_inserter(vulkanFences), [](const VulkanFence* fence)
                   { return fence->GetRaw(); });

    vkWaitForFences(InternalLogicalDevice,
                    vulkanFences.size(),
                    vulkanFences.data(),
                    waitForAll,
                    timeout);
}

VkDevice VulkanLogicalDevice::GetRaw() const
{
    return InternalLogicalDevice;
}

