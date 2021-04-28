//
// Created by jbili on 28.04.2021.
//

#ifndef CLUSEK_RT_VULKANSURFACE_H
#define CLUSEK_RT_VULKANSURFACE_H

#include <vulkan/vulkan.h>
#include <memory>

#include "VulkanInstance.h"
#include "../../window/Window.h"

class VulkanSurface
{
public:
    VulkanSurface(std::shared_ptr<VulkanInstance> instance, std::shared_ptr<Window> window);
    ~VulkanSurface();
    VulkanSurface(const VulkanSurface& other) = delete;
    VulkanSurface(VulkanSurface&& other) noexcept = delete;
    VulkanSurface& operator=(const VulkanSurface& other) = delete;
    VulkanSurface& operator=(VulkanSurface&& other) noexcept = delete;

    [[nodiscard]] VkSurfaceKHR GetRaw() const;
private:
    VkSurfaceKHR InternalSurface = VK_NULL_HANDLE;
    std::shared_ptr<VulkanInstance> Instance;
};


#endif //CLUSEK_RT_VULKANSURFACE_H
