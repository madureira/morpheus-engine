#include "Actionbar.h"
#include "Editor/Widgets/Button/Button.h"

namespace Editor {

    Actionbar::Actionbar()
    {
    }

    void Actionbar::Render(entt::registry &registry)
    {
        auto& projectEntity = registry.ctx<Morpheus::ProjectEntity>();
        bool projectLoaded = projectEntity.path.empty();

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

            Button::Render(nullptr, ICON_FA_ARROWS_ALT, "Move", projectLoaded);
            ImGui::SameLine();

            Button::Render(nullptr, ICON_FA_SYNC_ALT, "Rotate", projectLoaded);
            ImGui::SameLine();

            Button::Render(nullptr, ICON_FA_EXPAND_ARROWS_ALT, "Scale", projectLoaded);
            ImGui::SameLine();

            ImGui::Dummy(ImVec2(io.DisplaySize.x / 2 - 125.f, 0.0f));
            ImGui::SameLine();

            static bool play = false;

            if (Button::Render(nullptr, play ? ICON_FA_PAUSE : ICON_FA_PLAY, play ? "Pause" : "Play", projectLoaded))
            {
                play = !play;
            }

            projectEntity.playing = play;
        }
        ImGui::End();
        ImGui::PopStyleVar();
    }

}
