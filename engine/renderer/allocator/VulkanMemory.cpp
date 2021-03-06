//
// Created by jbili on 22.04.2021.
//

#include "VulkanMemory.h"

#include <stdexcept>

VulkanMemory::VulkanMemory(const VulkanInstance& vulkanInstance,
                           const VulkanPhysicalDevice& vulkanPhysicalDevice,
                           const VulkanLogicalDevice& vulkanLogicalDevice,
                           const uint32_t vulkanApiVersion,
                           const bool checkMemoryBeforeMapping)
{
    CheckMemoryBeforeMapping = checkMemoryBeforeMapping;

    VmaAllocatorCreateInfo allocatorCreateInfo{};
    allocatorCreateInfo.vulkanApiVersion = vulkanApiVersion;
    allocatorCreateInfo.instance = vulkanInstance.GetRaw();
    allocatorCreateInfo.physicalDevice = vulkanPhysicalDevice.GetRaw();
    allocatorCreateInfo.device = vulkanLogicalDevice.GetRaw();

    const auto result = vmaCreateAllocator(&allocatorCreateInfo, &InternalAllocator);
    if (result != VK_SUCCESS)
        throw std::runtime_error("Critical error when creating Allocator!");
}

VulkanMemory::~VulkanMemory()
{
    vmaDestroyAllocator(InternalAllocator);
}

bool VulkanMemory::IsMappable(const VmaAllocationInfo& allocationInfo) const
{
    VkMemoryPropertyFlags memoryPropertyFlags;
    vmaGetMemoryTypeProperties(InternalAllocator, allocationInfo.memoryType, &memoryPropertyFlags);

    return ((memoryPropertyFlags & VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT) != 0);
}

bool VulkanMemory::ShouldCheckMemoryBeforeMapping() const
{
    return CheckMemoryBeforeMapping;
}

VmaAllocator VulkanMemory::GetRaw() const
{
    return InternalAllocator;
}