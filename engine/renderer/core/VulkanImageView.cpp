//
// Created by jbili on 07.05.2021.
//

#include "VulkanImageView.h"

VulkanImageView::VulkanImageView(std::shared_ptr<VulkanLogicalDevice> logicalDevice,
                                 const std::shared_ptr<VulkanImage> image,
                                 const VkImageViewType imageViewType,
                                 const VkFormat format,
                                 const VkImageAspectFlags aspectMask,
                                 const uint32_t baseMipLevel,
                                 const uint32_t levelCount,
                                 const uint32_t baseArrayLayer,
                                 const uint32_t layerCount)
{
    LogicalDevice = std::move(logicalDevice);

    VkImageViewCreateInfo imageViewCreateInfo{};
    imageViewCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    imageViewCreateInfo.image = image->GetRaw();
    imageViewCreateInfo.viewType = imageViewType;
    imageViewCreateInfo.format = format;
    imageViewCreateInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
    imageViewCreateInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
    imageViewCreateInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
    imageViewCreateInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
    imageViewCreateInfo.subresourceRange.aspectMask = aspectMask;
    imageViewCreateInfo.subresourceRange.baseMipLevel = baseMipLevel;
    imageViewCreateInfo.subresourceRange.levelCount = levelCount;
    imageViewCreateInfo.subresourceRange.baseArrayLayer = baseArrayLayer;
    imageViewCreateInfo.subresourceRange.layerCount = layerCount;

    const auto result = vkCreateImageView(LogicalDevice->GetRaw(), &imageViewCreateInfo, nullptr, &InternalImageView);
    if (result != VK_SUCCESS)
        throw std::runtime_error("Image view creation failed!");
}

VulkanImageView::~VulkanImageView()
{
    vkDestroyImageView(LogicalDevice->GetRaw(), InternalImageView, nullptr);
}

VkImageView VulkanImageView::GetRaw() const
{
    return InternalImageView;
}
