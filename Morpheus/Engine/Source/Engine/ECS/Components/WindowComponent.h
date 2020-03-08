#pragma once

#include <GLFW/glfw3.h>

namespace Morpheus {

	class Window;

	class WindowComponent final
	{
	private:
		Window* m_WindowInstance;

	public:
		WindowComponent(Window* windowInstance);
		void Close() const;
		GLFWwindow* GetNativeWindow() const;
	};

}
