#include "mepch.h"
#include "Keyboard.h"

namespace Morpheus {

    Keyboard::Keyboard(GLFWwindow* pNativeWindow)
        : m_NativeWindow(pNativeWindow)
    {
    }

    InputStateComponent Keyboard::GetState() const
    {
        InputStateComponent state;

        state.UP = glfwGetKey(m_NativeWindow, GLFW_KEY_UP) == GLFW_PRESS;
        state.DOWN = glfwGetKey(m_NativeWindow, GLFW_KEY_DOWN) == GLFW_PRESS;
        state.LEFT = glfwGetKey(m_NativeWindow, GLFW_KEY_LEFT) == GLFW_PRESS;
        state.RIGHT = glfwGetKey(m_NativeWindow, GLFW_KEY_RIGHT) == GLFW_PRESS;
        state.SPACE = glfwGetKey(m_NativeWindow, GLFW_KEY_SPACE) == GLFW_PRESS;
        state.LEFT_CONTROL = glfwGetKey(m_NativeWindow, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS;
        state.LEFT_SHIFT = glfwGetKey(m_NativeWindow, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS;
        state.W = glfwGetKey(m_NativeWindow, GLFW_KEY_W) == GLFW_PRESS;
        state.S = glfwGetKey(m_NativeWindow, GLFW_KEY_S) == GLFW_PRESS;

        return state;
    }

}
