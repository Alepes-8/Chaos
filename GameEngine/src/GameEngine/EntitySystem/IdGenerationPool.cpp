#include "IdGenerationPool.h"

GameEngine::IdGenerationPool* GameEngine::IdGenerationPool::m_Instance = NULL;


GameEngine::IdGenerationPool::IdGenerationPool() {
	/*Create a new pool of available ids*/
	idPool = new uint32_t[1024];
	generations = new uint32_t[1024];
	uint64_t value = 0x00000000;
	for (int i = 0; i < 1024; i++) {
		idPool[i] = value;
		generations[i] = 0x01000000;
		value += 0x00000001;
	}
}

GameEngine::IdGenerationPool* GameEngine::IdGenerationPool::CreateInstance() {
	if (m_Instance == NULL) {
		m_Instance = new IdGenerationPool();
	}
	return m_Instance;

}

void GameEngine::IdGenerationPool::Terminate() {
	delete m_Instance;
	m_Instance = NULL;
}

GameEngine::IdGenerationPool::~IdGenerationPool() {
	delete idPool;
	delete generations;
	idPool = NULL;
	generations = NULL;
}



bool GameEngine::IdGenerationPool::Allocate() {
	return true;

}

bool GameEngine::IdGenerationPool::IsValid() {
	return true;

}