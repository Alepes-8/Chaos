#pragma once
#include "../BaseComponent.h"

namespace GameEngine {
	class UnitMovement : public BaseComponent {
	private:
		float movement;
	public:
		UnitMovement(float initSpeed);
		~UnitMovement();
		float GetMovement();
		void Update() override;
	};
}