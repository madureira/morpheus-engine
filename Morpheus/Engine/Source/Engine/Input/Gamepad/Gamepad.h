#pragma once

#include <GLFW/glfw3.h>
#include "Engine/ECS/ECS.h"

namespace Morpheus {

    constexpr float ANALOG_SENSIBILITY = 0.25f;

    class Gamepad final
    {
    private:
        GLFWgamepadstate m_GamepadState;

    public:
        InputStateComponent GetState();
    };

}
