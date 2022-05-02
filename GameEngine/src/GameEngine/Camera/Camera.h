#pragma once
#include "GameEngine/InputEvents/InputManager.h"
#include <bx/math.h>
#include <bx/bx.h>
#include <bgfx/bgfx.h>
#include <iostream>

namespace GameEngine {
	enum Direction { RIGHT, LEFT, FORWARD, BACKWARD, UP, DOWN };


	class Camera {
	private:
		bx::Vec3 _at = { 0.0f, 0.0f, 0.0f };
		bx::Vec3 _eye = { 0.0f, 0.0f, 10.0f };
		bx::Vec3 _up = { 0.0f, 1.0f, 0.0f };
		
		float camera_speed = 0.5f;
		static Camera* m_Instance;

	public:
		static Camera* CreateInstance();
		static void Terminate();
		void at(float x, float y, float z);
		void eye(float x, float y, float z);
		void up(float x, float y, float z);
		void translate(float x, float y, float z);
		void translate_direction(GameEngine::Direction direction, float speed);
		void reset();
		void listenEvent(GameEngine::InputManager* im);
		
		void Update(GameEngine::InputManager* im, int view_port_id, float screen_width, float screen_height);
		float _view[16];
		float _proj[16];
	};

}