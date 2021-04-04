//
// Created by jbili on 04.04.2021.
//

#include "VulkanVersion.h"

uint32_t VulkanVersion::GenerateVersion(const std::string& version)
{
    try
    {
        std::vector<int> items{};

        std::stringstream versionStream(version);
        std::string item;

        while (std::getline(versionStream, item, '.'))
        {
            if (item.length() > 0)
            {
                items.emplace_back(std::stoi(item));
            }
        }

        if (item.length() < 3)
            throw std::runtime_error("Corrupted version input string!");

        return VK_MAKE_VERSION(item[0], item[1], item[2]);
    }
    catch (const std::exception& e)
    {
        LOG_WARNING(e.what());
        LOG_WARNING("Failed to generate version! Returning '1.0.0' version...");
        return VK_MAKE_VERSION(1, 0, 0);
    }
}
