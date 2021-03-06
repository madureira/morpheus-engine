#pragma once

#include <imgui.h>

namespace Editor {

    class InputUtil final
    {
    public:
        // Avoid special chars
        // Only permit a-z, A-Z, 0-9, -, _
        static int SanitizeCallback(ImGuiInputTextCallbackData* data)
        {
            return ((data->EventChar >= 97 && data->EventChar <= 122) // a-z
                || (data->EventChar >= 65 && data->EventChar <= 90) // A-Z
                || (data->EventChar >= 48 && data->EventChar <= 57) // 0-9
                || (data->EventChar == 95 || data->EventChar == 45) // - or _
                ) ? 0 : 1;
        }
    };

}
