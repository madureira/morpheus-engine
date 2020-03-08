#pragma once

#include <GLFW/glfw3.h>
#include "Engine/ECS/ECS.h"

namespace Morpheus {

	class Gamepad;
	class Keyboard;

	class Input final
	{
	private:
		Gamepad* m_Gamepad;
		Keyboard* m_Keyboard;

	public:
		Input(entt::registry& registry, GLFWwindow* pNativeWindow);
		~Input();

		void Update(entt::registry& registry) const;
	};

}
