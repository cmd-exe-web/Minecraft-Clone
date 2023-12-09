#pragma once

#include "Graphics/Renderer.h"
#include "Window.h"

namespace MyCraft {

	class Application
	{
	public:
		Application();
		~Application();

		void Run();
	private:
		Window m_Window;
		Renderer m_Renderer;
		bool m_IsRunning = true;
		bool m_WireFrameMode = false;
	};

}
