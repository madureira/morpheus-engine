#pragma once

#include <string>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include "Engine/ECS/ECS.h"

namespace Morpheus {

    class Window final
    {
    private:
        entt::registry& m_Registry;
        GLFWwindow* m_Window;
        unsigned int m_Width;
        unsigned int m_Height;

    public:
        Window(entt::registry& registry);
        ~Window();

        bool IsOpen() const;
        void PollEvents() const;
        void Clear() const;
        void SwapBuffers() const;
        unsigned int GetWidth() const;
        unsigned int GetHeight() const;
        double GetTime() const;
        void Close() const;
        GLFWwindow* GetNativeWindow() const;

    private:
        void Shutdown() const;
    };

}
