#pragma once
#include "GameObject.h"
#include <vector>

namespace GameEngine {
	class EntityManager {
	private: 
		std::vector<GameObject*> EntityList;
		static EntityManager* m_Instance;
	public:
		void TerminateEnity(int ID);
		void CreateNewEntity();
		static EntityManager* CreateInstance();
		static void Terminate();
	private:
		int GetNewID();
		EntityManager();
		~EntityManager();

	};
}