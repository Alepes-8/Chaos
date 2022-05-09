#pragma once
#include <GameEngine/EntitySystem/Physic/Colider.h>
#include <GameEngine/EntitySystem/Physic/BoxCollider.h>
#include <GameEngine/MathHelper.h>
#include <GameEngine/Log.h>


namespace GameEngine {
	class SphereCollider : public Collider {
	private:
		Vector3 origine;
		float radius;

	public:
		SphereCollider(GameObject* parent, Vector3 origine, float radius);
		bool AreColliding(Collider& c) override;

		//getters
		Vector3 GetOrigine() { return origine; }
		float GetRadius() { return radius; }


		void Update() override;
	};

}
