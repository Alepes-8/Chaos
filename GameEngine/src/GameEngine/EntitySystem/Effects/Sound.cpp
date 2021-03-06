#include "Sound.h"

namespace fs = std::filesystem;

//-------------------------------------------------------------------
GameEngine::Sound::Sound(GameObject* parent) : BaseComponent(parent) {
	std::cout << "Start audio" << std::endl;

	if (Mix_Init((SDL_INIT_AUDIO) == 0)) {
		printf("ERROR: SDL_INIT_AUDIO has failed!\n");
		printf("SDL error: %s\n", Mix_GetError());
	}

	if (Mix_OpenAudio(FREQUENCY_, MIX_DEFAULT_FORMAT, HARDWARE_CHANNELS_, CHUNK_SIZE_) == -1) {
		printf("ERROR: SDL_Mixer failed to open!\n");
		printf("SDL error: %s\n", Mix_GetError());
	}

	Mix_AllocateChannels(MAX_CHUNKS_PLAYING_);
	playing = 1;

}

//-------------------------------------------------------------------
GameEngine::Sound::~Sound() {
	std::cout << "Stop audio" << std::endl;

	m_effectMap.clear();

	Mix_CloseAudio();
	Mix_Quit();
}

//-------------------------------------------------------------------
void GameEngine::Sound::Update() {
	//std::cout << "Update audio" << std::endl;

}

//-------------------------------------------------------------------
/*
	Load music file to use.
	@param path to audio file
	Returns: A pointer to a Mix_Music. NULL is returned on errors.
*/
Mix_Music* GameEngine::Sound::LoadMusic(std::string path) {
	Mix_Music* m = Mix_LoadMUS(path.c_str());
	if(!m) {
		printf("Error: Mix_Music could not be loaded for '%s'!\n", path.c_str());
		printf("SDL error: %s\n", Mix_GetError());
		
	}
	else {
		return m;
	}
}

//-------------------------------------------------------------------
/*
	Load file for use as a sample.
	@param path to audio file
	Returns: A pointer to the sample as a Mix_Chunk. NULL is returned on errors.
*/
std::map<std::string, Mix_Chunk*> GameEngine::Sound::LoadChunk(std::string path) {
	
	std::string ext(".wav");
	for (auto& p : fs::recursive_directory_iterator(path)) {
		if (p.path().extension() == ext) {
			std::string str = p.path().string();
			const char* file = str.c_str();

			Mix_Chunk* c = Mix_LoadWAV(file);
			
			m_effectMap.insert(std::pair<std::string, Mix_Chunk*>( p.path().stem().string(), c));
			
		}
	}
	
	/*Mix_Chunk* c = Mix_LoadWAV(path.c_str());
	if (!c) {
		printf("ERROR: A Mix_Chunk could not be loaded for '%s'!\n", 
			path.c_str());
		printf("SDL error: %s\n", Mix_GetError());
	} else {
		return c;
	}
	}*/
	
	
	return m_effectMap;
}



//-------------------------------------------------------------------
//	Music part
//-------------------------------------------------------------------

//-----------------------------------------------------------------
/**
	Play music, with looping

	@param m pointer to Mix_Music to play.
	@param volume of the music.
	@param repeats, number of times to play through the music.
 */
void GameEngine::Sound::PlayMusic(Mix_Music* m, int volume, int repeats) {
	Mix_VolumeMusic((int)volume);
	if (Mix_PlayMusic(m, repeats) == -1) { // -1 plays the music forever
		printf("Error: Music file could not be played!\n");
		printf("SDL error: %s\n", Mix_GetError());
	}
	
}

//-------------------------------------------------------------------
/*
	Pause music
*/
void GameEngine::Sound::PauseMusic(){
	Mix_PauseMusic();
	playing = false;
}

//-------------------------------------------------------------------
/*
	 Resume paused music
*/
void GameEngine::Sound::UnpauseMusic() {
	Mix_ResumeMusic();
	playing = true;
}

//-------------------------------------------------------------------
/*
	Stop music playback
*/
void GameEngine::Sound::StopMusic() {
	Mix_HaltMusic();
}

