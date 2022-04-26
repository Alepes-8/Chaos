#include "UnitHealth.h"

GameEngine::UnitHealth::UnitHealth() {
	health = 5.0f;
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