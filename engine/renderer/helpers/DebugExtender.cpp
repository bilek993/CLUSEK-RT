//
// Created by jbili on 20.04.2021.
//

#include "DebugExtender.h"

#include <vulkan/vulkan.h>

std::vector<const char*> DebugExtender::GetValidationLayers()
{
    return { "VK_LAYER_KHRONOS_validation" };
}

void DebugExtender::AddDebugExtensions(std::vector<const char*>& extensions)
{
    extensions.emplace_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME)
}
