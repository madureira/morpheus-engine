#pragma once

#include "Editor/UI/UIComponent.h"
#include <array>

namespace Editor {

	class NewProject : public UIComponent
	{
	private:
		bool m_IsOpened = true;
		std::array<char, 256> m_ProjectName;
		std::array<char, 512> m_ProjectLocation;

	public:
		void Draw(entt::registry& registry) override;
		bool IsOpened();
	};

}
