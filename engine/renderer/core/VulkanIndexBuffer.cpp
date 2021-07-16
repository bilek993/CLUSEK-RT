//
// Created by jbili on 02.06.2021.
//

#include "VulkanIndexBuffer.h"

VulkanIndexBuffer::VulkanIndexBuffer(std::shared_ptr<VulkanMemory> memory)
{
    LOG_DEBUG("Initializing index buffer...");
    Memory = std::move(memory);
}

void VulkanIndexBuffer::CleanUpAfterUploading()
{
    LOG_DEBUG("Cleaning index buffer data after uploading...");
    StagingBuffer = nullptr;
}

VkIndexType VulkanIndexBuffer::GetIndexType() const
{
    return IndexUnitType;
}

VkBuffer VulkanIndexBuffer::GetRaw() const
{
    return InternalIndexBuffer->GetRaw();
}

std::shared_ptr<VulkanBuffer> VulkanIndexBuffer::Get() const
{
    return InternalIndexBuffer;
}
