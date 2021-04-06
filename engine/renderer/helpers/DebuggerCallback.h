//
// Created by jbili on 06.04.2021.
//

#ifndef CLUSEK_RT_DEBUGGERCALLBACK_H
#define CLUSEK_RT_DEBUGGERCALLBACK_H

#include <vulkan/vulkan.h>

namespace DebuggerCallback
{
    VKAPI_ATTR VkBool32 VKAPI_CALL Callback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                                            VkDebugUtilsMessageTypeFlagsEXT messageType,
                                            const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
                                            void* pUserData);
}

#endif //CLUSEK_RT_DEBUGGERCALLBACK_H
