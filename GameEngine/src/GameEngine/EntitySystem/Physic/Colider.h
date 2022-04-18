#pragma once
#include <GameEngine/EntitySystem/BaseComponent.h>
namespace GameEngine {
	class Collider : public BaseComponent {
	public:
		virtual bool areColliding(Collider& c);
		virtual void Update() override = 0;
	};

}