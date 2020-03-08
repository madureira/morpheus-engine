#pragma once

#include "Editor/Containers/UIContainer.h"
#include <array>

namespace Editor {

	class NewProject final : public UIContainer
	{
	private:
		bool m_IsOpened = true;
		char m_ProjectName[128];
		char m_ProjectLocation[512];

	public:
		void Render(entt::registry& registry) override;
		bool IsOpened() const;
	};

}
