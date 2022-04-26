#pragma once
#include "../BaseComponent.h"
#include <SDL_mixer.h>

namespace GameEngine {
	class Sound : public BaseComponent {
	public:
		Sound(const char* dir);
		~Sound();
		void Update() override;
		
		void playSound(const char* fileName);
		void stopChannel();
		void setSoundVolume();

		void playMusic();
		void stopMusic();
		void setMusicVolume();
	};
}