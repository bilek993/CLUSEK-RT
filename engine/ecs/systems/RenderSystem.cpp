//
// Created by jbili on 30.03.2021.
//

#include "RenderSystem.h"

#include "../../common/debug/Logger.h"
#include "../../renderer/helpers/DeviceRequiredFeatures.h"
#include "../../renderer/helpers/DebugExtender.h"
#include "../../renderer/core/VulkanVertexBuffer.h"
#include "../../renderer/core/VulkanIndexBuffer.h"
#include "../../renderer/core/VulkanCommandBuffer.h"
#include "../../renderer/core/VulkanCommandPool.h"
#include "../../renderer/vertex/FatVertex.h"

std::string RenderSystem::GetName()
{
    return "Render System";
}

void RenderSystem::OnStart()
{
    LOG_DEBUG("Preparing to create Vulkan Instance...");
    auto vulkanInstanceRequiredExtensions = MainWindow->GetRequiredExtensions();
    DebugExtender::AddDebugExtensions(vulkanInstanceRequiredExtensions);
    Instance = std::make_shared<VulkanInstance>(ConfigurationData->EnableVulkanValidationLayers,
                                                ConfigurationData->ApplicationName,
                                                ConfigurationData->ApplicationVersion,
                                                VulkanApiVersion,
                                                vulkanInstanceRequiredExtensions);

    LOG_DEBUG("Preparing to create Vulkan Surface...");
    Surface = std::make_shared<VulkanSurface>(Instance, MainWindow);

    LOG_DEBUG("Preparing to create Vulkan Physical Device...");
    VkPhysicalDeviceFeatures physicalDeviceRequiredFeatures = DeviceRequiredFeatures::FromConfig(ConfigurationData);
    PhysicalDevice = std::make_shared<VulkanPhysicalDevice>(Instance,
                                                            ConfigurationData->VulkanRequireDiscreteDevice,
                                                            physicalDeviceRequiredFeatures);

    LOG_DEBUG("Searching for proper queues...");
    const std::vector<float> graphicPriorities = { 1.0F, 1.0F };
    const std::vector<float> computePriorities = {};
    const std::vector<float> transferPriorities = { 1.0F };
    Queues = std::make_shared<VulkanQueues>(PhysicalDevice,
                                            Surface,
                                            2,
                                            graphicPriorities,
                                            0,
                                            computePriorities,
                                            1,
                                            transferPriorities);

    LOG_DEBUG("Preparing to create Vulkan Logical Device with Vulkan Queues...");
    LogicalDevice = std::make_shared<VulkanLogicalDevice>(ConfigurationData->EnableVulkanValidationLayers,
                                                          PhysicalDevice,
                                                          Queues,
                                                          physicalDeviceRequiredFeatures,
                                                          LogicalDeviceRequiredExtensions);

    LOG_DEBUG("Acquiring and assigning queues...");
    const auto graphicQueues = Queues->GetGraphicsQueues();
    const auto computeQueues = Queues->GetComputeQueues();
    const auto transferQueues = Queues->GetTransferQueues();

    PresentationQueue = graphicQueues->at(0);
    RayTracingMainQueue = graphicQueues->at(1);

    TransferMainQueue = graphicQueues->at(0);

    if (!PresentationQueue.IsSupportingPresentation())
        throw std::runtime_error("Presentation queues is not capable for supporting presentation!");

    LOG_DEBUG("Preparing to create Vulkan Memory Allocator...");
    MemoryAllocator = std::make_shared<VulkanMemory>(Instance,
                                                     PhysicalDevice,
                                                     LogicalDevice,
                                                     VulkanApiVersion,
                                                     ConfigurationData->CheckVulkanBufferMemoryBeforeMapping);

    LOG_DEBUG("Preparing to create Vulkan Swap Chain...");
    const std::vector<VkPresentModeKHR> requestedPresentationModes = { VK_PRESENT_MODE_FIFO_KHR };
    const VkSurfaceFormatKHR requestedSwapChainFormat{ VK_FORMAT_B8G8R8A8_SRGB, VK_COLOR_SPACE_SRGB_NONLINEAR_KHR };
    SwapChain = std::make_shared<VulkanSwapChain>(LogicalDevice,
                                                  PhysicalDevice,
                                                  Surface,
                                                  MainWindow,
                                                  requestedSwapChainFormat,
                                                  requestedPresentationModes);

    // -----------------------------------------------------------------------------------------------------------------
    // -----------------------------------------------------------------------------------------------------------------
    // -----------------------------------------------------------------------------------------------------------------
    //                                 BELOW IS CODE FOR TESTING PURPOSES ONLY
    // -----------------------------------------------------------------------------------------------------------------
    // -----------------------------------------------------------------------------------------------------------------
    // -----------------------------------------------------------------------------------------------------------------

    // Preparing code

    std::shared_ptr<VulkanCommandPool> vulkanCommandPoolForTests = std::make_shared<VulkanCommandPool>(LogicalDevice,
                                                                                                       TransferMainQueue,
                                                                                                       true,
                                                                                                       false);
    std::shared_ptr<VulkanCommandBuffer> vulkanCommandBufferForTests =
            std::make_shared<VulkanCommandBuffer>(LogicalDevice,
                                                  vulkanCommandPoolForTests,
                                                  VK_COMMAND_BUFFER_LEVEL_PRIMARY);

    vulkanCommandBufferForTests->BeginRecording(true, false, false);

    // Vertex Buffer testing code

    std::shared_ptr<std::vector<FatVertex>> exampleVertices = std::make_shared<std::vector<FatVertex>>();
    exampleVertices->emplace_back(FatVertex{{ 0, 1, 2 }});
    exampleVertices->emplace_back(FatVertex{{ 2, 1, 0 }});

    VulkanVertexBuffer<FatVertex> exampleVertexBuffer{ MemoryAllocator };
    exampleVertexBuffer.UploadData(*vulkanCommandBufferForTests, exampleVertices->data(), exampleVertices->size());

    // Index Buffer testing code

    std::vector<uint32_t> indices{ 1, 2, 3 };

    VulkanIndexBuffer exampleIndexBuffer{ MemoryAllocator };
    exampleIndexBuffer.UploadData(*vulkanCommandBufferForTests, indices.data(), indices.size());

    // Cleaning up

    vulkanCommandBufferForTests->EndRecording();

    TransferMainQueue.Submit({ vulkanCommandBufferForTests });
    TransferMainQueue.WaitIdle();

    exampleVertexBuffer.CleanUpAfterUploading();
    exampleIndexBuffer.CleanUpAfterUploading();
}

void RenderSystem::OnUpdate(float deltaTime)
{

}

