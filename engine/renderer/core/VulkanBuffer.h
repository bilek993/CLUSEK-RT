//
// Created by jbili on 26.04.2021.
//

#ifndef CLUSEK_RT_VULKANBUFFER_H
#define CLUSEK_RT_VULKANBUFFER_H

#include <vulkan/vulkan.h>
#include <vk_mem_alloc.h>

struct VulkanBuffer final
{
    VkBuffer Buffer;
    VmaAllocation Allocation;
    VmaAllocationInfo AllocationInfo;
};

#endif //CLUSEK_RT_VULKANBUFFER_H
