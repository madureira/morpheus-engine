#include "Hierarchy.h"

namespace Editor {

	Hierarchy::Hierarchy(entt::registry& registry)
	{
	}

	void Hierarchy::Draw(entt::registry& registry)
	{
		ImGui::Begin(ICON_FA_STREAM" Hierarchy###hierarchy");
		ImGui::End();
	}

}
