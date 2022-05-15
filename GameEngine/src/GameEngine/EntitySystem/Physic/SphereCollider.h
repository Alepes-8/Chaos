#pragma once
#include "GameEngine/EntitySystem/BaseComponent.h"
//#include <GameEngine/EntitySystem/Physic/BoxCollider.h>
#include "GameEngine/MathHelper.h"
#include "GameEngine/Log.h"
#include "GameEngine/EntitySystem/Physic/Transform.h"


namespace GameEngine {
	class SphereCollider : public BaseComponent {
	private:
		//Vector3 origine;
		float radius;
		Vector3 origin;
		Transform* transform;

	public:
		SphereCollider(GameObject* parent, Vector3 orgin, float radius);
		bool AreColliding(SphereCollider* control);
		float GetRadius();
		Vector3 GetPosition();
		Vector3 GetOverlap(SphereCollider* control);
		void Update() override;
	};

}
