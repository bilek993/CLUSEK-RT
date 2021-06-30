//
// Created by jbili on 28.06.2021.
//

#include "VulkanRenderPass.h"

#include "../../common/debug/Logger.h"

VulkanRenderPass::VulkanRenderPass(std::shared_ptr<VulkanLogicalDevice> logicalDevice,
                                   const std::vector<VkAttachmentDescription>& attachmentDescriptions,
                                   bool lastElementIsDepthStencil,
                                   const std::vector<VkSubpassDependency>& dependencies,
                                   const std::vector<VulkanSubpass>& subpasses)
{
    LogicalDevice = std::move(logicalDevice);

    std::vector<VkAttachmentReference> attachmentReferences{ attachmentDescriptions.size() };
    for (auto i = 0; i < attachmentDescriptions.size(); i++)
    {
        attachmentReferences[i].attachment = i;
        attachmentReferences[i].layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
    }

    if (lastElementIsDepthStencil)
        attachmentReferences.back().layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

    std::vector<VkSubpassDescription> subpassDescription{ subpasses.size() };
    std::vector<std::vector<VkAttachmentReference>> subpassAttachmentBindings{ subpasses.size() };

    for (auto i = 0; i < subpasses.size(); i++)
    {
        for (auto& colorAttachmentIdsForCurrentSubpass : subpasses[i].UsedColorAttachmentsIds)
        {
            if (colorAttachmentIdsForCurrentSubpass >= attachmentReferences.size())
                LOG_ERROR("Incorrect index passed into subpass data!");
            else
                subpassAttachmentBindings[i].emplace_back(attachmentReferences[colorAttachmentIdsForCurrentSubpass]);
        }

        subpassDescription[i].colorAttachmentCount = subpasses[i].UsedColorAttachmentsIds.size();
        subpassDescription[i].pColorAttachments = subpassAttachmentBindings[i].data();

        if (subpasses[i].UseDepthStencilAttachment)
        {
            if (lastElementIsDepthStencil)
                subpassDescription[i].pDepthStencilAttachment = &attachmentReferences.back();
            else
                LOG_WARNING(
                        "Cannot set depth-stencil attachment reference without any depth-stencil attachment passed.");
        }
    }

    VkRenderPassCreateInfo renderPassInfo{};
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    renderPassInfo.attachmentCount = attachmentDescriptions.size();
    renderPassInfo.pAttachments = attachmentDescriptions.data();
    renderPassInfo.subpassCount = subpassDescription.size();
    renderPassInfo.pSubpasses = subpassDescription.data();
    renderPassInfo.dependencyCount = dependencies.size();
    renderPassInfo.pDependencies = dependencies.data();

    const auto result = vkCreateRenderPass(LogicalDevice->GetRaw(),
                                           &renderPassInfo,
                                           nullptr,
                                           &InternalRenderPass);
    if (result != VK_SUCCESS)
        throw std::runtime_error("Creating render pass failed!");
}

VulkanRenderPass::~VulkanRenderPass()
{
    if (InternalRenderPass != VK_NULL_HANDLE)
        vkDestroyRenderPass(LogicalDevice->GetRaw(), InternalRenderPass, nullptr);
}

VkRenderPass VulkanRenderPass::GetRaw() const
{
    return InternalRenderPass;
}
