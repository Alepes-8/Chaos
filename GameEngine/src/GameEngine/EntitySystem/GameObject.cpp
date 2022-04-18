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
