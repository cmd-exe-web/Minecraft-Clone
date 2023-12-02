#pragma once

#include <GLFW/glfw3.h>

#include <unordered_map>
#include <utility>

namespace MyCraft {

	namespace InputManager {

		extern std::unordered_map<int, int> m_KeyStates;
		extern double m_MouseX;
		extern double m_MouseY;
		extern double m_MouseScrollX;
		extern double m_MouseScrollY;

		void Init(GLFWwindow* window);
		bool IsKeyDown(int key);                 // Checks if a key is tapped
		bool IsKeyPressed(int key);				 // Checks if a key is held down
		bool IsMouseButtonDown(int button);
		std::pair<double, double> GetMousePosition();


		void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
		void MousePositionCallback(GLFWwindow* window, double xPos, double yPos);
		void MouseScrollCallback(GLFWwindow* window, double xOffset, double yOffset);
	};

}
