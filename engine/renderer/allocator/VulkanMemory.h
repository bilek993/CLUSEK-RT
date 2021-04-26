//
// Created by jbili on 22.04.2021.
//

#ifndef CLUSEK_RT_VULKANMEMORY_H
#define CLUSEK_RT_VULKANMEMORY_H

#include <vk_mem_alloc.h>
#include <memory>
#include <utility>

#include "../core/VulkanInstance.h"
#include "../core/VulkanPhysicalDevice.h"
#include "../core/VulkanLogicalDevice.h"
#include "../core/VulkanBuffer.h"

class VulkanMemory
{
public:
    VulkanMemory(std::shared_ptr<VulkanInstance> vulkanInstance,
                 std::shared_ptr<VulkanPhysicalDevice> vulkanPhysicalDevice,
                 std::shared_ptr<VulkanLogicalDevice> vulkanLogicalDevice,
                 uint32_t vulkanApiVersion,
                 bool checkMemoryBeforeMapping);
    ~VulkanMemory();
    VulkanMemory(const VulkanMemory& other) = delete;
    VulkanMemory(VulkanMemory&& other) noexcept = delete;
    VulkanMemory& operator=(const VulkanMemory& other) = delete;
    VulkanMemory& operator=(VulkanMemory&& other) noexcept = delete;

    [[nodiscard]] VulkanBuffer CreateBufferExclusive(VkBufferUsageFlags bufferUsage,
                                                     VkMemoryPropertyFlags requiredMemoryProperties,
                                                     VkMemoryPropertyFlags preferredMemoryProperties,
                                                     VmaAllocationCreateFlags allocationCreateFlags,
                                                     VkDeviceSize bufferSize) const;
    /// Consider using `CreateBufferExclusive` instead of this function due to potential performance impact.
    [[nodiscard]] VulkanBuffer CreateBufferConcurrent(VkBufferUsageFlags bufferUsage,
                                                      uint32_t queueFamilyIndexCount,
                                                      const uint32_t* queueFamilyIndices,
                                                      VkMemoryPropertyFlags requiredMemoryProperties,
                                                      VkMemoryPropertyFlags preferredMemoryProperties,
                                                      VmaAllocationCreateFlags allocationCreateFlags,
                                                      VkDeviceSize bufferSize) const;
    void DestroyBuffer(const VulkanBuffer& buffer) const;

    void MapBuffer(const VulkanBuffer& buffer, void* mappedData) const;
    void UnmapBuffer(const VulkanBuffer& buffer) const;

    [[nodiscard]] VmaAllocator GetRaw() const;
private:
    [[nodiscard]] VulkanBuffer CreateBuffer(VkBufferCreateInfo bufferInfo,
                                            VmaAllocationCreateInfo allocationCreateInfo) const;

    [[nodiscard]] bool IsMappable(const VulkanBuffer& buffer) const;

    VmaAllocator InternalAllocator = VK_NULL_HANDLE;

    bool CheckMemoryBeforeMapping = false;
};


#endif //CLUSEK_RT_VULKANMEMORY_H
