#include "Window.h"

#include <iostream>

#include "glm/gtc/matrix_transform.hpp"

#include "Constants.h"
#include "InputManager.h"
#include "Renderer/Shader.h"
#include "Renderer/Vertex.h"

glm::mat4 translation(1.0f);
glm::mat4 scale(1.0f);
glm::mat4 rotation(1.0f);
glm::mat4 view(1.0f);
glm::mat4 proj(1.0f);

const float SPEED = 0.01f;
float positionX = 0.0f;
float positionY = 0.0f;

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

		int flags;
		glGetIntegerv(GL_CONTEXT_FLAGS, &flags);

		glEnable              ( GL_DEBUG_OUTPUT );
		glDebugMessageCallback(MessageCallback, 0);

	//if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
	//{
	//	glEnable(GL_DEBUG_OUTPUT);
	//	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS); 
	//	glDebugMessageCallback(glDebugOutput, nullptr);
	//	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
	//} 

		glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

		InputManager::Init(m_Window);
	}

	void Window::SendDataToOpenGL()
	{
		Vertex vertices[] = {
			{ {-0.5f, -0.5f,  0.0f }, {1.0f, 0.0f, 0.0f, 1.0f}},
			{ { 0.5f, -0.5f,  0.0f }, {0.0f, 1.0f, 0.0f, 1.0f}},
			{ { 0.5f,  0.5f,  0.0f }, {0.0f, 0.0f, 1.0f, 1.0f}},
			{ {-0.5f,  0.5f,  0.0f }, {1.0f, 1.0f, 0.0f, 1.0f}},
		};
 unsigned short indices[] = {
			0, 1, 2,
			0, 2, 3
		};

		VAO = new VertexArray();
		VAO->Bind();

		VBO = new VertexBuffer(vertices, sizeof(vertices));
		layout = new VertexBufferLayout();
		layout->Push<float>(3);
		layout->Push<float>(4);

		IBO = new IndexBuffer(indices, sizeof(indices));

		VAO->AddBuffers(*VBO, *layout);

		VAO->Unbind();
		VBO->Unbind();
		IBO->Unbind();

		shader = new Shader("res/shaders/Basic.shader");
		shader->Bind();
		shader->SetUniform4fv("u_Color", glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));
		proj = glm::ortho(-4.0f, 4.0f, -2.25f, 2.25f);
	}

	void Window::Run()
	{
		SendDataToOpenGL();
		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(m_Window))
		{
			/* Poll for and process events */
			glfwPollEvents();
			/* Update */
			if (InputManager::IsKeyDown(GLFW_KEY_W)) {
				printf("Pressed the W key\n");
				positionY += SPEED;
			}
			if (InputManager::IsKeyDown(GLFW_KEY_A)) {
				printf("Pressed the A key\n");
				positionX -= SPEED;
			}
			if (InputManager::IsKeyDown(GLFW_KEY_S)) {
				printf("Pressed the S key\n");
				positionY -= SPEED;
			}
			if (InputManager::IsKeyDown(GLFW_KEY_D)) {
				printf("Pressed the D key\n");
				positionX += SPEED;
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

			/* Update */
			glm::vec3 newPosition(positionX, positionY, 0.0f);
			scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f, 0.5f, 0.5f));
			rotation = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
			translation = glm::translate(glm::mat4(1.0f), newPosition);
			glm::mat4 model = translation * rotation * scale;
			shader->Bind();
			shader->SetUniformMat4("u_Model", model);
			shader->SetUniformMat4("u_View", view);
			shader->SetUniformMat4("u_Proj", proj);

			/* Render here */
			glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			VAO->Bind();
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
			
			/* Swap front and back buffers */
			glfwSwapBuffers(m_Window);
		}
	}

	void Window::ShutDown()
	{
		glfwDestroyWindow(m_Window);
		glfwTerminate();
	}

}