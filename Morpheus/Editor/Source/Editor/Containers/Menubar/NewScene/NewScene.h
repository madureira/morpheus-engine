#pragma once

#include "Editor/Containers/UIContainer.h"

namespace Editor {

	class NewScene final : public UIContainer
	{
	private:
		char m_SceneName[128];
		bool m_IsOpened = true;

	public:
		void Render(entt::registry& registry) override;
		bool IsOpened() const;
	};

}
