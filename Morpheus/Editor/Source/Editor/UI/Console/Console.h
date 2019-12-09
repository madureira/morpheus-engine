#pragma once

#include "Editor/UI/UIComponent.h"

namespace Editor {

	class Console : public UIComponent
	{
	public:
		void Draw(entt::registry& registry) override;
	};

}
