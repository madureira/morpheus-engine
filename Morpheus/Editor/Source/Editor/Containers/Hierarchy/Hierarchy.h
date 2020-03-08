#pragma once

#include "Editor/Containers/UIContainer.h"

namespace Editor {

	class Hierarchy final : public UIContainer
	{
	public:
		void Render(entt::registry& registry) override;
	};

}
