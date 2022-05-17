#include "EntityManager.h"



GameEngine::EntityManager* GameEngine::EntityManager::m_Instance = NULL;

 GameEngine::EntityManager* GameEngine::EntityManager::CreateInstance() {
	if (m_Instance == NULL) {m_Instance = new EntityManager();}
	return m_Instance;
}

 void GameEngine::EntityManager::Terminate() {
	 delete m_Instance;
	 m_Instance = NULL;
 }

GameEngine::EntityManager::EntityManager(){
    m_IdPool = GameEngine::IdGenerationPool::CreateInstance();

    /*componentLists["UnitDamage"].push_back(new UnitDamage(5.0f));

    UnitDamage* child = dynamic_cast<UnitDamage*>(componentLists.at("UnitDamage")[0]);
    std::cout << "Damage value:" << child->GetDamage() << std::endl;*/
}

GameEngine::EntityManager::~EntityManager() {
    delete m_IdPool;
    m_IdPool = NULL;
}


int GameEngine::EntityManager::CreateNewEntity(char* form, float x_pos, float y_pos , float z_pos) {
	std::cout << "New entity created " << std::endl;
    GameObject* entity = new GameObject();
    EntityList.insert({ entity->GetID(), entity});
    
    /*--------Load the json file---------*/
    std::ifstream testData("Data/EntityData.json");
    Json::Value actualJson;
    Json::Reader reader;

    // using the reader we parse the json 
    reader.parse(testData, actualJson);

    entity->GetTransform()->SetTransform(x_pos, y_pos, z_pos);

    /*------Take out the the info regarding which components to add.--------*/
    for (Json::Value::const_iterator itr = actualJson[form]["Components"].begin(); itr != actualJson[form]["Components"].end(); itr++) {
        BaseComponent* comp;
        int componentID = 0x00000000;
        if (itr->asCString() == (std::string) "UnitDamage") {
            comp = new UnitDamage(entity, actualJson[form]["Template"]["minDamage"].asFloat(), 
                actualJson[form]["Template"]["maxDamage"].asFloat());
            componentID = 0x00000001;
        }

        else if (itr->asCString() == (std::string)"UnitHealth") {
            comp = new UnitHealth(entity, actualJson[form]["Template"]["Health"].asFloat());
            componentID = 0x00000002;

        }

        else if (itr->asCString() == (std::string)"UnitMovement") {
            comp = new UnitMovement(entity, actualJson[form]["Template"]["Speed"].asFloat());
            componentID = 0x00000003;
        }

        else if (itr->asCString() == (std::string)"PathFinding") {
            std::string NavData = actualJson[form]["Template"]["Navmesh"].asCString();
            const char* NavDir = NavData.c_str();
            comp = new PathFinding(entity, NavDir);
            componentID = 0x00000004;
        }


        else if (itr->asCString() == (std::string)"Renderable") {
            std::string meshData = actualJson[form]["Template"]["Mesh"].asCString();
            const char* meshDir = meshData.c_str();
            std::string fragData = actualJson[form]["Template"]["fs_Shader"].asCString();
            const char* fragDir = fragData.c_str();
            std::string vertData = actualJson[form]["Template"]["vs_Shader"].asCString();
            const char* vertDir = vertData.c_str();

            comp = new Renderable(entity, meshDir, fragDir, vertDir);
            componentID = 0x00000006;
        }


        else if (itr->asCString() == (std::string)"Sound") {
            std::string data = actualJson[form]["Template"]["Sound"].asCString();
            const char* directory = data.c_str();
            comp = new Sound(entity);
            componentID = 0x00000007;
        }

        else if (itr->asCString() == (std::string)"StaticBody") {
            comp = new StaticBody(entity);
            componentID = 0x00000008;
        }

        else if (itr->asCString() == (std::string)"DynamicBody") {
            comp = new DynamicBody(entity);
            componentID = 0x00000009;
        }

        else if (itr->asCString() == (std::string)"Physics") {
            comp = new Physics(entity);
            componentID = 0x00000010;
        }
        
        else if (itr->asCString() == (std::string)"SphereCollider") {
            comp = new SphereCollider(entity, Vector3(x_pos, y_pos, z_pos), actualJson[form]["Template"]["Size"].asFloat());
            componentID = 0x00000011;
        }

        else if (itr->asCString() == (std::string)"Team") {
            comp = new Team(entity, actualJson[form]["Template"]["Team"].asInt());
            componentID = 0x00000012;
        }

        if (componentID != 0x00000000) {
            entity->AddComponent(componentID, comp);
        }
        
    }
    return entity->GetID();

}

void GameEngine::EntityManager::PlayAudio(int id) {
    Sound* child = dynamic_cast<Sound*>(EntityList.at(id));
    
    Mix_Music* music = child->Sound::LoadMusic("Audio/Music/Glorious_morning.wav");
    //std::map<std::string, Mix_Chunk*> audio = child->Sound::LoadChunk("Audio/SoundEffect/");
    
    child->Sound::PlayMusic(music, 26, -1);
    //child->Sound::PlayChunk(audio.at("test_Seq08"), 52, 0);
}

void GameEngine::EntityManager::TerminateEnity(int entityID) {
    /*--Delete the entity--*/
    if (GetEntity(entityID) == nullptr) {
        return;
    }
    delete EntityList.at(entityID);
    EntityList.at(entityID) = NULL;
    EntityList.erase(EntityList.find(entityID));
    
    /*---------------------*/
    
}


