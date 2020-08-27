#pragma once

#include <vector>
#include "Entity.h"
#include "SceneEntity.h"

namespace Morpheus {

    struct ProjectType final
    {
        inline static const std::string TWO_DIMENSIONS = "2D";
        inline static const std::string THREE_DIMENSIONS = "3D";
    };

    struct ProjectEntity final : public Entity
    {
        std::string path;
        std::string name;
        std::string type;
        std::vector<SceneEntity> scenes;
        bool reload;
        bool resetTreeViewOnly;
    };

}
