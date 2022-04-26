#pragma once
#include "BaseComponent.h"
#include <vector>
#include "../Log.h"


namespace GameEngine {
	class GameObject {
	public:
		int ID;
		std::vector<BaseComponent*> componentsList;
		GameObject* entity;

		void EarlyUpdate();
		void Update();
		void LateUpdate();

	private:
		GameObject();
		~GameObject();
	};
}