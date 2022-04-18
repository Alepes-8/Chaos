#pragma once
#include "BaseComponent.h"
#include <vector>


namespace GameEngine {
	class GameObject {
	public:
		int ID;
		std::vector<BaseComponent*> componentsList;


		void EarlyUpdate();
		void Update();
		void LateUpdate();

	private:
		GameObject();
		~GameObject();
	};
}