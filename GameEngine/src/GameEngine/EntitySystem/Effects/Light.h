#pragma once
#include "../BaseComponent.h"

namespace GameEngine {
	class Light : public BaseComponent {
		Light();
		~Light();
		void Update() override;
	};
}