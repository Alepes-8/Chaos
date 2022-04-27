#pragma once
#include "BaseComponent.h"
#include <vector>
#include "../Log.h"
#include <map>
#include "AI/UnitDamage.h"
#include "AI/UnitHealth.h"
#include "AI/UnitMovement.h"

namespace GameEngine {
	class GameObject {
	public:
		int ID;
		std::map<int, BaseComponent*> components;
		void Terminate();
		void EarlyUpdate();
		void Update();
		void LateUpdate();
		void PrintList();
		GameObject(int inputID);
		~GameObject();		
	};
}