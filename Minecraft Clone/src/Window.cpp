#include "Window.h"
#include "Constants.h"

#include "InputManager.h"

#include <iostream>


namespace MyCraft {

	Window::Window()
		:m_WindowHeight(SCREEN_HEIGHT),
		m_WindowWidth(SCREEN_WIDTH),
		m_WindowTitle(TITLE),
		m_Window(nullptr)

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

		glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

		InputManager::Init(m_Window);
	}

	void Window::Run()
	{
		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(m_Window))
		{
			glfwPollEvents();
			/* Update */
			if (InputManager::IsKeyDown(GLFW_KEY_W)) {
				printf("Pressed the W key\n");
			}

			if (InputManager::IsKeyDown(GLFW_KEY_ESCAPE)) {
				glfwSetWindowShouldClose(m_Window, GLFW_TRUE);
			}

			if (InputManager::IsMouseButtonDown(GLFW_MOUSE_BUTTON_RIGHT)) {
				printf("Clicked RMB\n");
			}

			if (InputManager::IsMouseButtonDown(GLFW_MOUSE_BUTTON_LEFT)) {
				printf("Clicked LMB\n");
			}

			auto position = InputManager::GetMousePosition();
			std::cout << position.first << " : " << position.second << std::endl;

			/* Render here */
			glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			/* Swap front and back buffers */
			glfwSwapBuffers(m_Window);

			/* Poll for and process events */
		}
	}

	void Window::ShutDown()
	{
		glfwDestroyWindow(m_Window);
		glfwTerminate();
	}

}