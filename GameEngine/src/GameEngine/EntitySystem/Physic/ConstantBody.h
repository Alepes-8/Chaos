#pragma once

#include "../BaseComponent.h"

namespace GameEngine {
	class ConstantBody : public BaseComponent {
	public:
		ConstantBody(GameObject* parent);
		~ConstantBody();
		void Update() override;
	};
}