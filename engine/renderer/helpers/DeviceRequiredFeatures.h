//
// Created by jbili on 14.04.2021.
//

#ifndef CLUSEK_RT_DEVICEREQUIREDFEATURES_H
#define CLUSEK_RT_DEVICEREQUIREDFEATURES_H

#include <vulkan/vulkan.h>
#include <memory>

#include "../../common/ConfigData.h"

namespace DeviceRequiredFeatures
{
    [[nodiscard]] VkPhysicalDeviceFeatures FromConfig(std::shared_ptr<ConfigData> configurationData);
};


#endif //CLUSEK_RT_DEVICEREQUIREDFEATURES_H
