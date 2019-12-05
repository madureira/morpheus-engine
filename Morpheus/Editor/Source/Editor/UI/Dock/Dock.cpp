#include "Dock.h"

namespace Editor {

	Dock::Dock(Morpheus::Settings* pSettings)
	{
		this->m_ColorPicker = new ColorPicker("Background color");
		this->m_Viewport = new Viewport(pSettings);
		this->m_Hierarchy = new Hierarchy();
		this->m_Project = new Project();
		this->m_Console = new Console();
	}

	Dock::~Dock()
	{
		delete this->m_Viewport;
		delete this->m_Hierarchy;
		delete this->m_Project;
		delete this->m_Console;
		delete this->m_ColorPicker;
	}

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

				ImGui::DockBuilderDockWindow("###inspector", dock_right_id);
				ImGui::DockBuilderDockWindow("###hierarchy", dock_left_id);
				ImGui::DockBuilderDockWindow("###project", dock_down_id);
				ImGui::DockBuilderDockWindow("###console", dock_down_right_id);
				ImGui::DockBuilderDockWindow("###scene", dock_main_id);

				ImGui::DockBuilderFinish(dock_main_id);
			}

			ImGuiDockNodeFlags dockspaceFlags = ImGuiDockNodeFlags_None
				| ImGuiDockNodeFlags_NoWindowMenuButton
				| ImGuiDockNodeFlags_NoCloseButton;

			ImGui::DockSpace(dockspaceID, ImVec2(0.0f, 0.0f), dockspaceFlags);

			ImGui::Begin(ICON_FA_LIST" Inspector###inspector");
			{
				this->m_ColorPicker->Draw();
			}
			ImGui::End();

			this->m_Hierarchy->Draw();
			this->m_Project->Draw();
			this->m_Console->Draw();

			this->m_Viewport->ChangeColor(this->m_ColorPicker->GetSelectedColor());
			this->m_Viewport->Draw();
		}
		ImGui::End();
		ImGui::PopStyleVar();
	}

}
