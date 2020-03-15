#pragma once

#include "Entity.h"
#include <string>

namespace Morpheus {

	struct SceneEntity final : public Entity
	{
		std::string name;
	};

}
