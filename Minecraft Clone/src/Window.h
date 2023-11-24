#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>

namespace MyCraft {

	class Window {
	public:
		Window();
		~Window();

		void Init();
		void Run();
		void ShutDown();
	private:
		int m_WindowHeight;
		int m_WindowWidth;
		std::string m_WindowTitle;
		GLFWwindow* m_Window;
	};

}
