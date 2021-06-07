//
// Created by jbili on 04.06.2021.
//

#ifndef CLUSEK_RT_BUFFERMEMORYBARRIERBUILDER_H
#define CLUSEK_RT_BUFFERMEMORYBARRIERBUILDER_H

#include <vulkan/vulkan.h>

#include "../core/VulkanQueue.h"
#include "../core/VulkanBuffer.h"

class BufferMemoryBarrierBuilder final
{
public:
    BufferMemoryBarrierBuilder();

    BufferMemoryBarrierBuilder& SetAccessFlags(const VkAccessFlags& srcAccessMask,
                                               const VkAccessFlags& dstAccessMask);
    BufferMemoryBarrierBuilder& SetOwnershipTransferIfNeeded(const VulkanQueue& srcQueue,
                                                             const VulkanQueue& dstQueue);
    BufferMemoryBarrierBuilder& SetBufferData(const VulkanBuffer& buffer);

    [[nodiscard]] VkBufferMemoryBarrier Build() const;

private:
    VkBufferMemoryBarrier InternalBufferMemoryBarrier{};
};

#endif //CLUSEK_RT_BUFFERMEMORYBARRIERBUILDER_H
