#pragma once

#include <string>
#include <GLFW/glfw3.h>
#include "Engine/ECS/ECS.h"

namespace Morpheus {

	class Window
	{
	private:
		entt::registry& m_Registry;
		GLFWwindow* m_Window;
		unsigned int m_Width;
		unsigned int m_Height;

	public:
		Window(entt::registry& registry);
		~Window();

		bool IsOpen();
		void PollEvents();
		void Clear();
		void SwapBuffers();
		inline unsigned int GetWidth() const { return this->m_Width; }
		inline unsigned int GetHeight() const { return this->m_Height; }
		inline GLFWwindow* GetNativeWindow() const { return this->m_Window; };
		double GetTime();
		void Close();

	private:
		void Initialize();
		void Shutdown();
	};

}
