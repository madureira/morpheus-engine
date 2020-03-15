#pragma once

#include <string>
#include <entt/entt.hpp>

namespace Morpheus {

	struct Entity
	{
		entt::entity id;
		std::string uuid;
	};

}
