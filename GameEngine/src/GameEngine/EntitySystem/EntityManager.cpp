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

void GameEngine::EntityManager::CreateNewEntity() {
	std::cout << "create new entity " << std::endl;
}
