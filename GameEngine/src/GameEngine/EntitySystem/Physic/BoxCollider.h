#pragma once
#include <GameEngine/EntitySystem/Physic/Colider.h>
#include <GameEngine/MathHelper.h>
#include <GameEngine/Log.h>

namespace GameEngine {
	class BoxCollider : public Collider {
	private:
		Vector3 origine;
		Vector3 scale;

	public:
		BoxCollider(Vector3 origine, Vector3 scale);
		bool areColliding(const Collider& c) override;
		void update() override;

		bool isScaleValide(Vector3 scale)
	};

}
