#include "Application.h"
#include "GameEngine/Log.h"


namespace GameEngine
{
	Application::Application() {

	}

	Application::~Application() {

	}

	void Application::Run() {
		WindowResizeEvent e(12800, 720);
		WindowCloseEvent c;

		EventDispatcher test(e);
		//HZ_TRACE(e);
		GameEngine::Log::GetCoreLogger()->warn(e.GetCategoryFlags());		
		GameEngine::Log::GetCoreLogger()->warn(e.GetWidth());
		GameEngine::Log::GetCoreLogger()->warn(e.GetHeight());
		GameEngine::Log::GetCoreLogger()->warn(e.GetName());
		GameEngine::Log::GetCoreLogger()->warn(e.ToString());

		GameEngine::Log::GetCoreLogger()->warn(c.GetName());

		if (e.IsInCategory(EventCategoryApplication)) {
			GameEngine::Log::GetCoreLogger()->info("Yes it is inside the application.");
		}

		while (true);
		
	}
}