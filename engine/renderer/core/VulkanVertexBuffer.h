//
// Created by jbili on 02.06.2021.
//

#ifndef CLUSEK_RT_VULKANVERTEXBUFFER_H
#define CLUSEK_RT_VULKANVERTEXBUFFER_H

#include <memory>
#include <vulkan/vulkan.h>

#include "../allocator/VulkanMemory.h"
#include "../core/VulkanBuffer.h"
#include "../core/VulkanCommandBuffer.h"
#include "../../common/debug/Logger.h"

// ______  _____  _____  _       ___  ______   ___   _____  _____  _____  _   _
// |  _  \|  ___|/  __ \| |     / _ \ | ___ \ / _ \ |_   _||_   _||  _  || \ | |
// | | | || |__  | /  \/| |    / /_\ \| |_/ // /_\ \  | |    | |  | | | ||  \| |
// | | | ||  __| | |    | |    |  _  ||    / |  _  |  | |    | |  | | | || . ` |
// | |/ / | |___ | \__/\| |____| | | || |\ \ | | | |  | |   _| |_ \ \_/ /| |\  |
// |___/  \____/  \____/\_____/\_| |_/\_| \_|\_| |_/  \_/   \___/  \___/ \_| \_/
//

template<class T>
class VulkanVertexBuffer final
{
public:
    VulkanVertexBuffer(std::shared_ptr<VulkanMemory> memory);
    VulkanVertexBuffer(const VulkanVertexBuffer& other) = delete;
    VulkanVertexBuffer(VulkanVertexBuffer&& other) noexcept = delete;
    VulkanVertexBuffer& operator=(const VulkanVertexBuffer& other) = delete;
    VulkanVertexBuffer& operator=(VulkanVertexBuffer&& other) noexcept = delete;

    void UploadData(VulkanCommandBuffer& commandBuffer, T* vertexData, uint32_t vertexCount);
    void CleanUpAfterUploading();

    [[nodiscard]] VkBuffer GetRaw() const;
    [[nodiscard]] std::shared_ptr<VulkanBuffer> Get() const;

private:
    std::shared_ptr<VulkanMemory> Memory;

    std::unique_ptr<VulkanBuffer> StagingBuffer;
    std::shared_ptr<VulkanBuffer> InternalVertexBuffer;
    uint32_t Stride;
};

//  _____ ___  _________  _      _____ ___  ___ _____  _   _  _____   ___   _____  _____  _____  _   _
// |_   _||  \/  || ___ \| |    |  ___||  \/  ||  ___|| \ | ||_   _| / _ \ |_   _||_   _||  _  || \ | |
//   | |  | .  . || |_/ /| |    | |__  | .  . || |__  |  \| |  | |  / /_\ \  | |    | |  | | | ||  \| |
//   | |  | |\/| ||  __/ | |    |  __| | |\/| ||  __| | . ` |  | |  |  _  |  | |    | |  | | | || . ` |
//  _| |_ | |  | || |    | |____| |___ | |  | || |___ | |\  |  | |  | | | |  | |   _| |_ \ \_/ /| |\  |
//  \___/ \_|  |_/\_|    \_____/\____/ \_|  |_/\____/ \_| \_/  \_/  \_| |_/  \_/   \___/  \___/ \_| \_/
//

template<class T>
VulkanVertexBuffer<T>::VulkanVertexBuffer(std::shared_ptr<VulkanMemory> memory)
{
    LOG_DEBUG("Initializing vertex buffer...");
    Memory = std::move(memory);
    Stride = sizeof(T);
}

template<class T>
void VulkanVertexBuffer<T>::UploadData(VulkanCommandBuffer& commandBuffer, T* vertexData, const uint32_t vertexCount)
{
    LOG_DEBUG("Preparing data to be uploaded in vertex buffer...");

    const auto bufferSize = vertexCount * Stride;

    StagingBuffer = std::make_unique<VulkanBuffer>(Memory,
                                                   VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
                                                   VMA_MEMORY_USAGE_CPU_ONLY,
                                                   bufferSize);

    void* data;
    StagingBuffer->MapBuffer(&data);
    memcpy(data, vertexData, bufferSize);
    StagingBuffer->UnmapBuffer();

    InternalVertexBuffer = std::make_shared<VulkanBuffer>(Memory,
                                                          VK_BUFFER_USAGE_TRANSFER_DST_BIT |
                                                          VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
                                                          VMA_MEMORY_USAGE_GPU_ONLY,
                                                          bufferSize);

    commandBuffer.CopyBuffer(*StagingBuffer, *InternalVertexBuffer, bufferSize);
}

template<class T>
void VulkanVertexBuffer<T>::CleanUpAfterUploading()
{
    LOG_DEBUG("Cleaning vertex buffer data after uploading...");
    StagingBuffer = nullptr;
}

template<class T>
VkBuffer VulkanVertexBuffer<T>::GetRaw() const
{
    return InternalVertexBuffer->GetRaw();
}

template<class T>
std::shared_ptr<VulkanBuffer> VulkanVertexBuffer<T>::Get() const
{
    return InternalVertexBuffer;
}

#endif //CLUSEK_RT_VULKANVERTEXBUFFER_H
