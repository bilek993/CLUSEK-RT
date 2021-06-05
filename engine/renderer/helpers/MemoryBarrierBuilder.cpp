//
// Created by jbili on 04.06.2021.
//

#include "MemoryBarrierBuilder.h"

MemoryBarrierBuilder::MemoryBarrierBuilder()
{
    InternalBufferMemoryBarrier.sType = VK_STRUCTURE_TYPE_MEMORY_BARRIER;
    InternalBufferMemoryBarrier.pNext = nullptr;
}

MemoryBarrierBuilder& MemoryBarrierBuilder::SetAccessFlags(const VkAccessFlags& srcAccessMask,
                                                           const VkAccessFlags& dstAccessMask)
{
    InternalBufferMemoryBarrier.srcAccessMask = srcAccessMask;
    InternalBufferMemoryBarrier.dstAccessMask = dstAccessMask;
    return *this;
}

VkBufferMemoryBarrier MemoryBarrierBuilder::Build() const
{
    return InternalBufferMemoryBarrier;
}
