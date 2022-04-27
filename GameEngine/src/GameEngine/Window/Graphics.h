#pragma once
#include "GameEngine/Log.h"
#include "SDL.h"
#include <stdio.h>


#include <SDL_syswm.h>
#include <bgfx/bgfx.h>
#include <bgfx/platform.h>
#include <bx/math.h>
#include <bx/bx.h>
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
		void Initbgfx();
	private:
		Graphics();
		~Graphics();

		bool Init();
	};
}