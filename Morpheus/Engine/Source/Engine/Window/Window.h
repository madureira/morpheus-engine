#pragma once

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Morpheus {

	class Settings;
	class EventBus;

	class Window
	{
	private:
		Settings* m_Settings;
		EventBus* m_EventCallback;
		GLFWwindow* m_Window;
		std::string m_Title;
		unsigned int m_Width;
		unsigned int m_Height;
		bool m_IsFullScreen;

	public:
		Window(Settings* pSettings, EventBus* pEventBus);
		~Window();

		bool IsOpen();
		void PollEvents();
		void Clear();
		void SwapBuffers();
		inline unsigned int GetWidth() const { return this->m_Width; }
		inline unsigned int GetHeight() const { return this->m_Height; }
		inline GLFWwindow* GetNativeWindow() const { return this->m_Window; };
		inline double GetTime() { return glfwGetTime(); }

	private:
		void Initialize();
		void Shutdown();
	};

}
