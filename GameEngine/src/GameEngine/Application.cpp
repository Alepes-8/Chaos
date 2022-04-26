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

        m_EntityManager = GameEngine::EntityManager::CreateInstance();
    }


    Application::~Application() {
        GameEngine::InputManager::Terminate();
        GameEngine::Timer::Terminate();
        GameEngine::Graphics::Terminate();
        GameEngine::EntityManager::Terminate();
        m_InputManager = NULL;
        m_Timer = NULL;
        m_Graphics = NULL;
        m_EntityManager = NULL;
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
        if (m_InputManager->KeyPressed(SDL_SCANCODE_C)) {
            GameEngine::Log::GetCoreLogger()->info("C Create");
            m_EntityManager->CreateNewEntity("Peasant");
        }
        if (m_InputManager->KeyPressed(SDL_SCANCODE_P)) {
            GameEngine::Log::GetCoreLogger()->info("P print");
            m_EntityManager->PrintList();
        }
        if (m_InputManager->KeyPressed(SDL_SCANCODE_O)) {
            GameEngine::Log::GetCoreLogger()->info("O print list");
            m_EntityManager->PrintFirstEntity();
        }
        if (m_InputManager->KeyPressed(SDL_SCANCODE_T)) {
            GameEngine::Log::GetCoreLogger()->info("T terminate");
            m_EntityManager->TerminateEnity(1);
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
        m_Graphics->Render();
    }

    void Application::LateUpdate() {
        m_InputManager->UpdatePrevInput();
        m_Timer->Reset();
    }

    void GameEngine::Application::Run() {

        //------------------WINDOW------------------//
        m_Graphics->Initbgfx();

       //-----------------SHADERS--------------------//
        //Create shader
        Shader shader = Shader("../GameEngine/src/GameEngine/Shaders/fs_cubes.bin",
            "../GameEngine/src/GameEngine/Shaders/vs_cubes.bin");
        bgfx::ProgramHandle m_program = shader.createProgram();
        //-------------------------------------------//

        //-----------------RENDERABLES-----------------//
        //Init Renderables so bgfx knows the format of our renderable data
        Renderer::init();

        //create a cube
        Renderer cube = CubeRenderable();
        //init vertices and indices buffers
        cube.createBuffers();

        Renderer cube2 = CubeRenderable();
        cube2.createBuffers();
        
        Renderer floor = CubeRenderable();
        floor.createBuffers();
        //----------------------------------------//

        //-----------------CAMERA-----------------//
        Camera cam = Camera();
        //----------------------------------------//
        m_EntityManager->CreateNewEntity("BackgroundMusic");
        //--------------------LOOP---------------------//
        // Poll for events and wait till user closes window

        m_EntityManager->CreateNewEntity("Cube");

        SDL_Event currentEvent;
        unsigned int counter = 0;
        while (!mQuit) {

            m_Timer->Update();

            if (SDL_PollEvent(&currentEvent) != 0) {
                if (currentEvent.type == SDL_QUIT) {
                    mQuit = true;
                }
            }

            if (m_Timer->getDeltaTime() >= 1.0f / frameRate) {
                EarlyUpdate();
                Update();

                cam.update(m_InputManager, 0, m_Graphics->Screen_Width, m_Graphics->Screen_Hight);

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
                bx::mtxTranslate(mtx2,5,0,0);
                cube2.setMtx(mtx2);
                cube2.submit(0, m_program);
                //--------------------------------------//

                float mtxfloor[16];
                bx::mtxScale(mtxfloor, 10, 10, 0.01);
                floor.setMtx(mtxfloor);
                floor.submit(0, m_program);

                LateUpdate();
                Render();
            }
        }
    }
}