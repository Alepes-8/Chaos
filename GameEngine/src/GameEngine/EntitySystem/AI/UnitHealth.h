#pragma once
#include "../BaseComponent.h"

namespace GameEngine {
	class UnitHealth : public BaseComponent {
	private:
		float health;
	public:	
		UnitHealth(GameObject* parent, float initHealth);
		~UnitHealth();
		float GetHealth();
		void EditHealth(float change);
		void Update() override;
		

	};
}