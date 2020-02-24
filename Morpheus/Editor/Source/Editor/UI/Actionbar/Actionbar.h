#pragma once

#include "Editor/UI/UIComponent.h"

namespace Editor {

	class Actionbar : public UIComponent
	{
	private:
		bool m_IsPlaying;

	public:
		Actionbar();

		void Draw(entt::registry& registry) override;

	private:
		bool DrawButton(const char* icon, const char* label, bool disabled);
	};

}
