//
// Created by jbili on 06.07.2021.
//

#ifndef CLUSEK_RT_VULKANFRAMEBUFFER_H
#define CLUSEK_RT_VULKANFRAMEBUFFER_H

#include <vulkan/vulkan.h>
#include <memory>

#include "VulkanLogicalDevice.h"
#include "VulkanRenderPass.h"
#include "VulkanImageView.h"

class VulkanFrameBuffer final
{
public:
    VulkanFrameBuffer(std::shared_ptr<VulkanLogicalDevice> logicalDevice,
                      const VulkanRenderPass& renderPass,
                      const std::vector<VulkanImageView>& attachments,
                      uint32_t width,
                      uint32_t height,
                      uint32_t layers);
    ~VulkanFrameBuffer();
    VulkanFrameBuffer(const VulkanFrameBuffer& other) = delete;
    VulkanFrameBuffer(VulkanFrameBuffer&& other) noexcept = delete;
    VulkanFrameBuffer& operator=(const VulkanFrameBuffer& other) = delete;
    VulkanFrameBuffer& operator=(VulkanFrameBuffer&& other) noexcept = delete;

    [[nodiscard]] VkFramebuffer GetRaw() const;

private:
    VkFramebuffer InternalFrameBuffer = VK_NULL_HANDLE;
    std::shared_ptr<VulkanLogicalDevice> LogicalDevice;
};


#endif //CLUSEK_RT_VULKANFRAMEBUFFER_H
