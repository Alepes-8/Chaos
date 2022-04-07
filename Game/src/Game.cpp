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
    ASSERT_POSTCONDITION(SDL_GetWindowWMInfo(sdlWindow, &wmi), "SDL version unsupported!");
    HWND win = (HWND)wmi.info.win.window;
    return (void*)win;
}

struct Config {
    std::string title;
    std::string iblDirectory;
    std::string dirt;
    float scale = 1.0f;
    bool splitView = false;
    mutable filament::Engine::Backend backend = filament::Engine::Backend::DEFAULT;
    filament::camutils::Mode cameraMode = filament::camutils::Mode::ORBIT;
    bool resizeable = true;
    bool headless = false;
};

int main(int argc, char** argv)
{
    Config config;
    config.title = "hellotriangle";
    const int x = SDL_WINDOWPOS_CENTERED;
    const int y = SDL_WINDOWPOS_CENTERED;
    uint32_t windowFlags = SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_RESIZABLE;
    SDL_Window* mWindow = SDL_CreateWindow("Filament", x, y, (int)720, (int)1280, windowFlags);

    void* nativeWindow = ::getNativeWindow(mWindow);
    // Create the Engine after the window in case this happens to be a single-threaded platform.
    // For single-threaded platforms, we need to ensure that Filament's OpenGL context is
    // current, rather than the one created by SDL.
    filament::Engine* engine = filament::Engine::create(config.backend);
    config.backend = engine->getBackend();
    void* nativeSwapChain = nativeWindow;
    filament::SwapChain* swapChain = engine->createSwapChain(nativeSwapChain);
    filament::Renderer* renderer = engine->createRenderer();

    filament::Camera* camera = engine->createCamera(utils::EntityManager::get().create());
    filament::View* view = engine->createView();
    filament::Scene* scene = engine->createScene();

    view->setCamera(camera);
    view->setScene(scene);

    utils::Entity renderable = utils::EntityManager::get().create();
    // build a quad
    RenderableManager::Builder(1)
        .boundingBox({ { -1, -1, -1 }, { 1, 1, 1 } })
        .material(0, materialInstance)
        .geometry(0, RenderableManager::PrimitiveType::TRIANGLES, vertexBuffer, indexBuffer, 0, 6)
        .culling(false)
        .build(*engine, renderable);
    scene->addEntity(renderable);

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