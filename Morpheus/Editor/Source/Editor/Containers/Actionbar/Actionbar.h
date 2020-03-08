#pragma once

#include "Editor/Containers/UIContainer.h"

namespace Editor {

	class Actionbar : public UIContainer
	{
	private:
		bool m_IsPlaying;

	public:
		Actionbar();

		void Render(entt::registry& registry) override;

	private:
		bool RenderButton(const char* icon, const char* label, bool disabled);
	};

}
