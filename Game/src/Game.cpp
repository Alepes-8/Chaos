#include "GameEngine.h"
#include <iostream>

class Game : public GameEngine::Application
{
public:
	Game()
	{

	}
	~Game()
	{

	}
};

void* getNativeWindow(SDL_Window* sdlWindow) {
    SDL_SysWMinfo wmi;
    SDL_VERSION(&wmi.version);
    //ASSERT_POSTCONDITION(SDL_GetWindowWMInfo(sdlWindow, &wmi), "SDL version unsupported!");
    HWND win = (HWND)wmi.info.win.window;
    return (void*)win;
}

int main(int argc, char** argv)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "Failed to initialize the SDL2 library\n";
        return -1;
    }

    SDL_Window* window = SDL_CreateWindow("SDL2 Window",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        680, 480,
        0);

    if (!window)
    {
        std::cout << "Failed to create window\n";
        return -1;
    }

    SDL_Surface* window_surface = SDL_GetWindowSurface(window);

    if (!window_surface)
    {
        std::cout << "Failed to get the surface from the window\n";
        return -1;
    }

    SDL_UpdateWindowSurface(window);

    filament::Engine* engine = filament::Engine::create();
    filament::SwapChain* swapChain = engine->createSwapChain(getNativeWindow(window));
    filament::Renderer* renderer = engine->createRenderer();


	printf("Starting GameEngine Hejsan\n");


	GameEngine::Log::Init();
	GameEngine::Log::GetCoreLogger()->warn("The code making this should be shortend with define in log.h");


	auto game = GameEngine::CreateApplication();
	game->Run();
	delete game;

}

GameEngine::Application* GameEngine::CreateApplication()
{
	return new Game;
}