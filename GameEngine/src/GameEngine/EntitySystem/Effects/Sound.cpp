#include "Sound.h"

GameEngine::Sound::Sound(const char* dir) {
	std::cout << "Create sound" << std::endl;
}

GameEngine::Sound::~Sound() {
	std::cout << "Delete sound" << std::endl;

}
void GameEngine::Sound::Update() {
	std::cout << "Update sound" << std::endl;

}