#pragma once

#ifdef HZ_PLATFORM_WINDOWS

extern GameEngine::Application* GameEngine::CreateApplication();

int main(int argc, char** argv)
{
	printf("Starting GameEngine Hejsan\n");


	GameEngine::Log::Init();
	GameEngine::Log::GetCoreLogger()->warn("life is bad");


	auto game = GameEngine::CreateApplication();
	game->Run();
	delete game;
}

#endif // HZ_PLATFORM_WINDOWS
