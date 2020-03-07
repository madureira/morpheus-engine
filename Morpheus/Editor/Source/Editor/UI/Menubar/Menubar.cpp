#include "Menubar.h"
#include <Engine/ECS/Components/WindowComponent.h>
#include "Editor/UI/Components/FileSystemDialog/FileSystemDialog.h"

namespace Editor {

	Menubar::Menubar()
		: m_NewProject(nullptr)
	{
	}

	Menubar::~Menubar()
	{
		delete this->m_NewProject;
	}

	void Menubar::Draw(entt::registry& registry)
	{
		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem(ICON_FA_FOLDER_PLUS "   New Project..."))
				{
					if (this->m_NewProject == nullptr)
					{
						this->m_NewProject = new NewProject();
					}
				}

				if (ImGui::MenuItem(ICON_FA_FOLDER_OPEN "  Open Project..."))
				{
					std::string selectedProject = FileSystemDialog::OpenFolderSelector();
					if (!selectedProject.empty())
					{
						auto& projectEntity = registry.ctx<Morpheus::ProjectEntity>();
						auto& projectComponent = registry.get<Morpheus::ProjectComponent>(projectEntity.id);
						projectComponent.projectPath = selectedProject;
						ME_LOG_INFO("Project selected: {0}", selectedProject);
					}
				}

				if (ImGui::MenuItem(ICON_FA_SAVE"   Save"))
				{
				}

				ImGui::Separator();

				if (ImGui::MenuItem(ICON_FA_POWER_OFF"   Exit"))
				{
					auto& windowEntity = registry.ctx<Morpheus::WindowEntity>();
					auto& windowComponent = registry.get<Morpheus::WindowComponent>(windowEntity.id);
					windowComponent.Close();
				}
				ImGui::EndMenu();
			}
			ImGui::EndMainMenuBar();

			if (this->m_NewProject != nullptr && this->m_NewProject->IsOpened())
			{
				this->m_NewProject->Draw(registry);
			}
			else
			{
				this->m_NewProject = nullptr;
			}
		}
	}

}
