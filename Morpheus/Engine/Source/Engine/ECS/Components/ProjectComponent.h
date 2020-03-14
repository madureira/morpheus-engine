#pragma once

#include <string>
#include <vector>

namespace Morpheus {

	struct ProjectType final
	{
		inline static const std::string TWO_DIMENSIONS = "2D";
		inline static const std::string THREE_DIMENSIONS = "3D";
	};

	struct ProjectComponent final
	{
		std::string uuid;
		std::string projectPath;
		std::string projectName;
		std::string projectType;
		std::vector<SceneEntity> projectScenes;
	};

}
