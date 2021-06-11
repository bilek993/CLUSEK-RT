//
// Created by jbili on 10.06.2021.
//

#ifndef CLUSEK_RT_VULKANSHADERMODULE_H
#define CLUSEK_RT_VULKANSHADERMODULE_H

#include <vulkan/vulkan.h>
#include <memory>

#include "VulkanLogicalDevice.h"

class VulkanShaderModule final
{
public:
    VulkanShaderModule(std::shared_ptr<VulkanLogicalDevice> logicalDevice,
                       const std::string& filepath,
                       VkShaderStageFlagBits stage,
                       const std::string& entryPointName);
    VulkanShaderModule(std::shared_ptr<VulkanLogicalDevice> logicalDevice,
                       const std::vector<char>& data,
                       VkShaderStageFlagBits stage,
                       const std::string& entryPointName);
    ~VulkanShaderModule();
    VulkanShaderModule(const VulkanShaderModule& other) = delete;
    VulkanShaderModule(VulkanShaderModule&& other) noexcept = delete;
    VulkanShaderModule& operator=(const VulkanShaderModule& other) = delete;
    VulkanShaderModule& operator=(VulkanShaderModule&& other) noexcept = delete;

    [[nodiscard]] VkPipelineShaderStageCreateInfo GenerateShaderStageCreateInfo() const;

    [[nodiscard]] VkShaderModule GetRaw() const;

private:
    static std::vector<char> ReadFile(const std::string& filepath);
    void CreateInternalInstance(const std::vector<char>& data);

    VkShaderModule InternalShaderModule = VK_NULL_HANDLE;
    VkShaderStageFlagBits Stage;
    std::string EntryPointName;

    std::shared_ptr<VulkanLogicalDevice> LogicalDevice;
};


#endif //CLUSEK_RT_VULKANSHADERMODULE_H
