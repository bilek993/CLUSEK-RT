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
#include "VulkanImage.h"
#include "VulkanImageView.h"
#include "../../window/Window.h"

class VulkanSwapChain final
{
public:
    VulkanSwapChain(std::shared_ptr<VulkanLogicalDevice> logicalDevice,
                    const VulkanPhysicalDevice& physicalDevice,
                    const VulkanSurface& surface,
                    Window& window,
                    VkSurfaceFormatKHR requestedFormat,
                    const std::vector<VkPresentModeKHR>& requestedPresentationModes);
    ~VulkanSwapChain();
    VulkanSwapChain(const VulkanSwapChain& other) = delete;
    VulkanSwapChain(VulkanSwapChain&& other) noexcept = delete;
    VulkanSwapChain& operator=(const VulkanSwapChain& other) = delete;
    VulkanSwapChain& operator=(VulkanSwapChain&& other) noexcept = delete;

    std::vector<std::shared_ptr<VulkanImage>> GetImages();
    std::shared_ptr<VulkanImage> GetImage(int id);
    std::size_t GetImageCount();

    std::vector<std::shared_ptr<VulkanImageView>> GetImageViews();
    std::shared_ptr<VulkanImageView> GetImageView(int id);
    std::size_t GetImageViewCount();

    [[nodiscard]] VkExtent2D GetUsedExtent() const;
    [[nodiscard]] VkSurfaceFormatKHR GetUsedFormat() const;

    [[nodiscard]] VkSwapchainKHR GetRaw() const;

private:
    static VkSurfaceCapabilitiesKHR GetSurfaceCapabilities(const VulkanSurface& surface,
                                                           const VulkanPhysicalDevice& physicalDevice);

    static bool CheckRequestedFormatSupport(const VulkanSurface& surface,
                                            const VulkanPhysicalDevice& physicalDevice,
                                            VkSurfaceFormatKHR requestedFormat);
    static VkPresentModeKHR SelectPresentationMode(const VulkanPhysicalDevice& physicalDevice,
                                                   const VulkanSurface& surface,
                                                   const std::vector<VkPresentModeKHR>& requestedPresentationModes);
    static VkExtent2D GenerateExtent(const VkSurfaceCapabilitiesKHR& capabilities,
                                     Window& window);

    VkSwapchainKHR InternalSwapchain = VK_NULL_HANDLE;
    VkExtent2D Extent;
    VkSurfaceFormatKHR Format;
    std::shared_ptr<VulkanLogicalDevice> LogicalDevice;

    std::vector<std::shared_ptr<VulkanImage>> InternalSwapchainImages{};
    std::vector<std::shared_ptr<VulkanImageView>> InternalSwapchainImageViews{};
};


#endif //CLUSEK_RT_VULKANSWAPCHAIN_H
