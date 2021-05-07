//
// Created by jbili on 07.05.2021.
//

#ifndef CLUSEK_RT_VULKANIMAGE_H
#define CLUSEK_RT_VULKANIMAGE_H

#include <vulkan/vulkan.h>

#include "VulkanLogicalDevice.h"

class VulkanImage final
{
public:
    VulkanImage(std::shared_ptr<VulkanLogicalDevice> logicalDevice,
                const VkImage& inputImage,
                bool autoDestroy);
    virtual ~VulkanImage();

    [[nodiscard]] VkImage GetRaw() const;
private:
    std::shared_ptr<VulkanLogicalDevice> LogicalDevice;

    VkImage InternalImage = VK_NULL_HANDLE;
    bool AutoDestroy = true;
};


#endif //CLUSEK_RT_VULKANIMAGE_H
