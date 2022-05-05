#include "Messenger.h"


/*------------Init Constructur && distructur---------------*/
GameEngine::Messenger* GameEngine::Messenger::m_Instance = NULL;
		
GameEngine::Messenger* GameEngine::Messenger::CreateInstance() {
	if (m_Instance == NULL) {
		m_Instance = new Messenger();
	}
	return m_Instance;
}

GameEngine::Messenger::Messenger() {
	m_manager = GameEngine::EntityManager::CreateInstance();
}
GameEngine::Messenger::~Messenger() {
	std::cout << "delete messenger" << std::endl;
}

/*--------------Class methords --------------*/

void GameEngine::Messenger::Terminate() {
	delete m_Instance;
	m_Instance = NULL;
}

void GameEngine::Messenger::DamageUnit(int id, float damage) {
	GameObject* entity = m_manager->GetEntity(id);
	if (entity == nullptr) {
		std::cout << "The entity ID does not exist" << std::endl;
	}
	else {
		BaseComponent* comp = entity->GetComponent(0x00000002);

		//does the comp exist
		if (comp == nullptr ) {	
			std::cout << "The Component does not exist in entity" << std::endl;
		}
		else {
			std::cout << "Did "<< damage << " points of damage to the unit" << std::endl;
			UnitHealth* healthComp = dynamic_cast<UnitHealth*>(comp);
			healthComp->DamageHealth(damage);
			if (healthComp->GetHealth() <= 0) {	//Is the unit dead
				std::cout << "The unit died" << std::endl;
				m_manager->TerminateEnity(id);
			}
		}
	}
}

void GameEngine::Messenger::MoveUnit() {
	std::cout << "move unit" << std::endl;
}