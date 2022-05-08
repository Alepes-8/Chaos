#pragma once
#include "../BaseComponent.h"
#include <SDL_mixer.h>
#include <SDL.h>
#include <string>
#include <map>
#include <fstream>
#include <iostream>
#include <filesystem>

namespace GameEngine {

	class Sound : public BaseComponent 
	{
	public:
		enum VolumePreset{MIN = 26, LOW = 52, MEDIUM = 78, HIGH = 104, MAX = 128};

		Sound(GameObject* parent/*, const char* dir*/);
		~Sound();
		void Update() override;
		
		Mix_Music* loadMusic(std::string path);
		std::map<std::string, Mix_Chunk*> loadChunk(std::string path);

		void playMusic(Mix_Music* m, int volume = LOW, int repeats = -1);// For SDL_Mixer, -1 means "repeat endlessly"
		void pauseMusic();
		void unpauseMusic();
		void stopMusic();
		void fadeMusic(int fadeTime = 1000);
		void changeMusicVolume(int volume);

		void playChunk(Mix_Chunk* c, int volume = HIGH, int repeats = 0);
		void pauseChunk(Mix_Chunk* c);
		void unpauseChunk(Mix_Chunk* c);
		void stopChunk(Mix_Chunk* c);

		bool isMusicPlaying();
		bool isMusicPaused();
		bool isChunkPlaying(Mix_Chunk* c);
		bool isChunkPaused(Mix_Chunk* c);

	private:
		const int HARDWARE_CHANNELS_ = 2;
		const int FREQUENCY_ = 44100;
		const int CHUNK_SIZE_ = 2048;
		const int MAX_CHUNKS_PLAYING_ = 5;
		
		std::map<std::string, Mix_Chunk*> m_effectMap;
	};
}