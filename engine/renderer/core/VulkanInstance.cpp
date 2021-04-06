//
// Created by jbili on 03.04.2021.
//

#include "VulkanInstance.h"

#include "../helpers/VulkanVersion.h"

VulkanInstance::VulkanInstance(const bool debugMode,
                               const std::string& applicationName,
                               const std::string& applicationVersion,
                               const std::vector<const char*>& requiredExtensions)
{
    VkApplicationInfo applicationInfo{};
    applicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    applicationInfo.pApplicationName = applicationName.c_str();
    applicationInfo.applicationVersion = VulkanVersion::GenerateVersion(applicationVersion);
    applicationInfo.pEngineName = "CLUSEK-RT";
    applicationInfo.engineVersion = VulkanVersion::GenerateVersion(ENGINE_VERSION);
    applicationInfo.apiVersion = VK_API_VERSION_1_2;

    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &applicationInfo;
    createInfo.ppEnabledExtensionNames = requiredExtensions.data();
    createInfo.enabledExtensionCount = static_cast<uint32_t>(requiredExtensions.size());

    const auto result = vkCreateInstance(&createInfo, nullptr, &InternalInstance);

    if (result != VK_SUCCESS)
        throw std::runtime_error("Critical error when creating Vulkan Instance!");
}

VulkanInstance::~VulkanInstance()
{
    vkDestroyInstance(InternalInstance, nullptr);
}

VkInstance VulkanInstance::GetRaw() const
{
    return InternalInstance;
}
