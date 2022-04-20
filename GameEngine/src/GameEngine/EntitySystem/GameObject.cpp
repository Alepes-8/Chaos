#include "GameObject.h"

void GameEngine::GameObject::EarlyUpdate() {

}

void GameEngine::GameObject::Update() {
	for (auto component : componentsList) {
		component->Update();
	}
}

void GameEngine::GameObject::LateUpdate() {

}

GameEngine::GameObject::GameObject() {
	GameEngine::Log::GetCoreLogger()->info("create the GameObject Class");
}

GameEngine::GameObject::~GameObject() {
	GameEngine::Log::GetCoreLogger()->info("Destroy the GameObject Class");
}

