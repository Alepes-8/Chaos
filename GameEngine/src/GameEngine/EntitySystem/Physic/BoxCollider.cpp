#include <GameEngine/EntitySystem/Physic/BoxCollider.h>

//WORK IN PROGRESS

GameEngine::BoxCollider::BoxCollider(
	GameObject* parent,
	Vector3 origine = Vector3(0, 0, 0),
	Vector3 scale = Vector3(1, 1, 1)
) : Collider(parent) {
	this->origine = origine;
	if (!isScaleValide(scale)) {
		this->scale = Vector3(1, 1, 1);
		GameEngine::Log::GetCoreLogger()->warn("Scale has to be postive or null, Scale set up to (1,1,1)");
	}
	else {
		this->scale = scale;
	}

}

bool GameEngine::BoxCollider::AreColliding(Collider& c){
	
	if (SphereCollider* sc = dynamic_cast<SphereCollider*>(&c)) {
		Vector3 dist = (sc->GetOrigine() - this->origine).Magnitude();
		float radius = sc->GetRadius();
		return
			dist.x < radius + this->scale.x / 2 &&
			dist.y < radius + this->scale.y / 2 &&
			dist.z < radius + this->scale.z / 2;
		
	}
	else if (BoxCollider* bc = dynamic_cast<BoxCollider*>(&c)) {
		Vector3 dist = (bc->origine - this->origine).Normalized();
		return
			dist.x < (bc->scale.x + this->scale.x) / 2 &&
			dist.y < (bc->scale.y + this->scale.y) / 2 &&
			dist.z < (bc->scale.z + this->scale.z) / 2;
	}
	return false;
}

void GameEngine::BoxCollider::Update(){
	std::cout << "Box Collider test" << std::endl;
	//TODO
}

bool GameEngine::BoxCollider::isScaleValide(Vector3 scale) {
	return scale.x > 0 && scale.y > 0 && scale.z > 0;
}