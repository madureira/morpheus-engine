#include "mepch.h"
#include "Window.h"
#include <glad/glad.h>
#include "Engine/Util/ImageLoader.h"
#include "Engine/Util/FileUtil.h"

namespace Morpheus {

    Window::Window(entt::registry& registry)
        : m_Registry(registry)
    {
        if (!glfwInit())
        {
            ME_LOG_ERROR("GLFW ERROR: {0}", "Could not initialize GLFW");
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
        glfwWindowHint(GLFW_REFRESH_RATE, 60);

        this->m_Window = glfwCreateWindow(this->m_Width, this->m_Height, settingsSize.windowTitle.c_str(), settingsSize.isWindowFullScreen ? pMonitor : nullptr, nullptr);

        if (!this->m_Window)
        {
            ME_LOG_ERROR("GLFW ERROR: {0}", "Could not create GLFWwindow*");
            this->Shutdown();
            return;
        }

        glfwMakeContextCurrent(this->m_Window);
        glfwSetWindowUserPointer(this->m_Window, this);
        glfwSetWindowPos(this->m_Window, (pMode->width - this->m_Width) / 2, (pMode->height - this->m_Height) / 2);
        glfwSetWindowSizeLimits(this->m_Window, 800, 600, 3840, 2160);
        glfwSwapInterval(settingsSize.isVSyncOn ? 1 : 0);
        glfwFocusWindow(this->m_Window);

        Image icon;
        ImageLoader::Load("Assets/icons/window-icon.png", false, icon);

        Image smallIcon;
        ImageLoader::Load("Assets/icons/window-small-icon.png", false, smallIcon);

        GLFWimage images[2];
        images[0] = { icon.width, icon.height, icon.pixels };
        images[1] = { smallIcon.width, smallIcon.height, smallIcon.pixels };

        glfwSetWindowIcon(this->m_Window, 2, images);

        ImageLoader::FreeImage(icon);
        ImageLoader::FreeImage(smallIcon);

        glfwSetErrorCallback([](int error, const char* description)
            {
                ME_LOG_ERROR("GLFW ERROR: code: {0}, message: {1}", error, description);
            });

        glfwSetWindowSizeCallback(this->m_Window, [](GLFWwindow* pNativeWindow, int width, int height)
            {
                Window& window = *(Window*)glfwGetWindowUserPointer(pNativeWindow);
                window.m_Width = width;
                window.m_Height = height;
                glViewport(0, 0, width, height);

                auto& windowEntity = window.m_Registry.ctx<Morpheus::WindowEntity>();
                auto& windowSize = window.m_Registry.get<Morpheus::SizeComponent>(windowEntity.id);
                windowSize.width = (float)width;
                windowSize.height = (float)height;
            });

        glfwSetDropCallback(this->m_Window, [](GLFWwindow* pNativeWindow, int count, const char** paths)
            {
                Window& window = *(Window*)glfwGetWindowUserPointer(pNativeWindow);
                auto& windowEntity = window.m_Registry.ctx<Morpheus::WindowEntity>();
                auto& dropFilesComponent = window.m_Registry.get<Morpheus::DropFilesComponent>(windowEntity.id);

                int validFiles = 0;
                for (int i = 0; i < count; i++)
                {
                    std::string filePath(paths[i]);
                    if (FileUtil::IsFile(filePath)) validFiles++;
                }

                if (count == validFiles)
                {
                    for (int i = 0; i < count; i++)
                    {
                        dropFilesComponent.filesPath.push_back(paths[i]);
                    }
                }
            });

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            ME_LOG_ERROR("OpenGL ERROR: {0}", "Failed to initialize OpenGL context");
            this->Shutdown();
            return;
        }

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    Window::~Window()
    {
        this->Shutdown();
    }

    bool Window::IsOpen() const
    {
        return !glfwWindowShouldClose(this->m_Window);
    }

    void Window::PollEvents() const
    {
        glfwPollEvents();
    }

    void Window::Clear() const
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void Window::SwapBuffers() const
    {
        glfwSwapBuffers(this->m_Window);
    }

    unsigned int Window::GetWidth() const
    {
        return this->m_Width;
    }

    unsigned int Window::GetHeight() const
    {
        return this->m_Height;
    }

    double Window::GetTime() const
    {
        return glfwGetTime();
    }

    void Window::Close() const
    {
        glfwSetWindowShouldClose(this->m_Window, GLFW_TRUE);
    }

    GLFWwindow* Window::GetNativeWindow() const
    {
        return this->m_Window;
    };

    void Window::Shutdown() const
    {
        glfwDestroyWindow(this->m_Window);
        glfwTerminate();
    }

}
