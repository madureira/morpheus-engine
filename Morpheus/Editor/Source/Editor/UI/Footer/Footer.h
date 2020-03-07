#pragma once

#include "Editor/UI/UIContainer.h"

namespace Editor {

	class Footer : public UIContainer
	{
	public:
		void Draw(entt::registry& registry) override;
	};

}
