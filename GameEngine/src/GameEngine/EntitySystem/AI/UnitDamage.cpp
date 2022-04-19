#include "UnitDamage.h"

GameEngine::UnitDamage::UnitDamage() {
	damage = rand() % 1 + 1;
}

GameEngine::UnitDamage::~UnitDamage() {
	damage = NULL;
}

int GameEngine::UnitDamage::GetDamage() {
	return damage;
}