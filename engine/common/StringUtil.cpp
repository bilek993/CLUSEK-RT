//
// Created by jbili on 04.04.2021.
//

#include "StringUtil.h"

std::string StringUtil::FindDirectory(const std::string& input)
{
    const auto path = std::filesystem::path(input);
    const auto parentPath = path.parent_path();

    return parentPath.generic_string();
}

std::string StringUtil::FindExtension(std::string input)
{
    const auto position = input.find_last_of('.');

    if (position == std::string::npos)
        return "";

    std::transform(input.begin(), input.end(), input.begin(), ::toupper);
    return input.substr(position + 1);
}

std::string StringUtil::FindFilename(const std::string& input)
{
    const auto path = std::filesystem::path(input);
    const auto fileName = path.filename();

    return fileName.generic_string();
}
