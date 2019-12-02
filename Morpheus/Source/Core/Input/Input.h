#pragma once

#include <GLFW/glfw3.h>

namespace Morpheus {

	class EventBus;
	class Gamepad;
	class Keyboard;

	class Input
	{
	private:
		EventBus* m_EventBus;
		Gamepad* m_Gamepad;
		Keyboard* m_Keyboard;

	public:
		Input(EventBus* pEventBus, GLFWwindow* pNativeWindow);
		void Update();
	};

}
