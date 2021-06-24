//
// Created by jbili on 24.06.2021.
//

#ifndef CLUSEK_RT_VERTEXBINDINGDESCRIPTORGENERATOR_H
#define CLUSEK_RT_VERTEXBINDINGDESCRIPTORGENERATOR_H

#include <vulkan/vulkan.h>

namespace VertexBindingDescriptorGenerator
{
    // ______  _____  _____  _       ___  ______   ___   _____  _____  _____  _   _
    // |  _  \|  ___|/  __ \| |     / _ \ | ___ \ / _ \ |_   _||_   _||  _  || \ | |
    // | | | || |__  | /  \/| |    / /_\ \| |_/ // /_\ \  | |    | |  | | | ||  \| |
    // | | | ||  __| | |    | |    |  _  ||    / |  _  |  | |    | |  | | | || . ` |
    // | |/ / | |___ | \__/\| |____| | | || |\ \ | | | |  | |   _| |_ \ \_/ /| |\  |
    // |___/  \____/  \____/\_____/\_| |_/\_| \_|\_| |_/  \_/   \___/  \___/ \_| \_/
    //

    template<class T>
    VkVertexInputBindingDescription Generate(uint32_t indexOfBinding = 0,
                                             VkVertexInputRate inputRate = VK_VERTEX_INPUT_RATE_VERTEX);

    //  _____ ___  _________  _      _____ ___  ___ _____  _   _  _____   ___   _____  _____  _____  _   _
    // |_   _||  \/  || ___ \| |    |  ___||  \/  ||  ___|| \ | ||_   _| / _ \ |_   _||_   _||  _  || \ | |
    //   | |  | .  . || |_/ /| |    | |__  | .  . || |__  |  \| |  | |  / /_\ \  | |    | |  | | | ||  \| |
    //   | |  | |\/| ||  __/ | |    |  __| | |\/| ||  __| | . ` |  | |  |  _  |  | |    | |  | | | || . ` |
    //  _| |_ | |  | || |    | |____| |___ | |  | || |___ | |\  |  | |  | | | |  | |   _| |_ \ \_/ /| |\  |
    //  \___/ \_|  |_/\_|    \_____/\____/ \_|  |_/\____/ \_| \_/  \_/  \_| |_/  \_/   \___/  \___/ \_| \_/
    //


    template<class T>
    VkVertexInputBindingDescription Generate(uint32_t indexOfBinding,
                                             VkVertexInputRate inputRate)
    {
        VkVertexInputBindingDescription vertexInputBindingDescription{};
        vertexInputBindingDescription.binding = indexOfBinding;
        vertexInputBindingDescription.stride = sizeof(T);
        vertexInputBindingDescription.inputRate = inputRate;

        return vertexInputBindingDescription;
    }
};


#endif //CLUSEK_RT_VERTEXBINDINGDESCRIPTORGENERATOR_H
