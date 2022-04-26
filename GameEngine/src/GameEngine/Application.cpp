#include "Application.h" 



namespace GameEngine
{
    GameEngine::Application* GameEngine::Application::sInstance = NULL;

    void GameEngine::Application::Terminate()
    {
        delete sInstance;
        sInstance = NULL;
    }

    GameEngine::Application::Application() {
        GameEngine::Log::Init();

        m_InputManager = GameEngine::InputManager::CreateInstance();

        mQuit = false;
        m_Timer = GameEngine::Timer::CreateInstance();

        m_Graphics = GameEngine::Graphics::CreateInstance();
        if (!GameEngine::Graphics::GetInitialize()) { mQuit = true; }

        m_EntityManager = GameEngine::EntityManager::CreateInstance();
    }


    GameEngine::Application::~Application() {
        GameEngine::InputManager::Terminate();
        GameEngine::Timer::Terminate();
        GameEngine::Graphics::Terminate();
        m_InputManager = NULL;
        m_Timer = NULL;
        m_Graphics = NULL;
    }


    void GameEngine::Application::EarlyUpdate() {
        m_InputManager->Update();
    }

    void GameEngine::Application::Update() {
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

    void GameEngine::Application::Render() {
        bgfx::frame(); //Advance to next frame. When using multithreaded renderer,
        m_Graphics->Render();
    }

    void GameEngine::Application::LateUpdate() {
        m_InputManager->UpdatePrevInput();
        m_Timer->Reset();
    }

    SDL_Window* window = NULL;


    void GameEngine::Application::Run() {
        window = m_Graphics->window;

        // Collect information about the window from SDL
        SDL_SysWMinfo wmi;
        SDL_VERSION(&wmi.version);
        SDL_GetWindowWMInfo(window, &wmi);

        bgfx::PlatformData pd;
        pd.nwh = (void*)(uintptr_t)wmi.info.win.window; // and give the pointer to the window to pd
        bgfx::setPlatformData(pd);// Tell bgfx about the platform and window
        bgfx::renderFrame();// Render an empty frame

        
        bgfx::Init init;//innit bgfx
        init.type = bgfx::RendererType::OpenGL;
        bgfx::init(init);

        
        bgfx::reset(m_Graphics->Screen_Width, m_Graphics->Screen_Hight, BGFX_RESET_VSYNC);// Reset window
        bgfx::setDebug(BGFX_DEBUG_TEXT /*| BGFX_DEBUG_STATS*/);// Enable debug text.

       
        bgfx::setViewRect(0, 0, 0, uint16_t(m_Graphics->Screen_Width),
            uint16_t(m_Graphics->Screen_Hight)); // Set view rectangle for 0th view

        
        bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH,
            0x443355FF, 1.0f, 0);// Clear the view rect

        // Set empty primitive on screen
        bgfx::touch(0);
        //------------------------------------------//


       //-----------------SHADERS--------------------//
        //Create shader
        Shader shader = Shader();
        shader.loadFragmentShader("../GameEngine/src/GameEngine/Shaders/fs_cubes.bin");
        shader.loadVertexShader("../GameEngine/src/GameEngine/Shaders/vs_cubes.bin");
        
        //Create a program so we can pass value to the sahder
        bgfx::ProgramHandle m_program = shader.createProgram();
        //-------------------------------------------//

        //-----------------RENDERABLES-----------------//
        //Init Renderables so bgfx knows the format of our renderable data
        Renderable::init();
        
        Renderable cube = CubeRenderable();//create a cube
        Renderable cube2 = CubeRenderable();

        cube.createBuffers();//init vertices and indices buffers
        cube2.createBuffers();
        //-------------------------------------------//


        SDL_Event currentEvent;
        unsigned int counter = 0;

        while (!mQuit) {

            m_Timer->Update();

            if (SDL_PollEvent(&currentEvent) != 0) {
                if (currentEvent.type == SDL_QUIT) {
                    mQuit = true;
                }
            }

            if (m_Timer->getDeltaTime() >= 1.0f / frameRate) { //this is not the couse of the black blinking bug
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

                cube.setMtx(mtx);// Set model matrix for rendering.
                cube.submit(0, m_program);//submit cube values to the program
                //--------------------------------------//

                //----------------CUBE 2-----------------//
                float mtx2[16];
                bx::mtxRotateXY(mtx2, counter * 0.01f, counter * 0.01f);
                mtx2[12] = counter * 0.01f;
                cube2.setMtx(mtx2);
                cube2.submit(0, m_program);
                //--------------------------------------//

                LateUpdate();
                Render();
                counter++;
            }
            

         
        }
        bgfx::shutdown();
        // Free up window
        SDL_DestroyWindow(window);
        // Shutdown SDL
        SDL_Quit();
    }
}