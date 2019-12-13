#pragma once

#include "Editor/UI/UIComponent.h"

namespace Editor {

	class NewProject : public UIComponent
	{
	private:
		bool m_IsOpened = true;
		char m_ProjectName[64] = "";
		char m_ProjectLocation[64] = "";

	public:
		void Draw(entt::registry& registry) override;
		bool IsOpened();
	};

}
