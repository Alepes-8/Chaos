#include "Application.h" 



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

        bgfx::Init init;
        init.type = bgfx::RendererType::OpenGL;
        bgfx::init(init);

        //Shader
        Shader shader = Shader("../../GameEngine/GameEngine/src/GameEngine/Shaders/v_simple.bin",
            "../../GameEngine/GameEngine/src/GameEngine/Shaders/f_simple.bin");

        //Render a cube
        CubeRenderable cube;
        cube.setShader(shader);
        cube.init();
        
        
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
            while (SDL_PollEvent(&m_Events) != 0) {
                if (m_Events.type == SDL_QUIT) {
                    mQuit = true;
                }

                const bx::Vec3 at = { 0.0f, 0.0f,   0.0f };
                const bx::Vec3 eye = { 0.0f, 0.0f, 10.0f };

                // Set view and projection matrix for view 0.
                float view[16];
                bx::mtxLookAt(view, eye, at);

                float proj[16];
                bx::mtxProj(proj,
                    60.0f,
                    float(GameEngine::Graphics::Screen_Width) / float(GameEngine::Graphics::Screen_Hight),
                    0.1f, 100.0f,
                    bgfx::getCaps()->homogeneousDepth);

                bgfx::setViewTransform(0, view, proj);

                // Set view 0 default viewport.
                bgfx::setViewRect(0, 0, 0,
                    GameEngine::Graphics::Screen_Width,
                    GameEngine::Graphics::Screen_Hight);

                bgfx::touch(0);


                float mtx[16];
                bx::mtxRotateY(mtx, 0.0f);

                // position x,y,z
                mtx[12] = 0.0f;
                mtx[13] = 0.0f;
                mtx[14] = 0.0f;

                // Set model matrix for rendering.
                bgfx::setTransform(mtx);

                // Set vertex and index buffer.
                cube.render();


                switch (bgfx::getRendererType()) {
                    case bgfx::RendererType::Noop:
                    case bgfx::RendererType::Direct3D9:  std::printf("dx9 used");   break;
                    case bgfx::RendererType::Direct3D11:
                    case bgfx::RendererType::Direct3D12: std::printf("dx11 used");  break;
                    case bgfx::RendererType::Gnm:        std::printf("pssl used");  break;
                    case bgfx::RendererType::Metal:      std::printf("metal used"); break;
                    case bgfx::RendererType::OpenGL:     std::printf("glsl used");  break;
                    case bgfx::RendererType::OpenGLES:   std::printf("essl used");  break;
                    case bgfx::RendererType::Vulkan:     std::printf("spirv used"); break;
                }

                // Set render states.
                bgfx::setState(BGFX_STATE_DEFAULT);

                bgfx::frame();
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