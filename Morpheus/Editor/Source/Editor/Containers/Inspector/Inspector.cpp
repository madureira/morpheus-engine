#include "Inspector.h"
#include "Editor/Widgets/ColorPicker/ColorPicker.h"

namespace Editor {

    void Inspector::Render(entt::registry& registry)
    {
        static bool* show = NULL;
        ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar;
        ImGui::Begin(ICON_FA_INFO_CIRCLE"  Inspector###inspector", show, windowFlags);
        {
            auto& projectEntity = registry.ctx<Morpheus::ProjectEntity>();

            if (!projectEntity.scenes.empty())
            {
                auto& windowEntity = registry.ctx<Morpheus::WindowEntity>();
                auto& color = registry.get<Morpheus::ColorComponent>(windowEntity.id);
                ImVec4 bgColor(color.r, color.g, color.b, color.a);
                ColorPicker::Draw("Background color", bgColor);
                color.r = bgColor.x;
                color.g = bgColor.y;
                color.b = bgColor.z;
                color.a = bgColor.w;
            }
        }
        ImGui::End();
    }

}
