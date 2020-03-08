#pragma once

#include "Editor/Containers/UIContainer.h"

namespace Editor {

	class Footer : public UIContainer
	{
	public:
		void Render(entt::registry& registry) override;
	};

}
