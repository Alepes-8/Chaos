#include "Renderable.h"

GameEngine::Renderable::Renderable() {
	std::cout << "Create Renderable" << std::endl;
}
GameEngine::Renderable::~Renderable() {
	std::cout << "Delete Renderable" << std::endl;
}
void GameEngine::Renderable::Update() {
	std::cout << "Update Renderable" << std::endl;
}