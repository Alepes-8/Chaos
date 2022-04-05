#pragma once

#include "InputEvents/EventMain.h"
#include "GameEngine/InputEvents/WindowEvents.h"
#include "GameEngine/InputEvents/MouseEvents.h"
#include "GameEngine/InputEvents/KeyEvents.h"



namespace GameEngine
{
	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	/*--A function defined in the client*/
	Application* CreateApplication();
}