//-------------------------------------------------------------------
/*
	Stop music, with fade out
	@param fadeTime milliseconds of time that the fade-out effect should take to go to silence, starting now.
*/
void GameEngine::Sound::FadeMusic(int fadeTime) {
	Mix_FadeOutMusic(fadeTime);
}

//-------------------------------------------------------------------
/*
	Change music volume
	@param volume an int value between 0-128
*/
void GameEngine::Sound::ChangeMusicVolume(int volume) {
	Mix_VolumeMusic((int)volume);
}


//-------------------------------------------------------------------
//	Chunk part
//-------------------------------------------------------------------

//-------------------------------------------------------------------
/*
	Play chunk on the first free unreserved channel.

	@params c sample to play.
	@params volume of the sample.
	@params repeats number of loops, -1 is infinite loops. Passing one here plays the sample twice (1 loop).
*/
void GameEngine::Sound::PlayChunk(Mix_Chunk* c, int volume, int repeats) {
	Mix_VolumeChunk(c, (int)volume);
	if (Mix_PlayChannel(-1, c, repeats) == -1) {
		if (Mix_GetError() == "No free channels available") {
			printf("WARNING: Mix_Chunk play requests have exceeded the ");
			printf("channels allocated for them!\n");
		}
		else {
			printf("WARNING: A Mix_Chunk could not be played!\n");
			printf("SDL error: %s\n", Mix_GetError());
		}
	}
}

//-------------------------------------------------------------------
/*
	Pause a channel

	@params c sample to pause.
*/
void GameEngine::Sound::PauseChunk(Mix_Chunk* c) {
	int numChannels = Mix_AllocateChannels(-1);

	for (int i = 0; i < numChannels; i++) {
		if (Mix_GetChunk(i) == c) {
			Mix_Pause(i);
		}
	}
}

//-------------------------------------------------------------------
/*
	Resume a paused channel

	@params c sample to resume.
*/
void GameEngine::Sound::UnpauseChunk(Mix_Chunk* c) {
	int numChannels = Mix_AllocateChannels(-1);

	for (int i = 0; i < numChannels; i++) {
		if (Mix_GetChunk(i) == c) {
			Mix_Resume(i);
		}
	}
}

//-------------------------------------------------------------------
/*
	Stop playing on a channel

	@params c sample to stop.
*/
void GameEngine::Sound::StopChunk(Mix_Chunk* c) {
	int numChannels = Mix_AllocateChannels(-1);

	for (int i = 0; i < numChannels; i++) {
		if (Mix_GetChunk(i) == c) {
			Mix_HaltChannel(i);
		}
	}
}


//-------------------------------------------------------------------
//	Info part
//-------------------------------------------------------------------

//-------------------------------------------------------------------
/*
	Test whether music is playing
*/
bool GameEngine::Sound::IsMusicPlaying() {
	if (playing) {
		return true;
	}
	else {
		return false;
	}
}

//-------------------------------------------------------------------
/*
	Test whether music is paused
*/
bool GameEngine::Sound::IsMusicPaused() {
	if (!playing) {
		return true;
	}
	else {
		return false;
	}
}

//-------------------------------------------------------------------
/*
	Get the active playing status of a channel

	@params c sample playing on the channel.
*/
bool GameEngine::Sound::IsChunkPlaying(Mix_Chunk* c) {
	int numChannels = Mix_AllocateChannels(-1);

	for (int i = 0; i < numChannels; i++) {
		if (Mix_GetChunk(i) == c) {
			if (Mix_Playing(i) && !Mix_Paused(i)) {
				return true;
			}
		}
	}

	return false;
}

//-------------------------------------------------------------------
/*
	Get the pause status of a channel

	@params c sample paused on the channel.
*/
bool GameEngine::Sound::IsChunkPaused(Mix_Chunk* c) {
	int numChannels = Mix_AllocateChannels(-1);
	for (int i = 0; i < numChannels; i++) {
		if (Mix_GetChunk(i) == c && Mix_Playing(i) && Mix_Paused(i)) {
			return true;
		}
	}

	return false;
}
