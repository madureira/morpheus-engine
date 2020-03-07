#include "Inspector.h"
#include "Editor/Components/ColorPicker/ColorPicker.h"

namespace Editor {

	Inspector::Inspector(entt::registry& registry)
	{
		auto& windowEntity = registry.ctx<Morpheus::WindowEntity>();
		this->m_ColorPicker = new ColorPicker("Background color", registry, windowEntity.id);
	}

	Inspector::~Inspector()
	{
		delete this->m_ColorPicker;
	}

	void Inspector::Draw(entt::registry& registry)
	{
		static bool* show = NULL;
		ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoCollapse
			| ImGuiWindowFlags_NoScrollbar;

		ImGui::Begin(ICON_FA_INFO_CIRCLE" Inspector###inspector", show, windowFlags);
		this->m_ColorPicker->Draw(registry);
		ImGui::End();
	}

}
