#pragma once
#include "GameObject.h"
#include <vector>

#include <fstream>	//can probably be deleted. Ask Alex(test txt files)
#include "json/json.h"	//can probably be deleted. Ask Alex(test txt files)
#include "json/value.h"

namespace GameEngine {
	class EntityManager {
	private: 
		std::vector<GameObject*> EntityList;
		static EntityManager* m_Instance;
	public:
		void TerminateEnity(int ID);
		void CreateNewEntity(char* form, char* type);
		static EntityManager* CreateInstance();
		static void Terminate();
		void PrintList();
	private:
		int GetNewID();
		EntityManager();
		~EntityManager();

	};
}