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
		int ID;

	public:
		GameObject();
		~GameObject();
		
		
		void AddComponent(int, BaseComponent*);

		Transform* GetTransform();
		BaseComponent* GetComponent(int); 
		int GetID();

		void EarlyUpdate();
		void Update();
		void LateUpdate();

			
	};
}