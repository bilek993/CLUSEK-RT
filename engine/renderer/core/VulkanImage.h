//
// Created by jbili on 07.05.2021.
//

#ifndef CLUSEK_RT_VULKANIMAGE_H
#define CLUSEK_RT_VULKANIMAGE_H

#include <vulkan/vulkan.h>

#include "../allocator/VulkanMemory.h"
#include "VulkanLogicalDevice.h"

class VulkanImage final
{
public:
    VulkanImage(const VkImage& inputImage);
    VulkanImage(std::shared_ptr<VulkanMemory> memory,
                VkImageType imageType,
                uint32_t width,
                uint32_t height,
                uint32_t depth,
                uint32_t mipLevelsCount,
                uint32_t arrayLayers,
                VkFormat format,
                VkImageTiling tiling,
                VkImageUsageFlags usage,
                const VmaMemoryUsage& memoryUsage);
    virtual ~VulkanImage();

    [[nodiscard]] VkImage GetRaw() const;
private:
    std::shared_ptr<VulkanMemory> Memory;

    VkImage InternalImage = VK_NULL_HANDLE;
    VmaAllocation InternalAllocation = VK_NULL_HANDLE;
    VmaAllocationInfo InternalAllocationInfo{};
};


#endif //CLUSEK_RT_VULKANIMAGE_H
