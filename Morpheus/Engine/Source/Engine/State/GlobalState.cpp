#include "mepch.h"
#include "GlobalState.h"
#include <Engine/Util/UUID.h>
#include <Engine/Util/JSON.h>
#include <Engine/Util/FileUtil.h>
#include <vector>

namespace Morpheus {

    void GlobalState::Save(entt::registry& registry)
    {
        auto& projectEntity = registry.ctx<Morpheus::ProjectEntity>();

        static std::string PATH_SEP(FileUtil::PathSeparator());
        std::string projectPath(projectEntity.path);
        std::string scenesPath(projectPath + PATH_SEP + SCENES_DIR);

        std::vector<std::string> scenesNames;
        for (auto& sceneEntity : projectEntity.scenes)
        {
            JSON scene;
            scene["uuid"] = sceneEntity.uuid;
            scene["name"] = sceneEntity.name;

            scenesNames.push_back(sceneEntity.name);
            std::string sceneFile(sceneEntity.name + Morpheus::Extension::SCN);

            FileUtil::WriteFile(scenesPath, sceneFile, scene.dump(CODE_INDENT));
        }

        JSON project;
        project["uuid"] = projectEntity.uuid;
        project["name"] = projectEntity.name;
        project["type"] = projectEntity.type;
        project["scenes"] = scenesNames;

        FileUtil::WriteFile(projectPath, PROJECT_FILE, project.dump(CODE_INDENT));

        projectEntity.reload = true;

        ME_LOG_INFO("Project saved successfully");
    }

    void GlobalState::Load(entt::registry& registry, std::string& projectFilePath)
    {
        static std::string PATH_SEP(FileUtil::PathSeparator());

        auto& projectEntity = registry.ctx<Morpheus::ProjectEntity>();

        JSON project = JSON::parse(Morpheus::FileUtil::ReadFile(projectFilePath));

        if ((project.find("uuid") != project.end()) && (project.find("name") != project.end()) && (project.find("type") != project.end()))
        {
            static std::string pathSep("\\/");
#ifndef WIN32
            pathSep = "/";
#endif
            projectEntity.uuid = project["uuid"].get<std::string>();
            projectEntity.name = project["name"].get<std::string>();
            projectEntity.type = project["type"].get<std::string>();
            projectEntity.path = projectFilePath.substr(0, projectFilePath.find_last_of(pathSep));

            for (auto& scene : projectEntity.scenes)
            {
                registry.destroy(scene.id);
            }
            projectEntity.scenes.clear();

            for (auto& sceneName : project["scenes"].get<std::vector<std::string>>())
            {
                std::string sceneFilePath(projectEntity.path + PATH_SEP + SCENES_DIR + PATH_SEP + sceneName + Morpheus::Extension::SCN);

                JSON scene = JSON::parse(Morpheus::FileUtil::ReadFile(sceneFilePath));

                Morpheus::SceneEntity sceneEntity{ registry.create() };
                sceneEntity.uuid = scene["uuid"].get<std::string>();
                sceneEntity.name = scene["name"].get<std::string>();
                registry.set<Morpheus::SceneEntity>(sceneEntity);

                projectEntity.scenes.push_back(sceneEntity);
            }

            ME_LOG_INFO("Project selected: {0}", projectFilePath);
        }
        else
        {
            ME_LOG_ERROR("Invalid project");
        }
    }

}
