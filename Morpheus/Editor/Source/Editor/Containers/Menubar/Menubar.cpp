#include "Menubar.h"
#include <Engine/State/GlobalState.h>
#include <Engine/ECS/Components/WindowComponent.h>
#include "Editor/Widgets/FileSystemDialog/FileSystemDialog.h"
#include "./NewProject/NewProject.h"
#include "./NewScene/NewScene.h"

namespace Editor {

    Menubar::Menubar()
        : m_NewProject(nullptr)
        , m_NewScene(nullptr)
    {
    }

    Menubar::~Menubar()
    {
        delete m_NewProject;
        delete m_NewScene;
    }

    void Menubar::Render(entt::registry& registry)
    {
        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem(ICON_FA_FOLDER_PLUS "   New Project..."))
                {
                    if (m_NewProject == nullptr)
                    {
                        m_NewProject = new NewProject();
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
                    if (m_NewScene == nullptr)
                    {
                        m_NewScene = new NewScene();
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

            if (m_NewProject != nullptr && m_NewProject->IsOpened())
            {
                m_NewProject->Render(registry);
            }
            else
            {
                m_NewProject = nullptr;
            }

            if (m_NewScene != nullptr && m_NewScene->IsOpened())
            {
                m_NewScene->Render(registry);
            }
            else
            {
                m_NewScene = nullptr;
            }
        }
    }

}
