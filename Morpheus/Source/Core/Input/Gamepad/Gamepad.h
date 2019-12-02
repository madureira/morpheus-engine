#pragma once

#include <GLFW/glfw3.h>

namespace Morpheus {

	constexpr float ANALOG_SENSIBILITY = 0.25f;

	class InputState;

	class Gamepad
	{
	private:
		GLFWgamepadstate m_GamepadState;

	public:
		InputState GetState();
	};

}
