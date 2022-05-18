#include "UnitDamage.h"

GameEngine::UnitDamage::UnitDamage(GameObject* parent, float minDamage, float maxDamage) : BaseComponent(parent) {
	std::cout << "damage create " << minDamage << " - " << maxDamage << std::endl;
	this->minDamage = minDamage;
	this->maxDamage = maxDamage;

}

GameEngine::UnitDamage::~UnitDamage() {
	std::cout << "damage delete" << std::endl;
	minDamage = NULL;
	maxDamage = NULL;

}

float GameEngine::UnitDamage::GetDamage() {
	return (maxDamage - minDamage) * ((((float)rand()) / (float)RAND_MAX)) + minDamage;
}

void GameEngine::UnitDamage::Update(){
}
