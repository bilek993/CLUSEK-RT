//
// Created by jbili on 04.06.2021.
//

#ifndef CLUSEK_RT_MEMORYBARRIERBUILDER_H
#define CLUSEK_RT_MEMORYBARRIERBUILDER_H

#include <vulkan/vulkan.h>

class MemoryBarrierBuilder final
{
public:
    MemoryBarrierBuilder();
    MemoryBarrierBuilder& SetAccessFlags(const VkAccessFlags& srcAccessMask,
                                         const VkAccessFlags& dstAccessMask);

private:
    VkBufferMemoryBarrier InternalBufferMemoryBarrier{};
};

#endif //CLUSEK_RT_MEMORYBARRIERBUILDER_H
