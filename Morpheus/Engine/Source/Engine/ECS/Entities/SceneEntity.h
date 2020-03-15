#pragma once

#include <string>
#include "Entity.h"

namespace Morpheus {

	struct SceneEntity final : public Entity
	{
		std::string name;
	};

}
