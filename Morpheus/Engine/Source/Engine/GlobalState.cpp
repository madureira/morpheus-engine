#include "mepch.h"
#include "GlobalState.h"
#include <vector>
#include <Engine/Util/UUID.h>
#include <Engine/Util/JSON.h>
#include <Engine/Util/FileUtil.h>

namespace Morpheus {

	void GlobalState::Save(entt::registry& registry)
	{
		auto& projectEntity = registry.ctx<Morpheus::ProjectEntity>();
		auto& projectComponent = registry.get<Morpheus::ProjectComponent>(projectEntity.id);

		static std::string& PATH_SEP = FileUtil::PathSeparator();
		std::string& projectPath = projectComponent.projectPath;
		std::string scenesPath = projectPath + PATH_SEP + SCENES_DIR;

		std::vector<std::string> scenesNames;

		for (auto& sceneEntity : projectComponent.projectScenes)
		{
			JSON scene;
			scene["uuid"] = sceneEntity.uuid;
			scene["name"] = sceneEntity.name;

			scenesNames.push_back(sceneEntity.name);
			std::string sceneFile = sceneEntity.name + ".json";

			FileUtil::WriteFile(scenesPath, sceneFile, scene.dump(4));
		}

		JSON project;
		project["uuid"] = projectComponent.uuid;
		project["name"] = projectComponent.projectName;
		project["type"] = projectComponent.projectType;
		project["scenes"] = scenesNames;

		FileUtil::WriteFile(projectPath, PROJECT_FILE, project.dump(4));

		ME_LOG_INFO("Project saved successfully");
	}

	void GlobalState::Load(entt::registry& registry, std::string& projectFilePath)
	{
		static std::string& PATH_SEP = FileUtil::PathSeparator();

		auto& projectEntity = registry.ctx<Morpheus::ProjectEntity>();
		auto& projectComponent = registry.get<Morpheus::ProjectComponent>(projectEntity.id);

		JSON project = JSON::parse(Morpheus::FileUtil::ReadFile(projectFilePath));

		if ((project.find("name") != project.end()) && (project.find("type") != project.end()))
		{
			static std::string pathSep("\\/");
#ifndef WIN32
			static std::string pathSep("/");
#endif
			projectComponent.projectPath = projectFilePath.substr(0, projectFilePath.find_last_of(pathSep));
			projectComponent.uuid = project["uuid"].get<std::string>();
			projectComponent.projectName = project["name"].get<std::string>();
			projectComponent.projectType = project["type"].get<std::string>();

			for (auto& scene : projectComponent.projectScenes)
			{
				registry.destroy(scene.id);
			}
			projectComponent.projectScenes.clear();

			for (auto& sceneName : project["scenes"].get<std::vector<std::string>>())
			{
				std::string sceneFilePath = projectComponent.projectPath + PATH_SEP + SCENES_DIR + PATH_SEP + sceneName + ".json";
				JSON scene = JSON::parse(Morpheus::FileUtil::ReadFile(sceneFilePath));

				Morpheus::SceneEntity sceneEntity{ registry.create() };
				sceneEntity.uuid = scene["uuid"].get<std::string>();
				sceneEntity.name = scene["name"].get<std::string>();
				registry.set<Morpheus::SceneEntity>(sceneEntity);

				projectComponent.projectScenes.push_back(sceneEntity);
			}

			ME_LOG_INFO("Project selected: {0}", projectFilePath);
		}
		else
		{
			ME_LOG_ERROR("Invalid project");
		}
	}

}
