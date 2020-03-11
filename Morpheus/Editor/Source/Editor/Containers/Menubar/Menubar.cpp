#include "Menubar.h"
#include <nlohmann/json.hpp>
#include <Engine/Util/FileUtil.h>
#include <Engine/ECS/Components/WindowComponent.h>
#include "Editor/Components/FileSystemDialog/FileSystemDialog.h"

namespace Editor {

	using json = nlohmann::json;

	Menubar::Menubar()
		: m_NewProject(nullptr)
		, m_NewScene(nullptr)
	{
	}

	Menubar::~Menubar()
	{
		delete this->m_NewProject;
		delete this->m_NewScene;
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
							std::string projectName = project["name"].get<std::string>();

							auto& windowEntity = registry.ctx<Morpheus::WindowEntity>();
							auto& windowComponent = registry.get<Morpheus::WindowComponent>(windowEntity.id);
							GLFWwindow* nativeWindow = windowComponent.GetNativeWindow();
							glfwSetWindowTitle(nativeWindow, projectName.c_str());

							auto& projectEntity = registry.ctx<Morpheus::ProjectEntity>();
							auto& projectComponent = registry.get<Morpheus::ProjectComponent>(projectEntity.id);
							projectComponent.projectName = projectName;

							if (project["type"] == "3D")
							{
								projectComponent.projectType = Morpheus::ProjectComponent::ProjectType::THREE_DIMENSIONS;
							}
							else
							{
								projectComponent.projectType = Morpheus::ProjectComponent::ProjectType::TWO_DIMENSIONS;
							}

							std::string pathSep("\\/");
#ifndef WIN32
							pathSep = "/";
#endif
							projectComponent.projectPath = selectedProject.substr(0, selectedProject.find_last_of(pathSep));

							ME_LOG_INFO("Project selected: {0}", projectComponent.projectPath);
						}
						else
						{
							ME_LOG_ERROR("Invalid project");
						}
					}
				}

				ImGui::Separator();

				auto& projectEntity = registry.ctx<Morpheus::ProjectEntity>();
				auto& projectComponent = registry.get<Morpheus::ProjectComponent>(projectEntity.id);
				bool projectLoaded = !projectComponent.projectName.empty();

				if (!projectLoaded)
				{
					ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
					ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);
				}

				if (ImGui::MenuItem(ICON_FA_CUBES"   New Scene"))
				{
					if (this->m_NewScene == nullptr)
					{
						this->m_NewScene = new NewScene();
					}
				}

				if (ImGui::MenuItem(ICON_FA_SAVE"   Save"))
				{
					ME_LOG_INFO("Current project status saved successfully!");
				}

				if (!projectLoaded)
				{
					ImGui::PopItemFlag();
					ImGui::PopStyleVar();
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

			if (this->m_NewScene != nullptr && this->m_NewScene->IsOpened())
			{
				this->m_NewScene->Render(registry);
			}
			else
			{
				this->m_NewScene = nullptr;
			}
		}
	}

}
