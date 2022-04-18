#pragma once
#include <GameEngine/EntitySystem/Physic/Colider.h>
#include <GameEngine/MathHelper.h>
#include <GameEngine/Log.h>

namespace GameEngine {
	class SphereCollider : public Collider {
	private:
		Vector3 origine;
		float radius;

	public:
		SphereCollider(Vector3 origine, float radius);
		bool areColliding(const Collider& c) override;
		void update() override;
	};

}
