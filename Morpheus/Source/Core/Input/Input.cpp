#include <iostream>
#include "Input.h"
#include "Core/Event/EventBus.h"
#include "Core/Event/Types/InputEvent.h"

bool g_is_gamepad_connected = false;

namespace Morpheus {

	Input::Input(EventBus* pEventBus, GLFWwindow* pNativeWindow)
		: m_EventBus(pEventBus),
		m_NativeWindow(pNativeWindow)
	{
		glfwSetJoystickCallback([](int jid, int event) {
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
		this->ResetInput();
		if (g_is_gamepad_connected)
		{
			this->UpdateGamepadState();
		}
		else
		{
			this->UpdateKeyboardState();
		}
		this->EmitEvent();
	}

	void Input::UpdateKeyboardState()
	{
		this->m_IsUpKeyPressed = glfwGetKey(this->m_NativeWindow, GLFW_KEY_UP) == GLFW_PRESS;
		this->m_IsDownKeyPressed = glfwGetKey(this->m_NativeWindow, GLFW_KEY_DOWN) == GLFW_PRESS;
		this->m_IsLeftKeyPressed = glfwGetKey(this->m_NativeWindow, GLFW_KEY_LEFT) == GLFW_PRESS;
		this->m_IsRightKeyPressed = glfwGetKey(this->m_NativeWindow, GLFW_KEY_RIGHT) == GLFW_PRESS;
	}

	void Input::UpdateGamepadState()
	{
		if (glfwGetGamepadState(GLFW_JOYSTICK_1, &this->m_GamepadState))
		{
			if (this->m_GamepadState.buttons[GLFW_GAMEPAD_BUTTON_A])
			{
				std::cout << "BUTTON_A" << std::endl;
			}

			float x = this->m_GamepadState.axes[GLFW_GAMEPAD_AXIS_LEFT_X];
			float y = this->m_GamepadState.axes[GLFW_GAMEPAD_AXIS_LEFT_Y];

			float sensibility = 0.25f;

			if (y < -sensibility)
			{
				this->m_IsUpKeyPressed = true;
			}

			if (y > sensibility)
			{
				this->m_IsDownKeyPressed = true;
			}

			if (x < -sensibility)
			{
				this->m_IsLeftKeyPressed = true;
			}

			if (x > sensibility)
			{
				this->m_IsRightKeyPressed = true;
			}
		}
	}

	void Input::EmitEvent()
	{
		InputState state;
		state.UP = this->m_IsUpKeyPressed;
		state.DOWN = this->m_IsDownKeyPressed;
		state.LEFT = this->m_IsLeftKeyPressed;
		state.RIGHT = this->m_IsRightKeyPressed;

		InputEvent inputEvent(state);
		this->m_EventBus->publish(&inputEvent);
	}

	void Input::ResetInput()
	{
		this->m_IsUpKeyPressed = false;
		this->m_IsDownKeyPressed = false;
		this->m_IsLeftKeyPressed = false;
		this->m_IsRightKeyPressed = false;
		this->m_IsSpaceKeyPressed = false;
		this->m_IsAKeyPressed = false;
		this->m_IsWKeyPressed = false;
		this->m_IsDKeyPressed = false;
		this->m_IsSKeyPressed = false;
	}

}
