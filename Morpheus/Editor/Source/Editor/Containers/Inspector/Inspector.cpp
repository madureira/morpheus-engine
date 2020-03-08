#include "Inspector.h"
#include "Editor/Components/ColorPicker/ColorPicker.h"

namespace Editor {

	void Inspector::Render(entt::registry& registry)
	{
		auto& windowEntity = registry.ctx<Morpheus::WindowEntity>();
		auto& color = registry.get<Morpheus::ColorComponent>(windowEntity.id);

		static bool* show = NULL;
		ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar;
		ImGui::Begin(ICON_FA_INFO_CIRCLE" Inspector###inspector", show, windowFlags);
		{
			ImVec4 bgColor(color.r, color.g, color.b, color.a);
			ColorPicker::Draw("Background color", bgColor);
			color.r = bgColor.x;
			color.g = bgColor.y;
			color.b = bgColor.z;
			color.a = bgColor.w;
		}
		ImGui::End();
	}

}
