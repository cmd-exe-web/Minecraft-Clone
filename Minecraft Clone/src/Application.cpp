#include "Application.h"
#include "Constants.h"

#include <iostream>


namespace MyCraft {
	Application::Application()
		:m_WindowHeight(SCREEN_HEIGHT),
		m_WindowWidth(SCREEN_WIDTH),
		m_WindowTitle(TITLE),
		m_Window(nullptr)

	{
	}
	Application::~Application()
	{
	}
	void Application::Init()
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

		glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	}
	void Application::Run()
	{
		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(m_Window))
		{
			/* Render here */
			glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			/* Swap front and back buffers */
			glfwSwapBuffers(m_Window);

			/* Poll for and process events */
			glfwPollEvents();
		}
	}
	void Application::ShutDown()
	{
		glfwDestroyWindow(m_Window);
		glfwTerminate();
	}
}