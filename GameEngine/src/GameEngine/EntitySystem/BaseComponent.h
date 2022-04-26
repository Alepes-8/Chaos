#pragma once
#include <iostream>

namespace GameEngine {
	class BaseComponent{
	public:
		virtual void Update() = 0;
	};
}