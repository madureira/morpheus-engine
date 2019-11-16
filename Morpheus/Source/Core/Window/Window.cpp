#include "Core/Event/EventBus.h"
#include "Core/Input/Keyboard/KeyboardEvent.h"
#include "Window.h"

namespace Morpheus {

	Window::Window(const std::string& title, unsigned int width, unsigned int height, bool vsync, EventBus* pEventBus)
		: m_Window(nullptr)
	{
		m_Data.Title = title;
		m_Data.Width = width;
		m_Data.Height = height;
		m_Data.VSync = vsync;
		m_Data.EventCallback = pEventBus;

		this->Initialize();
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
		glViewport(0, 0, this->m_Data.Width, this->m_Data.Height);
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

		// Set all the required options for GLFW
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_SAMPLES, 4); // Anti-Alising
		glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
		glfwSwapInterval(this->m_Data.VSync ? 1 : 0);

		GLFWmonitor* pMonitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* pMode = glfwGetVideoMode(pMonitor);

#ifdef DEBUG
		this->m_Window = glfwCreateWindow(this->m_Data.Width, this->m_Data.Height, this->m_Data.Title.c_str(), nullptr, nullptr);
#else
		//this->m_Data.Width = pMode->width;
		//this->m_Data.Height = pMode->height;
		this->m_Window = glfwCreateWindow(this->m_Data.Width, this->m_Data.Height, this->m_Data.Title.c_str(), pMonitor, nullptr);
#endif // DEBUG


		if (!this->m_Window)
		{
			std::cout << "Could not create GLFWwindow*" << std::endl;
			this->Shutdown();
			return;
		}

		glfwWindowHint(GLFW_RED_BITS, pMode->redBits);
		glfwWindowHint(GLFW_GREEN_BITS, pMode->greenBits);
		glfwWindowHint(GLFW_BLUE_BITS, pMode->blueBits);
		glfwWindowHint(GLFW_REFRESH_RATE, pMode->refreshRate);

		glfwSetWindowPos(this->m_Window, (pMode->width - this->m_Data.Width) / 2, (pMode->height - this->m_Data.Height) / 2);
		glfwMakeContextCurrent(this->m_Window);
		glfwSetWindowUserPointer(this->m_Window, &this->m_Data);

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

		// Set OpenGL options
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_FRONT_FACE);
		glFrontFace(GL_CW);

		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		glViewport(0, 0, this->m_Data.Width, this->m_Data.Height);

		std::cout << "OpenGL " << glGetString(GL_VERSION) << std::endl;
	}

	void Window::Shutdown()
	{
		glfwDestroyWindow(this->m_Window);
		glfwTerminate();
	}

	Window::~Window()
	{
		this->Shutdown();
	}
}
