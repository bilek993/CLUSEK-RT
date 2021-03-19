//
// Created by jbili on 19.03.2021.
//

#ifndef CLUSEK_RT_CONFIGDATA_H
#define CLUSEK_RT_CONFIGDATA_H

#include "ConfigMacros.h"

CONFIG_OBJECT(NAME = ConfigData)
struct ConfigData
{
    CONFIG_PARAMETER(NAME = FilePath, TYPE = std::string)
    std::string FilePath{};
};

#endif //CLUSEK_RT_CONFIGDATA_H
