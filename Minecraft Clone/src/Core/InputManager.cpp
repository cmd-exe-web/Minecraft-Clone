#include "InputManager.h"

#include <iostream>

namespace MyCraft {

	namespace InputManager {

		bool m_KeyPressedData[GLFW_KEY_LAST];
		bool m_MouseButtonPressedData[GLFW_MOUSE_BUTTON_LAST];
		double m_MouseX = 0.0;
		double m_MouseY = 0.0;
		double m_MouseScrollX = 0.0;
		double m_MouseScrollY = 0.0;

		void Init(GLFWwindow* window) {
			glfwSetKeyCallback(window, InputManager::KeyCallback);
			glfwSetCursorPosCallback(window, InputManager::MousePositionCallback);
			glfwSetMouseButtonCallback(window, InputManager::MouseButtonCallback);
			glfwSetScrollCallback(window, InputManager::MouseScrollCallback);
		}

		bool IsKeyDown(int key)
		{
			if (key >= 0 && key < GLFW_KEY_LAST) {
				return m_KeyPressedData[key];
			}
			return false;
		}

		bool IsMouseButtonDown(int button)
		{
			if (button >= 0 && button < GLFW_MOUSE_BUTTON_LAST) {
				return m_MouseButtonPressedData[button];
			}
			return false;
		}

		std::pair<double, double> GetMousePosition()
		{
			return { m_MouseX, m_MouseY };
		}

		void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			if (key >= 0 && key < GLFW_KEY_LAST) {
				m_KeyPressedData[key] = action != GLFW_RELEASE;
			}
		}

		void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
		{
			if (button >= 0 && button < GLFW_MOUSE_BUTTON_LAST) {
				m_MouseButtonPressedData[button] = action != GLFW_RELEASE;
			}
		}

		void MousePositionCallback(GLFWwindow* window, double xPos, double yPos)
		{
			// printf("%lf : %lf\n", xPos, yPos);
			m_MouseX = xPos;
			m_MouseY = yPos;
		}

		void MouseScrollCallback(GLFWwindow* window, double xOffset, double yOffset)
		{
			m_MouseScrollX = xOffset;
			m_MouseScrollY = yOffset;
		}

	}

}
