#include "Team.h"


GameEngine::Team::Team(GameObject* parent, int teamNum) : BaseComponent(parent) {
	team = teamNum;
	std::cout << "Create Team" << std::endl;
}

GameEngine::Team::~Team() {

}

int GameEngine::Team::GetTeam() {
	return team;
}

void GameEngine::Team::Update() {

}