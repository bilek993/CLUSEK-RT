//
// Created by jbili on 05.05.2021.
//

#include "VulkanSwapChain.h"

#include <algorithm>

VulkanSwapChain::VulkanSwapChain(std::shared_ptr<VulkanLogicalDevice> logicalDevice,
                                 const std::shared_ptr<VulkanPhysicalDevice> physicalDevice,
                                 const std::shared_ptr<VulkanSurface> surface,
                                 const std::shared_ptr<Window> window,
                                 const VkSurfaceFormatKHR requestedFormat,
                                 const std::vector<VkPresentModeKHR>& requestedPresentationModes)
{
    LogicalDevice = std::move(logicalDevice);

    const auto isFormatSupported = CheckRequestedFormatSupport(surface, physicalDevice, requestedFormat);
    if (isFormatSupported)
        throw std::runtime_error("Requested Swap Chain format is not supported!");

    const auto presentationMode = SelectPresentationMode(physicalDevice, surface, requestedPresentationModes);
    const auto extend = GenerateExtend(surface, physicalDevice, window);
}

VulkanSwapChain::~VulkanSwapChain()
{
    vkDestroySwapchainKHR(LogicalDevice->GetRaw(), InternalSwapchain, nullptr);
}

bool VulkanSwapChain::CheckRequestedFormatSupport(const std::shared_ptr<VulkanSurface> surface,
                                                  const std::shared_ptr<VulkanPhysicalDevice> physicalDevice,
                                                  const VkSurfaceFormatKHR requestedFormat)
{
    uint32_t supportedFormatsCount;
    auto result = vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice->GetRaw(),
                                                       surface->GetRaw(),
                                                       &supportedFormatsCount,
                                                       nullptr);
    if (result != VK_SUCCESS)
        throw std::runtime_error("Critical error when getting surface formats!");

    std::vector<VkSurfaceFormatKHR> supportedFormats{ supportedFormatsCount };
    result = vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice->GetRaw(),
                                                  surface->GetRaw(),
                                                  &supportedFormatsCount,
                                                  supportedFormats.data());
    if (result != VK_SUCCESS)
        throw std::runtime_error("Critical error when getting surface formats!");


    return std::any_of(supportedFormats.cbegin(), supportedFormats.cend(), [&requestedFormat](VkSurfaceFormatKHR format)
    {
        return format.format == requestedFormat.format && format.colorSpace && requestedFormat.colorSpace;
    });
}

VkPresentModeKHR VulkanSwapChain::SelectPresentationMode(const std::shared_ptr<VulkanPhysicalDevice> physicalDevice,
                                                         const std::shared_ptr<VulkanSurface> surface,
                                                         const std::vector<VkPresentModeKHR>& requestedPresentationModes)
{
    uint32_t supportedPresentModesCount;
    auto result = vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice->GetRaw(),
                                                            surface->GetRaw(),
                                                            &supportedPresentModesCount,
                                                            nullptr);
    if (result != VK_SUCCESS)
        throw std::runtime_error("Critical error when getting surface presentation modes!");

    std::vector<VkPresentModeKHR> supportedPresentModes{ supportedPresentModesCount };
    result = vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice->GetRaw(),
                                                       surface->GetRaw(),
                                                       &supportedPresentModesCount,
                                                       supportedPresentModes.data());
    if (result != VK_SUCCESS)
        throw std::runtime_error("Critical error when getting surface presentation modes!");

    for (auto requestedPresentationMode : requestedPresentationModes)
        for (auto supportedPresentMode : supportedPresentModes)
            if (requestedPresentationMode == supportedPresentMode) return requestedPresentationMode;

    throw std::runtime_error("Found 0 compatible presentation modes (based on requested values)!");
}

VkExtent2D VulkanSwapChain::GenerateExtend(const std::shared_ptr<VulkanSurface> surface,
                                           const std::shared_ptr<VulkanPhysicalDevice> physicalDevice,
                                           const std::shared_ptr<Window> window)
{
    VkSurfaceCapabilitiesKHR capabilities;
    const auto result = vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice->GetRaw(),
                                                                  surface->GetRaw(),
                                                                  &capabilities);
    if (result != VK_SUCCESS)
        throw std::runtime_error("Critical error when getting surface capabilities!");

    if (capabilities.currentExtent.width != UINT32_MAX)
    {
        return capabilities.currentExtent;
    }
    else
    {
        window->UpdateSize();

        const auto& minExtend = capabilities.minImageExtent;
        const auto& maxExtend = capabilities.maxImageExtent;

        const auto width = std::clamp(static_cast<uint32_t>(window->GetWidth()), minExtend.width, maxExtend.width);
        const auto height = std::clamp(static_cast<uint32_t>(window->GetHeight()), minExtend.height, maxExtend.height);

        return { width, height };
    }
}
