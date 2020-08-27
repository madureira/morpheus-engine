#pragma once

#include <string>
#include <Engine/ECS/ECS.h>

namespace Morpheus {

    constexpr auto PROJECT_FILE = "project.json";
    constexpr auto SCENES_DIR = "Scenes";
    constexpr auto ASSETS_DIR = "Assets";
    constexpr auto CODE_INDENT = 4;

    class GlobalState final
    {
    public:
        static void Save(entt::registry& registry);
        static void Load(entt::registry& registry, std::string& projectFilePath);
    };

}
