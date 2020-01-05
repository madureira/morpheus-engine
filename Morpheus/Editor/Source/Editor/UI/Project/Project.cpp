#include "Project.h"
#include "Engine/Util/FileUtil.h"
#include <functional>

namespace Editor {

	Project::Project(entt::registry& registry)
		: m_Preview(nullptr)
		, m_TreeView(nullptr)
		, m_CodeEditor(nullptr)
		, m_ProjectPath("")
		, m_CurrentFolderSelected("")
		, m_CurrentFileSelected("")
	{
		this->m_Preview = new Preview(
			[&selectedFolder = this->m_CurrentFolderSelected](std::string selectedFolderByUser) {
				selectedFolder = selectedFolderByUser;
			},
			[&selectedFile = this->m_CurrentFileSelected](std::string selectedFileByUser) {
				selectedFile = selectedFileByUser;
			}
		);
	}

	Project::~Project()
	{
		delete this->m_Preview;
		delete this->m_TreeView;
		delete this->m_CodeEditor;
	}

	void Project::Draw(entt::registry& registry)
	{
		auto& projectEntity = registry.ctx<Morpheus::ProjectEntity>();
		auto& projectComponent = registry.get<Morpheus::ProjectComponent>(projectEntity.id);

		this->UpdateProjectPath(projectComponent);
		this->OpenCodeEditor(registry);

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

	void Project::UpdateProjectPath(Morpheus::ProjectComponent& projectComponent)
	{
		if (this->m_ProjectPath != projectComponent.projectPath && !projectComponent.projectPath.empty())
		{
			delete this->m_TreeView;

			this->m_ProjectPath = projectComponent.projectPath;
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

	void Project::OpenCodeEditor(entt::registry& registry)
	{
		static bool showCodeEditor = false;
		static std::string filePath = "";

		if (!this->m_CurrentFileSelected.empty() && this->m_CurrentFileSelected != filePath)
		{
			showCodeEditor = true;
			filePath = this->m_CurrentFileSelected;
			this->m_CodeEditor = new CodeEditor(this->m_CurrentFileSelected);
		}

		if (showCodeEditor)
		{
			this->m_CodeEditor->Draw(registry);
		}
	}

}
