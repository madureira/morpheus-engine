#pragma once

#include <string>
#include <GLFW/glfw3.h>
#include "Engine/ECS/ECS.h"

namespace Morpheus {

	class Settings;

	class Window
	{
	private:
		Settings* m_Settings;
		GLFWwindow* m_Window;
		std::string m_Title;
		unsigned int m_Width;
		unsigned int m_Height;
		bool m_IsFullScreen;
		entt::registry& m_Registry;

	public:
		Window(entt::registry& registry, Settings* pSettings);
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
