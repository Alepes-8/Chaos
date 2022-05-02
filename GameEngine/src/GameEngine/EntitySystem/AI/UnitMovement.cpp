#include "UnitMovement.h"

GameEngine::UnitMovement::UnitMovement(float initSpeed) {
	std::cout << "Movement create " << initSpeed << std::endl;
	movement = initSpeed;
}

GameEngine::UnitMovement::~UnitMovement() {
	std::cout << "Movement delete "<< std::endl;
	movement = NULL;
}

float GameEngine::UnitMovement::GetMovement() {
	return movement;
}

void GameEngine::UnitMovement::Update() {
}