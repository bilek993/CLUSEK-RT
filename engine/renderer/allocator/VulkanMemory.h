//
// Created by jbili on 22.04.2021.
//

#ifndef CLUSEK_RT_VULKANMEMORY_H
#define CLUSEK_RT_VULKANMEMORY_H


class VulkanMemory
{
public:
    VulkanMemory();
    ~VulkanMemory();
    VulkanMemory(const VulkanMemory& other) = delete;
    VulkanMemory(VulkanMemory&& other) noexcept = delete;
    VulkanMemory& operator=(const VulkanMemory& other) = delete;
    VulkanMemory& operator=(VulkanMemory&& other) noexcept = delete;

private:
};


#endif //CLUSEK_RT_VULKANMEMORY_H
