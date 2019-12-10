#include "mepch.h"
#include "Window.h"
#include <glad/glad.h>

namespace Morpheus {

	Window::Window(entt::registry& registry)
		: m_Registry(registry),
		m_Window(nullptr)
	{
		this->Initialize();
	}

	Window::~Window()
	{
		this->Shutdown();
	}

	bool Window::IsOpen()
	{
		return !glfwWindowShouldClose(this->m_Window);
	}

	void Window::PollEvents()
	{
		glfwPollEvents();
	}

	void Window::Clear()
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void Window::SwapBuffers()
	{
		glfwSwapBuffers(this->m_Window);
	}

	double Window::GetTime()
	{
		return glfwGetTime();
	}

	void Window::Close()
	{
		glfwSetWindowShouldClose(this->m_Window, GLFW_TRUE);
	}

	void Window::Initialize()
	{
		if (!glfwInit())
		{
			std::cout << "Could not initialize GLFW" << std::endl;
			this->Shutdown();
			return;
		}

		auto& settingsEntity = this->m_Registry.ctx<SettingsEntity>();
		auto& settingsSize = this->m_Registry.get<SettingsComponent>(settingsEntity.id);

		this->m_Width = settingsSize.windowWidth;
		this->m_Height = settingsSize.windowHeight;

		const int MONITOR_INDEX = settingsSize.isPrimaryMonitor ? 0 : 1;
		int monitors;
		GLFWmonitor* pMonitor = glfwGetMonitors(&monitors)[MONITOR_INDEX];
		const GLFWvidmode* pMode = glfwGetVideoMode(pMonitor);

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // To make MacOS happy;
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
		glfwWindowHint(GLFW_DOUBLEBUFFER, GL_TRUE);
		glfwWindowHint(GLFW_RED_BITS, pMode->redBits);
		glfwWindowHint(GLFW_GREEN_BITS, pMode->greenBits);
		glfwWindowHint(GLFW_BLUE_BITS, pMode->blueBits);
		glfwWindowHint(GLFW_REFRESH_RATE, pMode->refreshRate);

		this->m_Window = glfwCreateWindow(this->m_Width, this->m_Height, settingsSize.windowTitle.c_str(), settingsSize.isWindowFullScreen ? pMonitor : nullptr, nullptr);

		if (!this->m_Window)
		{
			std::cout << "Could not create GLFWwindow*" << std::endl;
			this->Shutdown();
			return;
		}

		glfwMakeContextCurrent(this->m_Window);
		glfwSetWindowUserPointer(this->m_Window, this);
		glfwSetWindowPos(this->m_Window, (pMode->width - this->m_Width) / 2, (pMode->height - this->m_Height) / 2);
		glfwSetWindowSizeLimits(this->m_Window, 800, 600, 3840, 2160);
		glfwSwapInterval(settingsSize.isVSyncOn ? 1 : 0);
		glfwFocusWindow(this->m_Window);
		//glfwSetInputMode(this->m_Window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		//glfwSetWindowAspectRatio(this->m_Window, 16, 9);

		glfwSetErrorCallback([](int error, const char* description)
			{
				std::cout << "GLFW ERROR: code " << error << " msg: " << description << std::endl;
			});

		glfwSetWindowSizeCallback(this->m_Window, [](GLFWwindow* pNativeWindow, int width, int height)
			{
				Window& window = *(Window*)glfwGetWindowUserPointer(pNativeWindow);
				window.m_Width = width;
				window.m_Height = height;
				glViewport(0, 0, width, height);

				auto& windowEntity = window.m_Registry.ctx<Morpheus::WindowEntity>();
				auto& windowSize = window.m_Registry.get<Morpheus::SizeComponent>(windowEntity.id);
				windowSize.width = (float) width;
				windowSize.height = (float) height;
			});

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to initialize OpenGL context" << std::endl;
			this->Shutdown();
			return;
		}

		std::cout << "OpenGL " << glGetString(GL_VERSION) << std::endl;

		// Set OpenGL options
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void Window::Shutdown()
	{
		glfwDestroyWindow(this->m_Window);
		glfwTerminate();
	}

}
