//
// Created by jbili on 02.06.2021.
//

#ifndef CLUSEK_RT_FATVERTEX_H
#define CLUSEK_RT_FATVERTEX_H

#include <glm/glm.hpp>

#include "../../common/generators/VertexMacros.h"

VERTEX_STRUCTURE(FatVertex)
struct FatVertex final
{
    GENERATE_ATTRIBUTE(Position, 0, 0, VK_FORMAT_R32G32B32_SFLOAT)
    glm::vec3 Position;
};

#endif //CLUSEK_RT_FATVERTEX_H
