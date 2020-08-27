#include "Menubar.h"
#include <Engine/State/GlobalState.h>
#include <Engine/ECS/Components/WindowComponent.h>
#include "Editor/Widgets/FileSystemDialog/FileSystemDialog.h"

namespace Editor {

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

                auto& projectEntity = registry.ctx<Morpheus::ProjectEntity>();

                if (ImGui::MenuItem(ICON_FA_FOLDER_OPEN "  Open Project..."))
                {
                    std::string selectedProject = FileSystemDialog::OpenFileSelector("json");
                    if (!selectedProject.empty())
                    {
                        Morpheus::GlobalState::Load(registry, selectedProject);
                    }
                }

                ImGui::Separator();

                bool projectLoaded = !projectEntity.name.empty();

                if (!projectLoaded)
                {
                    ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
                    ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);
                }

                if (ImGui::MenuItem(ICON_FA_CUBE"   New Scene"))
                {
                    if (this->m_NewScene == nullptr)
                    {
                        this->m_NewScene = new NewScene();
                    }
                }

                if (ImGui::MenuItem(ICON_FA_SAVE"   Save"))
                {
                    Morpheus::GlobalState::Save(registry);
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
