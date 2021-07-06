//
// Created by jbili on 07.05.2021.
//

#ifndef CLUSEK_RT_VULKANIMAGEVIEW_H
#define CLUSEK_RT_VULKANIMAGEVIEW_H

#include <vulkan/vulkan.h>
#include <memory>

#include "VulkanLogicalDevice.h"
#include "VulkanImage.h"

class VulkanImageView final
{
public:
    VulkanImageView(std::shared_ptr<VulkanLogicalDevice> logicalDevice,
                    const VulkanImage& image,
                    VkImageViewType imageViewType,
                    VkFormat format,
                    VkImageAspectFlags aspectMask,
                    uint32_t baseMipLevel,
                    uint32_t levelCount,
                    uint32_t baseArrayLayer,
                    uint32_t layerCount);
    ~VulkanImageView();
    VulkanImageView(const VulkanImageView& other) = delete;
    VulkanImageView(VulkanImageView&& other) noexcept = delete;
    VulkanImageView& operator=(const VulkanImageView& other) = delete;
    VulkanImageView& operator=(VulkanImageView&& other) noexcept = delete;

    [[nodiscard]] VkImageAspectFlags GetAspectMask() const;
    [[nodiscard]] uint32_t GetBaseMipLevel() const;
    [[nodiscard]] uint32_t GetLevelCount() const;
    [[nodiscard]] uint32_t GetBaseArrayLayer() const;
    [[nodiscard]] uint32_t GetLayerCount() const;

    [[nodiscard]] VkImageView GetRaw() const;
private:
    VkImageView InternalImageView = VK_NULL_HANDLE;
    std::shared_ptr<VulkanLogicalDevice> LogicalDevice;

    VkImageAspectFlags AspectMask;
    uint32_t BaseMipLevel;
    uint32_t LevelCount;
    uint32_t BaseArrayLayer;
    uint32_t LayerCount;
};


#endif //CLUSEK_RT_VULKANIMAGEVIEW_H
