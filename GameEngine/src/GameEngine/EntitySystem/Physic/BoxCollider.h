#pragma once
#include <GameEngine/EntitySystem/Physic/Colider.h>
#include <GameEngine/EntitySystem/Physic/SphereCollider.h>
#include <GameEngine/MathHelper.h>
#include <GameEngine/Log.h>

namespace GameEngine {
	class BoxCollider : public Collider {
	private:
		Vector3 origine;
		Vector3 scale;

	public:
		BoxCollider(GameObject* parent, Vector3 origine, Vector3 scale);
		bool AreColliding(Collider& c) override;
		void Update() override;

		//getters
		Vector3 getOrigine() { return origine; }
		Vector3 getScale() { return scale; }

		bool isScaleValide(Vector3 scale);
	};
}
