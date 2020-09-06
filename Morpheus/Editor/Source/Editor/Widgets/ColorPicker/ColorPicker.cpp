#include "ColorPicker.h"
#include "Vendors/IconsFontAwesome5/IconsFontAwesome5.h"
#include "Editor/Widgets/Button/Button.h"

namespace Editor {

    void ColorPicker::Draw(const char* label, ImVec4& color)
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

        bool open_popup = ImGui::ColorButton("Current color##3b", color, ImGuiColorEditFlags_AlphaPreview);
        ImGui::SameLine();

        open_popup |= Button::Render(label);

        if (open_popup)
        {
            ImGui::OpenPopup("mypicker");
            backup_color = color;
        }

        if (ImGui::BeginPopup("mypicker"))
        {
            ImGui::Text(ICON_FA_PALETTE"  Color picker");
            ImGui::Separator();
            ImGui::ColorPicker4("##picker", (float*)&color, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoSmallPreview);
            ImGui::SameLine();
            ImGui::BeginGroup();
            ImGui::Text("Current");
            ImGui::ColorButton("##current", color, ImGuiColorEditFlags_NoPicker | ImGuiColorEditFlags_AlphaPreview, ImVec2(60, 40));
            ImGui::Text("Previous");

            if (ImGui::ColorButton("##previous", backup_color, ImGuiColorEditFlags_NoPicker | ImGuiColorEditFlags_AlphaPreview, ImVec2(60, 40)))
            {
                color = backup_color;
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
                    color = ImVec4(saved_palette[n].x, saved_palette[n].y, saved_palette[n].z, color.w);
                }
                ImGui::PopID();
            }
            ImGui::EndGroup();
            ImGui::EndPopup();
        }
    }

}
