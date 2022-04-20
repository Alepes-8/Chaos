#pragma once
#include "../BaseComponent.h"

namespace GameEngine {
	class UnitMovement : public BaseComponent {
	private:
		float movement;
	public:
		UnitMovement();
		~UnitMovement();
		float GetMovement();
	};
}