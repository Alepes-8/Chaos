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

    componentLists.insert(std::pair<std::string, std::vector<BaseComponent*> >("UnitDamage", std::vector<BaseComponent*>()));
    componentLists.insert(std::pair<std::string, std::vector<BaseComponent*> >("UnitHealth", std::vector<BaseComponent*>()));
    componentLists.insert(std::pair<std::string, std::vector<BaseComponent*> >("UnitMovement", std::vector<BaseComponent*>()));
    componentLists.insert(std::pair<std::string, std::vector<BaseComponent*> >("PathFinding", std::vector<BaseComponent*>()));
    componentLists.insert(std::pair<std::string, std::vector<BaseComponent*> >("Sound", std::vector<BaseComponent*>()));

    /*componentLists["UnitDamage"].push_back(new UnitDamage(5.0f));

    UnitDamage* child = dynamic_cast<UnitDamage*>(componentLists.at("UnitDamage")[0]);
    std::cout << "Damage value:" << child->GetDamage() << std::endl;*/
}

GameEngine::EntityManager::~EntityManager() {}

void GameEngine::EntityManager::PrintList() {
    std::cout << "The length of the current EntityList is " 
     << EntityList.size() << " long" << std::endl;
}

void GameEngine::EntityManager::CreateNewEntity(char* form) {
	std::cout << "New entity created " << std::endl;

    GameObject* entity = new GameObject(GetNewID());
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

        if (itr->asCString() == (std::string) "UnitDamage") {
            comp = new UnitDamage(actualJson[form]["Template"]["Damage"].asFloat());
        }

        else if (itr->asCString() == (std::string)"UnitHealth") {
            comp = new UnitHealth(actualJson[form]["Template"]["Health"].asFloat());
        }

        else if (itr->asCString() == (std::string)"UnitMovement") {
            comp = new UnitMovement(actualJson[form]["Template"]["Speed"].asFloat());
        }

        if (itr->asCString() == (std::string)"PathFinding") {
            comp = new PathFinding();
        }

        if (itr->asCString() == (std::string)"Sound") {
            std::string data = actualJson[form]["Template"]["Sound"].asCString();
            const char* directory = data.c_str();
            comp = new Sound(directory);
        }

        BaseComponent** ptr = &comp;
        componentLists[itr->asCString()].push_back(comp);
        entity->components.insert({ itr->asCString(), ptr, });
    }

}

void GameEngine::EntityManager::TerminateEnity(int entityID) {
    /*--delete components--*/
    EntityList.at(entityID)->Terminate();
    /*---------------------*/
    /*---Delete pointers---*/

    /*---------------------*/
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