//
// Created by jbili on 03.04.2021.
//

#ifndef CLUSEK_RT_VULKANINSTANCE_H
#define CLUSEK_RT_VULKANINSTANCE_H

#include <vulkan/vulkan.h>

class VulkanInstance
{
public:
    VulkanInstance();
    ~VulkanInstance();
    VulkanInstance(const VulkanInstance& other) = delete;
    VulkanInstance(VulkanInstance&& other) noexcept = delete;
    VulkanInstance& operator=(const VulkanInstance& other) = delete;
    VulkanInstance& operator=(VulkanInstance&& other) noexcept = delete;

private:
    VkInstance InternalInstance;
};


#endif //CLUSEK_RT_VULKANINSTANCE_H
