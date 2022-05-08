#pragma once
#include <GameEngine/EntitySystem/BaseComponent.h>
namespace GameEngine {
	class Collider : public BaseComponent {
	public:
		Collider(GameObject* parent) : BaseComponent(parent) {};
		virtual bool AreColliding(Collider& c);
		virtual void Update() override = 0;
	};

}