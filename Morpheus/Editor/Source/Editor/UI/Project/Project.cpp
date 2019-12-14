#include "Project.h"
#include <iostream>

namespace Editor {

	Project::Project()
	{
		this->m_TreeView = new TreeView();
	}

	void Project::Draw(entt::registry& registry)
	{
		ImGui::Begin(ICON_FA_FOLDER" Project###project");
		{
			static float w = 200.0f;
			ImVec2 cr = ImGui::GetWindowContentRegionMax();

			ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));

			ImGui::PushStyleColor(ImGuiCol_ChildBg, { 0.180f, 0.180f , 0.180f , 1.00f });
			ImGui::BeginChild("TreeView", ImVec2(w, 0), true);
			this->m_TreeView->Draw(registry);
			ImGui::EndChild();
			ImGui::PopStyleColor();

			ImGui::SameLine();
			ImGui::InvisibleButton("vsplitter", ImVec2(5.0f, cr.y - 30));
			if (ImGui::IsItemHovered())
			{
				ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeEW);
			}

			if (ImGui::IsItemActive())
			{
				ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeEW);
				if (w + ImGui::GetIO().MouseDelta.x > 10 && w + ImGui::GetIO().MouseDelta.x < cr.x - 20)
				{
					w += ImGui::GetIO().MouseDelta.x;
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

}
