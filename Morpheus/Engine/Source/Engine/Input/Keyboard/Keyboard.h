#pragma once

#include <GLFW/glfw3.h>
#include "Engine/ECS/ECS.h"

namespace Morpheus {

	struct InputState;

	class Keyboard final
	{
	private:
		GLFWwindow* m_NativeWindow;

	public:
		Keyboard(GLFWwindow* pNativeWindow);

		InputStateComponent GetState() const;
	};

}
