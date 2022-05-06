#pragma once
#include <iostream>


namespace GameEngine {

	//forward declaration
	class GameObject;
	class Transform;

	class BaseComponent{
	protected:
		GameObject* parent;

	public:
		BaseComponent(GameObject* parent);

		// Get the Transform of the GameObject that owns this Base Component
		GameEngine::Transform* getParentTransform();

		~BaseComponent();

		virtual void Update();
	};
}