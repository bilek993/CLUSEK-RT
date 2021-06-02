//
// Created by jbili on 24.05.2021.
//

#ifndef CLUSEK_RT_VULKANCOMMANDBUFFER_H
#define CLUSEK_RT_VULKANCOMMANDBUFFER_H

#include <vulkan/vulkan.h>

#include "VulkanLogicalDevice.h"
#include "VulkanCommandPool.h"

class VulkanCommandBuffer final
{
public:
    VulkanCommandBuffer(std::shared_ptr<VulkanLogicalDevice> logicalDevice,
                        std::shared_ptr<VulkanCommandPool> commandPool,
                        VkCommandBufferLevel level);
    ~VulkanCommandBuffer();
    VulkanCommandBuffer(const VulkanCommandBuffer& other) = delete;
    VulkanCommandBuffer(VulkanCommandBuffer&& other) noexcept = delete;
    VulkanCommandBuffer& operator=(const VulkanCommandBuffer& other) = delete;
    VulkanCommandBuffer& operator=(VulkanCommandBuffer&& other) noexcept = delete;

    void BeginRecording(bool oneTimeSubmit,
                        bool renderPassContinue,
                        bool useSimultaneous);
    void BeginRecording(bool oneTimeSubmit,
                        bool renderPassContinue,
                        bool useSimultaneous,
                        const VkCommandBufferInheritanceInfo* inheritanceInfo);
    void EndRecording();

    [[nodiscard]] bool IsRecording() const;

    [[nodiscard]] VkCommandBuffer GetRaw() const;
    VkCommandBuffer* GetPointerToRaw();

private:
    VkCommandBuffer InternalCommandBuffer = VK_NULL_HANDLE;

    std::shared_ptr<VulkanLogicalDevice> LogicalDevice;
    std::shared_ptr<VulkanCommandPool> CommandPool;

    bool RecordingInProgress = false;
};


#endif //CLUSEK_RT_VULKANCOMMANDBUFFER_H
