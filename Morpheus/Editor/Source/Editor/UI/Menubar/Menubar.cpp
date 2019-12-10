#include "Menubar.h"
#include "Engine/ECS/Components/WindowComponent.h"

namespace Editor {

	void Menubar::Draw(entt::registry& registry)
	{
		if (ImGui::BeginMainMenuBar()) {
			if (ImGui::BeginMenu("File")) {
				if (ImGui::MenuItem(ICON_FA_FOLDER_PLUS "   New Project...")) {}
				if (ImGui::MenuItem(ICON_FA_FOLDER_OPEN "  Open...")) {}
				if (ImGui::MenuItem(ICON_FA_SAVE"   Save")) {}
				ImGui::Separator();
				if (ImGui::MenuItem(ICON_FA_POWER_OFF"   Exit")) {
					auto& windowEntity = registry.ctx<Morpheus::WindowEntity>();
					auto& windowComponent = registry.get<Morpheus::WindowComponent>(windowEntity.id);
					windowComponent.Close();
				}
				ImGui::EndMenu();
			}
			ImGui::EndMainMenuBar();
		}
	}

}
