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
		std::map<int, BaseComponent*> components;

	public:

		int ID;
		Transform* getTransform();
		void AddComponent(int, BaseComponent*);
		BaseComponent* GetComponent(int); 
		void EarlyUpdate();
		void Update();
		void LateUpdate();
		void PrintList();
		GameObject();
		~GameObject();		
	};
}