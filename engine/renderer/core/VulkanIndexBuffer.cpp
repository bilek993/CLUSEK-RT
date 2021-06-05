//
// Created by jbili on 02.06.2021.
//

#include "VulkanIndexBuffer.h"

#include "../../common/debug/Logger.h"

VulkanIndexBuffer::VulkanIndexBuffer(std::shared_ptr<VulkanMemory> memory)
{
    LOG_DEBUG("Initializing index buffer...");
    Memory = std::move(memory);
}

void VulkanIndexBuffer::UploadData(VulkanCommandBuffer& commandBuffer, uint32_t* indexData, uint32_t indexCount)
{
    LOG_DEBUG("Preparing data to be uploaded in index buffer...");

    const auto bufferSize = indexCount * sizeof(uint32_t);

    StagingBuffer = std::make_unique<VulkanBuffer>(Memory,
                                                   VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
                                                   VMA_MEMORY_USAGE_CPU_ONLY,
                                                   bufferSize);

    void* data;
    StagingBuffer->MapBuffer(&data);
    memcpy(data, indexData, bufferSize);
    StagingBuffer->UnmapBuffer();

    InternalIndexBuffer = std::make_unique<VulkanBuffer>(Memory,
                                                         VK_BUFFER_USAGE_TRANSFER_DST_BIT |
                                                         VK_BUFFER_USAGE_INDEX_BUFFER_BIT,
                                                         VMA_MEMORY_USAGE_GPU_ONLY,
                                                         bufferSize);

    commandBuffer.CopyBuffer(*StagingBuffer, *InternalIndexBuffer, bufferSize);
}

void VulkanIndexBuffer::CleanUpAfterUploading()
{
    LOG_DEBUG("Cleaning index buffer data after uploading...");
    StagingBuffer = nullptr;
}

VkBuffer VulkanIndexBuffer::GetRaw() const
{
    return InternalIndexBuffer->GetRaw();
}
