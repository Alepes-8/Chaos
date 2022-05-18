#pragma once
#include "../BaseComponent.h"

namespace GameEngine {
	class Team : public BaseComponent
	{
	private:
		int team;
	public:
		Team(GameObject*, int);
		~Team();
		int* GetTeam();
		void Update() override;
	};

}

