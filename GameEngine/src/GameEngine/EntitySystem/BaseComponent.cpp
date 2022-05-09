#include "GameEngine/EntitySystem/BaseComponent.h"
#include "GameEngine/EntitySystem/GameObject.h"
#include "GameEngine/EntitySystem/Physic/Transform.h"

/// <summary>
/// Create a Base Component
/// </summary>
/// <param name="parent"> - Parent GameObject</param>
GameEngine::BaseComponent::BaseComponent(GameObject* parent)
{
	this->parent = parent;
}

/// <summary>
/// Get the Transform of the Parent GameObject
/// </summary>
/// <returns> - Parent GameObject's Transform</returns>
GameEngine::Transform* GameEngine::BaseComponent::getParentTransform()
{
	return this->parent->GetTransform();
}


/// <summary>
/// Destructor
/// </summary>
GameEngine::BaseComponent::~BaseComponent()
{
	std::cout << "Delete component" << std::endl;
}

/// <summary>
/// Update the BaseComponent
/// </summary>
void GameEngine::BaseComponent::Update()
{
	std::cout << "update BaseComponent" << std::endl;
}
