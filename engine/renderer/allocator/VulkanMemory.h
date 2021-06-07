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

class VulkanMemory final
{
public:
    VulkanMemory(const VulkanInstance& vulkanInstance,
                 const VulkanPhysicalDevice& vulkanPhysicalDevice,
                 const VulkanLogicalDevice& vulkanLogicalDevice,
                 uint32_t vulkanApiVersion,
                 bool checkMemoryBeforeMapping);
    ~VulkanMemory();
    VulkanMemory(const VulkanMemory& other) = delete;
    VulkanMemory(VulkanMemory&& other) noexcept = delete;
    VulkanMemory& operator=(const VulkanMemory& other) = delete;
    VulkanMemory& operator=(VulkanMemory&& other) noexcept = delete;

    [[nodiscard]] bool IsMappable(const VmaAllocationInfo& allocationInfo) const;
    [[nodiscard]] bool ShouldCheckMemoryBeforeMapping() const;

    [[nodiscard]] VmaAllocator GetRaw() const;
private:
    VmaAllocator InternalAllocator = VK_NULL_HANDLE;

    bool CheckMemoryBeforeMapping = false;
};


#endif //CLUSEK_RT_VULKANMEMORY_H
