//
// Created by jbili on 28.05.2021.
//

#include "VulkanSemaphore.h"

VulkanSemaphore::VulkanSemaphore(std::shared_ptr<VulkanLogicalDevice> logicalDevice)
{
    LogicalDevice = std::move(logicalDevice);

    VkSemaphoreCreateInfo semaphoreCreateInfo{};
    semaphoreCreateInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

    const auto result = vkCreateSemaphore(LogicalDevice->GetRaw(), &semaphoreCreateInfo, nullptr, &InternalSemaphore);
    if (result != VK_SUCCESS)
        throw std::runtime_error("Semaphore creation failed!");
}

VulkanSemaphore::~VulkanSemaphore()
{
    if (InternalSemaphore != VK_NULL_HANDLE)
        vkDestroySemaphore(LogicalDevice->GetRaw(), InternalSemaphore, nullptr);
}

VkSemaphore VulkanSemaphore::GetRaw() const
{
    return InternalSemaphore;
}
