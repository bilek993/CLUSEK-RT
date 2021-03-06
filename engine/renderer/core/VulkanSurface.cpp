//
// Created by jbili on 28.04.2021.
//

#include "VulkanSurface.h"

VulkanSurface::VulkanSurface(std::shared_ptr<VulkanInstance> instance, const Window& window)
{
    Instance = std::move(instance);

    const auto result = glfwCreateWindowSurface(Instance->GetRaw(), window.GetRaw(), nullptr, &InternalSurface);
    if (result != VK_SUCCESS)
        throw std::runtime_error("Window surface cannot be created!");
}

VulkanSurface::~VulkanSurface()
{
    if (InternalSurface != VK_NULL_HANDLE)
        vkDestroySurfaceKHR(Instance->GetRaw(), InternalSurface, nullptr);
}

VkSurfaceKHR VulkanSurface::GetRaw() const
{
    return InternalSurface;
}
