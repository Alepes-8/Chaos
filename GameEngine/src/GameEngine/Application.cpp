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

    //void Application::Run() {

    //    /* Enable Unicode translation */
    //    int SDL_EnableUNICODE(1);
    //    SDL_Window* window = NULL;

    //    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    //        printf("SDL could not initialize! SDL_Error: %s\n",
    //            SDL_GetError());
    //    }
    //    else {
    //        //Create a window
    //        window = m_Graphics->window;
    //        if (window == NULL) {
    //            printf("Window could not be created! SDL_Error: %s\n",
    //                SDL_GetError());
    //        }
    //    }

    //    // Collect information about the window from SDL
    //    SDL_SysWMinfo wmi;
    //    SDL_VERSION(&wmi.version);
    //    if (!SDL_GetWindowWMInfo(window, &wmi)) {

    //    }

    //    bgfx::PlatformData pd;
    //    // and give the pointer to the window to pd
    //    pd.nwh = (void*)(uintptr_t)wmi.info.win.window;

    //    // Tell bgfx about the platform and window
    //    bgfx::setPlatformData(pd);

    //    // Render an empty frame
    //    bgfx::renderFrame();

    //    // Initialize bgfx

    //    bgfx::Init init;
    //    init.type = bgfx::RendererType::OpenGL;
    //    bgfx::init(init);

    //    //Shader
    //    Shader shader = Shader("../../GameEngine/GameEngine/src/GameEngine/Shaders/v_simple.bin",
    //        "../../GameEngine/GameEngine/src/GameEngine/Shaders/f_simple.bin");

    //    //Render a cube
    //    CubeRenderable cube;
    //    cube.setShader(shader);
    //    cube.init();
    //    
    //    
    //    // Reset window
    //    bgfx::reset(m_Graphics->Screen_Width, m_Graphics->Screen_Hight, BGFX_RESET_VSYNC);

    //    // Enable debug text.
    //    bgfx::setDebug(BGFX_DEBUG_TEXT /*| BGFX_DEBUG_STATS*/);

    //    // Set view rectangle for 0th view
    //    bgfx::setViewRect(0, 0, 0, uint16_t(m_Graphics->Screen_Width), uint16_t(m_Graphics->Screen_Hight));

    //    // Clear the view rect
    //    bgfx::setViewClear(0,
    //        BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH,
    //        0x443355FF, 1.0f, 0);

    //    // Set empty primitive on screen
    //    bgfx::touch(0);

    //    // Poll for events and wait till user closes window

    //    while (!mQuit) {
    //        m_Timer->Update();


    //        while (SDL_PollEvent(&m_Events) != 0) {

    //            if (m_Events.type == SDL_QUIT) {
    //                mQuit = true;
    //            }

    //            if (m_Events.type == SDL_MOUSEMOTION) {
    //                GameEngine::Log::GetCoreLogger()->warn("x then y");
    //                GameEngine::Log::GetCoreLogger()->warn((m_InputManager->MousePos()).x);
    //                GameEngine::Log::GetCoreLogger()->warn((m_InputManager->MousePos()).y);
    //            }
    //            /*else {
    //                PrintKeyInfo(&m_Events.key);
    //            }*/

    //            const bx::Vec3 at = { 0.0f, 0.0f,   0.0f };
    //            const bx::Vec3 eye = { 0.0f, 0.0f, 10.0f };

    //            // Set view and projection matrix for view 0.
    //            float view[16];
    //            bx::mtxLookAt(view, eye, at);

    //            float proj[16];
    //            bx::mtxProj(proj,
    //                60.0f,
    //                float(GameEngine::Graphics::Screen_Width) / float(GameEngine::Graphics::Screen_Hight),
    //                0.1f, 100.0f,
    //                bgfx::getCaps()->homogeneousDepth);

    //            bgfx::setViewTransform(0, view, proj);

    //            // Set view 0 default viewport.
    //            bgfx::setViewRect(0, 0, 0,
    //                GameEngine::Graphics::Screen_Width,
    //                GameEngine::Graphics::Screen_Hight);

    //            bgfx::touch(0);


    //            float mtx[16];
    //            bx::mtxRotateY(mtx, 0.0f);

    //            // position x,y,z
    //            mtx[12] = 0.0f;
    //            mtx[13] = 0.0f;
    //            mtx[14] = 0.0f;

    //            // Set model matrix for rendering.
    //            bgfx::setTransform(mtx);

    //            // Set vertex and index buffer.
    //            cube.render();

    //            // Set render states.
    //            bgfx::setState(BGFX_STATE_DEFAULT);

    //            bgfx::frame();
    //        }

    //        if (m_Timer->getDeltaTime() >= 1.0f / frameRate) {

    //            EarlyUpdate();
    //            Update();
    //            LateUpdate();
    //            Render();
    //        }

    //    }
    //    // Free up window
    //    SDL_DestroyWindow(window);

    //    bgfx::shutdown();
    //    // Shutdown SDL
    //    SDL_Quit();

    //}

    //void PrintKeyInfo(SDL_KeyboardEvent* key) {
    //    /* Is it a release or a press? */
    //    GameEngine::Log::GetCoreLogger()->info(SDL_GetKeyName(key->keysym.sym));


    //}

    SDL_Window* window = NULL;
    const int WIDTH = 640;
    const int HEIGHT = 480;

    bgfx::ShaderHandle loadShader(const char* _name) {
        char* data = new char[2048];
        std::ifstream file;
        size_t fileSize;
        file.open(_name);
        if (file.is_open()) {
            file.seekg(0, std::ios::end);
            fileSize = file.tellg();
            file.seekg(0, std::ios::beg);
            file.read(data, fileSize);
            file.close();
        }
        const bgfx::Memory* mem = bgfx::copy(data, fileSize + 1);
        mem->data[mem->size - 1] = '\0';
        bgfx::ShaderHandle handle = bgfx::createShader(mem);
        bgfx::setName(handle, _name);
        return handle;
    }


    static PosColorVertex s_cubeVertices[] =
    {
     {  0.5f,  0.5f, 0.0f, 0xff0000ff },
     {  0.5f, -0.5f, 0.0f, 0xff0000ff },
     { -0.5f, -0.5f, 0.0f, 0xff00ff00 },
     { -0.5f,  0.5f, 0.0f, 0xff00ff00 }
    };


    static const uint16_t s_cubeTriList[] =
    {
     0,1,3,
     1,2,3
    };

    static PosColorVertex cubeVertices[] =
    {
        {-1.0f,  1.0f,  1.0f, 0xff000000 },
        { 1.0f,  1.0f,  1.0f, 0xff0000ff },
        {-1.0f, -1.0f,  1.0f, 0xff00ff00 },
        { 1.0f, -1.0f,  1.0f, 0xff00ffff },
        {-1.0f,  1.0f, -1.0f, 0xffff0000 },
        { 1.0f,  1.0f, -1.0f, 0xffff00ff },
        {-1.0f, -1.0f, -1.0f, 0xffffff00 },
        { 1.0f, -1.0f, -1.0f, 0xffffffff },
    };

    static const uint16_t cubeTriList[] =
    {
        0, 1, 2,
        1, 3, 2,
        4, 6, 5,
        5, 6, 7,
        0, 2, 4,
        4, 2, 6,
        1, 5, 3,
        5, 7, 3,
        0, 4, 1,
        4, 5, 1,
        2, 3, 6,
        6, 3, 7,
    };

    bgfx::VertexBufferHandle m_vbh;
    bgfx::IndexBufferHandle m_ibh;
    bgfx::ProgramHandle m_program;

    void GameEngine::Application::Run() {

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

        PosColorVertex::init();
        m_vbh = bgfx::createVertexBuffer(
            // Static data can be passed with bgfx::makeRef
            bgfx::makeRef(cubeVertices, sizeof(cubeVertices)),
            PosColorVertex::ms_decl
        );

        m_ibh = bgfx::createIndexBuffer(
            // Static data can be passed with bgfx::makeRef
            bgfx::makeRef(cubeTriList, sizeof(cubeTriList))
        );

        bgfx::ShaderHandle vsh = loadShader("../../GameEngine/GameEngine/src/GameEngine/Shaders/vs_cubes.bin");
        bgfx::ShaderHandle fsh = loadShader("../../GameEngine/GameEngine/src/GameEngine/Shaders/fs_cubes.bin");

        m_program = bgfx::createProgram(vsh, fsh, true);



        // Reset window
        bgfx::reset(WIDTH, HEIGHT, BGFX_RESET_VSYNC);

        // Enable debug text.
        bgfx::setDebug(BGFX_DEBUG_TEXT /*| BGFX_DEBUG_STATS*/);

        // Set view rectangle for 0th view
        bgfx::setViewRect(0, 0, 0, uint16_t(WIDTH), uint16_t(HEIGHT));

        // Clear the view rect
        bgfx::setViewClear(0,
            BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH,
            0x443355FF, 1.0f, 0);


        // Set empty primitive on screen
        bgfx::touch(0);

        // Poll for events and wait till user closes window
        bool quit = false;
        SDL_Event currentEvent;
        unsigned int counter = 0;
        while (!quit) {
            m_Timer->Update();

            while (SDL_PollEvent(&currentEvent) != 0) {
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
                    float(WIDTH) / float(HEIGHT),
                    0.1f, 100.0f,
                    bgfx::getCaps()->homogeneousDepth);

                bgfx::setViewTransform(0, view, proj);

                // Set view 0 default viewport.
                bgfx::setViewRect(0, 0, 0,
                    WIDTH,
                    HEIGHT);

                bgfx::touch(0);


                float mtx[16];
                //bx::mtxRotateY(mtx, 0.0f);

                //// position x,y,z
                //mtx[12] = 0.0f;
                //mtx[13] = 0.0f;
                //mtx[14] = 0.0f;
                bx::mtxRotateXY(mtx, counter * 0.01f, counter * 0.01f);
                counter++;

                // Set model matrix for rendering.
                bgfx::setTransform(mtx);

                // Set vertex and index buffer.
                bgfx::setVertexBuffer(0, m_vbh);
                bgfx::setIndexBuffer(m_ibh);

                // Set render states.
                bgfx::setState(BGFX_STATE_DEFAULT);

                // Submit primitive for rendering to view 0.
                bgfx::submit(0, m_program);

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