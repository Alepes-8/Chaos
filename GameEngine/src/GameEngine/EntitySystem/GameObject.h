#pragma once
#include "BaseComponent.h"
#include <vector>
#include "../Log.h"
#include <map>


namespace GameEngine {
	class GameObject {
	public:
		int ID;
		std::map<std::string, BaseComponent**> components;

		void EarlyUpdate();
		void Update();
		void LateUpdate();
		GameObject(int inputID);
		~GameObject();		
	};
}