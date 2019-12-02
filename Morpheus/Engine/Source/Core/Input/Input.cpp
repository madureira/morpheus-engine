#include "mepch.h"
#include "Input.h"
#include "Core/Event/EventBus.h"
#include "Core/Event/Types/InputEvent.h"
#include "./Gamepad/Gamepad.h"
#include "./Keyboard/Keyboard.h"

bool g_is_gamepad_connected = false;

namespace Morpheus {

	Input::Input(EventBus* pEventBus, GLFWwindow* pNativeWindow)
		: m_EventBus(pEventBus)
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

		g_is_gamepad_connected = glfwJoystickPresent(GLFW_JOYSTICK_1) == GL_TRUE;
	}

	void Input::Update()
	{
		if (g_is_gamepad_connected)
		{
			InputEvent inputEvent(this->m_Gamepad->GetState());
			this->m_EventBus->Publish(&inputEvent);
		}
		else
		{
			InputEvent inputEvent(this->m_Keyboard->GetState());
			this->m_EventBus->Publish(&inputEvent);
		}
	}

}
