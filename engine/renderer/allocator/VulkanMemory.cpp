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
        throw std::runtime_error("Critical error when creating Allocator!");
}

VulkanMemory::~VulkanMemory()
{
    vmaDestroyAllocator(InternalAllocator);
}

std::pair<VkBuffer, VmaAllocation> VulkanMemory::CreateBufferWithAllocation(const VkBufferUsageFlags bufferUsage,
                                                                            const VkSharingMode sharingMode,
                                                                            const VkMemoryPropertyFlags requiredMemoryProperties,
                                                                            const VkMemoryPropertyFlags preferredMemoryProperties,
                                                                            const VmaAllocationCreateFlags allocationCreateFlags,
                                                                            const VkDeviceSize bufferSize) const
{
    VkBuffer buffer;
    VmaAllocation allocation;

    VkBufferCreateInfo bufferInfo{};
    bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferInfo.size = bufferSize;
    bufferInfo.usage = bufferUsage;
    bufferInfo.sharingMode = sharingMode;

    VmaAllocationCreateInfo allocationInfo{};
    allocationInfo.requiredFlags = requiredMemoryProperties;
    allocationInfo.preferredFlags = preferredMemoryProperties;
    allocationInfo.flags = allocationCreateFlags;

    const auto result = vmaCreateBuffer(InternalAllocator, &bufferInfo, &allocationInfo, &buffer, &allocation, nullptr);
    if (result != VK_SUCCESS)
        throw std::runtime_error("Buffer creation failed!");

    return std::make_pair(buffer, allocation);
}

void VulkanMemory::DestroyBuffer(const std::pair<VkBuffer, VmaAllocation>& bufferWithAllocation) const
{
    vmaDestroyBuffer(InternalAllocator, bufferWithAllocation.first, bufferWithAllocation.second);
}

VmaAllocator VulkanMemory::GetRaw() const
{
    return InternalAllocator;
}
