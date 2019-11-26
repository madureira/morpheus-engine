#include "Window.h"
#include "Config/Settings.h"
#include "Core/Event/EventBus.h"
#include "Core/Event/Types/WindowResizeEvent.h"

namespace Morpheus {

	Window::Window(Settings* pSettings, EventBus* pEventBus)
		: m_Settings(pSettings),
		m_EventCallback(pEventBus),
		m_Window(nullptr)
	{
		this->m_Title = this->m_Settings->GetWindowTitle();
		this->m_Width = this->m_Settings->GetWindowWidth();
		this->m_Height = this->m_Settings->GetWindowHeight();
		this->m_IsFullScreen = this->m_Settings->IsWindowFullscreen();

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

	void Window::Initialize()
	{
		if (!glfwInit())
		{
			std::cout << "Could not initialize GLFW" << std::endl;
			this->Shutdown();
			return;
		}

		const int MONITOR_INDEX = this->m_Settings->IsPrimaryMonitor() ? 0 : 1;
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

		this->m_Window = glfwCreateWindow(this->m_Width, this->m_Height, this->m_Title.c_str(), this->m_IsFullScreen ? pMonitor : nullptr, nullptr);

		if (!this->m_Window)
		{
			std::cout << "Could not create GLFWwindow*" << std::endl;
			this->Shutdown();
			return;
		}

		glfwMakeContextCurrent(this->m_Window);
		glfwSetWindowUserPointer(this->m_Window, this);
		glfwSetWindowAspectRatio(this->m_Window, 16, 9);
		glfwSetWindowPos(this->m_Window, (pMode->width - this->m_Width) / 2, (pMode->height - this->m_Height) / 2);
		glfwSwapInterval(this->m_Settings->IsVSyncOn() ? 1 : 0);
		glfwSetInputMode(this->m_Window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		glfwFocusWindow(this->m_Window);

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

				WindowResizeEvent event(width, height);
				window.m_EventCallback->publish(&event);
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
