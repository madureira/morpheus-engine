#include "mepch.h"
#include "Input.h"
#include "Gamepad/Gamepad.h"
#include "Keyboard/Keyboard.h"

bool g_is_gamepad_connected = false;

namespace Morpheus {

    Input::Input(entt::registry& registry, GLFWwindow* pNativeWindow)
        : m_Gamepad(new Gamepad())
        , m_Keyboard(new Keyboard(pNativeWindow))
    {
        glfwSetJoystickCallback([](int joystickId, int event) {
            if (event == GLFW_CONNECTED)
            {
                g_is_gamepad_connected = true;
            }
            else if (event == GLFW_DISCONNECTED)
            {
                g_is_gamepad_connected = false;
            }
            });

        g_is_gamepad_connected = (glfwJoystickPresent(GLFW_JOYSTICK_1) == 1);
    }

    Input::~Input()
    {
        delete m_Gamepad;
        delete m_Keyboard;
    }

    void Input::Update(entt::registry& registry) const
    {
        auto& inputEntity = registry.ctx<Morpheus::InputEntity>();
        auto& inputState = registry.get<Morpheus::InputStateComponent>(inputEntity.id);

        if (g_is_gamepad_connected)
        {
            inputState = m_Gamepad->GetState();
        }
        else
        {
            inputState = m_Keyboard->GetState();
        }
    }

}
