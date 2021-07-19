//
// Created by jbili on 19.07.2021.
//

#ifndef CLUSEK_RT_VULKANPUSHCONSTANTRANGES_H
#define CLUSEK_RT_VULKANPUSHCONSTANTRANGES_H

#include <vector>
#include <vulkan/vulkan.h>

#include "../../math/PaddingCalculator.h"

class VulkanPushConstantRanges final
{
public:
    template<class T>
    void AddPushConstantDefinition(VkShaderStageFlags stageFlags);

    [[nodiscard]] uint32_t GetCount() const;
    [[nodiscard]] const VkPushConstantRange* GetRawPointer() const;

private:
    std::vector<VkPushConstantRange> InternalRanges{};
    uint32_t Offset = 0;
};

template<class T>
void VulkanPushConstantRanges::AddPushConstantDefinition(VkShaderStageFlags stageFlags)
{
    const auto pushConstantSize = PaddingCalculator::Calculate<T>(sizeof(T), 4);

    VkPushConstantRange pushConstantRange{
            stageFlags,
            Offset,
            pushConstantSize,
    };

    InternalRanges.emplace_back(pushConstantRange);
    Offset += pushConstantSize;
}

#endif //CLUSEK_RT_VULKANPUSHCONSTANTRANGES_H
