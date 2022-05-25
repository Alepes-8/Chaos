#pragma once
#include "../BaseComponent.h"
#include "../AI/UnitMovement.h"
#include "../../MathHelper.h"
#include "GameEngine/EntitySystem/Physic/Transform.h"
#include "GameEngine/EntitySystem/Physic/Physics.h"


namespace GameEngine {
	class DynamicBody: public BaseComponent
	{
	private:
		Vector3 CurrentMoveSpeed;
		Vector3 CurrentRotationSpeed;

		Physics* physicsComp = NULL;
		UnitMovement* movementComp = NULL;


	public: 
		DynamicBody(GameObject* parent);
		~DynamicBody();
		void AddMovement(Vector3 direction);
		void AddRotation(Vector3 direction);
		Vector3* GetMovement();
		void Update() override;
	};
}


