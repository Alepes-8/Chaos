#include <GameEngine/EntitySystem/Physic/BoxCollider.h>

//WORK IN PROGRESS

GameEngine::BoxCollider::BoxCollider(
	GameObject* parent,
	Vector3 origine = Vector3(0, 0, 0),
	Vector3 scale = Vector3(1, 1, 1)
) : Colider(parent) {
	this->origine = origine;
	if (!isScaleValide(scale)) {
		this->scale = Vector3(1, 1, 1);
		GameEngine::Log::GetCoreLogger()->warn("Scale has to be postive or null, Scale set up to (1,1,1)");
	}
	else {
		this->scale = scale;
	}

}


bool GameEngine::BoxCollider::AreColliding(Colider& c){

	return false;
}

void GameEngine::BoxCollider::Update(){
	std::cout << "Box Collider test" << std::endl;
	//TODO
}

bool GameEngine::BoxCollider::isScaleValide(Vector3 scale) {
	return scale.x > 0 && scale.y > 0 && scale.z > 0;
}