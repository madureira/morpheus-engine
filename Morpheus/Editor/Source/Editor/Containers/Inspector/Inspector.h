#pragma once

#include "Editor/Containers/UIContainer.h"

namespace Editor {

	class Inspector : public UIContainer
	{
	public:
		void Render(entt::registry& registry) override;
	};

}
