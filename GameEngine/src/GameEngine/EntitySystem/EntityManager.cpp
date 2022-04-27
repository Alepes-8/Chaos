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


    /*componentLists["UnitDamage"].push_back(new UnitDamage(5.0f));

    UnitDamage* child = dynamic_cast<UnitDamage*>(componentLists.at("UnitDamage")[0]);
    std::cout << "Damage value:" << child->GetDamage() << std::endl;*/
}

GameEngine::EntityManager::~EntityManager() {}

void GameEngine::EntityManager::PrintList() {
    std::cout << "The length of the current EntityList is " 
     << EntityList.size() << " long" << std::endl;
}

int GameEngine::EntityManager::CreateNewEntity(char* form) {
	std::cout << "New entity created " << std::endl;
    int ID = GetNewID();
    GameObject* entity = new GameObject(ID);
    EntityList.insert({ entity->ID, entity, });
    
    /*--------Load the json file---------*/
    std::ifstream testData("Data/EntityData.json");
    Json::Value actualJson;
    Json::Reader reader;

    // using the reader we parse the json 
    reader.parse(testData, actualJson);

    /*------Take out the the info regarding which components to add.--------*/
    for (Json::Value::const_iterator itr = actualJson[form]["Components"].begin(); itr != actualJson[form]["Components"].end(); itr++) {
        BaseComponent* comp;
        int componentID = 0x00000000;
        if (itr->asCString() == (std::string) "UnitDamage") {
            comp = new UnitDamage(actualJson[form]["Template"]["Damage"].asFloat());
            componentID = 0x00000001;
        }

        else if (itr->asCString() == (std::string)"UnitHealth") {
            comp = new UnitHealth(actualJson[form]["Template"]["Health"].asFloat());
            componentID = 0x00000002;

        }

        else if (itr->asCString() == (std::string)"UnitMovement") {
            comp = new UnitMovement(actualJson[form]["Template"]["Speed"].asFloat());
            componentID = 0x00000003;

        }

        else if (itr->asCString() == (std::string)"PathFinding") {
            comp = new PathFinding();
            componentID = 0x00000004;

        }

        else if (itr->asCString() == (std::string)"Transform") {
            comp = new Transform();
            componentID = 0x00000005;

        }

        else if (itr->asCString() == (std::string)"Renderable") {
            comp = new Renderable();
            componentID = 0x00000006;

        }

        else if (itr->asCString() == (std::string)"ConstantBody") {
            comp = new ConstantBody();
            componentID = 0x00000007;

        }

        else if (itr->asCString() == (std::string)"Sound") {
            std::string data = actualJson[form]["Template"]["Sound"].asCString();
            const char* directory = data.c_str();
            comp = new Sound(directory);
            componentID = 0x00000008;

        }
        if (componentID != 0x00000000) {
            entity->components.insert({ componentID, comp, });
        }
        
    }
    return ID;

}

void GameEngine::EntityManager::TerminateEnity(int entityID) {
    /*--Delete the entity--*/
    delete EntityList.at(entityID);
    EntityList.at(entityID) = NULL;
    EntityList.erase(entityID);
    /*---------------------*/
    
}


void GameEngine::EntityManager::PrintFirstEntity() {
    EntityList[0]->PrintList();
}

int GameEngine::EntityManager::GetNewID() {
    currentID += 1;
    return currentID;
}