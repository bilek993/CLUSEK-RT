//
// Created by jbili on 16.04.2021.
//

#ifndef CLUSEK_RT_VULKANQUEUE_H
#define CLUSEK_RT_VULKANQUEUE_H

#include <vulkan/vulkan.h>

class VulkanQueue final
{
public:
    VulkanQueue();
    VulkanQueue(uint32_t familyIndex, bool supportPresentation);

    [[nodiscard]] uint32_t GetFamilyIndex() const;
    [[nodiscard]] bool IsSupportingPresentation() const;

    [[nodiscard]] VkQueue GetRaw() const;
    VkQueue* GetPointerToRaw();
private:
    uint32_t FamilyIndex = 0;
    bool SupportPresentation = false;

    VkQueue InternalQueue = VK_NULL_HANDLE;
};


#endif //CLUSEK_RT_VULKANQUEUE_H
