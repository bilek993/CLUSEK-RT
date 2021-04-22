//
// Created by jbili on 22.04.2021.
//

#include "VulkanMemory.h"

#include <stdexcept>

VulkanMemory::VulkanMemory(const std::shared_ptr<VulkanInstance> vulkanInstance,
                           const std::shared_ptr<VulkanPhysicalDevice> vulkanPhysicalDevice,
                           const std::shared_ptr<VulkanLogicalDevice> vulkanLogicalDevice,
                           const uint32_t vulkanApiVersion)
{
    VmaAllocatorCreateInfo allocatorCreateInfo{};
    allocatorCreateInfo.vulkanApiVersion = vulkanApiVersion;
    allocatorCreateInfo.instance = vulkanInstance->GetRaw();
    allocatorCreateInfo.physicalDevice = vulkanPhysicalDevice->GetRaw();
    allocatorCreateInfo.device = vulkanLogicalDevice->GetRaw();

    const auto result = vmaCreateAllocator(&allocatorCreateInfo, &InternalAllocator);
    if (result != VK_SUCCESS)
        throw std::runtime_error("Critical error when creating Vulkan Instance!");
}

VulkanMemory::~VulkanMemory()
{
    vmaDestroyAllocator(InternalAllocator);
}
