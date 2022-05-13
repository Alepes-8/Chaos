#include "StaticBody.h"

GameEngine::StaticBody::StaticBody(GameObject* parent) : BaseComponent(parent) {
	std::cout << " create static Body" << std::endl;

}

GameEngine::StaticBody::~StaticBody() {

}

void GameEngine::StaticBody::Update() {
}
