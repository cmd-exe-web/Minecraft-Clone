#include "Renderer.h"

#include <GLFW/glfw3.h>

#include <iostream>

Renderer::Renderer()
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		printf("Failed to initialize GLAD.\n");
		glfwTerminate();
		exit(-1);
	}
	glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
}

Renderer::~Renderer()
{
}

void Renderer::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::Render()
{
	Clear();
}
