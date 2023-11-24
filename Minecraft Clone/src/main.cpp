#include "Application.h"

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_E && action == GLFW_PRESS)
        printf("Pressed E key\n");
}

int main(void)
{
    MyCraft::Application app;

    app.Init();
    app.Run();
    app.ShutDown();

	return 0;
}