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

    LOG_DEBUG("Preparing to create synchronization for presentation mechanism...");

    PresentationCompleteSemaphore = std::make_shared<VulkanSemaphore>(LogicalDevice);
    RenderCompleteSemaphore = std::make_shared<VulkanSemaphore>(LogicalDevice);

    for (size_t i = 0; i < SwapChain->GetImageCount(); i++)
    {
        const auto temporaryFence = std::make_shared<VulkanFence>(LogicalDevice, true);
        InFlightFences.emplace_back(temporaryFence);
    }

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

    TriangleVertexShader = std::make_shared<VulkanShaderModule>(LogicalDevice,
                                                                "./data/shaders/example_vs.spv",
                                                                VK_SHADER_STAGE_VERTEX_BIT,
                                                                "main");

    TrianglePixelShader = std::make_shared<VulkanShaderModule>(LogicalDevice,
                                                               "./data/shaders/example_fs.spv",
                                                               VK_SHADER_STAGE_FRAGMENT_BIT,
                                                               "main");

    // Vertex Buffer testing code

    auto exampleVertices = std::vector<FatVertex>();
    exampleVertices.emplace_back(FatVertex{{ -0.5f, -0.5f, 0.0f }});
    exampleVertices.emplace_back(FatVertex{{ 0.5f, -0.5f, 0.0f }});
    exampleVertices.emplace_back(FatVertex{{ 0.0f, 0.5f, 0.0f }});

    TriangleVertexBuffer = std::make_shared<VulkanVertexBuffer<FatVertex>>(MemoryAllocator);
    TriangleVertexBuffer->UploadData(vulkanCommandBufferForTests, exampleVertices);

    // Index Buffer testing code

    std::vector<uint16_t> indices{ 0, 1, 2 };

    TriangleIndexBuffer = std::make_shared<VulkanIndexBuffer>(MemoryAllocator);
    TriangleIndexBuffer->UploadData(vulkanCommandBufferForTests, indices, VK_INDEX_TYPE_UINT16);

    // Transfer ownership from transfer queue to graphics queue

    const auto exampleVertexBufferBarrier = BufferMemoryBarrierBuilder()
            .SetBufferData(*TriangleVertexBuffer->Get())
            .SetOwnershipTransferIfNeeded(TransferMainQueue, GraphicsMainQueue)
            .Build();

    const auto exampleIndexBufferBarrier = BufferMemoryBarrierBuilder()
            .SetBufferData(*TriangleIndexBuffer->Get())
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

    TriangleRenderPass = std::make_shared<VulkanRenderPass>(LogicalDevice,
                                                            std::vector<VkAttachmentDescription>{
                                                                    colorAttachmentDescription,
                                                            },
                                                            false,
                                                            std::vector<VkSubpassDependency>{
                                                                    testSubpassDependency,
                                                            },
                                                            std::vector<VulkanSubpass>{
                                                                    {{ 0 }, false },
                                                            });

    TrianglePipelineLayout = std::make_shared<VulkanPipelineLayout>(LogicalDevice);

    TrianglePipeline = RasterizationPipelineBuilder()
            .SetLogicalDevice(LogicalDevice)
            .AddShaderStage(*TriangleVertexShader)
            .AddShaderStage(*TrianglePixelShader)
            .AddVertexInput(VertexBindingDescriptorGenerator::Generate<FatVertex>(),
                            VertexInputAttributeDescriptions::GetDescriptionForFatVertex())
            .EnableDynamicViewport()
            .AddDynamicViewportAndScissor()
            .SetCullMode(VK_CULL_MODE_BACK_BIT)
            .AddBlendAttachmentWithDisabledBlending(VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT |
                                                    VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT)
            .SetPipelineLayout(*TrianglePipelineLayout)
            .SetRenderPass(*TriangleRenderPass)
            .SetSubpassIndex(0)
            .Build();

    // Framebuffer testing code

    for (auto i = 0; i < SwapChain->GetImageViewCount(); i++)
    {
        const std::vector<VulkanImageView*> frameBufferImageView{ SwapChain->GetImageView(i).get() };
        const auto temporaryFrameBuffer = std::make_shared<VulkanFrameBuffer>(LogicalDevice,
                                                                              *TriangleRenderPass,
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
        const auto renderPassBeginInfo = TriangleRenderPass->GenerateRenderPassBeginInfo(*ScreenFrameBuffers[i],
                                                                                         {{ 0, 0 },
                                                                                          SwapChain->GetUsedExtent() },
                                                                                         &clearValues);
        temporaryCommandBuffer->BeginRenderPass(renderPassBeginInfo);

        temporaryCommandBuffer->BindPipeline(*TrianglePipeline, VK_PIPELINE_BIND_POINT_GRAPHICS);

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

        temporaryCommandBuffer->BindIndexBuffer(*TriangleIndexBuffer);
        temporaryCommandBuffer->BindVertexBuffer<FatVertex>({ TriangleVertexBuffer.get() }, { 0 });
        temporaryCommandBuffer->SetDynamicViewportsAndScissors({ testViewport }, { testScissor });
        temporaryCommandBuffer->Draw(indices.size());

        temporaryCommandBuffer->EndRenderPass();

        temporaryCommandBuffer->EndRecording();

        TriangleCommandBuffers.emplace_back(temporaryCommandBuffer);
    }

    // Cleaning up

    TriangleVertexBuffer->CleanUpAfterUploading();
    TriangleIndexBuffer->CleanUpAfterUploading();
}

void RenderSystem::OnUpdate(const float deltaTime)
{
    auto result = SwapChain->AcquireNextImageIndex(PresentationCompleteSemaphore.get(),
                                                   nullptr,
                                                   &CurrentFrameIndex);

    InFlightFences[CurrentFrameIndex]->Wait();
    InFlightFences[CurrentFrameIndex]->Reset();

    if (result == VK_ERROR_OUT_OF_DATE_KHR)
    {
        Recreate();
        return;
    }
    else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR)
    {
        throw std::runtime_error("Error when acquiring next image...");
    }

    VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
    GraphicsMainQueue.Submit({ TriangleCommandBuffers[CurrentFrameIndex].get() },
                             { PresentationCompleteSemaphore.get() },
                             { RenderCompleteSemaphore.get() },
                             InFlightFences[CurrentFrameIndex].get(),
                             waitStages);

    result = PresentationQueue.Present({ RenderCompleteSemaphore.get() },
                                       { SwapChain.get() },
                                       &CurrentFrameIndex);

    if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || MainWindow->HasBeenResized())
        Recreate();
    else if (result != VK_SUCCESS)
        throw std::runtime_error("Failed to present result!");
}

void RenderSystem::OnFinish()
{
    LogicalDevice->WaitIdle();
}

void RenderSystem::Recreate() // TODO: Implement this function
{
    LOG_DEBUG("Preparing to recreate the resources...");
}
