#include "Hierarchy.h"

namespace Editor {

	void Hierarchy::Draw(entt::registry& registry)
	{
		static bool* show = NULL;
		ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoCollapse
			| ImGuiWindowFlags_NoScrollbar;

		ImGui::Begin(ICON_FA_STREAM" Hierarchy###hierarchy", show, windowFlags);
		ImGui::End();
	}

}
