#pragma once

#include "Editor/Containers/UIContainer.h"
#include <Engine/Log/Log.h>

namespace Editor {

	class Console final : public UIContainer
	{
	public:
		void Render(entt::registry& registry) override;
	};

}
