#include "Application.h"

#include <GLFW/glfw3.h>

#include <iostream>

#include "InputManager.h"
#include "Graphics/Shader.h"
#include "Graphics/Camera.h"
#include "Graphics/Texture.h"
#include "Graphics/Shapes/Builder/CubeBuilder.h"
#include "Graphics/Shapes/Cube.h"
#include "Graphics/Mesh.h"

#include "Graphics/VertexArray.h"
#include "Graphics/VertexBuffer.h"
#include "Graphics/VertexBufferLayout.h" 
#include "Graphics/IndexBuffer.h"
#include "Graphics/Renderer/CubeRenderer.h"
#include "Scene/Chunk.h"

namespace MyCraft {

	Application::Application()
		:m_Window()
	{
		InputManager::Init(m_Window.GetHandle());
		CubeRenderer::Init();
	}

	Application::~Application()
	{
		m_Window.ShutDown();
	}

	void Application::Run()
	{
		Shader shader("res/shaders/Texture.shader");
		Camera camera;
		Texture texture(GL_TEXTURE_2D, "res/textures/cobblestone.png", Format::PNG);
		texture.Load();
		texture.Bind(GL_TEXTURE0);

		shader.Bind();
		shader.SetUniformMat4("u_Proj", camera.GetProjectionMatrix());
		shader.SetUniform1i("u_Tex0", 0);
		shader.Unbind();

		GLFWwindow* window = m_Window.GetHandle();

		Chunk chunk;

		double lastTime = glfwGetTime();
		int frameCount = 0;
		double currentTime = 0;
		glClearColor(0.0f, 1.0f, 1.0f, 1.0f);

		/* Loop until the user closes the window */
		while (!m_Window.ShouldClose()) {
			/* Poll for and process events */

			currentTime = glfwGetTime();
			frameCount++;
			if (currentTime - lastTime >= 1.0f) {
				printf("FPS: %d, Frame Time: %f ms\n", frameCount, 1000.0 / (double)frameCount);
				frameCount = 0;
				lastTime += 1.0;
			}
			CubeRenderer::ResetStats();
			m_Window.PollEvents();
			camera.ProcessKeyboardEvents(window);
			camera.ProcessMouseEvent(window);

			if (InputManager::IsKeyDown(GLFW_KEY_ESCAPE)) {
				m_Window.CloseWindow();
			}
			if (InputManager::IsKeyDown(GLFW_KEY_G)) {
				m_WireFrameMode = !m_WireFrameMode;
				glPolygonMode(GL_FRONT_AND_BACK, m_WireFrameMode ? GL_LINE : GL_FILL);
			}
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			CubeRenderer::BeginBatch();

			camera.Update();
			chunk.Update();

			// CubeBuilder cubeBuilder;
			// cubeBuilder.AddFaces(Direction::Front);
			// cubeBuilder.AddFaces(Direction::Back);
			// cubeBuilder.AddFaces(Direction::Left);
			// cubeBuilder.AddFaces(Direction::Right);
			// cubeBuilder.AddFaces(Direction::Top);
			// cubeBuilder.AddFaces(Direction::Bottom);

			// CubeRenderer::AddCube(cubeBuilder, { 0.0f, 0.0f, 0.0f });
			// CubeRenderer::AddCube(cubeBuilder, { 1.0f, 0.0f, 0.0f });

			CubeRenderer::EndBatch();

			shader.Bind();
			shader.SetUniformMat4("u_View", camera.GetViewMatrix());

			CubeRenderer::Flush();

			/* Swap front and back buffers */
			m_Window.SwapBuffers();
			std::cout << "Cube Count: " << CubeRenderer::GetStats().CubeCount << " : " << "Draw Calls: " << CubeRenderer::GetStats().DrawCount << std::endl;
		}
	}

}