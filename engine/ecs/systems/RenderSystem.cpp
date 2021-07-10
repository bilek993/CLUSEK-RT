//
// Created by jbili on 30.03.2021.
//

#include "RenderSystem.h"

#include "../../common/debug/Logger.h"
#include "../../generated/VertexInputAttributeDescriptions.h"
#include "../../renderer/helpers/DeviceRequiredFeatures.h"
#include "../../renderer/helpers/DebugExtender.h"
#include "../../renderer/helpers/BufferMemoryBarrierBuilder.h"
#include "../../renderer/helpers/VertexBindingDescriptorGenerator.h"
#include "../../renderer/helpers/RasterizationPipelineBuilder.h"
#include "../../renderer/core/VulkanVertexBuffer.h"
#include "../../renderer/core/VulkanIndexBuffer.h"
#include "../../renderer/core/VulkanShaderModule.h"
#include "../../renderer/core/VulkanRenderPass.h"
#include "../../renderer/core/VulkanRasterizationPipeline.h"
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
    Surface = std::make_shared<VulkanSurface>(Instance, *MainWindow);

    LOG_DEBUG("Preparing to create Vulkan Physical Device...");
    VkPhysicalDeviceFeatures physicalDeviceRequiredFeatures = DeviceRequiredFeatures::FromConfig(*ConfigurationData);
    PhysicalDevice = std::make_shared<VulkanPhysicalDevice>(*Instance,
                                                            ConfigurationData->VulkanRequireDiscreteDevice,
                                                            physicalDeviceRequiredFeatures);

    LOG_DEBUG("Searching for proper queues...");
    const std::vector<float> graphicPriorities = { 1.0F, 1.0F };
    const std::vector<float> computePriorities = {};
    const std::vector<float> transferPriorities = { 1.0F };
    Queues = std::make_shared<VulkanQueues>(*PhysicalDevice,
                                            *Surface,
                                            2,
                                            graphicPriorities,
                                            0,
                                            computePriorities,
                                            1,
                                            transferPriorities);

    LOG_DEBUG("Preparing to create Vulkan Logical Device with Vulkan Queues...");
    LogicalDevice = std::make_shared<VulkanLogicalDevice>(ConfigurationData->EnableVulkanValidationLayers,
                                                          *PhysicalDevice,
                                                          *Queues,
                                                          physicalDeviceRequiredFeatures,
                                                          LogicalDeviceRequiredExtensions);

    LOG_DEBUG("Acquiring and assigning queues...");
    const auto graphicQueues = Queues->GetGraphicsQueues();
    const auto computeQueues = Queues->GetComputeQueues();
    const auto transferQueues = Queues->GetTransferQueues();

    PresentationQueue = graphicQueues->at(0);
    GraphicsMainQueue = graphicQueues->at(1);

    TransferMainQueue = graphicQueues->at(0);

    if (!PresentationQueue.IsSupportingPresentation())
        throw std::runtime_error("Presentation queues is not capable for supporting presentation!");

    LOG_DEBUG("Preparing to create Vulkan Memory Allocator...");
    MemoryAllocator = std::make_shared<VulkanMemory>(*Instance,
                                                     *PhysicalDevice,
                                                     *LogicalDevice,
                                                     VulkanApiVersion,
                                                     ConfigurationData->CheckVulkanBufferMemoryBeforeMapping);

    LOG_DEBUG("Preparing to create Vulkan Swap Chain...");
    const std::vector<VkPresentModeKHR> requestedPresentationModes = { VK_PRESENT_MODE_FIFO_KHR };
    const VkSurfaceFormatKHR requestedSwapChainFormat{ VK_FORMAT_B8G8R8A8_SRGB, VK_COLOR_SPACE_SRGB_NONLINEAR_KHR };
    SwapChain = std::make_shared<VulkanSwapChain>(LogicalDevice,
                                                  *PhysicalDevice,
                                                  *Surface,
                                                  *MainWindow,
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

    const auto vulkanCommandPoolForTests = std::make_shared<VulkanCommandPool>(LogicalDevice,
                                                                               TransferMainQueue,
                                                                               true,
                                                                               false);
    auto vulkanCommandBufferForTests = VulkanCommandBuffer(LogicalDevice,
                                                           vulkanCommandPoolForTests,
                                                           VK_COMMAND_BUFFER_LEVEL_PRIMARY);

    vulkanCommandBufferForTests.BeginRecording(true, false, false);

    // Shader modules testing code

    const auto exampleVertexShaderModule = VulkanShaderModule(LogicalDevice,
                                                              "./data/shaders/example_vs.spv",
                                                              VK_SHADER_STAGE_VERTEX_BIT,
                                                              "main");

    const auto exampleFragmentShaderModule = VulkanShaderModule(LogicalDevice,
                                                                "./data/shaders/example_fs.spv",
                                                                VK_SHADER_STAGE_FRAGMENT_BIT,
                                                                "main");

    // Vertex Buffer testing code

    auto exampleVertices = std::make_shared<std::vector<FatVertex>>();
    exampleVertices->emplace_back(FatVertex{{ 0, 1, 2 }});
    exampleVertices->emplace_back(FatVertex{{ 2, 1, 0 }});
    exampleVertices->emplace_back(FatVertex{{ 0, 2, 1 }});

    VulkanVertexBuffer<FatVertex> exampleVertexBuffer{ MemoryAllocator };
    exampleVertexBuffer.UploadData(vulkanCommandBufferForTests, exampleVertices->data(), exampleVertices->size());

    // Index Buffer testing code

    std::vector<uint32_t> indices{ 0, 1, 2 };

    VulkanIndexBuffer exampleIndexBuffer{ MemoryAllocator };
    exampleIndexBuffer.UploadData(vulkanCommandBufferForTests, indices.data(), indices.size(), VK_INDEX_TYPE_UINT16);

    // Transfer ownership from transfer queue to graphics queue

    const auto exampleVertexBufferBarrier = BufferMemoryBarrierBuilder()
            .SetBufferData(*exampleVertexBuffer.Get())
            .SetOwnershipTransferIfNeeded(TransferMainQueue, GraphicsMainQueue)
            .Build();

    const auto exampleIndexBufferBarrier = BufferMemoryBarrierBuilder()
            .SetBufferData(*exampleIndexBuffer.Get())
            .SetOwnershipTransferIfNeeded(TransferMainQueue, GraphicsMainQueue)
            .Build();

    vulkanCommandBufferForTests.AddBarrier(VK_PIPELINE_STAGE_TRANSFER_BIT,
                                           VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT,
                                           0,
                                           {},
                                           { exampleVertexBufferBarrier, exampleIndexBufferBarrier },
                                           {});

    vulkanCommandBufferForTests.EndRecording();

    TransferMainQueue.Submit({ &vulkanCommandBufferForTests });
    TransferMainQueue.WaitIdle();

    // Rasterization pipeline testing code

    VkAttachmentDescription colorAttachmentDescription{};
    colorAttachmentDescription.format = SwapChain->GetUsedFormat().format;
    colorAttachmentDescription.samples = VK_SAMPLE_COUNT_1_BIT;
    colorAttachmentDescription.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    colorAttachmentDescription.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    colorAttachmentDescription.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    colorAttachmentDescription.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    colorAttachmentDescription.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    colorAttachmentDescription.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

    VkSubpassDependency testSubpassDependency{};
    testSubpassDependency.srcSubpass = VK_SUBPASS_EXTERNAL;
    testSubpassDependency.dstSubpass = 0;
    testSubpassDependency.srcStageMask =
            VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
    testSubpassDependency.dstStageMask =
            VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
    testSubpassDependency.srcAccessMask = 0;
    testSubpassDependency.dstAccessMask =
            VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;

    const auto testRenderPass = VulkanRenderPass(LogicalDevice,
                                                 {
                                                         colorAttachmentDescription,
                                                 },
                                                 false,
                                                 {
                                                         testSubpassDependency,
                                                 },
                                                 {
                                                         {{ 0 }, false },
                                                 });

    const auto testPipelineLayout = VulkanPipelineLayout(LogicalDevice);

    const auto testPipeline = RasterizationPipelineBuilder()
            .SetLogicalDevice(LogicalDevice)
            .AddShaderStage(exampleVertexShaderModule)
            .AddShaderStage(exampleFragmentShaderModule)
            .AddVertexInput(VertexBindingDescriptorGenerator::Generate<FatVertex>(),
                            VertexInputAttributeDescriptions::GetDescriptionForFatVertex())
            .EnableDynamicViewport()
            .AddDynamicViewportAndScissor()
            .SetCullMode(VK_CULL_MODE_BACK_BIT)
            .AddBlendAttachmentWithDisabledBlending(VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT |
                                                    VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT)
            .SetPipelineLayout(testPipelineLayout)
            .SetRenderPass(testRenderPass)
            .SetSubpassIndex(0)
            .Build();

    // Framebuffer testing code

    for (auto i = 0; i < SwapChain->GetImageViewCount(); i++)
    {
        const std::vector<VulkanImageView*> frameBufferImageView{ SwapChain->GetImageView(i).get() };
        const auto temporaryFrameBuffer = std::make_shared<VulkanFrameBuffer>(LogicalDevice,
                                                                              testRenderPass,
                                                                              frameBufferImageView,
                                                                              SwapChain->GetUsedExtent().width,
                                                                              SwapChain->GetUsedExtent().height,
                                                                              1);
        ScreenFrameBuffers.emplace_back(temporaryFrameBuffer);
    }

    // Triangle command pool code

    TriangleCommandPool = std::make_shared<VulkanCommandPool>(LogicalDevice,
                                                              GraphicsMainQueue,
                                                              false,
                                                              true);

    // Triangle command buffer code

    for (auto i = 0; i < SwapChain->GetImageViewCount(); i++)
    {
        const auto temporaryCommandBuffer = std::make_shared<VulkanCommandBuffer>(LogicalDevice,
                                                                                  TriangleCommandPool,
                                                                                  VK_COMMAND_BUFFER_LEVEL_PRIMARY);

        temporaryCommandBuffer->BeginRecording(false, false, false);

        const auto clearValues = std::vector<VkClearValue>{{ 0.0f, 0.0f, 0.0f, 1.0f },
                                                           { 1.0f, 0 }};
        const auto renderPassBeginInfo = testRenderPass.GenerateRenderPassBeginInfo(*ScreenFrameBuffers[i],
                                                                                    {{ 0, 0 },
                                                                                     SwapChain->GetUsedExtent() },
                                                                                    &clearValues);
        temporaryCommandBuffer->BeginRenderPass(renderPassBeginInfo);

        temporaryCommandBuffer->BindPipeline(testPipeline, VK_PIPELINE_BIND_POINT_GRAPHICS);

        const std::vector<VulkanVertexBuffer<FatVertex>*> verticesForDrawing = { &exampleVertexBuffer };
        const std::vector<VkDeviceSize> offsets = { 0 };

        VkViewport testViewport{};
        testViewport.x = 0.0F;
        testViewport.y = static_cast<float>(SwapChain->GetUsedExtent().height);
        testViewport.width = static_cast<float>(SwapChain->GetUsedExtent().width);
        testViewport.height = -static_cast<float>(SwapChain->GetUsedExtent().height);
        testViewport.minDepth = 0.0F;
        testViewport.maxDepth = 1.0F;

        VkRect2D testScissor{};
        testScissor.offset = { 0, 0 };
        testScissor.extent = SwapChain->GetUsedExtent();

        temporaryCommandBuffer->BindIndexBuffer(exampleIndexBuffer);
        temporaryCommandBuffer->BindVertexBuffer<FatVertex>(verticesForDrawing, offsets);
        temporaryCommandBuffer->SetDynamicViewportsAndScissors({ testViewport }, { testScissor });
        temporaryCommandBuffer->Draw(indices.size());

        temporaryCommandBuffer->EndRenderPass();

        temporaryCommandBuffer->EndRecording();

        TriangleCommandBuffers.emplace_back(temporaryCommandBuffer);
    }

    // Cleaning up

    exampleVertexBuffer.CleanUpAfterUploading();
    exampleIndexBuffer.CleanUpAfterUploading();
}

void RenderSystem::OnUpdate(float deltaTime)
{

}

void RenderSystem::OnFinish()
{
    LogicalDevice->WaitIdle();
}

