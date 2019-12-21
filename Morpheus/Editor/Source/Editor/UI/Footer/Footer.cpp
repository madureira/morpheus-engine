#include "Footer.h"

namespace Editor {

	void Footer::Draw(entt::registry& registry)
	{
		ImGuiIO& io = ImGui::GetIO();

		static bool showFooter = true;
		ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoMove
			| ImGuiWindowFlags_NoResize
			| ImGuiWindowFlags_NoTitleBar
			| ImGuiWindowFlags_NoCollapse
			| ImGuiWindowFlags_NoScrollbar
			| ImGuiWindowFlags_NoSavedSettings
			| ImGuiWindowFlags_NoDocking;

		ImGui::SetNextWindowPos(ImVec2(0.0f, io.DisplaySize.y - 26.0f));
		ImGui::SetNextWindowSize(ImVec2(io.DisplaySize.x, 25.f));
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);

		ImGui::Begin("Footer", &showFooter, windowFlags);
		ImGui::Text("Status");
		ImGui::End();
		ImGui::PopStyleVar();
	}

}
