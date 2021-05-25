//
// Created by jbili on 07.05.2021.
//

#include "VulkanImage.h"

VulkanImage::VulkanImage(const VkImage& inputImage)
{
    InternalImage = inputImage;
}

VulkanImage::VulkanImage(std::shared_ptr<VulkanMemory> memory,
                         const VkImageType imageType,
                         const uint32_t width,
                         const uint32_t height,
                         const uint32_t depth,
                         const uint32_t mipLevelsCount,
                         const uint32_t arrayLayers,
                         const VkFormat format,
                         const VkImageTiling tiling,
                         const VkImageUsageFlags usage,
                         const VmaMemoryUsage& memoryUsage)
{
    Memory = std::move(memory);

    VkImageCreateInfo imageCreateInfo{};
    imageCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    imageCreateInfo.imageType = imageType;
    imageCreateInfo.extent.width = width;
    imageCreateInfo.extent.height = height;
    imageCreateInfo.extent.depth = depth;
    imageCreateInfo.mipLevels = mipLevelsCount;
    imageCreateInfo.arrayLayers = arrayLayers;
    imageCreateInfo.format = format;
    imageCreateInfo.tiling = tiling;
    imageCreateInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    imageCreateInfo.usage = usage;
    imageCreateInfo.samples = VK_SAMPLE_COUNT_1_BIT;
    imageCreateInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

    VmaAllocationCreateInfo allocationCreateInfo{};
    allocationCreateInfo.usage = memoryUsage;

    const auto result = vmaCreateImage(Memory->GetRaw(),
                                       &imageCreateInfo,
                                       &allocationCreateInfo,
                                       &InternalImage,
                                       &InternalAllocation,
                                       &InternalAllocationInfo);
    if (result != VK_SUCCESS)
        throw std::runtime_error("Image creation failed!");
}

VulkanImage::~VulkanImage()
{
    if (Memory != nullptr && InternalImage != VK_NULL_HANDLE)
        vmaDestroyImage(Memory->GetRaw(), InternalImage, InternalAllocation);
}

VkImage VulkanImage::GetRaw() const
{
    return InternalImage;
}
