#pragma once
#include "../BaseComponent.h"

namespace GameEngine {
	class PathFinding : public BaseComponent 
	{
	public:
		PathFinding();
		~PathFinding();
		void Update() override;
	};
}