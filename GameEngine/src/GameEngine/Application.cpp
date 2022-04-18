#include "Application.h" 
#include "GameEngine/EntitySystem/GameObject.h"

namespace GameEngine
{
	GameEngine::Application* GameEngine::Application::sInstance = NULL;

	void GameEngine::Application::Terminate()
	{
		delete sInstance;
		sInstance = NULL;
	}

	Application::Application() {
		GameEngine::Log::Init();

        m_InputManager = GameEngine::InputManager::CreateInstance();

		mQuit = false;
		m_Timer = GameEngine::Timer::CreateInstance();

		m_Graphics = GameEngine::Graphics::CreateInstance();
		if (!GameEngine::Graphics::GetInitialize()) { mQuit = true; }
	}

	Application::~Application() {
        GameEngine::InputManager::Terminate();
		GameEngine::Timer::Terminate();
		GameEngine::Graphics::Terminate();
        m_InputManager = NULL;
        m_Timer = NULL;
		m_Graphics = NULL;
	}



    void Application::EarlyUpdate() {
        m_InputManager->Update();
    }

    void Application::Update() {
        if (m_InputManager->Keydown(SDL_SCANCODE_ESCAPE)){
            mQuit = true;
        }
        if (m_InputManager->Keydown(SDL_SCANCODE_W)) {
            GameEngine::Log::GetCoreLogger()->info("W Down");
        }
        if (m_InputManager->KeyPressed(SDL_SCANCODE_W)) {
            GameEngine::Log::GetCoreLogger()->info("W Pressed");
        }
        if (m_InputManager->KeyReleased(SDL_SCANCODE_W)) {
            GameEngine::Log::GetCoreLogger()->info("W Released");
        }
        if (m_InputManager->MouseButtonDown(GameEngine::InputManager::left)) {
            GameEngine::Log::GetCoreLogger()->info("left Mouse down");
        }
        if (m_InputManager->MouseButtonPressed(GameEngine::InputManager::left)) {
            GameEngine::Log::GetCoreLogger()->info("left Mouse pressed");
        }
        if (m_InputManager->MouseButtonReleased(GameEngine::InputManager::left)) {
            GameEngine::Log::GetCoreLogger()->info("left Mouse released");
        }
    }

    void Application::Render() {
        bgfx::frame(); //Advance to next frame. When using multithreaded renderer,
        m_Graphics->Render();
    }

    void Application::LateUpdate() {
        m_InputManager->UpdatePrevInput();
        m_Timer->Reset();
    }

    void Application::Run() {

        /* Enable Unicode translation */
        int SDL_EnableUNICODE(1);
        SDL_Window* window = NULL;

        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            printf("SDL could not initialize! SDL_Error: %s\n",
                SDL_GetError());
        }
        else {
            //Create a window
            window = m_Graphics->window;
            if (window == NULL) {
                printf("Window could not be created! SDL_Error: %s\n",
                    SDL_GetError());
            }
        }

        // Collect information about the window from SDL
        SDL_SysWMinfo wmi;
        SDL_VERSION(&wmi.version);
        if (!SDL_GetWindowWMInfo(window, &wmi)) {

        }

        bgfx::PlatformData pd;
        // and give the pointer to the window to pd
        pd.nwh = (void*)(uintptr_t)wmi.info.win.window;

        // Tell bgfx about the platform and window
        bgfx::setPlatformData(pd);

        // Render an empty frame
        bgfx::renderFrame();

        // Initialize bgfx
        bgfx::init();

        // Reset window
        bgfx::reset(m_Graphics->Screen_Width, m_Graphics->Screen_Hight, BGFX_RESET_VSYNC);

        // Enable debug text.
        bgfx::setDebug(BGFX_DEBUG_TEXT /*| BGFX_DEBUG_STATS*/);

        // Set view rectangle for 0th view
        bgfx::setViewRect(0, 0, 0, uint16_t(m_Graphics->Screen_Width), uint16_t(m_Graphics->Screen_Hight));

        // Clear the view rect
        bgfx::setViewClear(0,
            BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH,
            0x443355FF, 1.0f, 0);

        // Set empty primitive on screen
        bgfx::touch(0);

        // Poll for events and wait till user closes window


        while (!mQuit) {
            m_Timer->Update();

            while (SDL_PollEvent(&m_Events) != 0) {
                if (m_Events.type == SDL_QUIT) {
                    mQuit = true;
                }
                if (m_Events.type == SDL_MOUSEMOTION) {
                    GameEngine::Log::GetCoreLogger()->warn("x then y");
                    GameEngine::Log::GetCoreLogger()->warn((m_InputManager->MousePos()).x);
                    GameEngine::Log::GetCoreLogger()->warn((m_InputManager->MousePos()).y);
                }
                /*else {
                    PrintKeyInfo(&m_Events.key);
                }*/
                
            }
            if (m_Timer->getDeltaTime() >= 1.0f / frameRate) { 
                
                EarlyUpdate();
                Update();
                LateUpdate();
                Render(); 
            }

        }
        // Free up window
        SDL_DestroyWindow(window);

        bgfx::shutdown();
        // Shutdown SDL
        SDL_Quit();

    }

    void PrintKeyInfo(SDL_KeyboardEvent* key) {
        /* Is it a release or a press? */
        GameEngine::Log::GetCoreLogger()->info(SDL_GetKeyName(key->keysym.sym));


    }

}