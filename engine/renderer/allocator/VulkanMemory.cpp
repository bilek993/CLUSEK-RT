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

VulkanBuffer VulkanMemory::CreateBufferExclusive(const VkBufferUsageFlags bufferUsage,
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

VulkanBuffer VulkanMemory::CreateBufferConcurrent(const VkBufferUsageFlags bufferUsage,
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

void VulkanMemory::DestroyBuffer(const VulkanBuffer& buffer) const
{
    vmaDestroyBuffer(InternalAllocator, buffer.Buffer, buffer.Allocation);
}

void VulkanMemory::MapBuffer(const VulkanBuffer& buffer, void* mappedData) const
{
    if (CheckMemoryBeforeMapping && !IsMappable(buffer))
        throw std::runtime_error("This buffer is not mappable!");

    const auto result = vmaMapMemory(InternalAllocator, buffer.Allocation, &mappedData);
    if (result != VK_SUCCESS)
        throw std::runtime_error("Buffer mapping failed!");
}

void VulkanMemory::UnmapBuffer(const VulkanBuffer& buffer) const
{
    if (CheckMemoryBeforeMapping && !IsMappable(buffer))
        throw std::runtime_error("This buffer is not unmappable!");

    vmaUnmapMemory(InternalAllocator, buffer.Allocation);
}

VmaAllocator VulkanMemory::GetRaw() const
{
    return InternalAllocator;
}

VulkanBuffer VulkanMemory::CreateBuffer(VkBufferCreateInfo bufferInfo,
                                        VmaAllocationCreateInfo allocationCreateInfo) const
{
    VkBuffer buffer;
    VmaAllocation allocation;
    VmaAllocationInfo allocationInfo;

    const auto result = vmaCreateBuffer(InternalAllocator,
                                        &bufferInfo,
                                        &allocationCreateInfo,
                                        &buffer,
                                        &allocation,
                                        &allocationInfo);
    if (result != VK_SUCCESS)
        throw std::runtime_error("Buffer creation failed!");

    VulkanBuffer newBuffer{};
    newBuffer.Buffer = buffer;
    newBuffer.Allocation = allocation;
    newBuffer.AllocationInfo = allocationInfo;

    return newBuffer;
}

bool VulkanMemory::IsMappable(const VulkanBuffer& buffer) const
{
    VkMemoryPropertyFlags memoryPropertyFlags;
    vmaGetMemoryTypeProperties(InternalAllocator, buffer.AllocationInfo.memoryType, &memoryPropertyFlags);

    return ((memoryPropertyFlags & VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT) != 0);
}
