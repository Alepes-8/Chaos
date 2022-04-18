#pragma once
#include <GameEngine/EntitySystem/BaseComponent.h>
namespace GameEngine {
	class Collider : public BaseComponent {
	public:
		virtual bool areColliding(const Collider& c);
		virtual void update();
	};

}