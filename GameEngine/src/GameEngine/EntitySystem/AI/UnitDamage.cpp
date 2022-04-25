#include "UnitDamage.h"

GameEngine::UnitDamage::UnitDamage(float dmgValue) {

	damage = dmgValue;
	std::cout << "damaga create" << std::endl;
}

GameEngine::UnitDamage::~UnitDamage() {
	damage = NULL;
}

int GameEngine::UnitDamage::GetDamage() {
	return damage;
}

void GameEngine::UnitDamage::Update(){
	std::cout << "Update UnitDamage" << std::endl;
}