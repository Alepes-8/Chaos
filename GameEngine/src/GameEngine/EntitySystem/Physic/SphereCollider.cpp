#include "SphereCollider.h"

//WORK IN PROGRESS

GameEngine::SphereCollider::SphereCollider(GameObject* parent, Vector3 origin, float radius) : BaseComponent(parent)
{
	transform = getParentTransform();
	this->origin = origin;
	this->radius = radius/2;
	std::cout << "create sphere colider" << std::endl;
}

bool GameEngine::SphereCollider::AreColliding(SphereCollider* control) {
	
	if ( (std::sqrt(std::pow((origin.x - control->GetPosition().x),2 ) + 
		std::pow((origin.y - control->GetPosition().y),2) +
		std::pow((origin.z - control->GetPosition().z),2))) <
		(std::pow((control->GetRadius() + this->radius),2)))
	{
		return true;
	}
	return false;
}

float GameEngine::SphereCollider::GetRadius() {
	return this->radius;
}

GameEngine::Vector3 GameEngine::SphereCollider::GetPosition() {
	return this->origin;
}

void GameEngine::SphereCollider::Update() {
	//TODO
	origin.x = transform->getPosition().pos[0];
	origin.y = transform->getPosition().pos[1]+radius;
	origin.z = transform->getPosition().pos[2];
}

GameEngine::Vector3 GameEngine::SphereCollider::GetOverlap(SphereCollider* control) {
	return 
		Vector3(
		std::abs(origin.x - control->GetPosition().x), 
		std::abs(origin.y - control->GetPosition().y), 
		std::abs(origin.z - control->GetPosition().z)
		);
}