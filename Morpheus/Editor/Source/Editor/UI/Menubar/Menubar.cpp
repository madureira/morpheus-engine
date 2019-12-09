#include "Menubar.h"

namespace Editor {

	Menubar::Menubar(Morpheus::Window* pWindow)
		: m_Window(pWindow)
	{
	}

	void Menubar::Draw(entt::registry& registry)
	{
		if (ImGui::BeginMainMenuBar()) {
			if (ImGui::BeginMenu("File")) {
				if (ImGui::MenuItem(ICON_FA_FOLDER_PLUS "   New Project...")) {}
				if (ImGui::MenuItem(ICON_FA_FOLDER_OPEN "  Open...")) {}
				if (ImGui::MenuItem(ICON_FA_SAVE"   Save")) {}
				ImGui::Separator();
				if (ImGui::MenuItem(ICON_FA_POWER_OFF"   Exit")) {
					this->m_Window->Close();
				}
				ImGui::EndMenu();
			}
			ImGui::EndMainMenuBar();
		}
	}

}
