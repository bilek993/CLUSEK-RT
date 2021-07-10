//
// Created by jbili on 05.05.2021.
//

#include "VulkanSwapChain.h"

#include <algorithm>

VulkanSwapChain::VulkanSwapChain(std::shared_ptr<VulkanLogicalDevice> logicalDevice,
                                 const VulkanPhysicalDevice& physicalDevice,
                                 const VulkanSurface& surface,
                                 Window& window,
                                 const VkSurfaceFormatKHR requestedFormat,
                                 const std::vector<VkPresentModeKHR>& requestedPresentationModes)
{
    LogicalDevice = std::move(logicalDevice);
    Format = requestedFormat;

    const auto isFormatSupported = CheckRequestedFormatSupport(surface, physicalDevice, requestedFormat);
    if (isFormatSupported)
        throw std::runtime_error("Requested Swap Chain format is not supported!");

    const auto capabilities = GetSurfaceCapabilities(surface, physicalDevice);

    const auto presentationMode = SelectPresentationMode(physicalDevice, surface, requestedPresentationModes);
    Extent = GenerateExtent(capabilities, window);

    VkSwapchainCreateInfoKHR swapchainCreateInfo{};
    swapchainCreateInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    swapchainCreateInfo.surface = surface.GetRaw();
    swapchainCreateInfo.minImageCount = std::min(capabilities.maxImageCount, capabilities.minImageCount + 1);
    swapchainCreateInfo.imageFormat = requestedFormat.format;
    swapchainCreateInfo.imageColorSpace = requestedFormat.colorSpace;
    swapchainCreateInfo.imageExtent = Extent;
    swapchainCreateInfo.imageArrayLayers = 1;
    swapchainCreateInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
    swapchainCreateInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
    swapchainCreateInfo.queueFamilyIndexCount = 0;
    swapchainCreateInfo.pQueueFamilyIndices = nullptr;
    swapchainCreateInfo.preTransform = capabilities.currentTransform;
    swapchainCreateInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    swapchainCreateInfo.presentMode = presentationMode;
    swapchainCreateInfo.clipped = VK_TRUE;
    swapchainCreateInfo.oldSwapchain = VK_NULL_HANDLE;

    auto result = vkCreateSwapchainKHR(LogicalDevice->GetRaw(),
                                       &swapchainCreateInfo,
                                       nullptr,
                                       &InternalSwapchain);
    if (result != VK_SUCCESS)
        throw std::runtime_error("Critical error when creating Vulkan Swap Chain!");

    uint32_t imageCount;
    result = vkGetSwapchainImagesKHR(LogicalDevice->GetRaw(), InternalSwapchain, &imageCount, nullptr);
    if (result != VK_SUCCESS)
        throw std::runtime_error("Error retrieving swapchain images!");

    std::vector<VkImage> vulkanImages(imageCount);
    InternalSwapchainImages.resize(imageCount);
    InternalSwapchainImageViews.resize(imageCount);

    result = vkGetSwapchainImagesKHR(LogicalDevice->GetRaw(), InternalSwapchain, &imageCount, vulkanImages.data());
    if (result != VK_SUCCESS)
        throw std::runtime_error("Error retrieving swapchain images!");

    for (uint32_t i = 0; i < imageCount; i++)
    {
        InternalSwapchainImages[i] = std::make_shared<VulkanImage>(vulkanImages[i]);
        InternalSwapchainImageViews[i] = std::make_shared<VulkanImageView>(LogicalDevice,
                                                                           *InternalSwapchainImages[i],
                                                                           VK_IMAGE_VIEW_TYPE_2D,
                                                                           Format.format,
                                                                           VK_IMAGE_ASPECT_COLOR_BIT,
                                                                           0,
                                                                           1,
                                                                           0,
                                                                           1);
    }
}

VulkanSwapChain::~VulkanSwapChain()
{
    if (InternalSwapchain != VK_NULL_HANDLE)
        vkDestroySwapchainKHR(LogicalDevice->GetRaw(), InternalSwapchain, nullptr);
}

std::vector<std::shared_ptr<VulkanImage>> VulkanSwapChain::GetImages()
{
    return InternalSwapchainImages;
}

std::shared_ptr<VulkanImage> VulkanSwapChain::GetImage(int id)
{
    return InternalSwapchainImages[id];
}

std::size_t VulkanSwapChain::GetImageCount()
{
    return InternalSwapchainImages.size();
}

std::vector<std::shared_ptr<VulkanImageView>> VulkanSwapChain::GetImageViews()
{
    return InternalSwapchainImageViews;
}

std::shared_ptr<VulkanImageView> VulkanSwapChain::GetImageView(int id)
{
    return InternalSwapchainImageViews[id];
}

