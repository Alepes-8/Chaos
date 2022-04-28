#include "UnitDamage.h"

GameEngine::UnitDamage::UnitDamage(float dmgValue) {
	std::cout << "damage create " << dmgValue << std::endl;
	damage = dmgValue;
}

GameEngine::UnitDamage::~UnitDamage() {
	std::cout << "damage delete" << std::endl;
	damage = NULL;
}

int GameEngine::UnitDamage::GetDamage() {
	return damage;
}

void GameEngine::UnitDamage::Update(){
}
