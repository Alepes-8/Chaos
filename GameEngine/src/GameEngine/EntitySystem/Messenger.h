#pragma once
#include "EntityManager.h"

namespace GameEngine {
	class Messenger {
	private:
		static Messenger* m_Instance;
		Messenger();
		~Messenger();
	public:
		static Messenger* CreateInstance(); 
		static void Terminate();
		void DamageUnit();
		void MoveUnit();
	};
}