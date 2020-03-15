#include "Hierarchy.h"

namespace Editor {

	void Hierarchy::Render(entt::registry& registry)
	{
		static bool* show = NULL;
		ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoCollapse
			| ImGuiWindowFlags_NoScrollbar;

		ImGui::Begin(ICON_FA_STREAM" Hierarchy###hierarchy", show, windowFlags);
		{
			auto& projectEntity = registry.ctx<Morpheus::ProjectEntity>();

			for (auto& sceneEntity : projectEntity.scenes)
			{
				std::string nodeTitle = ICON_FA_CUBE;
				nodeTitle += "  ";
				nodeTitle += sceneEntity.name;

				ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_None;
				if (ImGui::TreeNodeEx(nodeTitle.c_str(), flags))
				{
					ImGui::Indent();
					ImGui::Text(ICON_FA_VIDEO "  Camera");
					ImGui::Unindent();
					ImGui::TreePop();
				}
			}
		}
		ImGui::End();
	}

}
