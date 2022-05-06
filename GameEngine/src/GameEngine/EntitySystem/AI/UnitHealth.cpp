#include "UnitHealth.h"

GameEngine::UnitHealth::UnitHealth(GameObject* parent, float initHealth) : BaseComponent(parent) {
	std::cout << "create health" << initHealth << std::endl;
	health = initHealth;
}

GameEngine::UnitHealth::~UnitHealth() {
	std::cout << "delete health"  << std::endl;

	health = NULL;
}

float GameEngine::UnitHealth::GetHealth() {
	return health;
}

void GameEngine::UnitHealth::DamageHealth(float change) {
	health -= change;
}

void GameEngine::UnitHealth::HealHealth(float change){
	health += change;
}

void GameEngine::UnitHealth::Update() {
}