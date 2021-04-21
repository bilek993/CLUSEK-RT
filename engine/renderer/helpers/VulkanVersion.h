//
// Created by jbili on 04.04.2021.
//

#ifndef CLUSEK_RT_VULKANVERSION_H
#define CLUSEK_RT_VULKANVERSION_H

#include <vulkan/vulkan.h>
#include <sstream>
#include <vector>

#include "../../common/debug/Logger.h"

namespace VulkanVersion
{
    uint32_t GenerateVersion(const std::string& version);
}

#endif //CLUSEK_RT_VULKANVERSION_H
