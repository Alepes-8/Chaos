#include "Messenger.h"


GameEngine::Messenger* GameEngine::Messenger::m_Instance = NULL;
		
GameEngine::Messenger* GameEngine::Messenger::CreateInstance() {
	if (m_Instance == NULL) {
		m_Instance = new Messenger();
	}
	return m_Instance;
}

GameEngine::Messenger::Messenger() {

}
GameEngine::Messenger::~Messenger() {

}


void GameEngine::Messenger::Terminate() {
	delete m_Instance;
	m_Instance = NULL;
}

void GameEngine::Messenger::DamageUnit() {
	std::cout << "damage unit" << std::endl;
}

void GameEngine::Messenger::MoveUnit() {
	std::cout << "move unit" << std::endl;
}