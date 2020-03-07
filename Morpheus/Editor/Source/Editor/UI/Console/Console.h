#pragma once

#include "Editor/UI/UIContainer.h"
#include <Engine/Log/Log.h>

namespace Editor {

	class Console : public UIContainer
	{
	public:
		void Draw(entt::registry& registry) override;
	};

}
