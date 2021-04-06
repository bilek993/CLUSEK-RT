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
    Instance = std::make_unique<VulkanInstance>(true, "Name", "1.0.0"); // TODO: Change this
}

void RenderSystem::OnUpdate(float deltaTime)
{

}
