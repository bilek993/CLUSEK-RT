//
// Created by jbili on 05.05.2021.
//

#ifndef CLUSEK_RT_VULKANSWAPCHAIN_H
#define CLUSEK_RT_VULKANSWAPCHAIN_H

#include <vulkan/vulkan.h>
#include <memory>

#include "VulkanLogicalDevice.h"
#include "VulkanPhysicalDevice.h"
#include "VulkanSurface.h"
#include "../../window/Window.h"

class VulkanSwapChain final
{
public:
    /// The concurrent mode may result in bad performance on some devices. Consider using the exclusive mode
    /// by passing `VK_SHARING_MODE_EXCLUSIVE` into `sharingMode`, `0` into `queueFamilyIndexCount`
    /// and `nullptr` into `queueFamilyIndices` for consistent better performance on wide range of devices.
    VulkanSwapChain(std::shared_ptr<VulkanLogicalDevice> logicalDevice,
                    std::shared_ptr<VulkanPhysicalDevice> physicalDevice,
                    std::shared_ptr<VulkanSurface> surface,
                    std::shared_ptr<Window> window,
                    VkSurfaceFormatKHR requestedFormat,
                    const std::vector<VkPresentModeKHR>& requestedPresentationModes,
                    const VkSharingMode& sharingMode,
                    uint32_t queueFamilyIndexCount,
                    const uint32_t* queueFamilyIndices);
    ~VulkanSwapChain();
    VulkanSwapChain(const VulkanSwapChain& other) = delete;
    VulkanSwapChain(VulkanSwapChain&& other) noexcept = delete;
    VulkanSwapChain& operator=(const VulkanSwapChain& other) = delete;
    VulkanSwapChain& operator=(VulkanSwapChain&& other) noexcept = delete;

private:
    static VkSurfaceCapabilitiesKHR GetSurfaceCapabilities(std::shared_ptr<VulkanSurface> surface,
                                                           std::shared_ptr<VulkanPhysicalDevice> physicalDevice);

    static bool CheckRequestedFormatSupport(std::shared_ptr<VulkanSurface> surface,
                                            std::shared_ptr<VulkanPhysicalDevice> physicalDevice,
                                            VkSurfaceFormatKHR requestedFormat);
    static VkPresentModeKHR SelectPresentationMode(std::shared_ptr<VulkanPhysicalDevice> physicalDevice,
                                                   std::shared_ptr<VulkanSurface> surface,
                                                   const std::vector<VkPresentModeKHR>& requestedPresentationModes);
    static VkExtent2D GenerateExtent(const VkSurfaceCapabilitiesKHR& capabilities,
                                     std::shared_ptr<Window> window);

    VkSwapchainKHR InternalSwapchain = VK_NULL_HANDLE;
    std::shared_ptr<VulkanLogicalDevice> LogicalDevice;
};


#endif //CLUSEK_RT_VULKANSWAPCHAIN_H
