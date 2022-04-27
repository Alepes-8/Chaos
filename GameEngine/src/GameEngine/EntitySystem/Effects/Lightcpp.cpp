#include "Light.h"

GameEngine::Light::Light() {
	std::cout << "Create health" << std::endl;

}

GameEngine::Light::~Light() {
	std::cout << "delete health" << std::endl;

}

void GameEngine::Light::Update() {
	std::cout << "Update health" << std::endl;

}