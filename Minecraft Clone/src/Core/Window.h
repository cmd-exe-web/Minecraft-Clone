#pragma once

#include <string>

#include "Graphics/VertexArray.h"
#include "Graphics/VertexBuffer.h"
#include "Graphics/VertexBufferLayout.h"
#include "Graphics/IndexBuffer.h"
#include "Graphics/Shader.h"
#include "Graphics/Camera.h"

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
