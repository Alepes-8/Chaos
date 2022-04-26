#pragma once
#include "../BaseComponent.h"

namespace GameEngine {
	class StaticBody: public BaseComponent {
		void Update() override{
			std::cout << "static body test" << std::endl;
		}
	};
}