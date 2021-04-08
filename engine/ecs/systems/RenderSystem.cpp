//
// Created by jbili on 30.03.2021.
//

#include "RenderSystem.h"

#include "../../common/debug/Logger.h"

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
    PhysicalDevice = std::make_shared<VulkanPhysicalDevice>(Instance);
}

void RenderSystem::OnUpdate(float deltaTime)
{

}
