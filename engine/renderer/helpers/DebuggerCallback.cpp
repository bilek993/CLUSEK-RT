//
// Created by jbili on 06.04.2021.
//

#include "DebuggerCallback.h"

#include "../../common/debug/Logger.h"

VkBool32 DebuggerCallback::Callback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                                    VkDebugUtilsMessageTypeFlagsEXT messageType,
                                    const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
                                    void* pUserData)
{
    LOG_DEBUG("aaaaaaaaaaaaaaaaaa"); // TODO: Change this
    return VK_FALSE;
}

