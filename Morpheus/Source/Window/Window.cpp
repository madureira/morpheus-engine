#include "Window.h"

namespace Morpheus {

	Window::Window(const std::string& title, unsigned int width, unsigned int height, bool vsync)
		: m_Window(nullptr)
	{
		m_Data.Title = title;
		m_Data.Width = width;
		m_Data.Height = height;
		m_Data.VSync = vsync;

		this->Init();
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

	void Window::SwapBuffers()
	{
		glfwSwapBuffers(this->m_Window);
	}

	void Window::Init()
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

		this->m_Window = glfwCreateWindow(this->m_Data.Width, this->m_Data.Height, this->m_Data.Title.c_str(), nullptr, nullptr);

		if (!this->m_Window)
		{
			std::cout << "Could not create GLFWwindow*" << std::endl;
			this->Shutdown();
			return;
		}

		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* mode = glfwGetVideoMode(monitor);
		glfwSetWindowPos(this->m_Window, (mode->width - this->m_Data.Width) / 2, (mode->height - this->m_Data.Height) / 2);
		glfwMakeContextCurrent(this->m_Window);
		glfwSetWindowUserPointer(this->m_Window, &this->m_Data);

		glfwSetWindowSizeCallback(this->m_Window, [](GLFWwindow* window, int width, int height)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				data.Width = width;
				data.Height = height;
			});

		glfwSetErrorCallback([](int error, const char* description)
			{
				std::cout << "GLFW ERROR: code " << error << " msg: " << description << std::endl;
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
}
