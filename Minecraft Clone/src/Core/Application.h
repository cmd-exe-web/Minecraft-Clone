#pragma once

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
		bool m_IsRunning = true;
		bool m_WireFrameMode = false;
	};

}
