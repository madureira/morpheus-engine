#include "Project.h"
#include <iostream>

namespace Editor {

	Project::Project(entt::registry& registry)
		: m_ProjectPath(""),
		m_TreeView(nullptr)
	{
		this->UpdateProjectPath(registry);
	}

	void Project::Draw(entt::registry& registry)
	{
		this->UpdateProjectPath(registry);

		ImGui::Begin(ICON_FA_FOLDER" Project###project");
		{
			static float s_treeViewWidth = 200.0f;
			ImVec2 contentRegionMax = ImGui::GetWindowContentRegionMax();

			ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));

			ImGui::PushStyleColor(ImGuiCol_ChildBg, { 0.180f, 0.180f , 0.180f , 1.00f });
			ImGui::BeginChild("TreeView", ImVec2(s_treeViewWidth, 0), false, ImGuiWindowFlags_HorizontalScrollbar);

			if (this->m_TreeView != nullptr)
			{
				this->m_TreeView->Draw(registry);
			}

			ImGui::EndChild();
			ImGui::PopStyleColor();

			ImGui::SameLine();
			ImGui::InvisibleButton("vsplitter", ImVec2(5.0f, contentRegionMax.y - 30));
			if (ImGui::IsItemHovered())
			{
				ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeEW);
			}

			if (ImGui::IsItemActive())
			{
				ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeEW);
				if (s_treeViewWidth + ImGui::GetIO().MouseDelta.x > 10 && s_treeViewWidth + ImGui::GetIO().MouseDelta.x < contentRegionMax.x - 20)
				{
					s_treeViewWidth += ImGui::GetIO().MouseDelta.x;
				}
			}
			ImGui::SameLine();

			ImGui::PushStyleColor(ImGuiCol_ChildBg, { 0.180f, 0.180f , 0.180f , 1.00f });
			ImGui::BeginChild("FilesPreview", ImVec2(0, 0), true);
			ImGui::EndChild();
			ImGui::PopStyleColor();

			ImGui::PopStyleVar();
		}
		ImGui::End();
	}

	void Project::UpdateProjectPath(entt::registry& registry)
	{
		auto& projectEntity = registry.ctx<Morpheus::ProjectEntity>();
		auto& projectComponent = registry.get<Morpheus::ProjectComponent>(projectEntity.id);

		if (this->m_ProjectPath.compare(projectComponent.projectPath) != 0
			&& !projectComponent.projectPath.empty())
		{
			this->m_ProjectPath = projectComponent.projectPath;
			delete this->m_TreeView;
			this->m_TreeView = new TreeView(this->m_ProjectPath);
		}
	}

}
