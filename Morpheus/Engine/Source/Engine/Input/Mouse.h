#pragma once

#include <GLFW/glfw3.h>
#include "Engine/ECS/ECS.h"

namespace Morpheus {

	class Mouse final
	{
	private:
		GLFWwindow* m_Window;

	public:
		Mouse(entt::registry& registry, GLFWwindow* pNativeWindow);
		~Mouse();

		void Update(entt::registry& registry) const;
	};

}
