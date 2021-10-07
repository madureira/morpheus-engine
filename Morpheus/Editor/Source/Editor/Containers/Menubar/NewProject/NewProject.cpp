#include "NewProject.h"
#include <Engine/State/GlobalState.h>
#include <Engine/Util/UUID.h>
#include <Engine/Util/FileUtil.h>
#include <Engine/ECS/Components/WindowComponent.h>
#include "Editor/Widgets/FileSystemDialog/FileSystemDialog.h"
#include "Editor/Widgets/Button/Button.h"
#include "Editor/Util/InputUtil.h"

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
            ImGui::InputText("##projectName", m_ProjectName, IM_ARRAYSIZE(m_ProjectName), flags, InputUtil::SanitizeCallback);

            ImGui::Dummy(ImVec2(0.0f, 5.0f));
            ImGui::Dummy(ImVec2(32.0f, 0.0f)); ImGui::SameLine();
            ImGui::Text("Location:"); ImGui::SameLine();
            ImGui::PushItemWidth(193);
            ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
            ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);
            ImGui::InputText("##projectLocation", m_ProjectLocation, IM_ARRAYSIZE(m_ProjectLocation));
            ImGui::PopItemFlag();
            ImGui::PopStyleVar();
            ImGui::PopItemWidth();
            ImGui::SameLine();

            if (Button::Render(ICON_FA_FOLDER_OPEN))
            {
                std::string selectedPath = FileSystemDialog::OpenFolderSelector();
                std::copy(selectedPath.begin(), selectedPath.end(), m_ProjectLocation);
            }

            ImGui::Dummy(ImVec2(0.0f, 5.0f));
            ImGui::Separator();
            ImGui::Dummy(ImVec2(0.0f, 5.0f));

            ImGui::Indent(203);
            if (Button::Render("Cancel"))
            {
                m_IsOpened = false;
                ImGui::CloseCurrentPopup();
            }
            ImGui::SameLine();

            std::string projectName(m_ProjectName);
            std::string projectLocation(m_ProjectLocation);

            if (projectName.empty() || projectLocation.empty())
            {
                ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
                ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);
            }

            ImGui::Indent(62);
            if (Button::Render("Confirm"))
            {
                ME_LOG_INFO("Creating project: {0} into directory: {1}", projectName, projectLocation);

                if (Morpheus::FileUtil::CreateFolder(projectLocation, projectName))
                {
                    static std::string pathSep = Morpheus::FileUtil::PathSeparator();
                    std::string projectPath = projectLocation + pathSep + projectName;

                    auto& projectEntity = registry.ctx<Morpheus::ProjectEntity>();
                    projectEntity.uuid = Morpheus::UUID::Generate();
                    projectEntity.path = projectPath;
                    projectEntity.name = projectName;
                    projectEntity.type = Morpheus::ProjectType::TWO_DIMENSIONS;

                    for (auto& scene : projectEntity.scenes)
                    {
                        registry.destroy(scene.id);
                    }
                    projectEntity.scenes.clear();

                    Morpheus::FileUtil::CreateFolder(projectPath, "Scenes");
                    Morpheus::FileUtil::CreateFolder(projectPath, "Assets");
                    Morpheus::GlobalState::Save(registry);

                    m_IsOpened = false;
                    ImGui::CloseCurrentPopup();
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
        return m_IsOpened;
    }

}
