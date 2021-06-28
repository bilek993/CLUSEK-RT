//
// Created by jbili on 28.06.2021.
//

#ifndef CLUSEK_RT_VULKANPIPELINELAYOUT_H
#define CLUSEK_RT_VULKANPIPELINELAYOUT_H


class VulkanPipelineLayout final
{
public:
    VulkanPipelineLayout();
    ~VulkanPipelineLayout();
    VulkanPipelineLayout(const VulkanPipelineLayout& other) = delete;
    VulkanPipelineLayout(VulkanPipelineLayout&& other) noexcept = delete;
    VulkanPipelineLayout& operator=(const VulkanPipelineLayout& other) = delete;
    VulkanPipelineLayout& operator=(VulkanPipelineLayout&& other) noexcept = delete;
};


#endif //CLUSEK_RT_VULKANPIPELINELAYOUT_H
