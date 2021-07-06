//
// Created by jbili on 30.06.2021.
//

#ifndef CLUSEK_RT_VULKANSUBPASS_H
#define CLUSEK_RT_VULKANSUBPASS_H

#include <vector>

struct VulkanSubpass
{
    std::vector<int> UsedColorAttachmentsIds{};
    bool UseDepthStencilAttachment = false;
};

#endif //CLUSEK_RT_VULKANSUBPASS_H
