#include <GameEngine/EntitySystem/Physic/BoxCollider.h>

GameEngine::BoxCollider::BoxCollider(
	Vector3 origine = Vector3(0, 0, 0),
	Vector3 scale = Vector3(1, 1, 1)
){
	this->origine = origine;
	if (!isScaleValide(scale)) {
		this->scale = Vector3(1, 1, 1);
		GameEngine::Log::GetCoreLogger()->warn("Scale has to be postive or null, Scale set up to (1,1,1)");
	}
	else {
		this->scale = scale;
	}

}

bool GameEngine::BoxCollider::areColliding(Collider& c){
	if (SphereCollider* sc = dynamic_cast<SphereCollider*>(&c)) {
		
	}
	else if (BoxCollider* bc = dynamic_cast<BoxCollider*>(&c)) {

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