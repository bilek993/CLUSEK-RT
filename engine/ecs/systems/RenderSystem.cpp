//
// Created by jbili on 30.03.2021.
//

#include "RenderSystem.h"

#include "../../common/debug/Logger.h"
#include "../../renderer/helpers/DeviceRequiredFeatures.h"
#include "../../renderer/helpers/DebugExtender.h"

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
                                                vulkanInstanceRequiredExtensions);

    LOG_DEBUG("Preparing to create Vulkan Physical Device...");
    VkPhysicalDeviceFeatures physicalDeviceRequiredFeatures = DeviceRequiredFeatures::FromConfig(ConfigurationData);
    PhysicalDevice = std::make_shared<VulkanPhysicalDevice>(Instance,
                                                            ConfigurationData->VulkanRequireDiscreteDevice,
                                                            physicalDeviceRequiredFeatures);

    LOG_DEBUG("Searching for proper queues...");
    const std::vector<float> graphicPriorities = { 1.0F };
    const std::vector<float> computePriorities = {};
    const std::vector<float> transferPriorities = { 1.0F };
    Queues = std::make_shared<VulkanQueues>(PhysicalDevice,
                                            1,
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
}

void RenderSystem::OnUpdate(float deltaTime)
{

}

