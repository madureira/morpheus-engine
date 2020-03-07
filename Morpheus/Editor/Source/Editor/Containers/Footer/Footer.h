#pragma once

#include "Editor/Containers/UIContainer.h"

namespace Editor {

	class Footer : public UIContainer
	{
	public:
		void Draw(entt::registry& registry) override;
	};

}
