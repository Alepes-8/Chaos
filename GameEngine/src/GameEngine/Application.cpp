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
        if (m_InputManager->Keydown(SDL_SCANCODE_ESCAPE)) {
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

    SDL_Window* window = NULL;
  

    void GameEngine::Application::Run() {

        //------------------WINDOW------------------//
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
       
        //innit bgfx
        bgfx::Init init;
        init.type = bgfx::RendererType::OpenGL;
        bgfx::init(init);

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
        //------------------------------------------//


       //-----------------SHADERS--------------------//
        //Create shader
        Shader shader = Shader();
        shader.loadFragmentShader("./src/Shaders/BIN/f_simple.bin");
        shader.loadVertexShader("./src/Shaders/BIN/v_simple.bin");
        //Create a program so we can pass value to the sahder
        bgfx::ProgramHandle m_program = shader.createProgram();
        //-------------------------------------------//

        //-----------------RENDERABLES-----------------//
        //Init Renderables so bgfx knows the format of our renderable data
        Renderable::init();

        //create a cube
        Renderable cube = CubeRenderable();
        //init vertices and indices buffers
        cube.createBuffers();

        Renderable cube2 = CubeRenderable();
        cube2.createBuffers();
        //-------------------------------------------//

        //------------------MESH---------------------//
        Mesh* vampire /*= meshLoad("3DModels/BIN format/vampire.bin")*/;
        //--------------------------------------------//

        
        //--------------------LOOP---------------------//
        // Poll for events and wait till user closes window
        bool quit = false;
        SDL_Event currentEvent;
        unsigned int counter = 0;
        while (!quit) {
            m_Timer->Update();
            
            if (SDL_PollEvent(&currentEvent) != 0) {
                if (currentEvent.type == SDL_QUIT) {
                    quit = true;
                }
               /* if (m_Events.type == SDL_MOUSEMOTION) {
                    GameEngine::Log::GetCoreLogger()->warn("x then y");
                    GameEngine::Log::GetCoreLogger()->warn((m_InputManager->MousePos()).x);
                    GameEngine::Log::GetCoreLogger()->warn((m_InputManager->MousePos()).y);
                }*/
                /*else {
                    PrintKeyInfo(&m_Events.key);
                }*/
            }

            if (m_Timer->getDeltaTime() >= 1.0f / frameRate){
                EarlyUpdate();
                Update();

                const bx::Vec3 at = { 0.0f, 0.0f,   0.0f };
                const bx::Vec3 eye = { 0.0f, 0.0f, 10.0f };

                // Set view and projection matrix for view 0.
                float view[16];
                bx::mtxLookAt(view, eye, at);

                float proj[16];
                bx::mtxProj(proj,
                    60.0f,
                    float(m_Graphics->Screen_Width) / float(m_Graphics->Screen_Hight),
                    0.1f, 100.0f,
                    bgfx::getCaps()->homogeneousDepth);

                bgfx::setViewTransform(0, view, proj);

                // Set view 0 default viewport.
                bgfx::setViewRect(0, 0, 0,
                    m_Graphics->Screen_Width,
                    m_Graphics->Screen_Hight);

                bgfx::touch(0);

                
                //-----------CUBE 1--------------------//
                float mtx[16];
                bx::mtxRotateXY(mtx, counter * 0.01f, counter * 0.01f);
                counter++;

                // Set model matrix for rendering.
                cube.setMtx(mtx);

                //submit cube values to the program
                cube.submit(0, m_program);
                //--------------------------------------//

                 //----------------CUBE 2-----------------//
                float mtx2[16];
                bx::mtxRotateXY(mtx2, counter * 0.01f, counter * 0.01f);
                mtx2[12] = counter * 0.01f;
                cube2.setMtx(mtx2);
                cube2.submit(0, m_program);
                //--------------------------------------//

                //-----------VAMPIRE----------------//
                float mtx_vampire[16];
                bx::mtxRotateXY(mtx_vampire, counter * 0.01f, counter * 0.01f);
                /*meshSubmit(vampire, 0, m_program, mtx_vampire);*/


                bgfx::frame();

                LateUpdate();
                Render();
            }
        }

        bgfx::shutdown();
        // Free up window
        SDL_DestroyWindow(window);
        // Shutdown SDL
        SDL_Quit();
    }
}