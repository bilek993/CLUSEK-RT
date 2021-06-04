//
// Created by jbili on 04.06.2021.
//

#include "ImageMemoryBarrierBuilder.h"

ImageMemoryBarrierBuilder::ImageMemoryBarrierBuilder()
{
    InternalImageMemoryBarrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
    InternalImageMemoryBarrier.pNext = nullptr;
    InternalImageMemoryBarrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    InternalImageMemoryBarrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
}

ImageMemoryBarrierBuilder& ImageMemoryBarrierBuilder::SetAccessFlags(const VkAccessFlags& srcAccessMask,
                                                                     const VkAccessFlags& dstAccessMask)
{
    InternalImageMemoryBarrier.srcAccessMask = srcAccessMask;
    InternalImageMemoryBarrier.dstAccessMask = dstAccessMask;
    return *this;
}

ImageMemoryBarrierBuilder& ImageMemoryBarrierBuilder::SetImageLayouts(const VkImageLayout& oldLayout,
                                                                      const VkImageLayout& newLayout)
{
    InternalImageMemoryBarrier.oldLayout = oldLayout;
    InternalImageMemoryBarrier.newLayout = newLayout;
    return *this;
}

ImageMemoryBarrierBuilder& ImageMemoryBarrierBuilder::SetOwnershipTransferIfNeeded(const VulkanQueue& srcQueue,
                                                                                   const VulkanQueue& dstQueue)
{
    if (srcQueue.GetFamilyIndex() == dstQueue.GetFamilyIndex())
    {
        InternalImageMemoryBarrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
        InternalImageMemoryBarrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    }
    else
    {
        InternalImageMemoryBarrier.srcQueueFamilyIndex = srcQueue.GetFamilyIndex();
        InternalImageMemoryBarrier.dstQueueFamilyIndex = dstQueue.GetFamilyIndex();
    }

    return *this;
}

ImageMemoryBarrierBuilder& ImageMemoryBarrierBuilder::SetImage(const std::shared_ptr<VulkanImage> image)
{
    InternalImageMemoryBarrier.image = image->GetRaw();
    return *this;
}

ImageMemoryBarrierBuilder& ImageMemoryBarrierBuilder::SetSubresourceRange(VkImageAspectFlags aspectMask,
                                                                          uint32_t baseMipLevel,
                                                                          uint32_t levelCount,
                                                                          uint32_t baseArrayLayer,
                                                                          uint32_t layerCount)
{
    InternalImageMemoryBarrier.subresourceRange.aspectMask = aspectMask;
    InternalImageMemoryBarrier.subresourceRange.baseMipLevel = baseMipLevel;
    InternalImageMemoryBarrier.subresourceRange.levelCount = levelCount;
    InternalImageMemoryBarrier.subresourceRange.baseArrayLayer = baseArrayLayer;
    InternalImageMemoryBarrier.subresourceRange.layerCount = layerCount;
    return *this;
}

VkImageMemoryBarrier ImageMemoryBarrierBuilder::Build() const
{
    return InternalImageMemoryBarrier;
}
