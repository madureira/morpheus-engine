#include "Project.h"
#include <functional>
#include "Engine/Util/FileUtil.h"

namespace Editor {

	Project::Project(entt::registry& registry)
		: m_ProjectPath("")
		, m_TreeView(nullptr)
		, m_Preview(nullptr)
		, m_CurrentFolderSelected("")
		, m_CurrentFileSelected("")
	{
		this->m_Preview = new Preview([&selectedFolder = this->m_CurrentFolderSelected](std::string selectedFolderByUser) {
			selectedFolder = selectedFolderByUser;
		});
		this->UpdateProjectPath(registry);
	}

	Project::~Project()
	{
		delete this->m_Preview;
		delete this->m_TreeView;
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
			ImGui::BeginChild("FilesPreview", ImVec2(0, 0), false);
			this->m_Preview->UpdateSelectedFolder(this->m_CurrentFolderSelected);
			this->m_Preview->Draw(registry);
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

			this->m_CurrentFolderSelected = this->m_ProjectPath;
			this->m_CurrentFileSelected = "";

			this->m_TreeView = new TreeView(this->m_ProjectPath,
				[&selectedFolder = this->m_CurrentFolderSelected](std::string selectedFolderByUser) {
					selectedFolder = selectedFolderByUser;
				},
				[&selectedFile = this->m_CurrentFileSelected](std::string selectedFileByUser) {
					selectedFile = selectedFileByUser;
				}
			);
		}
	}

}
