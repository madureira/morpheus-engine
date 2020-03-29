#include "mepch.h"
#include "Mouse.h"

namespace Morpheus {

	static double s_xPos;
	static double s_yPos;
	static double s_xOffset;
	static double s_yOffset;
	static bool s_leftButton;
	static bool s_middleButton;
	static bool s_rightButton;

	Mouse::Mouse(entt::registry& registry, GLFWwindow* pNativeWindow)
		: m_Window(pNativeWindow)
	{
		glfwSetCursorPosCallback(this->m_Window, [](GLFWwindow* pNativeWindow, double xpos, double ypos)
			{
				s_xPos = xpos;
				s_yPos = ypos;
			});

		glfwSetScrollCallback(this->m_Window, [](GLFWwindow* pNativeWindow, double xoffset, double yoffset)
			{
				s_xOffset = xoffset;
				s_yOffset = yoffset;
			});

		glfwSetMouseButtonCallback(this->m_Window, [](GLFWwindow* pNativeWindow, int button, int action, int mods)
			{
				s_leftButton = (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS);
				s_middleButton = (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_PRESS);
				s_rightButton = (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS);
			});
	}

	Mouse::~Mouse()
	{
	}

	void Mouse::Update(entt::registry& registry) const
	{
		auto& mouseEntity = registry.ctx<Morpheus::MouseEntity>();
		auto& mouseState = registry.get<Morpheus::MouseStateComponent>(mouseEntity.id);

		mouseState.cursorX = s_xPos;
		mouseState.cursorY = s_yPos;
		mouseState.isLeftButtonPressed = s_leftButton;
		mouseState.isMiddleButtonPressed = s_middleButton;
		mouseState.isRightButtonPressed = s_rightButton;
		mouseState.xOffSet = s_xOffset;
		mouseState.yOffSet = s_yOffset;

		//s_leftButton = false;
		//s_middleButton = false;
		//s_rightButton = false;
		s_xOffset = 0;
		s_yOffset = 0;
	}

}
