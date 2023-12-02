#include "InputManager.h"

#include <iostream>

namespace MyCraft {

	namespace InputManager {

		std::unordered_map<int, int> m_KeyStates;
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

		// Checks if a key is tapped
		bool IsKeyDown(int key)
		{
			if (m_KeyStates.find(key) != m_KeyStates.end() && m_KeyStates[key] == GLFW_PRESS) {
				return true;
			}
			return false;

		}
		// Checks if a key is held down
		bool IsKeyPressed(int key)
		{
			if (m_KeyStates.find(key) != m_KeyStates.end() && m_KeyStates[key] != GLFW_RELEASE) {
				return true;
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
			m_KeyStates[key] = action;
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
