#include "Dock.h"

#include "Editor/Containers/Scene/Scene.h"
#include "Editor/Containers/Project/Project.h"
#include "Editor/Containers/Console/Console.h"
#include "Editor/Containers/Hierarchy/Hierarchy.h"
#include "Editor/Containers/Inspector/Inspector.h"

namespace Editor {

    Dock::Dock(entt::registry& registry)
        : m_Scene(new Scene(registry))
        , m_Console(new Console())
        , m_Hierarchy(new Hierarchy())
        , m_Inspector(new Inspector())
        , m_Project(new Project(registry))
    {
    }

    Dock::~Dock()
    {
        delete m_Project;
        delete m_Inspector;
        delete m_Hierarchy;
        delete m_Console;
        delete m_Scene;
    }

    void Dock::Render(entt::registry& registry)
    {
        ImGuiIO& io = ImGui::GetIO();

        static bool dockEnabled = true;
        ImGuiWindowFlags dockFlags = ImGuiWindowFlags_NoMove
            | ImGuiWindowFlags_NoResize
            | ImGuiWindowFlags_NoTitleBar
            | ImGuiWindowFlags_NoCollapse
            | ImGuiWindowFlags_NoScrollbar
            | ImGuiWindowFlags_NoBringToFrontOnFocus;

        ImGuiID dockspaceID = ImGui::GetID("MainDock");

        ImGuiViewport* viewport = ImGui::GetMainViewport();

        ImGui::SetNextWindowPos(ImVec2(viewport->Pos.x, viewport->Pos.y + 66.0f));
        ImGui::SetNextWindowSize(ImVec2(viewport->Size.x, viewport->Size.y - 97.0f));
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);

        ImGui::Begin("Engine", &dockEnabled, dockFlags);
        {
            if (!ImGui::DockBuilderGetNode(dockspaceID))
            {
                ImGui::DockBuilderRemoveNode(dockspaceID);
                ImGui::DockBuilderAddNode(dockspaceID, ImGuiDockNodeFlags_None);

                ImGuiID dock_main_id = dockspaceID;
                ImGuiID dock_left_id = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Left, 0.2f, nullptr, &dock_main_id);
                ImGuiID dock_right_id = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Right, 0.2f, nullptr, &dock_main_id);
                ImGuiID dock_down_id = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Down, 0.2f, nullptr, &dock_main_id);
                ImGuiID dock_down_right_id = ImGui::DockBuilderSplitNode(dock_down_id, ImGuiDir_Right, 0.2f, nullptr, &dock_down_id);

                ImGui::DockBuilderDockWindow("###hierarchy", dock_left_id);
                ImGui::DockBuilderDockWindow("###inspector", dock_right_id);
                ImGui::DockBuilderDockWindow("###project", dock_down_id);
                ImGui::DockBuilderDockWindow("###console", dock_down_right_id);
                ImGui::DockBuilderDockWindow("###scene", dock_main_id);

                ImGui::DockBuilderFinish(dock_main_id);
            }

            ImGuiDockNodeFlags dockspaceFlags = ImGuiDockNodeFlags_None
                | ImGuiDockNodeFlags_NoWindowMenuButton
                | ImGuiDockNodeFlags_NoCloseButton;

            ImGui::DockSpace(dockspaceID, ImVec2(0.0f, 0.0f), dockspaceFlags);

            m_Hierarchy->Render(registry);
            m_Inspector->Render(registry);
            m_Project->Render(registry);
            m_Console->Render(registry);
            m_Scene->Render(registry);
        }
        ImGui::End();
        ImGui::PopStyleVar();
    }

}
