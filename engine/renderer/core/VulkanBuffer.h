//
// Created by jbili on 26.04.2021.
//

#ifndef CLUSEK_RT_VULKANBUFFER_H
#define CLUSEK_RT_VULKANBUFFER_H

#include <vulkan/vulkan.h>
#include <vk_mem_alloc.h>
#include <memory>

#include "../allocator/VulkanMemory.h"

class VulkanBuffer final
{
public:
    VulkanBuffer(std::shared_ptr<VulkanMemory> memory,
                 const VkBufferUsageFlags bufferUsage,
                 const VkMemoryPropertyFlags requiredMemoryProperties,
                 const VkMemoryPropertyFlags preferredMemoryProperties,
                 const VmaAllocationCreateFlags allocationCreateFlags,
                 const VkDeviceSize bufferSize);
    virtual ~VulkanBuffer();

    void MapBuffer(void* mappedData) const;
    void UnmapBuffer() const;

    [[nodiscard]] VkBuffer GetRaw() const;
private:
    VkBuffer InternalBuffer = VK_NULL_HANDLE;
    VmaAllocation InternalAllocation = VK_NULL_HANDLE;
    VmaAllocationInfo InternalAllocationInfo = VK_NULL_HANDLE;

    std::shared_ptr<VulkanMemory> Memory;
};

#endif //CLUSEK_RT_VULKANBUFFER_H
