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
		SphereCollider(Vector3 origine, float radius);
		bool areColliding(Collider& c) override;

		//getters
		Vector3 getOrigine() { return origine; }
		float getRadius() { return radius; }


		void Update() override;
	};

}
