#pragma once
#include "GameObject.h"
#include <vector>
#include <map>


#include <fstream>	//can probably be deleted. Ask Alex(test txt files)
#include "json/json.h"	//can probably be deleted. Ask Alex(test txt files)
#include "json/value.h"
#include "AI/UnitDamage.h"
#include "AI/UnitHealth.h"
#include "AI/UnitMovement.h"
#include "AI/PathFinding.h"
#include "Effects/Sound.h"

namespace GameEngine {
	class EntityManager {
	private: 
		int currentID = 0;
		std::map<int , GameObject*> EntityList;
		std::map<std::string, std::vector<BaseComponent*>> componentLists;
		static EntityManager* m_Instance;
	public:
		void TerminateEnity(int entityID);
		void CreateNewEntity(char* form, char* type);
		static EntityManager* CreateInstance();
		static void Terminate();
		void PrintList();
		void PrintFirstEntity();
	private:
		int GetNewID();
		EntityManager();
		~EntityManager();
	};
}