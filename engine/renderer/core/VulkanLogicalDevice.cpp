//
// Created by jbili on 07.04.2021.
//

#include "VulkanLogicalDevice.h"

VulkanLogicalDevice::VulkanLogicalDevice(std::shared_ptr<VulkanPhysicalDevice> physicalDevice,
                                         const std::shared_ptr<VulkanQueues> queues,
                                         const VkPhysicalDeviceFeatures& requiredFeatures)
{
    const auto usedQueueFamiliesIndices = queues->GetUsedQueueFamilies();

    const auto queuePriority = 1.0F;
    std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;

    for (const auto queueFamilyIndex : usedQueueFamiliesIndices)
    {
        VkDeviceQueueCreateInfo queueCreateInfo{};
        queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueCreateInfo.queueFamilyIndex = queueFamilyIndex;
        queueCreateInfo.queueCount = queues->CountQueuesInFamily(queueFamilyIndex);
        queueCreateInfo.pQueuePriorities = &queuePriority;
        queueCreateInfos.push_back(queueCreateInfo);
    }

    VkDeviceCreateInfo deviceCreateInfo{};
    deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    deviceCreateInfo.pQueueCreateInfos = queueCreateInfos.data();
    deviceCreateInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
    deviceCreateInfo.pEnabledFeatures = &requiredFeatures;
    //deviceCreateInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size()); // TODO: IMPLEMENT THIS
    //deviceCreateInfo.ppEnabledExtensionNames = deviceExtensions.data(); // TODO: IMPLEMENT THIS

    const auto result = vkCreateDevice(physicalDevice->GetRaw(), &deviceCreateInfo, nullptr, &InternalLogicalDevice);
    if (result != VK_SUCCESS)
        throw std::runtime_error("Failed to create proper logical device!");
}

VulkanLogicalDevice::~VulkanLogicalDevice()
{
    vkDestroyDevice(InternalLogicalDevice, nullptr);
}

VkDevice VulkanLogicalDevice::GetRaw() const
{
    return InternalLogicalDevice;
}

