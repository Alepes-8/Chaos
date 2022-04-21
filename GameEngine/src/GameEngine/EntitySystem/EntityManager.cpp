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
	
	//create a entitylist
}

GameEngine::EntityManager::~EntityManager() {
	//delete the entitylist
	//set the entitylist ass NULL
	
}
void GameEngine::EntityManager::PrintList() {
    std::cout << "The length of the current EntityList is " 
        << EntityList.size() << " long" << std::endl;
}

void GameEngine::EntityManager::CreateNewEntity(char* form , char* type) {
	std::cout << "create new entity " << std::endl;

    std::ifstream testData("Data/testData.json");
    Json::Value actualJson;
    Json::Reader reader;


    // using the reader we parse the json 
    reader.parse(testData, actualJson);

    //now the acualJson will have json data
    //std::cout <<  actualJson << std::endl;
    char* types = "Leader";
    //acceesssing the specific data parts
    std::cout << "The " << types << " entity has the following components:" << std::endl;

    for (Json::Value::const_iterator itr = actualJson["Unit"]["Components"].begin(); itr != actualJson["Unit"]["Components"].end(); itr++) {
        std::cout << "  -" << itr->asCString() << std::endl;
    }
    std::cout << "\n Then the following stats:" << std::endl;

    for (Json::Value::const_iterator itr = actualJson["Unit"]["Type"]["Peasant"].begin(); itr != actualJson["Unit"]["Type"]["Peasant"].end(); itr++) {
        std::cout << "  -" << itr.key() << ": " << itr->asInt() << std::endl;
    }
}
