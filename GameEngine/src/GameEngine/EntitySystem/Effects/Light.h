#pragma once
#include "../BaseComponent.h"

namespace GameEngine {
	class Light : public BaseComponent {
		Light(GameObject* parent);
		~Light();
		void Update() override;
	};
}