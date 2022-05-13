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
	
	if (m_manager->GetEntity(entityID) == nullptr) {
		std::cout << "The entity ID does not exist" << std::endl;
		return 0;
	}

	//does the comp exist
	if (m_manager->GetEntity(entityID)->GetComponent(compID) == nullptr) {
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

	std::cout << "Did "<< damage << " points of damage to the unit" << std::endl;
	UnitHealth* healthComp = dynamic_cast<UnitHealth*>(m_manager->GetEntity(id)->GetComponent(compID));
	healthComp->DamageHealth(damage);


	if (healthComp->GetHealth() <= 0) {	//Is the unit dead
		std::cout << "The unit died" << std::endl;
		m_manager->TerminateEnity(id);
	}
}

void GameEngine::Messenger::MoveUnit(int id, Vector3 translation) {
	int compID = 0x00000009;
	if (CheckStatus(id, compID) == 0) { return; }

	dynamic_cast<DynamicBody*>(m_manager->GetEntity(id)->GetComponent(0x00000009))->AddMovement(translation);

}

void GameEngine::Messenger::RotateUnit(int id, Vector3 translation) {
	int compID = 0x00000003;
	if (CheckStatus(id, compID) == 0) { return; }
	GameObject* entity = m_manager->GetEntity(id);

	UnitMovement* movementComp = dynamic_cast<UnitMovement*>(entity->GetComponent(compID));
	float speed = movementComp->GetMovement();

	translation = translation * (speed / 10);
	Transform* transform = entity->GetTransform();

	transform->Rotates(translation.x, translation.y, translation.z);
	std::cout << "move unit" << std::endl;
}

void GameEngine::Messenger::ChangeAudioState(int id) {
	int compID = 0x00000007;
	if (CheckStatus(id, compID) == 0) { return; }

	Sound* child = dynamic_cast<Sound*>(m_manager->GetEntity(id)->GetComponent(compID));

	if (child->Sound::IsMusicPlaying()) {
		child->Sound::PauseMusic();
	}
	else if (child->Sound::IsMusicPaused()) {
		child->Sound::UnpauseMusic();
	}
	
}


int GameEngine::Messenger::GetMouseID(float mouseX, float mouseY) {


	std::map<int, GameObject* >* tempList = m_manager->GetList(); 
	int rightAreaID = 0;
	float  rightAreaZ = 0;

	for (auto entity : *tempList) {
		if (CheckStatus(entity.first, 0x00000006) == 0) {
			continue;
		}
		Renderable* renderableComp = dynamic_cast<Renderable*>(entity.second->GetComponent(0x00000006));
		Vector3 boundingboxMin;
		Vector3 boundingboxMax;
		renderableComp->GetBoundingBox(&boundingboxMin, &boundingboxMax);

		

		if (!(boundingboxMin.x + -entity.second->GetTransform()->mtx[12] < mouseX)) {
			continue;
		}

		if (!(boundingboxMax.x + -entity.second->GetTransform()->mtx[12] > mouseX)) {
			continue;
		}

		if (!(boundingboxMin.y + entity.second->GetTransform()->mtx[13] < mouseY)) {
			continue;
		}

		if (!(boundingboxMax.y + entity.second->GetTransform()->mtx[13] > mouseY)) {
			continue;
		}


		if (rightAreaID == 0) {
			rightAreaID = entity.first;
			rightAreaZ = boundingboxMax.z + entity.second->GetTransform()->mtx[14];
		}
		else if (rightAreaZ < boundingboxMax.z + entity.second->GetTransform()->mtx[14]) {
			rightAreaID = entity.first;
			rightAreaZ = boundingboxMax.z + entity.second->GetTransform()->mtx[14];
		}
	}

	return rightAreaID;
}

