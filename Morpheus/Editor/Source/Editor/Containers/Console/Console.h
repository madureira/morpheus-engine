#pragma once

#include <Engine/Log/Log.h>
#include "Editor/Containers/UIContainer.h"

namespace Editor {

	class Console final : public UIContainer
	{
	public:
		void Render(entt::registry& registry) override;
	};

}
