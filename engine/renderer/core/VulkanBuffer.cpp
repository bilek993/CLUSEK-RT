//
// Created by jbili on 10.05.2021.
//

#include "VulkanBuffer.h"

VulkanBuffer::VulkanBuffer(std::shared_ptr<VulkanMemory> memory,
                           const VkBufferUsageFlags& bufferUsage,
                           const VmaMemoryUsage& memoryUsage,
                           const VkDeviceSize& bufferSize)
{
    Memory = std::move(memory);
    Size = bufferSize;

    VkBufferCreateInfo bufferCreateInfo{};
    bufferCreateInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferCreateInfo.size = Size;
    bufferCreateInfo.usage = bufferUsage;
    bufferCreateInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

    VmaAllocationCreateInfo allocationCreateInfo{};
    allocationCreateInfo.usage = memoryUsage;

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
    if (InternalBuffer != VK_NULL_HANDLE)
        vmaDestroyBuffer(Memory->GetRaw(), InternalBuffer, InternalAllocation);
}

void VulkanBuffer::MapBuffer(void** mappedData) const
{
    if (Memory->ShouldCheckMemoryBeforeMapping() && !Memory->IsMappable(InternalAllocationInfo))
        throw std::runtime_error("This buffer is not mappable!");

    const auto result = vmaMapMemory(Memory->GetRaw(), InternalAllocation, mappedData);
    if (result != VK_SUCCESS)
        throw std::runtime_error("Buffer mapping failed!");
}

void VulkanBuffer::UnmapBuffer() const
{
    if (Memory->ShouldCheckMemoryBeforeMapping() && !Memory->IsMappable(InternalAllocationInfo))
        throw std::runtime_error("This buffer is not unmappable!");

    vmaUnmapMemory(Memory->GetRaw(), InternalAllocation);
}

VkDeviceSize VulkanBuffer::GetSize() const
{
    return Size;
}

VkDeviceSize VulkanBuffer::GetOffset()
{
    // According to the VMA documentation, we don't need offset, because the buffer should always point to the beginning
    // of the resource. That's why `0` is always returned from this getter. This getter has been reserved for easier
    // code refactoring in the future.
    //
    // https://gpuopen-librariesandsdks.github.io/VulkanMemoryAllocator/html/struct_vma_allocation_info.html#a4a3c732388dbdc7a23f9365b00825268
    return 0;
}

VmaAllocation VulkanBuffer::GetAllocation() const
{
    return InternalAllocation;
}

VmaAllocationInfo VulkanBuffer::GetAllocationInfo() const
{
    return InternalAllocationInfo;
}

VkBuffer VulkanBuffer::GetRaw() const
{
    return InternalBuffer;
}
