//
// Created by jbili on 30.03.2021.
//

#include "RenderSystem.h"

#include "../../common/debug/Logger.h"
#include "../../renderer/helpers/DeviceRequiredFeatures.h"

std::string RenderSystem::GetName()
{
    return "Render System";
}

void RenderSystem::OnStart()
{
    LOG_DEBUG("Preparing to create Vulkan Instance...");
    const auto vulkanInstanceRequiredExtensions = MainWindow->GetRequiredExtensions();
    Instance = std::make_shared<VulkanInstance>(ConfigurationData->EnableVulkanValidationLayers,
                                                ConfigurationData->ApplicationName,
                                                ConfigurationData->ApplicationVersion,
                                                vulkanInstanceRequiredExtensions);

    LOG_DEBUG("Preparing to create Vulkan Physical Device...");
    // TODO: Rename physicalDeviceRequiredFeatures and remove this comment
    VkPhysicalDeviceFeatures physicalDeviceRequiredFeatures = DeviceRequiredFeatures::FromConfig(ConfigurationData);
    PhysicalDevice = std::make_shared<VulkanPhysicalDevice>(Instance,
                                                            ConfigurationData->VulkanRequireDiscreteDevice,
                                                            physicalDeviceRequiredFeatures);

    LOG_DEBUG("Searching for proper queues...");
    Queues = std::make_shared<VulkanQueues>(PhysicalDevice, 1, 0, 1);

    LOG_DEBUG("Preparing to create Vulkan Logical Device with Vulkan Queues...");
    LogicalDevice = std::make_shared<VulkanLogicalDevice>(PhysicalDevice, Queues, physicalDeviceRequiredFeatures);
}

void RenderSystem::OnUpdate(float deltaTime)
{

}

