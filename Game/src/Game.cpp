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
	auto game = GameEngine::CreateApplication();
	game->Run();
	GameEngine::Application::Terminate();
	game = NULL;
	return 0;
}

GameEngine::Application* GameEngine::CreateApplication()
{
	if (GameEngine::Application::sInstance == NULL) 
	{
		GameEngine::Application::sInstance = new Game;
	}
	return GameEngine::Application::sInstance;
}