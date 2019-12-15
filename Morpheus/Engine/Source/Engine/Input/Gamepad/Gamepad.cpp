#include "mepch.h"
#include "Gamepad.h"

namespace Morpheus {

	InputStateComponent Gamepad::GetState()
	{
		InputStateComponent state;

		if (glfwGetGamepadState(GLFW_JOYSTICK_1, &this->m_GamepadState))
		{
			float x = this->m_GamepadState.axes[GLFW_GAMEPAD_AXIS_LEFT_X];
			float y = this->m_GamepadState.axes[GLFW_GAMEPAD_AXIS_LEFT_Y];

			if (y < -ANALOG_SENSIBILITY)
			{
				state.UP = true;
			}

			if (y > ANALOG_SENSIBILITY)
			{
				state.DOWN = true;
			}

			if (x < -ANALOG_SENSIBILITY)
			{
				state.LEFT = true;
			}

			if (x > ANALOG_SENSIBILITY)
			{
				state.RIGHT = true;
			}

			if (this->m_GamepadState.buttons[GLFW_GAMEPAD_BUTTON_CIRCLE])
			{
				state.S = true;
			}

			if (this->m_GamepadState.buttons[GLFW_GAMEPAD_BUTTON_CROSS])
			{
				state.W = true;
			}

			if (this->m_GamepadState.axes[GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER] > ANALOG_SENSIBILITY)
			{
				state.SPACE = true;
			}

			if (this->m_GamepadState.axes[GLFW_GAMEPAD_AXIS_LEFT_TRIGGER] > ANALOG_SENSIBILITY)
			{
				state.LEFT_CONTROL = true;
			}
		}

		return state;
	}

}
