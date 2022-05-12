#include "Physics.h"

GameEngine::Physics::Physics(GameObject* parent) : BaseComponent(parent) {
	std::cout << "create Physics" << std::endl; 
}

GameEngine::Physics::~Physics() {

}


GameEngine::Vector3 GameEngine::Physics::CalculateSpeed(GameEngine::Vector3 movement, float speed) {
	std::cout << "got to the physics" << std::endl;
}

void GameEngine::Physics::Update(){

}