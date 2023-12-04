#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>

#include "Renderer/VertexArray.h"
#include "Renderer/VertexBuffer.h"
#include "Renderer/VertexBufferLayout.h"
#include "Renderer/IndexBuffer.h"
#include "Renderer/Shader.h"
#include "Renderer/Cube.h"
#include "Renderer/Camera.h"

namespace MyCraft {

	class Window {
	public:
		Window();
		~Window();

		void Init();
		void SendDataToOpenGL();
		void Run();
		void Update();
		void Draw();
		void ShutDown();
	private:
		int m_WindowHeight;
		int m_WindowWidth;
		std::string m_WindowTitle;
		GLFWwindow* m_Window;
		bool m_WireFrameMode;
		Camera camera;
	};

}
