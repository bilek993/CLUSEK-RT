//
// Created by jbili on 22.04.2021.
//

#include "VulkanMemory.h"

#include <stdexcept>

VulkanMemory::VulkanMemory(const std::shared_ptr<VulkanInstance> vulkanInstance,
                           const std::shared_ptr<VulkanPhysicalDevice> vulkanPhysicalDevice,
                           const std::shared_ptr<VulkanLogicalDevice> vulkanLogicalDevice,
                           const uint32_t vulkanApiVersion,
                           const bool checkMemoryBeforeMapping)
{
    CheckMemoryBeforeMapping = checkMemoryBeforeMapping;

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

std::pair<VkBuffer, VmaAllocation> VulkanMemory::CreateBufferExclusive(const VkBufferUsageFlags bufferUsage,
                                                                       const VkMemoryPropertyFlags requiredMemoryProperties,
                                                                       const VkMemoryPropertyFlags preferredMemoryProperties,
                                                                       const VmaAllocationCreateFlags allocationCreateFlags,
                                                                       const VkDeviceSize bufferSize) const
{
    VkBufferCreateInfo bufferInfo{};
    bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferInfo.size = bufferSize;
    bufferInfo.usage = bufferUsage;
    bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

    VmaAllocationCreateInfo allocationInfo{};
    allocationInfo.requiredFlags = requiredMemoryProperties;
    allocationInfo.preferredFlags = preferredMemoryProperties;
    allocationInfo.flags = allocationCreateFlags;

    return CreateBuffer(bufferInfo, allocationInfo);
}

std::pair<VkBuffer, VmaAllocation> VulkanMemory::CreateBufferConcurrent(const VkBufferUsageFlags bufferUsage,
                                                                        const uint32_t queueFamilyIndexCount,
                                                                        const uint32_t* queueFamilyIndices,
                                                                        const VkMemoryPropertyFlags requiredMemoryProperties,
                                                                        const VkMemoryPropertyFlags preferredMemoryProperties,
                                                                        const VmaAllocationCreateFlags allocationCreateFlags,
                                                                        const VkDeviceSize bufferSize) const
{
    VkBufferCreateInfo bufferInfo{};
    bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferInfo.size = bufferSize;
    bufferInfo.usage = bufferUsage;
    bufferInfo.sharingMode = VK_SHARING_MODE_CONCURRENT;
    bufferInfo.queueFamilyIndexCount = queueFamilyIndexCount;
    bufferInfo.pQueueFamilyIndices = queueFamilyIndices;

    VmaAllocationCreateInfo
            allocationInfo{};
    allocationInfo.requiredFlags = requiredMemoryProperties;
    allocationInfo.preferredFlags = preferredMemoryProperties;
    allocationInfo.flags = allocationCreateFlags;

    return CreateBuffer(bufferInfo, allocationInfo);
}

void VulkanMemory::DestroyBuffer(const std::pair<VkBuffer, VmaAllocation>& bufferWithAllocation) const
{
    vmaDestroyBuffer(InternalAllocator, bufferWithAllocation.first, bufferWithAllocation.second);
}

VmaAllocator VulkanMemory::GetRaw() const
{
    return InternalAllocator;
}

std::pair<VkBuffer, VmaAllocation> VulkanMemory::CreateBuffer(VkBufferCreateInfo bufferInfo,
                                                              VmaAllocationCreateInfo allocationInfo) const
{
    VkBuffer buffer;
    VmaAllocation allocation;

    const auto result = vmaCreateBuffer(InternalAllocator, &bufferInfo, &allocationInfo, &buffer, &allocation, nullptr);
    if (result != VK_SUCCESS)
        throw std::runtime_error("Buffer creation failed!");

    return std::make_pair(buffer, allocation);
}
