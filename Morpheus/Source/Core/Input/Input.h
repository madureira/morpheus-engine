#pragma once

#include <GLFW/glfw3.h>

namespace Morpheus {

	class EventBus;

	class Input
	{
	private:
		GLFWgamepadstate m_GamepadState;
		GLFWwindow* m_NativeWindow;
		EventBus* m_EventBus;

		bool m_IsUpKeyPressed;
		bool m_IsDownKeyPressed;
		bool m_IsLeftKeyPressed;
		bool m_IsRightKeyPressed;
		bool m_IsSpaceKeyPressed;
		bool m_IsAKeyPressed;
		bool m_IsWKeyPressed;
		bool m_IsDKeyPressed;
		bool m_IsSKeyPressed;

	public:
		Input(EventBus* pEventBus, GLFWwindow* pNativeWindow);
		void Update();

	private:
		void UpdateKeyboardState();
		void UpdateGamepadState();
		void EmitEvent();
		void ResetInput();
	};

}
