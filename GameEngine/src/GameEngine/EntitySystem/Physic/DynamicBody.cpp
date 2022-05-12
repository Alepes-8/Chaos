#include "DynamicBody.h"

GameEngine::DynamicBody::DynamicBody(GameObject* parent) : BaseComponent(parent) {
	std::cout << " create dynamic Body" << std::endl;
}

GameEngine::DynamicBody::~DynamicBody() {

}


void GameEngine::DynamicBody::Update() {
	if (CurrentMoveSpeed.x == 0 && CurrentMoveSpeed.y == 0 && CurrentMoveSpeed.z == 0) {
		return;
	}

	getParentTransform()->Translate(CurrentMoveSpeed);
	

	/*
	Here we will have a function which call for the physics so that the unit will move 
	acording the the units speed and not just each press of a button.

	Will store it's current speed in this component. 
	Physics will only help caluclate the new speed
	*/
	if (CurrentMoveSpeed.x > 0) {
		CurrentMoveSpeed.x -= 0.005;
		if (CurrentMoveSpeed.x < 0.01) {
			CurrentMoveSpeed.x = 0;
		}
	}

	if (CurrentMoveSpeed.y > 0) {
		CurrentMoveSpeed.y -= 0.005;
		if (CurrentMoveSpeed.y < 0.01) {
			CurrentMoveSpeed.y = 0;
		}
	}

	if (CurrentMoveSpeed.z > 0) {
		CurrentMoveSpeed.z -= 0.005;
		if (CurrentMoveSpeed.z < 0.01) {
			CurrentMoveSpeed.z = 0;
		}
	}

	if (CurrentMoveSpeed.x < 0) {
		CurrentMoveSpeed.x += 0.005;
		if (CurrentMoveSpeed.x > -0.01) {
			CurrentMoveSpeed.x = 0;
		}
	}

	if (CurrentMoveSpeed.y < 0) {
		CurrentMoveSpeed.y += 0.005;
		if (CurrentMoveSpeed.y > -0.01) {
			CurrentMoveSpeed.y = 0;
		}
	}

	if (CurrentMoveSpeed.z < 0) {
		CurrentMoveSpeed.z += 0.005;
		if (CurrentMoveSpeed.z > -0.01) {
			CurrentMoveSpeed.z = 0;
		}
	}

	/*This will be to lower the movement*/
	
	
	std::cout << CurrentMoveSpeed.x << " " << CurrentMoveSpeed.y << " " << CurrentMoveSpeed.z << std::endl;
}



/*This one will be if we call on the movement with a button or so*/
void GameEngine::DynamicBody::AddMovement(Vector3 direction) {
	float speed = dynamic_cast<UnitMovement*>(getComponent(0x00000003))->GetMovement();

	/*this will need to change with physics*/
	CurrentMoveSpeed.x += speed * direction.x;
	CurrentMoveSpeed.y += speed * direction.y;
	CurrentMoveSpeed.z += speed * direction.z;
}

void GameEngine::DynamicBody::AddRotation(Vector3 direction) {
	UnitMovement* comp = dynamic_cast<UnitMovement*>(getComponent(0x00000003));
	float speed = comp->GetMovement();
}