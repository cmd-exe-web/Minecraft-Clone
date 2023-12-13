#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>

namespace MyCraft {

	class Window {
	public:
		Window();
		~Window();

		void ShutDown();

		bool ShouldClose() const;
		void PollEvents();
		void SwapBuffers();

		void CloseWindow();
		GLFWwindow* GetHandle() const { return m_Window; }
	private:
		int m_WindowHeight;
		int m_WindowWidth;
		std::string m_WindowTitle;
		GLFWwindow* m_Window;
		bool m_WireFrameMode;
	};

}
