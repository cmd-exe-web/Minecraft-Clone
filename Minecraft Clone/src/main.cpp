#include "Core/Window.h"

int main(void)
{
    MyCraft::Window window;

    window.Init();
    window.Run();
    window.ShutDown();

	return 0;
}