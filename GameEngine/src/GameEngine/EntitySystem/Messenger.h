#pragma once
#include "EntityManager.h"
#include "GameObject.h"

namespace GameEngine {
	class Messenger {
	private:
		static Messenger* m_Instance;
		GameEngine::EntityManager* m_manager;
		Messenger();
		~Messenger();

	public:
		static Messenger* CreateInstance();
		static void Terminate();
		void DamageUnit(int id, float damage);
		void MoveUnit();
	};
}