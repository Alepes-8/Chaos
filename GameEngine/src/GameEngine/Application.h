#pragma once

#include "Window/Timer.h"
#include "Window/Graphics.h"
#include "InputEvents/EventMain.h"
#include "GameEngine/InputEvents/WindowEvents.h"
#include "GameEngine/InputEvents/MouseEvents.h"
#include "GameEngine/InputEvents/KeyEvents.h"


namespace GameEngine
{
	class Application
	{
	private:
		const int frameRate = 60;
		bool mQuit;
		SDL_Event m_Events;

		GameEngine::Graphics* m_Graphics;
		GameEngine::Timer* m_Timer;

	public: 
		static Application* sInstance;
		static void Terminate();

		Application();
		virtual ~Application();

		void Run();
	};

	/*--A function defined in the client*/
	Application* CreateApplication();
}