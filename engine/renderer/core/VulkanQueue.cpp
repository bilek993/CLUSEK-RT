//
// Created by jbili on 13.05.2021.
//

#include "VulkanQueue.h"

#include <stdexcept>
#include <algorithm>

#include "VulkanCommandBuffer.h"
#include "VulkanSemaphore.h"
#include "VulkanFence.h"

VulkanQueue::VulkanQueue()
{
}

VulkanQueue::VulkanQueue(uint32_t familyIndex, bool supportPresentation)
{
    FamilyIndex = familyIndex;
    SupportPresentation = supportPresentation;
}

void VulkanQueue::WaitIdle()
{
    const auto result = vkQueueWaitIdle(InternalQueue);
    if (result != VK_SUCCESS)
        throw std::runtime_error("Waiting for queue failed!");
}

uint32_t VulkanQueue::GetFamilyIndex() const
{
    return FamilyIndex;
}

bool VulkanQueue::IsSupportingPresentation() const
{
    return SupportPresentation;
}

void VulkanQueue::Submit(const std::vector<std::shared_ptr<VulkanCommandBuffer>>& commandBuffers)
{
    Submit(commandBuffers, {}, {}, nullptr, nullptr);
}

void VulkanQueue::Submit(const std::vector<std::shared_ptr<VulkanCommandBuffer>>& commandBuffers,
                         const std::vector<std::shared_ptr<VulkanSemaphore>>& waitSemaphores,
                         const std::vector<std::shared_ptr<VulkanSemaphore>>& signalSemaphores,
                         const std::shared_ptr<VulkanFence> signalFence,
                         const VkPipelineStageFlags* waitDestinationStageMask)
{
    std::vector<VkCommandBuffer> vkCommandBuffers;
    std::transform(commandBuffers.begin(), commandBuffers.end(),
                   std::back_inserter(vkCommandBuffers), [](std::shared_ptr<VulkanCommandBuffer> buffer)
                   { return buffer->GetRaw(); });

    std::vector<VkSemaphore> vkWaitSemaphores;
    std::transform(waitSemaphores.begin(), waitSemaphores.end(),
                   std::back_inserter(vkWaitSemaphores), [](std::shared_ptr<VulkanSemaphore> semaphore)
                   { return semaphore->GetRaw(); });

    std::vector<VkSemaphore> vkSignalSemaphores;
    std::transform(signalSemaphores.begin(), signalSemaphores.end(),
                   std::back_inserter(vkSignalSemaphores), [](std::shared_ptr<VulkanSemaphore> semaphore)
                   { return semaphore->GetRaw(); });

    const auto vkSignalFence = signalFence != nullptr ? signalFence->GetRaw() : VK_NULL_HANDLE;

    VkSubmitInfo submitInfo{};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submitInfo.commandBufferCount = vkCommandBuffers.size();
    submitInfo.pCommandBuffers = vkCommandBuffers.data();
    submitInfo.waitSemaphoreCount = vkWaitSemaphores.size();
    submitInfo.pWaitSemaphores = vkWaitSemaphores.data();
    submitInfo.signalSemaphoreCount = vkSignalSemaphores.size();
    submitInfo.pSignalSemaphores = vkSignalSemaphores.data();
    submitInfo.pWaitDstStageMask = waitDestinationStageMask;

    const auto result = vkQueueSubmit(InternalQueue, 1, &submitInfo, vkSignalFence);
    if (result != VK_SUCCESS)
        throw std::runtime_error("Submitting command buffers failed!");
}

VkQueue VulkanQueue::GetRaw() const
{
    return InternalQueue;
}

VkQueue* VulkanQueue::GetPointerToRaw()
{
    return &InternalQueue;
}
