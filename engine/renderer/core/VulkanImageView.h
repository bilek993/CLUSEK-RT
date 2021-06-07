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
    virtual ~VulkanImageView();

    [[nodiscard]] VkImageView GetRaw() const;
private:
    VkImageView InternalImageView = VK_NULL_HANDLE;
    std::shared_ptr<VulkanLogicalDevice> LogicalDevice;
};


#endif //CLUSEK_RT_VULKANIMAGEVIEW_H
