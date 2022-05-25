#pragma once
#include "Window/Timer.h"
#include "Window/Graphics.h"
#include "InputEvents/InputManager.h"
#include "GameEngine/Camera/Camera.h"
#include "GameEngine/EntitySystem/Messenger.h"

#include <vector>


namespace GameEngine
{
	class Application
	{
	private:
		const int frameRate = 600;
		
		int audio;
		bool mQuit;
		SDL_Event m_Events;
		int selectedID;

		GameEngine::EntityManager* m_EntityManager;
		GameEngine::Graphics* m_Graphics;
		GameEngine::Timer* m_Timer;
		GameEngine::InputManager* m_InputManager;
		GameEngine::Camera* m_Camera;
		GameEngine::Messenger* m_Messenger;

		void CallCreation(char*);
		struct Vector2  GetRealCords();
		

		void EarlyUpdate();
		void Update();
		void LateUpdate();
		void Render();
		void initUnit(int unitID, PathFinding* pathfindingComponent, EntityManager* m_EntityManager);
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