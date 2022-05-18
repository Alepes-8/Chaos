#pragma once
#include <GameEngine/EntitySystem/BaseComponent.h>
namespace GameEngine {
	class Colider : public BaseComponent {
	public:
		Colider(GameObject* parent) : BaseComponent(parent) {};
	};

}