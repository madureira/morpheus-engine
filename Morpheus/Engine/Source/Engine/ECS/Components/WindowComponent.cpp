#include "mepch.h"
#include "WindowComponent.h"
#include "Engine/Window/Window.h"

namespace Morpheus {

	WindowComponent::WindowComponent(Window* windowInstance)
		: m_WindowInstance(windowInstance)
	{
	}

	void WindowComponent::Close()
	{
		return this->m_WindowInstance->Close();
	}

	GLFWwindow* WindowComponent::GetNativeWindow()
	{
		return this->m_WindowInstance->GetNativeWindow();
	}

}
