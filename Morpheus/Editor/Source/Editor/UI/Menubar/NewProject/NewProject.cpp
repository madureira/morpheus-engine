#include "NewProject.h"
#include "Editor/UI/FileSystemDialog/FileSystemDialog.h"
#include "Engine/Util/FileUtil.h"

namespace Editor {

	void NewProject::Draw(entt::registry& registry)
	{
		ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoMove
			| ImGuiWindowFlags_NoResize
			| ImGuiWindowFlags_NoCollapse
			| ImGuiWindowFlags_NoScrollbar;

		float modalWidth = 350.0f;
		float modalHeight = 170.0f;

		ImGuiIO& io = ImGui::GetIO(); (void)io;
		float posX = (io.DisplaySize.x - modalWidth) / 2;
		float posY = (io.DisplaySize.y - modalHeight) / 2;

		ImGui::SetNextWindowPos(ImVec2(posX, posY));
		ImGui::SetNextWindowSize(ImVec2(modalWidth, modalHeight));

		ImGui::OpenPopup("###new_project");
		if (ImGui::BeginPopupModal(ICON_FA_FOLDER_PLUS"  New###new_project", NULL, windowFlags))
		{
			ImGui::Dummy(ImVec2(5.0f, 0.0f));ImGui::SameLine();
			ImGui::Text("Create a new project");
			ImGui::Separator();

			ImGui::Dummy(ImVec2(0.0f, 5.0f));
			ImGui::Dummy(ImVec2(5.0f, 0.0f)); ImGui::SameLine();
			ImGui::Text("Project name:"); ImGui::SameLine();
			ImGui::InputText("##projectName", this->m_ProjectName.data(), this->m_ProjectName.size());

			ImGui::Dummy(ImVec2(0.0f, 5.0f));
			ImGui::Dummy(ImVec2(32.0f, 0.0f)); ImGui::SameLine();
			ImGui::Text("Location:"); ImGui::SameLine();
			ImGui::PushItemWidth(191);
			ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
			ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);
			ImGui::InputText("##projectLocation", this->m_ProjectLocation.data(), this->m_ProjectLocation.size());
			ImGui::PopItemFlag();
			ImGui::PopStyleVar();
			ImGui::PopItemWidth();
			ImGui::SameLine();

			if (ImGui::Button(ICON_FA_FOLDER_OPEN))
			{
				std::string selectedPath = FileSystemDialog::OpenFolderSelector();
				std::copy(selectedPath.begin(), selectedPath.end(), this->m_ProjectLocation.data());
			}

			ImGui::Dummy(ImVec2(0.0f, 5.0f));
			ImGui::Separator();
			ImGui::Dummy(ImVec2(0.0f, 5.0f));

			ImGui::Indent(203);
			if (ImGui::Button("Cancel"))
			{
				this->m_IsOpened = false;
				ImGui::CloseCurrentPopup();
			}
			ImGui::SameLine();

			std::string projectName(this->m_ProjectName.data());
			std::string projectLocation(this->m_ProjectLocation.data());

			if (projectName.empty() || projectLocation.empty())
			{
				ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
				ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);
			}

			ImGui::Indent(62);
			if (ImGui::Button("Confirm"))
			{
				ME_LOG_INFO("Creating project: {0} into directory: {1}", projectName, projectLocation);

				if (Morpheus::FileUtil::CreateFolder(projectLocation, projectName))
				{
					std::string pathSep = Morpheus::FileUtil::PathSeparator();
					std::string filePath = projectLocation + pathSep + projectName;
					Morpheus::FileUtil::WriteFile(filePath, "project.json", "{\n  name: \"" + projectName + "\"\n}");
					this->m_IsOpened = false;
					ImGui::CloseCurrentPopup();
					ME_LOG_INFO("Project create successfully");

					auto& projectEntity = registry.ctx<Morpheus::ProjectEntity>();
					auto& projectComponent = registry.get<Morpheus::ProjectComponent>(projectEntity.id);
					projectComponent.projectPath = filePath;
				}
				else
				{
					ME_LOG_ERROR("Fail to create the folder");
				}
			}

			if (projectName.empty() || projectLocation.empty())
			{
				ImGui::PopItemFlag();
				ImGui::PopStyleVar();
			}
			ImGui::EndPopup();
		}
	}

	bool NewProject::IsOpened()
	{
		return this->m_IsOpened;
	}

}
