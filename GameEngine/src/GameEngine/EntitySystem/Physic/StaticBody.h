#pragma once
#include "../BaseComponent.h"


namespace GameEngine {
	class StaticBody: public BaseComponent
	{
	public: 
		StaticBody(GameObject* parent);
		~StaticBody();

		void Update() override;
	};
}


