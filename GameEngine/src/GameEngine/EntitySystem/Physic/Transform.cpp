#include <GameEngine/EntitySystem/Physic/Transform.h>


GameEngine::Transform::Transform() {
	coordinates = Vector3(0, 0, 0);
	rotation = Vector3(0, 0, 0);
	scale = Vector3(1, 1, 1);
}

GameEngine::Transform::Transform(
	Vector3 coordinates = Vector3(0, 0, 0),
	Vector3 rotation = Vector3(0, 0, 0),
	Vector3 scale = Vector3(1, 1, 1)) 
{
	this->coordinates = coordinates;
	this->rotation = rotation;
	if (!isScaleValid(scale)) {
		this->scale = (1, 1, 1);
		GameEngine::Log::GetCoreLogger()->warn("Scale has to be postive or null, Scale set up to (1,1,1)");
	}
	else {
		this->scale = scale;
	}
}

void GameEngine::Transform::translate(Vector3 translation) { coordinates += translation; }


void GameEngine::Transform::setRotation(Vector3 rotation) {	this->rotation = rotation; }

void GameEngine::Transform::rotate(Vector3 axis, float value) {
	//TODO
}

void GameEngine::Transform::setScale(Vector3 scale) {
	if (!isScaleValid(scale)) {
		GameEngine::Log::GetCoreLogger()->warn("Couldn't update scale, scale has to be postive or null");
	}
	else {
		this->scale = scale;
	}
}

void GameEngine::Transform::rescale(float coef) {
	if (coef < 0) {
		GameEngine::Log::GetCoreLogger()->warn("Couldn't update scale, scale has to be postive or null, please use a positive coeficient");
	}
	else {
		this->scale *= coef;
	}
}

bool GameEngine::Transform::isScaleValid(Vector3 scale) { return scale.x >= 0 && scale.y >= 0 && scale.z >= 0; }



void GameEngine::Transform::update() {
	std::cout << "transform test" << std::endl;
	//TODO
}

