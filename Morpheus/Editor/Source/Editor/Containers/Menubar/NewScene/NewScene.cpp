#include "NewScene.h"
#include <Engine/State/GlobalState.h>
#include <Engine/Util/UUID.h>
#include "Editor/Util/InputUtil.h"

namespace Editor {

    void NewScene::Render(entt::registry& registry)
    {
        ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoMove
            | ImGuiWindowFlags_NoResize
            | ImGuiWindowFlags_NoCollapse
            | ImGuiWindowFlags_NoScrollbar;

        float modalWidth = 350.0f;
        float modalHeight = 130.0f;

        ImGuiViewport* viewport = ImGui::GetMainViewport();
        float posX = (viewport->Pos.x + ((viewport->Size.x - modalWidth) / 2));
        float posY = (viewport->Pos.y + ((viewport->Size.y - modalHeight) / 2));

        ImGui::SetNextWindowPos(ImVec2(posX, posY));
        ImGui::SetNextWindowSize(ImVec2(modalWidth, modalHeight));

        ImGui::OpenPopup("###new_scene");
        if (ImGui::BeginPopupModal(ICON_FA_CUBE"  New###new_scene", NULL, windowFlags))
        {
            ImGui::Dummy(ImVec2(5.0f, 0.0f));
            ImGui::SameLine();
            ImGui::Text("Create a new Scene");
            ImGui::Separator();

            ImGui::Dummy(ImVec2(0.0f, 5.0f));
            ImGui::Dummy(ImVec2(5.0f, 0.0f));
            ImGui::SameLine();
            ImGui::Text("Scene name:"); ImGui::SameLine();
            ImGuiInputTextFlags flags = ImGuiInputTextFlags_CallbackCharFilter;
            ImGui::PushItemWidth(230);
            ImGui::InputText("##sceneName", m_SceneName, IM_ARRAYSIZE(m_SceneName), flags, InputUtil::SanitizeCallback);
            ImGui::PopItemWidth();

            ImGui::Dummy(ImVec2(0.0f, 5.0f));
            ImGui::Separator();
            ImGui::Dummy(ImVec2(0.0f, 5.0f));

            ImGui::Indent(203);
            if (ImGui::Button("Cancel"))
            {
                m_IsOpened = false;
                ImGui::CloseCurrentPopup();
            }
            ImGui::SameLine();

            std::string sceneName(m_SceneName);

            if (sceneName.empty())
            {
                ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
                ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);
            }

            ImGui::Indent(62);
            if (ImGui::Button("Confirm"))
            {
                Morpheus::SceneEntity sceneEntity{ registry.create() };
                sceneEntity.uuid = Morpheus::UUID::Generate();
                sceneEntity.name = sceneName;
                registry.set<Morpheus::SceneEntity>(sceneEntity);

                auto& projectEntity = registry.ctx<Morpheus::ProjectEntity>();
                projectEntity.scenes.push_back(sceneEntity);

                Morpheus::GlobalState::Save(registry);

                m_IsOpened = false;
                ImGui::CloseCurrentPopup();
            }

            if (sceneName.empty())
            {
                ImGui::PopItemFlag();
                ImGui::PopStyleVar();
            }
            ImGui::EndPopup();
        }
    }

    bool NewScene::IsOpened() const
    {
        return m_IsOpened;
    }

}
