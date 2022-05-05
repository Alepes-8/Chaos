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
        std::cout << "start application" << std::endl;

        GameEngine::Log::Init();

        m_InputManager = GameEngine::InputManager::CreateInstance();

        mQuit = false;
        m_Timer = GameEngine::Timer::CreateInstance();

        m_Graphics = GameEngine::Graphics::CreateInstance();
        if (!GameEngine::Graphics::GetInitialize()) { mQuit = true; }

        m_EntityManager = GameEngine::EntityManager::CreateInstance();
        m_Camera = GameEngine::Camera::CreateInstance();
        m_Messenger = GameEngine::Messenger::CreateInstance();

    }


    Application::~Application() {
        GameEngine::InputManager::Terminate();
        GameEngine::Timer::Terminate();
        GameEngine::Graphics::Terminate();
        GameEngine::EntityManager::Terminate();
        GameEngine::Camera::Terminate();
        GameEngine::Messenger::Terminate();

        m_InputManager = NULL;
        m_Timer = NULL;
        m_Graphics = NULL;
        m_EntityManager = NULL;
        m_Camera = NULL;
        m_Messenger = NULL;
    }


    void GameEngine::Application::CallCreation(char* name) {
        float y = (m_InputManager->MousePos().y / (float)m_Graphics->Screen_Hight) * 2 - 1;
        float x = (m_InputManager->MousePos().x / (float)m_Graphics->Screen_Width) * 2 - 1;
        float vert[4][1];
        vert[0][0] = x;
        vert[0][1] = y;
        vert[0][2] = 1;
        vert[0][3] = 0;

        float invview[16];
        float invproj[16];
        
        MathHelper* math = new MathHelper();
        math->InvMatrix(m_Camera->_view, invview);
        math->InvMatrix(m_Camera->_proj, invproj);
        delete math;

        float tempview[4][4];
        float tempproj[4][4];
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                tempview[i][j] = invview[i * 4 + j];
                tempproj[i][j] = invproj[i * 4 + j];
            }
        }

        float mid[1][4] = { 0,0,0,0 };
        float out[1][4] = { 0,0,0,0 };

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                mid[0][i] += vert[0][j] * tempview[j][i];
            }
        }

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                out[0][i] += mid[0][j] * tempproj[j][i];
            }
        }

        float procent = tempview[3][2] / 10.0f;
        m_EntityManager->CreateNewEntity(name, out[0][0] * 10 * procent + tempview[3][0], -out[0][1] * 10 + tempview[3][1], 0);
        //m_EntityManager->CreateNewEntity("Peasant", out[0][0] * 10 * procent + tempview[3][0], -out[0][1] * 10 + tempview[3][1], 10-tempview[3][2]+ out[0][0]*10 * ( 1- procent));
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
            CallCreation("Leader");
        }
        if (m_InputManager->KeyReleased(SDL_SCANCODE_W)) {
            GameEngine::Log::GetCoreLogger()->info("W Released");
        }
        if (m_InputManager->KeyPressed(SDL_SCANCODE_C)) {
            GameEngine::Log::GetCoreLogger()->info("C Create");
            CallCreation("Peasant");
        }
        if (m_InputManager->KeyPressed(SDL_SCANCODE_D)) {
            GameEngine::Log::GetCoreLogger()->info("D print");
            m_Messenger->DamageUnit(1, 2);
        }
        if (m_InputManager->KeyPressed(SDL_SCANCODE_T)) {
            GameEngine::Log::GetCoreLogger()->info("T terminate");
            m_EntityManager->TerminateEnity(1);
        }

        /*-------- left mouse ----------*/
        if (m_InputManager->MouseButtonDown(GameEngine::InputManager::left)) {
            GameEngine::Log::GetCoreLogger()->info("left Mouse down");
        }
        if (m_InputManager->MouseButtonPressed(GameEngine::InputManager::left)) {
            GameEngine::Log::GetCoreLogger()->info("left Mouse pressed");
        }
        if (m_InputManager->MouseButtonReleased(GameEngine::InputManager::left)) {
            GameEngine::Log::GetCoreLogger()->info("left Mouse released");
        }

        /*-----------arrow pad-----------*/

        if (m_InputManager->Keydown(SDL_SCANCODE_J)) {
            GameEngine::Log::GetCoreLogger()->info("Move Left");
            m_Messenger->MoveUnit(1, Vector3(-1, 0, 0));
        }
        if (m_InputManager->Keydown(SDL_SCANCODE_L)) {
            GameEngine::Log::GetCoreLogger()->info("Move Right");
            m_Messenger->MoveUnit(1, Vector3(1, 0, 0));
        }
        if (m_InputManager->Keydown(SDL_SCANCODE_I)) {
            GameEngine::Log::GetCoreLogger()->info("Move Forward");
            m_Messenger->MoveUnit(1, Vector3(0, 0, 1));
        }
        if (m_InputManager->Keydown(SDL_SCANCODE_K)) {
            GameEngine::Log::GetCoreLogger()->info("Move Back");
            m_Messenger->MoveUnit(1, Vector3(0, 0, -1));
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

        //--------------------LOOP---------------------//
        // Poll for events and wait till user closes window
        m_EntityManager->CreateNewEntity("Leader", 0,-5, 0);


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