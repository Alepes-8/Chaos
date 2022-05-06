#include "GameObject.h"
#include <vector>
#include "../Log.h"
#include "AI/UnitDamage.h"
#include "AI/UnitHealth.h"
#include "AI/UnitMovement.h"
#include "GameEngine/EntitySystem/Physic/Transform.h"

unsigned int GameEngine::GameObject::gameObjCounter = 0;

void GameEngine::GameObject::EarlyUpdate() {

}

void GameEngine::GameObject::Update() {


	for (auto comp : components) {
		comp.second->Update();
	}
	transform->Update();
}

void GameEngine::GameObject::LateUpdate() {

}

GameEngine::GameObject::GameObject() {
	GameEngine::Log::GetCoreLogger()->warn("Create the GameObject Class");
	gameObjCounter++;
	ID = gameObjCounter;
	transform = new Transform();
}

GameEngine::GameObject::~GameObject() {
	GameEngine::Log::GetCoreLogger()->warn("Destroy the GameObject Class");
	for (auto comp : components) {
		delete comp.second;
	}
	delete transform;
}




void GameEngine::GameObject::PrintList() {

	for (auto comps : components)
	{
		std::cout << comps.first << " " << comps.second << "\n";
	}
}

GameEngine::Transform* GameEngine::GameObject::getTransform()
{
	return transform;
}

void GameEngine::GameObject::AddComponent(int id, BaseComponent* comp) {
	components.insert({ id, comp });
}

GameEngine::BaseComponent* GameEngine::GameObject::GetComponent(int id) {
	if (components.count(id) == 0) {
		return nullptr;
	}
	return components.at(id);
}