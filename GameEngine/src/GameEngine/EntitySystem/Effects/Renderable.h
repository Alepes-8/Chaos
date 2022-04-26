#pragma once
#include "../BaseComponent.h"

namespace GameEngine {
	class Renderable : public BaseComponent {
	public: 
		Renderable();
		~Renderable();
		void Update() override;
	};
}