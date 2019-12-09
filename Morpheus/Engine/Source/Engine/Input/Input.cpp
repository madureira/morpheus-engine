#include "mepch.h"
#include "Input.h"
#include "./Gamepad/Gamepad.h"
#include "./Keyboard/Keyboard.h"

bool g_is_gamepad_connected = false;

namespace Morpheus {

	Input::Input(entt::registry& registry, GLFWwindow* pNativeWindow)
	{
		this->m_Gamepad = new Gamepad();
		this->m_Keyboard = new Keyboard(pNativeWindow);

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

		g_is_gamepad_connected = glfwJoystickPresent(GLFW_JOYSTICK_1) == 1;
	}

	void Input::Update(entt::registry& registry)
	{
		auto& inputEntity = registry.ctx<Morpheus::InputEntity>();
		auto& inputState = registry.get<Morpheus::InputStateComponent>(inputEntity.id);

		if (g_is_gamepad_connected)
		{

			inputState = this->m_Gamepad->GetState();
		}
		else
		{
			inputState = this->m_Keyboard->GetState();
		}
	}

}
