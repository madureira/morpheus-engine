#include "Dock.h"

namespace Editor {

	void Dock::Draw()
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
				ImGuiID dock_right_id = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Right, 0.2f, nullptr, &dock_main_id);
				ImGuiID dock_left_id = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Left, 0.2f, nullptr, &dock_main_id);
				ImGuiID dock_down_id = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Down, 0.2f, nullptr, &dock_main_id);
				ImGuiID dock_down_right_id = ImGui::DockBuilderSplitNode(dock_down_id, ImGuiDir_Right, 0.2f, nullptr, &dock_down_id);

				ImGui::DockBuilderDockWindow("Inspector", dock_right_id);
				ImGui::DockBuilderDockWindow("Hierarchy", dock_left_id);
				ImGui::DockBuilderDockWindow("Project", dock_down_id);
				ImGui::DockBuilderDockWindow("Console", dock_down_right_id);
				ImGui::DockBuilderDockWindow("Scene", dock_main_id);

				ImGui::DockBuilderFinish(dock_main_id);
			}

			ImGuiDockNodeFlags dockspaceFlags = ImGuiDockNodeFlags_None | ImGuiDockNodeFlags_NoWindowMenuButton | ImGuiDockNodeFlags_NoCloseButton;
			ImGui::DockSpace(dockspaceID, ImVec2(0.0f, 0.0f), dockspaceFlags);

			ImGui::Begin("Inspector");
			ImGui::End();

			ImGui::Begin("Hierarchy");
			ImGui::End();

			ImGui::Begin("Project");
			ImGui::End();

			ImGui::Begin("Console");
			ImGui::End();

			ImGui::Begin("Scene");
			ImGui::End();
		}
		ImGui::End();
		ImGui::PopStyleVar();
	}

}
