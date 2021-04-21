//
// Created by jbili on 03.04.2021.
//

#include "VulkanInstance.h"

#include "../helpers/VulkanVersion.h"
#include "../helpers/DebuggerCallback.h"
#include "../helpers/DebugExtender.h"

VulkanInstance::VulkanInstance(const bool enableValidationLayers,
                               const std::string& applicationName,
                               const std::string& applicationVersion,
                               std::vector<const char*> requiredExtensions)
{
    InitializeValidation(enableValidationLayers);
    InitializeInstance(applicationName, applicationVersion, requiredExtensions);
    InitializeDebugUtilsMessenger();
}

VulkanInstance::~VulkanInstance()
{
    if (UseValidationLayers)
        DestroyDebugUtilsMessengerExtension(InternalInstance, InternalDebugUtilsMessenger, nullptr);

    vkDestroyInstance(InternalInstance, nullptr);
}

VkInstance VulkanInstance::GetRaw() const
{
    return InternalInstance;
}

void VulkanInstance::InitializeValidation(bool enableValidationLayers)
{
    UseValidationLayers = enableValidationLayers;
    ValidationLayers = DebugExtender::GetValidationLayers();

    if (enableValidationLayers && CheckValidationLayersSupport())
    {
        LOG_DEBUG("Validation layers are not supported!");
        UseValidationLayers = false;
    }
}

void VulkanInstance::InitializeInstance(const std::string& applicationName,
                                        const std::string& applicationVersion,
                                        const std::vector<const char*>& requiredExtensions)
{
    VkApplicationInfo applicationInfo{};
    applicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    applicationInfo.pApplicationName = applicationName.c_str();
    applicationInfo.applicationVersion = VulkanVersion::GenerateVersion(applicationVersion);
    applicationInfo.pEngineName = "CLUSEK-RT Engine";
    applicationInfo.engineVersion = VulkanVersion::GenerateVersion(ENGINE_VERSION);
    applicationInfo.apiVersion = VK_API_VERSION_1_2;

    VkInstanceCreateInfo instanceCreateInfo{};
    instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    instanceCreateInfo.pApplicationInfo = &applicationInfo;
    instanceCreateInfo.ppEnabledExtensionNames = requiredExtensions.data();
    instanceCreateInfo.enabledExtensionCount = static_cast<uint32_t>(requiredExtensions.size());

    if (UseValidationLayers)
    {
        auto debugUtilsMessengerCreateInfo = GenerateDebugUtilsMessengerCreateInfo();
        instanceCreateInfo.pNext = static_cast<VkDebugUtilsMessengerCreateInfoEXT*>(&debugUtilsMessengerCreateInfo);

        instanceCreateInfo.enabledLayerCount = static_cast<uint32_t>(ValidationLayers.size());
        instanceCreateInfo.ppEnabledLayerNames = ValidationLayers.data();
    }
    else
    {
        instanceCreateInfo.enabledLayerCount = 0;
    }

    const auto result = vkCreateInstance(&instanceCreateInfo, nullptr, &InternalInstance);
    if (result != VK_SUCCESS)
        throw std::runtime_error("Critical error when creating Vulkan Instance!");
}

void VulkanInstance::InitializeDebugUtilsMessenger()
{
    if (!UseValidationLayers)
        return;

    const auto debugUtilsMessengerCreateInfo = GenerateDebugUtilsMessengerCreateInfo();
    const auto result = CreateDebugUtilsMessengerExtension(InternalInstance,
                                                           &debugUtilsMessengerCreateInfo,
                                                           nullptr,
                                                           &InternalDebugUtilsMessenger);
    if (result != VK_SUCCESS)
        throw std::runtime_error("Critical error when debug messenger!");
}

bool VulkanInstance::CheckValidationLayersSupport() const
{
    uint32_t layerCount;
    auto result = vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
    if (result != VK_SUCCESS)
        throw std::runtime_error("Cannot check validation layers support!");

    std::vector<VkLayerProperties> availableLayers(layerCount);
    result = vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());
    if (result != VK_SUCCESS)
        throw std::runtime_error("Cannot check validation layers support!");

    for (const char* layerName : ValidationLayers)
    {
        bool layerFound = false;

        for (const auto& layerProperties : availableLayers)
        {
            if (layerName == layerProperties.layerName)
            {
                layerFound = true;
                break;
            }
        }

        if (!layerFound)
            return false;
    }

    return true;
}

VkResult VulkanInstance::CreateDebugUtilsMessengerExtension(VkInstance instance,
                                                            const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
                                                            const VkAllocationCallbacks* pAllocator,
                                                            VkDebugUtilsMessengerEXT* pDebugMessenger)
{
    auto func = reinterpret_cast<PFN_vkCreateDebugUtilsMessengerEXT>(
            vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT"));

    if (func != nullptr)
        return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
    else
        return VK_ERROR_EXTENSION_NOT_PRESENT;
}

void VulkanInstance::DestroyDebugUtilsMessengerExtension(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger,
                                                         const VkAllocationCallbacks* pAllocator)
{
    auto func = reinterpret_cast<PFN_vkDestroyDebugUtilsMessengerEXT>(
            vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT"));

    if (func != nullptr)
        func(instance, debugMessenger, pAllocator);
}

VkDebugUtilsMessengerCreateInfoEXT VulkanInstance::GenerateDebugUtilsMessengerCreateInfo()
{
    VkDebugUtilsMessengerCreateInfoEXT debugUtilsMessengerCreateInfo{};
    debugUtilsMessengerCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    debugUtilsMessengerCreateInfo.messageSeverity =
            VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
    debugUtilsMessengerCreateInfo.messageType =
            VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
    debugUtilsMessengerCreateInfo.pfnUserCallback = DebuggerCallback::Callback;
    debugUtilsMessengerCreateInfo.pUserData = nullptr;

    return debugUtilsMessengerCreateInfo;
}