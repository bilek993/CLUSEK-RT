//
// Created by jbili on 07.04.2021.
//

#include "VulkanLogicalDevice.h"

VulkanLogicalDevice::VulkanLogicalDevice()
{
    // TODO: Implement this
}

VulkanLogicalDevice::~VulkanLogicalDevice()
{
    vkDestroyDevice(InternalLogicalDevice, nullptr);
}

VkDevice VulkanLogicalDevice::GetRaw() const
{
    return InternalLogicalDevice;
}
