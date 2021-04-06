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
    VulkanInstance(bool debugMode,
                   const std::string& applicationName,
                   const std::string& applicationVersion,
                   const std::vector<const char*>& requiredExtensions);
    ~VulkanInstance();
    VulkanInstance(const VulkanInstance& other) = delete;
    VulkanInstance(VulkanInstance&& other) noexcept = delete;
    VulkanInstance& operator=(const VulkanInstance& other) = delete;
    VulkanInstance& operator=(VulkanInstance&& other) noexcept = delete;

    [[nodiscard]] VkInstance GetRaw() const;
private:
    VkInstance InternalInstance;
};


#endif //CLUSEK_RT_VULKANINSTANCE_H
