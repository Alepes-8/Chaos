#include <GameEngine/EntitySystem/Physic/SphereCollider.h>

GameEngine::SphereCollider::SphereCollider(
	GameObject* parent,
	Vector3 origine = Vector3(0, 0, 0),
	float radius = 0
) : Collider(parent)
{
	this->origine = origine;
	if (radius < 0) {
		this->radius = 1;
		GameEngine::Log::GetCoreLogger()->warn("Radius has to be postive or null, Radius set up to 1");
	}
	else {
		this->radius = radius;
	}
}

bool GameEngine::SphereCollider::areColliding(Collider& c) {
	if (SphereCollider* sc = dynamic_cast<SphereCollider*>(&c)) {
		float distance = (sc->getOrigine() - this->getOrigine()).MagnitudeSqr() - sc->getRadius() - this->getRadius();
		if (distance < 0) return true;
	}
	else if (BoxCollider* bc = dynamic_cast<BoxCollider*>(&c)) {
		
	}
	return false;
}

void GameEngine::SphereCollider::Update() {
	std::cout << "Sphere Collider test" << std::endl;
	//TODO
}