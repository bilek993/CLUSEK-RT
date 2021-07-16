//
// Created by jbili on 28.06.2021.
//

#ifndef CLUSEK_RT_VULKANRENDERPASS_H
#define CLUSEK_RT_VULKANRENDERPASS_H

#include <memory>
#include <vector>
#include <vulkan/vulkan.h>

#include "../helpers/VulkanSubpass.h"
#include "VulkanLogicalDevice.h"

class VulkanFrameBuffer;

class VulkanRenderPass final
{
public:
    VulkanRenderPass(std::shared_ptr<VulkanLogicalDevice> logicalDevice,
                     const std::vector<VkAttachmentDescription>& attachmentDescriptions,
                     bool lastElementIsDepthStencil,
                     const std::vector<VkSubpassDependency>& dependencies,
                     const std::vector<VulkanSubpass>& subpasses);
    ~VulkanRenderPass();
    VulkanRenderPass(const VulkanRenderPass& other) = delete;
    VulkanRenderPass(VulkanRenderPass&& other) noexcept = delete;
    VulkanRenderPass& operator=(const VulkanRenderPass& other) = delete;
    VulkanRenderPass& operator=(VulkanRenderPass&& other) noexcept = delete;

    [[nodiscard]] VkRenderPassBeginInfo GenerateRenderPassBeginInfo(const VulkanFrameBuffer& frameBuffer,
                                                                    const VkRect2D& renderArea,
                                                                    const std::vector<VkClearValue>* clearValues) const;

    [[nodiscard]] VkRenderPass
    GetRaw() const;

private:
    VkRenderPass InternalRenderPass = VK_NULL_HANDLE;
    std::shared_ptr<VulkanLogicalDevice> LogicalDevice;
};


#endif //CLUSEK_RT_VULKANRENDERPASS_H
