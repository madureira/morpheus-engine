#include "Button.h"

#include <string>
#include <imgui.h>
#include <imgui_internal.h>
#include "Vendors/IconsFontAwesome5/IconsFontAwesome5.h"

namespace Editor {

    bool Button::Render(const char* icon, const char* label, const char* tooltip, bool disabled)
    {
        return Button::RenderButton(icon, label, tooltip, disabled);
    }

    bool Button::RenderButton(const char* icon, const char* label, const char* tooltip, bool disabled)
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
            textButton = "no text";
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

        if (!disabled && ImGui::IsItemHovered())
        {
            ImGui::BeginTooltip();
            ImGui::TextUnformatted(tooltip);
            ImGui::EndTooltip();
        }

        return clicked;
    }

}
