//
// Created by jbili on 04.06.2021.
//

#ifndef CLUSEK_RT_IMAGEMEMORYBARRIERBUILDER_H
#define CLUSEK_RT_IMAGEMEMORYBARRIERBUILDER_H

#include <vulkan/vulkan.h>
#include <memory>

#include "../core/VulkanQueue.h"
#include "../core/VulkanImage.h"

class ImageMemoryBarrierBuilder
{
public:
    ImageMemoryBarrierBuilder();

    ImageMemoryBarrierBuilder& SetAccessFlags(const VkAccessFlags& srcAccessMask,
                                              const VkAccessFlags& dstAccessMask);
    ImageMemoryBarrierBuilder& SetImageLayouts(const VkImageLayout& oldLayout,
                                               const VkImageLayout& newLayout);
    ImageMemoryBarrierBuilder& SetOwnershipTransferIfNeeded(const VulkanQueue& srcQueue,
                                                            const VulkanQueue& dstQueue);
    ImageMemoryBarrierBuilder& SetImage(std::shared_ptr<VulkanImage> image);
    ImageMemoryBarrierBuilder& SetSubresourceRange(VkImageAspectFlags aspectMask,
                                                   uint32_t baseMipLevel,
                                                   uint32_t levelCount,
                                                   uint32_t baseArrayLayer,
                                                   uint32_t layerCount);

    [[nodiscard]]
    VkImageMemoryBarrier Build() const;

private:
    VkImageMemoryBarrier InternalImageMemoryBarrier{};
};

#endif //CLUSEK_RT_IMAGEMEMORYBARRIERBUILDER_H
