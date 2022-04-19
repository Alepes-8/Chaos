#include "UnitMovement.h"

GameEngine::UnitMovement::UnitMovement() {
	movement = 2.0f;
}

GameEngine::UnitMovement::~UnitMovement() {
	movement = NULL;
}

float GameEngine::UnitMovement::GetMovement() {
	return movement;
}