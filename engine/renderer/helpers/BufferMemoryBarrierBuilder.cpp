//
// Created by jbili on 04.06.2021.
//

#include "BufferMemoryBarrierBuilder.h"

BufferMemoryBarrierBuilder::BufferMemoryBarrierBuilder()
{
    InternalBufferMemoryBarrier.sType = VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER;
    InternalBufferMemoryBarrier.pNext = nullptr;
    InternalBufferMemoryBarrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    InternalBufferMemoryBarrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
}

BufferMemoryBarrierBuilder& BufferMemoryBarrierBuilder::SetAccessFlags(const VkAccessFlags& srcAccessMask,
                                                                       const VkAccessFlags& dstAccessMask)
{
    InternalBufferMemoryBarrier.srcAccessMask = srcAccessMask;
    InternalBufferMemoryBarrier.dstAccessMask = dstAccessMask;
    return *this;
}

BufferMemoryBarrierBuilder& BufferMemoryBarrierBuilder::SetOwnershipTransferIfNeeded(const VulkanQueue& srcQueue,
                                                                                     const VulkanQueue& dstQueue)
{
    if (srcQueue.GetFamilyIndex() == dstQueue.GetFamilyIndex())
    {
        InternalBufferMemoryBarrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
        InternalBufferMemoryBarrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    }
    else
    {
        InternalBufferMemoryBarrier.srcQueueFamilyIndex = srcQueue.GetFamilyIndex();
        InternalBufferMemoryBarrier.dstQueueFamilyIndex = dstQueue.GetFamilyIndex();
    }

    return *this;
}

BufferMemoryBarrierBuilder& BufferMemoryBarrierBuilder::SetBufferData(const VulkanBuffer& buffer)
{
    InternalBufferMemoryBarrier.buffer = buffer.GetRaw();
    InternalBufferMemoryBarrier.offset = buffer.GetOffset();
    InternalBufferMemoryBarrier.size = buffer.GetSize();

    return *this;
}

VkBufferMemoryBarrier BufferMemoryBarrierBuilder::Build() const
{
    return InternalBufferMemoryBarrier;
}
