#pragma once

#include "Editor/UI/UIComponent.h"
#include <Engine/Log/Log.h>

namespace Editor {

	class Console : public UIComponent
	{
	public:
		void Draw(entt::registry& registry) override;
	};

}
