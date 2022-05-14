#include <GameEngine/EntitySystem/Physic/SphereCollider.h>

//WORK IN PROGRESS

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

bool GameEngine::SphereCollider::AreColliding(Collider& c) {
	if (SphereCollider* sc = dynamic_cast<SphereCollider*>(&c)) {
		float distance = (sc->GetOrigine() - this->GetOrigine()).MagnitudeSqr() - sc->GetRadius() - this->GetRadius();
		if (distance < 0) return true;
	}
	else if (BoxCollider* bc = dynamic_cast<BoxCollider*>(&c)) {
		Vector3 dist = (bc->getOrigine() - this->origine).Magnitude();
		Vector3 bc_scale = bc->getScale();
		return
			dist.x < radius + bc_scale.x &&
			dist.y < radius + bc_scale.y &&
			dist.z < radius + bc_scale.z;
	}

	return false;
}

void GameEngine::SphereCollider::Update() {
	std::cout << "Sphere Collider test" << std::endl;
	//TODO
}