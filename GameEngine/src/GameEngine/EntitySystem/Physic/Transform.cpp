#include <GameEngine/EntitySystem/Physic/Transform.h>



GameEngine::Transform::~Transform() {
	std::cout << "Delete Transform" << std::endl;
}

void GameEngine::Transform::translate(Vector3 translation)
{

	mtx[12] += translation.x;
	mtx[13] += translation.y;
	mtx[14] += translation.z;
}


void GameEngine::Transform::SetTransform(float x_pos, float y_pos, float z_pos) {
	float mtx_mesh[16];
	bx::mtxScale(mtx_mesh, 5);
	mtx_mesh[12] = x_pos;   //left and right
	mtx_mesh[13] = y_pos;   //up and down
	mtx_mesh[14] = z_pos;   //Back and forward

	for (int i = 0; i < 16; i++) {
		mtx[i] = mtx_mesh[i];
	}
}


void GameEngine::Transform::setTranslation(Vector3 translation)
{
	mtx[12] = translation.x;
	mtx[13] = translation.y;
	mtx[14] = translation.z;
}

GameEngine::Transform::Transform(float m[16]) {
	std::cout << "create transform" << std::endl; 
	for (int i = 0; i < 16; i++) {
		mtx[i] = m[i];
	}
}

void GameEngine::Transform::rescale(Vector3 scale) {
	float m[16] = {
		scale.x, 0, 0, 0,
		0, scale.y, 0, 0,
		0, 0, scale.z, 0,
		0, 0, 0, 1
	};
	Transform t = Transform(m);
	*this = t * *this;

}

void GameEngine::Transform::rotates(Vector3 axis, float value) {
	//float m[16];
	//float c = cos(value);
	//float s = sin(value);

	//Vector3 unit_axis = axis.Normalized();

	//float x = unit_axis.x;
	//float y = unit_axis.y;
	//float z = unit_axis.z;

	////formula -> https://en.wikipedia.org/wiki/Rotation_matrix
	//m[0] = x * x * (1 - c) + c;
	//m[1] = x * y * (1 - c) + z * s;
	//m[2] = x * z * (1 - c) - y * s;
	//m[3] = 0;

	//m[4] = x * y * (1 - c) - z * s;
	//m[5] = y * y * (1 - c) + c;
	//m[6] = y * z * (1 - c) + x * s;
	//m[7] = 0;

	//m[8] = x * z * (1 - c) + y * s;
	//m[9] = y * z * (1 - c) - x * s;
	//m[10] = z * z * (1 - c) + c;
	//m[11] = 0;

	//m[12] = 0;
	//m[13] = 0;
	//m[13] = 0;
	//m[15] = 1;
	
	//Transform t = Transform(m);
	//*this = t * *this;
}

void GameEngine::Transform::rotates(float x, float y, float z) {
	float m[16];
	bx::mtxRotateXYZ(m, x, y, z);
	mtx[3] = 0;
	mtx[7] = 0;
	mtx[11] = 0;

	*this = Transform(m) * *this;
}


GameEngine::Transform GameEngine::Transform::operator*(GameEngine::Transform t)
{
	GameEngine::Transform res;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			float sum = 0.0;
			for (int k = 0; k < 4; k++)
				sum = sum + this->mtx[i * 4 + k] * t.mtx[k * 4 + j];
			res.mtx[i * 4 + j] = sum;
		}
	}

	return res;
}

void GameEngine::Transform::print() {
	for (int i = 0; i < 16; i++) {
		std::cout << mtx[i] << " ";
		if (i % 4 == 3) std::cout << std::endl;
	}
	std::cout << std::endl;
}


void GameEngine::Transform::Update(){
	//std::cout << "transform test" << std::endl;
}

