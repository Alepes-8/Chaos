#pragma once
#include "../BaseComponent.h"

namespace GameEngine {
	class UnitDamage : public BaseComponent{
	private:
		unsigned int damage;
	public:
		int GetDamage();
		UnitDamage();
		~UnitDamage();
	};
}