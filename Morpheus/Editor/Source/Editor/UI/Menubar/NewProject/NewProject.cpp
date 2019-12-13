#include "NewProject.h"
#include "Editor/UI/FileSystemDialog/FileSystemDialog.h"
#include "Engine/Log/Log.h"

namespace Editor {

	void NewProject::Draw(entt::registry& registry)
	{
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoMove
			| ImGuiWindowFlags_NoResize
			| ImGuiWindowFlags_NoCollapse
			| ImGuiWindowFlags_NoScrollbar;

		float width = 380.0f;
		float height = 170.0f;

		ImGuiIO& io = ImGui::GetIO(); (void)io;
		float posX = (io.DisplaySize.x - width) / 2;
		float posY = (io.DisplaySize.y - height) / 2;

		ImGui::SetNextWindowPos(ImVec2(posX, posY));
		ImGui::SetNextWindowSize(ImVec2(width, height));

		ImGui::OpenPopup("###new_project");
		if (ImGui::BeginPopupModal(ICON_FA_FOLDER_PLUS"  New###new_project", NULL, window_flags))
		{
			ImGui::Text("Create a new project");
			ImGui::Separator();
			ImGui::Spacing();
			ImGui::Spacing();
			ImGui::Spacing();
			ImGui::Spacing();
			ImGui::Spacing();

			ImGui::Indent(10);
			ImGui::Text("Project name:");
			ImGui::SameLine(110);
			ImGui::InputText("##projectName", this->m_ProjectName, IM_ARRAYSIZE(this->m_ProjectName));
			ImGui::Spacing();
			ImGui::Spacing();
			ImGui::Spacing();

			ImGui::Indent(30);
			ImGui::Text("Location:");
			ImGui::SameLine(110);
			ImGui::InputText("##projectLocation", this->m_ProjectLocation, IM_ARRAYSIZE(this->m_ProjectLocation));
			ImGui::Spacing();
			ImGui::Spacing();
			ImGui::Spacing();
			ImGui::Spacing();
			ImGui::Spacing();

			ImGui::Separator();
			ImGui::Spacing();
			ImGui::Spacing();
			ImGui::Spacing();
			ImGui::Spacing();

			ImGui::Indent(190);
			if (ImGui::Button("Confirm"))
			{
				std::string selectedPath = FileSystemDialog::Open();
				ME_LOG_INFO("SELECTED FILE: {0}", selectedPath);
			}
			ImGui::SameLine();

			ImGui::Indent(70);
			if (ImGui::Button("Cancel"))
			{
				this->m_IsOpened = false;
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();
		}
	}

	bool NewProject::IsOpened()
	{
		return this->m_IsOpened;
	}

}
