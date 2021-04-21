//
// Created by jbili on 12.03.2021.
//

#ifndef CLUSEK_RT_STRINGUTIL_H
#define CLUSEK_RT_STRINGUTIL_H

#include <algorithm>
#include <string>
#include <filesystem>

namespace StringUtil
{
    std::string FindDirectory(const std::string& input);
    std::string FindExtension(std::string input);
    std::string FindFilename(const std::string& input);
}

#endif //CLUSEK_RT_STRINGUTIL_H
