#pragma once

namespace Editor {

    class Button final
    {
    public:
        static bool Render(const char* label, const char* icon = nullptr, const char* tooltip = nullptr, bool disabled = false);

    private:
        static bool RenderButton(const char* label, const char* icon, const char* tooltip, bool disabled = false) ;
    };

}
