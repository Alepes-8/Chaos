#include "GameEngine.h"


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

int main(int argc, char** argv)
{

	filament::Engine* engine = filament::Engine::create();
	

	engine->createRenderer();

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

    SDL_Delay(5000);

	printf("Starting GameEngine Hejsan\n");


	auto game = GameEngine::CreateApplication();
	game->Run();
	delete game;
	engine->destroy(&engine);

}

GameEngine::Application* GameEngine::CreateApplication()
{
	return new Game;
}