//
// Created by jbili on 28.06.2021.
//

#ifndef CLUSEK_RT_VULKANRENDERPASS_H
#define CLUSEK_RT_VULKANRENDERPASS_H


class VulkanRenderPass final
{
public:
    VulkanRenderPass();
    ~VulkanRenderPass();
    VulkanRenderPass(const VulkanRenderPass& other) = delete;
    VulkanRenderPass(VulkanRenderPass&& other) noexcept = delete;
    VulkanRenderPass& operator=(const VulkanRenderPass& other) = delete;
    VulkanRenderPass& operator=(VulkanRenderPass&& other) noexcept = delete;
};


#endif //CLUSEK_RT_VULKANRENDERPASS_H
