#include "mepch.h"
#include "WindowComponent.h"
#include "Engine/Window/Window.h"

namespace Morpheus {

    WindowComponent::WindowComponent(Window* windowInstance)
        : m_WindowInstance(windowInstance)
    {
    }

    void WindowComponent::Close() const
    {
        return m_WindowInstance->Close();
    }

    GLFWwindow* WindowComponent::GetNativeWindow() const
    {
        return m_WindowInstance->GetNativeWindow();
    }

}
