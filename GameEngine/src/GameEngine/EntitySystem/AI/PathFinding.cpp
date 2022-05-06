#include "PathFinding.h"


GameEngine::PathFinding::PathFinding(GameObject* parent) : BaseComponent(parent) {
	std::cout << "Create PathFinding" << std::endl;
}
GameEngine::PathFinding::~PathFinding() {
	std::cout << "Delete PathFinding" << std::endl;
}

void GameEngine::PathFinding::Update() {
}
