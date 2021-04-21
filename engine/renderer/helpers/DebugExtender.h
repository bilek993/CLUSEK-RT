//
// Created by jbili on 20.04.2021.
//

#ifndef CLUSEK_RT_DEBUGEXTENDER_H
#define CLUSEK_RT_DEBUGEXTENDER_H

#include <vector>

namespace DebugExtender
{
    std::vector<const char*> GetValidationLayers();
    void AddDebugExtensions(std::vector<const char*>& extensions);
};


#endif //CLUSEK_RT_DEBUGEXTENDER_H
