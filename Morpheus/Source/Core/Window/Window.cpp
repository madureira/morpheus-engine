#include "Config/Settings.h"
#include "Core/Event/EventBus.h"
#include "Core/Input/Keyboard/KeyboardEvent.h"
#include "Window.h"

namespace Morpheus {

	Window::Window(const std::string& title, unsigned int width, unsigned int height, bool fullScreen, EventBus* pEventBus, Settings* pSettings)
		: m_Window(nullptr)
	{
		m_Data.Title = title;
		m_Data.Width = width;
		m_Data.Height = height;
		m_Data.FullScreen = fullScreen;
		m_Data.EventCallback = pEventBus;
		this->m_Settings = pSettings;

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

		//int MONITOR_INDEX = 0;
		//int monitors;
		//GLFWmonitor* pMonitor = glfwGetMonitors(&monitors)[MONITOR_INDEX];
		GLFWmonitor* pMonitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* pMode = glfwGetVideoMode(pMonitor);

		glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
		glfwWindowHint(GLFW_DOUBLEBUFFER, GL_TRUE);
		glfwWindowHint(GLFW_RED_BITS, pMode->redBits);
		glfwWindowHint(GLFW_GREEN_BITS, pMode->greenBits);
		glfwWindowHint(GLFW_BLUE_BITS, pMode->blueBits);
		glfwWindowHint(GLFW_REFRESH_RATE, pMode->refreshRate);

		this->m_Window = glfwCreateWindow(this->m_Data.Width, this->m_Data.Height, this->m_Data.Title.c_str(), this->m_Data.FullScreen ? pMonitor : nullptr, nullptr);

		if (!this->m_Window)
		{
			std::cout << "Could not create GLFWwindow*" << std::endl;
			this->Shutdown();
			return;
		}
		glfwMakeContextCurrent(this->m_Window);
		glfwSetWindowPos(this->m_Window, (pMode->width - this->m_Data.Width) / 2, (pMode->height - this->m_Data.Height) / 2);
		glfwSetWindowUserPointer(this->m_Window, &this->m_Data);
		glfwSetWindowAspectRatio(this->m_Window, 16, 9);
		glfwSwapInterval(this->m_Settings->IsVSyncOn() ? 1 : 0);

		glfwSetErrorCallback([](int error, const char* description)
			{
				std::cout << "GLFW ERROR: code " << error << " msg: " << description << std::endl;
			});

		glfwSetWindowSizeCallback(this->m_Window, [](GLFWwindow* window, int width, int height)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				data.Width = width;
				data.Height = height;
			});

		glfwSetFramebufferSizeCallback(this->m_Window, [](GLFWwindow* window, int width, int height)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				data.Width = width;
				data.Height = height;
				glViewport(0, 0, width, height);
			});

		glfwSetKeyCallback(this->m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
					case GLFW_PRESS:
					{
						KeyboardEvent event(KeyboardEvent::Action::PRESS, key);
						data.EventCallback->publish(&event);
						break;
					}
					case GLFW_RELEASE:
					{
						KeyboardEvent event(KeyboardEvent::Action::RELEASE, key);
						data.EventCallback->publish(&event);
						break;
					}
				}
			});

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to initialize OpenGL context" << std::endl;
			this->Shutdown();
			return;
		}

		if (GLAD_GL_VERSION_3_1)
		{
			// Call OpenGL 3.2+ specific code
			std::cout << "OpenGL " << glGetString(GL_VERSION) << std::endl;
		}

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
