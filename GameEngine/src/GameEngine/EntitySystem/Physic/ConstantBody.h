#pragma once

#include "../BaseComponent.h"

namespace GameEngine {
	class ConstantBody : public BaseComponent {
	public:
		ConstantBody();
		~ConstantBody();
		void Update() override;
	};
}