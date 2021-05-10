//
// Created by jbili on 10.05.2021.
//

#include "VulkanBuffer.h"

VulkanBuffer::VulkanBuffer(std::shared_ptr<VulkanMemory> memory,
                           const VkBufferUsageFlags bufferUsage,
                           const VkMemoryPropertyFlags requiredMemoryProperties,
                           const VkMemoryPropertyFlags preferredMemoryProperties,
                           const VmaAllocationCreateFlags allocationCreateFlags,
                           const VkDeviceSize bufferSize)
{
    Memory = std::move(memory);

    VkBufferCreateInfo bufferCreateInfo{};
    bufferCreateInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferCreateInfo.size = bufferSize;
    bufferCreateInfo.usage = bufferUsage;
    bufferCreateInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

    VmaAllocationCreateInfo allocationCreateInfo{};
    allocationCreateInfo.requiredFlags = requiredMemoryProperties;
    allocationCreateInfo.preferredFlags = preferredMemoryProperties;
    allocationCreateInfo.flags = allocationCreateFlags;

    const auto result = vmaCreateBuffer(Memory->GetRaw(),
                                        &bufferCreateInfo,
                                        &allocationCreateInfo,
                                        &InternalBuffer,
                                        &InternalAllocation,
                                        &InternalAllocationInfo);
    if (result != VK_SUCCESS)
        throw std::runtime_error("Buffer creation failed!");
}

VulkanBuffer::~VulkanBuffer()
{
    vmaDestroyBuffer(Memory->GetRaw(), InternalBuffer, InternalAllocation);
}

void VulkanBuffer::MapBuffer(void* mappedData) const
{
    if (Memory->ShouldCheckMemoryBeforeMapping() && !IsMappable())
        throw std::runtime_error("This buffer is not mappable!");

    const auto result = vmaMapMemory(Memory->GetRaw(), InternalAllocation, &mappedData);
    if (result != VK_SUCCESS)
        throw std::runtime_error("Buffer mapping failed!");
}

void VulkanBuffer::UnmapBuffer() const
{
    if (Memory->ShouldCheckMemoryBeforeMapping() && !IsMappable())
        throw std::runtime_error("This buffer is not unmappable!");

    vmaUnmapMemory(Memory->GetRaw(), InternalAllocation);
}

VkBuffer VulkanBuffer::GetRaw() const
{
    return InternalBuffer;
}

bool VulkanBuffer::IsMappable() const
{
    VkMemoryPropertyFlags memoryPropertyFlags;
    vmaGetMemoryTypeProperties(Memory->GetRaw(), InternalAllocationInfo.memoryType, &memoryPropertyFlags);

    return ((memoryPropertyFlags & VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT) != 0);
}
