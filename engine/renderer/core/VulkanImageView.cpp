//
// Created by jbili on 07.05.2021.
//

#include "VulkanImageView.h"

VulkanImageView::VulkanImageView(std::shared_ptr<VulkanLogicalDevice> logicalDevice,
                                 const VulkanImage& image,
                                 const VkImageViewType imageViewType,
                                 const VkFormat format,
                                 const VkImageAspectFlags aspectMask,
                                 const uint32_t baseMipLevel,
                                 const uint32_t levelCount,
                                 const uint32_t baseArrayLayer,
                                 const uint32_t layerCount)
{
    LogicalDevice = std::move(logicalDevice);

    AspectMask = aspectMask;
    BaseMipLevel = baseMipLevel;
    LevelCount = levelCount;
    BaseArrayLayer = baseArrayLayer;
    LayerCount = layerCount;

    VkImageViewCreateInfo imageViewCreateInfo{};
    imageViewCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    imageViewCreateInfo.image = image.GetRaw();
    imageViewCreateInfo.viewType = imageViewType;
    imageViewCreateInfo.format = format;
    imageViewCreateInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
    imageViewCreateInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
    imageViewCreateInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
    imageViewCreateInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
    imageViewCreateInfo.subresourceRange.aspectMask = AspectMask;
    imageViewCreateInfo.subresourceRange.baseMipLevel = BaseMipLevel;
    imageViewCreateInfo.subresourceRange.levelCount = LevelCount;
    imageViewCreateInfo.subresourceRange.baseArrayLayer = BaseArrayLayer;
    imageViewCreateInfo.subresourceRange.layerCount = LayerCount;

    const auto result = vkCreateImageView(LogicalDevice->GetRaw(), &imageViewCreateInfo, nullptr, &InternalImageView);
    if (result != VK_SUCCESS)
        throw std::runtime_error("Image view creation failed!");
}

VulkanImageView::~VulkanImageView()
{
    if (InternalImageView != VK_NULL_HANDLE)
        vkDestroyImageView(LogicalDevice->GetRaw(), InternalImageView, nullptr);
}

VkImageAspectFlags VulkanImageView::GetAspectMask() const
{
    return AspectMask;
}

uint32_t VulkanImageView::GetBaseMipLevel() const
{
    return BaseMipLevel;
}

uint32_t VulkanImageView::GetLevelCount() const
{
    return LayerCount;
}

uint32_t VulkanImageView::GetBaseArrayLayer() const
{
    return BaseArrayLayer;
}

uint32_t VulkanImageView::GetLayerCount() const
{
    return LayerCount;
}

VkImageView VulkanImageView::GetRaw() const
{
    return InternalImageView;
}
