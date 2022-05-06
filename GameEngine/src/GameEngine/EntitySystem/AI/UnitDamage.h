#pragma once
#include "../BaseComponent.h"


namespace GameEngine {
	class UnitDamage : public BaseComponent{
	private:
		float damage;
	public:
		int GetDamage();
		UnitDamage(GameObject* parent, float dmgValue);
		~UnitDamage();
		void Update() override;
	};
}