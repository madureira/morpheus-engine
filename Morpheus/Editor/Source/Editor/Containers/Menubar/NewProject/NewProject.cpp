#include "NewProject.h"
#include <Engine/Util/FileUtil.h>
#include <Engine/ECS/Components/WindowComponent.h>
#include "Editor/Components/FileSystemDialog/FileSystemDialog.h"
#include "Editor/Utils/InputUtils.h"

namespace Editor {

	void NewProject::Render(entt::registry& registry)
	{
		ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoMove
			| ImGuiWindowFlags_NoResize
			| ImGuiWindowFlags_NoCollapse
			| ImGuiWindowFlags_NoScrollbar;

		float modalWidth = 350.0f;
		float modalHeight = 170.0f;

		ImGuiViewport* viewport = ImGui::GetMainViewport();
		float posX = (viewport->Pos.x + ((viewport->Size.x - modalWidth) / 2));
		float posY = (viewport->Pos.y + ((viewport->Size.y - modalHeight) / 2));

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
			ImGuiInputTextFlags flags = ImGuiInputTextFlags_CallbackCharFilter;
			ImGui::InputText("##projectName", this->m_ProjectName, IM_ARRAYSIZE(this->m_ProjectName), flags, InputUtils::SanitizeCallback);

			ImGui::Dummy(ImVec2(0.0f, 5.0f));
			ImGui::Dummy(ImVec2(32.0f, 0.0f)); ImGui::SameLine();
			ImGui::Text("Location:"); ImGui::SameLine();
			ImGui::PushItemWidth(191);
			ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
			ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);
			ImGui::InputText("##projectLocation", this->m_ProjectLocation, IM_ARRAYSIZE(this->m_ProjectLocation));
			ImGui::PopItemFlag();
			ImGui::PopStyleVar();
			ImGui::PopItemWidth();
			ImGui::SameLine();

			if (ImGui::Button(ICON_FA_FOLDER_OPEN))
			{
				std::string selectedPath = FileSystemDialog::OpenFolderSelector();
				std::copy(selectedPath.begin(), selectedPath.end(), this->m_ProjectLocation);
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

			std::string projectName(this->m_ProjectName);
			std::string projectLocation(this->m_ProjectLocation);

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
					Morpheus::FileUtil::WriteFile(filePath, "project.json", "{\n  \"name\": \"" + projectName + "\",\n  \"type\": \"2D\"\n}");

					auto& projectEntity = registry.ctx<Morpheus::ProjectEntity>();
					auto& projectComponent = registry.get<Morpheus::ProjectComponent>(projectEntity.id);
					projectComponent.projectPath = filePath;
					projectComponent.projectName = projectName;
					projectComponent.projectType = Morpheus::ProjectComponent::ProjectType::TWO_DIMENSIONS;

					auto& windowEntity = registry.ctx<Morpheus::WindowEntity>();
					auto& windowComponent = registry.get<Morpheus::WindowComponent>(windowEntity.id);
					GLFWwindow* nativeWindow = windowComponent.GetNativeWindow();
					glfwSetWindowTitle(nativeWindow, projectName.c_str());

					this->m_IsOpened = false;
					ImGui::CloseCurrentPopup();
					ME_LOG_INFO("Project create successfully");
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

	bool NewProject::IsOpened() const
	{
		return this->m_IsOpened;
	}

}
