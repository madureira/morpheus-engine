#pragma once

#include "Editor/UI/UIComponent.h"

namespace Editor {

	class Hierarchy : public UIComponent
	{
	public:
		Hierarchy(entt::registry& registry);
		void Draw(entt::registry& registry) override;
	};

}
