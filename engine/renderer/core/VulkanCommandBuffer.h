//
// Created by jbili on 24.05.2021.
//

#ifndef CLUSEK_RT_VULKANCOMMANDBUFFER_H
#define CLUSEK_RT_VULKANCOMMANDBUFFER_H

#include <vulkan/vulkan.h>
#include <algorithm>

#include "VulkanLogicalDevice.h"
#include "VulkanCommandPool.h"
#include "VulkanBuffer.h"

template<class T>
class VulkanVertexBuffer;

class VulkanIndexBuffer;

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

    void BeginRenderPass(const VkRenderPassBeginInfo& renderPassBeginInfo);
    void EndRenderPass();

    template<class P>
    void BindPipeline(const P& pipeline, VkPipelineBindPoint bindPoint);

    template<class T>
    void BindVertexBuffer(const std::vector<VulkanVertexBuffer<T>*>& vertexBuffers,
                          const std::vector<VkDeviceSize>& offsets,
                          uint32_t firstBinding = 0);
    void BindIndexBuffer(const VulkanIndexBuffer& indexBuffer,
                         VkDeviceSize offset = 0);

    void Draw(uint32_t indexCount,
              uint32_t instanceCount = 1,
              uint32_t firstIndex = 0,
              int32_t vertexOffset = 0,
              uint32_t firstInstance = 0);

    void CopyBuffer(VulkanBuffer& srcBuffer, VulkanBuffer& dstBuffer, VkDeviceSize bufferSize);

    void AddBarrier(VkPipelineStageFlags srcStageMask,
                    VkPipelineStageFlags dstStageMask,
                    VkDependencyFlags dependencyFlags,
                    const std::vector<VkMemoryBarrier>& memoryBarriers,
                    const std::vector<VkBufferMemoryBarrier>& bufferMemoryBarriers,
                    const std::vector<VkImageMemoryBarrier>& imageMemoryBarriers);

    [[nodiscard]] VkCommandBuffer GetRaw() const;
    VkCommandBuffer* GetPointerToRaw();

private:
    VkCommandBuffer InternalCommandBuffer = VK_NULL_HANDLE;

    std::shared_ptr<VulkanLogicalDevice> LogicalDevice;
    std::shared_ptr<VulkanCommandPool> CommandPool;

    VkCommandBufferLevel CommandBufferLevel;

    bool RecordingInProgress = false;
};

template<class P>
void VulkanCommandBuffer::BindPipeline(const P& pipeline, VkPipelineBindPoint bindPoint)
{
    vkCmdBindPipeline(InternalCommandBuffer, bindPoint, pipeline.GetRaw());
}

template<class T>
void VulkanCommandBuffer::BindVertexBuffer(const std::vector<VulkanVertexBuffer<T>*>& vertexBuffers,
                                           const std::vector<VkDeviceSize>& offsets,
                                           uint32_t firstBinding)
{
    if (vertexBuffers.size() != offsets.size())
        throw std::invalid_argument("Incorrect number of offsets elements!");

    std::vector<VkBuffer> vulkanVertexBuffers{};
    std::transform(vertexBuffers.begin(), vertexBuffers.end(),
                   std::back_inserter(vulkanVertexBuffers), [](VulkanVertexBuffer<T>* vertexBuffer)
                   { return vertexBuffer->GetRaw(); });

    vkCmdBindVertexBuffers(InternalCommandBuffer, 0, vertexBuffers.size(), vulkanVertexBuffers.data(), offsets.data());
}

#endif //CLUSEK_RT_VULKANCOMMANDBUFFER_H
