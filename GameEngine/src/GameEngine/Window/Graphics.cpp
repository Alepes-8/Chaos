#include "Graphics.h"

GameEngine::Graphics* GameEngine::Graphics::m_sInstance = NULL;
bool GameEngine::Graphics::m_sInitialized = false;

GameEngine::Graphics::Graphics() {
	m_BackBuffer = NULL;
	m_sInitialized = Init();
}

GameEngine::Graphics::~Graphics() {
	bgfx::shutdown();
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

void GameEngine::Graphics::Initbgfx() {

    // Collect information about the window from SDL
    SDL_SysWMinfo wmi;
    SDL_VERSION(&wmi.version);
    SDL_GetWindowWMInfo(window, &wmi);

    bgfx::PlatformData pd;
    // and give the pointer to the window to pd
    pd.nwh = (void*)(uintptr_t)wmi.info.win.window;

    bgfx::setPlatformData(pd); // Tell bgfx about the platform and window
    
    bgfx::renderFrame(); // Render an empty frame

    //innit bgfx
    bgfx::Init init;
    init.type = bgfx::RendererType::OpenGL;
    bgfx::init(init);

    // Reset window
    bgfx::reset(Screen_Width, Screen_Hight, BGFX_RESET_VSYNC);

    
    bgfx::setDebug(BGFX_DEBUG_TEXT);// Enable debug text.

    // Set view rectangle for 0th view
    bgfx::setViewRect(0, 0, 0, uint16_t(Screen_Width), uint16_t(Screen_Hight));

    // Clear the view rect
    bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH,
        0x443355FF, 1.0f, 0);

    bgfx::touch(0);// Set empty primitive on screen
}

/*Used to refresh the window*/
void GameEngine::Graphics::Render() {
	bgfx::frame(); //Advance to next frame. When using multithreaded renderer,
}