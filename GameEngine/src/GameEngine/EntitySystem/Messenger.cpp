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


bool GameEngine::Messenger::CheckStatus( int entityID, int compID) {
	GameObject* entity = m_manager->GetEntity(entityID);
	if (entity == nullptr) {
		std::cout << "The entity ID does not exist" << std::endl;
		return 0;
	}
	
	BaseComponent* comp = entity->GetComponent(compID);

	//does the comp exist
	if (comp == nullptr) {
		std::cout << "The Component does not exist in entity" << std::endl;
		return 0;
	}
	return 1;
}

/*--------------Class methords --------------*/

void GameEngine::Messenger::Terminate() {
	delete m_Instance;
	m_Instance = NULL;
}

void GameEngine::Messenger::DamageUnit(int id, float damage) {
	int compID = 0x00000002;
	if (CheckStatus( id, compID) == 0) {return;}
	GameObject* entity = m_manager->GetEntity(id);
	BaseComponent* comp = entity->GetComponent(compID);


	std::cout << "Did "<< damage << " points of damage to the unit" << std::endl;
	UnitHealth* healthComp = dynamic_cast<UnitHealth*>(comp);
	healthComp->DamageHealth(damage);


	if (healthComp->GetHealth() <= 0) {	//Is the unit dead
		std::cout << "The unit died" << std::endl;
		m_manager->TerminateEnity(id);
	}
}

void GameEngine::Messenger::MoveUnit(int id, Vector3 translation) {
	int compID = 0x00000003;
	if (CheckStatus(id, compID) == 0) { return; }
	GameObject* entity = m_manager->GetEntity(id);
	BaseComponent* comp = entity->GetComponent(compID);
	

	UnitMovement* movementComp = dynamic_cast<UnitMovement*>(comp);
	float speed = movementComp->GetMovement();

	translation = translation * (speed / 10);
	Transform* transform = entity->getTransform();
	
	transform->translate(translation);
	std::cout << "move unit" << std::endl;
	
		
	
}