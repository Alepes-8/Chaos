#pragma once
#include "../BaseComponent.h"
#include "GameEngine/MathHelper.h"
#include <SDL.h>


namespace GameEngine {
	class Physics : public BaseComponent {
	private:
		float m_friction = 20;
		float m_DeltaTime;
		float m_StartTicks;
		unsigned int m_ElipsedTime;
	public:
		Physics(GameObject* parent);
		~Physics();

		Vector3 CalculateSpeed(Vector3 movement, float speed);
		Vector3 CalculateAcceleration(Vector3 movement, Vector3 direction, float speed);
		void ResetTime();
		void Update() override;
	};
}