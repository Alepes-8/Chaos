#include "Sound.h"

#define SOUND_REPLAY_PROTECTION_TIME 50

class SoundData {
private:
	Mix_Chunk* chunk;
public:
	
	~SoundData() {
		if (chunk) {
			Mix_FreeChunk(chunk);
			chunk = 0;
		}
	}

	Mix_Chunk* getData() const { return chunk; }
};


//-------------------------------------------------------------------
GameEngine::Sound::Sound(const char* dir) {
	std::cout << "Create sound" << std::endl;

	if (SDL_InitSubSystem(SDL_INIT_AUDIO) < 0) {
		throw Exception("SDL_init audio error: %s", SDL_GetError());
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		throw Exception("Couldn´t open audio device: %s", Mix_GetError());
	}

	loadSound("audio/");
	Mix_AllocateChannels(32);
}

//-------------------------------------------------------------------
GameEngine::Sound::~Sound() {
	std::cout << "Delete sound" << std::endl;

	stopMusic();
	Mix_CloseAudio();

	for () {

	}
}

//-------------------------------------------------------------------
void GameEngine::Sound::Update() {
	std::cout << "Update sound" << std::endl;

}

//-------------------------------------------------------------------
/*
	Play sound once
	@param name sound name
*/
void GameEngine::Sound::playSound(const char* name) {

}

//-------------------------------------------------------------------
/*
	Stop playing the channel
	@param channel to stop
*/
void GameEngine::Sound::stopChannel(int channel) {

}

//-------------------------------------------------------------------
/*
	Load all *.wav from directory
	@param directory path to the directory
*/
void GameEngine::Sound::loadSound(const char* directory) {

}

//-------------------------------------------------------------------
void GameEngine::Sound::setSoundVolume(unsigned int volume) {

}

//-------------------------------------------------------------------
//	Music part
//-------------------------------------------------------------------

void GameEngine::Sound::playMusic(const char* directory) {

}

void GameEngine::Sound::stopMusic() {

}

void GameEngine::Sound::setMusicVolume(unsigned int volume) {

}

