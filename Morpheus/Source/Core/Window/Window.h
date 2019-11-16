#pragma once

#include <iostream>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Morpheus {

	class EventBus;

	class Window
	{
	private:
		struct WindowData
		{
			std::string Title = "Morpheus";
			unsigned int Width = 800;
			unsigned int Height = 600;
			bool VSync = true;
			bool FullScreen = false;
			EventBus* EventCallback;
		};

		GLFWwindow* m_Window;
		WindowData m_Data;

	public:
		Window(const std::string& title, unsigned int width, unsigned int height, bool fullScreen, bool vsync, EventBus* pEventBus);
		~Window();

		bool IsOpen();
		void PollEvents();
		void Clear();
		void SwapBuffers();
		inline unsigned int GetWidth() const { return m_Data.Width; }
		inline unsigned int GetHeight() const { return m_Data.Height; }
		inline double GetTime() { return glfwGetTime(); }
		inline const GLFWwindow* GetNativeWindow() const { return m_Window; };

	private:
		void Initialize();
		void Shutdown();
	};

}
