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
        m_Camera = GameEngine::Camera::CreateInstance();
        m_Messenger = GameEngine::Messenger::CreateInstance();

        audio = m_EntityManager->CreateNewEntity("BackgroundMusic", 0, 0, 0);
    }


    GameEngine::Application::~Application() {
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

    GameEngine::Vector2 GameEngine::Application::GetRealCords() {
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

        return Vector2((float)out[0][0], (float)out[0][1]);
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
        float z = 0;
        float width = (tempview[3][2] - z) * tan(3.14f/4.0f);
        m_EntityManager->CreateNewEntity(name, out[0][0] * width + tempview[3][0], -out[0][1] * width + tempview[3][1], z);
        //m_EntityManager->CreateNewEntity("Peasant", out[0][0] * 10 * procent + tempview[3][0], -out[0][1] * 10 + tempview[3][1], 10-tempview[3][2]+ out[0][0]*10 * ( 1- procent));
    }

    void Application::EarlyUpdate() {
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
            m_Messenger->DamageUnit(selectedID, 2);
        }
        if (m_InputManager->KeyPressed(SDL_SCANCODE_T)) {
            GameEngine::Log::GetCoreLogger()->info("T terminate");
            m_EntityManager->TerminateEnity(selectedID);
        }

        if (m_InputManager->KeyPressed(SDL_SCANCODE_Z)) {
            GameEngine::Log::GetCoreLogger()->info("Z Change music state");
            m_Messenger->ChangeAudioState(audio);
        }

        if (m_InputManager->KeyPressed(SDL_SCANCODE_PAGEUP)) {
            GameEngine::Log::GetCoreLogger()->info("Page Up");
            selectedID = m_EntityManager->GetID(selectedID, 1);
        }   
        if (m_InputManager->KeyPressed(SDL_SCANCODE_PAGEDOWN)) {
            GameEngine::Log::GetCoreLogger()->info("Page Up");
            selectedID = m_EntityManager->GetID(selectedID, 0);
        }

        /*-------- left mouse ----------*/
        
        if (m_InputManager->MouseButtonPressed(GameEngine::InputManager::left)) {
            GameEngine::Log::GetCoreLogger()->info("left Mouse pressed");

            //std::cout << "modi pos "<< -GetRealCords().x << "  " << -GetRealCords().y << std::endl;
            int id = m_Messenger->GetMouseID(-GetRealCords().x * 10 , -GetRealCords().y  * 10);
            if (id != 0) {
                selectedID = id;
            }
        }
        if (m_InputManager->MouseButtonReleased(GameEngine::InputManager::left)) {
            GameEngine::Log::GetCoreLogger()->info("left Mouse released");
        }

        /*-----------Movement j/k/l/i-----------*/

        if (m_InputManager->Keydown(SDL_SCANCODE_J)) {
            GameEngine::Log::GetCoreLogger()->info("Move Left");
            if (selectedID != 0) {
                m_Messenger->MoveUnit(selectedID, Vector3(-1, 0, 0));
            }
        }
        if (m_InputManager->Keydown(SDL_SCANCODE_L)) {
            GameEngine::Log::GetCoreLogger()->info("Move Right");
            if (selectedID != 0) {
                m_Messenger->MoveUnit(selectedID, Vector3(1, 0, 0));
            }
        }

        if (m_InputManager->Keydown(SDL_SCANCODE_I)) {
            GameEngine::Log::GetCoreLogger()->info("Move Forward");
            if (selectedID != 0) {
                m_Messenger->MoveUnit(selectedID, Vector3(0, 0, 1));
            }
        }

        if (m_InputManager->Keydown(SDL_SCANCODE_K)) {
            GameEngine::Log::GetCoreLogger()->info("Move Back");
            if (selectedID != 0) {
                m_Messenger->MoveUnit(selectedID, Vector3(0, 0, -1));
            }
        }
        /*-----------Rotate u/o-----------*/
        if (m_InputManager->Keydown(SDL_SCANCODE_U)) {
            GameEngine::Log::GetCoreLogger()->info("Rotate Left");
            if (selectedID != 0) {
                m_Messenger->RotateUnit(selectedID, Vector3(0, 1, 0));
            }
        }
        if (m_InputManager->Keydown(SDL_SCANCODE_O)) {
            GameEngine::Log::GetCoreLogger()->info("Rotate Right");
            if (selectedID != 0) {
                m_Messenger->RotateUnit(selectedID, Vector3(0, -1, 0));
            }
        }
    }

    void Application::Render() {
        m_Graphics->Render();
    }

    void GameEngine::Application::LateUpdate() {
        m_Camera->Update(m_InputManager, 0, m_Graphics->Screen_Width, m_Graphics->Screen_Hight);
        m_EntityManager->Update();
        m_InputManager->UpdatePrevInput();
        m_Timer->Reset();
    }

    void GameEngine::Application::initUnit(int unitID, PathFinding* pathfindingComponent,EntityManager* m_EntityManager) {
        GameObject* unit = m_EntityManager->GetEntity(unitID);
        BaseComponent* pathfindingUnit = unit->GetComponent(0x00000004);
        PathFinding* pathfindingComponentUnit = dynamic_cast<PathFinding*>(pathfindingUnit);
        pathfindingComponentUnit->setNavMesh(pathfindingComponent->getNavMesh());
        pathfindingComponentUnit->Init();

    }

    void GameEngine::Application::Run() {
        m_Graphics->Initbgfx();  //WINDOW


        int worldID = m_EntityManager->CreateNewEntity("Worldmap", 0, 0, 0);
        GameObject* worldMap = m_EntityManager->GetEntity(worldID);
        BaseComponent* pathfinding = worldMap->GetComponent(0x00000004);
        PathFinding* pathfindingComponent = dynamic_cast<PathFinding*>(pathfinding);
        /*
       for (int i = 0; i < 30; i++) {
            int unitID = m_EntityManager->CreateNewEntity("Leader", -30, 5, 0);
            initUnit(unitID, pathfindingComponent, m_EntityManager);
        }
        for (int i = 0; i < 30; i++) {
            int unitID = m_EntityManager->CreateNewEntity("Peasant", 30, 0, 0);
            initUnit(unitID, pathfindingComponent, m_EntityManager);
        }*/
 
        for (int i = 0; i < 1000; i++) {
            int unitID = m_EntityManager->CreateNewEntity("Zombie", 0, 0, 0);
            initUnit(unitID, pathfindingComponent, m_EntityManager);
        }
        /*
        m_EntityManager->CreateNewEntity("Peasant", 0, 0, 0);
        m_EntityManager->CreateNewEntity("Peasant", -4, 0, 0);
        m_EntityManager->CreateNewEntity("Leader", 4, 0, 0);
       */


        m_EntityManager->PlayAudio(audio);

        SDL_Event currentEvent;
        while (!mQuit) {

            m_Timer->Update();

            if (SDL_PollEvent(&currentEvent) != 0) {
                if (currentEvent.type == SDL_QUIT) {
                    mQuit = true;
                }
            }

            if (m_Timer->getDeltaTime() >= 1.0f / frameRate) {
                //std::cout << (m_Timer->getDeltaTime() / frameRate) << std::endl;  //print the framerate
                EarlyUpdate();
                Update();
                LateUpdate();
                Render();
            }
        }

    }
}