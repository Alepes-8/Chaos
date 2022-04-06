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
	engine->destroy(&engine);

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