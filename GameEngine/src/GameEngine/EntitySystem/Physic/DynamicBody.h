#pragma once
#include "../BaseComponent.h"

namespace GameEngine {
	class DynamicBody : BaseComponent{
		void Update() override {
			std::cout << "dynamic body test" << std::endl;
		}
	};
}