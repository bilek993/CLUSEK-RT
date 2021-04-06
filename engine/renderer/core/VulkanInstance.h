//
// Created by jbili on 03.04.2021.
//

#ifndef CLUSEK_RT_VULKANINSTANCE_H
#define CLUSEK_RT_VULKANINSTANCE_H

#include <vulkan/vulkan.h>
#include <string>
#include <vector>

class VulkanInstance
{
public:
    VulkanInstance(bool enableValidationLayers,
                   const std::string& applicationName,
                   const std::string& applicationVersion,
                   std::vector<const char*> requiredExtensions);
    ~VulkanInstance();
    VulkanInstance(const VulkanInstance& other) = delete;
    VulkanInstance(VulkanInstance&& other) noexcept = delete;
    VulkanInstance& operator=(const VulkanInstance& other) = delete;
    VulkanInstance& operator=(VulkanInstance&& other) noexcept = delete;

    [[nodiscard]] VkInstance GetRaw() const;

private:
    void InitializeValidation(bool enableValidationLayers, std::vector<const char*>& requiredExtensions);
    void InitializeInstance(const std::string& applicationName,
                            const std::string& applicationVersion,
                            const std::vector<const char*>& requiredExtensions);
    void InitializeDebugUtilsMessenger();

    [[nodiscard]] static bool CheckValidationLayersSupport();

    [[nodiscard]] static VkResult CreateDebugUtilsMessengerExtension(VkInstance instance,
                                                                     const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
                                                                     const VkAllocationCallbacks* pAllocator,
                                                                     VkDebugUtilsMessengerEXT* pDebugMessenger);
    static void DestroyDebugUtilsMessengerExtension(VkInstance instance,
                                                    VkDebugUtilsMessengerEXT debugMessenger,
                                                    const VkAllocationCallbacks* pAllocator);

    [[nodiscard]] static VkDebugUtilsMessengerCreateInfoEXT GenerateDebugUtilsMessengerCreateInfo();


    inline static const std::vector<const char*> ValidationLayers = { VK_EXT_DEBUG_UTILS_EXTENSION_NAME };

    bool UseValidationLayers;

    VkInstance InternalInstance;
    VkDebugUtilsMessengerEXT InternalDebugUtilsMessenger;
};


#endif //CLUSEK_RT_VULKANINSTANCE_H
