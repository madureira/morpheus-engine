#pragma once

#include "Editor/UI/UIComponent.h"

namespace Editor {

	class Project : public UIComponent
	{
	public:
		void Draw(entt::registry& registry) override;
	};

}
