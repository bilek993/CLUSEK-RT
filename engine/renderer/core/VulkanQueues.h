//
// Created by jbili on 16.04.2021.
//

#ifndef CLUSEK_RT_VULKANQUEUES_H
#define CLUSEK_RT_VULKANQUEUES_H


class VulkanQueues final
{
public:
    VulkanQueues() = default;
    ~VulkanQueues() = default;
    VulkanQueues(const VulkanQueues& other) = delete;
    VulkanQueues(VulkanQueues&& other) noexcept = delete;
    VulkanQueues& operator=(const VulkanQueues& other) = delete;
    VulkanQueues& operator=(VulkanQueues&& other) noexcept = delete;

private:
};


#endif //CLUSEK_RT_VULKANQUEUES_H
