#include "Physics.h"

GameEngine::Physics::Physics(GameObject* parent) : BaseComponent(parent) {
	std::cout << "create Physics" << std::endl; 
}

GameEngine::Physics::~Physics() {

}


GameEngine::Vector3 GameEngine::Physics::CalculateSpeed(GameEngine::Vector3 movement, float speed) {
	m_ElipsedTime = SDL_GetTicks() - m_StartTicks;	//time between the last reset and time right now
	m_DeltaTime = m_ElipsedTime * 0.001f;

	if (std::abs(movement.x) > 0) {
		if (movement.x > 0) {
			movement.x += (-speed * m_friction * m_DeltaTime);
		}
		else if (movement.x < 0) {
			movement.x += (speed * m_friction * m_DeltaTime);
		}

		if (movement.x > 0 && movement.x < 0.01) {
			movement.x = 0;
		}
		if (movement.x< 0 && movement.x>-0.01) {
			movement.x = 0;
		}

	}

	if (std::abs(movement.y) > 0) {
		if (movement.y > 0) {
			movement.y += (-speed * m_friction * m_DeltaTime);
		}
		else if (movement.y < 0) {
			movement.y += (speed * m_friction * m_DeltaTime);
		}

		if (movement.y > 0 && movement.y < 0.01) {
			movement.y = 0;
		}
		if (movement.y< 0 && movement.y>-0.01) {
			movement.y = 0;
		}

	}

	if (std::abs(movement.z) > 0) {
		if (movement.z > 0) {
			movement.z += (-speed * m_friction * m_DeltaTime);
		}
		else if (movement.z < 0) {
			movement.z += (speed * m_friction * m_DeltaTime);
		}

		if (movement.z > 0 && movement.z < 0.01) {
			movement.z = 0;
		}
		if (movement.z< 0 && movement.z>-0.01) {
			movement.z = 0;
		}

	}

	ResetTime();
	return movement;
}

GameEngine::Vector3 GameEngine::Physics::CalculateAcceleration(Vector3 movement, Vector3 direction, float speed) {

	m_ElipsedTime = SDL_GetTicks() - m_StartTicks;	//time between the last reset and time right now
	m_DeltaTime = m_ElipsedTime * 0.001f;

	movement.x += speed * direction.x;
	movement.x += (-movement.x * m_friction * m_DeltaTime);
	movement.y += speed * direction.y;
	movement.y += (-movement.y * m_friction * m_DeltaTime);
	movement.z += speed * direction.z;
	movement.z += (-movement.z * m_friction * m_DeltaTime);

	ResetTime();
	return movement;
}

void GameEngine::Physics::ResetTime() {
	m_StartTicks = SDL_GetTicks();
	m_DeltaTime = 0.0f;
}
void GameEngine::Physics::Update(){

}