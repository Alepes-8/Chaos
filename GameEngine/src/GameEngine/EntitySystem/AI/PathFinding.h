#pragma once
#include "../BaseComponent.h"

namespace GameEngine {
	class PathFinding : public BaseComponent 
	{
	public:
		PathFinding(GameObject* parent);
		~PathFinding();
		void Update() override;
	};
}