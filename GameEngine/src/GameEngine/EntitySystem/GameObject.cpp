#include "GameObject.h"

void GameEngine::GameObject::EarlyUpdate() {

}

void GameEngine::GameObject::Update() {
	for (auto component : componetsList) {
		component->Update();
	}
}

void GameEngine::GameObject::LateUpdate() {

}