#include "GameObject.h"
#include <vector>
#include "../Log.h"
#include "AI/UnitDamage.h"
#include "AI/UnitHealth.h"
#include "AI/UnitMovement.h"
#include "GameEngine/EntitySystem/Physic/Transform.h"

unsigned int GameEngine::GameObject::gameObjCounter = 0;

/// <summary>
/// Update before rendering the frame
/// </summary>
void GameEngine::GameObject::EarlyUpdate() {

}

/// <summary>
/// Update all components of the GameObject
/// </summary>
void GameEngine::GameObject::Update() {


	for (auto comp : components) {
		comp.second->Update();
	}
	transform->Update();
}

/// <summary>
/// Update after the rendering frame
/// </summary>
void GameEngine::GameObject::LateUpdate() {

}

/// <summary>
/// Create a GameObject
/// </summary>
GameEngine::GameObject::GameObject() {
	GameEngine::Log::GetCoreLogger()->warn("Create the GameObject Class");
	gameObjCounter++;
	ID = gameObjCounter;
	transform = new Transform();
}

/// <summary>
/// Delete a GameObject
/// </summary>
GameEngine::GameObject::~GameObject() {
	GameEngine::Log::GetCoreLogger()->warn("Destroy the GameObject Class");
	std::cout << components.size() << std::endl;
	for (auto comp : components) {
		delete comp.second;
	}
	delete transform;
}

/// <summary>
/// get the id of the GameObject
/// </summary>
/// <returns> the GameObject's id </returns>
int GameEngine::GameObject::GetID() {
	return ID;
}

/// <summary>
/// Get the Transform of the GameObject
/// </summary>
/// <returns> GameObject's Transform </returns>
GameEngine::Transform* GameEngine::GameObject::GetTransform()
{
	return transform;
}

/// <summary>
/// Add a new BaseComponent to the GameObject
/// </summary>
/// <param name="id"> - id of the BaseComponent</param>
/// <param name="comp"> - Pointer to the BaseComponent to add</param>
void GameEngine::GameObject::AddComponent(int id, BaseComponent* comp) {
	components.insert({ id, comp });
}

/// <summary>
/// Get the BaseComponent corresponding to the given id
/// </summary>
/// <param name="id"> - id of the BaseComponent </param>
/// <returns> Pointer to the BaseComponent </returns>
GameEngine::BaseComponent* GameEngine::GameObject::GetComponent(int id) {
	if (components.count(id) == 0) {
		return nullptr;
	}
	return components.at(id);
}