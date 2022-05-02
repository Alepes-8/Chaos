#pragma once
#include <map>

namespace GameEngine {

	//forward declaration
	class Transform;
	class BaseComponent;

	class GameObject {
	private:
		static unsigned int gameObjCounter;
		Transform* transform;

	public:
		int ID;
		std::map<int, BaseComponent*> components;
		
		Transform* getTransform();
		void Terminate();
		void EarlyUpdate();
		void Update();
		void LateUpdate();
		void PrintList();
		GameObject();
		~GameObject();		
	};
}