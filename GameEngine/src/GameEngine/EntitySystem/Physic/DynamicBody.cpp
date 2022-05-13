#include "DynamicBody.h"

GameEngine::DynamicBody::DynamicBody(GameObject* parent) : BaseComponent(parent) {
	std::cout << " create dynamic Body" << std::endl;
}

GameEngine::DynamicBody::~DynamicBody() {

}


void GameEngine::DynamicBody::Update() {
	if (CurrentMoveSpeed.x == 0 && CurrentMoveSpeed.y == 0 && CurrentMoveSpeed.z == 0) {
		dynamic_cast<Physics*>(getComponent(0x00000010))->ResetTime();
		return;
	}

	getParentTransform()->Translate(CurrentMoveSpeed);


	CurrentMoveSpeed = physicsComp->CalculateSpeed(CurrentMoveSpeed,
		dynamic_cast<UnitMovement*>(getComponent(0x00000003))->GetMovement());

	
	
	std::cout << CurrentMoveSpeed.x << " " << CurrentMoveSpeed.y << " " << CurrentMoveSpeed.z << std::endl;
}



/*This one will be if we call on the movement with a  button or so*/
void GameEngine::DynamicBody::AddMovement(Vector3 direction) {
	if (physicsComp == nullptr) {
		physicsComp = dynamic_cast<Physics*>(getComponent(0x00000010));
		if (physicsComp == nullptr) {
			std::cout << "Error, No Physics engine" << std::endl;
			return;
		}
	}
	float speed = dynamic_cast<UnitMovement*>(getComponent(0x00000003))->GetMovement();

	CurrentMoveSpeed = physicsComp->CalculateAcceleration(CurrentMoveSpeed, direction, speed);
	/*this will need to change with physics*/
	
}

void GameEngine::DynamicBody::AddRotation(Vector3 direction) {
	UnitMovement* comp = dynamic_cast<UnitMovement*>(getComponent(0x00000003));
	float speed = comp->GetMovement();
}