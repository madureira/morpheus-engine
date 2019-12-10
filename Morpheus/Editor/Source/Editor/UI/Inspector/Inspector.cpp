#include "Inspector.h"
#include "Editor/UI/ColorPicker/ColorPicker.h"

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
		ImGui::Begin(ICON_FA_INFO_CIRCLE" Inspector###inspector");
		this->m_ColorPicker->Draw(registry);
		ImGui::End();
	}

}
