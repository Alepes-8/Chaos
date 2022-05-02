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
        m_Camera = GameEngine::Camera::CreateInstance();
    }


    Application::~Application() {
        GameEngine::InputManager::Terminate();
        GameEngine::Timer::Terminate();
        GameEngine::Graphics::Terminate();
        GameEngine::EntityManager::Terminate();
        GameEngine::Camera::Terminate();

        m_InputManager = NULL;
        m_Timer = NULL;
        m_Graphics = NULL;
        m_EntityManager = NULL;
        m_Camera = NULL;
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
            m_EntityManager->CreateNewEntity("Leader", -(m_InputManager->MousePos().x / 100) + 6, -(m_InputManager->MousePos().y / 100) + 3);

        }
        if (m_InputManager->KeyReleased(SDL_SCANCODE_W)) {
            GameEngine::Log::GetCoreLogger()->info("W Released");
        }
        if (m_InputManager->KeyPressed(SDL_SCANCODE_C)) {
            GameEngine::Log::GetCoreLogger()->info("C Create");
            std::cout << "positions x and y:" << -(m_InputManager->MousePos().x / 100) + 6 << ", " << -(m_InputManager->MousePos().y / 100) + 3 << std::endl;
            float y = (m_InputManager->MousePos().y / (float)m_Graphics->Screen_Hight) * 2 - 1;
            float x = (m_InputManager->MousePos().x / (float)m_Graphics->Screen_Width) * 2 - 1;
            
            float tempview[4][4];
            float tempproj[4][4];

            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    tempview[i][j] = m_Camera->_view[i * 4 + j];
                    tempproj[i][j] = m_Camera->_proj[i * 4 + j];
                }
            }

            float start[3];
            start[0] = x;
            start[1] = y;
            start[2] = 0;
            std::cout << start << std::endl;
            m_EntityManager->CreateNewEntity("Peasant", -(m_InputManager->MousePos().x / 100) + 6, -(m_InputManager->MousePos().y / 100) + 3);
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

        //-----------------CAMERA-----------------//


        //--------------------LOOP---------------------//
        // Poll for events and wait till user closes window
        

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
                counter++;
                EarlyUpdate();
                Update();

                m_Camera->Update(m_InputManager, 0, m_Graphics->Screen_Width, m_Graphics->Screen_Hight);
               
                //mesh.Update();
                m_EntityManager->Update();

                LateUpdate();
                Render();
            }
        }
    }
}