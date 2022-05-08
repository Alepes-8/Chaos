#pragma once
#include "../BaseComponent.h"
#include <SDL_mixer.h>
#include <SDL.h>
#include <string>

namespace GameEngine {

	

	class Sound : public BaseComponent 
	{
	public:
		enum VolumePreset{MIN = 26, LOW = 52, MEDIUM = 78, HIGH = 104, MAX = 128};

		Sound(GameObject* parent);
		~Sound();
		void Update() override;
		
		Mix_Music* loadMusic(std::string path);
		void PlayMusic(Mix_Music* m, int volume = LOW, int repeats = -1);
		// For SDL_Mixer, -1 means "repeat endlessly"
		void PauseMusic();
		void UnpauseMusic();
		void StopMusic();
		void DadeMusic(int fadeTime = 1000);
		void ChangeMusicVolume(int volume);

		Mix_Chunk* loadChunk(std::string path);
		void PlayChunk(Mix_Chunk* c, int volume = HIGH, int repeats = 0);
		void PauseChunk(Mix_Chunk* c);
		void UnpauseChunk(Mix_Chunk* c);
		void StopChunk(Mix_Chunk* c);

		bool IsMusicPlaying();
		bool IsMusicPaused();
		bool IsChunkPlaying(Mix_Chunk* c);
		bool IsChunkPaused(Mix_Chunk* c);

	private:
		const int HARDWARE_CHANNELS_ = 2;
		const int FREQUENCY_ = 44100;
		const int CHUNK_SIZE_ = 2048;
		const int MAX_CHUNKS_PLAYING_ = 5;
	};
}