#include "SphereCollider.h"

//WORK IN PROGRESS

GameEngine::SphereCollider::SphereCollider(GameObject* parent, Vector3 origin, float radius) : BaseComponent(parent)
{
	transform = getParentTransform();
	this->origin = origin;
	this->radius = radius;
	std::cout << "create sphere colider" << std::endl;
}

bool GameEngine::SphereCollider::AreColliding(SphereCollider* control) {
	std::cout << this->origin.x << " " << this->origin.y << " " << this->origin.z << std::endl;

	return false;
}

void GameEngine::SphereCollider::Update() {
	//TODO
	origin.x = transform->getPosition().pos[0];
	origin.y = transform->getPosition().pos[1];
	origin.z = transform->getPosition().pos[2];
}