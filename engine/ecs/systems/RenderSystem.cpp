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
    Instance = std::make_unique<VulkanInstance>(true, // TODO: Change this
                                                "Name", // TODO: Change this
                                                "1.0.0", // TODO: Change this
                                                vulkanInstanceRequiredExtensions);
}

void RenderSystem::OnUpdate(float deltaTime)
{

}
