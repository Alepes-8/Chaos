#pragma once
#include "../BaseComponent.h"


namespace GameEngine {
	class UnitDamage : public BaseComponent{
	private:
		float minDamage;
		float maxDamage;
	public:
		float GetDamage();
		UnitDamage(GameObject* parent, float minDamage, float maxDamage);
		~UnitDamage();
		void Update() override;
	};
}