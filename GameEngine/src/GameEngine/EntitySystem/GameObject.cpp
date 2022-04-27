#include "GameObject.h"

void GameEngine::GameObject::EarlyUpdate() {

}

void GameEngine::GameObject::Update() {
	/*for (auto component : componentsList) {
		component->Update();
	}*/
}

void GameEngine::GameObject::LateUpdate() {

}

GameEngine::GameObject::GameObject(int inputID) {
	GameEngine::Log::GetCoreLogger()->warn("Create the GameObject Class");
	ID = inputID;
}

GameEngine::GameObject::~GameObject() {
	GameEngine::Log::GetCoreLogger()->warn("Destroy the GameObject Class");
	for (auto comp : components) {
		delete comp.second;
	}

}

void GameEngine::GameObject::PrintList() {

	for (auto comps : components)
	{
		std::cout << comps.first << " " << comps.second << "\n";
	}
}

void GameEngine::GameObject::Terminate() {

	/*-delete componets parts-*/
	
	/*------------------------*/
	/*--Delete the dictinary--*/

	/*------------------------*/

}