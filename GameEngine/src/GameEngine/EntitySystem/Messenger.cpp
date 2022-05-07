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

void GameEngine::Messenger::RotateUnit(int id, Vector3 translation) {
	int compID = 0x00000003;
	if (CheckStatus(id, compID) == 0) { return; }
	GameObject* entity = m_manager->GetEntity(id);
	BaseComponent* comp = entity->GetComponent(compID);


	UnitMovement* movementComp = dynamic_cast<UnitMovement*>(comp);
	float speed = movementComp->GetMovement();

	translation = translation * (speed / 10);
	Transform* transform = entity->getTransform();

	transform->rotates(translation.x, translation.y, translation.z);
	std::cout << "move unit" << std::endl;
}




int GameEngine::Messenger::GetID(float mouseX, float mouseY) {
	std::cout << "x,y mouse; = " << mouseX << " , " << mouseY << std::endl;


	std::map<int, GameObject* >* tempList = m_manager->GetList(); 
	int rightAreaID = 0;
	float  rightAreaZ = 0;

	for (auto entity : *tempList) {
		std::cout << entity.first << std::endl;
		if (CheckStatus(entity.first, 0x00000006) == 0) {
			continue;
		}
		BaseComponent* comp = entity.second->GetComponent(0x00000006);
		Renderable* renderableComp = dynamic_cast<Renderable*>(comp);
		Vector3 boundingboxMin;
		Vector3 boundingboxMax;
		renderableComp->GetBoundingBox(&boundingboxMin, &boundingboxMax);

		

		if (!(boundingboxMin.x + -entity.second->getTransform()->mtx[12] < mouseX)) {
			continue;
		}

		if (!(boundingboxMax.x + -entity.second->getTransform()->mtx[12] > mouseX)) {
			continue;
		}

		if (!(boundingboxMin.y + entity.second->getTransform()->mtx[13] < mouseY)) {
			continue;
		}

		if (!(boundingboxMax.y + entity.second->getTransform()->mtx[13] > mouseY)) {
			continue;
		}


		if (rightAreaID == 0) {
			rightAreaID = entity.first;
			rightAreaZ = boundingboxMax.z + entity.second->getTransform()->mtx[14];
		}
		else if (rightAreaZ < boundingboxMax.z + entity.second->getTransform()->mtx[14]) {
			rightAreaID = entity.first;
			rightAreaZ = boundingboxMax.z + entity.second->getTransform()->mtx[14];
		}
	}

	return rightAreaID;
}

