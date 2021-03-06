//
// Created by jbili on 30.03.2021.
//

#ifndef CLUSEK_RT_RENDERSYSTEM_H
#define CLUSEK_RT_RENDERSYSTEM_H

#include <memory>
#include <vector>
#include <vulkan/vulkan.h>

#include "BaseSystem.h"
#include "../../renderer/allocator/VulkanMemoryAllocatorImplementation.h"
#include "../../renderer/allocator/VulkanMemory.h"
#include "../../renderer/core/VulkanInstance.h"
#include "../../renderer/core/VulkanPhysicalDevice.h"
#include "../../renderer/core/VulkanQueues.h"
#include "../../renderer/core/VulkanLogicalDevice.h"
#include "../../renderer/core/VulkanSurface.h"
#include "../../renderer/core/VulkanSwapChain.h"
#include "../../renderer/core/VulkanFrameBuffer.h"
#include "../../renderer/core/VulkanCommandBuffer.h"
#include "../../renderer/core/VulkanCommandPool.h"
#include "../../renderer/core/VulkanRasterizationPipeline.h"
#include "../../renderer/core/VulkanVertexBuffer.h"
#include "../../renderer/core/VulkanIndexBuffer.h"
#include "../../renderer/core/VulkanRenderPass.h"
#include "../../renderer/core/VulkanPipelineLayout.h"
#include "../../renderer/core/VulkanShaderModule.h"
#include "../../renderer/vertex/FatVertex.h"

class RenderSystem final : public BaseSystem
{
public:
    std::string GetName() override;

protected:
    void OnStart() override;
    void OnUpdate(float deltaTime) override;
    void OnFinish() override;

private:
    std::shared_ptr<VulkanInstance> Instance = nullptr;
    std::shared_ptr<VulkanSurface> Surface = nullptr;
    std::shared_ptr<VulkanPhysicalDevice> PhysicalDevice = nullptr;
    std::shared_ptr<VulkanQueues> Queues = nullptr;
    std::shared_ptr<VulkanLogicalDevice> LogicalDevice = nullptr;
    std::shared_ptr<VulkanSwapChain> SwapChain = nullptr;
    std::shared_ptr<VulkanMemory> MemoryAllocator = nullptr;
    std::shared_ptr<VulkanSemaphore> PresentationCompleteSemaphore;
    std::shared_ptr<VulkanSemaphore> RenderCompleteSemaphore;
    std::vector<std::shared_ptr<VulkanFence>> InFlightFences;
    std::vector<std::shared_ptr<VulkanFrameBuffer>> ScreenFrameBuffers{}; // TODO: Remove this! For testing purposes only

    VulkanQueue PresentationQueue;
    VulkanQueue GraphicsMainQueue;
    VulkanQueue TransferMainQueue;

    uint32_t CurrentFrameIndex;

    std::shared_ptr<VulkanCommandPool> TriangleCommandPool = nullptr; // TODO: Remove this! For testing purposes only
    std::vector<std::shared_ptr<VulkanCommandBuffer>> TriangleCommandBuffers{}; // TODO: Remove this! For testing purposes only
    std::shared_ptr<VulkanRasterizationPipeline> TrianglePipeline = nullptr; // TODO: Remove this! For testing purposes only
    std::shared_ptr<VulkanRenderPass> TriangleRenderPass = nullptr; // TODO: Remove this! For testing purposes only
    std::shared_ptr<VulkanIndexBuffer> TriangleIndexBuffer = nullptr; // TODO: Remove this! For testing purposes only
    std::shared_ptr<VulkanVertexBuffer<FatVertex>> TriangleVertexBuffer = nullptr; // TODO: Remove this! For testing purposes only
    std::shared_ptr<VulkanPipelineLayout> TrianglePipelineLayout = nullptr; // TODO: Remove this! For testing purposes only
    std::shared_ptr<VulkanShaderModule> TriangleVertexShader = nullptr; // TODO: Remove this! For testing purposes only
    std::shared_ptr<VulkanShaderModule> TrianglePixelShader = nullptr; // TODO: Remove this! For testing purposes only

    std::vector<const char*> LogicalDeviceRequiredExtensions = {
            VK_KHR_SWAPCHAIN_EXTENSION_NAME
    };
    uint32_t VulkanApiVersion = VK_API_VERSION_1_2;

    void Recreate();
};


#endif //CLUSEK_RT_RENDERSYSTEM_H
