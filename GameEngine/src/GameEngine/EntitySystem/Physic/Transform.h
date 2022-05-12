#pragma once
#include <GameEngine/MathHelper.h>
#include <GameEngine/Log.h>
#include <bx/math.h>
#include <iostream>

namespace GameEngine {
	typedef struct Position {
		float pos[3];
	};
	class Transform {
	
	public:

		float mtx[16] = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
		};



		Transform() {}

		Transform(float m[16]);

		~Transform();

		void SetTransform(float x_pos, float y_pos, float z_pos);

		void Translate(Vector3 translation);

		void SetTranslation(Vector3 translation);

		Position getPosition();

		void Rescale(Vector3 scale);

		void Rotates(Vector3 axis, float value);

		void Rotates(float x, float y, float z);

		Transform operator*(Transform t);

		void Print();

		void Update();


	};

}

//https://www.brainvoyager.com/bv/doc/UsersGuide/CoordsAndTransforms/SpatialTransformationMatrices.html