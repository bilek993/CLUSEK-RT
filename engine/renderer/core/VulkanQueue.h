//
// Created by jbili on 16.04.2021.
//

#ifndef CLUSEK_RT_VULKANQUEUE_H
#define CLUSEK_RT_VULKANQUEUE_H

#include <vulkan/vulkan.h>

struct VulkanQueue final
{
    uint32_t FamilyIndex = 0;
    VkQueue Queue = VK_NULL_HANDLE;
    bool SupportPresentation = false;
};


#endif //CLUSEK_RT_VULKANQUEUE_H
