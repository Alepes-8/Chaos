#pragma once
#include "../BaseComponent.h"
#include "GameEngine/MathHelper.h"

namespace GameEngine {
	class Physics : public BaseComponent {
	public:
		Physics(GameObject* parent);
		~Physics();

		Vector3 CalculateSpeed(Vector3 movement, float speed);
		
		void Update() override;
	};
}