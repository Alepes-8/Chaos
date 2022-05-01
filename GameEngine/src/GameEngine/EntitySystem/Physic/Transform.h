#pragma once
#include <GameEngine/EntitySystem/BaseComponent.h>
#include <GameEngine/MathHelper.h>
#include <GameEngine/Log.h>
#include <bx/math.h>

namespace GameEngine {

	class Transform : public GameEngine::BaseComponent {
	
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

		void translate(Vector3 translation);

		void setTranslation(Vector3 translation);

		void rescale(Vector3 scale);

		void rotates(Vector3 axis, float value);

		void rotates(float x, float y, float z);

		Transform operator*(Transform t);

		void print();

		virtual void Update() override;
	};

}

//https://www.brainvoyager.com/bv/doc/UsersGuide/CoordsAndTransforms/SpatialTransformationMatrices.html