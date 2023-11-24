#pragma once

#include <GLFW/glfw3.h>

#include <utility>

namespace MyCraft {

	namespace InputManager {

		extern bool m_KeyPressedData[GLFW_KEY_LAST];
		extern bool m_MouseButtonPressedData[GLFW_MOUSE_BUTTON_LAST];
		extern double m_MouseX;
		extern double m_MouseY;
		extern double m_MouseScrollX;
		extern double m_MouseScrollY;

		void Init(GLFWwindow* window);
		bool IsKeyDown(int key);
		bool IsMouseButtonDown(int button);
		std::pair<double, double> GetMousePosition();


		void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
		void MousePositionCallback(GLFWwindow* window, double xPos, double yPos);
		void MouseScrollCallback(GLFWwindow* window, double xOffset, double yOffset);
	};

}
