#include "Graphics.h"

GameEngine::Graphics* GameEngine::Graphics::m_sInstance = NULL;
bool GameEngine::Graphics::m_sInitialized = false;

GameEngine::Graphics::Graphics() {
	m_BackBuffer = NULL;
	m_sInitialized = Init();
}

GameEngine::Graphics::~Graphics() {
	SDL_DestroyWindow(window);
	window = NULL;
	SDL_Quit();
}

bool GameEngine::Graphics::GetInitialize() { return m_sInitialized; }


/*Create the video and all in it*/
bool GameEngine::Graphics::Init() {

	/*Window Init*/
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		GameEngine::Log::GetCoreLogger()->warn("SDL Initilization Error");
		return false;
	}

	/*Window creation*/
	window = SDL_CreateWindow("SDL2 Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Screen_Width, Screen_Hight, SDL_WINDOW_SHOWN);
	if (window == NULL) {
		GameEngine::Log::GetCoreLogger()->warn("Window Creation Error");
		return false;
	}

	m_BackBuffer = SDL_GetWindowSurface(window);
	return true;
}

GameEngine::Graphics* GameEngine::Graphics::CreateInstance()
{
	if (m_sInstance == NULL) {
		m_sInstance = new GameEngine::Graphics();
	}
	return m_sInstance;
}

void GameEngine::Graphics::Terminate()
{
	delete m_sInstance;
	m_sInstance = NULL;
	m_sInitialized = false;
}

/*Used to refresh the window*/
void GameEngine::Graphics::Render() { SDL_UpdateWindowSurface(window); }