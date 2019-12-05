#include "Actionbar.h"

namespace Editor {

	void Actionbar::Draw()
	{
		ImGuiIO& io = ImGui::GetIO();

		bool showActionBar = true;
		ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoMove
			| ImGuiWindowFlags_NoResize
			| ImGuiWindowFlags_NoTitleBar
			| ImGuiWindowFlags_NoCollapse
			| ImGuiWindowFlags_NoScrollbar
			| ImGuiWindowFlags_NoSavedSettings
			| ImGuiWindowFlags_NoDocking;

		ImGui::SetNextWindowPos(ImVec2(0.0f, 22.0f));
		ImGui::SetNextWindowSize(ImVec2(io.DisplaySize.x, 44.0f));
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::Begin("Actions", &showActionBar, windowFlags);
		{
			ImGui::Dummy(ImVec2(0.0f, 4.0f));
			ImGui::Dummy(ImVec2(2.0f, 0.0f));
			ImGui::SameLine();

			ImGui::Button(ICON_FA_ARROWS_ALT);
			if (ImGui::IsItemHovered())
			{
				ImGui::BeginTooltip();
				ImGui::TextUnformatted("Move");
				ImGui::EndTooltip();
			}
			ImGui::SameLine();

			ImGui::Button(ICON_FA_SYNC_ALT);
			if (ImGui::IsItemHovered())
			{
				ImGui::BeginTooltip();
				ImGui::TextUnformatted("Rotate");
				ImGui::EndTooltip();
			}
			ImGui::SameLine();

			ImGui::Button(ICON_FA_EXPAND_ARROWS_ALT);
			if (ImGui::IsItemHovered())
			{
				ImGui::BeginTooltip();
				ImGui::TextUnformatted("Scale");
				ImGui::EndTooltip();
			}
			ImGui::SameLine();

			ImGui::Dummy(ImVec2(20.0f, 0.0f));
			ImGui::SameLine();

			ImGui::Button(ICON_FA_PLAY);
			if (ImGui::IsItemHovered())
			{
				ImGui::BeginTooltip();
				ImGui::TextUnformatted("Play");
				ImGui::EndTooltip();
			}
			ImGui::SameLine();

			ImGui::Button(ICON_FA_PAUSE);
			if (ImGui::IsItemHovered())
			{
				ImGui::BeginTooltip();
				ImGui::TextUnformatted("Pause");
				ImGui::EndTooltip();
			}
		}
		ImGui::End();
		ImGui::PopStyleVar();
	}

}
