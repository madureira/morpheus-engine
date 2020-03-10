#include "Menubar.h"
#include <nlohmann/json.hpp>
#include <Engine/Util/FileUtil.h>
#include <Engine/ECS/Components/WindowComponent.h>
#include "Editor/Components/FileSystemDialog/FileSystemDialog.h"

namespace Editor {

	using json = nlohmann::json;

	Menubar::Menubar()
		: m_NewProject(nullptr)
	{
	}

	Menubar::~Menubar()
	{
		delete this->m_NewProject;
	}

	void Menubar::Render(entt::registry& registry)
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
					std::string selectedProject = FileSystemDialog::OpenFileSelector("json");

					if (!selectedProject.empty())
					{
						json project = json::parse(Morpheus::FileUtil::ReadFile(selectedProject));

						if ((project.find("name") != project.end()) && (project.find("type") != project.end()))
						{
							auto& windowEntity = registry.ctx<Morpheus::WindowEntity>();
							auto& windowComponent = registry.get<Morpheus::WindowComponent>(windowEntity.id);
							GLFWwindow* nativeWindow = windowComponent.GetNativeWindow();
							std::string projectName = project["name"];
							glfwSetWindowTitle(nativeWindow, projectName.c_str());

							auto& projectEntity = registry.ctx<Morpheus::ProjectEntity>();
							auto& projectComponent = registry.get<Morpheus::ProjectComponent>(projectEntity.id);

							if (project["type"] == "3D")
							{
								projectComponent.projectType = Morpheus::ProjectComponent::ProjectType::THREE_DIMENSIONS;
							}
							else
							{
								projectComponent.projectType = Morpheus::ProjectComponent::ProjectType::TWO_DIMENSIONS;
							}
#ifdef WIN32
							projectComponent.projectPath = selectedProject.substr(0, selectedProject.find_last_of("\\/"));
#else
							projectComponent.projectPath = selectedProject.substr(0, selectedProject.find_last_of("/"));
#endif
							ME_LOG_INFO("Project selected: {0}", projectComponent.projectPath);
						}
						else
						{
							ME_LOG_ERROR("Invalid project");
						}
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
				this->m_NewProject->Render(registry);
			}
			else
			{
				this->m_NewProject = nullptr;
			}
		}
	}

}
