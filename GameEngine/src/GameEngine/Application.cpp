#include "Application.h"


namespace GameEngine
{
	GameEngine::Application* GameEngine::Application::sInstance = NULL;

	void GameEngine::Application::Terminate()
	{
		delete sInstance;
		sInstance = NULL;
	}

	Application::Application() {
		GameEngine::Log::Init();

		mQuit = false;
		m_Timer = GameEngine::Timer::CreateInstance();

		m_Graphics = GameEngine::Graphics::CreateInstance();
		if (!GameEngine::Graphics::GetInitialize()) {mQuit = true;}
	}

	Application::~Application() {
		WindowCloseEvent c;
		GameEngine::Timer::Terminate();
		GameEngine::Graphics::Terminate();
		m_Timer = NULL;
		m_Graphics = NULL;
		
	}

	void Application::Run() {
		
		
		WindowResizeEvent e(12800, 720);
		WindowCloseEvent c;

		//HZ_TRACE(e);
		GameEngine::Log::GetCoreLogger()->warn("The code making this should be shortend with define in log.h");

		if (e.IsInCategory(EventCategoryApplication)) {
			GameEngine::Log::GetCoreLogger()->info("Yes it is inside the application.");
		}

		while (!mQuit) {
			m_Timer->Update();

			while (SDL_PollEvent(&m_Events) != 0) {
				if (m_Events.type == SDL_QUIT) {
					mQuit = true;
				}
				
			}
			if (m_Timer->getDeltaTime() >= 1.0f / frameRate) {
				m_Graphics->Render();
				m_Timer->Reset();
			}
			
		}
		
	}
}