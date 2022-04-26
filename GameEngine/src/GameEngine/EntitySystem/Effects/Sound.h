#pragma once
#include "../BaseComponent.h"
#include <SDL_mixer.h>

namespace GameEngine {
	class Sound : public BaseComponent 
	{
	public:
		Sound(const char* dir);
		~Sound();
		void Update() override;
		
		void playSound(const char* name);
		void stopChannel(int channel);
		void setSoundVolume(unsigned int volume);

		void playMusic(const char* directory);
		void stopMusic();
		void setMusicVolume(unsigned int volume);

	private:
		void loadSound(const char* directory);
	};
}