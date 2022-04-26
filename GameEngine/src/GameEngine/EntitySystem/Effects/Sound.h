#pragma once
#include "../BaseComponent.h"

namespace GameEngine {
	class Sound : public BaseComponent {
	public:
		Sound(const char* dir);
		~Sound();
		void Update() override;
	};
}