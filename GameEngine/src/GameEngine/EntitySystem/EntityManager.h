#pragma once
#include "GameEngine/EntitySystem/GameObject.h"
#include <vector>
#include <map>
#include "IdGenerationPool.h"

#include <fstream>	//can probably be deleted. Ask Alex(test txt files)
#include "json/json.h"	//can probably be deleted. Ask Alex(test txt files)
#include "json/value.h"
#include "AI/UnitDamage.h"
#include "AI/UnitHealth.h"
#include "AI/UnitMovement.h"
#include "AI/PathFinding.h"
#include "Effects/Sound.h"
#include "Effects/Renderable.h"
#include "Physic/Transform.h"
#include "Physic/StaticBody.h"
#include "Physic/DynamicBody.h"
#include "Physic/Physics.h"


namespace GameEngine {
	class EntityManager {
	private: 
		int currentID = 0;
		std::map<int, GameObject*> EntityList;
		static EntityManager* m_Instance;
		GameEngine::IdGenerationPool* m_IdPool;
	public:
		static EntityManager* CreateInstance();
		static void Terminate();

		int CreateNewEntity(char* form, float x_pos , float y_pos , float z_pos);
		void TerminateEnity(int entityID);

		void EarlyUpdate();
		void Update();
		void LateUpdate();
		GameObject* GetEntity(int id);
		std::map<int, GameObject*>* GetList();
		int GetID(int id, int direction);

		void PlayAudio(int id);
	private:
		int GetNewID();
		EntityManager();
		~EntityManager();
	};
}