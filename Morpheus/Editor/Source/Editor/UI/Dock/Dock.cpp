#include "Dock.h"

#include "Editor/UI/Viewport/Viewport.h"
#include "Editor/UI/Project/Project.h"
#include "Editor/UI/Console/Console.h"
#include "Editor/UI/Hierarchy/Hierarchy.h"
#include "Editor/UI/Inspector/Inspector.h"

namespace Editor {

	Dock::Dock(entt::registry& registry)
	{
		this->m_Viewport = new Viewport(registry);
		this->m_Console = new Console();
		this->m_Hierarchy = new Hierarchy(registry);
		this->m_Inspector = new Inspector(registry);
		this->m_Project = new Project(registry);
	}

	Dock::~Dock()
	{
		delete this->m_Viewport;
		delete this->m_Console;
		delete this->m_Project;
		delete this->m_Inspector;
		delete this->m_Hierarchy;
	}

	void Dock::Draw(entt::registry& registry)
	{
		ImGuiIO& io = ImGui::GetIO();

		bool dockEnabled = true;
		ImGuiWindowFlags dockFlags = ImGuiWindowFlags_NoMove
			| ImGuiWindowFlags_NoResize
			| ImGuiWindowFlags_NoTitleBar
			| ImGuiWindowFlags_NoCollapse
			| ImGuiWindowFlags_NoScrollbar;

		ImGuiID dockspaceID = ImGui::GetID("MainDock");

		ImGui::SetNextWindowPos(ImVec2(0.0f, 66.0f));
		ImGui::SetNextWindowSize(ImVec2(io.DisplaySize.x, io.DisplaySize.y - 66.0f));
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);

		ImGui::Begin("Engine", &dockEnabled, dockFlags);
		{
			if (!ImGui::DockBuilderGetNode(dockspaceID)) {
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
			
			this->m_Hierarchy->Draw(registry);
			this->m_Inspector->Draw(registry);
			this->m_Project->Draw(registry);
			this->m_Console->Draw(registry);
			this->m_Viewport->Draw(registry);
		}
		ImGui::End();
		ImGui::PopStyleVar();
	}

}
