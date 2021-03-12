//
// Created by jbili on 12.03.2021.
//

#ifndef CLUSEK_RT_STRINGUTIL_H
#define CLUSEK_RT_STRINGUTIL_H

#include <string>
#include <filesystem>

namespace StringUtil
{
    std::string FindDirectory(const std::string& input)
    {
        const auto path = std::filesystem::path(input);
        const auto parentPath = path.parent_path();

        return parentPath.generic_string();
    }

    std::string FindExtension(std::string input)
    {
        const auto position = input.find_last_of('.');

        if (position == std::string::npos)
            return "";

        std::transform(input.begin(), input.end(), input.begin(), ::toupper);
        return input.substr(position + 1);
    }

    std::string FindFilename(const std::string& input)
    {
        const auto path = std::filesystem::path(input);
        const auto fileName = path.filename();

        return fileName.generic_string();
    }
}

#endif //CLUSEK_RT_STRINGUTIL_H
