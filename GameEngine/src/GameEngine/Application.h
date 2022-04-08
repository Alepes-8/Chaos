#pragma once

#include "GameEngine/Graphics.h"
#include "InputEvents/EventMain.h"
#include "GameEngine/InputEvents/WindowEvents.h"
#include "GameEngine/InputEvents/MouseEvents.h"
#include "GameEngine/InputEvents/KeyEvents.h"



namespace GameEngine
{
	class Application
	{
	private:
		bool mQuit;
		GameEngine::Graphics* m_Graphics;
		SDL_Event m_Events;
	public: 
		static Application* sInstance;
		static void Release();

		Application();
		virtual ~Application();

		void Run();
	};

	/*--A function defined in the client*/
	Application* CreateApplication();
}