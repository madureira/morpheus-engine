#pragma once

#include "Editor/UI/UIContainer.h"

namespace Editor {

	class Actionbar : public UIContainer
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
