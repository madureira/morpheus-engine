#include "Actionbar.h"

namespace Editor {

	Actionbar::Actionbar()
		: m_IsPlaying(false)
		, m_FrameRate(0)
	{
	}

	void Actionbar::UpdateFrameRate(int frameRate)
	{
		this->m_FrameRate = frameRate;
	}

	void Actionbar::Draw(entt::registry& registry)
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

			ImGui::Dummy(ImVec2(io.DisplaySize.x / 2 - 140.f, 0.0f));
			ImGui::SameLine();

			static bool play = false;

			if (this->DrawButton(ICON_FA_PLAY, "Play", this->m_IsPlaying))
			{
				play = true;
			}
			ImGui::SameLine();

			if (this->DrawButton(ICON_FA_PAUSE, "Pause", !this->m_IsPlaying))
			{
				play = false;
			}
			ImGui::SameLine();

			this->m_IsPlaying = play;

			ImGui::Dummy(ImVec2(io.DisplaySize.x / 2 - 110, 0.0f));
			ImGui::SameLine();
			ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.4f, 0.9f, 0.2f, 1.0f));
			ImGui::Text("FPS: %d", this->m_FrameRate);
			ImGui::PopStyleColor();
		}
		ImGui::End();
		ImGui::PopStyleVar();
	}

	bool Actionbar::DrawButton(const char* icon, const char* label, bool disabled)
	{
		bool clicked = false;

		if (disabled)
		{
			ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
			ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);
		}

		if (ImGui::Button(icon))
		{
			clicked = true;
		}

		if (disabled)
		{
			ImGui::PopItemFlag();
			ImGui::PopStyleVar();
		}

		if (!disabled && ImGui::IsItemHovered())
		{
			ImGui::BeginTooltip();
			ImGui::TextUnformatted(label);
			ImGui::EndTooltip();
		}

		return clicked;
	}

}
