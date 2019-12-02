#pragma once

#include <GLFW/glfw3.h>

namespace Morpheus {

	class InputState;

	class Keyboard
	{
	private:
		GLFWwindow* m_NativeWindow;

	public:
		Keyboard(GLFWwindow* pNativeWindow);
		InputState GetState();
	};

}
