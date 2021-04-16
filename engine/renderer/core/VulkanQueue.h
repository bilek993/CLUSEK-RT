//
// Created by jbili on 16.04.2021.
//

#ifndef CLUSEK_RT_VULKANQUEUE_H
#define CLUSEK_RT_VULKANQUEUE_H

#include <vulkan/vulkan.h>

struct VulkanQueue final
{
    uint32_t Index = -1;
    VkQueue Queue = VK_NULL_HANDLE;
};


#endif //CLUSEK_RT_VULKANQUEUE_H
