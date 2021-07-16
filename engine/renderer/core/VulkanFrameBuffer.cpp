//
// Created by jbili on 06.07.2021.
//

#include "VulkanFrameBuffer.h"

#include <algorithm>

VulkanFrameBuffer::VulkanFrameBuffer(std::shared_ptr<VulkanLogicalDevice> logicalDevice,
                                     const VulkanRenderPass& renderPass,
                                     const std::vector<VulkanImageView*>& attachments,
                                     const uint32_t width,
                                     const uint32_t height,
                                     const uint32_t layers)
{
    LogicalDevice = std::move(logicalDevice);

    std::vector<VkImageView> vulkanAttachments{};
    std::transform(attachments.begin(), attachments.end(),
                   std::back_inserter(vulkanAttachments), [](const VulkanImageView* attachment)
                   { return attachment->GetRaw(); });

    VkFramebufferCreateInfo framebufferCreateInfo{};
    framebufferCreateInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    framebufferCreateInfo.renderPass = renderPass.GetRaw();
    framebufferCreateInfo.attachmentCount = vulkanAttachments.size();
    framebufferCreateInfo.pAttachments = vulkanAttachments.data();
    framebufferCreateInfo.width = width;
    framebufferCreateInfo.height = height;
    framebufferCreateInfo.layers = layers;

    const auto result = vkCreateFramebuffer(LogicalDevice->GetRaw(),
                                            &framebufferCreateInfo,
                                            nullptr,
                                            &InternalFrameBuffer);
    if (result != VK_SUCCESS)
        throw std::runtime_error("Frame Buffer creation failed!");
}

VulkanFrameBuffer::~VulkanFrameBuffer()
{
    if (InternalFrameBuffer != VK_NULL_HANDLE)
        vkDestroyFramebuffer(LogicalDevice->GetRaw(), InternalFrameBuffer, nullptr);
}

VkFramebuffer VulkanFrameBuffer::GetRaw() const
{
    return InternalFrameBuffer;
}
