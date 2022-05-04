#pragma once
#include <GameEngine/MathHelper.h>
#include <GameEngine/Log.h>
#include <bx/math.h>
#include <iostream>

namespace GameEngine {

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

		void translate(Vector3 translation);

		void setTranslation(Vector3 translation);

		void rescale(Vector3 scale);

		void rotates(Vector3 axis, float value);

		void rotates(float x, float y, float z);

		Transform operator*(Transform t);

		void print();

		void Update();
	};

}

//https://www.brainvoyager.com/bv/doc/UsersGuide/CoordsAndTransforms/SpatialTransformationMatrices.html