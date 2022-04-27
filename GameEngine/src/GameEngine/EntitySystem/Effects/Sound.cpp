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

void GameEngine::Sound::playSound(const char* name) {

}

void GameEngine::Sound::stopChannel(int channel) {

}

void GameEngine::Sound::loadSound(const char* directory) {

}

void GameEngine::Sound::setSoundVolume(unsigned int volume) {

}

void GameEngine::Sound::playMusic(const char* directory) {

}

void GameEngine::Sound::stopMusic() {

}

void GameEngine::Sound::setMusicVolume(unsigned int volume) {

}

