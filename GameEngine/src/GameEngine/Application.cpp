#include "Application.h"
#include "Init.cpp"


namespace GameEngine
{
	GameEngine::Application* GameEngine::Application::sInstance = NULL;

	void GameEngine::Application::Release()
	{
		delete sInstance;
		sInstance = NULL;
	}

	Application::Application() {
		mQuit = false;
		m_Graphics = GameEngine::Graphics::Instance();

		if (!GameEngine::Graphics::GetInitialize())
		{
			mQuit = true;
		}
	}

	Application::~Application() {
		GameEngine::Graphics::Release();
		m_Graphics = NULL;
	}

	void Application::Run() {
		StartInit();
		


		WindowResizeEvent e(12800, 720);
		WindowCloseEvent c;

		EventDispatcher test(e);
		//HZ_TRACE(e);
		GameEngine::Log::GetCoreLogger()->warn("The code making this should be shortend with define in log.h");

		GameEngine::Log::GetCoreLogger()->warn(e.GetCategoryFlags());		
		GameEngine::Log::GetCoreLogger()->warn(e.GetWidth());
		GameEngine::Log::GetCoreLogger()->warn(e.GetHeight());
		GameEngine::Log::GetCoreLogger()->warn(e.GetName());
		GameEngine::Log::GetCoreLogger()->warn(e.ToString());

		GameEngine::Log::GetCoreLogger()->warn(c.GetName());

		if (e.IsInCategory(EventCategoryApplication)) {
			GameEngine::Log::GetCoreLogger()->info("Yes it is inside the application.");
		}

		while (!mQuit) {
			while (SDL_PollEvent(&m_Events) != 0) {
				if (m_Events.type == SDL_QUIT) {
					mQuit = true;
				}
				m_Graphics->Render();
			}
		}
		
	}
}