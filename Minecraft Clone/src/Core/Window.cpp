#include "Window.h"

#include <iostream>

#include "glm/gtc/matrix_transform.hpp"

#include "Constants.h"
#include "InputManager.h"
#include "Renderer/Shader.h"
#include "Renderer/Vertex.h"
#include "Renderer/Texture.h"

namespace MyCraft {

	void GLAPIENTRY
	MessageCallback( GLenum source,
					 GLenum type,
					 GLuint id,
					 GLenum severity,
					 GLsizei length,
					 const GLchar* message,
					 const void* userParam )
	{
	  fprintf( stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
			   ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ),
				type, severity, message );
	}

	Window::Window()
		:m_WindowHeight(SCREEN_HEIGHT),
		m_WindowWidth(SCREEN_WIDTH),
		m_WindowTitle(TITLE),
		m_Window(nullptr),
		cube(nullptr),
		m_WireFrameMode(false)
	{
	}

	Window::~Window()
	{
	}

	void Window::Init()
	{
		/* Initialize the library */
		if (!glfwInit())
			exit(-1);

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);



		const int SCREEN_WIDTH = 1280;
		const int SCREEN_HEIGHT = 720;

		/* Create a windowed mode window and its OpenGL context */
		m_Window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Minecraft Clone", NULL, NULL);
		if (!m_Window)
		{
			glfwTerminate();
			exit(-1);
		}

		/* Make the window's context current */
		glfwMakeContextCurrent(m_Window);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			printf("Failed to initialize GLAD.\n");
			glfwTerminate();
			exit(-1);
		}

		int flags;
		glGetIntegerv(GL_CONTEXT_FLAGS, &flags);

		glEnable              ( GL_DEBUG_OUTPUT );
		glDebugMessageCallback(MessageCallback, 0);


		// glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
		glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

		InputManager::Init(m_Window);
		cube = new Cube();
	}

	void Window::SendDataToOpenGL()
	{
	}

	void Window::Run()
	{
		SendDataToOpenGL();
		Shader colorShader("res/shaders/Basic.shader");
		colorShader.Unbind();

		Shader textureShader("res/shaders/Texture.shader");
		Texture dirtTexture(GL_TEXTURE_2D, "res/textures/grass_side.png", Format::PNG);
		dirtTexture.Load();
		dirtTexture.Bind(GL_TEXTURE0);

		textureShader.SetUniform1i("u_Tex0", 0);

		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(m_Window))
		{
			/* Poll for and process events */
			glfwPollEvents();
			camera.ProcessKeyboardEvents(m_Window, 0.0f);
			camera.ProcessMouseEvent(m_Window);
			/* Update */

			if (InputManager::IsKeyPressed(GLFW_KEY_ESCAPE)) {
				glfwSetWindowShouldClose(m_Window, GLFW_TRUE);
			}

			if (InputManager::IsKeyDown(GLFW_KEY_G)) {
				m_WireFrameMode = !m_WireFrameMode;
				glPolygonMode(GL_FRONT_AND_BACK, m_WireFrameMode ? GL_LINE : GL_FILL);
			}

			//if (InputManager::IsMouseButtonDown(GLFW_MOUSE_BUTTON_RIGHT)) {
			//	printf("Clicked RMB\n");
			//}

			//if (InputManager::IsMouseButtonDown(GLFW_MOUSE_BUTTON_LEFT)) {
			//	printf("Clicked LMB\n");
			//}

			/* Render here */
			glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// glm::mat4 uProj = glm::ortho(-SCREEN_WIDTH / 100.0f, SCREEN_WIDTH / 100.0f, -SCREEN_HEIGHT / 100.0f, SCREEN_HEIGHT / 100.0f);
			glm::mat4 uProj = glm::perspective(glm::radians(60.0f), (float)SCREEN_WIDTH / SCREEN_HEIGHT, 0.1f, 100.0f);
			textureShader.Bind();
			textureShader.SetUniformMat4("u_Proj", camera.GetProjectionMatrix());
			textureShader.SetUniformMat4("u_View", camera.GetViewMatrix());
			Draw();
			
			/* Swap front and back buffers */
			glfwSwapBuffers(m_Window);
		}
	}

	void Window::Update()
	{
	}

	void Window::Draw()
	{
		cube->Draw();
	}

	void Window::ShutDown()
	{
		glfwDestroyWindow(m_Window);
		glfwTerminate();
	}

}