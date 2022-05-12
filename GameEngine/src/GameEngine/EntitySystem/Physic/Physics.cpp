#include "Physics.h"

GameEngine::Physics::Physics(GameObject* parent) : BaseComponent(parent) {
	std::cout << "create Physics" << std::endl; 
}

GameEngine::Physics::~Physics() {

}


GameEngine::Vector3 GameEngine::Physics::CalculateSpeed(GameEngine::Vector3 movement, float speed) {
	std::cout << "got to the physics" << std::endl;

	if (movement.x > 0) {
		movement.x -= 0.005;
		if (movement.x < 0.01) {
			movement.x = 0;
		}
	}

	if (movement.y > 0) {
		movement.y -= 0.005;
		if (movement.y < 0.01) {
			movement.y = 0;
		}
	}

	if (movement.z > 0) {
		movement.z -= 0.005;
		if (movement.z < 0.01) {
			movement.z = 0;
		}
	}

	if (movement.x < 0) {
		movement.x += 0.005;
		if (movement.x > -0.01) {
			movement.x = 0;
		}
	}

	if (movement.y < 0) {
		movement.y += 0.005;
		if (movement.y > -0.01) {
			movement.y = 0;
		}
	}

	if (movement.z < 0) {
		movement.z += 0.005;
		if (movement.z > -0.01) {
			movement.z = 0;
		}
	}
	return movement;
}

void GameEngine::Physics::Update(){

}