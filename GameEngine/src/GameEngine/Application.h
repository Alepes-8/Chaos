#pragma once
#include "GameEngine/EntitySystem/BaseComponent.h"
#include "GameEngine/EntitySystem/GameObject.h"
#include "Window/Timer.h"
#include "Window/Graphics.h"
#include "InputEvents/InputManager.h"
#include "EntitySystem/EntityManager.h"
#include "GameEngine/Camera/Camera.h"


#include <vector>


namespace GameEngine
{
	class Application
	{
	private:
		const int frameRate = 60;
		bool mQuit;
		SDL_Event m_Events;

		GameEngine::EntityManager* m_EntityManager;
		GameEngine::Graphics* m_Graphics;
		GameEngine::Timer* m_Timer;
		GameEngine::InputManager* m_InputManager;

	public:
		static Application* sInstance;
		static void Terminate();

		Application();
		virtual ~Application();

		void EarlyUpdate();
		void Update();
		void LateUpdate();
		void Render();
		void Run();
	};

	/*--A function defined in the client*/
	Application* CreateApplication();
}