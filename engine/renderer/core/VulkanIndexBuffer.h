//
// Created by jbili on 02.06.2021.
//

#ifndef CLUSEK_RT_VULKANINDEXBUFFER_H
#define CLUSEK_RT_VULKANINDEXBUFFER_H

#include <memory>
#include <vector>
#include <cstring>
#include <vulkan/vulkan.h>

#include "../allocator/VulkanMemory.h"
#include "../core/VulkanBuffer.h"
#include "../core/VulkanCommandBuffer.h"
#include "../../common/debug/Logger.h"

class VulkanIndexBuffer final
{
public:
    VulkanIndexBuffer(std::shared_ptr<VulkanMemory> memory);
    VulkanIndexBuffer(const VulkanIndexBuffer& other) = delete;
    VulkanIndexBuffer(VulkanIndexBuffer&& other) noexcept = delete;
    VulkanIndexBuffer& operator=(const VulkanIndexBuffer& other) = delete;
    VulkanIndexBuffer& operator=(VulkanIndexBuffer&& other) noexcept = delete;

    template<class T>
    void UploadData(VulkanCommandBuffer& commandBuffer,
                    std::vector<T> data,
                    VkIndexType indexUnitType);
    void CleanUpAfterUploading();

    [[nodiscard]] VkIndexType GetIndexType() const;

    [[nodiscard]] VkBuffer GetRaw() const;
    [[nodiscard]] std::shared_ptr<VulkanBuffer> Get() const;

private:
    std::shared_ptr<VulkanMemory> Memory;

    std::unique_ptr<VulkanBuffer> StagingBuffer;
    std::shared_ptr<VulkanBuffer> InternalIndexBuffer;

    VkIndexType IndexUnitType;
};

template<class T>
void VulkanIndexBuffer::UploadData(VulkanCommandBuffer& commandBuffer, std::vector<T> data, VkIndexType indexUnitType)
{
    LOG_DEBUG("Preparing data to be uploaded in index buffer...");

    IndexUnitType = indexUnitType;

    const auto bufferSize = data.size() * sizeof(T);

    StagingBuffer = std::make_unique<VulkanBuffer>(Memory,
                                                   VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
                                                   VMA_MEMORY_USAGE_CPU_ONLY,
                                                   bufferSize);

    void* pointerToBufferData;
    StagingBuffer->MapBuffer(&pointerToBufferData);
    memcpy(pointerToBufferData, data.data(), bufferSize);
    StagingBuffer->UnmapBuffer();

    InternalIndexBuffer = std::make_shared<VulkanBuffer>(Memory,
                                                         VK_BUFFER_USAGE_TRANSFER_DST_BIT |
                                                         VK_BUFFER_USAGE_INDEX_BUFFER_BIT,
                                                         VMA_MEMORY_USAGE_GPU_ONLY,
                                                         bufferSize);

    commandBuffer.CopyBuffer(*StagingBuffer, *InternalIndexBuffer, bufferSize);
}

#endif //CLUSEK_RT_VULKANINDEXBUFFER_H
