#include <GameEngine/EntitySystem/Physic/Transform.h>


/// <summary>
/// Destruct the collider
/// </summary>
GameEngine::Transform::~Transform() {
	std::cout << "Delete Transform" << std::endl;
	delete(this);
}

/// <summary>
/// Apply a translation to the Transform
/// </summary>
/// <param name="translation"> - Translation to apply</param>
void GameEngine::Transform::translate(Vector3 translation)
{

	mtx[12] += translation.x;
	mtx[13] += translation.y;
	mtx[14] += translation.z;
}


/// <summary>
/// Set the Transform to the given coordinates
/// </summary>
/// <param name="x_pos"> - x coordinate</param>
/// <param name="y_pos"> - y coordinate</param>
/// <param name="z_pos"> - z coordinate</param>
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

/// <summary>
/// Set the Transform to the given coordinates
/// </summary>
/// <param name="translation"> - Translation from origine</param>
void GameEngine::Transform::setTranslation(Vector3 translation)
{
	mtx[12] = translation.x;
	mtx[13] = translation.y;
	mtx[14] = translation.z;
}

/// <summary>
/// Create a Transform from the given spatial transformation matrix
/// </summary>
/// <param name="m"> - spatial transformation matrix</param>
GameEngine::Transform::Transform(float m[16]) {
	std::cout << "create transform" << std::endl; 
	for (int i = 0; i < 16; i++) {
		mtx[i] = m[i];
	}
}

/// <summary>
/// Set the scale of the Transform
/// </summary>
/// <param name="scale"> - New scale</param>
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
/// <summary>
/// <para> WORK IN PROGRESS </para>
/// Rotate the Transform using a rotation axis and an angle value
/// </summary>
/// <param name="axis"> - Rotation axis </param>
/// <param name="value"> - Angle value </param>
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

/// <summary>
/// Rotate the Transform using 3 degrees of rotation
/// </summary>
/// <param name="x"> - rotation angle around x axis</param>
/// <param name="y"> - rotation angle around y axis</param>
/// <param name="z"> - rotation angle around z axis</param>
void GameEngine::Transform::rotates(float x, float y, float z) {
	float m[16];
	bx::mtxRotateXYZ(m, x, y, z);
	mtx[3] = 0;
	mtx[7] = 0;
	mtx[11] = 0;

	*this = Transform(m) * *this;
}


/// <summary>
/// Redefinition of * operator to perform spatial transformation matrix multiplication 
/// </summary>
/// <param name="t"> - second Transform operand</param>
/// <returns> The resulting Transform </returns>
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

/// <summary>
/// Print Transform's spatial transformation matrix in the standart output
/// </summary>
void GameEngine::Transform::print() {
	for (int i = 0; i < 16; i++) {
		std::cout << mtx[i] << " ";
		if (i % 4 == 3) std::cout << std::endl;
	}
	std::cout << std::endl;
}

/// <summary>
/// Update transform values
/// </summary>
void GameEngine::Transform::Update(){
	//std::cout << "transform test" << std::endl;
}

