#pragma once
#include "Log.h"
#include "SDL.h"
#include <stdio.h>
namespace GameEngine {
	class Graphics
	{
	public:
		static const int Screen_Width = 800;
		static const int Screen_Hight = 600;

		SDL_Window* window;
		SDL_Surface* m_BackBuffer;

	private:
		static Graphics* m_sInstance;
		static bool m_sInitialize;

	public:
		static Graphics* Instance();
		static void Release();
		static bool GetInitialize();
		void Render();

	private:
		Graphics();
		~Graphics();

		bool Init();
	};
}
