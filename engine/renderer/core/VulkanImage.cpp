//
// Created by jbili on 07.05.2021.
//

#include "VulkanImage.h"

VulkanImage::VulkanImage(std::shared_ptr<VulkanLogicalDevice> logicalDevice,
                         const VkImage& inputImage,
                         const bool autoDestroy)
{
    LogicalDevice = std::move(logicalDevice);

    InternalImage = inputImage;
    AutoDestroy = autoDestroy;
}

VulkanImage::~VulkanImage()
{
    if (AutoDestroy)
        vkDestroyImage(LogicalDevice->GetRaw(), InternalImage, nullptr);
}

VkImage VulkanImage::GetRaw() const
{
    return InternalImage;
}
