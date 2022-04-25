#include "UnitMovement.h"

GameEngine::UnitMovement::UnitMovement(float initSpeed) {
	movement = 2.0f;
}

GameEngine::UnitMovement::~UnitMovement() {
	movement = NULL;
}

float GameEngine::UnitMovement::GetMovement() {
	return movement;
}

void GameEngine::UnitMovement::Update() {
	std::cout << "Update UnitMovement" << std::endl;
}