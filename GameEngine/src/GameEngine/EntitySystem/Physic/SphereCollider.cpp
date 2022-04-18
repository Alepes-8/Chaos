#include <GameEngine/EntitySystem/Physic/SphereCollider.h>

GameEngine::SphereCollider::SphereCollider(
	Vector3 origine = Vector3(0, 0, 0),
	float radius = 0
) {
	this->origine = origine;
	if (radius < 0) {
		this->radius = 1;
		GameEngine::Log::GetCoreLogger()->warn("Radius has to be postive or null, Radius set up to 1");
	}
	else {
		this->radius = radius;
	}
}

bool GameEngine::SphereCollider::areColliding(const Collider& c) {
	//TODO
	return false;
}

void GameEngine::SphereCollider::update() {
	std::cout << "Sphere Collider test" << std::endl;
	//TODO
}