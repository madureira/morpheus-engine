#include "Button.h"

#include <string>
#include <imgui.h>
#include <imgui_internal.h>
#include "Vendors/IconsFontAwesome5/IconsFontAwesome5.h"

namespace Editor {

    bool Button::Render(const char* label, const char* icon, const char* tooltip, bool disabled)
    {
        return Button::RenderButton(label, icon, tooltip, disabled);
    }

    bool Button::RenderButton(const char* label, const char* icon, const char* tooltip, bool disabled)
    {
        bool clicked = false;

        if (disabled)
        {
            ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
            ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);
        }

        std::string textButton = "";

        if (icon && !label)
        {
            textButton = icon;
        }
        else if (!icon && label)
        {
            textButton = label;
        }
        else if (icon && label)
        {
            textButton.append(icon).append(" ").append(label);
        }
        else
        {
            textButton = "no label";
        }

        if (ImGui::Button(textButton.c_str()))
        {
            clicked = true;
        }

        if (disabled)
        {
            ImGui::PopItemFlag();
            ImGui::PopStyleVar();
        }

        if (!disabled && tooltip && ImGui::IsItemHovered())
        {
            ImGui::BeginTooltip();
            ImGui::TextUnformatted(tooltip);
            ImGui::EndTooltip();
        }

        return clicked;
    }

}