std::size_t VulkanSwapChain::GetImageViewCount()
{
    return InternalSwapchainImageViews.size();
}

VkExtent2D VulkanSwapChain::GetUsedExtent() const
{
    return Extent;
}

VkSurfaceFormatKHR VulkanSwapChain::GetUsedFormat() const
{
    return Format;
}

VkSwapchainKHR VulkanSwapChain::GetRaw() const
{
    return InternalSwapchain;
}

VkSurfaceCapabilitiesKHR VulkanSwapChain::GetSurfaceCapabilities(const VulkanSurface& surface,
                                                                 const VulkanPhysicalDevice& physicalDevice)
{
    VkSurfaceCapabilitiesKHR capabilities;
    const auto result = vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice.GetRaw(),
                                                                  surface.GetRaw(),
                                                                  &capabilities);
    if (result != VK_SUCCESS)
        throw std::runtime_error("Critical error when getting surface capabilities!");

    return capabilities;
}

bool VulkanSwapChain::CheckRequestedFormatSupport(const VulkanSurface& surface,
                                                  const VulkanPhysicalDevice& physicalDevice,
                                                  const VkSurfaceFormatKHR requestedFormat)
{
    uint32_t supportedFormatsCount;
    auto result = vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice.GetRaw(),
                                                       surface.GetRaw(),
                                                       &supportedFormatsCount,
                                                       nullptr);
    if (result != VK_SUCCESS)
        throw std::runtime_error("Critical error when getting surface formats!");

    std::vector<VkSurfaceFormatKHR> supportedFormats{ supportedFormatsCount };
    result = vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice.GetRaw(),
                                                  surface.GetRaw(),
                                                  &supportedFormatsCount,
                                                  supportedFormats.data());
    if (result != VK_SUCCESS)
        throw std::runtime_error("Critical error when getting surface formats!");


    return std::any_of(supportedFormats.cbegin(), supportedFormats.cend(), [&requestedFormat](VkSurfaceFormatKHR format)
    {
        return format.format == requestedFormat.format && format.colorSpace && requestedFormat.colorSpace;
    });
}

VkPresentModeKHR VulkanSwapChain::SelectPresentationMode(const VulkanPhysicalDevice& physicalDevice,
                                                         const VulkanSurface& surface,
                                                         const std::vector<VkPresentModeKHR>& requestedPresentationModes)
{
    uint32_t supportedPresentModesCount;
    auto result = vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice.GetRaw(),
                                                            surface.GetRaw(),
                                                            &supportedPresentModesCount,
                                                            nullptr);
    if (result != VK_SUCCESS)
        throw std::runtime_error("Critical error when getting surface presentation modes!");

    std::vector<VkPresentModeKHR> supportedPresentModes{ supportedPresentModesCount };
    result = vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice.GetRaw(),
                                                       surface.GetRaw(),
                                                       &supportedPresentModesCount,
                                                       supportedPresentModes.data());
    if (result != VK_SUCCESS)
        throw std::runtime_error("Critical error when getting surface presentation modes!");

    for (auto requestedPresentationMode : requestedPresentationModes)
        for (auto supportedPresentMode : supportedPresentModes)
            if (requestedPresentationMode == supportedPresentMode) return requestedPresentationMode;

    throw std::runtime_error("Found 0 compatible presentation modes (based on requested values)!");
}

VkExtent2D VulkanSwapChain::GenerateExtent(const VkSurfaceCapabilitiesKHR& capabilities,
                                           Window& window)
{
    if (capabilities.currentExtent.width != UINT32_MAX)
        return capabilities.currentExtent;

    window.UpdateSize();

    const auto& minExtent = capabilities.minImageExtent;
    const auto& maxExtent = capabilities.maxImageExtent;

    const auto width = std::clamp(static_cast<uint32_t>(window.GetWidth()), minExtent.width, maxExtent.width);
    const auto height = std::clamp(static_cast<uint32_t>(window.GetHeight()), minExtent.height, maxExtent.height);

    return { width, height };
}

VkResult VulkanSwapChain::AcquireNextImage(const VulkanSemaphore& semaphore,
                                           const VulkanFence& fence,
                                           uint32_t* outputImageIndex,
                                           const uint64_t timeout)
{
    if (outputImageIndex == nullptr)
        throw std::invalid_argument("`outputImageIndex` parameter cannot be nullptr!");

    return vkAcquireNextImageKHR(LogicalDevice->GetRaw(),
                                 InternalSwapchain,
                                 timeout,
                                 semaphore.GetRaw(),
                                 fence.GetRaw(),
                                 outputImageIndex);
}
