#include "GameEngine/EntitySystem/BaseComponent.h"
#include "GameEngine/EntitySystem/GameObject.h"
#include "GameEngine/EntitySystem/Physic/Transform.h"


GameEngine::BaseComponent::BaseComponent(GameObject* parent)
{
	this->parent = parent;
}

GameEngine::Transform* GameEngine::BaseComponent::getParentTransform()
{
	return this->parent->getTransform();
}

GameEngine::BaseComponent::~BaseComponent()
{
	std::cout << "Delete component" << std::endl;
}

void GameEngine::BaseComponent::Update()
{
	std::cout << "update BaseComponent" << std::endl;
}
