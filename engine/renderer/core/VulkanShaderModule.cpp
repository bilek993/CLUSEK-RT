//
// Created by jbili on 10.06.2021.
//

#include "VulkanShaderModule.h"

#include <fmt/os.h>
#include <fmt/compile.h>
#include <fstream>
#include <utility>

VulkanShaderModule::VulkanShaderModule(std::shared_ptr<VulkanLogicalDevice> logicalDevice, const std::string& filepath)
{
    LogicalDevice = std::move(logicalDevice);

    const auto data = ReadFile(filepath);
    CreateInternalInstance(data);
}

VulkanShaderModule::VulkanShaderModule(std::shared_ptr<VulkanLogicalDevice> logicalDevice,
                                       const std::vector<char>& data)
{
    LogicalDevice = std::move(logicalDevice);

    CreateInternalInstance(data);
}

VulkanShaderModule::~VulkanShaderModule()
{
    if (InternalShaderModule != VK_NULL_HANDLE)
        vkDestroyShaderModule(LogicalDevice->GetRaw(), InternalShaderModule, nullptr);
}

VkShaderModule VulkanShaderModule::GetRaw() const
{
    return InternalShaderModule;
}

std::vector<char> VulkanShaderModule::ReadFile(const std::string& filepath)
{
    std::ifstream shaderFile(filepath, std::ios::ate | std::ios::binary);
    if (!shaderFile.is_open())
    {
        const auto message = fmt::format(FMT_COMPILE("Failed to open '{}'!"), filepath);
        throw std::runtime_error(message);
    }

    auto compiledShaderSize = static_cast<size_t>(shaderFile.tellg());
    std::vector<char> compiledShaderCode(compiledShaderSize);

    shaderFile.seekg(0);
    shaderFile.read(compiledShaderCode.data(), static_cast<std::streamsize>(compiledShaderSize));

    return compiledShaderCode;
}

void VulkanShaderModule::CreateInternalInstance(const std::vector<char>& data)
{
    VkShaderModuleCreateInfo shaderModuleCreateInfo{};
    shaderModuleCreateInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    shaderModuleCreateInfo.codeSize = data.size();
    shaderModuleCreateInfo.pCode = reinterpret_cast<const uint32_t*>(data.data());

    const auto result = vkCreateShaderModule(LogicalDevice->GetRaw(),
                                             &shaderModuleCreateInfo,
                                             nullptr,
                                             &InternalShaderModule);
    if (result != VK_SUCCESS)
        throw std::runtime_error("Shader module cannot be created!");
}
