#include "Window.h"

#include <iostream>

#include "glm/gtc/matrix_transform.hpp"

#include "Constants.h"
#include "InputManager.h"
#include "Graphics/Shader.h"
#include "Graphics/Texture.h"

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
		m_WireFrameMode(false)
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


		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
		glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	}

	Window::~Window()
	{
	}

	void Window::ShutDown()
	{
		glfwDestroyWindow(m_Window);
		glfwTerminate();
	}

	bool Window::ShouldClose() const
	{
		return glfwWindowShouldClose(m_Window);
	}

	void Window::PollEvents()
	{
		glfwPollEvents();
	}

	void Window::SwapBuffers()
	{
		glfwSwapBuffers(m_Window);
	}

	void Window::CloseWindow()
	{
		glfwSetWindowShouldClose(m_Window, GLFW_TRUE);
	}

}