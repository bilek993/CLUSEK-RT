//
// Created by jbili on 02.06.2021.
//

#ifndef CLUSEK_RT_VULKANINDEXBUFFER_H
#define CLUSEK_RT_VULKANINDEXBUFFER_H

#include <memory>
#include <vulkan/vulkan.h>

#include "../allocator/VulkanMemory.h"
#include "../core/VulkanBuffer.h"
#include "../core/VulkanCommandBuffer.h"

class VulkanIndexBuffer final
{
public:
    VulkanIndexBuffer(std::shared_ptr<VulkanMemory> memory);
    VulkanIndexBuffer(const VulkanIndexBuffer& other) = delete;
    VulkanIndexBuffer(VulkanIndexBuffer&& other) noexcept = delete;
    VulkanIndexBuffer& operator=(const VulkanIndexBuffer& other) = delete;
    VulkanIndexBuffer& operator=(VulkanIndexBuffer&& other) noexcept = delete;

    void UploadData(VulkanCommandBuffer& commandBuffer,
                    uint32_t* indexData,
                    uint32_t indexCount,
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

#endif //CLUSEK_RT_VULKANINDEXBUFFER_H
