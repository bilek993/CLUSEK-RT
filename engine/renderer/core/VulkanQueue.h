//
// Created by jbili on 16.04.2021.
//

#ifndef CLUSEK_RT_VULKANQUEUE_H
#define CLUSEK_RT_VULKANQUEUE_H

#include <vulkan/vulkan.h>
#include <memory>
#include <vector>

class VulkanCommandBuffer;

class VulkanSemaphore;

class VulkanFence;

class VulkanQueue final
{
public:
    VulkanQueue();
    VulkanQueue(uint32_t familyIndex, bool supportPresentation);

    void WaitIdle();

    [[nodiscard]] uint32_t GetFamilyIndex() const;
    [[nodiscard]] bool IsSupportingPresentation() const;

    void Submit(const std::vector<VulkanCommandBuffer*>& commandBuffers);
    void Submit(const std::vector<VulkanCommandBuffer*>& commandBuffers,
                const std::vector<VulkanSemaphore*>& waitSemaphores,
                const std::vector<VulkanSemaphore*>& signalSemaphores,
                const VulkanFence* signalFence,
                const VkPipelineStageFlags* waitDestinationStageMask);

    [[nodiscard]] VkQueue GetRaw() const;
    VkQueue* GetPointerToRaw();
private:
    uint32_t FamilyIndex = 0;
    bool SupportPresentation = false;

    VkQueue InternalQueue = VK_NULL_HANDLE;
};


#endif //CLUSEK_RT_VULKANQUEUE_H
