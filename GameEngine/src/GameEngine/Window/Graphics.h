#pragma once
#include "GameEngine/Log.h"
#include "SDL.h"
#include <stdio.h>
namespace GameEngine {
	class Graphics
	{
	public:
		static const int Screen_Width = 1200;
		static const int Screen_Hight = 800;

		SDL_Window* window;
		SDL_Surface* m_BackBuffer;

	private:
		static Graphics* m_sInstance;
		static bool m_sInitialized;

	public:
		static Graphics* CreateInstance();
		static void Terminate();
		static bool GetInitialize();
		void Render();

	private:
		Graphics();
		~Graphics();

		bool Init();
	};
}