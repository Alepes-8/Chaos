#pragma
#include <GameEngine/EntitySystem/BaseComponent.h>
#include <GameEngine/MathHelper.h>
#include <GameEngine/Log.h>

namespace GameEngine {
	
	class Transform : public GameEngine::BaseComponent {
	private:
		//coordinates
		Vector3 coordinates, rotation, scale;


	public:
		Transform();

		Transform(Vector3 coordinates, Vector3 rotation, Vector3 scale);

		void translate(Vector3 translation);

		void setRotation(Vector3 rotation);
		
		void rotate(Vector3 axis, float value);

		void setScale(Vector3 scale);

		void rescale(float coef);

		bool isScaleValid(Vector3 scale);

		virtual void update() override;
	};

}