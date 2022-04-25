#include "UnitHealth.h"

GameEngine::UnitHealth::UnitHealth(float initHealth) {
	std::cout << "create health" << initHealth << std::endl;
	health = initHealth;
}

GameEngine::UnitHealth::~UnitHealth() {
	health = NULL;
}

float GameEngine::UnitHealth::GetHealth() {
	return health;
}

void GameEngine::UnitHealth::EditHealth(float change) {
	health += change;
}

void GameEngine::UnitHealth::Update() {
	std::cout << "Update UnitHealth" << std::endl;
}