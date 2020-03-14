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
			auto& projectComponent = registry.get<Morpheus::ProjectComponent>(projectEntity.id);

			for (auto& sceneEntity : projectComponent.projectScenes)
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

				if (ImGui::IsItemClicked() || ImGui::IsItemFocused())
				{
					ME_LOG_INFO("Scene {0} clicked", sceneEntity.name);
				}
			}
		}
		ImGui::End();
	}

}
