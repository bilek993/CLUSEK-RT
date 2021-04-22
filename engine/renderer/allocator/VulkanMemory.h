//
// Created by jbili on 22.04.2021.
//

#ifndef CLUSEK_RT_VULKANMEMORY_H
#define CLUSEK_RT_VULKANMEMORY_H

#include <vk_mem_alloc.h>
#include <memory>

#include "../core/VulkanInstance.h"
#include "../core/VulkanPhysicalDevice.h"
#include "../core/VulkanLogicalDevice.h"

class VulkanMemory
{
public:
    VulkanMemory(std::shared_ptr<VulkanInstance> vulkanInstance,
                 std::shared_ptr<VulkanPhysicalDevice> vulkanPhysicalDevice,
                 std::shared_ptr<VulkanLogicalDevice> vulkanLogicalDevice,
                 uint32_t vulkanApiVersion);
    ~VulkanMemory();
    VulkanMemory(const VulkanMemory& other) = delete;
    VulkanMemory(VulkanMemory&& other) noexcept = delete;
    VulkanMemory& operator=(const VulkanMemory& other) = delete;
    VulkanMemory& operator=(VulkanMemory&& other) noexcept = delete;

    [[nodiscard]] VmaAllocator GetRaw() const;

private:
    VmaAllocator InternalAllocator = VK_NULL_HANDLE;
};


#endif //CLUSEK_RT_VULKANMEMORY_H
