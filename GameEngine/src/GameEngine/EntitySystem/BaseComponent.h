#pragma once
#include <iostream>

namespace GameEngine {
	class BaseComponent{
	public:
		~BaseComponent() {
			std::cout << "Delete component" << std::endl;
		}
		virtual void Update() = 0;
	};
}