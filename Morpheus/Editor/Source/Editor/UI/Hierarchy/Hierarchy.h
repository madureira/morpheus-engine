#pragma once

#include "Editor/UI/UIComponent.h"

namespace Editor {

	class Hierarchy : public UIComponent
	{
	public:
		void Draw(entt::registry& registry) override;
	};

}
