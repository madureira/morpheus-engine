#pragma once

#include "Editor/Containers/UIContainer.h"

namespace Editor {

	class Footer final : public UIContainer
	{
	public:
		void Render(entt::registry& registry) override;
	};

}
