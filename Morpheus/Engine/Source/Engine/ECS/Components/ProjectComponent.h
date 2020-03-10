#pragma once

#include <string>

namespace Morpheus {

	struct ProjectComponent final
	{
		enum class ProjectType
		{
			TWO_DIMENSIONS,
			THREE_DIMENSIONS
		};

		std::string projectPath;
		std::string projectName;
		ProjectType projectType;
	};

}
