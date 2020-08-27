#include "Hierarchy.h"

namespace Editor {

    void Hierarchy::Render(entt::registry& registry)
    {
        static bool* show = NULL;
        static ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar;

        ImGui::Begin(ICON_FA_STREAM"  Hierarchy###hierarchy", show, windowFlags);
        {
            auto& projectEntity = registry.ctx<Morpheus::ProjectEntity>();

            for (auto& sceneEntity : projectEntity.scenes)
            {
                static ImGuiTreeNodeFlags folderFlags = ImGuiTreeNodeFlags_None;
                std::string folderTitle(ICON_FA_CUBE"  " + sceneEntity.name);
                if (ImGui::TreeNodeEx(folderTitle.c_str(), folderFlags))
                {
                    static ImGuiTreeNodeFlags fileFlags = ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
                    ImGui::TreeNodeEx(ICON_FA_VIDEO"  Camera", fileFlags);
                    ImGui::TreeNodeEx(ICON_FA_LIGHTBULB"    Light", fileFlags);
                    ImGui::TreePop();
                }
            }
        }
        ImGui::End();
    }

}