void GameEngine::EntityManager::EarlyUpdate() {
    for (auto entity : EntityList) {
        entity.second->EarlyUpdate();
    }
}

void GameEngine::EntityManager::Update() {
    for (auto entity : EntityList) {
        entity.second->Update();
    }
    std::map<int, GameObject*>::iterator control;
    std::map<int, GameObject*>::iterator check;
    std::vector<int> terminateList;
    for (control = EntityList.begin(); control != EntityList.end(); control++)
    {
        
        SphereCollider* sphereBase = dynamic_cast<SphereCollider*>(control->second->GetComponent(0x00000011));
        if (sphereBase == nullptr) {
            continue;
        }
        int turn = 0;
        for (check = EntityList.find(control->first); check != EntityList.end(); check++)
        {
            if (!turn) {
                turn = 1;
                continue;
            }
            SphereCollider* sphereCheck = dynamic_cast<SphereCollider*>(check->second->GetComponent(0x00000011));
            if (sphereCheck == nullptr) {
                continue;
            }
            if (sphereCheck->AreColliding(sphereBase)) {
                //--Find the amount that they are overlapping--
                Vector3 overlap = sphereCheck->GetOverlap(sphereBase);

                //--Take out the current movementspeed of the entitys--
                Vector3* controlMovement = dynamic_cast<DynamicBody*>(control->second->GetComponent(0x00000009))->GetMovement();
                Vector3* checkMovement = dynamic_cast<DynamicBody*>(check->second->GetComponent(0x00000009))->GetMovement();
                /*
                //--Take out the procentage of the colltion each entity contributed with--
                float xtot = std::abs(controlMovement->x) + std::abs(checkMovement->x);
                float controlProcentX = std::abs(controlMovement->x) / xtot;
                float checkProcentX = std::abs(checkMovement->x) / xtot;

                //--Move entitys away from one another--
                if (controlMovement->x > 0) {
                    control->second->GetTransform()->Translate(Vector3(-std::abs(controlProcentX * overlap.x), 0, 0));
                    check->second->GetTransform()->Translate(Vector3(std::abs(checkProcentX * overlap.x), 0, 0));

                }

                */

                if (dynamic_cast<Team*>(control->second->GetComponent(0x00000012))->GetTeam() !=
                    dynamic_cast<Team*>(check->second->GetComponent(0x00000012))->GetTeam()) {

                   UnitHealth* checkHealth = dynamic_cast<UnitHealth*>(check->second->GetComponent(0x00000002));
                   UnitHealth* controlHealth = dynamic_cast<UnitHealth*>(control->second->GetComponent(0x00000002));
                   controlHealth->DamageHealth(dynamic_cast<UnitDamage*>(check->second->GetComponent(0x00000001))->GetDamage());
                   checkHealth->DamageHealth(dynamic_cast<UnitDamage*>(control->second->GetComponent(0x00000001))->GetDamage());

                   if (checkHealth->GetHealth() <= 0) {
                       terminateList.push_back(check->first);
                   }

                   if (controlHealth->GetHealth() <= 0) {
                       terminateList.push_back(control->first);
                   }
                   
                    GameEngine::Log::GetClientLogger()->trace("enemy");
                }
                if (controlMovement != nullptr) {
                    controlMovement->x *= -1;
                    controlMovement->y *= -1;
                    controlMovement->z *= -1;
                }
                if(checkMovement != nullptr) {
                    checkMovement->x *= -1;
                    checkMovement->y *= -1;
                    checkMovement->z *= -1;
                }
                GameEngine::Log::GetClientLogger()->warn("colition");
            }

        }
    }
    for (int id : terminateList) {
        TerminateEnity(id);
    }
}

void GameEngine::EntityManager::LateUpdate() {
    for (auto entity : EntityList) {
        entity.second->LateUpdate();
    }
}

int GameEngine::EntityManager::GetNewID() {
    currentID += 1;
    return currentID;
}

GameEngine::GameObject* GameEngine::EntityManager::GetEntity(int id) {
    if (EntityList.count(id) == 0) {
        return nullptr;
    }
    return EntityList.at(id);

}


std::map<int, GameEngine::GameObject*>* GameEngine::EntityManager::GetList() {
    return &EntityList;
}

int GameEngine::EntityManager::GetID(int id, int direction) {

    __int64 position = std::distance(EntityList.begin(), EntityList.find(id));
    __int64 length = std::distance(EntityList.begin(), EntityList.end());
    //float value = EntityList.find(1);
    if (id == 0) {
        if (EntityList.size() == 0) {
            return 0;
        }

        return EntityList.begin()->first;
    }
    if (EntityList.size() == 1) {
        return EntityList.rbegin()->first;
         
    }

    if (GetEntity(id) == nullptr) {
        return  EntityList.rbegin()->first;
    }
    if (direction == 0) {//goes downwards

        if (position == 0) {
            return EntityList.rbegin()->first;
        }
        std::map<int, GameObject*>::iterator it;
        int next = 0;
        for (it = EntityList.find(id); it != EntityList.begin(); it--)
        {
            if (next == 0) {
                next = 1;
                continue;
            }
            return it->first;
        }
        return EntityList.begin()->first;
    }
    else if (direction == 1) {
        if (position == length-1) {
            return EntityList.begin() -> first;
        }

        std::map<int, GameObject*>::iterator it;
        int next = 0;
        for (it = EntityList.find(id); it != EntityList.end(); it++)
        {
            if (next == 0) {
                next = 1;
                continue;
            }
            return it->first;
        }
    }

    return id;
}