#include "Actionbar.h"
#include "Editor/Widgets/Button/Button.h"

namespace Editor {

    Actionbar::Actionbar()
        : m_IsPlaying(false)
    {
    }

    void Actionbar::Render(entt::registry &registry)
    {
        auto& projectEntity = registry.ctx<Morpheus::ProjectEntity>();

        ImGuiIO &io = ImGui::GetIO();

        static bool showActionBar = true;
        ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoMove
            | ImGuiWindowFlags_NoResize
            | ImGuiWindowFlags_NoTitleBar
            | ImGuiWindowFlags_NoCollapse
            | ImGuiWindowFlags_NoScrollbar
            | ImGuiWindowFlags_NoSavedSettings
            | ImGuiWindowFlags_NoDocking;

        ImVec2 mainViewportPos = ImGui::GetMainViewport()->Pos;
        ImGui::SetNextWindowPos(ImVec2(mainViewportPos.x, mainViewportPos.y + 22));

        ImGui::SetNextWindowSize(ImVec2(io.DisplaySize.x, 44.0f));
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::Begin("Actions", &showActionBar, windowFlags);
        {
            ImGui::Dummy(ImVec2(0.0f, 4.0f));
            ImGui::Dummy(ImVec2(2.0f, 0.0f));
            ImGui::SameLine();

            Button::Render(nullptr, ICON_FA_ARROWS_ALT, "Move");
            ImGui::SameLine();

            Button::Render(nullptr, ICON_FA_SYNC_ALT, "Rotate");
            ImGui::SameLine();

            Button::Render(nullptr, ICON_FA_EXPAND_ARROWS_ALT, "Scale");
            ImGui::SameLine();

            ImGui::Dummy(ImVec2(io.DisplaySize.x / 2 - 140.f, 0.0f));
            ImGui::SameLine();

            static bool play = false;

            if (Button::Render(nullptr, ICON_FA_PLAY, "Play", this->m_IsPlaying))
            {
                play = true;
            }
            ImGui::SameLine();

            if (Button::Render(nullptr, ICON_FA_PAUSE, "Pause", !this->m_IsPlaying))
            {
                play = false;
            }
            ImGui::SameLine();

            this->m_IsPlaying = play;

            projectEntity.playing = this->m_IsPlaying;
        }
        ImGui::End();
        ImGui::PopStyleVar();
    }

}
