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

    bool gluInvertMatrix(const float m[16], float invOut[16])
    {
        float inv[16], det;
        int i;

        inv[0] = m[5] * m[10] * m[15] -
            m[5] * m[11] * m[14] -
            m[9] * m[6] * m[15] +
            m[9] * m[7] * m[14] +
            m[13] * m[6] * m[11] -
            m[13] * m[7] * m[10];

        inv[4] = -m[4] * m[10] * m[15] +
            m[4] * m[11] * m[14] +
            m[8] * m[6] * m[15] -
            m[8] * m[7] * m[14] -
            m[12] * m[6] * m[11] +
            m[12] * m[7] * m[10];

        inv[8] = m[4] * m[9] * m[15] -
            m[4] * m[11] * m[13] -
            m[8] * m[5] * m[15] +
            m[8] * m[7] * m[13] +
            m[12] * m[5] * m[11] -
            m[12] * m[7] * m[9];

        inv[12] = -m[4] * m[9] * m[14] +
            m[4] * m[10] * m[13] +
            m[8] * m[5] * m[14] -
            m[8] * m[6] * m[13] -
            m[12] * m[5] * m[10] +
            m[12] * m[6] * m[9];

        inv[1] = -m[1] * m[10] * m[15] +
        m[1] * m[11] * m[14] +
        m[9] * m[2] * m[15] -
        m[9] * m[3] * m[14] -
        m[13] * m[2] * m[11] +
        m[13] * m[3] * m[10];

        inv[5] = m[0] * m[10] * m[15] -
        m[0] * m[11] * m[14] -
        m[8] * m[2] * m[15] +
        m[8] * m[3] * m[14] +
        m[12] * m[2] * m[11] -
        m[12] * m[3] * m[10];

        inv[9] = -m[0] * m[9] * m[15] +
        m[0] * m[11] * m[13] +
        m[8] * m[1] * m[15] -
        m[8] * m[3] * m[13] -
        m[12] * m[1] * m[11] +
        m[12] * m[3] * m[9];

        inv[13] = m[0] * m[9] * m[14] -
        m[0] * m[10] * m[13] -
        m[8] * m[1] * m[14] +
        m[8] * m[2] * m[13] +
        m[12] * m[1] * m[10] -
        m[12] * m[2] * m[9];

        inv[2] = m[1] * m[6] * m[15] -
        m[1] * m[7] * m[14] -
        m[5] * m[2] * m[15] +
        m[5] * m[3] * m[14] +
        m[13] * m[2] * m[7] -
        m[13] * m[3] * m[6];


        inv[6] = -m[0] * m[6] * m[15] +
        m[0] * m[7] * m[14] +
        m[4] * m[2] * m[15] -
        m[4] * m[3] * m[14] -
        m[12] * m[2] * m[7] +
        m[12] * m[3] * m[6];

        inv[10] = m[0] * m[5] * m[15] -
        m[0] * m[7] * m[13] -
        m[4] * m[1] * m[15] +
        m[4] * m[3] * m[13] +
        m[12] * m[1] * m[7] -
        m[12] * m[3] * m[5];

        inv[14] = -m[0] * m[5] * m[14] +
        m[0] * m[6] * m[13] +
        m[4] * m[1] * m[14] -
        m[4] * m[2] * m[13] -
        m[12] * m[1] * m[6] +
        m[12] * m[2] * m[5];

        inv[3] = -m[1] * m[6] * m[11] +
        m[1] * m[7] * m[10] +
        m[5] * m[2] * m[11] -
        m[5] * m[3] * m[10] -
        m[9] * m[2] * m[7] +
        m[9] * m[3] * m[6];

        inv[7] = m[0] * m[6] * m[11] -
        m[0] * m[7] * m[10] -
        m[4] * m[2] * m[11] +
        m[4] * m[3] * m[10] +
        m[8] * m[2] * m[7] -
        m[8] * m[3] * m[6];

        inv[11] = -m[0] * m[5] * m[11] +
        m[0] * m[7] * m[9] +
        m[4] * m[1] * m[11] -
        m[4] * m[3] * m[9] -
        m[8] * m[1] * m[7] +
        m[8] * m[3] * m[5];

        inv[15] = m[0] * m[5] * m[10] -
        m[0] * m[6] * m[9] -
        m[4] * m[1] * m[10] +
        m[4] * m[2] * m[9] +
        m[8] * m[1] * m[6] -
        m[8] * m[2] * m[5];

        det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];

        if (det == 0)
        return false;

        det = 1.0 / det;

        for (i = 0; i < 16; i++)
            invOut[i] = inv[i] * det;

        return true;
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

        gluInvertMatrix(m_Camera->_view, invview);
        gluInvertMatrix(m_Camera->_proj, invproj);

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
        m_EntityManager->CreateNewEntity(name, out[0][0] * 10 * procent, -out[0][1] * 10, 0);
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
            m_Messenger->DamageUnit();
        }
        if (m_InputManager->KeyPressed(SDL_SCANCODE_O)) {
            GameEngine::Log::GetCoreLogger()->info("O print list");
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