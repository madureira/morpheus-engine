#include "ColorPicker.h"

namespace Editor {

	ColorPicker::ColorPicker(const char* label)
		: m_Label(label)
	{
	}

	void ColorPicker::Draw()
	{
		static bool saved_palette_inited = false;
		static ImVec4 saved_palette[32];
		static ImVec4 backup_color;

		if (!saved_palette_inited)
		{
			for (int n = 0; n < IM_ARRAYSIZE(saved_palette); n++)
			{
				ImGui::ColorConvertHSVtoRGB(n / 31.0f, 0.8f, 0.8f, saved_palette[n].x, saved_palette[n].y, saved_palette[n].z);
			}
		}

		bool open_popup = ImGui::ColorButton("MyColor##3b", this->m_Color, 0);
		ImGui::SameLine();
		open_popup |= ImGui::Button(this->m_Label);

		if (open_popup)
		{
			ImGui::OpenPopup("mypicker");
			backup_color = this->m_Color;
		}

		if (ImGui::BeginPopup("mypicker"))
		{
			ImGui::Text("Color picker");
			ImGui::Separator();
			ImGui::ColorPicker4("##picker", (float*)&this->m_Color, 0 | ImGuiColorEditFlags_NoSidePreview);
			ImGui::SameLine();
			ImGui::BeginGroup();
			ImGui::Text("Current");
			ImGui::ColorButton("##current", this->m_Color, ImGuiColorEditFlags_NoPicker | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_AlphaPreview, ImVec2(60, 40));
			ImGui::Text("Previous");

			if (ImGui::ColorButton("##previous", backup_color, ImGuiColorEditFlags_NoPicker | ImGuiColorEditFlags_AlphaPreview, ImVec2(60, 40)))
			{
				this->m_Color = backup_color;
			}

			ImGui::Separator();
			ImGui::Text("Palette");
			for (int n = 0; n < IM_ARRAYSIZE(saved_palette); n++)
			{
				ImGui::PushID(n);
				if ((n % 8) != 0)
				{
					ImGui::SameLine(0.0f, ImGui::GetStyle().ItemSpacing.y);
				}

				if (ImGui::ColorButton("##palette", saved_palette[n], ImGuiColorEditFlags_NoPicker | ImGuiColorEditFlags_NoTooltip, ImVec2(20, 20)))
				{
					this->m_Color = ImVec4(saved_palette[n].x, saved_palette[n].y, saved_palette[n].z, this->m_Color.w); // Preserve alpha!
				}
				ImGui::PopID();
			}
			ImGui::EndGroup();
			ImGui::EndPopup();
		}
	}

	glm::vec4 ColorPicker::GetSelectedColor()
	{
		return glm::vec4(this->m_Color.x, this->m_Color.y, this->m_Color.z, this->m_Color.w);
	}
}
